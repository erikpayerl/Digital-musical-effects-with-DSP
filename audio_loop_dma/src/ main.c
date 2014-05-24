//////////////////////////////////////////////////////////////////////////////
// DIGITALA MUSIKEFFEKTER MED DSP
// * File name: main.c
// *                                                                          
// * Description:  Main function.
// * 
// * Erik Payerl    2014-05-09                                                                         
// * Tomas McKelvey 2013-11-20                                                                        
//////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "ezdsp5535.h"
#include "ezdsp5535_i2s.h"
#include "ezdsp5535_i2c.h"
#include "aic_dma.h"
#include "dsplib.h"
#include "stdlib.h"
#include "tms320.h"
#include "time.h"
#include "stereo.h"

#include "uart_config.h"
#include "csl_uart.h"

#include "EQfilter.h"

extern void systemInit(void);

extern Int16 aic3204_init(unsigned long SamplingFrequency, unsigned int ADCgain);
extern Int16 aic3204_close( );
extern int dma_init(void);

/* Musical effects */
extern Int16 svf(Int16 s, Int16 F1, Int16 Q1, Int16 opmode);
extern Int16 fuzz(Int16 s, Int16 th, Int16 pG, Int16 opmode);
extern Int16 tremolo(Int16 sample, Int16 LFOspeed, Int16 depth, Int16 opmode);
extern Int16 echo(Int16 latest_input, Int16 depth, Int16 buffer_length, Int16 opmode);
extern Int16 reverb( Int16 latest_input, Int16 depth, Int16 rsvd, Int16 opmode);
extern void echo_array_clear(void);
extern void reverb_array_clear(void);

extern int pp;

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

extern CSL_UartHandle hUart;

int START_OF_MESSAGE = 255;
int messagestart = 0;

int data_ready;
int opmode = 0;
int param1 = 128;
int param2 = 200;
int e_index = 4;

char rx[5];
int i = 0;

Int16 (*fx[5])(Int16 s, Int16 a, Int16 b, Int16 opmode);

int new_EQ_filter = 1; //If>0 new EQ filter is calculated

//Delay buffers for EQ fir filtering
DATA  *dbptr = &db[0];

//EQ Filter coeff. buffer
DATA *H = &coeff_buffer[0];
  
/* Mono sound data buffers */
Int16 monoInputPing[CSL_DMA_BUFFER_SIZE];
Int16 monoInputPong[CSL_DMA_BUFFER_SIZE];

#define SAMPLES_PER_SECOND 48000	//12000, 24000, 48000

void main( void )
{ 	   	
	//clock_t start, stop, overhead; //For profiling...
		
	int index;
	
	fx[0] = svf;
	fx[1] = fuzz;
	fx[2] = tremolo;
	fx[3] = echo;
	fx[4] = reverb;
	
	/* EQ-band gains, 0-1 -> Uint8 0 - 255 */
	/* Default values */
	a[0] = 128;
	a[1] = 128;
	a[2] = 128;
	a[3] = 128;
	a[4] = 128;
	a[5] = 128;
	a[6] = 128;
	a[7] = 128;
	
	/* Clear delay buffers for EQ fir filters*/ 
	for (index = 0; index < (FFT_LENGTH+2); index++) db[index] = 0;  // clear delay buffer (a must)
	
	echo_array_clear();
	reverb_array_clear();
	
	/* Initialize board */
    systemInit();
		
    /* Initialize BSL */
    EZDSP5535_init( );

    printf( "\nInitializing AIC3204...\n");

    /* Initialize I2C */
    EZDSP5535_I2C_init( );

    /* Call aic init */
    aic3204_init(SAMPLES_PER_SECOND,0);
        
    /* Call dma init */
    dma_init( );
    
    /* Call uart init */
	uart_init();

	//start = clock(); /* Calculate the overhead of calling clock */
	//stop = clock(); /* and subtract this amount from the results. */
	//overhead = stop - start;	
	
	while (1) // eternal loop
	{
		if(CSL_FEXT(hUart->uartRegs->LSR, UART_LSR_DR))
		{
			if(messagestart == 0)
				rx[0] = CSL_FEXT(hUart->uartRegs->RBR,UART_RBR_DATA);
			else 
			{
				rx[i] = CSL_FEXT(hUart->uartRegs->RBR,UART_RBR_DATA);
				i++;
			}
			
			if(rx[0] == START_OF_MESSAGE)
				messagestart = 1;
			//printf("%i\nBREAK\n", rx[i]);//, param2, opmode);
			
			if(i > 3) 
			{
				e_index = (int)rx[0];
				param1 = (int)rx[1];
				param2 = (int)rx[2];
				opmode = (int)rx[3];
				i = 0;
				messagestart = 0;
				//printf("e_index %i \n param1 %i \n param2 %i \n opmode %i \n", e_index,param1,param2,opmode);
				
				/* EQ */
				if (e_index == 5) 
				{
					a[param1] = param2; //Sets amplitude of band # param1
					new_EQ_filter++; //Set flag to calculate new EQ filter
				} 	
			}
	   	}
		/* Calculate new EQ-filter coeff. */
		if (new_EQ_filter>0)
		{			
			//start = clock();
			new_EQ_filter--;
			(void)EQcoeff(a, H);
			
			/* Print filter coeff. */
			//for (index = 0; index < FFT_LENGTH; index++ ) { 	printf("%d\n",*(H + index)); }
			
			//stop = clock();
			//printf("cycles: %ld\n", (long)(stop - start - overhead));
		}
				
 		if (data_ready>0)
 		{               
            data_ready--;
        	if (pp == 0)
        	{
    		// PING EVENT
			
			stereo_to_mono_buffer(dmaPingDstBufLR, dmaPingDstBufRR, monoInputPing, CSL_DMA_BUFFER_SIZE);
			
			
    			if (e_index==5) //EQ
    			{		      			
	    			/* compute 2-chanels: cycles ca 790000 when FFT_LENGTH = 512 */
	    			//start = clock();
	    			(void)fir2(monoInputPing, H, dmaPingSrcBufLS, dbptr, CSL_DMA_BUFFER_SIZE, FFT_LENGTH);	    			
	      			
	      			//stop = clock();
					//printf("cycles: %ld\n", (long)(stop - start - overhead));
					
	      			for(index = 0; index < CSL_DMA_BUFFER_SIZE; index++)
	      			{
    					dmaPingSrcBufRS[index] = dmaPingSrcBufLS[index] <<=  1;
	      			}
	      			
    			}
    			else 
    			{
    				
    				for(index = 0; index < CSL_DMA_BUFFER_SIZE; index++)
	      			{   
	      				//start = clock();					
    					//monoInputPing[index] = stereo_to_mono(dmaPingDstBufLR[index], dmaPingDstBufRR[index]);
						dmaPingSrcBufRS[index] = dmaPingSrcBufLS[index] = (*fx[e_index])(monoInputPing[index], param1, param2, opmode);
						//stop = clock();
						//printf("cycles: %ld\n", (long)(stop - start - overhead));
	      			}
	      			
    			}
			}
  			else //  PONG EVENT
  			{  	
  		
  				stereo_to_mono_buffer(dmaPongDstBufLR, dmaPongDstBufRR, monoInputPong, CSL_DMA_BUFFER_SIZE);
  				
				if (e_index==5) //EQ
				{				
	  				/* compute 2-chanels: cycles ca 790000 when FFT_LENGTH = 512 */
	    			(void)fir2(monoInputPong, H, dmaPongSrcBufLS, dbptr, CSL_DMA_BUFFER_SIZE, FFT_LENGTH);
	    				    			
	    			for(index = 0; index < CSL_DMA_BUFFER_SIZE; index++)
	      			{
    					dmaPongSrcBufRS[index] = dmaPongSrcBufLS[index] *=  2;
	      			}
				}
				else
    			{
    				for(index = 0; index < CSL_DMA_BUFFER_SIZE; index++)
	      			{
 						//monoInputPong[index] = stereo_to_mono(dmaPongDstBufLR[index], dmaPongDstBufRR[index]);
      					dmaPongSrcBufRS[index] = dmaPongSrcBufLS[index] = (*fx[e_index])(monoInputPong[index], param1, param2, opmode);
	      			}  				
    			}
			}
		}       
	}	
	//aic3204_close( );
}
