// commit message FFmpeg@01ecb7172b (target=1, prob=0.9759948, correct=True): AAC encoder: Extensive improvements
/*0  */ static void quantize_and_encode_band_cost_ZERO_mips(struct AACEncContext *s,                              // (4) 0.05625
/*2  */                                                          PutBitContext *pb, const float *in, float *out,  // (0) 0.1479
/*4  */                                                          const float *scaled, int size, int scale_idx,    // (1) 0.1479
/*6  */                                                          int cb, const float lambda, const float uplim,   // (2) 0.1438
/*8  */                                                          int *bits, const float ROUNDING) {               // (3) 0.1396
/*10 */     int i;                                                                                                // (14) 0.0125
/*12 */     if (bits)                                                                                             // (13) 0.01458
/*14 */         *bits = 0;                                                                                        // (10) 0.025
/*16 */     if (out) {                                                                                            // (12) 0.01667
/*18 */         for (i = 0; i < size; i += 4) {                                                                   // (5) 0.04583
/*20 */            out[i  ] = 0.0f;                                                                               // (9) 0.04375
/*22 */            out[i+1] = 0.0f;                                                                               // (6) 0.04583
/*24 */            out[i+2] = 0.0f;                                                                               // (7) 0.04583
/*26 */            out[i+3] = 0.0f;                                                                               // (8) 0.04583
/*28 */         }                                                                                                 // (11) 0.01667
/*30 */     }                                                                                                     // (15) 0.008333
/*32 */ }                                                                                                         // (16) 0.002083
