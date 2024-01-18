// commit message FFmpeg@fbd97184f8 (target=1, prob=0.38204068, correct=False): Add missing check in link_filter_inouts(), and fix possible (yet very unlikely) crash.
/*0  */ static int link_filter_inouts(AVFilterContext *filt_ctx,                                 // (12) 0.03516
/*2  */                               AVFilterInOut **curr_inputs,                               // (2) 0.07813
/*4  */                               AVFilterInOut **open_inputs, AVClass *log_ctx)             // (0) 0.08984
/*6  */ {                                                                                        // (21) 0.001953
/*8  */     int pad = filt_ctx->input_count, ret;                                                // (14) 0.0332
/*12 */     while (pad--) {                                                                      // (19) 0.01758
/*14 */         AVFilterInOut *p = *curr_inputs;                                                 // (7) 0.04102
/*16 */         if (!p) {                                                                        // (17) 0.02344
/*18 */             av_log(log_ctx, AV_LOG_ERROR,                                                // (5) 0.04883
/*20 */                    "Not enough inputs specified for the \"%s\" filter.\n",               // (3) 0.06641
/*22 */                    filt_ctx->filter->name);                                              // (4) 0.05273
/*24 */             return AVERROR(EINVAL);                                                      // (8) 0.03906
/*26 */         }                                                                                // (20) 0.01562
/*30 */         *curr_inputs = (*curr_inputs)->next;                                             // (6) 0.04688
/*34 */         if (p->filter) {                                                                 // (16) 0.02734
/*36 */             if ((ret = link_filter(p->filter, p->pad_idx, filt_ctx, pad, log_ctx)) < 0)  // (1) 0.08594
/*38 */                 return ret;                                                              // (13) 0.03516
/*40 */             av_free(p->name);                                                            // (11) 0.03711
/*42 */             av_free(p);                                                                  // (15) 0.0332
/*44 */         } else {                                                                         // (18) 0.01953
/*46 */             p->filter = filt_ctx;                                                        // (9) 0.03906
/*48 */             p->pad_idx = pad;                                                            // (10) 0.03906
/*50 */             insert_inout(open_inputs, p);                                                // 0.0
/*52 */         }                                                                                // 0.0
/*54 */     }                                                                                    // 0.0
/*58 */     if (*curr_inputs) {                                                                  // 0.0
/*60 */         av_log(log_ctx, AV_LOG_ERROR,                                                    // 0.0
/*62 */                "Too many inputs specified for the \"%s\" filter.\n",                     // 0.0
/*64 */                filt_ctx->filter->name);                                                  // 0.0
/*66 */         return AVERROR(EINVAL);                                                          // 0.0
/*68 */     }                                                                                    // 0.0
/*72 */     pad = filt_ctx->output_count;                                                        // 0.0
/*74 */     while (pad--) {                                                                      // 0.0
/*76 */         AVFilterInOut *currlinkn = av_mallocz(sizeof(AVFilterInOut));                    // 0.0
/*80 */         currlinkn->filter  = filt_ctx;                                                   // 0.0
/*82 */         currlinkn->pad_idx = pad;                                                        // 0.0
/*84 */         insert_inout(curr_inputs, currlinkn);                                            // 0.0
/*86 */     }                                                                                    // 0.0
/*90 */     return 0;                                                                            // 0.0
/*92 */ }                                                                                        // 0.0
