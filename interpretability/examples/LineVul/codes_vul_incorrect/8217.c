// commit message FFmpeg@cbbb206734 (target=1, prob=0.31097016, correct=False): hwcontext_vdpau: implement av_hwdevice_get_hwframe_constraints()
/*0  */ static int vdpau_frames_init(AVHWFramesContext *ctx)                                       // (12) 0.03516
/*2  */ {                                                                                          // (22) 0.001953
/*4  */     VDPAUDeviceContext *device_priv = ctx->device_ctx->internal->priv;                     // (9) 0.05078
/*6  */     VDPAUFramesContext        *priv = ctx->internal->priv;                                 // (10) 0.05078
/*10 */     int i;                                                                                 // (18) 0.01172
/*14 */     switch (ctx->sw_format) {                                                              // (16) 0.02344
/*16 */     case AV_PIX_FMT_YUV420P: priv->chroma_type = VDP_CHROMA_TYPE_420; break;               // (0) 0.07227
/*18 */     case AV_PIX_FMT_YUV422P: priv->chroma_type = VDP_CHROMA_TYPE_422; break;               // (1) 0.07227
/*20 */     case AV_PIX_FMT_YUV444P: priv->chroma_type = VDP_CHROMA_TYPE_444; break;               // (2) 0.07227
/*22 */     default:                                                                               // (19) 0.009766
/*24 */         av_log(ctx, AV_LOG_ERROR, "Unsupported data layout: %s\n",                         // (8) 0.05859
/*26 */                av_get_pix_fmt_name(ctx->sw_format));                                       // (7) 0.0625
/*28 */         return AVERROR(ENOSYS);                                                            // (13) 0.03125
/*30 */     }                                                                                      // (20) 0.007812
/*34 */     for (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {                                 // (6) 0.06445
/*36 */         if (vdpau_pix_fmts[i].chroma_type == priv->chroma_type) {                          // (4) 0.06641
/*38 */             priv->chroma_idx  = i;                                                         // (11) 0.04297
/*40 */             priv->pix_fmts    = device_priv->pix_fmts[i];                                  // (5) 0.06641
/*42 */             priv->nb_pix_fmts = device_priv->nb_pix_fmts[i];                               // (3) 0.06836
/*44 */             break;                                                                         // (15) 0.02539
/*46 */         }                                                                                  // (17) 0.01562
/*48 */     }                                                                                      // (21) 0.007812
/*50 */     if (!priv->pix_fmts) {                                                                 // (14) 0.02734
/*52 */         av_log(ctx, AV_LOG_ERROR, "Unsupported chroma type: %d\n", priv->chroma_type);     // 0.0
/*54 */         return AVERROR(ENOSYS);                                                            // 0.0
/*56 */     }                                                                                      // 0.0
/*60 */     if (!ctx->pool) {                                                                      // 0.0
/*62 */         ctx->internal->pool_internal = av_buffer_pool_init2(sizeof(VdpVideoSurface), ctx,  // 0.0
/*64 */                                                             vdpau_pool_alloc, NULL);       // 0.0
/*66 */         if (!ctx->internal->pool_internal)                                                 // 0.0
/*68 */             return AVERROR(ENOMEM);                                                        // 0.0
/*70 */     }                                                                                      // 0.0
/*74 */     priv->get_data = device_priv->get_data;                                                // 0.0
/*76 */     priv->put_data = device_priv->put_data;                                                // 0.0
/*80 */     return 0;                                                                              // 0.0
/*82 */ }                                                                                          // 0.0
