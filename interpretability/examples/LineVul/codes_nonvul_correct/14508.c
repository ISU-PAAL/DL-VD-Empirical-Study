// commit message FFmpeg@6df1cfa7e4 (target=0, prob=0.054973073, correct=True): mace: check channel count, fixes FPE
/*0  */ static av_cold int mace_decode_init(AVCodecContext * avctx)  // (1) 0.1479
/*2  */ {                                                            // (8) 0.007042
/*4  */     MACEContext *ctx = avctx->priv_data;                     // (3) 0.1197
/*8  */     if (avctx->channels > 2)                                 // (5) 0.09155
/*10 */         return -1;                                           // (6) 0.07746
/*12 */     avctx->sample_fmt = AV_SAMPLE_FMT_S16;                   // (0) 0.1549
/*16 */     avcodec_get_frame_defaults(&ctx->frame);                 // (2) 0.1268
/*18 */     avctx->coded_frame = &ctx->frame;                        // (4) 0.1056
/*22 */     return 0;                                                // (7) 0.04225
/*24 */ }                                                            // (9) 0.007042
