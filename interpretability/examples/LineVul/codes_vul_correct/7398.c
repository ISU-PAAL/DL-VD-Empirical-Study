// commit message FFmpeg@4029f05c8b (target=1, prob=0.5224667, correct=True): avcodec/cuvid: Always check for internal errors during parsing
/*0   */ static int cuvid_decode_frame(AVCodecContext *avctx, void *data, int *got_frame, AVPacket *avpkt)                    // (2) 0.07227
/*2   */ {                                                                                                                    // (22) 0.001954
/*4   */     CuvidContext *ctx = avctx->priv_data;                                                                            // (11) 0.03125
/*6   */     AVHWDeviceContext *device_ctx = (AVHWDeviceContext*)ctx->hwdevice->data;                                         // (6) 0.05273
/*8   */     AVCUDADeviceContext *device_hwctx = device_ctx->hwctx;                                                           // (8) 0.04492
/*10  */     CUcontext dummy, cuda_ctx = device_hwctx->cuda_ctx;                                                              // (9) 0.04297
/*12  */     AVFrame *frame = data;                                                                                           // (19) 0.01953
/*14  */     CUVIDSOURCEDATAPACKET cupkt;                                                                                     // (12) 0.03125
/*16  */     AVPacket filter_packet = { 0 };                                                                                  // (14) 0.02734
/*18  */     AVPacket filtered_packet = { 0 };                                                                                // (13) 0.02734
/*20  */     CUdeviceptr mapped_frame = 0;                                                                                    // (18) 0.02344
/*22  */     int ret = 0, eret = 0;                                                                                           // (17) 0.02539
/*26  */     if (ctx->bsf && avpkt->size) {                                                                                   // (10) 0.0332
/*28  */         if ((ret = av_packet_ref(&filter_packet, avpkt)) < 0) {                                                      // (5) 0.06055
/*30  */             av_log(avctx, AV_LOG_ERROR, "av_packet_ref failed\n");                                                   // (4) 0.06836
/*32  */             return ret;                                                                                              // (15) 0.02734
/*34  */         }                                                                                                            // (20) 0.01562
/*38  */         if ((ret = av_bsf_send_packet(ctx->bsf, &filter_packet)) < 0) {                                              // (3) 0.07031
/*40  */             av_log(avctx, AV_LOG_ERROR, "av_bsf_send_packet failed\n");                                              // (1) 0.07422
/*42  */             av_packet_unref(&filter_packet);                                                                         // (7) 0.04687
/*44  */             return ret;                                                                                              // (16) 0.02734
/*46  */         }                                                                                                            // (21) 0.01562
/*50  */         if ((ret = av_bsf_receive_packet(ctx->bsf, &filtered_packet)) < 0) {                                         // (0) 0.07422
/*52  */             av_log(avctx, AV_LOG_ERROR, "av_bsf_receive_packet failed\n");                                           // 0.0
/*54  */             return ret;                                                                                              // 0.0
/*56  */         }                                                                                                            // 0.0
/*60  */         avpkt = &filtered_packet;                                                                                    // 0.0
/*62  */     }                                                                                                                // 0.0
/*66  */     ret = CHECK_CU(cuCtxPushCurrent(cuda_ctx));                                                                      // 0.0
/*68  */     if (ret < 0) {                                                                                                   // 0.0
/*70  */         av_packet_unref(&filtered_packet);                                                                           // 0.0
/*72  */         return ret;                                                                                                  // 0.0
/*74  */     }                                                                                                                // 0.0
/*78  */     memset(&cupkt, 0, sizeof(cupkt));                                                                                // 0.0
/*82  */     if (avpkt->size) {                                                                                               // 0.0
/*84  */         cupkt.payload_size = avpkt->size;                                                                            // 0.0
/*86  */         cupkt.payload = avpkt->data;                                                                                 // 0.0
/*90  */         if (avpkt->pts != AV_NOPTS_VALUE) {                                                                          // 0.0
/*92  */             cupkt.flags = CUVID_PKT_TIMESTAMP;                                                                       // 0.0
/*94  */             if (avctx->pkt_timebase.num && avctx->pkt_timebase.den)                                                  // 0.0
/*96  */                 cupkt.timestamp = av_rescale_q(avpkt->pts, avctx->pkt_timebase, (AVRational){1, 10000000});          // 0.0
/*98  */             else                                                                                                     // 0.0
/*100 */                 cupkt.timestamp = avpkt->pts;                                                                        // 0.0
/*102 */         }                                                                                                            // 0.0
/*104 */     } else {                                                                                                         // 0.0
/*106 */         cupkt.flags = CUVID_PKT_ENDOFSTREAM;                                                                         // 0.0
/*108 */     }                                                                                                                // 0.0
/*112 */     ret = CHECK_CU(cuvidParseVideoData(ctx->cuparser, &cupkt));                                                      // 0.0
/*116 */     av_packet_unref(&filtered_packet);                                                                               // 0.0
/*120 */     if (ret < 0) {                                                                                                   // 0.0
/*122 */         if (ctx->internal_error)                                                                                     // 0.0
/*124 */             ret = ctx->internal_error;                                                                               // 0.0
/*126 */         goto error;                                                                                                  // 0.0
/*128 */     }                                                                                                                // 0.0
/*132 */     if (av_fifo_size(ctx->frame_queue)) {                                                                            // 0.0
/*134 */         CUVIDPARSERDISPINFO dispinfo;                                                                                // 0.0
/*136 */         CUVIDPROCPARAMS params;                                                                                      // 0.0
/*138 */         unsigned int pitch = 0;                                                                                      // 0.0
/*140 */         int offset = 0;                                                                                              // 0.0
/*142 */         int i;                                                                                                       // 0.0
/*146 */         av_fifo_generic_read(ctx->frame_queue, &dispinfo, sizeof(CUVIDPARSERDISPINFO), NULL);                        // 0.0
/*150 */         memset(&params, 0, sizeof(params));                                                                          // 0.0
/*152 */         params.progressive_frame = dispinfo.progressive_frame;                                                       // 0.0
/*154 */         params.second_field = 0;                                                                                     // 0.0
/*156 */         params.top_field_first = dispinfo.top_field_first;                                                           // 0.0
/*160 */         ret = CHECK_CU(cuvidMapVideoFrame(ctx->cudecoder, dispinfo.picture_index, &mapped_frame, &pitch, &params));  // 0.0
/*162 */         if (ret < 0)                                                                                                 // 0.0
/*164 */             goto error;                                                                                              // 0.0
/*168 */         if (avctx->pix_fmt == AV_PIX_FMT_CUDA) {                                                                     // 0.0
/*170 */             ret = av_hwframe_get_buffer(ctx->hwframe, frame, 0);                                                     // 0.0
/*172 */             if (ret < 0) {                                                                                           // 0.0
/*174 */                 av_log(avctx, AV_LOG_ERROR, "av_hwframe_get_buffer failed\n");                                       // 0.0
/*176 */                 goto error;                                                                                          // 0.0
/*178 */             }                                                                                                        // 0.0
/*182 */             ret = ff_decode_frame_props(avctx, frame);                                                               // 0.0
/*184 */             if (ret < 0) {                                                                                           // 0.0
/*186 */                 av_log(avctx, AV_LOG_ERROR, "ff_decode_frame_props failed\n");                                       // 0.0
/*188 */                 goto error;                                                                                          // 0.0
/*190 */             }                                                                                                        // 0.0
/*194 */             for (i = 0; i < 2; i++) {                                                                                // 0.0
/*196 */                 CUDA_MEMCPY2D cpy = {                                                                                // 0.0
/*198 */                     .srcMemoryType = CU_MEMORYTYPE_DEVICE,                                                           // 0.0
/*200 */                     .dstMemoryType = CU_MEMORYTYPE_DEVICE,                                                           // 0.0
/*202 */                     .srcDevice     = mapped_frame,                                                                   // 0.0
/*204 */                     .dstDevice     = (CUdeviceptr)frame->data[i],                                                    // 0.0
/*206 */                     .srcPitch      = pitch,                                                                          // 0.0
/*208 */                     .dstPitch      = frame->linesize[i],                                                             // 0.0
/*210 */                     .srcY          = offset,                                                                         // 0.0
/*212 */                     .WidthInBytes  = FFMIN(pitch, frame->linesize[i]),                                               // 0.0
/*214 */                     .Height        = avctx->coded_height >> (i ? 1 : 0),                                             // 0.0
/*216 */                 };                                                                                                   // 0.0
/*220 */                 ret = CHECK_CU(cuMemcpy2D(&cpy));                                                                    // 0.0
/*222 */                 if (ret < 0)                                                                                         // 0.0
/*224 */                     goto error;                                                                                      // 0.0
/*228 */                 offset += avctx->coded_height;                                                                       // 0.0
/*230 */             }                                                                                                        // 0.0
/*232 */         } else if (avctx->pix_fmt == AV_PIX_FMT_NV12) {                                                              // 0.0
/*234 */             AVFrame *tmp_frame = av_frame_alloc();                                                                   // 0.0
/*236 */             if (!tmp_frame) {                                                                                        // 0.0
/*238 */                 av_log(avctx, AV_LOG_ERROR, "av_frame_alloc failed\n");                                              // 0.0
/*240 */                 ret = AVERROR(ENOMEM);                                                                               // 0.0
/*242 */                 goto error;                                                                                          // 0.0
/*244 */             }                                                                                                        // 0.0
/*248 */             tmp_frame->format        = AV_PIX_FMT_CUDA;                                                              // 0.0
/*250 */             tmp_frame->hw_frames_ctx = av_buffer_ref(ctx->hwframe);                                                  // 0.0
/*252 */             tmp_frame->data[0]       = (uint8_t*)mapped_frame;                                                       // 0.0
/*254 */             tmp_frame->linesize[0]   = pitch;                                                                        // 0.0
/*256 */             tmp_frame->data[1]       = (uint8_t*)(mapped_frame + avctx->coded_height * pitch);                       // 0.0
/*258 */             tmp_frame->linesize[1]   = pitch;                                                                        // 0.0
/*260 */             tmp_frame->width         = avctx->width;                                                                 // 0.0
/*262 */             tmp_frame->height        = avctx->height;                                                                // 0.0
/*266 */             ret = ff_get_buffer(avctx, frame, 0);                                                                    // 0.0
/*268 */             if (ret < 0) {                                                                                           // 0.0
/*270 */                 av_log(avctx, AV_LOG_ERROR, "ff_get_buffer failed\n");                                               // 0.0
/*272 */                 av_frame_free(&tmp_frame);                                                                           // 0.0
/*274 */                 goto error;                                                                                          // 0.0
/*276 */             }                                                                                                        // 0.0
/*280 */             ret = av_hwframe_transfer_data(frame, tmp_frame, 0);                                                     // 0.0
/*282 */             if (ret) {                                                                                               // 0.0
/*284 */                 av_log(avctx, AV_LOG_ERROR, "av_hwframe_transfer_data failed\n");                                    // 0.0
/*286 */                 av_frame_free(&tmp_frame);                                                                           // 0.0
/*288 */                 goto error;                                                                                          // 0.0
/*290 */             }                                                                                                        // 0.0
/*294 */             av_frame_free(&tmp_frame);                                                                               // 0.0
/*296 */         } else {                                                                                                     // 0.0
/*298 */             ret = AVERROR_BUG;                                                                                       // 0.0
/*300 */             goto error;                                                                                              // 0.0
/*302 */         }                                                                                                            // 0.0
/*306 */         frame->width = avctx->width;                                                                                 // 0.0
/*308 */         frame->height = avctx->height;                                                                               // 0.0
/*310 */         if (avctx->pkt_timebase.num && avctx->pkt_timebase.den)                                                      // 0.0
/*312 */             frame->pts = av_rescale_q(dispinfo.timestamp, (AVRational){1, 10000000}, avctx->pkt_timebase);           // 0.0
/*314 */         else                                                                                                         // 0.0
/*316 */             frame->pts = dispinfo.timestamp;                                                                         // 0.0
/*320 */         /* CUVIDs opaque reordering breaks the internal pkt logic.                                                   // 0.0
/*322 */          * So set pkt_pts and clear all the other pkt_ fields.                                                       // 0.0
/*324 */          */                                                                                                          // 0.0
/*326 */         frame->pkt_pts = frame->pts;                                                                                 // 0.0
/*328 */         av_frame_set_pkt_pos(frame, -1);                                                                             // 0.0
/*330 */         av_frame_set_pkt_duration(frame, 0);                                                                         // 0.0
/*332 */         av_frame_set_pkt_size(frame, -1);                                                                            // 0.0
/*336 */         frame->interlaced_frame = !dispinfo.progressive_frame;                                                       // 0.0
/*340 */         if (!dispinfo.progressive_frame)                                                                             // 0.0
/*342 */             frame->top_field_first = dispinfo.top_field_first;                                                       // 0.0
/*346 */         *got_frame = 1;                                                                                              // 0.0
/*348 */     } else {                                                                                                         // 0.0
/*350 */         *got_frame = 0;                                                                                              // 0.0
/*352 */     }                                                                                                                // 0.0
/*356 */ error:                                                                                                               // 0.0
/*358 */     if (mapped_frame)                                                                                                // 0.0
/*360 */         eret = CHECK_CU(cuvidUnmapVideoFrame(ctx->cudecoder, mapped_frame));                                         // 0.0
/*364 */     eret = CHECK_CU(cuCtxPopCurrent(&dummy));                                                                        // 0.0
/*368 */     if (eret < 0)                                                                                                    // 0.0
/*370 */         return eret;                                                                                                 // 0.0
/*372 */     else                                                                                                             // 0.0
/*374 */         return ret;                                                                                                  // 0.0
/*376 */ }                                                                                                                    // 0.0
