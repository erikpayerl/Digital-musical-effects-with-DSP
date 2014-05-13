#include "fuzz.h"
/*****************************************************************************/
/* fuzz(x,clip)                                                         */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* INPUTS:  sample s, clip treshold th, and pregain pG				*/
/* Lower threshold -> more distortion 										  */
/*                                                                           */
/* RETURNS: distorted sample					                             */
/*                                                                           */
/*****************************************************************************/

Int16 fuzz(Int16 s, Int16 th, Int16 pG, Int16 opmode) {
	
	Int32 temp;
	temp = (Int32)s*(pG+32);
	temp = temp>>5;
	s = (Int16)temp;
	th=th <<5;
	//lip at both ends
	if (s > th) {
		s = th;
	} 

    if (s < -th) {
        s = -th;   
    }
    
    //amplify!
    //x = amp*x;

	if ( s > 32767 ) {
		s = 32767;
	} 
	else if ( s < -32767) {
		s = - 32767;  
 	}
    return s;
}
