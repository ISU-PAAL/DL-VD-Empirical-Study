// commit message FFmpeg@87e302bfd8 (target=0, prob=0.49331912, correct=True): remove unused hack which set AVCodecContext frame_number to pic timestamp
/*0   */ static int svq3_decode_frame(AVCodecContext *avctx,                                                              // (8) 0.03711
/*2   */                              void *data, int *data_size,                                                         // (0) 0.07421
/*4   */                              AVPacket *avpkt)                                                                    // (1) 0.07031
/*6   */ {                                                                                                                // (24) 0.001958
/*8   */     const uint8_t *buf = avpkt->data;                                                                            // (13) 0.0332
/*10  */     int buf_size = avpkt->size;                                                                                  // (16) 0.02734
/*12  */     MpegEncContext *const s = avctx->priv_data;                                                                  // (11) 0.03516
/*14  */     H264Context *const h = avctx->priv_data;                                                                     // (12) 0.03321
/*16  */     int m, mb_type;                                                                                              // (18) 0.02148
/*20  */     /* special case for last picture */                                                                          // (20) 0.01953
/*22  */     if (buf_size == 0) {                                                                                         // (17) 0.02344
/*24  */         if (s->next_picture_ptr && !s->low_delay) {                                                              // (3) 0.04883
/*26  */             *(AVFrame *) data = *(AVFrame *) &s->next_picture;                                                   // (2) 0.05859
/*28  */             s->next_picture_ptr = NULL;                                                                          // (7) 0.04101
/*30  */             *data_size = sizeof(AVFrame);                                                                        // (6) 0.04101
/*32  */         }                                                                                                        // (22) 0.01562
/*34  */         return 0;                                                                                                // (21) 0.01953
/*36  */     }                                                                                                            // (23) 0.007812
/*40  */     init_get_bits (&s->gb, buf, 8*buf_size);                                                                     // (5) 0.04101
/*44  */     s->mb_x = s->mb_y = h->mb_xy = 0;                                                                            // (4) 0.04492
/*48  */     if (svq3_decode_slice_header(h))                                                                             // (10) 0.03516
/*50  */         return -1;                                                                                               // (19) 0.02148
/*54  */     s->pict_type = h->slice_type;                                                                                // (15) 0.0293
/*56  */     s->picture_number = h->slice_num;                                                                            // (14) 0.0293
/*60  */     if (avctx->debug&FF_DEBUG_PICT_INFO){                                                                        // (9) 0.03711
/*62  */         av_log(h->s.avctx, AV_LOG_DEBUG, "%c hpel:%d, tpel:%d aqp:%d qp:%d, slice_num:%02X\n",                   // 0.0
/*64  */                av_get_pict_type_char(s->pict_type), h->halfpel_flag, h->thirdpel_flag,                           // 0.0
/*66  */                s->adaptive_quant, s->qscale, h->slice_num);                                                      // 0.0
/*68  */     }                                                                                                            // 0.0
/*72  */     /* for hurry_up == 5 */                                                                                      // 0.0
/*74  */     s->current_picture.pict_type = s->pict_type;                                                                 // 0.0
/*76  */     s->current_picture.key_frame = (s->pict_type == FF_I_TYPE);                                                  // 0.0
/*80  */     /* Skip B-frames if we do not have reference frames. */                                                      // 0.0
/*82  */     if (s->last_picture_ptr == NULL && s->pict_type == FF_B_TYPE)                                                // 0.0
/*84  */         return 0;                                                                                                // 0.0
/*86  */     /* Skip B-frames if we are in a hurry. */                                                                    // 0.0
/*88  */     if (avctx->hurry_up && s->pict_type == FF_B_TYPE)                                                            // 0.0
/*90  */         return 0;                                                                                                // 0.0
/*92  */     /* Skip everything if we are in a hurry >= 5. */                                                             // 0.0
/*94  */     if (avctx->hurry_up >= 5)                                                                                    // 0.0
/*96  */         return 0;                                                                                                // 0.0
/*98  */     if (  (avctx->skip_frame >= AVDISCARD_NONREF && s->pict_type == FF_B_TYPE)                                   // 0.0
/*100 */         ||(avctx->skip_frame >= AVDISCARD_NONKEY && s->pict_type != FF_I_TYPE)                                   // 0.0
/*102 */         || avctx->skip_frame >= AVDISCARD_ALL)                                                                   // 0.0
/*104 */         return 0;                                                                                                // 0.0
/*108 */     if (s->next_p_frame_damaged) {                                                                               // 0.0
/*110 */         if (s->pict_type == FF_B_TYPE)                                                                           // 0.0
/*112 */             return 0;                                                                                            // 0.0
/*114 */         else                                                                                                     // 0.0
/*116 */             s->next_p_frame_damaged = 0;                                                                         // 0.0
/*118 */     }                                                                                                            // 0.0
/*122 */     if (frame_start(h) < 0)                                                                                      // 0.0
/*124 */         return -1;                                                                                               // 0.0
/*128 */     if (s->pict_type == FF_B_TYPE) {                                                                             // 0.0
/*130 */         h->frame_num_offset = (h->slice_num - h->prev_frame_num);                                                // 0.0
/*134 */         if (h->frame_num_offset < 0) {                                                                           // 0.0
/*136 */             h->frame_num_offset += 256;                                                                          // 0.0
/*138 */         }                                                                                                        // 0.0
/*140 */         if (h->frame_num_offset == 0 || h->frame_num_offset >= h->prev_frame_num_offset) {                       // 0.0
/*142 */             av_log(h->s.avctx, AV_LOG_ERROR, "error in B-frame picture id\n");                                   // 0.0
/*144 */             return -1;                                                                                           // 0.0
/*146 */         }                                                                                                        // 0.0
/*148 */     } else {                                                                                                     // 0.0
/*150 */         h->prev_frame_num = h->frame_num;                                                                        // 0.0
/*152 */         h->frame_num = h->slice_num;                                                                             // 0.0
/*154 */         h->prev_frame_num_offset = (h->frame_num - h->prev_frame_num);                                           // 0.0
/*158 */         if (h->prev_frame_num_offset < 0) {                                                                      // 0.0
/*160 */             h->prev_frame_num_offset += 256;                                                                     // 0.0
/*162 */         }                                                                                                        // 0.0
/*164 */     }                                                                                                            // 0.0
/*168 */     for (m = 0; m < 2; m++){                                                                                     // 0.0
/*170 */         int i;                                                                                                   // 0.0
/*172 */         for (i = 0; i < 4; i++){                                                                                 // 0.0
/*174 */             int j;                                                                                               // 0.0
/*176 */             for (j = -1; j < 4; j++)                                                                             // 0.0
/*178 */                 h->ref_cache[m][scan8[0] + 8*i + j]= 1;                                                          // 0.0
/*180 */             if (i < 3)                                                                                           // 0.0
/*182 */                 h->ref_cache[m][scan8[0] + 8*i + j]= PART_NOT_AVAILABLE;                                         // 0.0
/*184 */         }                                                                                                        // 0.0
/*186 */     }                                                                                                            // 0.0
/*190 */     for (s->mb_y = 0; s->mb_y < s->mb_height; s->mb_y++) {                                                       // 0.0
/*192 */         for (s->mb_x = 0; s->mb_x < s->mb_width; s->mb_x++) {                                                    // 0.0
/*194 */             h->mb_xy = s->mb_x + s->mb_y*s->mb_stride;                                                           // 0.0
/*198 */             if ( (get_bits_count(&s->gb) + 7) >= s->gb.size_in_bits &&                                           // 0.0
/*200 */                 ((get_bits_count(&s->gb) & 7) == 0 || show_bits(&s->gb, (-get_bits_count(&s->gb) & 7)) == 0)) {  // 0.0
/*204 */                 skip_bits(&s->gb, h->next_slice_index - get_bits_count(&s->gb));                                 // 0.0
/*206 */                 s->gb.size_in_bits = 8*buf_size;                                                                 // 0.0
/*210 */                 if (svq3_decode_slice_header(h))                                                                 // 0.0
/*212 */                     return -1;                                                                                   // 0.0
/*216 */                 /* TODO: support s->mb_skip_run */                                                               // 0.0
/*218 */             }                                                                                                    // 0.0
/*222 */             mb_type = svq3_get_ue_golomb(&s->gb);                                                                // 0.0
/*226 */             if (s->pict_type == FF_I_TYPE) {                                                                     // 0.0
/*228 */                 mb_type += 8;                                                                                    // 0.0
/*230 */             } else if (s->pict_type == FF_B_TYPE && mb_type >= 4) {                                              // 0.0
/*232 */                 mb_type += 4;                                                                                    // 0.0
/*234 */             }                                                                                                    // 0.0
/*236 */             if (mb_type > 33 || svq3_decode_mb(h, mb_type)) {                                                    // 0.0
/*238 */                 av_log(h->s.avctx, AV_LOG_ERROR, "error while decoding MB %d %d\n", s->mb_x, s->mb_y);           // 0.0
/*240 */                 return -1;                                                                                       // 0.0
/*242 */             }                                                                                                    // 0.0
/*246 */             if (mb_type != 0) {                                                                                  // 0.0
/*248 */                 hl_decode_mb (h);                                                                                // 0.0
/*250 */             }                                                                                                    // 0.0
/*254 */             if (s->pict_type != FF_B_TYPE && !s->low_delay) {                                                    // 0.0
/*256 */                 s->current_picture.mb_type[s->mb_x + s->mb_y*s->mb_stride] =                                     // 0.0
/*258 */                     (s->pict_type == FF_P_TYPE && mb_type < 8) ? (mb_type - 1) : -1;                             // 0.0
/*260 */             }                                                                                                    // 0.0
/*262 */         }                                                                                                        // 0.0
/*266 */         ff_draw_horiz_band(s, 16*s->mb_y, 16);                                                                   // 0.0
/*268 */     }                                                                                                            // 0.0
/*272 */     MPV_frame_end(s);                                                                                            // 0.0
/*276 */     if (s->pict_type == FF_B_TYPE || s->low_delay) {                                                             // 0.0
/*278 */         *(AVFrame *) data = *(AVFrame *) &s->current_picture;                                                    // 0.0
/*280 */     } else {                                                                                                     // 0.0
/*282 */         *(AVFrame *) data = *(AVFrame *) &s->last_picture;                                                       // 0.0
/*284 */     }                                                                                                            // 0.0
/*288 */     avctx->frame_number = s->picture_number - 1;                                                                 // 0.0
/*292 */     /* Do not output the last pic after seeking. */                                                              // 0.0
/*294 */     if (s->last_picture_ptr || s->low_delay) {                                                                   // 0.0
/*296 */         *data_size = sizeof(AVFrame);                                                                            // 0.0
/*298 */     }                                                                                                            // 0.0
/*302 */     return buf_size;                                                                                             // 0.0
/*304 */ }                                                                                                                // 0.0
