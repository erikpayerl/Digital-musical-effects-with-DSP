//////////////////////////////////////////////////////////////////////////////
// * File name:    fuzz.c
// * 
// * Function:     fuzz                                                                     
// * Description:  Applies a distortion-effect on input sample. 
// *                                                                                     
// * Usage:        Int16  = fuzz(    Int16 s,       		// input sample
// *                                 Int16 th, 				// sets the treshold, range (0-254)
// *                                 Int16 pG, 				// sets the pregain, range (0-254)
// *                                 Int16 opmode,			//  not used.
// *
// * Gustaf Johansson   2014-06-02                                                           
//////////////////////////////////////////////////////////////////////////////

#include "fuzz.h"

Int16 fuzz(Int16 s, Int16 th, Int16 pG, Int16 opmode) {
	
	Int32 temp;
	temp = (Int32)s*(pG+32); //gain is recalculated with regards to fix point
	temp = temp>>5;
	s = (Int16)temp;
	th=th <<5;				//threshold is recalculated with regards to fix point
	//lip at both ends
	if (s > th) { //set sample = th if sample is bigger than treshold
		s = th;
	} 

    if (s < -th) {//set sample = th if sample is smaller than negative treshold
        s = -th;   
    }

	if ( s > 32767 ) { // check if values are too big...
		s = 32767;
	} 
	else if ( s < -32767) { //... or too small
		s = - 32767;  
 	}
    return s;
}
