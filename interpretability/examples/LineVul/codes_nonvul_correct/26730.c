// commit message FFmpeg@79997def65 (target=0, prob=0.019651154, correct=True): ac3enc: use generic fixed-point mdct
/*0  */ static av_cold int fft_init(AVCodecContext *avctx, AC3MDCTContext *mdct, int ln)        // (2) 0.1003
/*2  */ {                                                                                       // (16) 0.003236
/*4  */     int i, n, n2;                                                                       // (8) 0.0356
/*6  */     float alpha;                                                                        // (13) 0.01942
/*10 */     n  = 1 << ln;                                                                       // (9) 0.0356
/*12 */     n2 = n >> 1;                                                                        // (11) 0.03236
/*16 */     FF_ALLOC_OR_GOTO(avctx, mdct->costab, n2 * sizeof(*mdct->costab), fft_alloc_fail);  // (1) 0.1294
/*18 */     FF_ALLOC_OR_GOTO(avctx, mdct->sintab, n2 * sizeof(*mdct->sintab), fft_alloc_fail);  // (0) 0.1359
/*22 */     for (i = 0; i < n2; i++) {                                                          // (6) 0.05502
/*24 */         alpha     = 2.0 * M_PI * i / n;                                                 // (3) 0.08091
/*26 */         mdct->costab[i] = FIX15(cos(alpha));                                            // (5) 0.07443
/*28 */         mdct->sintab[i] = FIX15(sin(alpha));                                            // (4) 0.07767
/*30 */     }                                                                                   // (15) 0.01294
/*34 */     return 0;                                                                           // (14) 0.01942
/*36 */ fft_alloc_fail:                                                                         // (12) 0.02265
/*38 */     mdct_end(mdct);                                                                     // (10) 0.0356
/*40 */     return AVERROR(ENOMEM);                                                             // (7) 0.03883
/*42 */ }                                                                                       // (17) 0.003236
