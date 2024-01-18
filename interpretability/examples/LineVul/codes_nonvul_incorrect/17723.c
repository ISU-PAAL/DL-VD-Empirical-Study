// commit message FFmpeg@3dfbdb328e (target=0, prob=0.9676885, correct=False): avcodec/ffv1dec: Check quant table symbols more completely
/*0  */ static int read_quant_table(RangeCoder *c, int16_t *quant_table, int scale)  // (0) 0.08638
/*2  */ {                                                                            // (18) 0.003322
/*4  */     int v;                                                                   // (16) 0.01993
/*6  */     int i = 0;                                                               // (14) 0.02658
/*8  */     uint8_t state[CONTEXT_SIZE];                                             // (9) 0.04651
/*12 */     memset(state, 128, sizeof(state));                                       // (10) 0.04651
/*16 */     for (v = 0; i < 128; v++) {                                              // (6) 0.05316
/*18 */         unsigned len = get_symbol(c, state, 0) + 1;                          // (1) 0.07973
/*22 */         if (len > 128 - i)                                                   // (7) 0.04983
/*24 */             return AVERROR_INVALIDDATA;                                      // (4) 0.06977
/*28 */         while (len--) {                                                      // (11) 0.04319
/*30 */             quant_table[i] = scale * v;                                      // (3) 0.07309
/*32 */             i++;                                                             // (12) 0.04319
/*34 */         }                                                                    // (15) 0.02658
/*36 */     }                                                                        // (17) 0.01329
/*40 */     for (i = 1; i < 128; i++)                                                // (8) 0.04983
/*42 */         quant_table[256 - i] = -quant_table[i];                              // (2) 0.07641
/*44 */     quant_table[128] = -quant_table[127];                                    // (5) 0.05648
/*48 */     return 2 * v - 1;                                                        // (13) 0.03322
/*50 */ }                                                                            // (19) 0.003322
