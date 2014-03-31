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
#include <stdlib.h>
#include <math.h>
#include <tms320.h>

#include "lowpassFIR.h"


extern Int16 aic3204_init( );
extern Int16 aic3204_close( );

extern int dma_init(void);

/*
 *
 *  main( )
 *
 */
 int rec_data;
 int * ptr;
 int data_ready;
 int enable_lms = 0;
 extern int pp;
 int pp0=0;
 int pp1=0;

//Delay buffers
DATA  *dbptrL = &dbL[0];
DATA  *dbptrR = &dbR[0];
  
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
	short i;
	int index;
	
	short filter = 0; 
	
    /* Initialize BSL */
    EZDSP5535_init( );

    printf( "\nInitializing AIC3204...\n");

    /* Initialize I2C */
    EZDSP5535_I2C_init( );

    /* Call aic init */
    aic3204_init( );

    /* Call dma init */
    dma_init( );

	/* clear delay buffers */ 
	for (i = 0; i < (NH+2); i++) dbL[i] = 0;  // clear delay buffer (a must)
	for (i = 0; i < (NH+2); i++) dbR[i] = 0;  // clear delay buffer (a must)

	while (1) // eternal loop
	{
		
 		if (data_ready>0)
 		{               
            data_ready--;
        	if (pp == 0){
    		// PING EVENT
    		
    			if (filter)
    			{
	    			// compute
	    			(void)fir2(dmaPingDstBufLR, h, dmaPingSrcBufLS, dbptrL, CSL_DMA_BUFFER_SIZE, NH);
	    			(void)fir2(dmaPingDstBufRR, h, dmaPingSrcBufRS, dbptrR, CSL_DMA_BUFFER_SIZE, NH);
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
					
	  				// compute
	    			(void)fir2(dmaPongDstBufLR, h, dmaPongSrcBufLS, dbptrL, CSL_DMA_BUFFER_SIZE, NH);
	    			(void)fir2(dmaPongDstBufRR, h, dmaPongSrcBufRS, dbptrR, CSL_DMA_BUFFER_SIZE, NH);
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
