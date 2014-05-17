#ifndef REVERB_H
#define REVERB_H
 
 void reverb_array_clear(void);              
 
 Int16 reverb( Int16 latest_input, Int16 buffer_length, Int16 depth, Int16 opmode);
 
#endif
