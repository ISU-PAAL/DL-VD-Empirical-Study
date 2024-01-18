// commit message FFmpeg@e0c6cce447 (target=0, prob=0.032894716, correct=True): x86: Replace checks for CPU extensions and flags by convenience macros
/*0   */ av_cold void ff_sws_init_swScale_mmx(SwsContext *c)                                               // (6) 0.04492
/*2   */ {                                                                                                 // (20) 0.001953
/*4   */     int cpu_flags = av_get_cpu_flags();                                                           // (13) 0.03125
/*8   */ #if HAVE_INLINE_ASM                                                                               // (17) 0.01758
/*10  */     if (cpu_flags & AV_CPU_FLAG_MMX)                                                              // (10) 0.03516
/*12  */         sws_init_swScale_MMX(c);                                                                  // (8) 0.03906
/*14  */ #if HAVE_MMXEXT_INLINE                                                                            // (16) 0.01953
/*16  */     if (cpu_flags & AV_CPU_FLAG_MMXEXT)                                                           // (9) 0.03711
/*18  */         sws_init_swScale_MMX2(c);                                                                 // (7) 0.04102
/*20  */ #endif                                                                                            // (19) 0.003906
/*22  */ #endif /* HAVE_INLINE_ASM */                                                                      // (15) 0.02148
/*26  */ #if HAVE_YASM                                                                                     // (18) 0.01367
/*28  */ #define ASSIGN_SCALE_FUNC2(hscalefn, filtersize, opt1, opt2) do { \                               // (5) 0.05859
/*30  */     if (c->srcBpc == 8) { \                                                                       // (14) 0.0293
/*32  */         hscalefn = c->dstBpc <= 10 ? ff_hscale8to15_ ## filtersize ## _ ## opt2 : \               // (2) 0.07812
/*34  */                                      ff_hscale8to19_ ## filtersize ## _ ## opt1; \                // (0) 0.1055
/*36  */     } else if (c->srcBpc == 9) { \                                                                // (11) 0.0332
/*38  */         hscalefn = c->dstBpc <= 10 ? ff_hscale9to15_ ## filtersize ## _ ## opt2 : \               // (3) 0.07812
/*40  */                                      ff_hscale9to19_ ## filtersize ## _ ## opt1; \                // (1) 0.1055
/*42  */     } else if (c->srcBpc == 10) { \                                                               // (12) 0.0332
/*44  */         hscalefn = c->dstBpc <= 10 ? ff_hscale10to15_ ## filtersize ## _ ## opt2 : \              // (4) 0.07812
/*46  */                                      ff_hscale10to19_ ## filtersize ## _ ## opt1; \               // 0.0
/*48  */     } else /* c->srcBpc == 16 */ { \                                                              // 0.0
/*50  */         hscalefn = c->dstBpc <= 10 ? ff_hscale16to15_ ## filtersize ## _ ## opt2 : \              // 0.0
/*52  */                                      ff_hscale16to19_ ## filtersize ## _ ## opt1; \               // 0.0
/*54  */     } \                                                                                           // 0.0
/*56  */ } while (0)                                                                                       // 0.0
/*58  */ #define ASSIGN_MMX_SCALE_FUNC(hscalefn, filtersize, opt1, opt2) \                                 // 0.0
/*60  */     switch (filtersize) { \                                                                       // 0.0
/*62  */     case 4:  ASSIGN_SCALE_FUNC2(hscalefn, 4, opt1, opt2); break; \                                // 0.0
/*64  */     case 8:  ASSIGN_SCALE_FUNC2(hscalefn, 8, opt1, opt2); break; \                                // 0.0
/*66  */     default: ASSIGN_SCALE_FUNC2(hscalefn, X, opt1, opt2); break; \                                // 0.0
/*68  */     }                                                                                             // 0.0
/*70  */ #define ASSIGN_VSCALEX_FUNC(vscalefn, opt, do_16_case, condition_8bit) \                          // 0.0
/*72  */ switch(c->dstBpc){ \                                                                              // 0.0
/*74  */     case 16:                          do_16_case;                          break; \               // 0.0
/*76  */     case 10: if (!isBE(c->dstFormat)) vscalefn = ff_yuv2planeX_10_ ## opt; break; \               // 0.0
/*78  */     case 9:  if (!isBE(c->dstFormat)) vscalefn = ff_yuv2planeX_9_  ## opt; break; \               // 0.0
/*80  */     default: if (condition_8bit)      vscalefn = ff_yuv2planeX_8_  ## opt; break; \               // 0.0
/*82  */     }                                                                                             // 0.0
/*84  */ #define ASSIGN_VSCALE_FUNC(vscalefn, opt1, opt2, opt2chk) \                                       // 0.0
/*86  */     switch(c->dstBpc){ \                                                                          // 0.0
/*88  */     case 16: if (!isBE(c->dstFormat))            vscalefn = ff_yuv2plane1_16_ ## opt1; break; \   // 0.0
/*90  */     case 10: if (!isBE(c->dstFormat) && opt2chk) vscalefn = ff_yuv2plane1_10_ ## opt2; break; \   // 0.0
/*92  */     case 9:  if (!isBE(c->dstFormat) && opt2chk) vscalefn = ff_yuv2plane1_9_  ## opt2;  break; \  // 0.0
/*94  */     default:                                     vscalefn = ff_yuv2plane1_8_  ## opt1;  break; \  // 0.0
/*96  */     }                                                                                             // 0.0
/*98  */ #define case_rgb(x, X, opt) \                                                                     // 0.0
/*100 */         case PIX_FMT_ ## X: \                                                                     // 0.0
/*102 */             c->lumToYV12 = ff_ ## x ## ToY_ ## opt; \                                             // 0.0
/*104 */             if (!c->chrSrcHSubSample) \                                                           // 0.0
/*106 */                 c->chrToYV12 = ff_ ## x ## ToUV_ ## opt; \                                        // 0.0
/*108 */             break                                                                                 // 0.0
/*110 */ #if ARCH_X86_32                                                                                   // 0.0
/*112 */     if (cpu_flags & AV_CPU_FLAG_MMX) {                                                            // 0.0
/*114 */         ASSIGN_MMX_SCALE_FUNC(c->hyScale, c->hLumFilterSize, mmx, mmx);                           // 0.0
/*116 */         ASSIGN_MMX_SCALE_FUNC(c->hcScale, c->hChrFilterSize, mmx, mmx);                           // 0.0
/*118 */         ASSIGN_VSCALE_FUNC(c->yuv2plane1, mmx, mmx2, cpu_flags & AV_CPU_FLAG_MMXEXT);             // 0.0
/*122 */         switch (c->srcFormat) {                                                                   // 0.0
/*124 */         case PIX_FMT_Y400A:                                                                       // 0.0
/*126 */             c->lumToYV12 = ff_yuyvToY_mmx;                                                        // 0.0
/*128 */             if (c->alpPixBuf)                                                                     // 0.0
/*130 */                 c->alpToYV12 = ff_uyvyToY_mmx;                                                    // 0.0
/*132 */             break;                                                                                // 0.0
/*134 */         case PIX_FMT_YUYV422:                                                                     // 0.0
/*136 */             c->lumToYV12 = ff_yuyvToY_mmx;                                                        // 0.0
/*138 */             c->chrToYV12 = ff_yuyvToUV_mmx;                                                       // 0.0
/*140 */             break;                                                                                // 0.0
/*142 */         case PIX_FMT_UYVY422:                                                                     // 0.0
/*144 */             c->lumToYV12 = ff_uyvyToY_mmx;                                                        // 0.0
/*146 */             c->chrToYV12 = ff_uyvyToUV_mmx;                                                       // 0.0
/*148 */             break;                                                                                // 0.0
/*150 */         case PIX_FMT_NV12:                                                                        // 0.0
/*152 */             c->chrToYV12 = ff_nv12ToUV_mmx;                                                       // 0.0
/*154 */             break;                                                                                // 0.0
/*156 */         case PIX_FMT_NV21:                                                                        // 0.0
/*158 */             c->chrToYV12 = ff_nv21ToUV_mmx;                                                       // 0.0
/*160 */             break;                                                                                // 0.0
/*162 */         case_rgb(rgb24, RGB24, mmx);                                                              // 0.0
/*164 */         case_rgb(bgr24, BGR24, mmx);                                                              // 0.0
/*166 */         case_rgb(bgra,  BGRA,  mmx);                                                              // 0.0
/*168 */         case_rgb(rgba,  RGBA,  mmx);                                                              // 0.0
/*170 */         case_rgb(abgr,  ABGR,  mmx);                                                              // 0.0
/*172 */         case_rgb(argb,  ARGB,  mmx);                                                              // 0.0
/*174 */         default:                                                                                  // 0.0
/*176 */             break;                                                                                // 0.0
/*178 */         }                                                                                         // 0.0
/*180 */     }                                                                                             // 0.0
/*182 */     if (cpu_flags & AV_CPU_FLAG_MMXEXT) {                                                         // 0.0
/*184 */         ASSIGN_VSCALEX_FUNC(c->yuv2planeX, mmx2, , 1);                                            // 0.0
/*186 */     }                                                                                             // 0.0
/*188 */ #endif /* ARCH_X86_32 */                                                                          // 0.0
/*190 */ #define ASSIGN_SSE_SCALE_FUNC(hscalefn, filtersize, opt1, opt2) \                                 // 0.0
/*192 */     switch (filtersize) { \                                                                       // 0.0
/*194 */     case 4:  ASSIGN_SCALE_FUNC2(hscalefn, 4, opt1, opt2); break; \                                // 0.0
/*196 */     case 8:  ASSIGN_SCALE_FUNC2(hscalefn, 8, opt1, opt2); break; \                                // 0.0
/*198 */     default: if (filtersize & 4) ASSIGN_SCALE_FUNC2(hscalefn, X4, opt1, opt2); \                  // 0.0
/*200 */              else                ASSIGN_SCALE_FUNC2(hscalefn, X8, opt1, opt2); \                  // 0.0
/*202 */              break; \                                                                             // 0.0
/*204 */     }                                                                                             // 0.0
/*206 */     if (cpu_flags & AV_CPU_FLAG_SSE2) {                                                           // 0.0
/*208 */         ASSIGN_SSE_SCALE_FUNC(c->hyScale, c->hLumFilterSize, sse2, sse2);                         // 0.0
/*210 */         ASSIGN_SSE_SCALE_FUNC(c->hcScale, c->hChrFilterSize, sse2, sse2);                         // 0.0
/*212 */         ASSIGN_VSCALEX_FUNC(c->yuv2planeX, sse2, ,                                                // 0.0
/*214 */                             HAVE_ALIGNED_STACK || ARCH_X86_64);                                   // 0.0
/*216 */         ASSIGN_VSCALE_FUNC(c->yuv2plane1, sse2, sse2, 1);                                         // 0.0
/*220 */         switch (c->srcFormat) {                                                                   // 0.0
/*222 */         case PIX_FMT_Y400A:                                                                       // 0.0
/*224 */             c->lumToYV12 = ff_yuyvToY_sse2;                                                       // 0.0
/*226 */             if (c->alpPixBuf)                                                                     // 0.0
/*228 */                 c->alpToYV12 = ff_uyvyToY_sse2;                                                   // 0.0
/*230 */             break;                                                                                // 0.0
/*232 */         case PIX_FMT_YUYV422:                                                                     // 0.0
/*234 */             c->lumToYV12 = ff_yuyvToY_sse2;                                                       // 0.0
/*236 */             c->chrToYV12 = ff_yuyvToUV_sse2;                                                      // 0.0
/*238 */             break;                                                                                // 0.0
/*240 */         case PIX_FMT_UYVY422:                                                                     // 0.0
/*242 */             c->lumToYV12 = ff_uyvyToY_sse2;                                                       // 0.0
/*244 */             c->chrToYV12 = ff_uyvyToUV_sse2;                                                      // 0.0
/*246 */             break;                                                                                // 0.0
/*248 */         case PIX_FMT_NV12:                                                                        // 0.0
/*250 */             c->chrToYV12 = ff_nv12ToUV_sse2;                                                      // 0.0
/*252 */             break;                                                                                // 0.0
/*254 */         case PIX_FMT_NV21:                                                                        // 0.0
/*256 */             c->chrToYV12 = ff_nv21ToUV_sse2;                                                      // 0.0
/*258 */             break;                                                                                // 0.0
/*260 */         case_rgb(rgb24, RGB24, sse2);                                                             // 0.0
/*262 */         case_rgb(bgr24, BGR24, sse2);                                                             // 0.0
/*264 */         case_rgb(bgra,  BGRA,  sse2);                                                             // 0.0
/*266 */         case_rgb(rgba,  RGBA,  sse2);                                                             // 0.0
/*268 */         case_rgb(abgr,  ABGR,  sse2);                                                             // 0.0
/*270 */         case_rgb(argb,  ARGB,  sse2);                                                             // 0.0
/*272 */         default:                                                                                  // 0.0
/*274 */             break;                                                                                // 0.0
/*276 */         }                                                                                         // 0.0
/*278 */     }                                                                                             // 0.0
/*280 */     if (cpu_flags & AV_CPU_FLAG_SSSE3) {                                                          // 0.0
/*282 */         ASSIGN_SSE_SCALE_FUNC(c->hyScale, c->hLumFilterSize, ssse3, ssse3);                       // 0.0
/*284 */         ASSIGN_SSE_SCALE_FUNC(c->hcScale, c->hChrFilterSize, ssse3, ssse3);                       // 0.0
/*286 */         switch (c->srcFormat) {                                                                   // 0.0
/*288 */         case_rgb(rgb24, RGB24, ssse3);                                                            // 0.0
/*290 */         case_rgb(bgr24, BGR24, ssse3);                                                            // 0.0
/*292 */         default:                                                                                  // 0.0
/*294 */             break;                                                                                // 0.0
/*296 */         }                                                                                         // 0.0
/*298 */     }                                                                                             // 0.0
/*300 */     if (cpu_flags & AV_CPU_FLAG_SSE4) {                                                           // 0.0
/*302 */         /* Xto15 don't need special sse4 functions */                                             // 0.0
/*304 */         ASSIGN_SSE_SCALE_FUNC(c->hyScale, c->hLumFilterSize, sse4, ssse3);                        // 0.0
/*306 */         ASSIGN_SSE_SCALE_FUNC(c->hcScale, c->hChrFilterSize, sse4, ssse3);                        // 0.0
/*308 */         ASSIGN_VSCALEX_FUNC(c->yuv2planeX, sse4,                                                  // 0.0
/*310 */                             if (!isBE(c->dstFormat)) c->yuv2planeX = ff_yuv2planeX_16_sse4,       // 0.0
/*312 */                             HAVE_ALIGNED_STACK || ARCH_X86_64);                                   // 0.0
/*314 */         if (c->dstBpc == 16 && !isBE(c->dstFormat))                                               // 0.0
/*316 */             c->yuv2plane1 = ff_yuv2plane1_16_sse4;                                                // 0.0
/*318 */     }                                                                                             // 0.0
/*322 */     if (cpu_flags & AV_CPU_FLAG_AVX) {                                                            // 0.0
/*324 */         ASSIGN_VSCALEX_FUNC(c->yuv2planeX, avx, ,                                                 // 0.0
/*326 */                             HAVE_ALIGNED_STACK || ARCH_X86_64);                                   // 0.0
/*328 */         ASSIGN_VSCALE_FUNC(c->yuv2plane1, avx, avx, 1);                                           // 0.0
/*332 */         switch (c->srcFormat) {                                                                   // 0.0
/*334 */         case PIX_FMT_YUYV422:                                                                     // 0.0
/*336 */             c->chrToYV12 = ff_yuyvToUV_avx;                                                       // 0.0
/*338 */             break;                                                                                // 0.0
/*340 */         case PIX_FMT_UYVY422:                                                                     // 0.0
/*342 */             c->chrToYV12 = ff_uyvyToUV_avx;                                                       // 0.0
/*344 */             break;                                                                                // 0.0
/*346 */         case PIX_FMT_NV12:                                                                        // 0.0
/*348 */             c->chrToYV12 = ff_nv12ToUV_avx;                                                       // 0.0
/*350 */             break;                                                                                // 0.0
/*352 */         case PIX_FMT_NV21:                                                                        // 0.0
/*354 */             c->chrToYV12 = ff_nv21ToUV_avx;                                                       // 0.0
/*356 */             break;                                                                                // 0.0
/*358 */         case_rgb(rgb24, RGB24, avx);                                                              // 0.0
/*360 */         case_rgb(bgr24, BGR24, avx);                                                              // 0.0
/*362 */         case_rgb(bgra,  BGRA,  avx);                                                              // 0.0
/*364 */         case_rgb(rgba,  RGBA,  avx);                                                              // 0.0
/*366 */         case_rgb(abgr,  ABGR,  avx);                                                              // 0.0
/*368 */         case_rgb(argb,  ARGB,  avx);                                                              // 0.0
/*370 */         default:                                                                                  // 0.0
/*372 */             break;                                                                                // 0.0
/*374 */         }                                                                                         // 0.0
/*376 */     }                                                                                             // 0.0
/*378 */ #endif                                                                                            // 0.0
/*380 */ }                                                                                                 // 0.0
