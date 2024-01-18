// commit message FFmpeg@221b804f34 (target=1, prob=0.9818293, correct=True): cosmetics attack, part II: Remove all tabs and prettyprint/reindent the code.
/*0  */ static inline void yuv2packedXinC(SwsContext *c, int16_t *lumFilter, int16_t **lumSrc, int lumFilterSize,  // (0) 0.1015
/*2  */ 				    int16_t *chrFilter, int16_t **chrSrc, int chrFilterSize,                                           // (3) 0.07921
/*4  */ 				    uint8_t *dest, int dstW, int y)                                                                    // (4) 0.05198
/*6  */ {                                                                                                          // (23) 0.002475
/*8  */ 	int i;                                                                                                    // (18) 0.009901
/*10 */ 	switch(c->dstFormat)                                                                                      // (16) 0.02228
/*12 */ 	{                                                                                                         // (22) 0.00495
/*14 */ 	case PIX_FMT_BGR32:                                                                                       // (13) 0.0297
/*16 */ 	case PIX_FMT_RGB32:                                                                                       // (14) 0.02723
/*18 */ 		YSCALE_YUV_2_RGBX_C(uint32_t)                                                                            // (5) 0.05198
/*20 */ 			((uint32_t*)dest)[i2+0]= r[Y1] + g[Y1] + b[Y1];                                                         // (1) 0.08168
/*22 */ 			((uint32_t*)dest)[i2+1]= r[Y2] + g[Y2] + b[Y2];                                                         // (2) 0.08168
/*24 */ 		}                                                                                                        // (20) 0.007426
/*26 */ 		break;                                                                                                   // (19) 0.009901
/*28 */ 	case PIX_FMT_RGB24:                                                                                       // (15) 0.02723
/*30 */ 		YSCALE_YUV_2_RGBX_C(uint8_t)                                                                             // (6) 0.05198
/*32 */ 			((uint8_t*)dest)[0]= r[Y1];                                                                             // (7) 0.04455
/*34 */ 			((uint8_t*)dest)[1]= g[Y1];                                                                             // (8) 0.04455
/*36 */ 			((uint8_t*)dest)[2]= b[Y1];                                                                             // (9) 0.04455
/*38 */ 			((uint8_t*)dest)[3]= r[Y2];                                                                             // (10) 0.04455
/*40 */ 			((uint8_t*)dest)[4]= g[Y2];                                                                             // (11) 0.04455
/*42 */ 			((uint8_t*)dest)[5]= b[Y2];                                                                             // (12) 0.04455
/*44 */ 			dest+=6;                                                                                                // (17) 0.01733
/*46 */ 		}                                                                                                        // (21) 0.007426
