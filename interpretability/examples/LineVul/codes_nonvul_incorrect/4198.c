// commit message FFmpeg@a755b725ec (target=0, prob=0.5222609, correct=False): avcodec: consider an error during decoder draining as EOF
/*0   */ static int do_decode(AVCodecContext *avctx, AVPacket *pkt)                        // (6) 0.04296
/*2   */ {                                                                                 // (24) 0.001954
/*4   */     int got_frame;                                                                // (21) 0.01562
/*6   */     int ret;                                                                      // (22) 0.01171
/*10  */     av_assert0(!avctx->internal->buffer_frame->buf[0]);                           // (7) 0.04295
/*14  */     if (!pkt)                                                                     // (20) 0.01562
/*16  */         pkt = avctx->internal->buffer_pkt;                                        // (11) 0.03905
/*20  */     // This is the lesser evil. The field is for compatibility with legacy users  // (12) 0.03526
/*22  */     // of the legacy API, and users using the new API should not be forced to     // (10) 0.0391
/*24  */     // even know about this field.                                                // (18) 0.01955
/*26  */     avctx->refcounted_frames = 1;                                                 // (17) 0.02734
/*30  */     // Some codecs (at least wma lossless) will crash when feeding drain packets  // (9) 0.04113
/*32  */     // after EOF was signaled.                                                    // (19) 0.01953
/*34  */     if (avctx->internal->draining_done)                                           // (16) 0.02929
/*36  */         return AVERROR_EOF;                                                       // (15) 0.02929
/*40  */     if (avctx->codec_type == AVMEDIA_TYPE_VIDEO) {                                // (8) 0.04295
/*42  */         ret = avcodec_decode_video2(avctx, avctx->internal->buffer_frame,         // (3) 0.06052
/*44  */                                     &got_frame, pkt);                             // (0) 0.08394
/*46  */         if (ret >= 0 && !(avctx->flags & AV_CODEC_FLAG_TRUNCATED))                // (2) 0.06442
/*48  */             ret = pkt->size;                                                      // (13) 0.03514
/*50  */     } else if (avctx->codec_type == AVMEDIA_TYPE_AUDIO) {                         // (5) 0.04881
/*52  */         ret = avcodec_decode_audio4(avctx, avctx->internal->buffer_frame,         // (4) 0.06052
/*54  */                                     &got_frame, pkt);                             // (1) 0.08394
/*56  */     } else {                                                                      // (23) 0.01171
/*58  */         ret = AVERROR(EINVAL);                                                    // (14) 0.03319
/*60  */     }                                                                             // 0.0
/*64  */     if (ret == AVERROR(EAGAIN))                                                   // 0.0
/*66  */         ret = pkt->size;                                                          // 0.0
/*70  */     if (ret < 0)                                                                  // 0.0
/*72  */         return ret;                                                               // 0.0
/*76  */     if (avctx->internal->draining && !got_frame)                                  // 0.0
/*78  */         avctx->internal->draining_done = 1;                                       // 0.0
/*82  */     if (ret >= pkt->size) {                                                       // 0.0
/*84  */         av_packet_unref(avctx->internal->buffer_pkt);                             // 0.0
/*86  */     } else {                                                                      // 0.0
/*88  */         int consumed = ret;                                                       // 0.0
/*92  */         if (pkt != avctx->internal->buffer_pkt) {                                 // 0.0
/*94  */             av_packet_unref(avctx->internal->buffer_pkt);                         // 0.0
/*96  */             if ((ret = av_packet_ref(avctx->internal->buffer_pkt, pkt)) < 0)      // 0.0
/*98  */                 return ret;                                                       // 0.0
/*100 */         }                                                                         // 0.0
/*104 */         avctx->internal->buffer_pkt->data += consumed;                            // 0.0
/*106 */         avctx->internal->buffer_pkt->size -= consumed;                            // 0.0
/*108 */         avctx->internal->buffer_pkt->pts   = AV_NOPTS_VALUE;                      // 0.0
/*110 */         avctx->internal->buffer_pkt->dts   = AV_NOPTS_VALUE;                      // 0.0
/*112 */     }                                                                             // 0.0
/*116 */     if (got_frame)                                                                // 0.0
/*118 */         av_assert0(avctx->internal->buffer_frame->buf[0]);                        // 0.0
/*122 */     return 0;                                                                     // 0.0
/*124 */ }                                                                                 // 0.0
