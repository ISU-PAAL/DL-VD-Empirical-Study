// commit message FFmpeg@a28cccf6d6 (target=1, prob=0.5908356, correct=True): Fix memory leak in ATRAC3 decoder
/*0  */ static av_cold void init_atrac3_transforms(ATRAC3Context *q) {                                                   // (4) 0.07034
/*2  */     float enc_window[256];                                                                                       // (11) 0.03058
/*4  */     int i;                                                                                                       // (13) 0.01835
/*8  */     /* Generate the mdct window, for details see                                                                 // (8) 0.04281
/*10 */      * http://wiki.multimedia.cx/index.php?title=RealAudio_atrc#Windows */                                       // (2) 0.08869
/*12 */     for (i=0 ; i<256; i++)                                                                                       // (7) 0.04587
/*14 */         enc_window[i] = (sin(((i + 0.5) / 256.0 - 0.5) * M_PI) + 1.0) * 0.5;                                     // (1) 0.1468
/*18 */     if (!mdct_window[0])                                                                                         // (10) 0.0367
/*20 */         for (i=0 ; i<256; i++) {                                                                                 // (6) 0.06116
/*22 */             mdct_window[i] = enc_window[i]/(enc_window[i]*enc_window[i] + enc_window[255-i]*enc_window[255-i]);  // (0) 0.1743
/*24 */             mdct_window[511-i] = mdct_window[i];                                                                 // (3) 0.08563
/*26 */         }                                                                                                        // (12) 0.02446
/*30 */     /* Initialize the MDCT transform. */                                                                         // (9) 0.0367
/*32 */     ff_mdct_init(&mdct_ctx, 9, 1, 1.0);                                                                          // (5) 0.07034
/*34 */ }                                                                                                                // (14) 0.003058
