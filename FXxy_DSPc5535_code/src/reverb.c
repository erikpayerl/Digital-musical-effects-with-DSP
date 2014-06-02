//////////////////////////////////////////////////////////////////////////////
// * File name:    reverb.c
// * 
// * Function:     reverb_array_clear, reverb                                                                       
// * Description:  Applies a reverb-effect on input sample. 
// *                                                                                     
// * Usage:        Int16  = reverb(  Int16 latest_input,         // input sample
// *                                 Int16 buffer_length, 		// sets the length of the buffer range (0-254)
// *                                 Int16 depth, 				// decides the maximum delay, range (0-254)
// *                                 Int16 opmode,				//  not used.
// *
// * Gustaf Johansson   2014-06-02                                                           
//////////////////////////////////////////////////////////////////////////////

#define N 2400

#include "ezdsp5535.h"


signed int reverb_array1[N]; /* Buffer for maximum 100 ms delay at 48kHz sampling freq */
signed int reverb_array2[N];
signed int reverb_array3[N];
signed int reverb_array4[N];

/* This function clears the reverb buffers */
void reverb_array_clear(void) {
	int i;
 
	for ( i = 0 ; i < N ; i++) {
		reverb_array1[i] = 0;
		reverb_array2[i] = 0;
		reverb_array3[i] = 0;
		reverb_array4[i] = 0;
	}
}


Int16 reverb( Int16 latest_input,  Int16 buffer_length, Int16 depth, Int16 opmode) {
	static signed int index1 = 0;
	static signed int index2 = 0;
	static signed int index3 = 0;
	static signed int index4 = 0;
	signed long temp1;
	signed long temp2;
	signed long temp3;
	signed long temp4;
	signed long oldest_input1;
	signed long oldest_input2;
	signed long oldest_input3;
	signed long oldest_input4;
	signed long output;
	int buffer_length2;
	int buffer_length3;
	int buffer_length4;
	
	/* calculates the different maximum index for the comb filters */
	buffer_length = 500 + 7*buffer_length;
	buffer_length2 = buffer_length - 125;
	buffer_length3 = buffer_length - 250;
	buffer_length4 = buffer_length - 400;
	
	depth <<= 7;
	
	if (depth > 32767) {
		depth = 32767;
	}
		
	oldest_input1 = ((long) reverb_array1[index1] * depth); /* scale oldest sample */
 	oldest_input2 = ((long) reverb_array2[index2] * depth);
 	oldest_input3 = ((long) reverb_array3[index3] * depth);
 	oldest_input4 = ((long) reverb_array4[index4] * depth);
 	
	oldest_input1 >>= 15; /*remove fractional part */
	oldest_input2 >>= 15;
	oldest_input3 >>= 15;
	oldest_input4 >>= 15;
 	
 	
	temp1 = (long) latest_input + oldest_input1; /* mix delayed sample with current sample */
	temp2 = (long) latest_input + oldest_input2;
	temp3 = (long) latest_input + oldest_input3;
	temp4 = (long) latest_input + oldest_input4;

	temp1 >>= 1;
	temp2 >>= 1;
	temp3 >>= 1;
	temp4 >>= 1;

 
	reverb_array1[index1] = temp1; /* insert current sample into buffer */
 	reverb_array2[index2] = temp2;
 	reverb_array3[index3] = temp3;
 	reverb_array4[index4] = temp4;
 	
 	output = oldest_input1 + oldest_input2 +  oldest_input3 + oldest_input4; //mix the outputs from comb filters
 	
 	output = output + latest_input;
 	output >>= 1;
 	
	if ( index1 < buffer_length - 1) { /* increment index if not at end */
		index1++;
	}  
	else {
		index1 = 0;  /* else go back to start */
	}
	if ( index2 < buffer_length2 - 1) { 
		index2++;
	}  
	else {
		index2 = 0;  
	}
	if ( index3 < buffer_length3 - 1) { 
		index3++;
	}  
	else {
		index3 = 0;  
	}
	if ( index4 < buffer_length4 - 1) { 
		index4++;
	}  
	else {
		index4 = 0;  
	}
   
	return( (signed int) output);

}
