#ifndef _STEREO
#define _STEREO

Int16 stereo_to_mono(unsigned short left_channel, unsigned short right_channel);
void stereo_to_mono_buffer(Int16 *left_channel, Int16 *right_channel, Int16 *mono_out, Int16 nx);

#endif /*STEREO_H_*/
