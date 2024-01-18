// commit message FFmpeg@5c2fb561d9 (target=0, prob=0.5170674, correct=False): h264: add H264_ prefix to the NAL unit types
/*0   */ static int h264_decode_frame(AVCodecContext *avctx, void *data,                      // (4) 0.04298
/*2   */                              int *got_frame, AVPacket *avpkt)                        // (0) 0.08203
/*4   */ {                                                                                    // (27) 0.001954
/*6   */     const uint8_t *buf = avpkt->data;                                                // (10) 0.0332
/*8   */     int buf_size       = avpkt->size;                                                // (8) 0.03906
/*10  */     H264Context *h     = avctx->priv_data;                                           // (7) 0.03906
/*12  */     AVFrame *pict      = data;                                                       // (13) 0.0293
/*14  */     int buf_index      = 0;                                                          // (15) 0.02929
/*16  */     int ret;                                                                         // (25) 0.01172
/*18  */     const uint8_t *new_extradata;                                                    // (14) 0.02929
/*20  */     int new_extradata_size;                                                          // (21) 0.02344
/*24  */     h->flags = avctx->flags;                                                         // (22) 0.02344
/*26  */     h->setup_finished = 0;                                                           // (24) 0.02148
/*30  */     /* end of stream, output what is still in the buffers */                         // (12) 0.03125
/*32  */ out:                                                                                 // (26) 0.003906
/*34  */     if (buf_size == 0) {                                                             // (23) 0.02344
/*36  */         H264Picture *out;                                                            // (19) 0.02539
/*38  */         int i, out_idx;                                                              // (16) 0.02929
/*42  */         h->cur_pic_ptr = NULL;                                                       // (11) 0.0332
/*46  */         // FIXME factorize this with the output code below                           // (9) 0.03517
/*48  */         out     = h->delayed_pic[0];                                                 // (5) 0.04297
/*50  */         out_idx = 0;                                                                 // (17) 0.02734
/*52  */         for (i = 1;                                                                  // (20) 0.02539
/*54  */              h->delayed_pic[i] &&                                                    // (6) 0.04297
/*56  */              !h->delayed_pic[i]->f->key_frame &&                                     // (2) 0.05664
/*58  */              !h->delayed_pic[i]->mmco_reset;                                         // (3) 0.05468
/*60  */              i++)                                                                    // (18) 0.02734
/*62  */             if (h->delayed_pic[i]->poc < out->poc) {                                 // (1) 0.0625
/*64  */                 out     = h->delayed_pic[i];                                         // 0.0
/*66  */                 out_idx = i;                                                         // 0.0
/*68  */             }                                                                        // 0.0
/*72  */         for (i = out_idx; h->delayed_pic[i]; i++)                                    // 0.0
/*74  */             h->delayed_pic[i] = h->delayed_pic[i + 1];                               // 0.0
/*78  */         if (out) {                                                                   // 0.0
/*80  */             ret = output_frame(h, pict, out->f);                                     // 0.0
/*82  */             if (ret < 0)                                                             // 0.0
/*84  */                 return ret;                                                          // 0.0
/*86  */             *got_frame = 1;                                                          // 0.0
/*88  */         }                                                                            // 0.0
/*92  */         return buf_index;                                                            // 0.0
/*94  */     }                                                                                // 0.0
/*98  */     new_extradata_size = 0;                                                          // 0.0
/*100 */     new_extradata = av_packet_get_side_data(avpkt, AV_PKT_DATA_NEW_EXTRADATA,        // 0.0
/*102 */                                             &new_extradata_size);                    // 0.0
/*104 */     if (new_extradata_size > 0 && new_extradata) {                                   // 0.0
/*106 */         ret = ff_h264_decode_extradata(new_extradata, new_extradata_size,            // 0.0
/*108 */                                        &h->ps, &h->is_avc, &h->nal_length_size,      // 0.0
/*110 */                                        avctx->err_recognition, avctx);               // 0.0
/*112 */         if (ret < 0)                                                                 // 0.0
/*114 */             return ret;                                                              // 0.0
/*116 */     }                                                                                // 0.0
/*120 */     buf_index = decode_nal_units(h, buf, buf_size);                                  // 0.0
/*122 */     if (buf_index < 0)                                                               // 0.0
/*124 */         return AVERROR_INVALIDDATA;                                                  // 0.0
/*128 */     if (!h->cur_pic_ptr && h->nal_unit_type == NAL_END_SEQUENCE) {                   // 0.0
/*130 */         buf_size = 0;                                                                // 0.0
/*132 */         goto out;                                                                    // 0.0
/*134 */     }                                                                                // 0.0
/*138 */     if (!(avctx->flags2 & AV_CODEC_FLAG2_CHUNKS) && !h->cur_pic_ptr) {               // 0.0
/*140 */         if (avctx->skip_frame >= AVDISCARD_NONREF)                                   // 0.0
/*142 */             return 0;                                                                // 0.0
/*144 */         av_log(avctx, AV_LOG_ERROR, "no frame!\n");                                  // 0.0
/*146 */         return AVERROR_INVALIDDATA;                                                  // 0.0
/*148 */     }                                                                                // 0.0
/*152 */     if (!(avctx->flags2 & AV_CODEC_FLAG2_CHUNKS) ||                                  // 0.0
/*154 */         (h->mb_y >= h->mb_height && h->mb_height)) {                                 // 0.0
/*156 */         if (avctx->flags2 & AV_CODEC_FLAG2_CHUNKS)                                   // 0.0
/*158 */             decode_postinit(h, 1);                                                   // 0.0
/*162 */         ff_h264_field_end(h, &h->slice_ctx[0], 0);                                   // 0.0
/*166 */         *got_frame = 0;                                                              // 0.0
/*168 */         if (h->next_output_pic && ((avctx->flags & AV_CODEC_FLAG_OUTPUT_CORRUPT) ||  // 0.0
/*170 */                                    h->next_output_pic->recovered)) {                 // 0.0
/*172 */             if (!h->next_output_pic->recovered)                                      // 0.0
/*174 */                 h->next_output_pic->f->flags |= AV_FRAME_FLAG_CORRUPT;               // 0.0
/*178 */             ret = output_frame(h, pict, h->next_output_pic->f);                      // 0.0
/*180 */             if (ret < 0)                                                             // 0.0
/*182 */                 return ret;                                                          // 0.0
/*184 */             *got_frame = 1;                                                          // 0.0
/*186 */         }                                                                            // 0.0
/*188 */     }                                                                                // 0.0
/*192 */     assert(pict->buf[0] || !*got_frame);                                             // 0.0
/*196 */     return get_consumed_bytes(buf_index, buf_size);                                  // 0.0
/*198 */ }                                                                                    // 0.0
