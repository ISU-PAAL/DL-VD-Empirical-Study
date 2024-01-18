// commit message FFmpeg@fbaf75b166 (target=1, prob=0.5606601, correct=True): h264: Use the correct croping values.
/*0   */ static int decode_frame(AVCodecContext *avctx, void *data,                                                             // (10) 0.03427
/*2   */                         int *got_frame, AVPacket *avpkt)                                                               // (0) 0.07025
/*4   */ {                                                                                                                      // (26) 0.001906
/*6   */     const uint8_t *buf = avpkt->data;                                                                                  // (12) 0.03228
/*8   */     int buf_size       = avpkt->size;                                                                                  // (9) 0.03798
/*10  */     H264Context *h     = avctx->priv_data;                                                                             // (8) 0.03869
/*12  */     AVFrame *pict      = data;                                                                                         // (15) 0.02851
/*14  */     int buf_index      = 0;                                                                                            // (16) 0.0285
/*16  */     Picture *out;                                                                                                      // (23) 0.01333
/*18  */     int i, out_idx;                                                                                                    // (22) 0.0209
/*20  */     int ret;                                                                                                           // (24) 0.01146
/*24  */     h->flags  = avctx->flags;                                                                                          // (20) 0.02476
/*28  */     /* end of stream, output what is still in the buffers */                                                           // (13) 0.0314
/*30  */     if (buf_size == 0) {                                                                                               // (21) 0.02282
/*32  */  out:                                                                                                                  // (25) 0.003821
/*36  */         h->cur_pic_ptr = NULL;                                                                                         // (11) 0.03232
/*38  */         h->first_field = 0;                                                                                            // (14) 0.02984
/*42  */         // FIXME factorize this with the output code below                                                             // (5) 0.05239
/*44  */         out     = h->delayed_pic[0];                                                                                   // (6) 0.04224
/*46  */         out_idx = 0;                                                                                                   // (18) 0.0266
/*48  */         for (i = 1;                                                                                                    // (19) 0.02477
/*50  */              h->delayed_pic[i] &&                                                                                      // (7) 0.04177
/*52  */              !h->delayed_pic[i]->f.key_frame &&                                                                        // (4) 0.05517
/*54  */              !h->delayed_pic[i]->mmco_reset;                                                                           // (3) 0.05526
/*56  */              i++)                                                                                                      // (17) 0.02675
/*58  */             if (h->delayed_pic[i]->poc < out->poc) {                                                                   // (1) 0.06076
/*60  */                 out     = h->delayed_pic[i];                                                                           // (2) 0.05695
/*62  */                 out_idx = i;                                                                                           // 0.0
/*64  */             }                                                                                                          // 0.0
/*68  */         for (i = out_idx; h->delayed_pic[i]; i++)                                                                      // 0.0
/*70  */             h->delayed_pic[i] = h->delayed_pic[i + 1];                                                                 // 0.0
/*74  */         if (out) {                                                                                                     // 0.0
/*76  */             out->reference &= ~DELAYED_PIC_REF;                                                                        // 0.0
/*78  */             ret = output_frame(h, pict, &out->f);                                                                      // 0.0
/*80  */             if (ret < 0)                                                                                               // 0.0
/*82  */                 return ret;                                                                                            // 0.0
/*84  */             *got_frame = 1;                                                                                            // 0.0
/*86  */         }                                                                                                              // 0.0
/*90  */         return buf_index;                                                                                              // 0.0
/*92  */     }                                                                                                                  // 0.0
/*94  */     if(h->is_avc && buf_size >= 9 && buf[0]==1 && buf[2]==0 && (buf[4]&0xFC)==0xFC && (buf[5]&0x1F) && buf[8]==0x67){  // 0.0
/*96  */         int cnt= buf[5]&0x1f;                                                                                          // 0.0
/*98  */         const uint8_t *p= buf+6;                                                                                       // 0.0
/*100 */         while(cnt--){                                                                                                  // 0.0
/*102 */             int nalsize= AV_RB16(p) + 2;                                                                               // 0.0
/*104 */             if(nalsize > buf_size - (p-buf) || p[2]!=0x67)                                                             // 0.0
/*106 */                 goto not_extra;                                                                                        // 0.0
/*108 */             p += nalsize;                                                                                              // 0.0
/*110 */         }                                                                                                              // 0.0
/*112 */         cnt = *(p++);                                                                                                  // 0.0
/*114 */         if(!cnt)                                                                                                       // 0.0
/*116 */             goto not_extra;                                                                                            // 0.0
/*118 */         while(cnt--){                                                                                                  // 0.0
/*120 */             int nalsize= AV_RB16(p) + 2;                                                                               // 0.0
/*122 */             if(nalsize > buf_size - (p-buf) || p[2]!=0x68)                                                             // 0.0
/*124 */                 goto not_extra;                                                                                        // 0.0
/*126 */             p += nalsize;                                                                                              // 0.0
/*128 */         }                                                                                                              // 0.0
/*132 */         return ff_h264_decode_extradata(h, buf, buf_size);                                                             // 0.0
/*134 */     }                                                                                                                  // 0.0
/*136 */ not_extra:                                                                                                             // 0.0
/*140 */     buf_index = decode_nal_units(h, buf, buf_size, 0);                                                                 // 0.0
/*142 */     if (buf_index < 0)                                                                                                 // 0.0
/*144 */         return -1;                                                                                                     // 0.0
/*148 */     if (!h->cur_pic_ptr && h->nal_unit_type == NAL_END_SEQUENCE) {                                                     // 0.0
/*150 */         av_assert0(buf_index <= buf_size);                                                                             // 0.0
/*152 */         goto out;                                                                                                      // 0.0
/*154 */     }                                                                                                                  // 0.0
/*158 */     if (!(avctx->flags2 & CODEC_FLAG2_CHUNKS) && !h->cur_pic_ptr) {                                                    // 0.0
/*160 */         if (avctx->skip_frame >= AVDISCARD_NONREF ||                                                                   // 0.0
/*162 */             buf_size >= 4 && !memcmp("Q264", buf, 4))                                                                  // 0.0
/*164 */             return buf_size;                                                                                           // 0.0
/*166 */         av_log(avctx, AV_LOG_ERROR, "no frame!\n");                                                                    // 0.0
/*168 */         return -1;                                                                                                     // 0.0
/*170 */     }                                                                                                                  // 0.0
/*174 */     if (!(avctx->flags2 & CODEC_FLAG2_CHUNKS) ||                                                                       // 0.0
/*176 */         (h->mb_y >= h->mb_height && h->mb_height)) {                                                                   // 0.0
/*178 */         if (avctx->flags2 & CODEC_FLAG2_CHUNKS)                                                                        // 0.0
/*180 */             decode_postinit(h, 1);                                                                                     // 0.0
/*184 */         field_end(h, 0);                                                                                               // 0.0
/*188 */         /* Wait for second field. */                                                                                   // 0.0
/*190 */         *got_frame = 0;                                                                                                // 0.0
/*192 */         if (h->next_output_pic && (h->next_output_pic->sync || h->sync>1)) {                                           // 0.0
/*194 */             ret = output_frame(h, pict, &h->next_output_pic->f);                                                       // 0.0
/*196 */             if (ret < 0)                                                                                               // 0.0
/*198 */                 return ret;                                                                                            // 0.0
/*200 */             *got_frame = 1;                                                                                            // 0.0
/*202 */             if (CONFIG_MPEGVIDEO) {                                                                                    // 0.0
/*204 */                 ff_print_debug_info2(h->avctx, h->next_output_pic, pict, h->er.mbskip_table,                           // 0.0
/*206 */                                     &h->low_delay,                                                                     // 0.0
/*208 */                                     h->mb_width, h->mb_height, h->mb_stride, 1);                                       // 0.0
/*210 */             }                                                                                                          // 0.0
/*212 */         }                                                                                                              // 0.0
/*214 */     }                                                                                                                  // 0.0
/*218 */     assert(pict->data[0] || !*got_frame);                                                                              // 0.0
/*222 */     return get_consumed_bytes(buf_index, buf_size);                                                                    // 0.0
/*224 */ }                                                                                                                      // 0.0
