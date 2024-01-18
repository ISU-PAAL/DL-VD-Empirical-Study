// commit message FFmpeg@ffd7fd7944 (target=1, prob=0.99907374, correct=True): avcodec/vda_h264: use av_buffer to manage buffers
/*0  */ static int vda_h264_end_frame(AVCodecContext *avctx)                           // (6) 0.07326
/*1  */ {                                                                              // (12) 0.003663
/*2  */     H264Context *h                      = avctx->priv_data;                    // (1) 0.1355
/*3  */     struct vda_context *vda_ctx         = avctx->hwaccel_context;              // (3) 0.1136
/*4  */     AVFrame *frame                      = &h->cur_pic_ptr->f;                  // (0) 0.1465
/*5  */     struct vda_buffer *context;                                                // (8) 0.04029
/*6  */     AVBufferRef *buffer;                                                       // (9) 0.03297
/*7  */     int status;                                                                // (11) 0.02198
/*8  */     if (!vda_ctx->decoder || !vda_ctx->priv_bitstream)                         // (4) 0.08791
/*9  */     status = vda_sync_decode(vda_ctx);                                         // (7) 0.06593
/*10 */     frame->data[3] = (void*)vda_ctx->cv_buffer;                                // (5) 0.08059
/*11 */     if (status)                                                                // (10) 0.02564
/*12 */         av_log(avctx, AV_LOG_ERROR, "Failed to decode frame (%d)\n", status);  // (2) 0.1209
