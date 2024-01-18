// commit message FFmpeg@f6774f905f (target=1, prob=0.5546686, correct=True): mpegvideo: operate with pointers to AVFrames instead of whole structs
/*0   */ static int rv10_decode_frame(AVCodecContext *avctx, void *data, int *got_frame,        // (3) 0.05667
/*2   */                              AVPacket *avpkt)                                          // (0) 0.07031
/*4   */ {                                                                                      // (27) 0.001955
/*6   */     const uint8_t *buf = avpkt->data;                                                  // (14) 0.0332
/*8   */     int buf_size       = avpkt->size;                                                  // (8) 0.03906
/*10  */     MpegEncContext *s = avctx->priv_data;                                              // (12) 0.0332
/*12  */     AVFrame *pict = data;                                                              // (19) 0.01954
/*14  */     int i, ret;                                                                        // (21) 0.01565
/*16  */     int slice_count;                                                                   // (23) 0.01563
/*18  */     const uint8_t *slices_hdr = NULL;                                                  // (9) 0.03516
/*22  */     av_dlog(avctx, "*****frame %d size=%d\n", avctx->frame_number, buf_size);          // (2) 0.0664
/*26  */     /* no supplementary picture */                                                     // (22) 0.01563
/*28  */     if (buf_size == 0) {                                                               // (18) 0.02343
/*30  */         return 0;                                                                      // (20) 0.01953
/*32  */     }                                                                                  // (26) 0.007811
/*36  */     if (!avctx->slice_count) {                                                         // (16) 0.02539
/*38  */         slice_count = (*buf++) + 1;                                                    // (13) 0.0332
/*40  */         buf_size--;                                                                    // (17) 0.02343
/*44  */         if (!slice_count || buf_size <= 8 * slice_count) {                             // (4) 0.04687
/*46  */             av_log(avctx, AV_LOG_ERROR, "Invalid slice count: %d.\n",                  // (1) 0.06835
/*48  */                    slice_count);                                                       // (5) 0.04296
/*50  */             return AVERROR_INVALIDDATA;                                                // (7) 0.04101
/*52  */         }                                                                              // (24) 0.01562
/*56  */         slices_hdr = buf + 4;                                                          // (15) 0.03125
/*58  */         buf       += 8 * slice_count;                                                  // (6) 0.04101
/*60  */         buf_size  -= 8 * slice_count;                                                  // (11) 0.03515
/*62  */     } else                                                                             // (25) 0.009764
/*64  */         slice_count = avctx->slice_count;                                              // (10) 0.03515
/*68  */     for (i = 0; i < slice_count; i++) {                                                // 0.0
/*70  */         unsigned offset = get_slice_offset(avctx, slices_hdr, i);                      // 0.0
/*72  */         int size, size2;                                                               // 0.0
/*76  */         if (offset >= buf_size)                                                        // 0.0
/*78  */             return AVERROR_INVALIDDATA;                                                // 0.0
/*82  */         if (i + 1 == slice_count)                                                      // 0.0
/*84  */             size = buf_size - offset;                                                  // 0.0
/*86  */         else                                                                           // 0.0
/*88  */             size = get_slice_offset(avctx, slices_hdr, i + 1) - offset;                // 0.0
/*92  */         if (i + 2 >= slice_count)                                                      // 0.0
/*94  */             size2 = buf_size - offset;                                                 // 0.0
/*96  */         else                                                                           // 0.0
/*98  */             size2 = get_slice_offset(avctx, slices_hdr, i + 2) - offset;               // 0.0
/*102 */         if (size <= 0 || size2 <= 0 ||                                                 // 0.0
/*104 */             offset + FFMAX(size, size2) > buf_size)                                    // 0.0
/*106 */             return AVERROR_INVALIDDATA;                                                // 0.0
/*110 */         if ((ret = rv10_decode_packet(avctx, buf + offset, size, size2)) < 0)          // 0.0
/*112 */             return ret;                                                                // 0.0
/*116 */         if (ret > 8 * size)                                                            // 0.0
/*118 */             i++;                                                                       // 0.0
/*120 */     }                                                                                  // 0.0
/*124 */     if (s->current_picture_ptr != NULL && s->mb_y >= s->mb_height) {                   // 0.0
/*126 */         ff_er_frame_end(&s->er);                                                       // 0.0
/*128 */         ff_MPV_frame_end(s);                                                           // 0.0
/*132 */         if (s->pict_type == AV_PICTURE_TYPE_B || s->low_delay) {                       // 0.0
/*134 */             if ((ret = av_frame_ref(pict, &s->current_picture_ptr->f)) < 0)            // 0.0
/*136 */                 return ret;                                                            // 0.0
/*138 */             ff_print_debug_info(s, s->current_picture_ptr);                            // 0.0
/*140 */         } else if (s->last_picture_ptr != NULL) {                                      // 0.0
/*142 */             if ((ret = av_frame_ref(pict, &s->last_picture_ptr->f)) < 0)               // 0.0
/*144 */                 return ret;                                                            // 0.0
/*146 */             ff_print_debug_info(s, s->last_picture_ptr);                               // 0.0
/*148 */         }                                                                              // 0.0
/*152 */         if (s->last_picture_ptr || s->low_delay) {                                     // 0.0
/*154 */             *got_frame = 1;                                                            // 0.0
/*156 */         }                                                                              // 0.0
/*160 */         // so we can detect if frame_end was not called (find some nicer solution...)  // 0.0
/*162 */         s->current_picture_ptr = NULL;                                                 // 0.0
/*164 */     }                                                                                  // 0.0
/*168 */     return avpkt->size;                                                                // 0.0
/*170 */ }                                                                                      // 0.0
