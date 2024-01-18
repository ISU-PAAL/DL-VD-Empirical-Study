// commit message FFmpeg@60f10e0ad3 (target=1, prob=0.99744654, correct=True): h264pred: use unsigned types for pixel values, fix signed overflows
/*0  */ static void pred8x8_top_dc_rv40_c(uint8_t *src, int stride){  // (0) 0.1414
/*2  */     int i;                                                    // (9) 0.03141
/*4  */     int dc0;                                                  // (8) 0.03665
/*8  */     dc0=0;                                                    // (7) 0.04188
/*10 */     for(i=0;i<8; i++)                                         // (6) 0.07853
/*12 */         dc0+= src[i-stride];                                  // (4) 0.08901
/*14 */     dc0= 0x01010101*((dc0 + 4)>>3);                           // (3) 0.1152
/*18 */     for(i=0; i<8; i++){                                       // (5) 0.08377
/*20 */         ((uint32_t*)(src+i*stride))[0]=                       // (2) 0.1257
/*22 */         ((uint32_t*)(src+i*stride))[1]= dc0;                  // (1) 0.1414
/*24 */     }                                                         // (10) 0.02094
/*26 */ }                                                             // (11) 0.005236
