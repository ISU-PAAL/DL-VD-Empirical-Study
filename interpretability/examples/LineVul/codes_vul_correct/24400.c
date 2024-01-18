// commit message FFmpeg@439c3d5bcc (target=1, prob=0.51801854, correct=True): nellymoserenc: fix crash due to memsetting the wrong area.
/*0  */ static int encode_frame(AVCodecContext *avctx, AVPacket *avpkt,               // (11) 0.04297
/*2  */                         const AVFrame *frame, int *got_packet_ptr)            // (3) 0.07422
/*4  */ {                                                                             // (22) 0.001953
/*6  */     NellyMoserEncodeContext *s = avctx->priv_data;                            // (12) 0.03906
/*8  */     int ret;                                                                  // (19) 0.01172
/*12 */     if (s->last_frame)                                                        // (15) 0.02148
/*14 */         return 0;                                                             // (16) 0.01953
/*18 */     memcpy(s->buf, s->buf + NELLY_SAMPLES, NELLY_BUF_LEN * sizeof(*s->buf));  // (2) 0.07617
/*20 */     if (frame) {                                                              // (17) 0.01562
/*22 */         memcpy(s->buf + NELLY_BUF_LEN, frame->data[0],                        // (5) 0.06055
/*24 */                frame->nb_samples * sizeof(*s->buf));                          // (8) 0.05273
/*26 */         if (frame->nb_samples < NELLY_SAMPLES) {                              // (9) 0.04883
/*28 */             memset(s->buf + NELLY_BUF_LEN + avctx->frame_size, 0,             // (4) 0.07227
/*30 */                    (NELLY_SAMPLES - frame->nb_samples) * sizeof(*s->buf));    // (0) 0.08008
/*32 */             if (frame->nb_samples >= NELLY_BUF_LEN)                           // (6) 0.05859
/*34 */                 s->last_frame = 1;                                            // (10) 0.04492
/*36 */         }                                                                     // (18) 0.01562
/*38 */         if ((ret = ff_af_queue_add(&s->afq, frame) < 0))                      // (7) 0.05664
/*40 */             return ret;                                                       // (14) 0.02734
/*42 */     } else {                                                                  // (20) 0.01172
/*44 */         memset(s->buf + NELLY_BUF_LEN, 0, NELLY_SAMPLES * sizeof(*s->buf));   // (1) 0.07812
/*46 */         s->last_frame = 1;                                                    // (13) 0.0293
/*48 */     }                                                                         // (21) 0.007812
/*52 */     if ((ret = ff_alloc_packet(avpkt, NELLY_BLOCK_LEN))) {                    // 0.0
/*54 */         av_log(avctx, AV_LOG_ERROR, "Error getting output packet\n");         // 0.0
/*56 */         return ret;                                                           // 0.0
/*58 */     }                                                                         // 0.0
/*60 */     encode_block(s, avpkt->data, avpkt->size);                                // 0.0
/*64 */     /* Get the next frame pts/duration */                                     // 0.0
/*66 */     ff_af_queue_remove(&s->afq, avctx->frame_size, &avpkt->pts,               // 0.0
/*68 */                        &avpkt->duration);                                     // 0.0
/*72 */     *got_packet_ptr = 1;                                                      // 0.0
/*74 */     return 0;                                                                 // 0.0
/*76 */ }                                                                             // 0.0
