#ifndef _FUZZ
#define _FUZZ
#include "ezdsp5535.h"
Int16 fuzz(Int16 s, Int16 th, Int16 pG, Int16 opmode);

Int16 pGain = 12228; // 1.5 * 2^13
Int16 thresh = 1000;

#endif /*FUZZ_H_*/
