// commit message FFmpeg@f43a16049e (target=0, prob=0.17179553, correct=True): cmdutils: Fix cpuflags so the flags dont pull in and out other flags.
/*0   */ int opt_cpuflags(const char *opt, const char *arg)                                                 // (14) 0.03125
/*2   */ {                                                                                                  // (15) 0.001953
/*4   */ #define CPUFLAG_MMX2     (AV_CPU_FLAG_MMX      | AV_CPU_FLAG_MMX2)                                 // (0) 0.07227
/*6   */ #define CPUFLAG_3DNOW    (AV_CPU_FLAG_3DNOW    | AV_CPU_FLAG_MMX)                                  // (1) 0.06641
/*8   */ #define CPUFLAG_3DNOWEXT (AV_CPU_FLAG_3DNOWEXT | CPUFLAG_3DNOW)                                    // (13) 0.05469
/*10  */ #define CPUFLAG_SSE      (AV_CPU_FLAG_SSE      | CPUFLAG_MMX2)                                     // (3) 0.06641
/*12  */ #define CPUFLAG_SSE2     (AV_CPU_FLAG_SSE2     | CPUFLAG_SSE)                                      // (8) 0.06445
/*14  */ #define CPUFLAG_SSE2SLOW (AV_CPU_FLAG_SSE2SLOW | CPUFLAG_SSE2)                                     // (11) 0.05859
/*16  */ #define CPUFLAG_SSE3     (AV_CPU_FLAG_SSE3     | CPUFLAG_SSE2)                                     // (4) 0.06641
/*18  */ #define CPUFLAG_SSE3SLOW (AV_CPU_FLAG_SSE3SLOW | CPUFLAG_SSE3)                                     // (12) 0.05859
/*20  */ #define CPUFLAG_SSSE3    (AV_CPU_FLAG_SSSE3    | CPUFLAG_SSE3)                                     // (10) 0.0625
/*22  */ #define CPUFLAG_SSE4     (AV_CPU_FLAG_SSE4     | CPUFLAG_SSSE3)                                    // (5) 0.06641
/*24  */ #define CPUFLAG_SSE42    (AV_CPU_FLAG_SSE42    | CPUFLAG_SSE4)                                     // (9) 0.0625
/*26  */ #define CPUFLAG_AVX      (AV_CPU_FLAG_AVX      | CPUFLAG_SSE42)                                    // (2) 0.06641
/*28  */ #define CPUFLAG_XOP      (AV_CPU_FLAG_XOP      | CPUFLAG_AVX)                                      // (7) 0.06445
/*30  */ #define CPUFLAG_FMA4     (AV_CPU_FLAG_FMA4     | CPUFLAG_AVX)                                      // (6) 0.06445
/*32  */     static const AVOption cpuflags_opts[] = {                                                      // 0.0
/*34  */         { "flags"   , NULL, 0, AV_OPT_TYPE_FLAGS, { 0 }, INT64_MIN, INT64_MAX, .unit = "flags" },  // 0.0
/*36  */         { "altivec" , NULL, 0, AV_OPT_TYPE_CONST, { AV_CPU_FLAG_ALTIVEC  },    .unit = "flags" },  // 0.0
/*38  */         { "mmx"     , NULL, 0, AV_OPT_TYPE_CONST, { AV_CPU_FLAG_MMX      },    .unit = "flags" },  // 0.0
/*40  */         { "mmx2"    , NULL, 0, AV_OPT_TYPE_CONST, { CPUFLAG_MMX2         },    .unit = "flags" },  // 0.0
/*42  */         { "sse"     , NULL, 0, AV_OPT_TYPE_CONST, { CPUFLAG_SSE          },    .unit = "flags" },  // 0.0
/*44  */         { "sse2"    , NULL, 0, AV_OPT_TYPE_CONST, { CPUFLAG_SSE2         },    .unit = "flags" },  // 0.0
/*46  */         { "sse2slow", NULL, 0, AV_OPT_TYPE_CONST, { CPUFLAG_SSE2SLOW     },    .unit = "flags" },  // 0.0
/*48  */         { "sse3"    , NULL, 0, AV_OPT_TYPE_CONST, { CPUFLAG_SSE3         },    .unit = "flags" },  // 0.0
/*50  */         { "sse3slow", NULL, 0, AV_OPT_TYPE_CONST, { CPUFLAG_SSE3SLOW     },    .unit = "flags" },  // 0.0
/*52  */         { "ssse3"   , NULL, 0, AV_OPT_TYPE_CONST, { CPUFLAG_SSSE3        },    .unit = "flags" },  // 0.0
/*54  */         { "atom"    , NULL, 0, AV_OPT_TYPE_CONST, { AV_CPU_FLAG_ATOM     },    .unit = "flags" },  // 0.0
/*56  */         { "sse4.1"  , NULL, 0, AV_OPT_TYPE_CONST, { CPUFLAG_SSE4         },    .unit = "flags" },  // 0.0
/*58  */         { "sse4.2"  , NULL, 0, AV_OPT_TYPE_CONST, { CPUFLAG_SSE42        },    .unit = "flags" },  // 0.0
/*60  */         { "avx"     , NULL, 0, AV_OPT_TYPE_CONST, { CPUFLAG_AVX          },    .unit = "flags" },  // 0.0
/*62  */         { "xop"     , NULL, 0, AV_OPT_TYPE_CONST, { CPUFLAG_XOP          },    .unit = "flags" },  // 0.0
/*64  */         { "fma4"    , NULL, 0, AV_OPT_TYPE_CONST, { CPUFLAG_FMA4         },    .unit = "flags" },  // 0.0
/*66  */         { "3dnow"   , NULL, 0, AV_OPT_TYPE_CONST, { CPUFLAG_3DNOW        },    .unit = "flags" },  // 0.0
/*68  */         { "3dnowext", NULL, 0, AV_OPT_TYPE_CONST, { CPUFLAG_3DNOWEXT     },    .unit = "flags" },  // 0.0
/*70  */         { NULL },                                                                                  // 0.0
/*72  */     };                                                                                             // 0.0
/*74  */     static const AVClass class = {                                                                 // 0.0
/*76  */         .class_name = "cpuflags",                                                                  // 0.0
/*78  */         .item_name  = av_default_item_name,                                                        // 0.0
/*80  */         .option     = cpuflags_opts,                                                               // 0.0
/*82  */         .version    = LIBAVUTIL_VERSION_INT,                                                       // 0.0
/*84  */     };                                                                                             // 0.0
/*86  */     int flags = av_get_cpu_flags();                                                                // 0.0
/*88  */     int ret;                                                                                       // 0.0
/*90  */     const AVClass *pclass = &class;                                                                // 0.0
/*94  */     if ((ret = av_opt_eval_flags(&pclass, &cpuflags_opts[0], arg, &flags)) < 0)                    // 0.0
/*96  */         return ret;                                                                                // 0.0
/*100 */     av_force_cpu_flags(flags);                                                                     // 0.0
/*102 */     return 0;                                                                                      // 0.0
/*104 */ }                                                                                                  // 0.0
