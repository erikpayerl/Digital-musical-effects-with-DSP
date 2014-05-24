/*****************************************************************************/
/* stereo_to_mono()                                                          */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* INPUTS:  left and right channel (stereo) information.                     */
/*                                                                           */
/* RETURNS: Average of two input channels (mono)                             */
/*                                                                           */
/*****************************************************************************/

#include "csl_intc.h"

Int16 stereo_to_mono(Int16 left_channel, Int16 right_channel)
{
	Int32 temp;
 
	/* Take average of left and right channels. */
 
	temp = (Int32) left_channel + (Int32) right_channel;
 
	//temp >>= 1;    /* Divide by 2 to prevent overload at output */
	temp = temp/2;
 
	return ((Int16) temp); /* Return mono value to calling function */
}

void stereo_to_mono_buffer(Int16 *left_channel, Int16 *right_channel, Int16 *mono_out, Int16 nx)
{
	Int16 i;
 
	/* Take average of left and right channels. */
 	for(i = 0; i < nx; i++)
	{
		mono_out[i] = (Int16)((Int32) left_channel[i] + (Int32) right_channel[i])/2;
	} 
}
