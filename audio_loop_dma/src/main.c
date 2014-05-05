//////////////////////////////////////////////////////////////////////////////
// DIGITALA MUSIKEFFEKTER MED DSP
// * File name: main.c
// *                                                                          
// * Description:  Main function.
// *                                                                                                                                              
//////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "usbstk5505.h"
#include "aic3204.h"
#include "PLL.h"
#include "stereo.h"
#include "Dsplib.h"

#include "EQ.h"

#define BUFFER_SIZE 128
Int16 left_in_buffer[BUFFER_SIZE];  
Int16 right_in_buffer[BUFFER_SIZE];   

Int16 left_out_buffer[BUFFER_SIZE];  
Int16 right_out_buffer[BUFFER_SIZE]; 

Int16 *li = &left_in_buffer[0];
Int16 *ri = &right_in_buffer[0];
Int16 *lo = &left_out_buffer[0];
Int16 *ro = &right_out_buffer[0];

Int16 *tmpL;
Int16 *tmpR;

Int16 counter = 0;

//Filter coeff. buffer
Int16 *H = &coeff_buffer[0];

Int16 left_input;
Int16 right_input;
Int16 left_output;
Int16 right_output;
Int16 mono_input;

//Delay buffers
Int16  *dbptrL = &dbL[0];
Int16  *dbptrR = &dbR[0];

#define SAMPLES_PER_SECOND 48000
#define GAIN_IN_dB         0

unsigned int i = 0;
int new_filter = 1;

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  main( )                                                                 *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void main( void ) 
{
	a[0] = 255;
	a[1] = 255;
	a[2] = 255;
	a[3] = 255;
	a[4] = 255;
	a[5] = 255;
	a[6] = 255;

	/* clear delay buffers */ 
	for (i = 0; i < (FFT_LENGTH+2); i++) dbL[i] = 0;  // clear delay buffer (a must)
	for (i = 0; i < (FFT_LENGTH+2); i++) dbR[i] = 0;  // clear delay buffer (a must)
	
	/* clear in/out buffers */
	for (i = 0; i < (BUFFER_SIZE); i++) left_in_buffer[i] = 0;
	for (i = 0; i < (BUFFER_SIZE); i++) left_out_buffer[i] = 0;
	for (i = 0; i < (BUFFER_SIZE); i++) right_in_buffer[i] = 0;
	for (i = 0; i < (BUFFER_SIZE); i++) right_out_buffer[i] = 0;
	
    /* Initialize BSL */
    USBSTK5505_init( );
    
    /* Initialize the Phase Locked Loop in EEPROM */
    pll_frequency_setup(100);
    
	/* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();
    
    /* Initialise the AIC3204 codec */
	aic3204_init(); 

    printf("\n\nRunning FIR Filters Project\n");
    printf( "<-> Audio Loopback from Stereo Line IN --> to HP/Lineout\n\n" );
	
	/* Set sampling frequency in Hz and ADC gain in dB */
    set_sampling_frequency_and_gain(SAMPLES_PER_SECOND, GAIN_IN_dB); 

    asm(" bclr XF");
    
 	while (1)
 	{
 		if (new_filter>0)
		{		
			new_filter--;
			EQCoeff(a, H);
		}

		aic3204_codec_read(&left_input, &right_input); // Configured for one interrupt per two channels.
		
		/* Store latest input in buffer */
	  	li[counter] = left_input; 
		ri[counter] = right_input;
		
		//left_output = lo[counter]; 
	    //right_output = ro[counter];
		
	 	if ( counter < (BUFFER_SIZE-1))
	    {
	    	counter++; /* Point to next buffer location */
	    } 
	 	else if (counter == (BUFFER_SIZE-1))
	    {
	     	/* Receive buffer is now full */
	     	tmpL = li;
	     	tmpR = ri;
	     	
	     	li=lo;
	     	ri=ro;
	     	
	     	lo=tmpL;
	     	ro=tmpR;
	    	
	    	counter = 0; /* Reset counter */    
	    }
	    
	    (void)fir2(&left_input, H, &left_output, dbptrL, 1, FFT_LENGTH);
		(void)fir2(&right_input, H, &right_output, dbptrR, 1, FFT_LENGTH);
		
	    //mono_input = stereo_to_mono(left_input, right_input);
		 
	    //left_output =  left_input;            // Very simple processing. Replace with your own code!
	    //right_output = right_input;          // Directly connect inputs to outputs.
	      
	    aic3204_codec_write(left_output, right_output);
 	}
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  End of main.c                                                           *
 *                                                                          *
 * ------------------------------------------------------------------------ */


