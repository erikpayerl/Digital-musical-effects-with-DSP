//////////////////////////////////////////////////////////////////////////////
// * File name:    tremolo.c
// * 
// * Function:     tremolo                                                                        
// * Description:  The input sample is scaled according to a LFO and then output, this generates a tremolo effect. 
// *               .
// *                                                                                     
// * Usage:        Int16  = flanger( Int16 sample,         // input sample
// *                                 Int16 LFOspeed, // sets the speed for LFO, range(0-254)
// *                                 Int16 depth, //    decides the maximum scaling, range (0-254)
// *                                 Int16 opmode,)//  not used.
// *
// * Erik Sandgren   2014-06-02                                                           
//////////////////////////////////////////////////////////////////////////////

#include "tistdtypes.h"
#include "LFO.h"
#include "math.h"
	
Int16 output;
Int32 output32;
Int16 modulator;
Int16 modsignal;


Int16 tremolo(Int16 sample, Int16 LFOspeed, Int16 depth, Int16 opmode)
{	
	depth = depth>>3;
	LFOspeed=260-LFOspeed; /*Modifies the parameter to fit the function better */
	modulator=LFO(LFOspeed); /*Retrieving value of LFO */
	/* Scaling */
	modsignal=(8192 - depth*256) + depth*modulator; 
	output32=(Int32) sample*modsignal;
	output= output32 >> 13; 
	
	return output;		
}


