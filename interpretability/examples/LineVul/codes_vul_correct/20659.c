// commit message FFmpeg@8728360b56 (target=1, prob=0.6254434, correct=True): avcodec/mationpixels: check for malloc failures
/*0  */ static av_cold int mp_decode_init(AVCodecContext *avctx)              // (6) 0.05525
/*2  */ {                                                                     // (18) 0.002762
/*4  */     MotionPixelsContext *mp = avctx->priv_data;                       // (11) 0.04696
/*6  */     int w4 = (avctx->width  + 3) & ~3;                                // (7) 0.05525
/*8  */     int h4 = (avctx->height + 3) & ~3;                                // (9) 0.05249
/*12 */     if(avctx->extradata_size < 2){                                    // (13) 0.0442
/*14 */         av_log(avctx, AV_LOG_ERROR, "extradata too small\n");         // (0) 0.08011
/*16 */         return AVERROR_INVALIDDATA;                                   // (12) 0.04696
/*18 */     }                                                                 // (17) 0.01105
/*22 */     motionpixels_tableinit();                                         // (15) 0.02762
/*24 */     mp->avctx = avctx;                                                // (14) 0.03039
/*26 */     ff_dsputil_init(&mp->dsp, avctx);                                 // (8) 0.05249
/*28 */     mp->changes_map = av_mallocz(avctx->width * h4);                  // (5) 0.06354
/*30 */     mp->offset_bits_len = av_log2(avctx->width * avctx->height) + 1;  // (1) 0.08011
/*32 */     mp->vpt = av_mallocz(avctx->height * sizeof(YuvPixel));           // (3) 0.06906
/*34 */     mp->hpt = av_mallocz(h4 * w4 / 16 * sizeof(YuvPixel));            // (2) 0.07735
/*38 */     avctx->pix_fmt = AV_PIX_FMT_RGB555;                               // (4) 0.06354
/*40 */     avcodec_get_frame_defaults(&mp->frame);                           // (10) 0.04972
/*42 */     return 0;                                                         // (16) 0.01657
/*44 */ }                                                                     // (19) 0.002762
