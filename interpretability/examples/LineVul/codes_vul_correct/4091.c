// commit message FFmpeg@bc488ec28a (target=1, prob=0.99909854, correct=True): avcodec/me_cmp: Fix crashes on ARM due to misalignment
/*0  */ av_cold void ff_pixblockdsp_init_x86(PixblockDSPContext *c,    // (4) 0.07808
/*2  */                                      AVCodecContext *avctx,    // (0) 0.1321
/*4  */                                      unsigned high_bit_depth)  // (1) 0.1291
/*6  */ {                                                              // (14) 0.003003
/*8  */     int cpu_flags = av_get_cpu_flags();                        // (9) 0.04805
/*12 */     if (EXTERNAL_MMX(cpu_flags)) {                             // (8) 0.05105
/*14 */         if (!high_bit_depth)                                   // (10) 0.04505
/*16 */             c->get_pixels = ff_get_pixels_mmx;                 // (3) 0.08408
/*19 */         c->diff_pixels = ff_diff_pixels_mmx;                   // (6) 0.07207
/*21 */     }                                                          // (12) 0.01201
/*25 */     if (EXTERNAL_SSE2(cpu_flags)) {                            // (7) 0.05405
/*27 */         if (!high_bit_depth)                                   // (11) 0.04505
/*29 */             c->get_pixels = ff_get_pixels_sse2;                // (2) 0.08709
/*32 */         c->diff_pixels = ff_diff_pixels_sse2;                  // (5) 0.07508
/*34 */     }                                                          // (13) 0.01201
/*36 */ }                                                              // (15) 0.003003
