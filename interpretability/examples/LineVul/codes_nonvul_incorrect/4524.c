// commit message FFmpeg@b46a77f19d (target=0, prob=0.5312991, correct=False): lavc: external hardware frame pool initialization
/*0   */ int ff_vdpau_common_init(AVCodecContext *avctx, VdpDecoderProfile profile,                                                 // (5) 0.05078
/*2   */                          int level)                                                                                        // (3) 0.05273
/*4   */ {                                                                                                                          // (24) 0.001954
/*6   */     VDPAUHWContext *hwctx = avctx->hwaccel_context;                                                                        // (11) 0.04492
/*8   */     VDPAUContext *vdctx = avctx->internal->hwaccel_priv_data;                                                              // (9) 0.04883
/*10  */     VdpVideoSurfaceQueryCapabilities *surface_query_caps;                                                                  // (13) 0.03516
/*12  */     VdpDecoderQueryCapabilities *decoder_query_caps;                                                                       // (14) 0.03516
/*14  */     VdpDecoderCreate *create;                                                                                              // (16) 0.02148
/*16  */     void *func;                                                                                                            // (23) 0.01367
/*18  */     VdpStatus status;                                                                                                      // (22) 0.01562
/*20  */     VdpBool supported;                                                                                                     // (18) 0.01758
/*22  */     uint32_t max_level, max_mb, max_width, max_height;                                                                     // (12) 0.04492
/*24  */     VdpChromaType type;                                                                                                    // (17) 0.01953
/*26  */     uint32_t width;                                                                                                        // (21) 0.01758
/*28  */     uint32_t height;                                                                                                       // (20) 0.01758
/*32  */     vdctx->width            = UINT32_MAX;                                                                                  // (7) 0.05078
/*34  */     vdctx->height           = UINT32_MAX;                                                                                  // (10) 0.04883
/*38  */     if (av_vdpau_get_surface_parameters(avctx, &type, &width, &height))                                                    // (0) 0.05859
/*40  */         return AVERROR(ENOSYS);                                                                                            // (15) 0.03125
/*44  */     if (hwctx) {                                                                                                           // (19) 0.01758
/*46  */         hwctx->reset            = 0;                                                                                       // (6) 0.05078
/*50  */         if (hwctx->context.decoder != VDP_INVALID_HANDLE) {                                                                // (2) 0.05664
/*52  */             vdctx->decoder = hwctx->context.decoder;                                                                       // (4) 0.05273
/*54  */             vdctx->render  = hwctx->context.render;                                                                        // (8) 0.05078
/*56  */             vdctx->device  = VDP_INVALID_HANDLE;                                                                           // (1) 0.05664
/*58  */             return 0; /* Decoder created by user */                                                                        // 0.0
/*60  */         }                                                                                                                  // 0.0
/*64  */         vdctx->device           = hwctx->device;                                                                           // 0.0
/*66  */         vdctx->get_proc_address = hwctx->get_proc_address;                                                                 // 0.0
/*70  */         if (hwctx->flags & AV_HWACCEL_FLAG_IGNORE_LEVEL)                                                                   // 0.0
/*72  */             level = 0;                                                                                                     // 0.0
/*76  */         if (!(hwctx->flags & AV_HWACCEL_FLAG_ALLOW_HIGH_DEPTH) &&                                                          // 0.0
/*78  */             type != VDP_CHROMA_TYPE_420)                                                                                   // 0.0
/*80  */             return AVERROR(ENOSYS);                                                                                        // 0.0
/*82  */     } else {                                                                                                               // 0.0
/*84  */         AVHWFramesContext *frames_ctx = NULL;                                                                              // 0.0
/*86  */         AVVDPAUDeviceContext *dev_ctx;                                                                                     // 0.0
/*90  */         // We assume the hw_frames_ctx always survives until ff_vdpau_common_uninit                                        // 0.0
/*92  */         // is called. This holds true as the user is not allowed to touch                                                  // 0.0
/*94  */         // hw_device_ctx, or hw_frames_ctx after get_format (and ff_get_format                                             // 0.0
/*96  */         // itself also uninits before unreffing hw_frames_ctx).                                                            // 0.0
/*98  */         if (avctx->hw_frames_ctx) {                                                                                        // 0.0
/*100 */             frames_ctx = (AVHWFramesContext*)avctx->hw_frames_ctx->data;                                                   // 0.0
/*102 */         } else if (avctx->hw_device_ctx) {                                                                                 // 0.0
/*104 */             int ret;                                                                                                       // 0.0
/*108 */             avctx->hw_frames_ctx = av_hwframe_ctx_alloc(avctx->hw_device_ctx);                                             // 0.0
/*110 */             if (!avctx->hw_frames_ctx)                                                                                     // 0.0
/*112 */                 return AVERROR(ENOMEM);                                                                                    // 0.0
/*116 */             frames_ctx            = (AVHWFramesContext*)avctx->hw_frames_ctx->data;                                        // 0.0
/*118 */             frames_ctx->format    = AV_PIX_FMT_VDPAU;                                                                      // 0.0
/*120 */             frames_ctx->sw_format = avctx->sw_pix_fmt;                                                                     // 0.0
/*122 */             frames_ctx->width     = avctx->coded_width;                                                                    // 0.0
/*124 */             frames_ctx->height    = avctx->coded_height;                                                                   // 0.0
/*128 */             ret = av_hwframe_ctx_init(avctx->hw_frames_ctx);                                                               // 0.0
/*130 */             if (ret < 0) {                                                                                                 // 0.0
/*132 */                 av_buffer_unref(&avctx->hw_frames_ctx);                                                                    // 0.0
/*134 */                 return ret;                                                                                                // 0.0
/*136 */             }                                                                                                              // 0.0
/*138 */         }                                                                                                                  // 0.0
/*142 */         if (!frames_ctx) {                                                                                                 // 0.0
/*144 */             av_log(avctx, AV_LOG_ERROR, "A hardware frames context is "                                                    // 0.0
/*146 */                    "required for VDPAU decoding.\n");                                                                      // 0.0
/*148 */             return AVERROR(EINVAL);                                                                                        // 0.0
/*150 */         }                                                                                                                  // 0.0
/*154 */         dev_ctx = frames_ctx->device_ctx->hwctx;                                                                           // 0.0
/*158 */         vdctx->device           = dev_ctx->device;                                                                         // 0.0
/*160 */         vdctx->get_proc_address = dev_ctx->get_proc_address;                                                               // 0.0
/*164 */         if (avctx->hwaccel_flags & AV_HWACCEL_FLAG_IGNORE_LEVEL)                                                           // 0.0
/*166 */             level = 0;                                                                                                     // 0.0
/*168 */     }                                                                                                                      // 0.0
/*172 */     if (level < 0)                                                                                                         // 0.0
/*174 */         return AVERROR(ENOTSUP);                                                                                           // 0.0
/*178 */     status = vdctx->get_proc_address(vdctx->device,                                                                        // 0.0
/*180 */                                      VDP_FUNC_ID_VIDEO_SURFACE_QUERY_CAPABILITIES,                                         // 0.0
/*182 */                                      &func);                                                                               // 0.0
/*184 */     if (status != VDP_STATUS_OK)                                                                                           // 0.0
/*186 */         return vdpau_error(status);                                                                                        // 0.0
/*188 */     else                                                                                                                   // 0.0
/*190 */         surface_query_caps = func;                                                                                         // 0.0
/*194 */     status = surface_query_caps(vdctx->device, type, &supported,                                                           // 0.0
/*196 */                                 &max_width, &max_height);                                                                  // 0.0
/*198 */     if (status != VDP_STATUS_OK)                                                                                           // 0.0
/*200 */         return vdpau_error(status);                                                                                        // 0.0
/*202 */     if (supported != VDP_TRUE ||                                                                                           // 0.0
/*204 */         max_width < width || max_height < height)                                                                          // 0.0
/*206 */         return AVERROR(ENOTSUP);                                                                                           // 0.0
/*210 */     status = vdctx->get_proc_address(vdctx->device,                                                                        // 0.0
/*212 */                                      VDP_FUNC_ID_DECODER_QUERY_CAPABILITIES,                                               // 0.0
/*214 */                                      &func);                                                                               // 0.0
/*216 */     if (status != VDP_STATUS_OK)                                                                                           // 0.0
/*218 */         return vdpau_error(status);                                                                                        // 0.0
/*220 */     else                                                                                                                   // 0.0
/*222 */         decoder_query_caps = func;                                                                                         // 0.0
/*226 */     status = decoder_query_caps(vdctx->device, profile, &supported, &max_level,                                            // 0.0
/*228 */                                 &max_mb, &max_width, &max_height);                                                         // 0.0
/*230 */ #ifdef VDP_DECODER_PROFILE_H264_CONSTRAINED_BASELINE                                                                       // 0.0
/*232 */     if ((status != VDP_STATUS_OK || supported != VDP_TRUE) && profile == VDP_DECODER_PROFILE_H264_CONSTRAINED_BASELINE) {  // 0.0
/*234 */         profile = VDP_DECODER_PROFILE_H264_MAIN;                                                                           // 0.0
/*236 */         status = decoder_query_caps(vdctx->device, profile, &supported,                                                    // 0.0
/*238 */                                     &max_level, &max_mb,                                                                   // 0.0
/*240 */                                     &max_width, &max_height);                                                              // 0.0
/*242 */     }                                                                                                                      // 0.0
/*244 */ #endif                                                                                                                     // 0.0
/*246 */     if (status != VDP_STATUS_OK)                                                                                           // 0.0
/*248 */         return vdpau_error(status);                                                                                        // 0.0
/*252 */     if (supported != VDP_TRUE || max_level < level ||                                                                      // 0.0
/*254 */         max_width < width || max_height < height)                                                                          // 0.0
/*256 */         return AVERROR(ENOTSUP);                                                                                           // 0.0
/*260 */     status = vdctx->get_proc_address(vdctx->device, VDP_FUNC_ID_DECODER_CREATE,                                            // 0.0
/*262 */                                      &func);                                                                               // 0.0
/*264 */     if (status != VDP_STATUS_OK)                                                                                           // 0.0
/*266 */         return vdpau_error(status);                                                                                        // 0.0
/*268 */     else                                                                                                                   // 0.0
/*270 */         create = func;                                                                                                     // 0.0
/*274 */     status = vdctx->get_proc_address(vdctx->device, VDP_FUNC_ID_DECODER_RENDER,                                            // 0.0
/*276 */                                      &func);                                                                               // 0.0
/*278 */     if (status != VDP_STATUS_OK)                                                                                           // 0.0
/*280 */         return vdpau_error(status);                                                                                        // 0.0
/*282 */     else                                                                                                                   // 0.0
/*284 */         vdctx->render = func;                                                                                              // 0.0
/*288 */     status = create(vdctx->device, profile, width, height, avctx->refs,                                                    // 0.0
/*290 */                     &vdctx->decoder);                                                                                      // 0.0
/*292 */     if (status == VDP_STATUS_OK) {                                                                                         // 0.0
/*294 */         vdctx->width  = avctx->coded_width;                                                                                // 0.0
/*296 */         vdctx->height = avctx->coded_height;                                                                               // 0.0
/*298 */     }                                                                                                                      // 0.0
/*302 */     return vdpau_error(status);                                                                                            // 0.0
/*304 */ }                                                                                                                          // 0.0
