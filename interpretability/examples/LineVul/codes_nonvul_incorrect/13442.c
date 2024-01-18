// commit message FFmpeg@d86d7b2486 (target=0, prob=0.7307038, correct=False): avcodec/mjpegdec: Fix negative shift
/*0   */ static int ljpeg_decode_rgb_scan(MJpegDecodeContext *s, int nb_components, int predictor, int point_transform)  // (1) 0.07341
/*2   */ {                                                                                                               // (22) 0.00203
/*4   */     int i, mb_x, mb_y;                                                                                          // (15) 0.03121
/*6   */     uint16_t (*buffer)[4];                                                                                      // (21) 0.02343
/*8   */     int left[4], top[4], topleft[4];                                                                            // (11) 0.03504
/*10  */     const int linesize = s->linesize[0];                                                                        // (17) 0.0292
/*12  */     const int mask     = ((1 << s->bits) - 1) << point_transform;                                               // (6) 0.05069
/*14  */     int resync_mb_y = 0;                                                                                        // (19) 0.02529
/*16  */     int resync_mb_x = 0;                                                                                        // (20) 0.02529
/*20  */     if (s->nb_components != 3 && s->nb_components != 4)                                                         // (8) 0.04475
/*22  */         return AVERROR_INVALIDDATA;                                                                             // (14) 0.03307
/*24  */     if (s->v_max != 1 || s->h_max != 1 || !s->lossless)                                                         // (5) 0.05253
/*26  */         return AVERROR_INVALIDDATA;                                                                             // (13) 0.0331
/*32  */     s->restart_count = s->restart_interval;                                                                     // (10) 0.03509
/*36  */     av_fast_malloc(&s->ljpeg_buffer, &s->ljpeg_buffer_size,                                                     // (3) 0.05678
/*38  */                    (unsigned)s->mb_width * 4 * sizeof(s->ljpeg_buffer[0][0]));                                  // (0) 0.08563
/*40  */     buffer = s->ljpeg_buffer;                                                                                   // (18) 0.02543
/*44  */     for (i = 0; i < 4; i++)                                                                                     // (16) 0.02968
/*46  */         buffer[0][i] = 1 << (s->bits - 1);                                                                      // (7) 0.04483
/*50  */     for (mb_y = 0; mb_y < s->mb_height; mb_y++) {                                                               // (4) 0.05455
/*52  */         uint8_t *ptr = s->picture_ptr->data[0] + (linesize * mb_y);                                             // (2) 0.06617
/*56  */         if (s->interlaced && s->bottom_field)                                                                   // (9) 0.0409
/*58  */             ptr += linesize >> 1;                                                                               // (12) 0.03502
/*62  */         for (i = 0; i < 4; i++)                                                                                 // 0.0
/*64  */             top[i] = left[i] = topleft[i] = buffer[0][i];                                                       // 0.0
/*68  */         for (mb_x = 0; mb_x < s->mb_width; mb_x++) {                                                            // 0.0
/*70  */             int modified_predictor = predictor;                                                                 // 0.0
/*74  */             if (s->restart_interval && !s->restart_count){                                                      // 0.0
/*76  */                 s->restart_count = s->restart_interval;                                                         // 0.0
/*78  */                 resync_mb_x = mb_x;                                                                             // 0.0
/*80  */                 resync_mb_y = mb_y;                                                                             // 0.0
/*82  */                 for(i=0; i<4; i++)                                                                              // 0.0
/*84  */                     top[i] = left[i]= topleft[i]= 1 << (s->bits - 1);                                           // 0.0
/*86  */             }                                                                                                   // 0.0
/*88  */             if (mb_y == resync_mb_y || mb_y == resync_mb_y+1 && mb_x < resync_mb_x || !mb_x)                    // 0.0
/*90  */                 modified_predictor = 1;                                                                         // 0.0
/*94  */             for (i=0;i<nb_components;i++) {                                                                     // 0.0
/*96  */                 int pred, dc;                                                                                   // 0.0
/*100 */                 topleft[i] = top[i];                                                                            // 0.0
/*102 */                 top[i]     = buffer[mb_x][i];                                                                   // 0.0
/*106 */                 PREDICT(pred, topleft[i], top[i], left[i], modified_predictor);                                 // 0.0
/*110 */                 dc = mjpeg_decode_dc(s, s->dc_index[i]);                                                        // 0.0
/*112 */                 if(dc == 0xFFFFF)                                                                               // 0.0
/*114 */                     return -1;                                                                                  // 0.0
/*118 */                 left[i] = buffer[mb_x][i] =                                                                     // 0.0
/*120 */                     mask & (pred + (dc << point_transform));                                                    // 0.0
/*122 */             }                                                                                                   // 0.0
/*126 */             if (s->restart_interval && !--s->restart_count) {                                                   // 0.0
/*128 */                 align_get_bits(&s->gb);                                                                         // 0.0
/*130 */                 skip_bits(&s->gb, 16); /* skip RSTn */                                                          // 0.0
/*132 */             }                                                                                                   // 0.0
/*134 */         }                                                                                                       // 0.0
/*136 */         if (s->rct && s->nb_components == 4) {                                                                  // 0.0
/*138 */             for (mb_x = 0; mb_x < s->mb_width; mb_x++) {                                                        // 0.0
/*140 */                 ptr[4*mb_x + 2] = buffer[mb_x][0] - ((buffer[mb_x][1] + buffer[mb_x][2] - 0x200) >> 2);         // 0.0
/*142 */                 ptr[4*mb_x + 1] = buffer[mb_x][1] + ptr[4*mb_x + 2];                                            // 0.0
/*144 */                 ptr[4*mb_x + 3] = buffer[mb_x][2] + ptr[4*mb_x + 2];                                            // 0.0
/*146 */                 ptr[4*mb_x + 0] = buffer[mb_x][3];                                                              // 0.0
/*148 */             }                                                                                                   // 0.0
/*150 */         } else if (s->nb_components == 4) {                                                                     // 0.0
/*152 */             for(i=0; i<nb_components; i++) {                                                                    // 0.0
/*154 */                 int c= s->comp_index[i];                                                                        // 0.0
/*156 */                 if (s->bits <= 8) {                                                                             // 0.0
/*158 */                     for(mb_x = 0; mb_x < s->mb_width; mb_x++) {                                                 // 0.0
/*160 */                         ptr[4*mb_x+3-c] = buffer[mb_x][i];                                                      // 0.0
/*162 */                     }                                                                                           // 0.0
/*164 */                 } else if(s->bits == 9) {                                                                       // 0.0
/*166 */                     return AVERROR_PATCHWELCOME;                                                                // 0.0
/*168 */                 } else {                                                                                        // 0.0
/*170 */                     for(mb_x = 0; mb_x < s->mb_width; mb_x++) {                                                 // 0.0
/*172 */                         ((uint16_t*)ptr)[4*mb_x+c] = buffer[mb_x][i];                                           // 0.0
/*174 */                     }                                                                                           // 0.0
/*176 */                 }                                                                                               // 0.0
/*178 */             }                                                                                                   // 0.0
/*180 */         } else if (s->rct) {                                                                                    // 0.0
/*182 */             for (mb_x = 0; mb_x < s->mb_width; mb_x++) {                                                        // 0.0
/*184 */                 ptr[3*mb_x + 1] = buffer[mb_x][0] - ((buffer[mb_x][1] + buffer[mb_x][2] - 0x200) >> 2);         // 0.0
/*186 */                 ptr[3*mb_x + 0] = buffer[mb_x][1] + ptr[3*mb_x + 1];                                            // 0.0
/*188 */                 ptr[3*mb_x + 2] = buffer[mb_x][2] + ptr[3*mb_x + 1];                                            // 0.0
/*190 */             }                                                                                                   // 0.0
/*192 */         } else if (s->pegasus_rct) {                                                                            // 0.0
/*194 */             for (mb_x = 0; mb_x < s->mb_width; mb_x++) {                                                        // 0.0
/*196 */                 ptr[3*mb_x + 1] = buffer[mb_x][0] - ((buffer[mb_x][1] + buffer[mb_x][2]) >> 2);                 // 0.0
/*198 */                 ptr[3*mb_x + 0] = buffer[mb_x][1] + ptr[3*mb_x + 1];                                            // 0.0
/*200 */                 ptr[3*mb_x + 2] = buffer[mb_x][2] + ptr[3*mb_x + 1];                                            // 0.0
/*202 */             }                                                                                                   // 0.0
/*204 */         } else {                                                                                                // 0.0
/*206 */             for(i=0; i<nb_components; i++) {                                                                    // 0.0
/*208 */                 int c= s->comp_index[i];                                                                        // 0.0
/*210 */                 if (s->bits <= 8) {                                                                             // 0.0
/*212 */                     for(mb_x = 0; mb_x < s->mb_width; mb_x++) {                                                 // 0.0
/*214 */                         ptr[3*mb_x+2-c] = buffer[mb_x][i];                                                      // 0.0
/*216 */                     }                                                                                           // 0.0
/*218 */                 } else if(s->bits == 9) {                                                                       // 0.0
/*220 */                     return AVERROR_PATCHWELCOME;                                                                // 0.0
/*222 */                 } else {                                                                                        // 0.0
/*224 */                     for(mb_x = 0; mb_x < s->mb_width; mb_x++) {                                                 // 0.0
/*226 */                         ((uint16_t*)ptr)[3*mb_x+2-c] = buffer[mb_x][i];                                         // 0.0
/*228 */                     }                                                                                           // 0.0
/*230 */                 }                                                                                               // 0.0
/*232 */             }                                                                                                   // 0.0
/*234 */         }                                                                                                       // 0.0
/*236 */     }                                                                                                           // 0.0
/*238 */     return 0;                                                                                                   // 0.0
/*240 */ }                                                                                                               // 0.0
