// commit message FFmpeg@79997def65 (target=0, prob=0.4269021, correct=True): ac3enc: use generic fixed-point mdct
/*0  */ static void mdct_test(AC3MDCTContext *mdct, AVLFG *lfg)                            // (5) 0.04492
/*2  */ {                                                                                  // (25) 0.001953
/*4  */     int16_t input[MDCT_SAMPLES];                                                   // (12) 0.03125
/*6  */     int32_t output[AC3_MAX_COEFS];                                                 // (10) 0.03516
/*8  */     float input1[MDCT_SAMPLES];                                                    // (15) 0.02734
/*10 */     float output1[AC3_MAX_COEFS];                                                  // (13) 0.03125
/*12 */     float s, a, err, e, emax;                                                      // (14) 0.0293
/*14 */     int i, k, n;                                                                   // (18) 0.01953
/*18 */     for (i = 0; i < MDCT_SAMPLES; i++) {                                           // (9) 0.04102
/*20 */         input[i]  = (av_lfg_get(lfg) % 65535 - 32767) * 9 / 10;                    // (2) 0.07031
/*22 */         input1[i] = input[i];                                                      // (11) 0.0332
/*24 */     }                                                                              // (23) 0.007812
/*28 */     mdct512(mdct, output, input);                                                  // (16) 0.02734
/*32 */     /* do it by hand */                                                            // (19) 0.01758
/*34 */     for (k = 0; k < AC3_MAX_COEFS; k++) {                                          // (6) 0.04492
/*36 */         s = 0;                                                                     // (17) 0.02148
/*38 */         for (n = 0; n < MDCT_SAMPLES; n++) {                                       // (3) 0.04883
/*40 */             a = (2*M_PI*(2*n+1+MDCT_SAMPLES/2)*(2*k+1) / (4 * MDCT_SAMPLES));      // (0) 0.1055
/*42 */             s += input1[n] * cos(a);                                               // (7) 0.04492
/*44 */         }                                                                          // (20) 0.01562
/*46 */         output1[k] = -2 * s / MDCT_SAMPLES;                                        // (4) 0.04883
/*48 */     }                                                                              // (24) 0.007812
/*52 */     err  = 0;                                                                      // (21) 0.01562
/*54 */     emax = 0;                                                                      // (22) 0.01562
/*56 */     for (i = 0; i < AC3_MAX_COEFS; i++) {                                          // (8) 0.04492
/*58 */         av_log(NULL, AV_LOG_DEBUG, "%3d: %7d %7.0f\n", i, output[i], output1[i]);  // (1) 0.08789
/*60 */         e = output[i] - output1[i];                                                // 0.0
/*62 */         if (e > emax)                                                              // 0.0
/*64 */             emax = e;                                                              // 0.0
/*66 */         err += e * e;                                                              // 0.0
/*68 */     }                                                                              // 0.0
/*70 */     av_log(NULL, AV_LOG_DEBUG, "err2=%f emax=%f\n", err / AC3_MAX_COEFS, emax);    // 0.0
/*72 */ }                                                                                  // 0.0
