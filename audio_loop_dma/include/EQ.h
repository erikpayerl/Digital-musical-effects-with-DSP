#ifndef EQ_H_
#define EQ_H_

#ifndef FFT_LENGTH
#define FFT_LENGTH 512
#endif 

void EQCoeff(Uint8 *a, Int16 *H);

/* EQ-coefficients */ 
#pragma DATA_SECTION(coeff_buffer,"coeffs")
Int16 coeff_buffer[FFT_LENGTH] ;

/* Filter buffers */
#pragma DATA_SECTION(dbL,"dbufferLeft")
Int16 dbL[FFT_LENGTH+2] ;

#pragma DATA_SECTION(dbR,"dbufferRight")
Int16 dbR[FFT_LENGTH+2] ;

Uint8 a[7];

#endif /*EQ_H_*/



