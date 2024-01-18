// commit message FFmpeg@d32547a24a (target=1, prob=0.9991165, correct=True): avcodec/utils: silence some deprecation warnings
/*0  */ int attribute_align_arg avcodec_encode_audio(AVCodecContext *avctx,               // (6) 0.04502
/*1  */                                              uint8_t *buf, int buf_size,          // (0) 0.1093
/*2  */                                              const short *samples)                // (1) 0.09762
/*3  */ {                                                                                 // (21) 0.001953
/*4  */     AVPacket pkt;                                                                 // (18) 0.01757
/*5  */     AVFrame *frame;                                                               // (20) 0.01562
/*6  */     int ret, samples_size, got_packet;                                            // (11) 0.02948
/*7  */     av_init_packet(&pkt);                                                         // (13) 0.02539
/*8  */     pkt.data = buf;                                                               // (16) 0.01953
/*9  */     pkt.size = buf_size;                                                          // (14) 0.02343
/*10 */     if (samples) {                                                                // (19) 0.01757
/*11 */         frame = av_frame_alloc();                                                 // (12) 0.02929
/*12 */         if (!frame)                                                               // (15) 0.02148
/*13 */             return AVERROR(ENOMEM);                                               // (8) 0.03905
/*14 */         if (avctx->frame_size) {                                                  // (10) 0.03319
/*15 */             frame->nb_samples = avctx->frame_size;                                // (5) 0.04881
/*16 */         } else {                                                                  // (17) 0.01952
/*17 */             /* if frame_size is not set, the number of samples must be            // (4) 0.05076
/*18 */              * calculated from the buffer size */                                 // (9) 0.0371
/*19 */             int64_t nb_samples;                                                   // (7) 0.041
/*20 */             if (!av_get_bits_per_sample(avctx->codec_id)) {                       // (3) 0.06248
/*21 */                 av_log(avctx, AV_LOG_ERROR, "avcodec_encode_audio() does not "    // (2) 0.08006
/*22 */                                             "support this codec\n");              // 0.0
/*23 */                 av_frame_free(&frame);                                            // 0.0
/*24 */                 return AVERROR(EINVAL);                                           // 0.0
/*25 */             }                                                                     // 0.0
/*26 */             nb_samples = (int64_t)buf_size * 8 /                                  // 0.0
/*27 */                          (av_get_bits_per_sample(avctx->codec_id) *               // 0.0
/*28 */                           avctx->channels);                                       // 0.0
/*29 */             if (nb_samples >= INT_MAX) {                                          // 0.0
/*30 */                 av_frame_free(&frame);                                            // 0.0
/*31 */                 return AVERROR(EINVAL);                                           // 0.0
/*32 */             }                                                                     // 0.0
/*33 */             frame->nb_samples = nb_samples;                                       // 0.0
/*34 */         }                                                                         // 0.0
/*35 */         /* it is assumed that the samples buffer is large enough based on the     // 0.0
/*36 */          * relevant parameters */                                                 // 0.0
/*37 */         samples_size = av_samples_get_buffer_size(NULL, avctx->channels,          // 0.0
/*38 */                                                   frame->nb_samples,              // 0.0
/*39 */                                                   avctx->sample_fmt, 1);          // 0.0
/*40 */         if ((ret = avcodec_fill_audio_frame(frame, avctx->channels,               // 0.0
/*41 */                                             avctx->sample_fmt,                    // 0.0
/*42 */                                             (const uint8_t *)samples,             // 0.0
/*43 */                                             samples_size, 1)) < 0) {              // 0.0
/*44 */             av_frame_free(&frame);                                                // 0.0
/*45 */             return ret;                                                           // 0.0
/*46 */         }                                                                         // 0.0
/*47 */         /* fabricate frame pts from sample count.                                 // 0.0
/*48 */          * this is needed because the avcodec_encode_audio() API does not have    // 0.0
/*49 */          * a way for the user to provide pts */                                   // 0.0
/*50 */         if (avctx->sample_rate && avctx->time_base.num)                           // 0.0
/*51 */             frame->pts = ff_samples_to_time_base(avctx,                           // 0.0
/*52 */                                                  avctx->internal->sample_count);  // 0.0
/*53 */         else                                                                      // 0.0
/*54 */             frame->pts = AV_NOPTS_VALUE;                                          // 0.0
/*55 */         avctx->internal->sample_count += frame->nb_samples;                       // 0.0
/*56 */     } else {                                                                      // 0.0
/*57 */         frame = NULL;                                                             // 0.0
/*58 */     }                                                                             // 0.0
/*59 */     got_packet = 0;                                                               // 0.0
/*60 */     ret = avcodec_encode_audio2(avctx, &pkt, frame, &got_packet);                 // 0.0
/*61 */     if (!ret && got_packet && avctx->coded_frame) {                               // 0.0
/*62 */         avctx->coded_frame->pts       = pkt.pts;                                  // 0.0
/*63 */         avctx->coded_frame->key_frame = !!(pkt.flags & AV_PKT_FLAG_KEY);          // 0.0
/*64 */     }                                                                             // 0.0
/*65 */     /* free any side data since we cannot return it */                            // 0.0
/*66 */     av_packet_free_side_data(&pkt);                                               // 0.0
/*67 */     if (frame && frame->extended_data != frame->data)                             // 0.0
/*68 */         av_freep(&frame->extended_data);                                          // 0.0
/*69 */     av_frame_free(&frame);                                                        // 0.0
/*70 */     return ret ? ret : pkt.size;                                                  // 0.0
/*71 */ }                                                                                 // 0.0
