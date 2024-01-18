// commit message FFmpeg@3e1028c625 (target=1, prob=0.21367598, correct=False): avcodec/flac: Fix several integer overflows
/*0  */ static void lpc_analyze_remodulate(int32_t *decoded, const int coeffs[32],   // (3) 0.0678
/*2  */                                    int order, int qlevel, int len, int bps)  // (0) 0.1162
/*4  */ {                                                                            // (21) 0.002421
/*6  */     int i, j;                                                                // (18) 0.01937
/*8  */     int ebps = 1 << (bps-1);                                                 // (14) 0.0339
/*10 */     unsigned sigma = 0;                                                      // (16) 0.02179
/*14 */     for (i = order; i < len; i++)                                            // (11) 0.03632
/*16 */         sigma |= decoded[i] + ebps;                                          // (4) 0.04843
/*20 */     if (sigma < 2*ebps)                                                      // (15) 0.03148
/*22 */         return;                                                              // (17) 0.02179
/*26 */     for (i = len - 1; i >= order; i--) {                                     // (6) 0.046
/*28 */         int64_t p = 0;                                                       // (12) 0.03632
/*30 */         for (j = 0; j < order; j++)                                          // (7) 0.046
/*32 */             p += coeffs[j] * (int64_t)decoded[i-order+j];                    // (1) 0.08475
/*34 */         decoded[i] -= p >> qlevel;                                           // (9) 0.04358
/*36 */     }                                                                        // (19) 0.009685
/*38 */     for (i = order; i < len; i++, decoded++) {                               // (5) 0.04843
/*40 */         int32_t p = 0;                                                       // (13) 0.03632
/*42 */         for (j = 0; j < order; j++)                                          // (8) 0.046
/*44 */             p += coeffs[j] * (uint32_t)decoded[j];                           // (2) 0.07506
/*46 */         decoded[j] += p >> qlevel;                                           // (10) 0.04358
/*48 */     }                                                                        // (20) 0.009685
/*50 */ }                                                                            // (22) 0.002421
