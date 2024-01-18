// commit message FFmpeg@41a052a6ba (target=1, prob=0.37815487, correct=False): cmdutils: fix "oswr may be used uninitialized" warning
/*0  */ int opt_default(const char *opt, const char *arg)                                          // (14) 0.0293
/*2  */ {                                                                                          // (19) 0.001953
/*4  */     const AVOption *oc, *of, *os, *oswr;                                                   // (11) 0.03711
/*6  */     char opt_stripped[128];                                                                // (16) 0.02148
/*8  */     const char *p;                                                                         // (17) 0.01562
/*10 */     const AVClass *cc = avcodec_get_class(), *fc = avformat_get_class(), *sc, *swr_class;  // (3) 0.07031
/*14 */     if (!(p = strchr(opt, ':')))                                                           // (12) 0.0332
/*16 */         p = opt + strlen(opt);                                                             // (13) 0.03125
/*18 */     av_strlcpy(opt_stripped, opt, FFMIN(sizeof(opt_stripped), p - opt + 1));               // (5) 0.06445
/*22 */     if ((oc = av_opt_find(&cc, opt_stripped, NULL, 0,                                      // (8) 0.04687
/*24 */                          AV_OPT_SEARCH_CHILDREN | AV_OPT_SEARCH_FAKE_OBJ)) ||              // (1) 0.1016
/*26 */         ((opt[0] == 'v' || opt[0] == 'a' || opt[0] == 's') &&                              // (4) 0.06836
/*28 */          (oc = av_opt_find(&cc, opt + 1, NULL, 0, AV_OPT_SEARCH_FAKE_OBJ))))               // (2) 0.08008
/*30 */         av_dict_set(&codec_opts, opt, arg, FLAGS(oc));                                     // (6) 0.05664
/*32 */     if ((of = av_opt_find(&fc, opt, NULL, 0,                                               // (10) 0.04102
/*34 */                           AV_OPT_SEARCH_CHILDREN | AV_OPT_SEARCH_FAKE_OBJ)))               // (0) 0.1016
/*36 */         av_dict_set(&format_opts, opt, arg, FLAGS(of));                                    // (7) 0.05469
/*38 */ #if CONFIG_SWSCALE                                                                         // (18) 0.01367
/*40 */     sc = sws_get_class();                                                                  // (15) 0.02344
/*42 */     if ((os = av_opt_find(&sc, opt, NULL, 0,                                               // (9) 0.04102
/*44 */                           AV_OPT_SEARCH_CHILDREN | AV_OPT_SEARCH_FAKE_OBJ))) {             // 0.0
/*46 */         // XXX we only support sws_flags, not arbitrary sws options                        // 0.0
/*48 */         int ret = av_opt_set(sws_opts, opt, arg, 0);                                       // 0.0
/*50 */         if (ret < 0) {                                                                     // 0.0
/*52 */             av_log(NULL, AV_LOG_ERROR, "Error setting option %s.\n", opt);                 // 0.0
/*54 */             return ret;                                                                    // 0.0
/*56 */         }                                                                                  // 0.0
/*58 */     }                                                                                      // 0.0
/*60 */ #endif                                                                                     // 0.0
/*62 */     swr_class = swr_get_class();                                                           // 0.0
/*64 */     if (!oc && !of && !os && (oswr = av_opt_find(&swr_class, opt, NULL, 0,                 // 0.0
/*66 */                           AV_OPT_SEARCH_CHILDREN | AV_OPT_SEARCH_FAKE_OBJ))) {             // 0.0
/*68 */         int ret = av_opt_set(swr_opts, opt, arg, 0);                                       // 0.0
/*70 */         if (ret < 0) {                                                                     // 0.0
/*72 */             av_log(NULL, AV_LOG_ERROR, "Error setting option %s.\n", opt);                 // 0.0
/*74 */             return ret;                                                                    // 0.0
/*76 */         }                                                                                  // 0.0
/*78 */     }                                                                                      // 0.0
/*82 */     if (oc || of || os || oswr)                                                            // 0.0
/*84 */         return 0;                                                                          // 0.0
/*86 */     av_log(NULL, AV_LOG_ERROR, "Unrecognized option '%s'\n", opt);                         // 0.0
/*88 */     return AVERROR_OPTION_NOT_FOUND;                                                       // 0.0
/*90 */ }                                                                                          // 0.0
