//////////////////////////////////////////////////////////////////////////////
// * File name:    EQfilter.c
// * 
// * Function:     EQfilter();                                                                        
// * Description:  Calculate filter coefficiants for 8-band graphic equalizer
// *               using hwafft. FFT_LENGTH = 512.
// *                                                                          
// * Usage:        void  = EQfilter( Uint8 *a,   // pointer to band amplitudes
// *                                 DATA  *H )  // return coefficient vector
// *
// * Benchmarks:  Cycles ca 80000 for FFT_LENGTH 512
// *               
// * Erik Payerl 2014-05-07                                                           
//////////////////////////////////////////////////////////////////////////////
#include "ezdsp5535.h"
#include "tms320.h"
#include "hwafft.h"
#include "EQ.h"

Int32 *complex_data, *bitrev_data, *scratch, *fft_data;
Uint16 out_sel;

void EQfilter( Uint8 *a, DATA *H )
{	
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
		else if (x<fc[6])
			H[i] = A[6];
		/* 12544 = 0.3828 normalized freq = 18375 Hz when fs = 48000 Hz,                      *
		 * if H(x)>0 when x>=12544 -> the frequency respons H(z) of the filter gets inverted! *
		 * I do not know why...                                                               */
		else if (x<12544)
			H[i] = A[7];
		else
			H[i] = 0;
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
	/*** OBS! Filtercoefficient H scaled x4 ***/
	for (i = 0; i < FFT_LENGTH; i++) {
		*(H + i) = (Int16)(*(fft_data + i) >> 14); // (no scale: >> 16)
		//*(imagR + i) = (Int16)((*(fft_data + i)) & 0x0000FFFF);
	}

	/* Window */
	for (i = 0; i < FFT_LENGTH; i++ ) { 	H[i] = (DATA)(((LDATA)(DATA)H[i] * (LDATA)(DATA)turkey512[i]) >> 15);	}
	 
}
