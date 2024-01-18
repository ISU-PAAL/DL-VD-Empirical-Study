// commit message FFmpeg@e0c6cce447 (target=0, prob=0.044395912, correct=True): x86: Replace checks for CPU extensions and flags by convenience macros
/*0  */ av_cold void ff_vp56dsp_init_x86(VP56DSPContext* c, enum AVCodecID codec)  // (2) 0.1174
/*2  */ {                                                                          // (14) 0.003788
/*4  */ #if HAVE_YASM                                                              // (10) 0.02652
/*6  */     int mm_flags = av_get_cpu_flags();                                     // (6) 0.06061
/*10 */     if (CONFIG_VP6_DECODER && codec == AV_CODEC_ID_VP6) {                  // (3) 0.1098
/*12 */ #if ARCH_X86_32                                                            // (7) 0.03409
/*14 */         if (mm_flags & AV_CPU_FLAG_MMX) {                                  // (5) 0.08712
/*16 */             c->vp6_filter_diag4 = ff_vp6_filter_diag4_mmx;                 // (1) 0.1364
/*18 */         }                                                                  // (8) 0.0303
/*20 */ #endif                                                                     // (12) 0.007576
/*24 */         if (mm_flags & AV_CPU_FLAG_SSE2) {                                 // (4) 0.09091
/*26 */             c->vp6_filter_diag4 = ff_vp6_filter_diag4_sse2;                // (0) 0.1402
/*28 */         }                                                                  // (9) 0.0303
/*30 */     }                                                                      // (11) 0.01515
/*32 */ #endif                                                                     // (13) 0.007576
/*34 */ }                                                                          // (15) 0.003788
