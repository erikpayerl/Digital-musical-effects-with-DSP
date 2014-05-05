#include "tistdtypes.h"
#include "EQfilter.h"
#include "hwafft.h"

void EQCoeff(Uint8 *a, Int16 *H) {
	
	Int32 *complex_data, *bitrev_data, *scratch, *fft_data;
	Uint16 out_sel;
	Int16 x, i, dF;
	
	//EQ-band 
	Int16 A[7];

	/* EQ-band gains, 0-1 -> Uint8 0 - 255 */
	/* Map Uint8 to Int16 (Int32) */
	A[0] = (Int16)(a[0]) << 7;
	A[1] = (Int16)(a[1]) << 7;
	A[2] = (Int16)(a[2]) << 7;
	A[3] = (Int16)(a[3]) << 7;
	A[4] = (Int16)(a[4]) << 7;
	A[5] = (Int16)(a[5]) << 7;
	A[6] = (Int16)(a[6]) << 7;

	dF = 32768/FFT_LENGTH;
	
	for (i=0;i < (FFT_LENGTH/2) ;i++) {
		x = i*dF; 
		if (x<fc[0])
			H[i] = A[0];
		else if (x<fc[1])
			H[i] = A[1];
		else if (x<fc[2])
			H[i] = A[2];
		else if (x<fc[3])
			H[i] = A[3];
		else if (x<fc[4])
			H[i] = A[4];
		else if (x<fc[5])
			H[i] = A[5];
		else if (x<13763) // 0.42 normalized freq, approx 20000 Hz
			H[i] = A[6];
		else
			H[i] = 0;
			//H[i]=(Int16)(-13*(Int32)(x)+212160);
	}
	
	/* Phase = exp(-1i*pi*k)= 1, -1, 1 -1,...  , k = 0,1,2,... */
	for (i=1;i<(FFT_LENGTH/2);i+=2)    H[i]=-H[i];
	
	/* Linear phase -> H(FFT_LENGTH-k) = *H(k) */
	for (i=0;i<(FFT_LENGTH/2 -1);i++) 	H[FFT_LENGTH-1-i] = H[i+1];
	
	/* FFT_LENGTH = EVEN -> H[FFT_LENGTH/2] = 0, for linear phase */
	H[FFT_LENGTH/2] = 0;
	
	/* Initialize relevant pointers */
	bitrev_data  = bitreversed_buffer;
	scratch = scratch_buffer;
	complex_data = complex_buffer;
	
	/* Convert real Int16 to "pseudo"-complex Int16 (real, 0) */
	/* Int32 complex = Int16 real (MSBs) + Int16 imag (LSBs) */
	for (i = 0; i < FFT_LENGTH; i++) {
		*(complex_data + i) = ( (Int32) (*(H + i)) ) << 16;
	}

	/* Perform bit-reversing */
	hwafft_br(complex_data, bitrev_data, FFT_LENGTH);

	/* Perform iFFT */
	out_sel = hwafft_512pts(bitrev_data, scratch, IFFT_FLAG, SCALE_FLAG);

	/* Return appropriate Int16 pointer */
	if (out_sel == OUT_SEL_DATA) {
		fft_data = bitrev_data; // results stored in this Int16 vector 
	}else {
		fft_data = scratch; // results stored in this scratch vector 
	}

	/* Extract real part  */
	for (i = 0; i < FFT_LENGTH; i++) {
		*(H + i) = (Int16)((*(fft_data + i)) >> 16);
		//*(imagR + i) = (Int16)((*(fft_data + i)) & 0x0000FFFF);
	}
	
	/* Window */
	for (i = 0; i < FFT_LENGTH; i++ ) { 	H[i] = (Int16)(((Int32)(Int16)H[i] * (Int32)(Int16)blackman512[i]) >> 15);	}

}
