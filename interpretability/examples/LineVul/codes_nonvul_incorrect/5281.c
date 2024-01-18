// commit message FFmpeg@63b1866ae1 (target=0, prob=0.6983953, correct=False): ac3enc: clip large coefficient values and negative exponents rather than using av_assert2().
/*0  */ static void ac3_extract_exponents_c(uint8_t *exp, int32_t *coef, int nb_coefs)  // (0) 0.1229
/*2  */ {                                                                               // (17) 0.003413
/*4  */     int i;                                                                      // (15) 0.02048
/*8  */     for (i = 0; i < nb_coefs; i++) {                                            // (3) 0.07167
/*10 */         int e;                                                                  // (12) 0.03413
/*12 */         int v = abs(coef[i]);                                                   // (7) 0.05802
/*14 */         if (v == 0)                                                             // (10) 0.04437
/*16 */             e = 24;                                                             // (8) 0.05119
/*18 */         else {                                                                  // (13) 0.03072
/*20 */             e = 23 - av_log2(v);                                                // (2) 0.07509
/*22 */             if (e >= 24) {                                                      // (6) 0.06143
/*24 */                 e = 24;                                                         // (5) 0.06485
/*26 */                 coef[i] = 0;                                                    // (1) 0.0785
/*28 */             }                                                                   // (11) 0.04096
/*30 */             av_assert2(e >= 0);                                                 // (4) 0.06826
/*32 */         }                                                                       // (14) 0.0273
/*34 */         exp[i] = e;                                                             // (9) 0.04778
/*36 */     }                                                                           // (16) 0.01365
/*38 */ }                                                                               // (18) 0.003413
