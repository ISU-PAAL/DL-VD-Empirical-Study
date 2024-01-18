// commit message FFmpeg@2da0d70d5e (target=1, prob=0.9940387, correct=True): cosmetics attack, part IV: Remove all tabs and prettyprint/reindent the code.
/*0  */ static inline void RENAME(rgb32ToY)(uint8_t *dst, uint8_t *src, int width)   // (1) 0.1685
/*2  */ {                                                                            // (9) 0.005435
/*4  */ 	int i;                                                                      // (6) 0.02174
/*6  */ 	for(i=0; i<width; i++)                                                      // (5) 0.07065
/*8  */ 	{                                                                           // (7) 0.01087
/*10 */ 		int r=  ((uint32_t*)src)[i]&0xFF;                                          // (4) 0.1141
/*12 */ 		int g= (((uint32_t*)src)[i]>>8)&0xFF;                                      // (2) 0.1304
/*14 */ 		int b= (((uint32_t*)src)[i]>>16)&0xFF;                                     // (3) 0.1304
/*18 */ 		dst[i]= ((RY*r + GY*g + BY*b + (33<<(RGB2YUV_SHIFT-1)) )>>RGB2YUV_SHIFT);  // (0) 0.2446
/*20 */ 	}                                                                           // (8) 0.01087
/*22 */ }                                                                            // (10) 0.005435
