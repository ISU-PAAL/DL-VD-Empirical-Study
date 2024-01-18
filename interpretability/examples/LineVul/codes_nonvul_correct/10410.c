// commit message FFmpeg@6d24231e50 (target=0, prob=0.017099379, correct=True): give the user a chance to override codec_tag
/*0  */ static int raw_init_encoder(AVCodecContext *avctx)     // (3) 0.1441
/*2  */ {                                                      // (6) 0.008475
/*4  */     avctx->coded_frame = (AVFrame *)avctx->priv_data;  // (1) 0.178
/*6  */     avctx->coded_frame->pict_type = FF_I_TYPE;         // (2) 0.1695
/*8  */     avctx->coded_frame->key_frame = 1;                 // (4) 0.1356
/*10 */     avctx->codec_tag = findFourCC(avctx->pix_fmt);     // (0) 0.2034
/*12 */     return 0;                                          // (5) 0.05085
/*14 */ }                                                      // (7) 0.008475
