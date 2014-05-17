#include "ezdsp5535.h"
 
#define N 24000 //12000

signed int echo_array[N]; /* Buffer f�r max 0.5s delay */

void echo_array_clear(void) {
	int i;
 
	for ( i = 0 ; i < N ; i++) {
		echo_array[i] = 0;
	}
}

Int16 echo( Int16 latest_input, Int16 depth, Int16 buffer_length, Int16 opmode) {
	static signed int index = 0;
	signed long temp;
	signed long oldest_input;
	
	buffer_length = 6000 + buffer_length*70;
 
 	depth <<= 7;
 

	oldest_input =  ((long) echo_array[index] * depth); /* skala �ldsta sampling */
 
	oldest_input >>= 15; /* ta bort decimaler */
 
	temp = (long) latest_input + oldest_input; /* mixa f�rdr�jd sampel med aktuell sampel */

	temp >>= 1;
 
	if ( temp > 32767) /* Kolla s� att inte v�rdena blir f�r stora... */
	{
		temp = 32767;
	} 
	else if ( temp < -32767) /* ... eller f�r sm� */
	{ 
		temp = -32767;
	}
	
	
 
	echo_array[index] = latest_input; /* l�gg in senaste insampel (FIR, feedforward) */
 
	//if ( index < N - 1)  /* incrementera index om inte i slutet av buffer */
	//{
	if ( index < buffer_length - 1) {
		index++;
	}  
	else
	{
		index = 0;  /* annars g� tillbaka till b�rjan */
	}
   
	return( (signed int) temp);

}

