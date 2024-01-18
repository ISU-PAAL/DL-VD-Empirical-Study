// commit message FFmpeg@39f01e346c (target=1, prob=0.881984, correct=True): mmaldec: be more tolerant against MMAL not returning decoded output
/*0   */ static int ffmmal_add_packet(AVCodecContext *avctx, AVPacket *avpkt,                  // (2) 0.05273
/*2   */                              int is_extradata)                                        // (0) 0.06836
/*4   */ {                                                                                     // (28) 0.001953
/*6   */     MMALDecodeContext *ctx = avctx->priv_data;                                        // (12) 0.03516
/*8   */     AVBufferRef *buf = NULL;                                                          // (20) 0.02148
/*10  */     int size = 0;                                                                     // (24) 0.01562
/*12  */     uint8_t *data = (uint8_t *)"";                                                    // (11) 0.03516
/*14  */     uint8_t *start;                                                                   // (21) 0.01953
/*16  */     int ret = 0;                                                                      // (23) 0.01563
/*20  */     if (avpkt->size) {                                                                // (18) 0.02344
/*22  */         if (avpkt->buf) {                                                             // (13) 0.03125
/*24  */             buf = av_buffer_ref(avpkt->buf);                                          // (3) 0.04883
/*26  */             size = avpkt->size;                                                       // (10) 0.03711
/*28  */             data = avpkt->data;                                                       // (9) 0.03711
/*30  */         } else {                                                                      // (22) 0.01953
/*32  */             buf = av_buffer_alloc(avpkt->size);                                       // (4) 0.04883
/*34  */             if (buf) {                                                                // (14) 0.03125
/*36  */                 memcpy(buf->data, avpkt->data, avpkt->size);                          // (1) 0.06836
/*38  */                 size = buf->size;                                                     // (7) 0.04102
/*40  */                 data = buf->data;                                                     // (6) 0.04102
/*42  */             }                                                                         // (19) 0.02344
/*44  */         }                                                                             // (26) 0.01562
/*46  */         if (!buf) {                                                                   // (17) 0.02344
/*48  */             ret = AVERROR(ENOMEM);                                                    // (5) 0.04102
/*50  */             goto done;                                                                // (16) 0.02734
/*52  */         }                                                                             // (25) 0.01562
/*54  */         if (!is_extradata)                                                            // (15) 0.0293
/*56  */             ctx->packets_sent++;                                                      // (8) 0.03711
/*58  */     } else {                                                                          // (27) 0.01172
/*60  */         if (!ctx->packets_sent) {                                                     // 0.0
/*62  */             // Short-cut the flush logic to avoid upsetting MMAL.                     // 0.0
/*64  */             ctx->eos_sent = 1;                                                        // 0.0
/*66  */             ctx->eos_received = 1;                                                    // 0.0
/*68  */             goto done;                                                                // 0.0
/*70  */         }                                                                             // 0.0
/*72  */     }                                                                                 // 0.0
/*76  */     start = data;                                                                     // 0.0
/*80  */     do {                                                                              // 0.0
/*82  */         FFBufferEntry *buffer = av_mallocz(sizeof(*buffer));                          // 0.0
/*84  */         if (!buffer) {                                                                // 0.0
/*86  */             ret = AVERROR(ENOMEM);                                                    // 0.0
/*88  */             goto done;                                                                // 0.0
/*90  */         }                                                                             // 0.0
/*94  */         buffer->data = data;                                                          // 0.0
/*96  */         buffer->length = FFMIN(size, ctx->decoder->input[0]->buffer_size);            // 0.0
/*100 */         if (is_extradata)                                                             // 0.0
/*102 */             buffer->flags |= MMAL_BUFFER_HEADER_FLAG_CONFIG;                          // 0.0
/*106 */         if (data == start)                                                            // 0.0
/*108 */             buffer->flags |= MMAL_BUFFER_HEADER_FLAG_FRAME_START;                     // 0.0
/*112 */         data += buffer->length;                                                       // 0.0
/*114 */         size -= buffer->length;                                                       // 0.0
/*118 */         buffer->pts = avpkt->pts == AV_NOPTS_VALUE ? MMAL_TIME_UNKNOWN : avpkt->pts;  // 0.0
/*120 */         buffer->dts = avpkt->dts == AV_NOPTS_VALUE ? MMAL_TIME_UNKNOWN : avpkt->dts;  // 0.0
/*124 */         if (!size)                                                                    // 0.0
/*126 */             buffer->flags |= MMAL_BUFFER_HEADER_FLAG_FRAME_END;                       // 0.0
/*130 */         if (!buffer->length) {                                                        // 0.0
/*132 */             buffer->flags |= MMAL_BUFFER_HEADER_FLAG_EOS;                             // 0.0
/*134 */             ctx->eos_sent = 1;                                                        // 0.0
/*136 */         }                                                                             // 0.0
/*140 */         if (buf) {                                                                    // 0.0
/*142 */             buffer->ref = av_buffer_ref(buf);                                         // 0.0
/*144 */             if (!buffer->ref) {                                                       // 0.0
/*146 */                 av_free(buffer);                                                      // 0.0
/*148 */                 ret = AVERROR(ENOMEM);                                                // 0.0
/*150 */                 goto done;                                                            // 0.0
/*152 */             }                                                                         // 0.0
/*154 */         }                                                                             // 0.0
/*158 */         // Insert at end of the list                                                  // 0.0
/*160 */         if (!ctx->waiting_buffers)                                                    // 0.0
/*162 */             ctx->waiting_buffers = buffer;                                            // 0.0
/*164 */         if (ctx->waiting_buffers_tail)                                                // 0.0
/*166 */             ctx->waiting_buffers_tail->next = buffer;                                 // 0.0
/*168 */         ctx->waiting_buffers_tail = buffer;                                           // 0.0
/*170 */     } while (size);                                                                   // 0.0
/*174 */ done:                                                                                 // 0.0
/*176 */     av_buffer_unref(&buf);                                                            // 0.0
/*178 */     return ret;                                                                       // 0.0
/*180 */ }                                                                                     // 0.0
