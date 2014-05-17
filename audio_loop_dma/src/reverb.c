#define N 4810

#include "ezdsp5535.h"

//#define DEPTH 0

signed int reverb_array[N]; /* Buffer f�r max 200 ms delay */


void reverb_array_clear(void) {
	int i;
 
	for ( i = 0 ; i < N ; i++) {
		reverb_array[i] = 0;
	}
}


Int16 reverb( Int16 latest_input,  Int16 buffer_length, Int16 depth, Int16 opmode) {
	static signed int index = 0; /* Retain value between calls */
	signed long temp;
	signed long oldest_input;
	
	buffer_length = 1000 + 15*buffer_length;
	depth <<= 7;
	
	if (depth > 32767) {
		depth = 32767;
	}
		
	oldest_input =  ((long) reverb_array[index] * depth); /* Skala �ldsta samplingen */
 
	oldest_input >>= 15; /*ta bort decimaler */
 
	temp = (long) latest_input + oldest_input; /* mixa f�rdr�jd sampel med aktuell sampel */

	temp >>= 1;
 
	if ( temp > 32767) { /* Kolla s� att inte v�rdena blir f�r stora... */
		temp = 32767;
	} 
	else if ( temp < -32767) { /* ...eller f�r sm� */
		temp = -32767;
	}
 
	reverb_array[index] = temp; /* l�gg in senaste utsampel (IIR, feedback) */
 
	if ( index < buffer_length - 1) { /* incrementera index om inte i slutet av buffer */
		index++;
	}  
	else {
		index = 0;  /* annars g� tillbaka till b�rjan */
	}
   
	return( (signed int) temp);

}
