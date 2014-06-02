#ifndef SVF_H_
#define SVF_H_
	Int16 svf(Int16 s, Int16 findex, Int16 Q1, Int16 opmode);
	
	Int16 D1 = 0;
	Int16 D2 = 0;
	
	unsigned short F1[254]; // 2^2
	Int16 Q1; // 2^2 Q1 ligger eg. mellan 0 och 2, men skalas med 2^14, sätts därmed mellan 0 och 32768, samma för F1	
	
	Int32 hVar1;
	Int32 hVar2;
	Int32 hVar3;
	Int32 hfc;
	Int16 pi=25736; //pi*2^13
	Int32 f1;
	Int16 outputs[4]; // outputs[0] = L, outputs[1] = H, outputs[2] = B, outputs[3] = N
	extern Int16 D1, D2;
#endif /*SVF_H_*/
