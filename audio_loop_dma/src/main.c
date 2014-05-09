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
#include "time.h"
#include "stereo.h"

#include "EQfilter.h"

extern void systemInit(void);

extern Int16 aic3204_init(unsigned long SamplingFrequency, unsigned int ADCgain);
extern Int16 aic3204_close( );
extern int dma_init(void);
extern Int16 led_test( );

#define SAMPLES_PER_SECOND 48000	//12000, 24000, 48000

int data_ready;
extern int pp;

int new_filter = 1;
short filter = 1;

//Delay buffers
DATA  *dbptrL = &dbL[0];
DATA  *dbptrR = &dbR[0];

//Filter coeff. buffer
DATA *H = &coeff_buffer[0];
  
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

Uint16 monoInputPing[CSL_DMA_BUFFER_SIZE];
Uint16 monoInputPong[CSL_DMA_BUFFER_SIZE];

void main( void )
{ 	   	
	clock_t start, stop, overhead;
		
	int index;
	Int16 i;
	
	int oflagL=0;
	int oflagR=0;
	
	int no_overflow=1;
	
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

	/* clear delay buffers */ 
	for (i = 0; i < (FFT_LENGTH+2); i++) dbL[i] = 0;  // clear delay buffer (a must)
	for (i = 0; i < (FFT_LENGTH+2); i++) dbR[i] = 0;  // clear delay buffer (a must)
	
	/* EQ-band gains, 0-1 -> Uint8 0 - 255 */
	a[0] = 255;
	a[1] = 255;
	a[2] = 0;
	a[3] = 0;
	a[4] = 0;
	a[5] = 0;
	a[6] = 0;
	a[7] = 0;

	while (no_overflow) // eternal loop
	{
		/* Calculate new EQ-filter coeff.                         *
		 * Cycles approx= 110 * FFT_LENGTH 7752 15802 32000 55621 */
		if (new_filter>0)
		{			
			//start = clock();
			new_filter--;
			(void)EQfilter(a, H);
			
			/* Print filter coeff. */
			//for (i = 0; i < FFT_LENGTH; i++ ) { 	printf("%d\n",*(H + i)); }
			
			//stop = clock();
			//printf("cycles: %ld\n", (long)(stop - start - overhead));
		}
				
 		if (data_ready>0)
 		{               
            data_ready--;
        	if (pp == 0){
    		// PING EVENT
    		
    			if (filter==1)
    			{		      			
	    			/* compute 2-chanels: cycles 260000, ca 130000 pro chanel , 790355 */
	    			//start = clock();
	    			oflagL=fir2(dmaPingDstBufLR, H, dmaPingSrcBufLS, dbptrL, CSL_DMA_BUFFER_SIZE, FFT_LENGTH);	    			
	    			oflagR=fir2(dmaPingDstBufRR, H, dmaPingSrcBufRS, dbptrR, CSL_DMA_BUFFER_SIZE, FFT_LENGTH);
	    			
	      			if (oflagL==1 || oflagR==1){
	      				no_overflow=0;
					}
	      			
	    			//stop = clock();
					//printf("cycles: %ld\n", (long)(stop - start - overhead));
    			}
    			else if (filter==2)
    			{
    				for(index = 0; index < CSL_DMA_BUFFER_SIZE; index++)
	      			{
    					dmaPingSrcBufLS[index] = dmaPingSrcBufRS[index] = stereo_to_mono(dmaPingDstBufLR[index], dmaPingDstBufRR[index]);
	      			}
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
				if (filter==1)
				{				
	  				// compute
	    			oflagL=fir2(dmaPongDstBufLR, H, dmaPongSrcBufLS, dbptrL, CSL_DMA_BUFFER_SIZE, FFT_LENGTH);
	    			oflagR=fir2(dmaPongDstBufRR, H, dmaPongSrcBufRS, dbptrR, CSL_DMA_BUFFER_SIZE, FFT_LENGTH);
	    			
	    			if (oflagL==1 || oflagR==1){
	      				no_overflow=0;
					}
				}
				else if (filter==2)
    			{
    				for(index = 0; index < CSL_DMA_BUFFER_SIZE; index++)
	      			{
 						dmaPongSrcBufLS[index] = dmaPongSrcBufRS[index] = stereo_to_mono(dmaPongDstBufLR[index], dmaPongDstBufRR[index]);  // Feed through L/R mono audio
	      			}  				
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
	printf("overflow");
	aic3204_close( );
}
