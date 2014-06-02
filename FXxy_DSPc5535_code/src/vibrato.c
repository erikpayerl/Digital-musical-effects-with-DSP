//////////////////////////////////////////////////////////////////////////////
// * File name:    vibrato.c
// * 
// * Function:     vibrato                                                                        
// * Description:  Every input sample is stored in a buffer, the output sample is the input signal delayed by a periodically varying delay. 
// *               .
// *                                                                                     
// * Usage:        Int16  = vibrato( Int16 sample,         // input sample
// *                                 Int16 LFOspeed, // sets the speed for LFO, range(0-254)
// *                                 Int16 depth, //    decides the maximum delay, range (0-254)
// *                                 Int16 opmode,)//  not used.
// *
// * Erik Sandgren, Gustaf Johansson   2014-06-02                                                           
//////////////////////////////////////////////////////////////////////////////

#include "tistdtypes.h"
#include "LFO.h"
#include "math.h"

/* Definitions for the circular buffer*/	
static Int16 DELAY_BUFFER_SIZE=512;
static Int16 buffer[512];
static Int16 vibindex=0;
static Int16 delay;
static Int16 LFOdelay;


static Int16 currentSample;
static Int16 previousSample;
static Int16 frac;
static Int32 output;

Int16 vibrato(Int16 sample,Int16 LFOspeed, Int16 depth, Int16 opmode)
{	
	
/* The in parameters are recalculated with regards to fix point and the actual implementation */	
depth = depth>>3;
LFOspeed=260-LFOspeed;
LFOdelay=LFO(LFOspeed)+256;  // The function LFO is called to calculate the current delay
LFOdelay*=depth;
frac= LFOdelay & 31; // frac is shifted down 5 times
LFOdelay>>=5; 		

/* Find sample delayed the number of samples the LFO gives */		
		delay = DELAY_BUFFER_SIZE-LFOdelay;

		delay = (vibindex+delay)&(DELAY_BUFFER_SIZE-1);

		currentSample = buffer[delay];
		
/* Find the sample delayed by one more sample than the above */
		delay = DELAY_BUFFER_SIZE-LFOdelay-1;

		delay = (vibindex+delay)&(DELAY_BUFFER_SIZE-1);

		previousSample = buffer[delay];

/* Calculate the output with linear interpolation of the two samples */

		output=(Int32) frac*previousSample + (Int32) (32-frac)*currentSample;
		output= output >> 5;
		
/* The latest sample is written to the buffer */
		buffer[vibindex]=sample;
		vibindex=(vibindex+1) & (DELAY_BUFFER_SIZE-1);
		
			
	return (Int16) output;	

}
