// commit message FFmpeg@ed1a687856 (target=1, prob=0.7381923, correct=True): avcodec/lossless_videodsp: add_hfyu_left_prediction_int16_c: fix harmless integer overflow
/*0  */ static int add_hfyu_left_prediction_int16_c(uint16_t *dst, const uint16_t *src, unsigned mask, int w, int acc){  // (0) 0.2057
/*2  */     int i;                                                                                                       // (11) 0.02871
/*6  */     for(i=0; i<w-1; i++){                                                                                        // (1) 0.08612
/*8  */         acc+= src[i];                                                                                            // (5) 0.0622
/*10 */         dst[i]= acc & mask;                                                                                      // (4) 0.07177
/*12 */         i++;                                                                                                     // (9) 0.04306
/*14 */         acc+= src[i];                                                                                            // (6) 0.0622
/*16 */         dst[i]= acc & mask;                                                                                      // (3) 0.07177
/*18 */     }                                                                                                            // (12) 0.01914
/*22 */     for(; i<w; i++){                                                                                             // (8) 0.0622
/*24 */         acc+= src[i];                                                                                            // (7) 0.0622
/*26 */         dst[i]= acc & mask;                                                                                      // (2) 0.07177
/*28 */     }                                                                                                            // (13) 0.01914
/*32 */     return acc;                                                                                                  // (10) 0.02871
/*34 */ }                                                                                                                // (14) 0.004785
