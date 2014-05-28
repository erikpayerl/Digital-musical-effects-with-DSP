//////////////////////////////////////////////////////////////////////////////
// * File name:    EQfilter.h
// *                                                                         
// *               
// * Erik Payerl 2014-05-28                                                          
//////////////////////////////////////////////////////////////////////////////

#ifndef EQFILTER_H_
#define EQFILTER_H_

void EQCoeff( Uint8 *a );
Int16 EQ(Int16 s, Int16 not_used1, Int16 not_used2, Int16 not_used3);
void EQ_clear();

//EQ-band 
Uint8 a[8];

#endif /*EQFILTER_H_*/
