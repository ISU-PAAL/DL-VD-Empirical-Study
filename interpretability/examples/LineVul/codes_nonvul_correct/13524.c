// commit message FFmpeg@6f1ec38ce2 (target=0, prob=0.090868704, correct=True): mpegaudio: clean up compute_antialias() definition
/*0  */ static void compute_antialias_float(MPADecodeContext *s,     // (4) 0.03516
/*2  */                               GranuleDef *g)                 // (2) 0.06836
/*4  */ {                                                            // (28) 0.001953
/*6  */     float *ptr;                                              // (25) 0.01367
/*8  */     int n, i;                                                // (24) 0.01562
/*12 */     /* we antialias only "long" bands */                     // (17) 0.02734
/*14 */     if (g->block_type == 2) {                                // (18) 0.02734
/*16 */         if (!g->switch_point)                                // (10) 0.0293
/*18 */             return;                                          // (21) 0.02539
/*20 */         /* XXX: check this for 8000Hz case */                // (6) 0.0332
/*22 */         n = 1;                                               // (22) 0.02148
/*24 */     } else {                                                 // (26) 0.01172
/*26 */         n = SBLIMIT - 1;                                     // (9) 0.03125
/*28 */     }                                                        // (27) 0.007812
/*32 */     ptr = g->sb_hybrid + 18;                                 // (19) 0.02734
/*34 */     for(i = n;i > 0;i--) {                                   // (7) 0.0332
/*36 */         float tmp0, tmp1;                                    // (20) 0.02734
/*38 */         float *csa = &csa_table_float[0][0];                 // (3) 0.04688
/*40 */ #define FLOAT_AA(j)\                                         // (23) 0.01953
/*42 */         tmp0= ptr[-1-j];\                                    // (5) 0.03516
/*44 */         tmp1= ptr[   j];\                                    // (8) 0.0332
/*46 */         ptr[-1-j] = tmp0 * csa[0+4*j] - tmp1 * csa[1+4*j];\  // (0) 0.08008
/*48 */         ptr[   j] = tmp0 * csa[1+4*j] + tmp1 * csa[0+4*j];   // (1) 0.07617
/*52 */         FLOAT_AA(0)                                          // (11) 0.0293
/*54 */         FLOAT_AA(1)                                          // (12) 0.0293
/*56 */         FLOAT_AA(2)                                          // (13) 0.0293
/*58 */         FLOAT_AA(3)                                          // (14) 0.0293
/*60 */         FLOAT_AA(4)                                          // (15) 0.0293
/*62 */         FLOAT_AA(5)                                          // (16) 0.0293
/*64 */         FLOAT_AA(6)                                          // 0.0
/*66 */         FLOAT_AA(7)                                          // 0.0
/*70 */         ptr += 18;                                           // 0.0
/*72 */     }                                                        // 0.0
/*74 */ }                                                            // 0.0
