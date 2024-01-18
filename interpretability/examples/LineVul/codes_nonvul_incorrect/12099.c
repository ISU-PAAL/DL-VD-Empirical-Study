// commit message FFmpeg@405af43104 (target=0, prob=0.6889533, correct=False): cin audio: restructure decoding loop to avoid a separate counter variable
/*0  */ static int cinaudio_decode_frame(AVCodecContext *avctx,       // (6) 0.04237
/*2  */                                  void *data, int *data_size,  // (0) 0.08898
/*4  */                                  AVPacket *avpkt)             // (1) 0.08475
/*6  */ {                                                             // (26) 0.002119
/*8  */     const uint8_t *buf = avpkt->data;                         // (10) 0.03602
/*10 */     int buf_size = avpkt->size;                               // (12) 0.02966
/*12 */     CinAudioContext *cin = avctx->priv_data;                  // (9) 0.03602
/*14 */     const uint8_t *src = buf;                                 // (15) 0.02754
/*16 */     int16_t *samples = data;                                  // (16) 0.02754
/*18 */     int delta;                                                // (23) 0.01271
/*22 */     buf_size = FFMIN(buf_size, *data_size/2);                 // (5) 0.04449
/*26 */     delta = cin->delta;                                       // (20) 0.02331
/*28 */     if (cin->initial_decode_frame) {                          // (11) 0.03178
/*30 */         cin->initial_decode_frame = 0;                        // (7) 0.04025
/*32 */         delta = (int16_t)AV_RL16(src); src += 2;              // (2) 0.05508
/*34 */         *samples++ = delta;                                   // (13) 0.02966
/*36 */         buf_size -= 2;                                        // (17) 0.02754
/*38 */     }                                                         // (24) 0.008475
/*40 */     while (buf_size > 0) {                                    // (18) 0.02542
/*42 */         delta += cinaudio_delta16_table[*src++];              // (4) 0.05085
/*44 */         delta = av_clip_int16(delta);                         // (8) 0.04025
/*46 */         *samples++ = delta;                                   // (14) 0.02966
/*48 */         --buf_size;                                           // (19) 0.02542
/*50 */     }                                                         // (25) 0.008475
/*52 */     cin->delta = delta;                                       // (21) 0.02331
/*56 */     *data_size = (uint8_t *)samples - (uint8_t *)data;        // (3) 0.05297
/*60 */     return src - buf;                                         // (22) 0.01695
/*62 */ }                                                             // (27) 0.002119
