// commit message FFmpeg@de1824e970 (target=0, prob=0.53300595, correct=False): mpeg12: fix logic that prevents extradata from being parsed twice.
/*0  */ static int mpeg_decode_frame(AVCodecContext *avctx,                                                   // (11) 0.03516
/*2  */                              void *data, int *data_size,                                              // (1) 0.07422
/*4  */                              AVPacket *avpkt)                                                         // (3) 0.07031
/*6  */ {                                                                                                     // (23) 0.001953
/*8  */     const uint8_t *buf = avpkt->data;                                                                 // (14) 0.0332
/*10 */     int buf_size = avpkt->size;                                                                       // (16) 0.02734
/*12 */     Mpeg1Context *s = avctx->priv_data;                                                               // (13) 0.0332
/*14 */     AVFrame *picture = data;                                                                          // (19) 0.01953
/*16 */     MpegEncContext *s2 = &s->mpeg_enc_ctx;                                                            // (10) 0.03906
/*18 */     av_dlog(avctx, "fill_buffer\n");                                                                  // (12) 0.03516
/*22 */     if (buf_size == 0 || (buf_size == 4 && AV_RB32(buf) == SEQ_END_CODE)) {                           // (4) 0.06836
/*24 */         /* special case for last picture */                                                           // (17) 0.02734
/*26 */         if (s2->low_delay == 0 && s2->next_picture_ptr) {                                             // (5) 0.05469
/*28 */             *picture = s2->next_picture_ptr->f;                                                       // (6) 0.04883
/*30 */             s2->next_picture_ptr = NULL;                                                              // (8) 0.04297
/*34 */             *data_size = sizeof(AVFrame);                                                             // (9) 0.04102
/*36 */         }                                                                                             // (20) 0.01562
/*38 */         return buf_size;                                                                              // (18) 0.02344
/*40 */     }                                                                                                 // (22) 0.007812
/*44 */     if (s2->flags & CODEC_FLAG_TRUNCATED) {                                                           // (7) 0.04297
/*46 */         int next = ff_mpeg1_find_frame_end(&s2->parse_context, buf, buf_size, NULL);                  // (2) 0.07031
/*50 */         if (ff_combine_frame(&s2->parse_context, next, (const uint8_t **)&buf, &buf_size) < 0)        // (0) 0.08594
/*52 */             return buf_size;                                                                          // (15) 0.03125
/*54 */     }                                                                                                 // (21) 0.007813
/*58 */     s2->codec_tag = avpriv_toupper4(avctx->codec_tag);                                                // 0.0
/*60 */     if (s->mpeg_enc_ctx_allocated == 0 && (   s2->codec_tag == AV_RL32("VCR2")                        // 0.0
/*62 */                                            || s2->codec_tag == AV_RL32("BW10")                        // 0.0
/*64 */                                           ))                                                          // 0.0
/*66 */         vcr2_init_sequence(avctx);                                                                    // 0.0
/*70 */     s->slice_count = 0;                                                                               // 0.0
/*74 */     if (avctx->extradata && !avctx->frame_number) {                                                   // 0.0
/*76 */         int ret = decode_chunks(avctx, picture, data_size, avctx->extradata, avctx->extradata_size);  // 0.0
/*78 */         if(*data_size) {                                                                              // 0.0
/*80 */             av_log(avctx, AV_LOG_ERROR, "picture in extradata\n");                                    // 0.0
/*82 */             *data_size = 0;                                                                           // 0.0
/*84 */         }                                                                                             // 0.0
/*86 */         if (ret < 0 && (avctx->err_recognition & AV_EF_EXPLODE))                                      // 0.0
/*88 */             return ret;                                                                               // 0.0
/*90 */     }                                                                                                 // 0.0
/*94 */     return decode_chunks(avctx, picture, data_size, buf, buf_size);                                   // 0.0
/*96 */ }                                                                                                     // 0.0
