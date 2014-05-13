//////////////////////////////////////////////////////////////////////////////
// * File name:    EQfilter.c
// * 
// * Function:     EQcoeff                                                                        
// * Description:  Calculate filter coefficiants for 8-band graphic equalizer.
// *               Method: Frequency sampling. FFT with hwafft. FFT_LENGTH = 512.
// *                                                                          
// * Usage:        void  = EQfilter( Uint8 *a)   // pointer to band amplitudes
// *                                 
// * Benchmarks:   Cycles ca 80000 for FFT_LENGTH 512              
// *
// *
// * Erik Payerl   2014-05-12                                                           
//////////////////////////////////////////////////////////////////////////////
#include "ezdsp5535.h"
#include "tms320.h"
#include "hwafft.h"
#include "EQ.h"

// Arrays for coeff calculation
Int32 *complex_data, *bitrev_data, *scratch, *fft_data;
Uint16 out_sel;

void EQcoeff( Uint8 *a, DATA *H ) {	
	/* Map Uint8 to DATA (Int32) */
	A[0] = (DATA)(a[0]) << 7;
	A[1] = (DATA)(a[1]) << 7;
	A[2] = (DATA)(a[2]) << 7;
	A[3] = (DATA)(a[3]) << 7;
	A[4] = (DATA)(a[4]) << 7;
	A[5] = (DATA)(a[5]) << 7;
	A[6] = (DATA)(a[6]) << 7;
	A[7] = (DATA)(a[7]) << 7;
	
	/* Setup frequency spacing */
	dF = 32768/FFT_LENGTH;
		
	/* Magnitud for filterbands */	
	for (ii=0;ii < (FFT_LENGTH/2) ;ii++) {
		x = ii*dF; 
		if (x<fc[0])
			H[ii] = A[0];
		else if (x<fc[1])
			H[ii] = A[1];
		else if (x<fc[2])
			H[ii] = A[2];
		else if (x<fc[3])
			H[ii] = A[3];
		else if (x<fc[4])
			H[ii] = A[4];
		else if (x<fc[5])
			H[ii] = A[5];
		else if (x<fc[6])
			H[ii] = A[6];
		/* 12544 = 0.3828 normalized freq = 18375 Hz when fs = 48000 Hz,                      *
		 * if H(x)>0 when x>=12544 -> the frequency respons H(z) of the filter gets inverted! *
		 * I do not know why...                                                               */
		else if (x<11360)
			H[ii] = A[7];
		else
			H[ii] = 0;
	}
	
	/* Phase = exp(-1i*pi*k)= 1, -1, 1 -1,...  , k = 0,1,2,... */
	for (ii=1;ii<(FFT_LENGTH/2);ii+=2)    H[ii]=-H[ii];
	
	/* Linear phase -> H(FFT_LENGTH-k) = *H(k) */
	for (ii=0;ii<(FFT_LENGTH/2 -1);ii++) 	H[FFT_LENGTH-1-ii] = H[ii+1];
	
	/* FFT_LENGTH = EVEN -> H[FFT_LENGTH/2] = 0, for linear phase */
	H[FFT_LENGTH/2] = 0;   
	
	/* Initialize relevant pointers */
	bitrev_data  = bitreversed_buffer;
	scratch = scratch_buffer;
	complex_data = complex_buffer;
	
	/* Convert real data to "pseudo"-complex data (real, 0) */
	/* Int32 complex = Int16 real (MSBs) + Int16 imag (LSBs) */
	for (ii = 0; ii < FFT_LENGTH; ii++) {
		*(complex_data + ii) = ( (Int32) (*(H + ii)) ) << 16;
	}	

	/* Perform bit-reversing */
	hwafft_br(complex_data, bitrev_data, FFT_LENGTH);

	/* Perform iFFT */
	if (FFT_LENGTH==512) {
		out_sel = hwafft_512pts(bitrev_data, scratch, IFFT_FLAG, SCALE_FLAG);
	} else if (FFT_LENGTH==256) {
		out_sel = hwafft_256pts(bitrev_data, scratch, IFFT_FLAG, SCALE_FLAG);
	} else if (FFT_LENGTH==128) {
		out_sel = hwafft_128pts(bitrev_data, scratch, IFFT_FLAG, SCALE_FLAG);
	}

	/* Return appropriate data pointer */
	if (out_sel == OUT_SEL_DATA) {
		fft_data = bitrev_data; // results stored in this data vector 
	}else {
		fft_data = scratch; // results stored in this scratch vector 
	}

	/* Extract real part  */
	for (ii = 0; ii < FFT_LENGTH; ii++) {
		*(H + ii) = (Int16)(*(fft_data + ii) >> 16); 
		//*(imagR + i) = (Int16)((*(fft_data + i)) & 0x0000FFFF);
	}

	/* Window */
	for (ii = 0; ii < FFT_LENGTH; ii++ ) { 	H[ii] = (DATA)(((LDATA)(DATA)H[ii] * (LDATA)(DATA)turkey512[ii]) >> 15);	}
	
	/* Print filter coeff. */
	//for (ii = 0; ii < FFT_LENGTH; ii++ ) { 	printf("%d\n",*(H + ii)); }
}
