// commit message FFmpeg@b8a2331a70 (target=1, prob=0.42286274, correct=False): ffv1: check for malloc failure.
/*0  */ av_cold int ffv1_common_init(AVCodecContext *avctx)  // (0) 0.08299
/*2  */ {                                                    // (16) 0.004149
/*4  */     FFV1Context *s = avctx->priv_data;               // (2) 0.07054
/*8  */     if (!avctx->width || !avctx->height)             // (6) 0.06639
/*10 */         return AVERROR_INVALIDDATA;                  // (5) 0.07054
/*14 */     s->avctx = avctx;                                // (12) 0.04564
/*16 */     s->flags = avctx->flags;                         // (10) 0.04979
/*20 */     s->picture.f = avcodec_alloc_frame();            // (4) 0.07054
/*22 */     s->last_picture.f = av_frame_alloc();            // (3) 0.07054
/*26 */     ff_dsputil_init(&s->dsp, avctx);                 // (1) 0.07884
/*30 */     s->width  = avctx->width;                        // (9) 0.05394
/*32 */     s->height = avctx->height;                       // (11) 0.04979
/*36 */     // defaults                                      // (14) 0.02075
/*38 */     s->num_h_slices = 1;                             // (7) 0.06224
/*40 */     s->num_v_slices = 1;                             // (8) 0.06224
/*44 */     return 0;                                        // (13) 0.0249
/*46 */ }                                                    // (15) 0.004149
