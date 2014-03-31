#ifndef LOWPASSFIR_
#define LOWPASSFIR_

#endif /*LOWPASSFIR_*/

#define NH 64

//#pragma DATA_SECTION(h,".coeffs")
DATA h[NH] ={ /* b0 b1 b2 ... b(NH-1) */
-26,
-28,
-32,
-36,
-41,
-46,
-50,
-52,
-51,
-45,
-33,
-13,
16,
55,
106,
169,
244,
330,
428,
535,
651,
771,
895,
1019,
1140,
1255,
1360,
1453,
1531,
1592,
1634,
1655,
1655,
1634,
1592,
1531,
1453,
1360,
1255,
1140,
1019,
895,
771,
651,
535,
428,
330,
244,
169,
106,
55,
16,
-13,
-33,
-45,
-51,
-52,
-50,
-46,
-41,
-36,
-32,
-28,
-26,
};

//#pragma DATA_SECTION(dbL,".dbufferLeft")
DATA dbL[NH+2] ;

//#pragma DATA_SECTION(dbR,".dbufferRight")
DATA dbR[NH+2] ;
