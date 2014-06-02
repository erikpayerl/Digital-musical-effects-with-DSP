// Den här funktionen tar in en sample, depth och LFOspeed. 
// depth är en skalfaktor som avgör hur djup amplitudmodulationen blir
// depth skall ligga mellan 0 och 32 som inparameter och motsvarar ett decimaltal mellan 0 och 1
// LFOspeed avgör hur snabb modulationen blir, högre LFOspeed-> lägre frekvens (OBS)
// LFOspeed=20 vid 48kHz samplingsfrekvens ger en LFO med frekvens ung. 4.7Hz

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
	LFOspeed=260-LFOspeed; // Satte 260 för att det inte skall kunna bli för hög frekvens.
	modulator=LFO(LFOspeed);
	modsignal=(8192 - depth*256) + depth*modulator;
	output32=(Int32) sample*modsignal;
	
	output= output32 >> 13; // stod 14 här innan jag ändrade modsignal
	
	return output;		
}


