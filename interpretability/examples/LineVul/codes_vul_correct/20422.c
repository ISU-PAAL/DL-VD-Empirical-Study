// commit message FFmpeg@5d7e3d7167 (target=1, prob=0.52871984, correct=True): Check for out of bound reads in the Tiertex Limited SEQ decoder.
/*0  */ static int seqvideo_decode_frame(AVCodecContext *avctx,                                                     // (5) 0.04945
/*2  */                                  void *data, int *data_size,                                                // (1) 0.1154
/*4  */                                  AVPacket *avpkt)                                                           // (2) 0.1099
/*6  */ {                                                                                                           // (16) 0.002747
/*8  */     const uint8_t *buf = avpkt->data;                                                                       // (7) 0.0467
/*10 */     int buf_size = avpkt->size;                                                                             // (10) 0.03846
/*14 */     SeqVideoContext *seq = avctx->priv_data;                                                                // (6) 0.0467
/*18 */     seq->frame.reference = 1;                                                                               // (12) 0.03022
/*20 */     seq->frame.buffer_hints = FF_BUFFER_HINTS_VALID | FF_BUFFER_HINTS_PRESERVE | FF_BUFFER_HINTS_REUSABLE;  // (0) 0.1374
/*22 */     if (avctx->reget_buffer(avctx, &seq->frame)) {                                                          // (4) 0.06044
/*24 */         av_log(seq->avctx, AV_LOG_ERROR, "tiertexseqvideo: reget_buffer() failed\n");                       // (3) 0.1016
/*26 */         return -1;                                                                                          // (13) 0.03022
/*28 */     }                                                                                                       // (15) 0.01099
/*32 */     seqvideo_decode(seq, buf, buf_size);                                                                    // (8) 0.0467
/*36 */     *data_size = sizeof(AVFrame);                                                                           // (11) 0.03571
/*38 */     *(AVFrame *)data = seq->frame;                                                                          // (9) 0.03846
/*42 */     return buf_size;                                                                                        // (14) 0.02198
/*44 */ }                                                                                                           // (17) 0.002747
