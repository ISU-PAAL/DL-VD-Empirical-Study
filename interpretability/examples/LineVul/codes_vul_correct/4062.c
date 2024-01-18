// commit message FFmpeg@f6774f905f (target=1, prob=0.6111065, correct=True): mpegvideo: operate with pointers to AVFrames instead of whole structs
/*0   */ static int svq1_encode_plane(SVQ1Context *s, int plane,                             // (9) 0.04297
/*2   */                              unsigned char *src_plane,                              // (5) 0.06836
/*4   */                              unsigned char *ref_plane,                              // (4) 0.06836
/*6   */                              unsigned char *decoded_plane,                          // (2) 0.07031
/*8   */                              int width, int height, int src_stride, int stride)     // (1) 0.08398
/*10  */ {                                                                                   // (22) 0.001953
/*12  */     const AVFrame *f = s->avctx->coded_frame;                                       // (10) 0.03516
/*14  */     int x, y;                                                                       // (18) 0.01563
/*16  */     int i;                                                                          // (20) 0.01172
/*18  */     int block_width, block_height;                                                  // (17) 0.02344
/*20  */     int level;                                                                      // (21) 0.01172
/*22  */     int threshold[6];                                                               // (19) 0.01562
/*24  */     uint8_t *src     = s->scratchbuf + stride * 16;                                 // (7) 0.04688
/*26  */     const int lambda = (f->quality * f->quality) >>                                 // (12) 0.0332
/*28  */                        (2 * FF_LAMBDA_SHIFT);                                       // (3) 0.06836
/*32  */     /* figure out the acceptable level thresholds in advance */                     // (16) 0.02539
/*34  */     threshold[5] = QUALITY_THRESHOLD;                                               // (13) 0.0332
/*36  */     for (level = 4; level >= 0; level--)                                            // (14) 0.03125
/*38  */         threshold[level] = threshold[level + 1] * THRESHOLD_MULTIPLIER;             // (6) 0.05859
/*42  */     block_width  = (width  + 15) / 16;                                              // (11) 0.0332
/*44  */     block_height = (height + 15) / 16;                                              // (15) 0.0293
/*48  */     if (f->pict_type == AV_PICTURE_TYPE_P) {                                        // (8) 0.04297
/*50  */         s->m.avctx                         = s->avctx;                              // (0) 0.08398
/*52  */         s->m.current_picture_ptr           = &s->m.current_picture;                 // 0.0
/*54  */         s->m.last_picture_ptr              = &s->m.last_picture;                    // 0.0
/*56  */         s->m.last_picture.f.data[0]        = ref_plane;                             // 0.0
/*58  */         s->m.linesize                      =                                        // 0.0
/*60  */         s->m.last_picture.f.linesize[0]    =                                        // 0.0
/*62  */         s->m.new_picture.f.linesize[0]     =                                        // 0.0
/*64  */         s->m.current_picture.f.linesize[0] = stride;                                // 0.0
/*66  */         s->m.width                         = width;                                 // 0.0
/*68  */         s->m.height                        = height;                                // 0.0
/*70  */         s->m.mb_width                      = block_width;                           // 0.0
/*72  */         s->m.mb_height                     = block_height;                          // 0.0
/*74  */         s->m.mb_stride                     = s->m.mb_width + 1;                     // 0.0
/*76  */         s->m.b8_stride                     = 2 * s->m.mb_width + 1;                 // 0.0
/*78  */         s->m.f_code                        = 1;                                     // 0.0
/*80  */         s->m.pict_type                     = f->pict_type;                          // 0.0
/*82  */         s->m.me_method                     = s->avctx->me_method;                   // 0.0
/*84  */         s->m.me.scene_change_score         = 0;                                     // 0.0
/*86  */         s->m.flags                         = s->avctx->flags;                       // 0.0
/*88  */         // s->m.out_format                    = FMT_H263;                           // 0.0
/*90  */         // s->m.unrestricted_mv               = 1;                                  // 0.0
/*92  */         s->m.lambda                        = f->quality;                            // 0.0
/*94  */         s->m.qscale                        = s->m.lambda * 139 +                    // 0.0
/*96  */                                              FF_LAMBDA_SCALE * 64 >>                // 0.0
/*98  */                                              FF_LAMBDA_SHIFT + 7;                   // 0.0
/*100 */         s->m.lambda2                       = s->m.lambda * s->m.lambda +            // 0.0
/*102 */                                              FF_LAMBDA_SCALE / 2 >>                 // 0.0
/*104 */                                              FF_LAMBDA_SHIFT;                       // 0.0
/*108 */         if (!s->motion_val8[plane]) {                                               // 0.0
/*110 */             s->motion_val8[plane]  = av_mallocz((s->m.b8_stride *                   // 0.0
/*112 */                                                  block_height * 2 + 2) *            // 0.0
/*114 */                                                 2 * sizeof(int16_t));               // 0.0
/*116 */             s->motion_val16[plane] = av_mallocz((s->m.mb_stride *                   // 0.0
/*118 */                                                  (block_height + 2) + 1) *          // 0.0
/*120 */                                                 2 * sizeof(int16_t));               // 0.0
/*122 */         }                                                                           // 0.0
/*126 */         s->m.mb_type = s->mb_type;                                                  // 0.0
/*130 */         // dummies, to avoid segfaults                                              // 0.0
/*132 */         s->m.current_picture.mb_mean   = (uint8_t *)s->dummy;                       // 0.0
/*134 */         s->m.current_picture.mb_var    = (uint16_t *)s->dummy;                      // 0.0
/*136 */         s->m.current_picture.mc_mb_var = (uint16_t *)s->dummy;                      // 0.0
/*138 */         s->m.current_picture.mb_type = s->dummy;                                    // 0.0
/*142 */         s->m.current_picture.motion_val[0]   = s->motion_val8[plane] + 2;           // 0.0
/*144 */         s->m.p_mv_table                      = s->motion_val16[plane] +             // 0.0
/*146 */                                                s->m.mb_stride + 1;                  // 0.0
/*148 */         s->m.dsp                             = s->dsp; // move                      // 0.0
/*150 */         ff_init_me(&s->m);                                                          // 0.0
/*154 */         s->m.me.dia_size      = s->avctx->dia_size;                                 // 0.0
/*156 */         s->m.first_slice_line = 1;                                                  // 0.0
/*158 */         for (y = 0; y < block_height; y++) {                                        // 0.0
/*160 */             s->m.new_picture.f.data[0] = src - y * 16 * stride; // ugly             // 0.0
/*162 */             s->m.mb_y                  = y;                                         // 0.0
/*166 */             for (i = 0; i < 16 && i + 16 * y < height; i++) {                       // 0.0
/*168 */                 memcpy(&src[i * stride], &src_plane[(i + 16 * y) * src_stride],     // 0.0
/*170 */                        width);                                                      // 0.0
/*172 */                 for (x = width; x < 16 * block_width; x++)                          // 0.0
/*174 */                     src[i * stride + x] = src[i * stride + x - 1];                  // 0.0
/*176 */             }                                                                       // 0.0
/*178 */             for (; i < 16 && i + 16 * y < 16 * block_height; i++)                   // 0.0
/*180 */                 memcpy(&src[i * stride], &src[(i - 1) * stride],                    // 0.0
/*182 */                        16 * block_width);                                           // 0.0
/*186 */             for (x = 0; x < block_width; x++) {                                     // 0.0
/*188 */                 s->m.mb_x = x;                                                      // 0.0
/*190 */                 ff_init_block_index(&s->m);                                         // 0.0
/*192 */                 ff_update_block_index(&s->m);                                       // 0.0
/*196 */                 ff_estimate_p_frame_motion(&s->m, x, y);                            // 0.0
/*198 */             }                                                                       // 0.0
/*200 */             s->m.first_slice_line = 0;                                              // 0.0
/*202 */         }                                                                           // 0.0
/*206 */         ff_fix_long_p_mvs(&s->m);                                                   // 0.0
/*208 */         ff_fix_long_mvs(&s->m, NULL, 0, s->m.p_mv_table, s->m.f_code,               // 0.0
/*210 */                         CANDIDATE_MB_TYPE_INTER, 0);                                // 0.0
/*212 */     }                                                                               // 0.0
/*216 */     s->m.first_slice_line = 1;                                                      // 0.0
/*218 */     for (y = 0; y < block_height; y++) {                                            // 0.0
/*220 */         for (i = 0; i < 16 && i + 16 * y < height; i++) {                           // 0.0
/*222 */             memcpy(&src[i * stride], &src_plane[(i + 16 * y) * src_stride],         // 0.0
/*224 */                    width);                                                          // 0.0
/*226 */             for (x = width; x < 16 * block_width; x++)                              // 0.0
/*228 */                 src[i * stride + x] = src[i * stride + x - 1];                      // 0.0
/*230 */         }                                                                           // 0.0
/*232 */         for (; i < 16 && i + 16 * y < 16 * block_height; i++)                       // 0.0
/*234 */             memcpy(&src[i * stride], &src[(i - 1) * stride], 16 * block_width);     // 0.0
/*238 */         s->m.mb_y = y;                                                              // 0.0
/*240 */         for (x = 0; x < block_width; x++) {                                         // 0.0
/*242 */             uint8_t reorder_buffer[3][6][7 * 32];                                   // 0.0
/*244 */             int count[3][6];                                                        // 0.0
/*246 */             int offset       = y * 16 * stride + x * 16;                            // 0.0
/*248 */             uint8_t *decoded = decoded_plane + offset;                              // 0.0
/*250 */             uint8_t *ref     = ref_plane + offset;                                  // 0.0
/*252 */             int score[4]     = { 0, 0, 0, 0 }, best;                                // 0.0
/*254 */             uint8_t *temp    = s->scratchbuf;                                       // 0.0
/*258 */             if (s->pb.buf_end - s->pb.buf -                                         // 0.0
/*260 */                 (put_bits_count(&s->pb) >> 3) < 3000) { // FIXME: check size        // 0.0
/*262 */                 av_log(s->avctx, AV_LOG_ERROR, "encoded frame too large\n");        // 0.0
/*264 */                 return -1;                                                          // 0.0
/*266 */             }                                                                       // 0.0
/*270 */             s->m.mb_x = x;                                                          // 0.0
/*272 */             ff_init_block_index(&s->m);                                             // 0.0
/*274 */             ff_update_block_index(&s->m);                                           // 0.0
/*278 */             if (f->pict_type == AV_PICTURE_TYPE_I ||                                // 0.0
/*280 */                 (s->m.mb_type[x + y * s->m.mb_stride] &                             // 0.0
/*282 */                  CANDIDATE_MB_TYPE_INTRA)) {                                        // 0.0
/*284 */                 for (i = 0; i < 6; i++)                                             // 0.0
/*286 */                     init_put_bits(&s->reorder_pb[i], reorder_buffer[0][i],          // 0.0
/*288 */                                   7 * 32);                                          // 0.0
/*290 */                 if (f->pict_type == AV_PICTURE_TYPE_P) {                            // 0.0
/*292 */                     const uint8_t *vlc = ff_svq1_block_type_vlc[SVQ1_BLOCK_INTRA];  // 0.0
/*294 */                     put_bits(&s->reorder_pb[5], vlc[1], vlc[0]);                    // 0.0
/*296 */                     score[0] = vlc[1] * lambda;                                     // 0.0
/*298 */                 }                                                                   // 0.0
/*300 */                 score[0] += encode_block(s, src + 16 * x, NULL, temp, stride,       // 0.0
/*302 */                                          5, 64, lambda, 1);                         // 0.0
/*304 */                 for (i = 0; i < 6; i++) {                                           // 0.0
/*306 */                     count[0][i] = put_bits_count(&s->reorder_pb[i]);                // 0.0
/*308 */                     flush_put_bits(&s->reorder_pb[i]);                              // 0.0
/*310 */                 }                                                                   // 0.0
/*312 */             } else                                                                  // 0.0
/*314 */                 score[0] = INT_MAX;                                                 // 0.0
/*318 */             best = 0;                                                               // 0.0
/*322 */             if (f->pict_type == AV_PICTURE_TYPE_P) {                                // 0.0
/*324 */                 const uint8_t *vlc = ff_svq1_block_type_vlc[SVQ1_BLOCK_INTER];      // 0.0
/*326 */                 int mx, my, pred_x, pred_y, dxy;                                    // 0.0
/*328 */                 int16_t *motion_ptr;                                                // 0.0
/*332 */                 motion_ptr = ff_h263_pred_motion(&s->m, 0, 0, &pred_x, &pred_y);    // 0.0
/*334 */                 if (s->m.mb_type[x + y * s->m.mb_stride] &                          // 0.0
/*336 */                     CANDIDATE_MB_TYPE_INTER) {                                      // 0.0
/*338 */                     for (i = 0; i < 6; i++)                                         // 0.0
/*340 */                         init_put_bits(&s->reorder_pb[i], reorder_buffer[1][i],      // 0.0
/*342 */                                       7 * 32);                                      // 0.0
/*346 */                     put_bits(&s->reorder_pb[5], vlc[1], vlc[0]);                    // 0.0
/*350 */                     s->m.pb = s->reorder_pb[5];                                     // 0.0
/*352 */                     mx      = motion_ptr[0];                                        // 0.0
/*354 */                     my      = motion_ptr[1];                                        // 0.0
/*356 */                     assert(mx     >= -32 && mx     <= 31);                          // 0.0
/*358 */                     assert(my     >= -32 && my     <= 31);                          // 0.0
/*360 */                     assert(pred_x >= -32 && pred_x <= 31);                          // 0.0
/*362 */                     assert(pred_y >= -32 && pred_y <= 31);                          // 0.0
/*364 */                     ff_h263_encode_motion(&s->m, mx - pred_x, 1);                   // 0.0
/*366 */                     ff_h263_encode_motion(&s->m, my - pred_y, 1);                   // 0.0
/*368 */                     s->reorder_pb[5] = s->m.pb;                                     // 0.0
/*370 */                     score[1]        += lambda * put_bits_count(&s->reorder_pb[5]);  // 0.0
/*374 */                     dxy = (mx & 1) + 2 * (my & 1);                                  // 0.0
/*378 */                     s->hdsp.put_pixels_tab[0][dxy](temp + 16,                       // 0.0
/*380 */                                                    ref + (mx >> 1) +                // 0.0
/*382 */                                                    stride * (my >> 1),              // 0.0
/*384 */                                                    stride, 16);                     // 0.0
/*388 */                     score[1] += encode_block(s, src + 16 * x, temp + 16,            // 0.0
/*390 */                                              decoded, stride, 5, 64, lambda, 0);    // 0.0
/*392 */                     best      = score[1] <= score[0];                               // 0.0
/*396 */                     vlc       = ff_svq1_block_type_vlc[SVQ1_BLOCK_SKIP];            // 0.0
/*398 */                     score[2]  = s->dsp.sse[0](NULL, src + 16 * x, ref,              // 0.0
/*400 */                                               stride, 16);                          // 0.0
/*402 */                     score[2] += vlc[1] * lambda;                                    // 0.0
/*404 */                     if (score[2] < score[best] && mx == 0 && my == 0) {             // 0.0
/*406 */                         best = 2;                                                   // 0.0
/*408 */                         s->hdsp.put_pixels_tab[0][0](decoded, ref, stride, 16);     // 0.0
/*410 */                         for (i = 0; i < 6; i++)                                     // 0.0
/*412 */                             count[2][i] = 0;                                        // 0.0
/*414 */                         put_bits(&s->pb, vlc[1], vlc[0]);                           // 0.0
/*416 */                     }                                                               // 0.0
/*418 */                 }                                                                   // 0.0
/*422 */                 if (best == 1) {                                                    // 0.0
/*424 */                     for (i = 0; i < 6; i++) {                                       // 0.0
/*426 */                         count[1][i] = put_bits_count(&s->reorder_pb[i]);            // 0.0
/*428 */                         flush_put_bits(&s->reorder_pb[i]);                          // 0.0
/*430 */                     }                                                               // 0.0
/*432 */                 } else {                                                            // 0.0
/*434 */                     motion_ptr[0]                      =                            // 0.0
/*436 */                     motion_ptr[1]                      =                            // 0.0
/*438 */                     motion_ptr[2]                      =                            // 0.0
/*440 */                     motion_ptr[3]                      =                            // 0.0
/*442 */                     motion_ptr[0 + 2 * s->m.b8_stride] =                            // 0.0
/*444 */                     motion_ptr[1 + 2 * s->m.b8_stride] =                            // 0.0
/*446 */                     motion_ptr[2 + 2 * s->m.b8_stride] =                            // 0.0
/*448 */                     motion_ptr[3 + 2 * s->m.b8_stride] = 0;                         // 0.0
/*450 */                 }                                                                   // 0.0
/*452 */             }                                                                       // 0.0
/*456 */             s->rd_total += score[best];                                             // 0.0
/*460 */             for (i = 5; i >= 0; i--)                                                // 0.0
/*462 */                 avpriv_copy_bits(&s->pb, reorder_buffer[best][i],                   // 0.0
/*464 */                                  count[best][i]);                                   // 0.0
/*466 */             if (best == 0)                                                          // 0.0
/*468 */                 s->hdsp.put_pixels_tab[0][0](decoded, temp, stride, 16);            // 0.0
/*470 */         }                                                                           // 0.0
/*472 */         s->m.first_slice_line = 0;                                                  // 0.0
/*474 */     }                                                                               // 0.0
/*476 */     return 0;                                                                       // 0.0
/*478 */ }                                                                                   // 0.0
