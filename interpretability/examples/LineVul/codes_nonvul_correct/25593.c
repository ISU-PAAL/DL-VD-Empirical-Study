// commit message FFmpeg@8be23d424f (target=0, prob=0.43414512, correct=True): avcodec/roqvideo: use JPEG color range
/*0  */ static av_cold int roq_decode_init(AVCodecContext *avctx)  // (2) 0.06269
/*2  */ {                                                          // (19) 0.002985
/*4  */     RoqContext *s = avctx->priv_data;                      // (10) 0.04776
/*8  */     s->avctx = avctx;                                      // (15) 0.03284
/*12 */     if (avctx->width % 16 || avctx->height % 16) {         // (3) 0.0597
/*14 */         av_log(avctx, AV_LOG_ERROR,                        // (4) 0.0597
/*16 */                "Dimensions must be a multiple of 16\n");   // (0) 0.07761
/*18 */         return AVERROR_PATCHWELCOME;                       // (5) 0.05672
/*20 */     }                                                      // (17) 0.01194
/*24 */     s->width = avctx->width;                               // (13) 0.03582
/*26 */     s->height = avctx->height;                             // (14) 0.03582
/*30 */     s->last_frame    = av_frame_alloc();                   // (9) 0.05373
/*32 */     s->current_frame = av_frame_alloc();                   // (12) 0.04478
/*34 */     if (!s->current_frame || !s->last_frame) {             // (6) 0.05672
/*36 */         av_frame_free(&s->current_frame);                  // (7) 0.05672
/*38 */         av_frame_free(&s->last_frame);                     // (8) 0.05672
/*40 */         return AVERROR(ENOMEM);                            // (11) 0.04776
/*42 */     }                                                      // (18) 0.01194
/*46 */     avctx->pix_fmt = AV_PIX_FMT_YUV444P;                   // (1) 0.07463
/*50 */     return 0;                                              // (16) 0.01791
/*52 */ }                                                          // (20) 0.002985
