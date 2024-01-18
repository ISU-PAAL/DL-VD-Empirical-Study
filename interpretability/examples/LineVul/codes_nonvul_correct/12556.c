// commit message FFmpeg@7546964f96 (target=0, prob=0.37638906, correct=True): nvdec: add frames_params support
/*0   */ int ff_nvdec_decode_init(AVCodecContext *avctx, unsigned int dpb_size)                       // (5) 0.05085
/*2   */ {                                                                                            // (26) 0.001954
/*4   */     NVDECContext *ctx = avctx->internal->hwaccel_priv_data;                                  // (6) 0.04491
/*8   */     NVDECFramePool      *pool;                                                               // (16) 0.0313
/*10  */     AVHWFramesContext   *frames_ctx;                                                         // (19) 0.02929
/*12  */     const AVPixFmtDescriptor *sw_desc;                                                       // (12) 0.03319
/*16  */     CUVIDDECODECREATEINFO params = { 0 };                                                    // (15) 0.03134
/*20  */     int cuvid_codec_type, cuvid_chroma_format;                                               // (7) 0.04295
/*22  */     int ret = 0;                                                                             // (23) 0.01562
/*26  */     sw_desc = av_pix_fmt_desc_get(avctx->sw_pix_fmt);                                        // (0) 0.05856
/*28  */     if (!sw_desc)                                                                            // (22) 0.01757
/*30  */         return AVERROR_BUG;                                                                  // (20) 0.02733
/*34  */     cuvid_codec_type = map_avcodec_id(avctx->codec_id);                                      // (3) 0.05466
/*36  */     if (cuvid_codec_type < 0) {                                                              // (13) 0.03318
/*38  */         av_log(avctx, AV_LOG_ERROR, "Unsupported codec ID\n");                               // (4) 0.05466
/*40  */         return AVERROR_BUG;                                                                  // (21) 0.02733
/*42  */     }                                                                                        // (24) 0.007809
/*46  */     cuvid_chroma_format = map_chroma_format(avctx->sw_pix_fmt);                              // (1) 0.05856
/*48  */     if (cuvid_chroma_format < 0) {                                                           // (14) 0.03318
/*50  */         av_log(avctx, AV_LOG_ERROR, "Unsupported chroma format\n");                          // (2) 0.05661
/*52  */         return AVERROR(ENOSYS);                                                              // (17) 0.03123
/*54  */     }                                                                                        // (25) 0.007808
/*58  */     if (avctx->thread_type & FF_THREAD_FRAME)                                                // (8) 0.03905
/*60  */         dpb_size += avctx->thread_count;                                                     // (10) 0.0371
/*64  */     if (!avctx->hw_frames_ctx) {                                                             // (18) 0.0293
/*66  */         AVHWFramesContext *frames_ctx;                                                       // (11) 0.03319
/*70  */         if (!avctx->hw_device_ctx) {                                                         // (9) 0.03727
/*72  */             av_log(avctx, AV_LOG_ERROR, "A hardware device or frames context "               // 0.0
/*74  */                    "is required for CUVID decoding.\n");                                     // 0.0
/*76  */             return AVERROR(EINVAL);                                                          // 0.0
/*78  */         }                                                                                    // 0.0
/*82  */         avctx->hw_frames_ctx = av_hwframe_ctx_alloc(avctx->hw_device_ctx);                   // 0.0
/*84  */         if (!avctx->hw_frames_ctx)                                                           // 0.0
/*86  */             return AVERROR(ENOMEM);                                                          // 0.0
/*88  */         frames_ctx = (AVHWFramesContext*)avctx->hw_frames_ctx->data;                         // 0.0
/*92  */         frames_ctx->format            = AV_PIX_FMT_CUDA;                                     // 0.0
/*94  */         frames_ctx->width             = avctx->coded_width;                                  // 0.0
/*96  */         frames_ctx->height            = avctx->coded_height;                                 // 0.0
/*98  */         frames_ctx->sw_format         = AV_PIX_FMT_NV12;                                     // 0.0
/*100 */         frames_ctx->sw_format         = sw_desc->comp[0].depth > 8 ?                         // 0.0
/*102 */                                         AV_PIX_FMT_P010 : AV_PIX_FMT_NV12;                   // 0.0
/*104 */         frames_ctx->initial_pool_size = dpb_size;                                            // 0.0
/*108 */         ret = av_hwframe_ctx_init(avctx->hw_frames_ctx);                                     // 0.0
/*110 */         if (ret < 0) {                                                                       // 0.0
/*112 */             av_log(avctx, AV_LOG_ERROR, "Error initializing internal frames context\n");     // 0.0
/*114 */             return ret;                                                                      // 0.0
/*116 */         }                                                                                    // 0.0
/*118 */     }                                                                                        // 0.0
/*120 */     frames_ctx = (AVHWFramesContext*)avctx->hw_frames_ctx->data;                             // 0.0
/*124 */     params.ulWidth             = avctx->coded_width;                                         // 0.0
/*126 */     params.ulHeight            = avctx->coded_height;                                        // 0.0
/*128 */     params.ulTargetWidth       = avctx->coded_width;                                         // 0.0
/*130 */     params.ulTargetHeight      = avctx->coded_height;                                        // 0.0
/*132 */     params.bitDepthMinus8      = sw_desc->comp[0].depth - 8;                                 // 0.0
/*134 */     params.OutputFormat        = params.bitDepthMinus8 ?                                     // 0.0
/*136 */                                  cudaVideoSurfaceFormat_P016 : cudaVideoSurfaceFormat_NV12;  // 0.0
/*138 */     params.CodecType           = cuvid_codec_type;                                           // 0.0
/*140 */     params.ChromaFormat        = cuvid_chroma_format;                                        // 0.0
/*142 */     params.ulNumDecodeSurfaces = dpb_size;                                                   // 0.0
/*144 */     params.ulNumOutputSurfaces = 1;                                                          // 0.0
/*148 */     ret = nvdec_decoder_create(&ctx->decoder_ref, frames_ctx->device_ref, &params, avctx);   // 0.0
/*150 */     if (ret < 0)                                                                             // 0.0
/*152 */         return ret;                                                                          // 0.0
/*156 */     pool = av_mallocz(sizeof(*pool));                                                        // 0.0
/*158 */     if (!pool) {                                                                             // 0.0
/*160 */         ret = AVERROR(ENOMEM);                                                               // 0.0
/*162 */         goto fail;                                                                           // 0.0
/*164 */     }                                                                                        // 0.0
/*166 */     pool->dpb_size = dpb_size;                                                               // 0.0
/*170 */     ctx->decoder_pool = av_buffer_pool_init2(sizeof(int), pool,                              // 0.0
/*172 */                                              nvdec_decoder_frame_alloc, av_free);            // 0.0
/*174 */     if (!ctx->decoder_pool) {                                                                // 0.0
/*176 */         ret = AVERROR(ENOMEM);                                                               // 0.0
/*178 */         goto fail;                                                                           // 0.0
/*180 */     }                                                                                        // 0.0
/*184 */     return 0;                                                                                // 0.0
/*186 */ fail:                                                                                        // 0.0
/*188 */     ff_nvdec_decode_uninit(avctx);                                                           // 0.0
/*190 */     return ret;                                                                              // 0.0
/*192 */ }                                                                                            // 0.0
