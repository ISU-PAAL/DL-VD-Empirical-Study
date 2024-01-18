// commit message FFmpeg@dd5d617956 (target=0, prob=0.39747787, correct=True): avfilter/vf_idet: Fixing idet for single-frame inputs.
/*0  */ static int request_frame(AVFilterLink *link)             // (13) 0.03561
/*2  */ {                                                        // (19) 0.002967
/*4  */     AVFilterContext *ctx = link->src;                    // (12) 0.03858
/*6  */     IDETContext *idet = ctx->priv;                       // (8) 0.04451
/*10 */     do {                                                 // (18) 0.01484
/*12 */         int ret;                                         // (15) 0.02967
/*16 */         if (idet->eof)                                   // (9) 0.04451
/*18 */             return AVERROR_EOF;                          // (5) 0.05638
/*22 */         ret = ff_request_frame(link->src->inputs[0]);    // (2) 0.07122
/*26 */         if (ret == AVERROR_EOF && idet->cur) {           // (3) 0.07122
/*28 */             AVFrame *next = av_frame_clone(idet->next);  // (0) 0.08012
/*32 */             if (!next)                                   // (10) 0.04451
/*34 */                 return AVERROR(ENOMEM);                  // (4) 0.07122
/*38 */             filter_frame(link->src->inputs[0], next);    // (1) 0.07715
/*40 */             idet->eof = 1;                               // (6) 0.05638
/*42 */         } else if (ret < 0) {                            // (7) 0.04748
/*44 */             return ret;                                  // (11) 0.04154
/*46 */         }                                                // (16) 0.02374
/*48 */     } while (!idet->cur);                                // (14) 0.03264
/*52 */     return 0;                                            // (17) 0.0178
/*54 */ }                                                        // (20) 0.002967
