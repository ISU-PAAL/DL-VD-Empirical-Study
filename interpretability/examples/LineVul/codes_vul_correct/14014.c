// commit message FFmpeg@4d87001096 (target=1, prob=0.71153516, correct=True): vp8: fix crash due to skiped update_dimensions().
/*0  */ static int update_dimensions(VP8Context *s, int width, int height)                                    // (13) 0.03711
/*2  */ {                                                                                                     // (17) 0.001953
/*4  */     if (width  != s->avctx->width ||                                                                  // (15) 0.0293
/*6  */         height != s->avctx->height) {                                                                 // (14) 0.0332
/*8  */         if (av_image_check_size(width, height, 0, s->avctx))                                          // (7) 0.05469
/*10 */             return AVERROR_INVALIDDATA;                                                               // (12) 0.04102
/*14 */         vp8_decode_flush_impl(s->avctx, 1, 0, 1);                                                     // (6) 0.05664
/*18 */         avcodec_set_dimensions(s->avctx, width, height);                                              // (8) 0.04883
/*20 */     }                                                                                                 // (16) 0.007812
/*24 */     s->mb_width  = (s->avctx->coded_width +15) / 16;                                                  // (9) 0.04883
/*26 */     s->mb_height = (s->avctx->coded_height+15) / 16;                                                  // (10) 0.04687
/*30 */     s->macroblocks_base        = av_mallocz((s->mb_width+s->mb_height*2+1)*sizeof(*s->macroblocks));  // (0) 0.0957
/*32 */     s->filter_strength         = av_mallocz(s->mb_width*sizeof(*s->filter_strength));                 // (3) 0.07422
/*34 */     s->intra4x4_pred_mode_top  = av_mallocz(s->mb_width*4);                                           // (5) 0.0625
/*36 */     s->top_nnz                 = av_mallocz(s->mb_width*sizeof(*s->top_nnz));                         // (1) 0.09375
/*38 */     s->top_border              = av_mallocz((s->mb_width+1)*sizeof(*s->top_border));                  // (2) 0.08789
/*42 */     if (!s->macroblocks_base || !s->filter_strength || !s->intra4x4_pred_mode_top ||                  // (4) 0.06836
/*44 */         !s->top_nnz || !s->top_border)                                                                // (11) 0.04297
/*46 */         return AVERROR(ENOMEM);                                                                       // 0.0
/*50 */     s->macroblocks        = s->macroblocks_base + 1;                                                  // 0.0
/*54 */     return 0;                                                                                         // 0.0
/*56 */ }                                                                                                     // 0.0
