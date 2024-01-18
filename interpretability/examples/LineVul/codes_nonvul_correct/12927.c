// commit message FFmpeg@d68c05380c (target=0, prob=0.028247323, correct=True): x86: check for AV_CPU_FLAG_AVXSLOW where useful
/*0  */ av_cold void ff_dct_init_x86(DCTContext *s)  // (3) 0.1143
/*2  */ {                                            // (8) 0.005714
/*4  */     int cpu_flags = av_get_cpu_flags();      // (5) 0.09143
/*8  */     if (EXTERNAL_SSE(cpu_flags))             // (7) 0.09143
/*10 */         s->dct32 = ff_dct32_float_sse;       // (1) 0.1371
/*12 */     if (EXTERNAL_SSE2(cpu_flags))            // (4) 0.09714
/*14 */         s->dct32 = ff_dct32_float_sse2;      // (0) 0.1429
/*16 */     if (EXTERNAL_AVX(cpu_flags))             // (6) 0.09143
/*18 */         s->dct32 = ff_dct32_float_avx;       // (2) 0.1371
/*20 */ }                                            // (9) 0.005714
