// commit message FFmpeg@2d66fc543b (target=1, prob=0.19721815, correct=False): lavfi/gradfun: fix rounding in MMX code.
/*0  */ static av_cold int init(AVFilterContext *ctx, const char *args)                     // (7) 0.06102
/*2  */ {                                                                                   // (15) 0.00339
/*4  */     GradFunContext *gf = ctx->priv;                                                 // (9) 0.05085
/*6  */     float thresh = 1.2;                                                             // (10) 0.03729
/*8  */     int radius = 16;                                                                // (12) 0.02712
/*12 */     if (args)                                                                       // (13) 0.02373
/*14 */         sscanf(args, "%f:%d", &thresh, &radius);                                    // (1) 0.08814
/*18 */     thresh = av_clipf(thresh, 0.51, 255);                                           // (5) 0.0678
/*20 */     gf->thresh = (1 << 15) / thresh;                                                // (8) 0.06102
/*22 */     gf->radius = av_clip((radius + 1) & ~1, 4, 32);                                 // (2) 0.08136
/*26 */     gf->blur_line = ff_gradfun_blur_line_c;                                         // (3) 0.07797
/*28 */     gf->filter_line = ff_gradfun_filter_line_c;                                     // (4) 0.07119
/*32 */     if (ARCH_X86)                                                                   // (11) 0.0339
/*34 */         ff_gradfun_init_x86(gf);                                                    // (6) 0.0678
/*38 */     av_log(ctx, AV_LOG_VERBOSE, "threshold:%.2f radius:%d\n", thresh, gf->radius);  // (0) 0.1322
/*42 */     return 0;                                                                       // (14) 0.02034
/*44 */ }                                                                                   // (16) 0.00339
