// commit message FFmpeg@f6774f905f (target=1, prob=0.4932353, correct=False): mpegvideo: operate with pointers to AVFrames instead of whole structs
/*0   */ static int rv10_decode_packet(AVCodecContext *avctx, const uint8_t *buf,        // (4) 0.05582
/*2   */                               int buf_size, int buf_size2)                      // (1) 0.07505
/*4   */ {                                                                               // (20) 0.007747
/*6   */     RVDecContext *rv = avctx->priv_data;                                        // (12) 0.03444
/*8   */     MpegEncContext *s = &rv->m;                                                 // (13) 0.032
/*10  */     int mb_count, mb_pos, left, start_mb_x, active_bits_size, ret;              // (2) 0.07027
/*14  */     active_bits_size = buf_size * 8;                                            // (17) 0.02876
/*16  */     init_get_bits(&s->gb, buf, FFMAX(buf_size, buf_size2) * 8);                 // (3) 0.05648
/*18  */     if (s->codec_id == AV_CODEC_ID_RV10)                                        // (10) 0.04545
/*20  */         mb_count = rv10_decode_picture_header(s);                               // (8) 0.04735
/*22  */     else                                                                        // (21) 0.007482
/*24  */         mb_count = rv20_decode_picture_header(rv);                              // (6) 0.049
/*26  */     if (mb_count < 0) {                                                         // (19) 0.02244
/*28  */         av_log(s->avctx, AV_LOG_ERROR, "HEADER ERROR\n");                       // (5) 0.05398
/*30  */         return AVERROR_INVALIDDATA;                                             // (15) 0.03161
/*32  */     }                                                                           // (22) 0.007462
/*36  */     if (s->mb_x >= s->mb_width ||                                               // (14) 0.03172
/*38  */         s->mb_y >= s->mb_height) {                                              // (11) 0.0374
/*40  */         av_log(s->avctx, AV_LOG_ERROR, "POS ERROR %d %d\n", s->mb_x, s->mb_y);  // (0) 0.08212
/*42  */         return AVERROR_INVALIDDATA;                                             // (16) 0.03158
/*44  */     }                                                                           // (23) 0.007435
/*46  */     mb_pos = s->mb_y * s->mb_width + s->mb_x;                                   // (7) 0.04851
/*48  */     left   = s->mb_width * s->mb_height - mb_pos;                               // (9) 0.04588
/*50  */     if (mb_count > left) {                                                      // (18) 0.02429
/*52  */         av_log(s->avctx, AV_LOG_ERROR, "COUNT ERROR\n");                        // 0.0
/*54  */         return AVERROR_INVALIDDATA;                                             // 0.0
/*56  */     }                                                                           // 0.0
/*60  */     if ((s->mb_x == 0 && s->mb_y == 0) || s->current_picture_ptr == NULL) {     // 0.0
/*62  */         // FIXME write parser so we always have complete frames?                // 0.0
/*64  */         if (s->current_picture_ptr) {                                           // 0.0
/*66  */             ff_er_frame_end(&s->er);                                            // 0.0
/*68  */             ff_MPV_frame_end(s);                                                // 0.0
/*70  */             s->mb_x = s->mb_y = s->resync_mb_x = s->resync_mb_y = 0;            // 0.0
/*72  */         }                                                                       // 0.0
/*74  */         if ((ret = ff_MPV_frame_start(s, avctx)) < 0)                           // 0.0
/*76  */             return ret;                                                         // 0.0
/*78  */         ff_mpeg_er_frame_start(s);                                              // 0.0
/*80  */     } else {                                                                    // 0.0
/*82  */         if (s->current_picture_ptr->f.pict_type != s->pict_type) {              // 0.0
/*84  */             av_log(s->avctx, AV_LOG_ERROR, "Slice type mismatch\n");            // 0.0
/*86  */             return AVERROR_INVALIDDATA;                                         // 0.0
/*88  */         }                                                                       // 0.0
/*90  */     }                                                                           // 0.0
/*94  */     av_dlog(avctx, "qscale=%d\n", s->qscale);                                   // 0.0
/*98  */     /* default quantization values */                                           // 0.0
/*100 */     if (s->codec_id == AV_CODEC_ID_RV10) {                                      // 0.0
/*102 */         if (s->mb_y == 0)                                                       // 0.0
/*104 */             s->first_slice_line = 1;                                            // 0.0
/*106 */     } else {                                                                    // 0.0
/*108 */         s->first_slice_line = 1;                                                // 0.0
/*110 */         s->resync_mb_x      = s->mb_x;                                          // 0.0
/*112 */     }                                                                           // 0.0
/*114 */     start_mb_x     = s->mb_x;                                                   // 0.0
/*116 */     s->resync_mb_y = s->mb_y;                                                   // 0.0
/*118 */     if (s->h263_aic) {                                                          // 0.0
/*120 */         s->y_dc_scale_table =                                                   // 0.0
/*122 */         s->c_dc_scale_table = ff_aic_dc_scale_table;                            // 0.0
/*124 */     } else {                                                                    // 0.0
/*126 */         s->y_dc_scale_table =                                                   // 0.0
/*128 */         s->c_dc_scale_table = ff_mpeg1_dc_scale_table;                          // 0.0
/*130 */     }                                                                           // 0.0
/*134 */     if (s->modified_quant)                                                      // 0.0
/*136 */         s->chroma_qscale_table = ff_h263_chroma_qscale_table;                   // 0.0
/*140 */     ff_set_qscale(s, s->qscale);                                                // 0.0
/*144 */     s->rv10_first_dc_coded[0] = 0;                                              // 0.0
/*146 */     s->rv10_first_dc_coded[1] = 0;                                              // 0.0
/*148 */     s->rv10_first_dc_coded[2] = 0;                                              // 0.0
/*150 */     s->block_wrap[0] =                                                          // 0.0
/*152 */     s->block_wrap[1] =                                                          // 0.0
/*154 */     s->block_wrap[2] =                                                          // 0.0
/*156 */     s->block_wrap[3] = s->b8_stride;                                            // 0.0
/*158 */     s->block_wrap[4] =                                                          // 0.0
/*160 */     s->block_wrap[5] = s->mb_stride;                                            // 0.0
/*162 */     ff_init_block_index(s);                                                     // 0.0
/*166 */     /* decode each macroblock */                                                // 0.0
/*168 */     for (s->mb_num_left = mb_count; s->mb_num_left > 0; s->mb_num_left--) {     // 0.0
/*170 */         int ret;                                                                // 0.0
/*172 */         ff_update_block_index(s);                                               // 0.0
/*174 */         av_dlog(avctx, "**mb x=%d y=%d\n", s->mb_x, s->mb_y);                   // 0.0
/*178 */         s->mv_dir  = MV_DIR_FORWARD;                                            // 0.0
/*180 */         s->mv_type = MV_TYPE_16X16;                                             // 0.0
/*182 */         ret = ff_h263_decode_mb(s, s->block);                                   // 0.0
/*186 */         // Repeat the slice end check from ff_h263_decode_mb with our active    // 0.0
/*188 */         // bitstream size                                                       // 0.0
/*190 */         if (ret != SLICE_ERROR) {                                               // 0.0
/*192 */             int v = show_bits(&s->gb, 16);                                      // 0.0
/*196 */             if (get_bits_count(&s->gb) + 16 > active_bits_size)                 // 0.0
/*198 */                 v >>= get_bits_count(&s->gb) + 16 - active_bits_size;           // 0.0
/*202 */             if (!v)                                                             // 0.0
/*204 */                 ret = SLICE_END;                                                // 0.0
/*206 */         }                                                                       // 0.0
/*208 */         if (ret != SLICE_ERROR && active_bits_size < get_bits_count(&s->gb) &&  // 0.0
/*210 */             8 * buf_size2 >= get_bits_count(&s->gb)) {                          // 0.0
/*212 */             active_bits_size = buf_size2 * 8;                                   // 0.0
/*214 */             av_log(avctx, AV_LOG_DEBUG, "update size from %d to %d\n",          // 0.0
/*216 */                    8 * buf_size, active_bits_size);                             // 0.0
/*218 */             ret = SLICE_OK;                                                     // 0.0
/*220 */         }                                                                       // 0.0
/*224 */         if (ret == SLICE_ERROR || active_bits_size < get_bits_count(&s->gb)) {  // 0.0
/*226 */             av_log(s->avctx, AV_LOG_ERROR, "ERROR at MB %d %d\n", s->mb_x,      // 0.0
/*228 */                    s->mb_y);                                                    // 0.0
/*230 */             return AVERROR_INVALIDDATA;                                         // 0.0
/*232 */         }                                                                       // 0.0
/*234 */         if (s->pict_type != AV_PICTURE_TYPE_B)                                  // 0.0
/*236 */             ff_h263_update_motion_val(s);                                       // 0.0
/*238 */         ff_MPV_decode_mb(s, s->block);                                          // 0.0
/*240 */         if (s->loop_filter)                                                     // 0.0
/*242 */             ff_h263_loop_filter(s);                                             // 0.0
/*246 */         if (++s->mb_x == s->mb_width) {                                         // 0.0
/*248 */             s->mb_x = 0;                                                        // 0.0
/*250 */             s->mb_y++;                                                          // 0.0
/*252 */             ff_init_block_index(s);                                             // 0.0
/*254 */         }                                                                       // 0.0
/*256 */         if (s->mb_x == s->resync_mb_x)                                          // 0.0
/*258 */             s->first_slice_line = 0;                                            // 0.0
/*260 */         if (ret == SLICE_END)                                                   // 0.0
/*262 */             break;                                                              // 0.0
/*264 */     }                                                                           // 0.0
/*268 */     ff_er_add_slice(&s->er, start_mb_x, s->resync_mb_y, s->mb_x - 1, s->mb_y,   // 0.0
/*270 */                     ER_MB_END);                                                 // 0.0
/*274 */     return active_bits_size;                                                    // 0.0
/*276 */ }                                                                               // 0.0
