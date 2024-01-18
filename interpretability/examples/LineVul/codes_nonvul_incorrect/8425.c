// commit message FFmpeg@b1306823d0 (target=0, prob=0.50851935, correct=False): check memory errors from av_strdup()
/*0  */ static int write_option(void *optctx, const OptionDef *po, const char *opt,                // (7) 0.04297
/*2  */                         const char *arg)                                                   // (4) 0.05469
/*4  */ {                                                                                          // (23) 0.001953
/*6  */     /* new-style options contain an offset into optctx, old-style address of               // (10) 0.03906
/*8  */      * a global var*/                                                                      // (20) 0.01758
/*10 */     void *dst = po->flags & (OPT_OFFSET | OPT_SPEC) ?                                      // (6) 0.04687
/*12 */                 (uint8_t *)optctx + po->u.off : po->u.dst_ptr;                             // (1) 0.07617
/*14 */     int *dstcount;                                                                         // (21) 0.01758
/*18 */     if (po->flags & OPT_SPEC) {                                                            // (18) 0.02734
/*20 */         SpecifierOpt **so = dst;                                                           // (17) 0.0293
/*22 */         char *p = strchr(opt, ':');                                                        // (9) 0.03906
/*26 */         dstcount = (int *)(so + 1);                                                        // (11) 0.03516
/*28 */         *so = grow_array(*so, sizeof(**so), dstcount, *dstcount + 1);                      // (3) 0.06055
/*30 */         (*so)[*dstcount - 1].specifier = av_strdup(p ? p + 1 : "");                        // (2) 0.06641
/*32 */         dst = &(*so)[*dstcount - 1].u;                                                     // (8) 0.04297
/*34 */     }                                                                                      // (22) 0.007813
/*38 */     if (po->flags & OPT_STRING) {                                                          // (16) 0.0293
/*40 */         char *str;                                                                         // (19) 0.02148
/*42 */         str = av_strdup(arg);                                                              // (13) 0.0332
/*44 */         av_freep(dst);                                                                     // (15) 0.0293
/*46 */         *(char **)dst = str;                                                               // (12) 0.0332
/*48 */     } else if (po->flags & OPT_BOOL || po->flags & OPT_INT) {                              // (5) 0.04883
/*50 */         *(int *)dst = parse_number_or_die(opt, arg, OPT_INT64, INT_MIN, INT_MAX);          // (0) 0.07617
/*52 */     } else if (po->flags & OPT_INT64) {                                                    // (14) 0.0332
/*54 */         *(int64_t *)dst = parse_number_or_die(opt, arg, OPT_INT64, INT64_MIN, INT64_MAX);  // 0.0
/*56 */     } else if (po->flags & OPT_TIME) {                                                     // 0.0
/*58 */         *(int64_t *)dst = parse_time_or_die(opt, arg, 1);                                  // 0.0
/*60 */     } else if (po->flags & OPT_FLOAT) {                                                    // 0.0
/*62 */         *(float *)dst = parse_number_or_die(opt, arg, OPT_FLOAT, -INFINITY, INFINITY);     // 0.0
/*64 */     } else if (po->flags & OPT_DOUBLE) {                                                   // 0.0
/*66 */         *(double *)dst = parse_number_or_die(opt, arg, OPT_DOUBLE, -INFINITY, INFINITY);   // 0.0
/*68 */     } else if (po->u.func_arg) {                                                           // 0.0
/*70 */         int ret = po->u.func_arg(optctx, opt, arg);                                        // 0.0
/*72 */         if (ret < 0) {                                                                     // 0.0
/*74 */             av_log(NULL, AV_LOG_ERROR,                                                     // 0.0
/*76 */                    "Failed to set value '%s' for option '%s'\n", arg, opt);                // 0.0
/*78 */             return ret;                                                                    // 0.0
/*80 */         }                                                                                  // 0.0
/*82 */     }                                                                                      // 0.0
/*84 */     if (po->flags & OPT_EXIT)                                                              // 0.0
/*86 */         exit_program(0);                                                                   // 0.0
/*90 */     return 0;                                                                              // 0.0
/*92 */ }                                                                                          // 0.0
