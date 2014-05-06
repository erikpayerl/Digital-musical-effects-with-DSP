//////////////////////////////////////////////////////////////////////////////
// DIGITALA MUSIKEFFEKTER MED DSP
// * File name: main.c
// *                                                                          
// * Description:  Main function.
// *                                                                          
// * Tomas McKelvey 2013-11-20                                                                        
//////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "ezdsp5535.h"
#include "ezdsp5535_i2s.h"
#include "ezdsp5535_i2c.h"
#include "aic_dma.h"
#include "dsplib.h"
#include "stdlib.h"
#include "math.h"
#include "tms320.h"
#include "hwafft.h"
#include "time.h"


#include "EQfilter.h"

extern void systemInit(void);

extern Int16 aic3204_init(unsigned long SamplingFrequency, unsigned int ADCgain);
extern Int16 aic3204_close( );

extern int dma_init(void);

extern Int16 led_test( );

extern void EQfilter( DATA *A, DATA *H );


/*
 *
 *  main( )
 *
 */
#define SAMPLES_PER_SECOND 48000	//12000, 24000, 48000

 int data_ready;
 extern int pp;

/*//Vet ej vad dessa variabler gör. Bruset försvan då dessa togs bort!
 int rec_data;
 int * ptr;
 int enable_lms = 0;
 int pp0=0;
 int pp1=0;
 */

 int new_filter = 1;

//Delay buffers
DATA  *dbptrL = &dbL[0];
DATA  *dbptrR = &dbR[0];

//Filter coeff. buffer
//DATA *H = &coeff_buffer[0];
  
/* Tidigare var dmaBuffrarna av typen unsigned int. Bytte till datatypen DATA som dsplib använder sig av.
   DATA är Q15 format, dvs signed int16, och spara tal mellan -1 och 1. /Erik P */

/* Buffers for L/R audio input/receive */
extern DATA dmaPingDstBufLR[CSL_DMA_BUFFER_SIZE];
extern DATA dmaPongDstBufLR[CSL_DMA_BUFFER_SIZE];
extern DATA dmaPingDstBufRR[CSL_DMA_BUFFER_SIZE];
extern DATA dmaPongDstBufRR[CSL_DMA_BUFFER_SIZE];

/* Declaration of the L/R audio output/send buffers */
extern DATA dmaPingSrcBufLS[CSL_DMA_BUFFER_SIZE];
extern DATA dmaPongSrcBufLS[CSL_DMA_BUFFER_SIZE];
extern DATA dmaPingSrcBufRS[CSL_DMA_BUFFER_SIZE];
extern DATA dmaPongSrcBufRS[CSL_DMA_BUFFER_SIZE];


void main( void )
{ 	   	
	clock_t start, stop, overhead;
		
	int index;
	Int32 *complex_data, *bitrev_data, *scratch, *fft_data;
	Uint16 out_sel;
	Int16 x, i, dF;
	DATA H[FFT_LENGTH];
	
	//EQ-band 
	DATA A[7];
	Uint8 a[7];

	short filter = 1; 
	
	start = clock(); /* Calculate the overhead of calling clock */
	stop = clock(); /* and subtract this amount from the results. */
	overhead = stop - start;	
	
	/* Initialize board */
    systemInit();
		
    /* Initialize BSL */
    EZDSP5535_init( );

    printf( "\nInitializing AIC3204...\n");

    /* Initialize I2C */
    EZDSP5535_I2C_init( );

    /* Call aic init */
    aic3204_init(SAMPLES_PER_SECOND,0);
    
    /* LED test */
    //led_test( );

    /* Call dma init */
    dma_init( );
    
	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * 
	 * Funktionsanrop efter dma_init() förvränger ljudet av någon anledning!
	 * 
	 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 */ 

	/* clear delay buffers */ 
	for (i = 0; i < (FFT_LENGTH+2); i++) dbL[i] = 0;  // clear delay buffer (a must)
	for (i = 0; i < (FFT_LENGTH+2); i++) dbR[i] = 0;  // clear delay buffer (a must)
	
	/* EQ-band gains, 0-1 -> Uint8 0 - 255 */
	
	a[0] = 0;
	a[1] = 255;
	a[2] = 0;
	a[3] = 255;
	a[4] = 0;
	a[5] = 0;
	a[6] = 0;
	
	/* Map Uint8 to DATA (Int32) */
	A[0] = (DATA)(a[0]) << 7;
	A[1] = (DATA)(a[1]) << 7;
	A[2] = (DATA)(a[2]) << 7;
	A[3] = (DATA)(a[3]) << 7;
	A[4] = (DATA)(a[4]) << 7;
	A[5] = (DATA)(a[5]) << 7;
	A[6] = (DATA)(a[6]) << 7;

	while (1) // eternal loop
	{
		/* Calculate new EQ-filter coeff. 
		 * Cycles approx= 110 * FFT_LENGTH 7752 15802 32000 55621
		 * */
		if (new_filter>0)
		{			
			//start = clock();
			new_filter--;
			dF = 32768/FFT_LENGTH;
			
			for (i=0;i < (FFT_LENGTH/2) ;i++) {
				x = i*dF; 
				if (x<fc[0])
					H[i] = A[0];
				else if (x<fc[1])
					H[i] = A[1];
				else if (x<fc[2])
					H[i] = A[2];
				else if (x<fc[3])
					H[i] = A[3];
				else if (x<fc[4])
					H[i] = A[4];
				else if (x<fc[5])
					H[i] = A[5];
				else if (x<13763) // 0.42 normalized freq, approx 20000 Hz
					H[i] = A[6];
				else
					H[i] = 0;
					//H[i]=(DATA)(-13*(Int32)(x)+212160);
			}
			
			/* Phase = exp(-1i*pi*k)= 1, -1, 1 -1,...  , k = 0,1,2,... */
			for (i=1;i<(FFT_LENGTH/2);i+=2)    H[i]=-H[i];
			
			/* Linear phase -> H(FFT_LENGTH-k) = *H(k) */
			for (i=0;i<(FFT_LENGTH/2 -1);i++) 	H[FFT_LENGTH-1-i] = H[i+1];
			
			/* FFT_LENGTH = EVEN -> H[FFT_LENGTH/2] = 0, for linear phase */
			H[FFT_LENGTH/2] = 0;
			
			/* Initialize relevant pointers */
			bitrev_data  = bitreversed_buffer;
			scratch = scratch_buffer;
			complex_data = complex_buffer;
			
			/* Convert real data to "pseudo"-complex data (real, 0) */
			/* Int32 complex = Int16 real (MSBs) + Int16 imag (LSBs) */
			for (i = 0; i < FFT_LENGTH; i++) {
				*(complex_data + i) = ( (Int32) (*(H + i)) ) << 16;
			}
		
			/* Perform bit-reversing */
			hwafft_br(complex_data, bitrev_data, FFT_LENGTH);
		
			/* Perform iFFT */
			if (FFT_LENGTH==512) {
				out_sel = hwafft_512pts(bitrev_data, scratch, IFFT_FLAG, SCALE_FLAG);
			} else if (FFT_LENGTH==256) {
				out_sel = hwafft_256pts(bitrev_data, scratch, IFFT_FLAG, SCALE_FLAG);
			}
		
			/* Return appropriate data pointer */
			if (out_sel == OUT_SEL_DATA) {
				fft_data = bitrev_data; // results stored in this data vector 
			}else {
				fft_data = scratch; // results stored in this scratch vector 
			}
		
			/* Extract real part  */
			for (i = 0; i < FFT_LENGTH; i++) {
				*(H + i) = (Int16)((*(fft_data + i)) >> 16);
				//*(imagR + i) = (Int16)((*(fft_data + i)) & 0x0000FFFF);
			}
			
			/* Window */
			//for (i = 0; i < FFT_LENGTH; i++ ) { 	H[i] = (DATA)(((LDATA)(DATA)H[i] * (LDATA)(DATA)blackman512[i]) >> 15);	}
			
			//stop = clock();
			//printf("cycles: %ld\n", (long)(stop - start - overhead));
			//index = test();
		}
		
 		if (data_ready>0)
 		{               
            data_ready--;
        	if (pp == 0){
    		// PING EVENT
    		
    			if (filter)
    			{
    				/*
    				for(index = 0; index < CSL_DMA_BUFFER_SIZE; index++)
					{
						dmaPingDstBufLR[index] = dmaPingDstBufLR[index] >> 2;
						dmaPingDstBufRR[index] = dmaPingDstBufRR[index] >> 2;
	      			};*/
	      			
	    			/* compute 2-chanels: cycles 260000, ca 130000 pro chanel , 790355 */
	    			//start = clock();
	    			(void)fir2(dmaPingDstBufLR, H, dmaPingSrcBufLS, dbptrL, CSL_DMA_BUFFER_SIZE, FFT_LENGTH);	    			
	    			(void)fir2(dmaPingDstBufRR, H, dmaPingSrcBufRS, dbptrR, CSL_DMA_BUFFER_SIZE, FFT_LENGTH);
	    			//stop = clock();
					//printf("cycles: %ld\n", (long)(stop - start - overhead));
    			}
    			else
				{			  
					for(index = 0; index < CSL_DMA_BUFFER_SIZE; index++)
					{
						dmaPingSrcBufLS[index] = dmaPingDstBufLR[index];  // Feed through L/R Audio
						dmaPingSrcBufRS[index] = dmaPingDstBufRR[index];
	      			};
				}
			}
  			else //  PONG EVENT
  			{  	
				if (filter)
				{
					/*
					for(index = 0; index < CSL_DMA_BUFFER_SIZE; index++)
					{
						dmaPongDstBufLR[index] = dmaPongDstBufLR[index] >> 2;
						dmaPongDstBufRR[index] = dmaPongDstBufRR[index] >> 2;
	      			};*/
					
	  				// compute
	    			(void)fir2(dmaPongDstBufLR, H, dmaPongSrcBufLS, dbptrL, CSL_DMA_BUFFER_SIZE, FFT_LENGTH);
	    			(void)fir2(dmaPongDstBufRR, H, dmaPongSrcBufRS, dbptrR, CSL_DMA_BUFFER_SIZE, FFT_LENGTH);
				}
				else
				{
	  				for(index = 0; index < CSL_DMA_BUFFER_SIZE; index++)
	      			{
						dmaPongSrcBufLS[index] = dmaPongDstBufLR[index];  // Feed through L/R Audio
						dmaPongSrcBufRS[index] = dmaPongDstBufRR[index];
	
	      			};
				}
			}
		}       
	}	
}
