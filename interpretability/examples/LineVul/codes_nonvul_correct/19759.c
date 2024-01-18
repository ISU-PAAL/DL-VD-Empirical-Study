// commit message FFmpeg@c8241e730f (target=0, prob=0.14078493, correct=True): vaapi_encode: Refactor initialisation
/*0   */ static av_cold int vaapi_encode_h264_init_constant_bitrate(AVCodecContext *avctx)  // (2) 0.05859
/*2   */ {                                                                                  // (24) 0.001953
/*4   */     VAAPIEncodeContext      *ctx = avctx->priv_data;                               // (6) 0.04492
/*6   */     VAAPIEncodeH264Context *priv = ctx->priv_data;                                 // (12) 0.03906
/*8   */     int hrd_buffer_size;                                                           // (20) 0.02148
/*10  */     int hrd_initial_buffer_fullness;                                               // (18) 0.02734
/*14  */     if (avctx->bit_rate > INT32_MAX) {                                             // (14) 0.03516
/*16  */         av_log(avctx, AV_LOG_ERROR, "Target bitrate of 2^31 bps or "               // (1) 0.0625
/*18  */                "higher is not supported.\n");                                      // (5) 0.04492
/*20  */         return AVERROR(EINVAL);                                                    // (16) 0.03125
/*22  */     }                                                                              // (21) 0.007813
/*26  */     if (avctx->rc_buffer_size)                                                     // (19) 0.02734
/*28  */         hrd_buffer_size = avctx->rc_buffer_size;                                   // (7) 0.04492
/*30  */     else                                                                           // (22) 0.007812
/*32  */         hrd_buffer_size = avctx->bit_rate;                                         // (10) 0.04102
/*34  */     if (avctx->rc_initial_buffer_occupancy)                                        // (15) 0.0332
/*36  */         hrd_initial_buffer_fullness = avctx->rc_initial_buffer_occupancy;          // (3) 0.05664
/*38  */     else                                                                           // (23) 0.007812
/*40  */         hrd_initial_buffer_fullness = hrd_buffer_size * 3 / 4;                     // (4) 0.05469
/*44  */     priv->rc_params.misc.type = VAEncMiscParameterTypeRateControl;                 // (9) 0.04297
/*46  */     priv->rc_params.rc = (VAEncMiscParameterRateControl) {                         // (11) 0.04102
/*48  */         .bits_per_second   = avctx->bit_rate,                                      // (8) 0.04492
/*50  */         .target_percentage = 66,                                                   // (17) 0.0293
/*52  */         .window_size       = 1000,                                                 // (13) 0.03906
/*54  */         .initial_qp        = (avctx->qmax >= 0 ? avctx->qmax : 40),                // (0) 0.07227
/*56  */         .min_qp            = (avctx->qmin >= 0 ? avctx->qmin : 18),                // 0.0
/*58  */         .basic_unit_size   = 0,                                                    // 0.0
/*60  */     };                                                                             // 0.0
/*62  */     ctx->global_params[ctx->nb_global_params] =                                    // 0.0
/*64  */         &priv->rc_params.misc;                                                     // 0.0
/*66  */     ctx->global_params_size[ctx->nb_global_params++] =                             // 0.0
/*68  */         sizeof(priv->rc_params);                                                   // 0.0
/*72  */     priv->hrd_params.misc.type = VAEncMiscParameterTypeHRD;                        // 0.0
/*74  */     priv->hrd_params.hrd = (VAEncMiscParameterHRD) {                               // 0.0
/*76  */         .initial_buffer_fullness = hrd_initial_buffer_fullness,                    // 0.0
/*78  */         .buffer_size             = hrd_buffer_size,                                // 0.0
/*80  */     };                                                                             // 0.0
/*82  */     ctx->global_params[ctx->nb_global_params] =                                    // 0.0
/*84  */         &priv->hrd_params.misc;                                                    // 0.0
/*86  */     ctx->global_params_size[ctx->nb_global_params++] =                             // 0.0
/*88  */         sizeof(priv->hrd_params);                                                  // 0.0
/*92  */     // These still need to be  set for pic_init_qp/slice_qp_delta.                 // 0.0
/*94  */     priv->fixed_qp_idr = 26;                                                       // 0.0
/*96  */     priv->fixed_qp_p   = 26;                                                       // 0.0
/*98  */     priv->fixed_qp_b   = 26;                                                       // 0.0
/*102 */     av_log(avctx, AV_LOG_DEBUG, "Using constant-bitrate = %"PRId64" bps.\n",       // 0.0
/*104 */            avctx->bit_rate);                                                       // 0.0
/*106 */     return 0;                                                                      // 0.0
/*108 */ }                                                                                  // 0.0
