// commit message FFmpeg@ecc92ee717 (target=1, prob=0.41740984, correct=False): lavc/libopenjpegenc: move opj_create_compress, opj_cio_open and opj_set_event_mgr to libopenjpeg_encode_frame
/*0   */ static av_cold int libopenjpeg_encode_init(AVCodecContext *avctx)               // (6) 0.04492
/*2   */ {                                                                               // (24) 0.001953
/*4   */     LibOpenJPEGContext *ctx = avctx->priv_data;                                 // (15) 0.03515
/*6   */     int err = AVERROR(ENOMEM);                                                  // (19) 0.0274
/*10  */     opj_set_default_encoder_parameters(&ctx->enc_params);                       // (10) 0.04296
/*14  */     ctx->enc_params.cp_rsiz = ctx->profile;                                     // (13) 0.03906
/*16  */     ctx->enc_params.mode = !!avctx->global_quality;                             // (12) 0.03906
/*18  */     ctx->enc_params.cp_cinema = ctx->cinema_mode;                               // (3) 0.04882
/*20  */     ctx->enc_params.prog_order = ctx->prog_order;                               // (7) 0.04492
/*22  */     ctx->enc_params.numresolution = ctx->numresolution;                         // (14) 0.0371
/*24  */     ctx->enc_params.cp_disto_alloc = ctx->disto_alloc;                          // (4) 0.04882
/*26  */     ctx->enc_params.cp_fixed_alloc = ctx->fixed_alloc;                          // (9) 0.04492
/*28  */     ctx->enc_params.cp_fixed_quality = ctx->fixed_quality;                      // (8) 0.04492
/*30  */     ctx->enc_params.tcp_numlayers = ctx->numlayers;                             // (5) 0.04687
/*32  */     ctx->enc_params.tcp_rates[0] = FFMAX(avctx->compression_level, 0) * 2;      // (0) 0.0664
/*36  */     if (ctx->cinema_mode > 0) {                                                 // (18) 0.03125
/*38  */         cinema_parameters(&ctx->enc_params);                                    // (16) 0.03515
/*40  */     }                                                                           // (23) 0.007812
/*44  */     ctx->compress = opj_create_compress(ctx->format);                           // (11) 0.04101
/*46  */     if (!ctx->compress) {                                                       // (20) 0.02148
/*48  */         av_log(avctx, AV_LOG_ERROR, "Error creating the compressor\n");         // (1) 0.05468
/*50  */         return AVERROR(ENOMEM);                                                 // (17) 0.03129
/*52  */     }                                                                           // (22) 0.007812
/*56  */     ctx->image = mj2_create_image(avctx, &ctx->enc_params);                     // (2) 0.05078
/*58  */     if (!ctx->image) {                                                          // (21) 0.01953
/*60  */         av_log(avctx, AV_LOG_ERROR, "Error creating the mj2 image\n");          // 0.0
/*62  */         err = AVERROR(EINVAL);                                                  // 0.0
/*64  */         goto fail;                                                              // 0.0
/*66  */     }                                                                           // 0.0
/*70  */     avctx->coded_frame = av_frame_alloc();                                      // 0.0
/*72  */     if (!avctx->coded_frame) {                                                  // 0.0
/*74  */         av_log(avctx, AV_LOG_ERROR, "Error allocating coded frame\n");          // 0.0
/*76  */         goto fail;                                                              // 0.0
/*78  */     }                                                                           // 0.0
/*82  */     memset(&ctx->event_mgr, 0, sizeof(opj_event_mgr_t));                        // 0.0
/*84  */     ctx->event_mgr.info_handler    = info_callback;                             // 0.0
/*86  */     ctx->event_mgr.error_handler = error_callback;                              // 0.0
/*88  */     ctx->event_mgr.warning_handler = warning_callback;                          // 0.0
/*90  */     opj_set_event_mgr((opj_common_ptr) ctx->compress, &ctx->event_mgr, avctx);  // 0.0
/*94  */     return 0;                                                                   // 0.0
/*98  */ fail:                                                                           // 0.0
/*100 */     opj_destroy_compress(ctx->compress);                                        // 0.0
/*102 */     ctx->compress = NULL;                                                       // 0.0
/*104 */     opj_image_destroy(ctx->image);                                              // 0.0
/*106 */     ctx->image = NULL;                                                          // 0.0
/*108 */     av_freep(&avctx->coded_frame);                                              // 0.0
/*110 */     return err;                                                                 // 0.0
/*112 */ }                                                                               // 0.0
