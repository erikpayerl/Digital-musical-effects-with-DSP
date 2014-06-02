//////////////////////////////////////////////////////////////////////////////
// DIGITALA MUSIKEFFEKTER MED DSP
// * File name: main.c
// *                                                                          
// * Description:  Main function.
// *                               
// * Erik Payerl, Erik Sandgren, Gustaf Johansson  
// * Rickard Dahl, Omid Fassihi - 2014-05-24                                                                                                               
//////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "usbstk5505.h"
#include "aic3204.h"
#include "PLL.h"
#include "stereo.h"

#include "EQfilter.h"

#include "uart_config.h"
#include "csl_uart.h"

#include "vibrato.h"
#include "flanger.h"

/* ----------- Musical effects ------------ */
extern Int16 svf(Int16 s, Int16 F1, Int16 Q1, Int16 opmode);
extern Int16 fuzz(Int16 s, Int16 th, Int16 pG, Int16 opmode);
extern Int16 tremolo(Int16 sample, Int16 LFOspeed, Int16 depth, Int16 opmode);
extern Int16 echo(Int16 latest_input, Int16 depth, Int16 buffer_length, Int16 opmode);
extern Int16 reverb( Int16 latest_input, Int16 depth, Int16 rsvd, Int16 opmode); 
//extern Int16 vibrato(Int16 sample, Int16 LFOspeed, Int16 depth, Int16 opmode);
//extern Int16 flanger(Int16 sample, Int16 LFOspeed, Int16 depth, Int16 opmode);

extern void echo_array_clear(void);
extern void reverb_array_clear(void);

/* Declared in EQfilter.h 
 * Int16 EQ(Int16 s, Int16 not_used1, Int16 not_used2, Int16 not_used3);
 * void EQcoeff( Uint8 *a );
 * void EQ_clear(); */
 
 Int16 (*fx[8])(Int16 s, Int16 a, Int16 b, Int16 opmode);
/* ----------------------------------------- */

/* --- Uart communication with interface --- */
extern CSL_UartHandle hUart;

int START_OF_MESSAGE = 255;
int messagestart = 0;

char rx[4];
int i = 0;
int data_ready;

/* Parameters from interface */
int e_index = 4;
int opmode = 0;
int param1 = 128;
int param2 = 200;
/* ------------------------------------------ */

/* --- Audio --- */
Int16 left_input;
Int16 right_input;
Int16 left_output;
Int16 right_output;
Int16 mono_input;

#define SAMPLES_PER_SECOND 48000
#define GAIN_IN_dB         0

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  main( )                                                                 *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void main( void ) 
{
	/* Initialize function pointers */
	fx[0] = svf;
	fx[1] = fuzz;
	fx[2] = tremolo; //tremolo;
	fx[3] = echo;
	fx[4] = reverb;
	fx[5] = EQ;
	fx[6] = vibrato;
	fx[7] = flanger;
	
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
	
	/* Calculate new EQ filter */
	(void)EQCoeff(a);
	
	/* Clear arrays used in different music effects */
	echo_array_clear();
	reverb_array_clear();
	EQ_clear();
		
    /* Initialize BSL */
    USBSTK5505_init( );
    
    /* Initialize the Phase Locked Loop in EEPROM */
    pll_frequency_setup(100); //100MHz
    
	/* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();
    
    /* Initialise the AIC3204 codec */
	aic3204_init(); 
	
	/* Set sampling frequency in Hz and ADC gain in dB */
    set_sampling_frequency_and_gain(SAMPLES_PER_SECOND, GAIN_IN_dB); 
    
    /* Call uart init */
	uart_init();

    asm(" bclr XF");
    
    /* Infinite loop */
 	while (1)
 	{
 		/* Get parameters from user interface*/
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
				
				if (e_index == 5) 
				{
					a[param1] = param2; //Sets amplitude of band # param1
					(void)EQCoeff(a); //Calculate new EQ filter
				} 
			}
		}

		/* Configured for one interrupt per two channels. */
		aic3204_codec_read(&left_input, &right_input); 

		mono_input = stereo_to_mono(left_input, right_input);
		
		/* Compute music effect */
		right_output =  left_output = (*fx[e_index])(mono_input, param1, param2, opmode);

	    aic3204_codec_write(left_output, right_output);
 	}
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  End of main.c                                                           *
 *                                                                          *
 * ------------------------------------------------------------------------ */
