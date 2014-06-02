//////////////////////////////////////////////////////////////////////////////
// * File name:    echo.c
// * 
// * Function:     echo_array_clear, echo                                                                       
// * Description:  Applies a echo-effect on input sample. 
// *                                                                                     
// * Usage:        Int16  = echo(    Int16 latest_input,         // input sample
// *                                 Int16 buffer_length, 		// sets the length of the buffer range (0-254)
// *                                 Int16 depth, 				// decides the maximum delay, range (0-254)
// *                                 Int16 opmode,				//  not used.
// *
// * Gustaf Johansson   2014-06-02                                                           
//////////////////////////////////////////////////////////////////////////////

#include "ezdsp5535.h"
 
#define N 12000 //12000

signed int echo_array1[N]; /* buffer for maximum 0.25s delay at 48kHz sampel freq */
signed int echo_array2[N];
signed int echo_array3[N];

/* clears buffers used by the echo-effect*/
void echo_array_clear(void) {
	int i;
 
	for ( i = 0 ; i < N ; i++) {
		echo_array1[i] = 0;
		echo_array2[i] = 0;
		echo_array3[i] = 0;
	}
}

Int16 echo( Int16 latest_input, Int16 depth, Int16 buffer_length, Int16 opmode) {
	static signed int index = 0;
	signed long temp;
	signed long oldest_input1;
	signed long oldest_input2;
	signed long oldest_input3;
	
	/*calculates the buffer length */
	buffer_length = 6000 + buffer_length*23;
 
 	depth <<= 7;
 

	oldest_input1 =  ((long) echo_array1[index] * depth); /* scale oldest sample  */
	oldest_input2 =  ((long) echo_array2[index] * depth);
	oldest_input3 =  ((long) echo_array3[index] * depth);
 
	oldest_input1 >>= 15; /* remove fractional part */
	oldest_input2 >>= 15;
	oldest_input3 >>= 15;
 
	temp = (long) latest_input + oldest_input1 + oldest_input2 + oldest_input3; /* mix delayed sample with current sample */

	temp >>= 2;

 
	if ( temp > 32767) /* check if values are too big... */
	{
		temp = 32767;
	} 
	else if ( temp < -32767) /* ... or too small */
	{ 
		temp = -32767;
	}
 
 	echo_array1[index] = latest_input; /* put latest sample into the buffer */
	echo_array2[index] = oldest_input1;
	echo_array3[index] = oldest_input2;
 	
	if ( index < buffer_length - 1) { /* increment index if not at end...*/
		index++;
	}  
	else
	{
		index = 0;  /* ...else go back to start */
	}
   
	return( (signed int) temp);

}

