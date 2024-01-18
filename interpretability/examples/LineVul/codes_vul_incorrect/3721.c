// commit message FFmpeg@2f86e7bd12 (target=1, prob=0.39602804, correct=False): graphparser: add a NULL check on the argument passed to strstr
/*0  */ static int create_filter(AVFilterContext **filt_ctx, AVFilterGraph *ctx, int index,   // (7) 0.04688
/*2  */                          const char *filt_name, const char *args, AVClass *log_ctx)   // (0) 0.08594
/*4  */ {                                                                                     // (25) 0.001953
/*6  */     AVFilter *filt;                                                                   // (19) 0.01758
/*8  */     char inst_name[30];                                                               // (16) 0.01953
/*10 */     char tmp_args[256];                                                               // (15) 0.01953
/*12 */     int ret;                                                                          // (21) 0.01172
/*16 */     snprintf(inst_name, sizeof(inst_name), "Parsed filter %d %s", index, filt_name);  // (1) 0.06445
/*20 */     filt = avfilter_get_by_name(filt_name);                                           // (11) 0.03906
/*24 */     if (!filt) {                                                                      // (20) 0.01758
/*26 */         av_log(log_ctx, AV_LOG_ERROR,                                                 // (9) 0.04102
/*28 */                "No such filter: '%s'\n", filt_name);                                  // (2) 0.06055
/*30 */         return AVERROR(EINVAL);                                                       // (13) 0.03125
/*32 */     }                                                                                 // (24) 0.007812
/*36 */     ret = avfilter_open(filt_ctx, filt, inst_name);                                   // (8) 0.04297
/*38 */     if (!*filt_ctx) {                                                                 // (14) 0.02344
/*40 */         av_log(log_ctx, AV_LOG_ERROR,                                                 // (10) 0.04102
/*42 */                "Error creating filter '%s'\n", filt_name);                            // (3) 0.05859
/*44 */         return ret;                                                                   // (18) 0.01953
/*46 */     }                                                                                 // (23) 0.007812
/*50 */     if ((ret = avfilter_graph_add_filter(ctx, *filt_ctx)) < 0) {                      // (4) 0.05469
/*52 */         avfilter_free(*filt_ctx);                                                     // (12) 0.0332
/*54 */         return ret;                                                                   // (17) 0.01953
/*56 */     }                                                                                 // (22) 0.007813
/*60 */     if (!strcmp(filt_name, "scale") && !strstr(args, "flags")) {                      // (5) 0.05273
/*62 */         snprintf(tmp_args, sizeof(tmp_args), "%s:%s",                                 // (6) 0.05078
/*64 */                  args, ctx->scale_sws_opts);                                          // 0.0
/*66 */         args = tmp_args;                                                              // 0.0
/*68 */     }                                                                                 // 0.0
/*72 */     if ((ret = avfilter_init_filter(*filt_ctx, args, NULL)) < 0) {                    // 0.0
/*74 */         av_log(log_ctx, AV_LOG_ERROR,                                                 // 0.0
/*76 */                "Error initializing filter '%s' with args '%s'\n", filt_name, args);   // 0.0
/*78 */         return ret;                                                                   // 0.0
/*80 */     }                                                                                 // 0.0
/*84 */     return 0;                                                                         // 0.0
/*86 */ }                                                                                     // 0.0
