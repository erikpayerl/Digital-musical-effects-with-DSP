#ifndef EQFILTER_H_
#define EQFILTER_H_

#define FFT_LENGTH 512

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

DATA fc[6] ={
/*137,
273,
546,
1092,
2185,
4369*/
102,    
205,    
410,    
819,   
1638,   
3277,
 };

/* Filter buffers */
#pragma DATA_SECTION(dbL,"dbufferLeft")
DATA dbL[FFT_LENGTH+2] ;

#pragma DATA_SECTION(dbR,"dbufferRight")
DATA dbR[FFT_LENGTH+2] ;

/* Hamming Window length 512 */
DATA hamming512[512] = { 2623, 2626, 2632, 2640, 2650, 2662, 2677, 2694, 2713, 2735, 2759, 2785, 2813, 2843, 2876, 2911, 2948, 2988, 3029, 3073, 3119, 3167, 3218, 3270, 3325, 3382, 3441, 3503, 3566, 3631, 3699, 3769, 3841, 3915, 3991, 4069, 4149, 4231, 4315, 4401, 4489, 4580, 4672, 4766, 4862, 4960, 5060, 5162, 5265, 5371, 5478, 5588, 5699, 5812, 5926, 6043, 6161, 6281, 6403, 6526, 6651, 6778, 6906, 7036, 7168, 7301, 7436, 7572, 7710, 7849, 7990, 8132, 8276, 8421, 8568, 8716, 8865, 9015, 9167, 9320, 9475, 9631, 9787, 9946, 10105, 10265, 10427, 10589, 10753, 10918, 11083, 11250, 11418, 11586, 11756, 11926, 12098, 12270, 12443, 12617, 12791, 12967, 13142, 13319, 13497, 13674, 13853, 14032, 14212, 14392, 14573, 14754, 14936, 15118, 15300, 15483, 15666, 15850, 16033, 16217, 16401, 16586, 16770, 16955, 17140, 17325, 17510, 17695, 17880, 18065, 18250, 18434, 18619, 18804, 18988, 19172, 19356, 19540, 19723, 19906, 20089, 20272, 20454, 20635, 20817, 20997, 21178, 21357, 21536, 21715, 21893, 22070, 22247, 22423, 22598, 22773, 22947, 23120, 23292, 23463, 23633, 23803, 23972, 24139, 24306, 24472, 24637, 24800, 24963, 25124, 25285, 25444, 25602, 25759, 25915, 26069, 26222, 26374, 26525, 26674, 26822, 26968, 27113, 27257, 27399, 27540, 27679, 27817, 27954, 28088, 28222, 28353, 28483, 28611, 28738, 28863, 28987, 29108, 29228, 29347, 29463, 29578, 29691, 29802, 29911, 30018, 30124, 30228, 30330, 30429, 30527, 30624, 30718, 30810, 30900, 30988, 31074, 31159, 31241, 31321, 31399, 31475, 31549, 31621, 31690, 31758, 31823, 31887, 31948, 32007, 32064, 32119, 32172, 32222, 32270, 32316, 32360, 32402, 32441, 32478, 32513, 32546, 32577, 32605, 32631, 32655, 32676, 32695, 32712, 32727, 32740, 32750, 32758, 32763, 32767, 32767, 32767, 32763, 32758, 32750, 32740, 32727, 32712, 32695, 32676, 32655, 32631, 32605, 32577, 32546, 32513, 32478, 32441, 32402, 32360, 32316, 32270, 32222, 32172, 32119, 32064, 32007, 31948, 31887, 31823, 31758, 31690, 31621, 31549, 31475, 31399, 31321, 31241, 31159, 31074, 30988, 30900, 30810, 30718, 30624, 30527, 30429, 30330, 30228, 30124, 30018, 29911, 29802, 29691, 29578, 29463, 29347, 29228, 29108, 28987, 28863, 28738, 28611, 28483, 28353, 28222, 28088, 27954, 27817, 27679, 27540, 27399, 27257, 27113, 26968, 26822, 26674, 26525, 26374, 26222, 26069, 25915, 25759, 25602, 25444, 25285, 25124, 24963, 24800, 24637, 24472, 24306, 24139, 23972, 23803, 23633, 23463, 23292, 23120, 22947, 22773, 22598, 22423, 22247, 22070, 21893, 21715, 21536, 21357, 21178, 20997, 20817, 20635, 20454, 20272, 20089, 19906, 19723, 19540, 19356, 19172, 18988, 18804, 18619, 18434, 18250, 18065, 17880, 17695, 17510, 17325, 17140, 16955, 16770, 16586, 16401, 16217, 16033, 15850, 15666, 15483, 15300, 15118, 14936, 14754, 14573, 14392, 14212, 14032, 13853, 13674, 13497, 13319, 13142, 12967, 12791, 12617, 12443, 12270, 12098, 11926, 11756, 11586, 11418, 11250, 11083, 10918, 10753, 10589, 10427, 10265, 10105, 9946, 9787, 9631, 9475, 9320, 9167, 9015, 8865, 8716, 8568, 8421, 8276, 8132, 7990, 7849, 7710, 7572, 7436, 7301, 7168, 7036, 6906, 6778, 6651, 6526, 6403, 6281, 6161, 6043, 5926, 5812, 5699, 5588, 5478, 5371, 5265, 5162, 5060, 4960, 4862, 4766, 4672, 4580, 4489, 4401, 4315, 4231, 4149, 4069, 3991, 3915, 3841, 3769, 3699, 3631, 3566, 3503, 3441, 3382, 3325, 3270, 3218, 3167, 3119, 3073, 3029, 2988, 2948, 2911, 2876, 2843, 2813, 2785, 2759, 2735, 2713, 2694, 2677, 2662, 2650, 2640, 2632, 2626, 2623, 2621 };

/* Blackman Windoe length 512 */
DATA blackman512[512] = {0, 2, 4, 7, 11, 16, 22, 29, 36, 45, 54, 64, 76, 88, 101, 115, 130, 146, 163, 181, 200, 221, 242, 264, 287, 311, 336, 363, 390, 419, 448, 479, 511, 545, 579, 615, 651, 690, 729, 770, 811, 855, 899, 945, 993, 1041, 1091, 1143, 1196, 1250, 1306, 1364, 1423, 1483, 1545, 1609, 1674, 1741, 1810, 1880, 1952, 2025, 2100, 2177, 2256, 2336, 2419, 2503, 2589, 2676, 2766, 2857, 2951, 3046, 3143, 3242, 3343, 3445, 3550, 3657, 3766, 3876, 3989, 4104, 4220, 4339, 4460, 4583, 4708, 4835, 4963, 5094, 5228, 5363, 5500, 5639, 5780, 5924, 6069, 6217, 6366, 6518, 6671, 6827, 6985, 7144, 7306, 7470, 7635, 7803, 7973, 8144, 8318, 8493, 8671, 8850, 9031, 9214, 9399, 9586, 9774, 9964, 10156, 10350, 10545, 10742, 10941, 11141, 11343, 11546, 11751, 11958, 12166, 12375, 12585, 12797, 13011, 13225, 13441, 13658, 13876, 14095, 14316, 14537, 14759, 14983, 15207, 15432, 15657, 15884, 16111, 16339, 16567, 16796, 17026, 17256, 17486, 17717, 17948, 18179, 18410, 18642, 18873, 19105, 19336, 19567, 19799, 20030, 20260, 20491, 20720, 20950, 21179, 21407, 21635, 21862, 22088, 22313, 22538, 22762, 22984, 23206, 23426, 23645, 23863, 24079, 24295, 24508, 24721, 24931, 25140, 25348, 25553, 25757, 25959, 26159, 26357, 26553, 26747, 26939, 27129, 27316, 27501, 27683, 27863, 28041, 28216, 28389, 28558, 28725, 28890, 29051, 29210, 29366, 29519, 29668, 29815, 29959, 30099, 30237, 30371, 30501, 30629, 30753, 30874, 30991, 31105, 31215, 31322, 31425, 31525, 31621, 31713, 31802, 31886, 31967, 32045, 32118, 32188, 32254, 32316, 32374, 32428, 32478, 32524, 32566, 32604, 32639, 32669, 32695, 32717, 32736, 32750, 32760, 32766, 32767, 32766, 32760, 32750, 32736, 32717, 32695, 32669, 32639, 32604, 32566, 32524, 32478, 32428, 32374, 32316, 32254, 32188, 32118, 32045, 31967, 31886, 31802, 31713, 31621, 31525, 31425, 31322, 31215, 31105, 30991, 30874, 30753, 30629, 30501, 30371, 30237, 30099, 29959, 29815, 29668, 29519, 29366, 29210, 29051, 28890, 28725, 28558, 28389, 28216, 28041, 27863, 27683, 27501, 27316, 27129, 26939, 26747, 26553, 26357, 26159, 25959, 25757, 25553, 25348, 25140, 24931, 24721, 24508, 24295, 24079, 23863, 23645, 23426, 23206, 22984, 22762, 22538, 22313, 22088, 21862, 21635, 21407, 21179, 20950, 20720, 20491, 20260, 20030, 19799, 19567, 19336, 19105, 18873, 18642, 18410, 18179, 17948, 17717, 17486, 17256, 17026, 16796, 16567, 16339, 16111, 15884, 15657, 15432, 15207, 14983, 14759, 14537, 14316, 14095, 13876, 13658, 13441, 13225, 13011, 12797, 12585, 12375, 12166, 11958, 11751, 11546, 11343, 11141, 10941, 10742, 10545, 10350, 10156, 9964, 9774, 9586, 9399, 9214, 9031, 8850, 8671, 8493, 8318, 8144, 7973, 7803, 7635, 7470, 7306, 7144, 6985, 6827, 6671, 6518, 6366, 6217, 6069, 5924, 5780, 5639, 5500, 5363, 5228, 5094, 4963, 4835, 4708, 4583, 4460, 4339, 4220, 4104, 3989, 3876, 3766, 3657, 3550, 3445, 3343, 3242, 3143, 3046, 2951, 2857, 2766, 2676, 2589, 2503, 2419, 2336, 2256, 2177, 2100, 2025, 1952, 1880, 1810, 1741, 1674, 1609, 1545, 1483, 1423, 1364, 1306, 1250, 1196, 1143, 1091, 1041, 993, 945, 899, 855, 811, 770, 729, 690, 651, 615, 579, 545, 511, 479, 448, 419, 390, 363, 336, 311, 287, 264, 242, 221, 200, 181, 163, 146, 130, 115, 101, 88, 76, 64, 54, 45, 36, 29, 22, 16, 11, 7, 4, 2, 0, 0};
/* EQ-coefficients */ 
#pragma DATA_SECTION(coeff_buffer,"coeffs")
DATA coeff_buffer[FFT_LENGTH] ;

/* Highpass*/
//DATA H[FFT_LENGTH] = {3,-12,-7,11,12,-9,-17,5,22,2,-26,-11,27,23,-25,-37,18,51,-5,-63,-16,70,43,-68,-74,55,106,-29,-133,-11,151,64,-154,-126,136,191,-92,-252,22,298,75,-318,-193,303,326,-242,-461,126,584,50,-677,-292,717,606,-677,-1004,515,1523,-146,-2284,-691,3839,3627,-15854,15854,-3627,-3839,691,2284,146,-1523,-515,1004,677,-606,-717,292,677,-50,-584,-126,461,242,-326,-303,193,318,-75,-298,-22,252,92,-191,-136,126,154,-64,-151,11,133,29,-106,-55,74,68,-43,-70,16,63,5,-51,-18,37,25,-23,-27,11,26,-2,-22,-5,17,9,-12,-11,7,12,-3 };

/* Lowpass */
//DATA H[FFT_LENGTH] = {19,20,21,22,24,26,29,31,35,38,42,47,52,57,63,70,77,84,92,100,109,118,128,138,149,159,171,182,194,206,219,231,244,257,270,283,297,310,323,336,349,362,374,387,399,411,422,433,443,454,463,472,481,489,496,502,508,514,518,522,525,527,529,530,530,529,527,525,522,518,514,508,502,496,489,481,472,463,454,443,433,422,411,399,387,374,362,349,336,323,310,297,283,270,257,244,231,219,206,194,182,171,159,149,138,128,118,109,100,92,84,77,70,63,57,52,47,42,38,35,31,29,26,24,22,21,20,19};

#endif /*EQFILTER_H_*/
