// commit message FFmpeg@f20b67173c (target=0, prob=0.7489522, correct=False): aacenc_tns: rework the way coefficients are calculated
/*0  */ static void apply_tns_filter(float *out, float *in, int order, int direction,  // (10) 0.04492
/*2  */                              float *tns_coefs, int ltp_used, int w, int filt,  // (0) 0.09766
/*4  */                              int start_i, int len)                             // (2) 0.07031
/*6  */ {                                                                              // (22) 0.001953
/*8  */     int i, j, inc, start = start_i;                                            // (16) 0.03125
/*10 */     float tmp[TNS_MAX_ORDER+1];                                                // (15) 0.03125
/*12 */     if (direction) {                                                           // (19) 0.01562
/*14 */         inc = -1;                                                              // (17) 0.02344
/*16 */         start = (start + len) - 1;                                             // (14) 0.0332
/*18 */     } else {                                                                   // (20) 0.01172
/*20 */         inc = 1;                                                               // (18) 0.02148
/*22 */     }                                                                          // (21) 0.007812
/*24 */     if (!ltp_used) {    /* AR filter */                                        // (13) 0.03516
/*26 */         for (i = 0; i < len; i++, start += inc)                                // (9) 0.04687
/*28 */             out[i] = in[start];                                                // (12) 0.03906
/*30 */             for (j = 1; j <= FFMIN(i, order); j++)                             // (5) 0.05469
/*32 */                 out[i] += tns_coefs[j]*in[start - j*inc];                      // (1) 0.07422
/*34 */     } else {            /* MA filter */                                        // (11) 0.04102
/*36 */         for (i = 0; i < len; i++, start += inc) {                              // (6) 0.04883
/*38 */             tmp[0] = out[i] = in[start];                                       // (7) 0.04883
/*40 */             for (j = 1; j <= FFMIN(i, order); j++)                             // (4) 0.05469
/*42 */                 out[i] += tmp[j]*tns_coefs[j];                                 // (3) 0.06641
/*44 */             for (j = order; j > 0; j--)                                        // (8) 0.04687
/*46 */                 tmp[j] = tmp[j - 1];                                           // 0.0
/*48 */         }                                                                      // 0.0
/*50 */     }                                                                          // 0.0
/*52 */ }                                                                              // 0.0
