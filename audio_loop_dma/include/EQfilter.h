//////////////////////////////////////////////////////////////////////////////
// * File name:    EQfilter.h
// *                                                                         
// * Description: Declare filter buffers and filter coefficient buffer
// *               
// * Erik Payerl 2014-05-13                                                          
//////////////////////////////////////////////////////////////////////////////

#ifndef EQFILTER_H_
#define EQFILTER_H_

#define FFT_LENGTH 512

void EQcoeff( Uint8 *a, DATA *H );

//EQ-band 
Uint8 a[8];

/* Filter buffers */
#pragma DATA_SECTION(dbL,"dbufferLeft")
DATA dbL[FFT_LENGTH+2] ;

#pragma DATA_SECTION(dbR,"dbufferRight")
DATA dbR[FFT_LENGTH+2] ;

/* EQ-coefficients */ 
#pragma DATA_SECTION(coeff_buffer,"coeffs")
DATA coeff_buffer[FFT_LENGTH] ;

#endif /*EQFILTER_H_*/
