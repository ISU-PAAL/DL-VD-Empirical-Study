// commit message FFmpeg@df824548d0 (target=0, prob=0.57635456, correct=False): 8svx: Fixing header size, move decoding to per call instead of the first call.
/*0   */ static int eightsvx_decode_frame(AVCodecContext *avctx, void *data,                                          // (6) 0.04688
/*2   */                                  int *got_frame_ptr, AVPacket *avpkt)                                        // (0) 0.09375
/*4   */ {                                                                                                            // (23) 0.001953
/*6   */     EightSvxContext *esc = avctx->priv_data;                                                                 // (13) 0.03516
/*8   */     int n, out_data_size;                                                                                    // (18) 0.02344
/*10  */     int ch, ret;                                                                                             // (21) 0.01563
/*12  */     uint8_t *src;                                                                                            // (20) 0.01953
/*16  */     /* decode and interleave the first packet */                                                             // (17) 0.02344
/*18  */     if (!esc->samples && avpkt) {                                                                            // (15) 0.0293
/*20  */         int packet_size = avpkt->size;                                                                       // (14) 0.03516
/*24  */         if (packet_size % avctx->channels) {                                                                 // (8) 0.04102
/*26  */             av_log(avctx, AV_LOG_WARNING, "Packet with odd size, ignoring last byte\n");                     // (1) 0.07227
/*28  */             if (packet_size < avctx->channels)                                                               // (7) 0.04687
/*30  */                 return packet_size;                                                                          // (10) 0.03906
/*32  */             packet_size -= packet_size % avctx->channels;                                                    // (5) 0.04883
/*34  */         }                                                                                                    // (22) 0.01562
/*36  */         esc->samples_size = !esc->table ?                                                                    // (12) 0.03711
/*38  */             packet_size : avctx->channels + (packet_size-avctx->channels) * 2;                               // (2) 0.07031
/*40  */         if (!(esc->samples = av_malloc(esc->samples_size)))                                                  // (3) 0.05273
/*42  */             return AVERROR(ENOMEM);                                                                          // (9) 0.03906
/*46  */         /* decompress */                                                                                     // (19) 0.02148
/*48  */         if (esc->table) {                                                                                    // (16) 0.02734
/*50  */             const uint8_t *buf = avpkt->data;                                                                // (4) 0.04883
/*52  */             uint8_t *dst;                                                                                    // (11) 0.03711
/*54  */             int buf_size = avpkt->size;                                                                      // 0.0
/*56  */             int i, n = esc->samples_size;                                                                    // 0.0
/*60  */             if (buf_size < 2) {                                                                              // 0.0
/*62  */                 av_log(avctx, AV_LOG_ERROR, "packet size is too small\n");                                   // 0.0
/*64  */                 return AVERROR(EINVAL);                                                                      // 0.0
/*66  */             }                                                                                                // 0.0
/*70  */             /* the uncompressed starting value is contained in the first byte */                             // 0.0
/*72  */             dst = esc->samples;                                                                              // 0.0
/*74  */             for (i = 0; i < avctx->channels; i++) {                                                          // 0.0
/*76  */                 *(dst++) = buf[0]+128;                                                                       // 0.0
/*78  */                 delta_decode(dst, buf + 1, buf_size / avctx->channels - 1, (buf[0]+128)&0xFF, esc->table);   // 0.0
/*80  */                 buf += buf_size / avctx->channels;                                                           // 0.0
/*82  */                 dst += n / avctx->channels - 1;                                                              // 0.0
/*84  */             }                                                                                                // 0.0
/*86  */         } else {                                                                                             // 0.0
/*88  */             raw_decode(esc->samples, avpkt->data, esc->samples_size);                                        // 0.0
/*90  */         }                                                                                                    // 0.0
/*92  */     }                                                                                                        // 0.0
/*96  */     /* get output buffer */                                                                                  // 0.0
/*98  */     av_assert1(!(esc->samples_size % avctx->channels || esc->samples_idx % avctx->channels));                // 0.0
/*100 */     esc->frame.nb_samples = FFMIN(MAX_FRAME_SIZE, esc->samples_size - esc->samples_idx)  / avctx->channels;  // 0.0
/*102 */     if ((ret = avctx->get_buffer(avctx, &esc->frame)) < 0) {                                                 // 0.0
/*104 */         av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");                                                // 0.0
/*106 */         return ret;                                                                                          // 0.0
/*108 */     }                                                                                                        // 0.0
/*112 */     *got_frame_ptr   = 1;                                                                                    // 0.0
/*114 */     *(AVFrame *)data = esc->frame;                                                                           // 0.0
/*118 */     out_data_size = esc->frame.nb_samples;                                                                   // 0.0
/*120 */     for (ch = 0; ch<avctx->channels; ch++) {                                                                 // 0.0
/*122 */         src = esc->samples + esc->samples_idx / avctx->channels + ch * esc->samples_size / avctx->channels;  // 0.0
/*124 */         memcpy(esc->frame.data[ch], src, out_data_size);                                                     // 0.0
/*126 */     }                                                                                                        // 0.0
/*128 */     out_data_size *= avctx->channels;                                                                        // 0.0
/*130 */     esc->samples_idx += out_data_size;                                                                       // 0.0
/*134 */     return esc->table ?                                                                                      // 0.0
/*136 */         (avctx->frame_number == 0)*2 + out_data_size / 2 :                                                   // 0.0
/*138 */         out_data_size;                                                                                       // 0.0
/*140 */ }                                                                                                            // 0.0
