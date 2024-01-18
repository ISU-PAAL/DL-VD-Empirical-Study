// commit message FFmpeg@c94326c1fc (target=1, prob=0.5072762, correct=True): avcodec/hevcpred_template: Fix left shift of negative value
/*0   */ static av_always_inline void FUNC(intra_pred)(HEVCContext *s, int x0, int y0,                                                                // (5) 0.05665
/*2   */                                               int log2_size, int c_idx)                                                                      // (0) 0.1113
/*4   */ {                                                                                                                                            // (19) 0.001953
/*6   */ #define PU(x) \                                                                                                                              // (17) 0.01367
/*8   */     ((x) >> s->ps.sps->log2_min_pu_size)                                                                                                     // (8) 0.04492
/*10  */ #define MVF(x, y) \                                                                                                                          // (16) 0.01953
/*12  */     (s->ref->tab_mvf[(x) + (y) * min_pu_width])                                                                                              // (7) 0.05468
/*14  */ #define MVF_PU(x, y) \                                                                                                                       // (14) 0.02344
/*16  */     MVF(PU(x0 + ((x) << hshift)), PU(y0 + ((y) << vshift)))                                                                                  // (4) 0.05859
/*18  */ #define IS_INTRA(x, y) \                                                                                                                     // (15) 0.02344
/*20  */     (MVF_PU(x, y).pred_flag == PF_INTRA)                                                                                                     // (9) 0.04492
/*22  */ #define MIN_TB_ADDR_ZS(x, y) \                                                                                                               // (13) 0.0332
/*24  */     s->ps.pps->min_tb_addr_zs[(y) * (s->ps.sps->tb_mask+2) + (x)]                                                                            // (2) 0.08202
/*26  */ #define EXTEND(ptr, val, len)         \                                                                                                      // (12) 0.03906
/*28  */ do {                                  \                                                                                                      // (3) 0.07031
/*30  */     pixel4 pix = PIXEL_SPLAT_X4(val); \                                                                                                      // (11) 0.04297
/*32  */     for (i = 0; i < (len); i += 4)    \                                                                                                      // (10) 0.04297
/*34  */         AV_WN4P(ptr + i, pix);        \                                                                                                      // (6) 0.05468
/*36  */ } while (0)                                                                                                                                  // (18) 0.009773
/*40  */ #define EXTEND_RIGHT_CIP(ptr, start, length)                                   \                                                             // (1) 0.1016
/*42  */         for (i = start; i < (start) + (length); i += 4)                        \                                                             // 0.0
/*44  */             if (!IS_INTRA(i, -1))                                              \                                                             // 0.0
/*46  */                 AV_WN4P(&ptr[i], a);                                           \                                                             // 0.0
/*48  */             else                                                               \                                                             // 0.0
/*50  */                 a = PIXEL_SPLAT_X4(ptr[i+3])                                                                                                 // 0.0
/*52  */ #define EXTEND_LEFT_CIP(ptr, start, length) \                                                                                                // 0.0
/*54  */         for (i = start; i > (start) - (length); i--) \                                                                                       // 0.0
/*56  */             if (!IS_INTRA(i - 1, -1)) \                                                                                                      // 0.0
/*58  */                 ptr[i - 1] = ptr[i]                                                                                                          // 0.0
/*60  */ #define EXTEND_UP_CIP(ptr, start, length)                                      \                                                             // 0.0
/*62  */         for (i = (start); i > (start) - (length); i -= 4)                      \                                                             // 0.0
/*64  */             if (!IS_INTRA(-1, i - 3))                                          \                                                             // 0.0
/*66  */                 AV_WN4P(&ptr[i - 3], a);                                       \                                                             // 0.0
/*68  */             else                                                               \                                                             // 0.0
/*70  */                 a = PIXEL_SPLAT_X4(ptr[i - 3])                                                                                               // 0.0
/*72  */ #define EXTEND_DOWN_CIP(ptr, start, length)                                    \                                                             // 0.0
/*74  */         for (i = start; i < (start) + (length); i += 4)                        \                                                             // 0.0
/*76  */             if (!IS_INTRA(-1, i))                                              \                                                             // 0.0
/*78  */                 AV_WN4P(&ptr[i], a);                                           \                                                             // 0.0
/*80  */             else                                                               \                                                             // 0.0
/*82  */                 a = PIXEL_SPLAT_X4(ptr[i + 3])                                                                                               // 0.0
/*86  */     HEVCLocalContext *lc = s->HEVClc;                                                                                                        // 0.0
/*88  */     int i;                                                                                                                                   // 0.0
/*90  */     int hshift = s->ps.sps->hshift[c_idx];                                                                                                   // 0.0
/*92  */     int vshift = s->ps.sps->vshift[c_idx];                                                                                                   // 0.0
/*94  */     int size = (1 << log2_size);                                                                                                             // 0.0
/*96  */     int size_in_luma_h = size << hshift;                                                                                                     // 0.0
/*98  */     int size_in_tbs_h  = size_in_luma_h >> s->ps.sps->log2_min_tb_size;                                                                      // 0.0
/*100 */     int size_in_luma_v = size << vshift;                                                                                                     // 0.0
/*102 */     int size_in_tbs_v  = size_in_luma_v >> s->ps.sps->log2_min_tb_size;                                                                      // 0.0
/*104 */     int x = x0 >> hshift;                                                                                                                    // 0.0
/*106 */     int y = y0 >> vshift;                                                                                                                    // 0.0
/*108 */     int x_tb = (x0 >> s->ps.sps->log2_min_tb_size) & s->ps.sps->tb_mask;                                                                     // 0.0
/*110 */     int y_tb = (y0 >> s->ps.sps->log2_min_tb_size) & s->ps.sps->tb_mask;                                                                     // 0.0
/*114 */     int cur_tb_addr = MIN_TB_ADDR_ZS(x_tb, y_tb);                                                                                            // 0.0
/*118 */     ptrdiff_t stride = s->frame->linesize[c_idx] / sizeof(pixel);                                                                            // 0.0
/*120 */     pixel *src = (pixel*)s->frame->data[c_idx] + x + y * stride;                                                                             // 0.0
/*124 */     int min_pu_width = s->ps.sps->min_pu_width;                                                                                              // 0.0
/*128 */     enum IntraPredMode mode = c_idx ? lc->tu.intra_pred_mode_c :                                                                             // 0.0
/*130 */                               lc->tu.intra_pred_mode;                                                                                        // 0.0
/*132 */     pixel4 a;                                                                                                                                // 0.0
/*134 */     pixel  left_array[2 * MAX_TB_SIZE + 1];                                                                                                  // 0.0
/*136 */     pixel  filtered_left_array[2 * MAX_TB_SIZE + 1];                                                                                         // 0.0
/*138 */     pixel  top_array[2 * MAX_TB_SIZE + 1];                                                                                                   // 0.0
/*140 */     pixel  filtered_top_array[2 * MAX_TB_SIZE + 1];                                                                                          // 0.0
/*144 */     pixel  *left          = left_array + 1;                                                                                                  // 0.0
/*146 */     pixel  *top           = top_array  + 1;                                                                                                  // 0.0
/*148 */     pixel  *filtered_left = filtered_left_array + 1;                                                                                         // 0.0
/*150 */     pixel  *filtered_top  = filtered_top_array  + 1;                                                                                         // 0.0
/*152 */     int cand_bottom_left = lc->na.cand_bottom_left && cur_tb_addr > MIN_TB_ADDR_ZS( x_tb - 1, (y_tb + size_in_tbs_v) & s->ps.sps->tb_mask);  // 0.0
/*154 */     int cand_left        = lc->na.cand_left;                                                                                                 // 0.0
/*156 */     int cand_up_left     = lc->na.cand_up_left;                                                                                              // 0.0
/*158 */     int cand_up          = lc->na.cand_up;                                                                                                   // 0.0
/*160 */     int cand_up_right    = lc->na.cand_up_right    && cur_tb_addr > MIN_TB_ADDR_ZS((x_tb + size_in_tbs_h) & s->ps.sps->tb_mask, y_tb - 1);   // 0.0
/*164 */     int bottom_left_size = (FFMIN(y0 + 2 * size_in_luma_v, s->ps.sps->height) -                                                              // 0.0
/*166 */                            (y0 + size_in_luma_v)) >> vshift;                                                                                 // 0.0
/*168 */     int top_right_size   = (FFMIN(x0 + 2 * size_in_luma_h, s->ps.sps->width) -                                                               // 0.0
/*170 */                            (x0 + size_in_luma_h)) >> hshift;                                                                                 // 0.0
/*174 */     if (s->ps.pps->constrained_intra_pred_flag == 1) {                                                                                       // 0.0
/*176 */         int size_in_luma_pu_v = PU(size_in_luma_v);                                                                                          // 0.0
/*178 */         int size_in_luma_pu_h = PU(size_in_luma_h);                                                                                          // 0.0
/*180 */         int on_pu_edge_x    = !av_mod_uintp2(x0, s->ps.sps->log2_min_pu_size);                                                               // 0.0
/*182 */         int on_pu_edge_y    = !av_mod_uintp2(y0, s->ps.sps->log2_min_pu_size);                                                               // 0.0
/*184 */         if (!size_in_luma_pu_h)                                                                                                              // 0.0
/*186 */             size_in_luma_pu_h++;                                                                                                             // 0.0
/*188 */         if (cand_bottom_left == 1 && on_pu_edge_x) {                                                                                         // 0.0
/*190 */             int x_left_pu   = PU(x0 - 1);                                                                                                    // 0.0
/*192 */             int y_bottom_pu = PU(y0 + size_in_luma_v);                                                                                       // 0.0
/*194 */             int max = FFMIN(size_in_luma_pu_v, s->ps.sps->min_pu_height - y_bottom_pu);                                                      // 0.0
/*196 */             cand_bottom_left = 0;                                                                                                            // 0.0
/*198 */             for (i = 0; i < max; i += 2)                                                                                                     // 0.0
/*200 */                 cand_bottom_left |= (MVF(x_left_pu, y_bottom_pu + i).pred_flag == PF_INTRA);                                                 // 0.0
/*202 */         }                                                                                                                                    // 0.0
/*204 */         if (cand_left == 1 && on_pu_edge_x) {                                                                                                // 0.0
/*206 */             int x_left_pu   = PU(x0 - 1);                                                                                                    // 0.0
/*208 */             int y_left_pu   = PU(y0);                                                                                                        // 0.0
/*210 */             int max = FFMIN(size_in_luma_pu_v, s->ps.sps->min_pu_height - y_left_pu);                                                        // 0.0
/*212 */             cand_left = 0;                                                                                                                   // 0.0
/*214 */             for (i = 0; i < max; i += 2)                                                                                                     // 0.0
/*216 */                 cand_left |= (MVF(x_left_pu, y_left_pu + i).pred_flag == PF_INTRA);                                                          // 0.0
/*218 */         }                                                                                                                                    // 0.0
/*220 */         if (cand_up_left == 1) {                                                                                                             // 0.0
/*222 */             int x_left_pu   = PU(x0 - 1);                                                                                                    // 0.0
/*224 */             int y_top_pu    = PU(y0 - 1);                                                                                                    // 0.0
/*226 */             cand_up_left = MVF(x_left_pu, y_top_pu).pred_flag == PF_INTRA;                                                                   // 0.0
/*228 */         }                                                                                                                                    // 0.0
/*230 */         if (cand_up == 1 && on_pu_edge_y) {                                                                                                  // 0.0
/*232 */             int x_top_pu    = PU(x0);                                                                                                        // 0.0
/*234 */             int y_top_pu    = PU(y0 - 1);                                                                                                    // 0.0
/*236 */             int max = FFMIN(size_in_luma_pu_h, s->ps.sps->min_pu_width - x_top_pu);                                                          // 0.0
/*238 */             cand_up = 0;                                                                                                                     // 0.0
/*240 */             for (i = 0; i < max; i += 2)                                                                                                     // 0.0
/*242 */                 cand_up |= (MVF(x_top_pu + i, y_top_pu).pred_flag == PF_INTRA);                                                              // 0.0
/*244 */         }                                                                                                                                    // 0.0
/*246 */         if (cand_up_right == 1 && on_pu_edge_y) {                                                                                            // 0.0
/*248 */             int y_top_pu    = PU(y0 - 1);                                                                                                    // 0.0
/*250 */             int x_right_pu  = PU(x0 + size_in_luma_h);                                                                                       // 0.0
/*252 */             int max = FFMIN(size_in_luma_pu_h, s->ps.sps->min_pu_width - x_right_pu);                                                        // 0.0
/*254 */             cand_up_right = 0;                                                                                                               // 0.0
/*256 */             for (i = 0; i < max; i += 2)                                                                                                     // 0.0
/*258 */                 cand_up_right |= (MVF(x_right_pu + i, y_top_pu).pred_flag == PF_INTRA);                                                      // 0.0
/*260 */         }                                                                                                                                    // 0.0
/*262 */         memset(left, 128, 2 * MAX_TB_SIZE*sizeof(pixel));                                                                                    // 0.0
/*264 */         memset(top , 128, 2 * MAX_TB_SIZE*sizeof(pixel));                                                                                    // 0.0
/*266 */         top[-1] = 128;                                                                                                                       // 0.0
/*268 */     }                                                                                                                                        // 0.0
/*270 */     if (cand_up_left) {                                                                                                                      // 0.0
/*272 */         left[-1] = POS(-1, -1);                                                                                                              // 0.0
/*274 */         top[-1]  = left[-1];                                                                                                                 // 0.0
/*276 */     }                                                                                                                                        // 0.0
/*278 */     if (cand_up)                                                                                                                             // 0.0
/*280 */         memcpy(top, src - stride, size * sizeof(pixel));                                                                                     // 0.0
/*282 */     if (cand_up_right) {                                                                                                                     // 0.0
/*284 */         memcpy(top + size, src - stride + size, size * sizeof(pixel));                                                                       // 0.0
/*286 */         EXTEND(top + size + top_right_size, POS(size + top_right_size - 1, -1),                                                              // 0.0
/*288 */                size - top_right_size);                                                                                                       // 0.0
/*290 */     }                                                                                                                                        // 0.0
/*292 */     if (cand_left)                                                                                                                           // 0.0
/*294 */         for (i = 0; i < size; i++)                                                                                                           // 0.0
/*296 */             left[i] = POS(-1, i);                                                                                                            // 0.0
/*298 */     if (cand_bottom_left) {                                                                                                                  // 0.0
/*300 */         for (i = size; i < size + bottom_left_size; i++)                                                                                     // 0.0
/*302 */             left[i] = POS(-1, i);                                                                                                            // 0.0
/*304 */         EXTEND(left + size + bottom_left_size, POS(-1, size + bottom_left_size - 1),                                                         // 0.0
/*306 */                size - bottom_left_size);                                                                                                     // 0.0
/*308 */     }                                                                                                                                        // 0.0
/*312 */     if (s->ps.pps->constrained_intra_pred_flag == 1) {                                                                                       // 0.0
/*314 */         if (cand_bottom_left || cand_left || cand_up_left || cand_up || cand_up_right) {                                                     // 0.0
/*316 */             int size_max_x = x0 + ((2 * size) << hshift) < s->ps.sps->width ?                                                                // 0.0
/*318 */                                     2 * size : (s->ps.sps->width - x0) >> hshift;                                                            // 0.0
/*320 */             int size_max_y = y0 + ((2 * size) << vshift) < s->ps.sps->height ?                                                               // 0.0
/*322 */                                     2 * size : (s->ps.sps->height - y0) >> vshift;                                                           // 0.0
/*324 */             int j = size + (cand_bottom_left? bottom_left_size: 0) -1;                                                                       // 0.0
/*326 */             if (!cand_up_right) {                                                                                                            // 0.0
/*328 */                 size_max_x = x0 + ((size) << hshift) < s->ps.sps->width ?                                                                    // 0.0
/*330 */                                                     size : (s->ps.sps->width - x0) >> hshift;                                                // 0.0
/*332 */             }                                                                                                                                // 0.0
/*334 */             if (!cand_bottom_left) {                                                                                                         // 0.0
/*336 */                 size_max_y = y0 + (( size) << vshift) < s->ps.sps->height ?                                                                  // 0.0
/*338 */                                                      size : (s->ps.sps->height - y0) >> vshift;                                              // 0.0
/*340 */             }                                                                                                                                // 0.0
/*342 */             if (cand_bottom_left || cand_left || cand_up_left) {                                                                             // 0.0
/*344 */                 while (j > -1 && !IS_INTRA(-1, j))                                                                                           // 0.0
/*346 */                     j--;                                                                                                                     // 0.0
/*348 */                 if (!IS_INTRA(-1, j)) {                                                                                                      // 0.0
/*350 */                     j = 0;                                                                                                                   // 0.0
/*352 */                     while (j < size_max_x && !IS_INTRA(j, -1))                                                                               // 0.0
/*354 */                         j++;                                                                                                                 // 0.0
/*356 */                     EXTEND_LEFT_CIP(top, j, j + 1);                                                                                          // 0.0
/*358 */                     left[-1] = top[-1];                                                                                                      // 0.0
/*360 */                 }                                                                                                                            // 0.0
/*362 */             } else {                                                                                                                         // 0.0
/*364 */                 j = 0;                                                                                                                       // 0.0
/*366 */                 while (j < size_max_x && !IS_INTRA(j, -1))                                                                                   // 0.0
/*368 */                     j++;                                                                                                                     // 0.0
/*370 */                 if (j > 0)                                                                                                                   // 0.0
/*372 */                     if (x0 > 0) {                                                                                                            // 0.0
/*374 */                         EXTEND_LEFT_CIP(top, j, j + 1);                                                                                      // 0.0
/*376 */                     } else {                                                                                                                 // 0.0
/*378 */                         EXTEND_LEFT_CIP(top, j, j);                                                                                          // 0.0
/*380 */                         top[-1] = top[0];                                                                                                    // 0.0
/*382 */                     }                                                                                                                        // 0.0
/*384 */                 left[-1] = top[-1];                                                                                                          // 0.0
/*386 */             }                                                                                                                                // 0.0
/*388 */             left[-1] = top[-1];                                                                                                              // 0.0
/*390 */             if (cand_bottom_left || cand_left) {                                                                                             // 0.0
/*392 */                 a = PIXEL_SPLAT_X4(left[-1]);                                                                                                // 0.0
/*394 */                 EXTEND_DOWN_CIP(left, 0, size_max_y);                                                                                        // 0.0
/*396 */             }                                                                                                                                // 0.0
/*398 */             if (!cand_left)                                                                                                                  // 0.0
/*400 */                 EXTEND(left, left[-1], size);                                                                                                // 0.0
/*402 */             if (!cand_bottom_left)                                                                                                           // 0.0
/*404 */                 EXTEND(left + size, left[size - 1], size);                                                                                   // 0.0
/*406 */             if (x0 != 0 && y0 != 0) {                                                                                                        // 0.0
/*408 */                 a = PIXEL_SPLAT_X4(left[size_max_y - 1]);                                                                                    // 0.0
/*410 */                 EXTEND_UP_CIP(left, size_max_y - 1, size_max_y);                                                                             // 0.0
/*412 */                 if (!IS_INTRA(-1, - 1))                                                                                                      // 0.0
/*414 */                     left[-1] = left[0];                                                                                                      // 0.0
/*416 */             } else if (x0 == 0) {                                                                                                            // 0.0
/*418 */                 EXTEND(left, 0, size_max_y);                                                                                                 // 0.0
/*420 */             } else {                                                                                                                         // 0.0
/*422 */                 a = PIXEL_SPLAT_X4(left[size_max_y - 1]);                                                                                    // 0.0
/*424 */                 EXTEND_UP_CIP(left, size_max_y - 1, size_max_y);                                                                             // 0.0
/*426 */             }                                                                                                                                // 0.0
/*428 */             top[-1] = left[-1];                                                                                                              // 0.0
/*430 */             if (y0 != 0) {                                                                                                                   // 0.0
/*432 */                 a = PIXEL_SPLAT_X4(left[-1]);                                                                                                // 0.0
/*434 */                 EXTEND_RIGHT_CIP(top, 0, size_max_x);                                                                                        // 0.0
/*436 */             }                                                                                                                                // 0.0
/*438 */         }                                                                                                                                    // 0.0
/*440 */     }                                                                                                                                        // 0.0
/*442 */     // Infer the unavailable samples                                                                                                         // 0.0
/*444 */     if (!cand_bottom_left) {                                                                                                                 // 0.0
/*446 */         if (cand_left) {                                                                                                                     // 0.0
/*448 */             EXTEND(left + size, left[size - 1], size);                                                                                       // 0.0
/*450 */         } else if (cand_up_left) {                                                                                                           // 0.0
/*452 */             EXTEND(left, left[-1], 2 * size);                                                                                                // 0.0
/*454 */             cand_left = 1;                                                                                                                   // 0.0
/*456 */         } else if (cand_up) {                                                                                                                // 0.0
/*458 */             left[-1] = top[0];                                                                                                               // 0.0
/*460 */             EXTEND(left, left[-1], 2 * size);                                                                                                // 0.0
/*462 */             cand_up_left = 1;                                                                                                                // 0.0
/*464 */             cand_left    = 1;                                                                                                                // 0.0
/*466 */         } else if (cand_up_right) {                                                                                                          // 0.0
/*468 */             EXTEND(top, top[size], size);                                                                                                    // 0.0
/*470 */             left[-1] = top[size];                                                                                                            // 0.0
/*472 */             EXTEND(left, left[-1], 2 * size);                                                                                                // 0.0
/*474 */             cand_up      = 1;                                                                                                                // 0.0
/*476 */             cand_up_left = 1;                                                                                                                // 0.0
/*478 */             cand_left    = 1;                                                                                                                // 0.0
/*480 */         } else { // No samples available                                                                                                     // 0.0
/*482 */             left[-1] = (1 << (BIT_DEPTH - 1));                                                                                               // 0.0
/*484 */             EXTEND(top,  left[-1], 2 * size);                                                                                                // 0.0
/*486 */             EXTEND(left, left[-1], 2 * size);                                                                                                // 0.0
/*488 */         }                                                                                                                                    // 0.0
/*490 */     }                                                                                                                                        // 0.0
/*494 */     if (!cand_left)                                                                                                                          // 0.0
/*496 */         EXTEND(left, left[size], size);                                                                                                      // 0.0
/*498 */     if (!cand_up_left) {                                                                                                                     // 0.0
/*500 */         left[-1] = left[0];                                                                                                                  // 0.0
/*502 */     }                                                                                                                                        // 0.0
/*504 */     if (!cand_up)                                                                                                                            // 0.0
/*506 */         EXTEND(top, left[-1], size);                                                                                                         // 0.0
/*508 */     if (!cand_up_right)                                                                                                                      // 0.0
/*510 */         EXTEND(top + size, top[size - 1], size);                                                                                             // 0.0
/*514 */     top[-1] = left[-1];                                                                                                                      // 0.0
/*518 */     // Filtering process                                                                                                                     // 0.0
/*520 */     if (!s->ps.sps->intra_smoothing_disabled_flag && (c_idx == 0  || s->ps.sps->chroma_format_idc == 3)) {                                   // 0.0
/*522 */         if (mode != INTRA_DC && size != 4){                                                                                                  // 0.0
/*524 */             int intra_hor_ver_dist_thresh[] = { 7, 1, 0 };                                                                                   // 0.0
/*526 */             int min_dist_vert_hor = FFMIN(FFABS((int)(mode - 26U)),                                                                          // 0.0
/*528 */                                           FFABS((int)(mode - 10U)));                                                                         // 0.0
/*530 */             if (min_dist_vert_hor > intra_hor_ver_dist_thresh[log2_size - 3]) {                                                              // 0.0
/*532 */                 int threshold = 1 << (BIT_DEPTH - 5);                                                                                        // 0.0
/*534 */                 if (s->ps.sps->sps_strong_intra_smoothing_enable_flag && c_idx == 0 &&                                                       // 0.0
/*536 */                     log2_size == 5 &&                                                                                                        // 0.0
/*538 */                     FFABS(top[-1]  + top[63]  - 2 * top[31])  < threshold &&                                                                 // 0.0
/*540 */                     FFABS(left[-1] + left[63] - 2 * left[31]) < threshold) {                                                                 // 0.0
/*542 */                     // We can't just overwrite values in top because it could be                                                             // 0.0
/*544 */                     // a pointer into src                                                                                                    // 0.0
/*546 */                     filtered_top[-1] = top[-1];                                                                                              // 0.0
/*548 */                     filtered_top[63] = top[63];                                                                                              // 0.0
/*550 */                     for (i = 0; i < 63; i++)                                                                                                 // 0.0
/*552 */                         filtered_top[i] = ((64 - (i + 1)) * top[-1] +                                                                        // 0.0
/*554 */                                            (i + 1)  * top[63] + 32) >> 6;                                                                    // 0.0
/*556 */                     for (i = 0; i < 63; i++)                                                                                                 // 0.0
/*558 */                         left[i] = ((64 - (i + 1)) * left[-1] +                                                                               // 0.0
/*560 */                                    (i + 1)  * left[63] + 32) >> 6;                                                                           // 0.0
/*562 */                     top = filtered_top;                                                                                                      // 0.0
/*564 */                 } else {                                                                                                                     // 0.0
/*566 */                     filtered_left[2 * size - 1] = left[2 * size - 1];                                                                        // 0.0
/*568 */                     filtered_top[2 * size - 1]  = top[2 * size - 1];                                                                         // 0.0
/*570 */                     for (i = 2 * size - 2; i >= 0; i--)                                                                                      // 0.0
/*572 */                         filtered_left[i] = (left[i + 1] + 2 * left[i] +                                                                      // 0.0
/*574 */                                             left[i - 1] + 2) >> 2;                                                                           // 0.0
/*576 */                     filtered_top[-1]  =                                                                                                      // 0.0
/*578 */                     filtered_left[-1] = (left[0] + 2 * left[-1] + top[0] + 2) >> 2;                                                          // 0.0
/*580 */                     for (i = 2 * size - 2; i >= 0; i--)                                                                                      // 0.0
/*582 */                         filtered_top[i] = (top[i + 1] + 2 * top[i] +                                                                         // 0.0
/*584 */                                            top[i - 1] + 2) >> 2;                                                                             // 0.0
/*586 */                     left = filtered_left;                                                                                                    // 0.0
/*588 */                     top  = filtered_top;                                                                                                     // 0.0
/*590 */                 }                                                                                                                            // 0.0
/*592 */             }                                                                                                                                // 0.0
/*594 */         }                                                                                                                                    // 0.0
/*596 */     }                                                                                                                                        // 0.0
/*600 */     switch (mode) {                                                                                                                          // 0.0
/*602 */     case INTRA_PLANAR:                                                                                                                       // 0.0
/*604 */         s->hpc.pred_planar[log2_size - 2]((uint8_t *)src, (uint8_t *)top,                                                                    // 0.0
/*606 */                                           (uint8_t *)left, stride);                                                                          // 0.0
/*608 */         break;                                                                                                                               // 0.0
/*610 */     case INTRA_DC:                                                                                                                           // 0.0
/*612 */         s->hpc.pred_dc((uint8_t *)src, (uint8_t *)top,                                                                                       // 0.0
/*614 */                        (uint8_t *)left, stride, log2_size, c_idx);                                                                           // 0.0
/*616 */         break;                                                                                                                               // 0.0
/*618 */     default:                                                                                                                                 // 0.0
/*620 */         s->hpc.pred_angular[log2_size - 2]((uint8_t *)src, (uint8_t *)top,                                                                   // 0.0
/*622 */                                            (uint8_t *)left, stride, c_idx,                                                                   // 0.0
/*624 */                                            mode);                                                                                            // 0.0
/*626 */         break;                                                                                                                               // 0.0
/*628 */     }                                                                                                                                        // 0.0
/*630 */ }                                                                                                                                            // 0.0
