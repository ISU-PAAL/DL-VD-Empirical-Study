// commit message FFmpeg@2df0c32ea1 (target=0, prob=0.4480859, correct=True): lavc: use a separate field for exporting audio encoder padding
/*0   */ static int amr_nb_encode_frame(AVCodecContext *avctx, AVPacket *avpkt,                          // (6) 0.05469
/*2   */                                const AVFrame *frame, int *got_packet_ptr)                       // (0) 0.08789
/*4   */ {                                                                                               // (22) 0.001955
/*6   */     AMRContext *s = avctx->priv_data;                                                           // (15) 0.03125
/*8   */     int written, ret;                                                                           // (18) 0.01563
/*10  */     int16_t *flush_buf = NULL;                                                                  // (16) 0.02734
/*12  */     const int16_t *samples = frame ? (const int16_t *)frame->data[0] : NULL;                    // (5) 0.05859
/*16  */     if (s->enc_bitrate != avctx->bit_rate) {                                                    // (12) 0.03906
/*18  */         s->enc_mode    = get_bitrate_mode(avctx->bit_rate, avctx);                              // (3) 0.06445
/*20  */         s->enc_bitrate = avctx->bit_rate;                                                       // (11) 0.04102
/*22  */     }                                                                                           // (21) 0.007812
/*26  */     if ((ret = ff_alloc_packet(avpkt, 32))) {                                                   // (10) 0.04102
/*28  */         av_log(avctx, AV_LOG_ERROR, "Error getting output packet\n");                           // (7) 0.05469
/*30  */         return ret;                                                                             // (17) 0.01953
/*32  */     }                                                                                           // (20) 0.007812
/*36  */     if (frame) {                                                                                // (19) 0.01562
/*38  */         if (frame->nb_samples < avctx->frame_size) {                                            // (8) 0.04687
/*40  */             flush_buf = av_mallocz(avctx->frame_size * sizeof(*flush_buf));                     // (2) 0.06641
/*42  */             if (!flush_buf)                                                                     // (14) 0.0332
/*44  */                 return AVERROR(ENOMEM);                                                         // (9) 0.04687
/*46  */             memcpy(flush_buf, samples, frame->nb_samples * sizeof(*flush_buf));                 // (1) 0.06641
/*48  */             samples = flush_buf;                                                                // (13) 0.0332
/*50  */             if (frame->nb_samples < avctx->frame_size - avctx->delay)                           // (4) 0.0625
/*52  */                 s->enc_last_frame = -1;                                                         // 0.0
/*54  */         }                                                                                       // 0.0
/*56  */         if ((ret = ff_af_queue_add(&s->afq, frame)) < 0) {                                      // 0.0
/*58  */             av_freep(&flush_buf);                                                               // 0.0
/*60  */             return ret;                                                                         // 0.0
/*62  */         }                                                                                       // 0.0
/*64  */     } else {                                                                                    // 0.0
/*66  */         if (s->enc_last_frame < 0)                                                              // 0.0
/*68  */             return 0;                                                                           // 0.0
/*70  */         flush_buf = av_mallocz(avctx->frame_size * sizeof(*flush_buf));                         // 0.0
/*72  */         if (!flush_buf)                                                                         // 0.0
/*74  */             return AVERROR(ENOMEM);                                                             // 0.0
/*76  */         samples = flush_buf;                                                                    // 0.0
/*78  */         s->enc_last_frame = -1;                                                                 // 0.0
/*80  */     }                                                                                           // 0.0
/*84  */     written = Encoder_Interface_Encode(s->enc_state, s->enc_mode, samples,                      // 0.0
/*86  */                                        avpkt->data, 0);                                         // 0.0
/*88  */     av_dlog(avctx, "amr_nb_encode_frame encoded %u bytes, bitrate %u, first byte was %#02x\n",  // 0.0
/*90  */             written, s->enc_mode, frame[0]);                                                    // 0.0
/*94  */     /* Get the next frame pts/duration */                                                       // 0.0
/*96  */     ff_af_queue_remove(&s->afq, avctx->frame_size, &avpkt->pts,                                 // 0.0
/*98  */                        &avpkt->duration);                                                       // 0.0
/*102 */     avpkt->size = written;                                                                      // 0.0
/*104 */     *got_packet_ptr = 1;                                                                        // 0.0
/*106 */     av_freep(&flush_buf);                                                                       // 0.0
/*108 */     return 0;                                                                                   // 0.0
/*110 */ }                                                                                               // 0.0
