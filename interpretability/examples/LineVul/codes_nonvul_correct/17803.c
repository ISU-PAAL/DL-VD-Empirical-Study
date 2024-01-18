// commit message FFmpeg@d68c05380c (target=0, prob=0.04982916, correct=True): x86: check for AV_CPU_FLAG_AVXSLOW where useful
/*0  */ av_cold void ff_float_dsp_init_x86(AVFloatDSPContext *fdsp)       // (10) 0.04883
/*2  */ {                                                                 // (23) 0.001953
/*4  */     int cpu_flags = av_get_cpu_flags();                           // (15) 0.03125
/*8  */ #if HAVE_6REGS && HAVE_INLINE_ASM                                 // (17) 0.0293
/*10 */     if (INLINE_AMD3DNOWEXT(cpu_flags)) {                          // (11) 0.03711
/*12 */         fdsp->vector_fmul_window  = vector_fmul_window_3dnowext;  // (4) 0.06055
/*14 */     }                                                             // (19) 0.007812
/*16 */     if (INLINE_SSE(cpu_flags)) {                                  // (16) 0.03125
/*18 */         fdsp->vector_fmul_window = vector_fmul_window_sse;        // (8) 0.05469
/*20 */     }                                                             // (18) 0.007813
/*22 */ #endif                                                            // (22) 0.003906
/*24 */     if (EXTERNAL_SSE(cpu_flags)) {                                // (13) 0.0332
/*26 */         fdsp->vector_fmul = ff_vector_fmul_sse;                   // (9) 0.05078
/*28 */         fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_sse;     // (1) 0.06641
/*30 */         fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_sse;     // (2) 0.06641
/*32 */         fdsp->vector_fmul_add    = ff_vector_fmul_add_sse;        // (3) 0.06445
/*34 */         fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_sse;   // (6) 0.05859
/*36 */         fdsp->scalarproduct_float = ff_scalarproduct_float_sse;   // (7) 0.05859
/*38 */         fdsp->butterflies_float   = ff_butterflies_float_sse;     // (5) 0.05859
/*40 */     }                                                             // (20) 0.007812
/*42 */     if (EXTERNAL_SSE2(cpu_flags)) {                               // (12) 0.03516
/*44 */         fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_sse2;    // (0) 0.06836
/*46 */     }                                                             // (21) 0.007812
/*48 */     if (EXTERNAL_AVX(cpu_flags)) {                                // (14) 0.0332
/*50 */         fdsp->vector_fmul = ff_vector_fmul_avx;                   // 0.0
/*52 */         fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_avx;     // 0.0
/*54 */         fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_avx;     // 0.0
/*56 */         fdsp->vector_fmul_add    = ff_vector_fmul_add_avx;        // 0.0
/*58 */         fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_avx;   // 0.0
/*60 */     }                                                             // 0.0
/*62 */ }                                                                 // 0.0
