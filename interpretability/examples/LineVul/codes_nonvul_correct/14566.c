// commit message FFmpeg@bcaf64b605 (target=0, prob=0.21547836, correct=True): normalize calls to ff_alloc_packet2
/*0  */ static int g722_encode_frame(AVCodecContext *avctx, AVPacket *avpkt,               // (6) 0.05273
/*2  */                              const AVFrame *frame, int *got_packet_ptr)            // (0) 0.08398
/*4  */ {                                                                                  // (22) 0.001953
/*6  */     G722Context *c = avctx->priv_data;                                             // (13) 0.0332
/*8  */     const int16_t *samples = (const int16_t *)frame->data[0];                      // (9) 0.04883
/*10 */     int nb_samples, out_size, ret;                                                 // (14) 0.03125
/*14 */     out_size = (frame->nb_samples + 1) / 2;                                        // (10) 0.03906
/*16 */     if ((ret = ff_alloc_packet2(avctx, avpkt, out_size)))                          // (8) 0.05078
/*18 */         return ret;                                                                // (18) 0.01953
/*22 */     nb_samples = frame->nb_samples - (frame->nb_samples & 1);                      // (7) 0.05078
/*26 */     if (avctx->trellis)                                                            // (17) 0.02344
/*28 */         g722_encode_trellis(c, avctx->trellis, avpkt->data, nb_samples, samples);  // (1) 0.08008
/*30 */     else                                                                           // (21) 0.007812
/*32 */         g722_encode_no_trellis(c, avpkt->data, nb_samples, samples);               // (3) 0.07031
/*36 */     /* handle last frame with odd frame_size */                                    // (15) 0.02539
/*38 */     if (nb_samples < frame->nb_samples) {                                          // (12) 0.03516
/*40 */         int16_t last_samples[2] = { samples[nb_samples], samples[nb_samples] };    // (4) 0.06836
/*42 */         encode_byte(c, &avpkt->data[nb_samples >> 1], last_samples);               // (5) 0.0625
/*44 */     }                                                                              // (20) 0.007813
/*48 */     if (frame->pts != AV_NOPTS_VALUE)                                              // (11) 0.03516
/*50 */         avpkt->pts = frame->pts - ff_samples_to_time_base(avctx, avctx->delay);    // (2) 0.07422
/*52 */     *got_packet_ptr = 1;                                                           // (16) 0.02539
/*54 */     return 0;                                                                      // (19) 0.01172
/*56 */ }                                                                                  // 0.0
