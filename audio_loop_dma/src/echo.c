#include "ezdsp5535.h"

#define N 24000

Int16 echo_array1[N]; /* Buffer för max 0.5s delay */
Int16 echo_array2[N];
Int16 echo_array3[N];

static int echoindex = 0;
Int32 temp;
Int32 oldest_input1;
Int32 oldest_input2;
Int32 oldest_input3;

int j;

void echo_array_clear(void) {
	
	for ( j = 0 ; j < N ; j++) {
		echo_array1[j] = 0;
		echo_array2[j] = 0;
		echo_array3[j] = 0;
	}
}


Int16 echo(Int16 latest_input, Int16 depth, Int16 buffer_length, Int16 opmode) {
	
 	depth<<=7;				// depth skickas som en int med maximalt värde 254
	buffer_length=5000+buffer_length*74; //
	
	depth=30000;
	buffer_length=23000;
	oldest_input1 =  ((Int32) echo_array1[echoindex] * depth); /* skala äldsta sampling */
 	oldest_input2 =  ((Int32) echo_array2[echoindex] * depth);
 	oldest_input3 =  ((Int32) echo_array3[echoindex] * depth);
 	
	oldest_input1 >>= 15; /* ta bort decimaler */
	oldest_input2 >>= 15;
	oldest_input3 >>= 15;
 
	temp = (Int32) latest_input; //+ oldest_input1 + oldest_input2 + oldest_input3; /* mixa fördröjd sampel med aktuell sampel */

	temp >>= 2;
 
	//if ( temp > 32767) /* Kolla så att inte värdena blir för stora... */
/*	{
		temp = 32767;
	} 
	else if ( temp < -32767) // ... eller för små 
	{ 
		temp = -32767;
	}*/
	
 
	echo_array1[echoindex] = latest_input; /* lägg in senaste insampel (FIR, feedforward) */
	echo_array2[echoindex] = oldest_input1;
	echo_array3[echoindex] = oldest_input2;
 
	//if ( index < N - 1)  /* incrementera index om inte i slutet av buffer */
	//{
	if ( echoindex < buffer_length - 1) {
		echoindex++;
	}  
	else
	{
		echoindex = 0;  /* annars gå tillbaka till början */
	}
   
	return (Int16) temp;

}
