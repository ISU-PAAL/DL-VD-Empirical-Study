// commit message FFmpeg@cd1047f391 (target=0, prob=0.59394276, correct=False): qsvdec: Pass the correct profile to libmfx
/*0   */ static int qsv_decode_init(AVCodecContext *avctx, QSVContext *q)                            // (9) 0.04883
/*2   */ {                                                                                           // (24) 0.001953
/*4   */     const AVPixFmtDescriptor *desc;                                                         // (13) 0.0293
/*6   */     mfxSession session = NULL;                                                              // (19) 0.01953
/*8   */     int iopattern = 0;                                                                      // (18) 0.02148
/*10  */     mfxVideoParam param = { { 0 } };                                                        // (15) 0.02734
/*12  */     int frame_width  = avctx->coded_width;                                                  // (12) 0.03125
/*14  */     int frame_height = avctx->coded_height;                                                 // (14) 0.0293
/*16  */     int ret;                                                                                // (21) 0.01172
/*20  */     desc = av_pix_fmt_desc_get(avctx->sw_pix_fmt);                                          // (4) 0.05469
/*22  */     if (!desc)                                                                              // (20) 0.01367
/*24  */         return AVERROR_BUG;                                                                 // (17) 0.02734
/*28  */     if (!q->async_fifo) {                                                                   // (16) 0.02734
/*30  */         q->async_fifo = av_fifo_alloc((1 + q->async_depth) *                                // (2) 0.0625
/*32  */                                       (sizeof(mfxSyncPoint*) + sizeof(QSVFrame*)));         // (0) 0.1094
/*34  */         if (!q->async_fifo)                                                                 // (11) 0.0332
/*36  */             return AVERROR(ENOMEM);                                                         // (10) 0.03906
/*38  */     }                                                                                       // (23) 0.007812
/*42  */     if (avctx->pix_fmt == AV_PIX_FMT_QSV && avctx->hwaccel_context) {                       // (1) 0.07031
/*44  */         AVQSVContext *user_ctx = avctx->hwaccel_context;                                    // (6) 0.05078
/*46  */         session           = user_ctx->session;                                              // (8) 0.04883
/*48  */         iopattern         = user_ctx->iopattern;                                            // (3) 0.05469
/*50  */         q->ext_buffers    = user_ctx->ext_buffers;                                          // (7) 0.05078
/*52  */         q->nb_ext_buffers = user_ctx->nb_ext_buffers;                                       // (5) 0.05273
/*54  */     }                                                                                       // (22) 0.007812
/*58  */     if (avctx->hw_frames_ctx) {                                                             // 0.0
/*60  */         AVHWFramesContext    *frames_ctx = (AVHWFramesContext*)avctx->hw_frames_ctx->data;  // 0.0
/*62  */         AVQSVFramesContext *frames_hwctx = frames_ctx->hwctx;                               // 0.0
/*66  */         if (!iopattern) {                                                                   // 0.0
/*68  */             if (frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME)                        // 0.0
/*70  */                 iopattern = MFX_IOPATTERN_OUT_OPAQUE_MEMORY;                                // 0.0
/*72  */             else if (frames_hwctx->frame_type & MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET)    // 0.0
/*74  */                 iopattern = MFX_IOPATTERN_OUT_VIDEO_MEMORY;                                 // 0.0
/*76  */         }                                                                                   // 0.0
/*80  */         frame_width  = frames_hwctx->surfaces[0].Info.Width;                                // 0.0
/*82  */         frame_height = frames_hwctx->surfaces[0].Info.Height;                               // 0.0
/*84  */     }                                                                                       // 0.0
/*88  */     if (!iopattern)                                                                         // 0.0
/*90  */         iopattern = MFX_IOPATTERN_OUT_SYSTEM_MEMORY;                                        // 0.0
/*92  */     q->iopattern = iopattern;                                                               // 0.0
/*96  */     ret = qsv_init_session(avctx, q, session, avctx->hw_frames_ctx);                        // 0.0
/*98  */     if (ret < 0) {                                                                          // 0.0
/*100 */         av_log(avctx, AV_LOG_ERROR, "Error initializing an MFX session\n");                 // 0.0
/*102 */         return ret;                                                                         // 0.0
/*104 */     }                                                                                       // 0.0
/*108 */     ret = ff_qsv_codec_id_to_mfx(avctx->codec_id);                                          // 0.0
/*110 */     if (ret < 0)                                                                            // 0.0
/*112 */         return ret;                                                                         // 0.0
/*116 */     param.mfx.CodecId      = ret;                                                           // 0.0
/*118 */     param.mfx.CodecProfile = avctx->profile;                                                // 0.0
/*120 */     param.mfx.CodecLevel   = avctx->level;                                                  // 0.0
/*124 */     param.mfx.FrameInfo.BitDepthLuma   = desc->comp[0].depth;                               // 0.0
/*126 */     param.mfx.FrameInfo.BitDepthChroma = desc->comp[0].depth;                               // 0.0
/*128 */     param.mfx.FrameInfo.Shift          = desc->comp[0].depth > 8;                           // 0.0
/*130 */     param.mfx.FrameInfo.FourCC         = q->fourcc;                                         // 0.0
/*132 */     param.mfx.FrameInfo.Width          = frame_width;                                       // 0.0
/*134 */     param.mfx.FrameInfo.Height         = frame_height;                                      // 0.0
/*136 */     param.mfx.FrameInfo.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;                           // 0.0
/*140 */     param.IOPattern   = q->iopattern;                                                       // 0.0
/*142 */     param.AsyncDepth  = q->async_depth;                                                     // 0.0
/*144 */     param.ExtParam    = q->ext_buffers;                                                     // 0.0
/*146 */     param.NumExtParam = q->nb_ext_buffers;                                                  // 0.0
/*150 */     ret = MFXVideoDECODE_Init(q->session, &param);                                          // 0.0
/*152 */     if (ret < 0)                                                                            // 0.0
/*154 */         return ff_qsv_print_error(avctx, ret,                                               // 0.0
/*156 */                                   "Error initializing the MFX video decoder");              // 0.0
/*160 */     q->frame_info = param.mfx.FrameInfo;                                                    // 0.0
/*164 */     return 0;                                                                               // 0.0
/*166 */ }                                                                                           // 0.0
