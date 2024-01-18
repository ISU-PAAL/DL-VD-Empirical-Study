// commit message FFmpeg@2254b559cb (target=1, prob=0.99249107, correct=True): swscale: make filterPos 32bit.
/*0  */ static void hScale8To15_c(SwsContext *c, int16_t *dst, int dstW, const uint8_t *src,  // (1) 0.1115
/*2  */                           const int16_t *filter, const int16_t *filterPos,            // (0) 0.13
/*4  */                           int filterSize)                                             // (4) 0.08978
/*6  */ {                                                                                     // (15) 0.003096
/*8  */     int i;                                                                            // (13) 0.01858
/*10 */     for (i=0; i<dstW; i++) {                                                          // (7) 0.05573
/*12 */         int j;                                                                        // (11) 0.03096
/*14 */         int srcPos= filterPos[i];                                                     // (8) 0.04954
/*16 */         int val=0;                                                                    // (10) 0.03715
/*18 */         for (j=0; j<filterSize; j++) {                                                // (5) 0.06502
/*20 */             val += ((int)src[srcPos + j])*filter[filterSize*i + j];                   // (2) 0.1022
/*22 */         }                                                                             // (12) 0.02477
/*24 */         //filter += hFilterSize;                                                      // (9) 0.04334
/*26 */         dst[i] = FFMIN(val>>7, (1<<15)-1); // the cubic equation does overflow ...    // (3) 0.1022
/*28 */         //dst[i] = val>>7;                                                            // (6) 0.05573
/*30 */     }                                                                                 // (14) 0.01238
/*32 */ }                                                                                     // (16) 0.003096
