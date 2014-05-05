#include "dsplib.h"
#include "data_types.h"
#include "EQ.h"
#include "hwafft.h"
#include <stdio.h>


/* --- Special buffers required for HWAFFT ---*/
#pragma DATA_SECTION(complex_buffer, "cmplxBuf");
//Static Allocation to Section: "cmplxBuf : > DARAM" in Linker CMD File
Int32 complex_buffer[FFT_LENGTH];

#pragma DATA_SECTION(bitreversed_buffer, "data_br_buf");
#pragma DATA_ALIGN(bitreversed_buffer, 2*FFT_LENGTH);
Int32 bitreversed_buffer[FFT_LENGTH];

#pragma DATA_SECTION(scratch_buffer, "scratch_buf");
//Static Allocation to Section: "scratch_buf : > DARAM" in Linker CMD File
Int32 scratch_buffer[FFT_LENGTH];
/* -------------------------------------------*/

void EQfilter( DATA *A, DATA *H )
{
	
	/*DATA H[128];*/ 
	Int32 *complex_data, *bitrev_data, *scratch, *fft_data;
	Uint16 out_sel;
	 
	Int16 x;
	Int16 i;

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
		else
			H[i] = A[6];
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
	
	/* Convert real data to "pseudo"-complex data (real, 0) */
	/* Int32 complex = Int16 real (MSBs) + Int16 imag (LSBs) */
	for (i = 0; i < FFT_LENGTH; i++) {
		*(complex_data + i) = ( (Int32) (*(H + i)) ) << 16;
	}

	/* Perform bit-reversing */
	hwafft_br(complex_data, bitrev_data, FFT_LENGTH);

	/* Perform iFFT */
	out_sel = hwafft_128pts(bitrev_data, scratch, IFFT_FLAG, SCALE_FLAG);

	/* Return appropriate data pointer */
	if (out_sel == OUT_SEL_DATA) {
		fft_data = bitrev_data; // results stored in this data vector 
	}else {
		fft_data = scratch; // results stored in this scratch vector 
	}

	/* Extract real part  */
	for (i = 0; i < FFT_LENGTH; i++) {
		*(H + i) = (Int16)((*(fft_data + i)) >> 16);
		//*(imagR + i) = (Int16)((*(fft_data + i)) & 0x0000FFFF);
	}
	
	printf("EQfilter() Done! \n");
}
