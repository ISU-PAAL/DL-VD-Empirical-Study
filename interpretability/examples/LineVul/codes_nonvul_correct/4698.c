// commit message FFmpeg@d1adad3cca (target=0, prob=0.044037096, correct=True): Merge swscale bloatup This will be cleaned up in the next merge
/*0  */ void sws_rgb2rgb_init(int flags)                         // (11) 0.05929
/*2  */ {                                                        // (13) 0.003953
/*4  */ #if HAVE_SSE2 || HAVE_MMX2 || HAVE_AMD3DNOW || HAVE_MMX  // (0) 0.09881
/*6  */     if (flags & SWS_CPU_CAPS_SSE2)                       // (4) 0.0751
/*8  */         rgb2rgb_init_SSE2();                             // (6) 0.07115
/*10 */     else if (flags & SWS_CPU_CAPS_MMX2)                  // (2) 0.07905
/*12 */         rgb2rgb_init_MMX2();                             // (7) 0.07115
/*14 */     else if (flags & SWS_CPU_CAPS_3DNOW)                 // (3) 0.07905
/*16 */         rgb2rgb_init_3DNOW();                            // (8) 0.07115
/*18 */     else if (flags & SWS_CPU_CAPS_MMX)                   // (5) 0.0751
/*20 */         rgb2rgb_init_MMX();                              // (9) 0.06719
/*22 */     else                                                 // (12) 0.01581
/*24 */ #endif /* HAVE_MMX2 || HAVE_AMD3DNOW || HAVE_MMX */      // (1) 0.083
/*26 */         rgb2rgb_init_C();                                // (10) 0.06324
/*28 */ }                                                        // (14) 0.003953
