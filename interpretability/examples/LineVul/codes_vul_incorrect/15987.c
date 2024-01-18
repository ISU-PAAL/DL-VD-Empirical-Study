// commit message FFmpeg@88ddcfa37f (target=1, prob=0.45059115, correct=False): avcodec/tdsc: use ff_codec_open2_recursive()
/*0  */ static av_cold int tdsc_init(AVCodecContext *avctx)                            // (9) 0.03516
/*2  */ {                                                                              // (29) 0.001953
/*4  */     TDSCContext *ctx = avctx->priv_data;                                       // (10) 0.0332
/*6  */     const AVCodec *codec;                                                      // (22) 0.02148
/*8  */     int ret;                                                                   // (27) 0.01172
/*12 */     avctx->pix_fmt = AV_PIX_FMT_BGR24;                                         // (3) 0.04687
/*16 */     /* These needs to be set to estimate buffer and frame size */              // (15) 0.03125
/*18 */     if (!(avctx->width && avctx->height)) {                                    // (11) 0.0332
/*20 */         av_log(avctx, AV_LOG_ERROR, "Video size not set.\n");                  // (0) 0.05664
/*22 */         return AVERROR_INVALIDDATA;                                            // (13) 0.0332
/*24 */     }                                                                          // (28) 0.007812
/*28 */     /* This value should be large enough for a RAW-only frame plus headers */  // (7) 0.03711
/*30 */     ctx->deflatelen = avctx->width * avctx->height * (3 + 1);                  // (2) 0.04883
/*32 */     ret = av_reallocp(&ctx->deflatebuffer, ctx->deflatelen);                   // (4) 0.04687
/*34 */     if (ret < 0)                                                               // (25) 0.01758
/*36 */         return ret;                                                            // (24) 0.01953
/*40 */     /* Allocate reference and JPEG frame */                                    // (23) 0.02148
/*42 */     ctx->refframe = av_frame_alloc();                                          // (17) 0.03125
/*44 */     ctx->jpgframe = av_frame_alloc();                                          // (18) 0.0293
/*46 */     if (!ctx->refframe || !ctx->jpgframe)                                      // (12) 0.0332
/*48 */         return AVERROR(ENOMEM);                                                // (14) 0.03125
/*52 */     /* Prepare everything needed for JPEG decoding */                          // (21) 0.02148
/*54 */     codec = avcodec_find_decoder(AV_CODEC_ID_MJPEG);                           // (1) 0.05078
/*56 */     if (!codec)                                                                // (26) 0.01562
/*58 */         return AVERROR_BUG;                                                    // (19) 0.02734
/*60 */     ctx->jpeg_avctx = avcodec_alloc_context3(codec);                           // (5) 0.04687
/*62 */     if (!ctx->jpeg_avctx)                                                      // (20) 0.02539
/*64 */         return AVERROR(ENOMEM);                                                // (16) 0.03125
/*66 */     ctx->jpeg_avctx->flags = avctx->flags;                                     // (8) 0.03711
/*68 */     ctx->jpeg_avctx->flags2 = avctx->flags2;                                   // (6) 0.04102
/*70 */     ctx->jpeg_avctx->dct_algo = avctx->dct_algo;                               // 0.0
/*72 */     ctx->jpeg_avctx->idct_algo = avctx->idct_algo;;                            // 0.0
/*74 */     ret = avcodec_open2(ctx->jpeg_avctx, codec, NULL);                         // 0.0
/*76 */     if (ret < 0)                                                               // 0.0
/*78 */         return ret;                                                            // 0.0
/*82 */     /* Set the output pixel format on the reference frame */                   // 0.0
/*84 */     ctx->refframe->format = avctx->pix_fmt;                                    // 0.0
/*88 */     return 0;                                                                  // 0.0
/*90 */ }                                                                              // 0.0
