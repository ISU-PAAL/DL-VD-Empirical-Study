// commit message FFmpeg@04763c6f87 (target=1, prob=0.35227376, correct=False): h264_direct: use the reference mask from the actual reference
/*0   */ static void pred_spatial_direct_motion(const H264Context *const h, H264SliceContext *sl,        // (4) 0.05273
/*2   */                                        int *mb_type)                                            // (2) 0.08594
/*4   */ {                                                                                               // (21) 0.001953
/*6   */     int b8_stride = 2;                                                                          // (16) 0.02344
/*8   */     int b4_stride = h->b_stride;                                                                // (12) 0.0332
/*10  */     int mb_xy = sl->mb_xy, mb_y = sl->mb_y;                                                     // (5) 0.05078
/*12  */     int mb_type_col[2];                                                                         // (15) 0.02539
/*14  */     const int16_t (*l1mv0)[2], (*l1mv1)[2];                                                     // (6) 0.05078
/*16  */     const int8_t *l1ref0, *l1ref1;                                                              // (9) 0.03906
/*18  */     const int is_b8x8 = IS_8X8(*mb_type);                                                       // (8) 0.04297
/*20  */     unsigned int sub_mb_type = MB_TYPE_L0L1;                                                    // (10) 0.03906
/*22  */     int i8, i4;                                                                                 // (17) 0.01953
/*24  */     int ref[2];                                                                                 // (19) 0.01562
/*26  */     int mv[2];                                                                                  // (18) 0.01758
/*28  */     int list;                                                                                   // (20) 0.01172
/*32  */     assert(sl->ref_list[1][0].reference & 3);                                                   // (11) 0.03711
/*36  */     await_reference_mb_row(h, sl->ref_list[1][0].parent,                                        // (7) 0.04883
/*38  */                            sl->mb_y + !!IS_INTERLACED(*mb_type));                               // (1) 0.08594
/*42  */ #define MB_TYPE_16x16_OR_INTRA (MB_TYPE_16x16 | MB_TYPE_INTRA4x4 | \                            // (3) 0.06641
/*44  */                                 MB_TYPE_INTRA16x16 | MB_TYPE_INTRA_PCM)                         // (0) 0.09961
/*48  */     /* ref = min(neighbors) */                                                                  // (14) 0.02539
/*50  */     for (list = 0; list < 2; list++) {                                                          // (13) 0.03125
/*52  */         int left_ref     = sl->ref_cache[list][scan8[0] - 1];                                   // 0.0
/*54  */         int top_ref      = sl->ref_cache[list][scan8[0] - 8];                                   // 0.0
/*56  */         int refc         = sl->ref_cache[list][scan8[0] - 8 + 4];                               // 0.0
/*58  */         const int16_t *C = sl->mv_cache[list][scan8[0]  - 8 + 4];                               // 0.0
/*60  */         if (refc == PART_NOT_AVAILABLE) {                                                       // 0.0
/*62  */             refc = sl->ref_cache[list][scan8[0] - 8 - 1];                                       // 0.0
/*64  */             C    = sl->mv_cache[list][scan8[0]  - 8 - 1];                                       // 0.0
/*66  */         }                                                                                       // 0.0
/*68  */         ref[list] = FFMIN3((unsigned)left_ref,                                                  // 0.0
/*70  */                            (unsigned)top_ref,                                                   // 0.0
/*72  */                            (unsigned)refc);                                                     // 0.0
/*74  */         if (ref[list] >= 0) {                                                                   // 0.0
/*76  */             /* This is just pred_motion() but with the cases removed that                       // 0.0
/*78  */              * cannot happen for direct blocks. */                                              // 0.0
/*80  */             const int16_t *const A = sl->mv_cache[list][scan8[0] - 1];                          // 0.0
/*82  */             const int16_t *const B = sl->mv_cache[list][scan8[0] - 8];                          // 0.0
/*86  */             int match_count = (left_ref == ref[list]) +                                         // 0.0
/*88  */                               (top_ref  == ref[list]) +                                         // 0.0
/*90  */                               (refc     == ref[list]);                                          // 0.0
/*94  */             if (match_count > 1) { // most common                                               // 0.0
/*96  */                 mv[list] = pack16to32(mid_pred(A[0], B[0], C[0]),                               // 0.0
/*98  */                                       mid_pred(A[1], B[1], C[1]));                              // 0.0
/*100 */             } else {                                                                            // 0.0
/*102 */                 assert(match_count == 1);                                                       // 0.0
/*104 */                 if (left_ref == ref[list])                                                      // 0.0
/*106 */                     mv[list] = AV_RN32A(A);                                                     // 0.0
/*108 */                 else if (top_ref == ref[list])                                                  // 0.0
/*110 */                     mv[list] = AV_RN32A(B);                                                     // 0.0
/*112 */                 else                                                                            // 0.0
/*114 */                     mv[list] = AV_RN32A(C);                                                     // 0.0
/*116 */             }                                                                                   // 0.0
/*118 */         } else {                                                                                // 0.0
/*120 */             int mask = ~(MB_TYPE_L0 << (2 * list));                                             // 0.0
/*122 */             mv[list]  = 0;                                                                      // 0.0
/*124 */             ref[list] = -1;                                                                     // 0.0
/*126 */             if (!is_b8x8)                                                                       // 0.0
/*128 */                 *mb_type &= mask;                                                               // 0.0
/*130 */             sub_mb_type &= mask;                                                                // 0.0
/*132 */         }                                                                                       // 0.0
/*134 */     }                                                                                           // 0.0
/*136 */     if (ref[0] < 0 && ref[1] < 0) {                                                             // 0.0
/*138 */         ref[0] = ref[1] = 0;                                                                    // 0.0
/*140 */         if (!is_b8x8)                                                                           // 0.0
/*142 */             *mb_type |= MB_TYPE_L0L1;                                                           // 0.0
/*144 */         sub_mb_type |= MB_TYPE_L0L1;                                                            // 0.0
/*146 */     }                                                                                           // 0.0
/*150 */     if (!(is_b8x8 | mv[0] | mv[1])) {                                                           // 0.0
/*152 */         fill_rectangle(&sl->ref_cache[0][scan8[0]], 4, 4, 8, (uint8_t)ref[0], 1);               // 0.0
/*154 */         fill_rectangle(&sl->ref_cache[1][scan8[0]], 4, 4, 8, (uint8_t)ref[1], 1);               // 0.0
/*156 */         fill_rectangle(&sl->mv_cache[0][scan8[0]], 4, 4, 8, 0, 4);                              // 0.0
/*158 */         fill_rectangle(&sl->mv_cache[1][scan8[0]], 4, 4, 8, 0, 4);                              // 0.0
/*160 */         *mb_type = (*mb_type & ~(MB_TYPE_8x8 | MB_TYPE_16x8 | MB_TYPE_8x16 |                    // 0.0
/*162 */                                  MB_TYPE_P1L0 | MB_TYPE_P1L1)) |                                // 0.0
/*164 */                    MB_TYPE_16x16 | MB_TYPE_DIRECT2;                                             // 0.0
/*166 */         return;                                                                                 // 0.0
/*168 */     }                                                                                           // 0.0
/*172 */     if (IS_INTERLACED(sl->ref_list[1][0].parent->mb_type[mb_xy])) { // AFL/AFR/FR/FL -> AFL/FL  // 0.0
/*174 */         if (!IS_INTERLACED(*mb_type)) {                    //     AFR/FR    -> AFL/FL           // 0.0
/*176 */             mb_y  = (sl->mb_y & ~1) + sl->col_parity;                                           // 0.0
/*178 */             mb_xy = sl->mb_x +                                                                  // 0.0
/*180 */                     ((sl->mb_y & ~1) + sl->col_parity) * h->mb_stride;                          // 0.0
/*182 */             b8_stride = 0;                                                                      // 0.0
/*184 */         } else {                                                                                // 0.0
/*186 */             mb_y  += sl->col_fieldoff;                                                          // 0.0
/*188 */             mb_xy += h->mb_stride * sl->col_fieldoff; // non-zero for FL -> FL & differ parity  // 0.0
/*190 */         }                                                                                       // 0.0
/*192 */         goto single_col;                                                                        // 0.0
/*194 */     } else {                                             // AFL/AFR/FR/FL -> AFR/FR             // 0.0
/*196 */         if (IS_INTERLACED(*mb_type)) {                   // AFL       /FL -> AFR/FR             // 0.0
/*198 */             mb_y           =  sl->mb_y & ~1;                                                    // 0.0
/*200 */             mb_xy          = (sl->mb_y & ~1) * h->mb_stride + sl->mb_x;                         // 0.0
/*202 */             mb_type_col[0] = sl->ref_list[1][0].parent->mb_type[mb_xy];                         // 0.0
/*204 */             mb_type_col[1] = sl->ref_list[1][0].parent->mb_type[mb_xy + h->mb_stride];          // 0.0
/*206 */             b8_stride      = 2 + 4 * h->mb_stride;                                              // 0.0
/*208 */             b4_stride     *= 6;                                                                 // 0.0
/*210 */             if (IS_INTERLACED(mb_type_col[0]) !=                                                // 0.0
/*212 */                 IS_INTERLACED(mb_type_col[1])) {                                                // 0.0
/*214 */                 mb_type_col[0] &= ~MB_TYPE_INTERLACED;                                          // 0.0
/*216 */                 mb_type_col[1] &= ~MB_TYPE_INTERLACED;                                          // 0.0
/*218 */             }                                                                                   // 0.0
/*222 */             sub_mb_type |= MB_TYPE_16x16 | MB_TYPE_DIRECT2; /* B_SUB_8x8 */                     // 0.0
/*224 */             if ((mb_type_col[0] & MB_TYPE_16x16_OR_INTRA) &&                                    // 0.0
/*226 */                 (mb_type_col[1] & MB_TYPE_16x16_OR_INTRA) &&                                    // 0.0
/*228 */                 !is_b8x8) {                                                                     // 0.0
/*230 */                 *mb_type |= MB_TYPE_16x8 | MB_TYPE_DIRECT2;  /* B_16x8 */                       // 0.0
/*232 */             } else {                                                                            // 0.0
/*234 */                 *mb_type |= MB_TYPE_8x8;                                                        // 0.0
/*236 */             }                                                                                   // 0.0
/*238 */         } else {                                         //     AFR/FR    -> AFR/FR             // 0.0
/*240 */ single_col:                                                                                     // 0.0
/*242 */             mb_type_col[0] =                                                                    // 0.0
/*244 */             mb_type_col[1] = sl->ref_list[1][0].parent->mb_type[mb_xy];                         // 0.0
/*248 */             sub_mb_type |= MB_TYPE_16x16 | MB_TYPE_DIRECT2; /* B_SUB_8x8 */                     // 0.0
/*250 */             if (!is_b8x8 && (mb_type_col[0] & MB_TYPE_16x16_OR_INTRA)) {                        // 0.0
/*252 */                 *mb_type |= MB_TYPE_16x16 | MB_TYPE_DIRECT2; /* B_16x16 */                      // 0.0
/*254 */             } else if (!is_b8x8 &&                                                              // 0.0
/*256 */                        (mb_type_col[0] & (MB_TYPE_16x8 | MB_TYPE_8x16))) {                      // 0.0
/*258 */                 *mb_type |= MB_TYPE_DIRECT2 |                                                   // 0.0
/*260 */                             (mb_type_col[0] & (MB_TYPE_16x8 | MB_TYPE_8x16));                   // 0.0
/*262 */             } else {                                                                            // 0.0
/*264 */                 if (!h->ps.sps->direct_8x8_inference_flag) {                                    // 0.0
/*266 */                     /* FIXME: Save sub mb types from previous frames (or derive                 // 0.0
/*268 */                      * from MVs) so we know exactly what block size to use. */                  // 0.0
/*270 */                     sub_mb_type += (MB_TYPE_8x8 - MB_TYPE_16x16); /* B_SUB_4x4 */               // 0.0
/*272 */                 }                                                                               // 0.0
/*274 */                 *mb_type |= MB_TYPE_8x8;                                                        // 0.0
/*276 */             }                                                                                   // 0.0
/*278 */         }                                                                                       // 0.0
/*280 */     }                                                                                           // 0.0
/*284 */     await_reference_mb_row(h, sl->ref_list[1][0].parent, mb_y);                                 // 0.0
/*288 */     l1mv0  = &sl->ref_list[1][0].parent->motion_val[0][h->mb2b_xy[mb_xy]];                      // 0.0
/*290 */     l1mv1  = &sl->ref_list[1][0].parent->motion_val[1][h->mb2b_xy[mb_xy]];                      // 0.0
/*292 */     l1ref0 = &sl->ref_list[1][0].parent->ref_index[0][4 * mb_xy];                               // 0.0
/*294 */     l1ref1 = &sl->ref_list[1][0].parent->ref_index[1][4 * mb_xy];                               // 0.0
/*296 */     if (!b8_stride) {                                                                           // 0.0
/*298 */         if (sl->mb_y & 1) {                                                                     // 0.0
/*300 */             l1ref0 += 2;                                                                        // 0.0
/*302 */             l1ref1 += 2;                                                                        // 0.0
/*304 */             l1mv0  += 2 * b4_stride;                                                            // 0.0
/*306 */             l1mv1  += 2 * b4_stride;                                                            // 0.0
/*308 */         }                                                                                       // 0.0
/*310 */     }                                                                                           // 0.0
/*314 */     if (IS_INTERLACED(*mb_type) != IS_INTERLACED(mb_type_col[0])) {                             // 0.0
/*316 */         int n = 0;                                                                              // 0.0
/*318 */         for (i8 = 0; i8 < 4; i8++) {                                                            // 0.0
/*320 */             int x8  = i8 & 1;                                                                   // 0.0
/*322 */             int y8  = i8 >> 1;                                                                  // 0.0
/*324 */             int xy8 = x8     + y8 * b8_stride;                                                  // 0.0
/*326 */             int xy4 = x8 * 3 + y8 * b4_stride;                                                  // 0.0
/*328 */             int a, b;                                                                           // 0.0
/*332 */             if (is_b8x8 && !IS_DIRECT(sl->sub_mb_type[i8]))                                     // 0.0
/*334 */                 continue;                                                                       // 0.0
/*336 */             sl->sub_mb_type[i8] = sub_mb_type;                                                  // 0.0
/*340 */             fill_rectangle(&sl->ref_cache[0][scan8[i8 * 4]], 2, 2, 8,                           // 0.0
/*342 */                            (uint8_t)ref[0], 1);                                                 // 0.0
/*344 */             fill_rectangle(&sl->ref_cache[1][scan8[i8 * 4]], 2, 2, 8,                           // 0.0
/*346 */                            (uint8_t)ref[1], 1);                                                 // 0.0
/*348 */             if (!IS_INTRA(mb_type_col[y8]) && !sl->ref_list[1][0].parent->long_ref &&           // 0.0
/*350 */                 ((l1ref0[xy8] == 0 &&                                                           // 0.0
/*352 */                   FFABS(l1mv0[xy4][0]) <= 1 &&                                                  // 0.0
/*354 */                   FFABS(l1mv0[xy4][1]) <= 1) ||                                                 // 0.0
/*356 */                  (l1ref0[xy8] < 0 &&                                                            // 0.0
/*358 */                   l1ref1[xy8] == 0 &&                                                           // 0.0
/*360 */                   FFABS(l1mv1[xy4][0]) <= 1 &&                                                  // 0.0
/*362 */                   FFABS(l1mv1[xy4][1]) <= 1))) {                                                // 0.0
/*364 */                 a =                                                                             // 0.0
/*366 */                 b = 0;                                                                          // 0.0
/*368 */                 if (ref[0] > 0)                                                                 // 0.0
/*370 */                     a = mv[0];                                                                  // 0.0
/*372 */                 if (ref[1] > 0)                                                                 // 0.0
/*374 */                     b = mv[1];                                                                  // 0.0
/*376 */                 n++;                                                                            // 0.0
/*378 */             } else {                                                                            // 0.0
/*380 */                 a = mv[0];                                                                      // 0.0
/*382 */                 b = mv[1];                                                                      // 0.0
/*384 */             }                                                                                   // 0.0
/*386 */             fill_rectangle(&sl->mv_cache[0][scan8[i8 * 4]], 2, 2, 8, a, 4);                     // 0.0
/*388 */             fill_rectangle(&sl->mv_cache[1][scan8[i8 * 4]], 2, 2, 8, b, 4);                     // 0.0
/*390 */         }                                                                                       // 0.0
/*392 */         if (!is_b8x8 && !(n & 3))                                                               // 0.0
/*394 */             *mb_type = (*mb_type & ~(MB_TYPE_8x8 | MB_TYPE_16x8 | MB_TYPE_8x16 |                // 0.0
/*396 */                                      MB_TYPE_P1L0 | MB_TYPE_P1L1)) |                            // 0.0
/*398 */                        MB_TYPE_16x16 | MB_TYPE_DIRECT2;                                         // 0.0
/*400 */     } else if (IS_16X16(*mb_type)) {                                                            // 0.0
/*402 */         int a, b;                                                                               // 0.0
/*406 */         fill_rectangle(&sl->ref_cache[0][scan8[0]], 4, 4, 8, (uint8_t)ref[0], 1);               // 0.0
/*408 */         fill_rectangle(&sl->ref_cache[1][scan8[0]], 4, 4, 8, (uint8_t)ref[1], 1);               // 0.0
/*410 */         if (!IS_INTRA(mb_type_col[0]) && !sl->ref_list[1][0].parent->long_ref &&                // 0.0
/*412 */             ((l1ref0[0] == 0 &&                                                                 // 0.0
/*414 */               FFABS(l1mv0[0][0]) <= 1 &&                                                        // 0.0
/*416 */               FFABS(l1mv0[0][1]) <= 1) ||                                                       // 0.0
/*418 */              (l1ref0[0] < 0 && !l1ref1[0] &&                                                    // 0.0
/*420 */               FFABS(l1mv1[0][0]) <= 1 &&                                                        // 0.0
/*422 */               FFABS(l1mv1[0][1]) <= 1 &&                                                        // 0.0
/*424 */               h->sei.unregistered.x264_build > 33U))) {                                         // 0.0
/*426 */             a = b = 0;                                                                          // 0.0
/*428 */             if (ref[0] > 0)                                                                     // 0.0
/*430 */                 a = mv[0];                                                                      // 0.0
/*432 */             if (ref[1] > 0)                                                                     // 0.0
/*434 */                 b = mv[1];                                                                      // 0.0
/*436 */         } else {                                                                                // 0.0
/*438 */             a = mv[0];                                                                          // 0.0
/*440 */             b = mv[1];                                                                          // 0.0
/*442 */         }                                                                                       // 0.0
/*444 */         fill_rectangle(&sl->mv_cache[0][scan8[0]], 4, 4, 8, a, 4);                              // 0.0
/*446 */         fill_rectangle(&sl->mv_cache[1][scan8[0]], 4, 4, 8, b, 4);                              // 0.0
/*448 */     } else {                                                                                    // 0.0
/*450 */         int n = 0;                                                                              // 0.0
/*452 */         for (i8 = 0; i8 < 4; i8++) {                                                            // 0.0
/*454 */             const int x8 = i8 & 1;                                                              // 0.0
/*456 */             const int y8 = i8 >> 1;                                                             // 0.0
/*460 */             if (is_b8x8 && !IS_DIRECT(sl->sub_mb_type[i8]))                                     // 0.0
/*462 */                 continue;                                                                       // 0.0
/*464 */             sl->sub_mb_type[i8] = sub_mb_type;                                                  // 0.0
/*468 */             fill_rectangle(&sl->mv_cache[0][scan8[i8 * 4]], 2, 2, 8, mv[0], 4);                 // 0.0
/*470 */             fill_rectangle(&sl->mv_cache[1][scan8[i8 * 4]], 2, 2, 8, mv[1], 4);                 // 0.0
/*472 */             fill_rectangle(&sl->ref_cache[0][scan8[i8 * 4]], 2, 2, 8,                           // 0.0
/*474 */                            (uint8_t)ref[0], 1);                                                 // 0.0
/*476 */             fill_rectangle(&sl->ref_cache[1][scan8[i8 * 4]], 2, 2, 8,                           // 0.0
/*478 */                            (uint8_t)ref[1], 1);                                                 // 0.0
/*482 */             assert(b8_stride == 2);                                                             // 0.0
/*484 */             /* col_zero_flag */                                                                 // 0.0
/*486 */             if (!IS_INTRA(mb_type_col[0]) && !sl->ref_list[1][0].parent->long_ref &&            // 0.0
/*488 */                 (l1ref0[i8] == 0 ||                                                             // 0.0
/*490 */                  (l1ref0[i8] < 0 &&                                                             // 0.0
/*492 */                   l1ref1[i8] == 0 &&                                                            // 0.0
/*494 */                   h->sei.unregistered.x264_build > 33U))) {                                     // 0.0
/*496 */                 const int16_t (*l1mv)[2] = l1ref0[i8] == 0 ? l1mv0 : l1mv1;                     // 0.0
/*498 */                 if (IS_SUB_8X8(sub_mb_type)) {                                                  // 0.0
/*500 */                     const int16_t *mv_col = l1mv[x8 * 3 + y8 * 3 * b4_stride];                  // 0.0
/*502 */                     if (FFABS(mv_col[0]) <= 1 && FFABS(mv_col[1]) <= 1) {                       // 0.0
/*504 */                         if (ref[0] == 0)                                                        // 0.0
/*506 */                             fill_rectangle(&sl->mv_cache[0][scan8[i8 * 4]], 2, 2,               // 0.0
/*508 */                                            8, 0, 4);                                            // 0.0
/*510 */                         if (ref[1] == 0)                                                        // 0.0
/*512 */                             fill_rectangle(&sl->mv_cache[1][scan8[i8 * 4]], 2, 2,               // 0.0
/*514 */                                            8, 0, 4);                                            // 0.0
/*516 */                         n += 4;                                                                 // 0.0
/*518 */                     }                                                                           // 0.0
/*520 */                 } else {                                                                        // 0.0
/*522 */                     int m = 0;                                                                  // 0.0
/*524 */                     for (i4 = 0; i4 < 4; i4++) {                                                // 0.0
/*526 */                         const int16_t *mv_col = l1mv[x8 * 2 + (i4 & 1) +                        // 0.0
/*528 */                                                      (y8 * 2 + (i4 >> 1)) * b4_stride];         // 0.0
/*530 */                         if (FFABS(mv_col[0]) <= 1 && FFABS(mv_col[1]) <= 1) {                   // 0.0
/*532 */                             if (ref[0] == 0)                                                    // 0.0
/*534 */                                 AV_ZERO32(sl->mv_cache[0][scan8[i8 * 4 + i4]]);                 // 0.0
/*536 */                             if (ref[1] == 0)                                                    // 0.0
/*538 */                                 AV_ZERO32(sl->mv_cache[1][scan8[i8 * 4 + i4]]);                 // 0.0
/*540 */                             m++;                                                                // 0.0
/*542 */                         }                                                                       // 0.0
/*544 */                     }                                                                           // 0.0
/*546 */                     if (!(m & 3))                                                               // 0.0
/*548 */                         sl->sub_mb_type[i8] += MB_TYPE_16x16 - MB_TYPE_8x8;                     // 0.0
/*550 */                     n += m;                                                                     // 0.0
/*552 */                 }                                                                               // 0.0
/*554 */             }                                                                                   // 0.0
/*556 */         }                                                                                       // 0.0
/*558 */         if (!is_b8x8 && !(n & 15))                                                              // 0.0
/*560 */             *mb_type = (*mb_type & ~(MB_TYPE_8x8 | MB_TYPE_16x8 | MB_TYPE_8x16 |                // 0.0
/*562 */                                      MB_TYPE_P1L0 | MB_TYPE_P1L1)) |                            // 0.0
/*564 */                        MB_TYPE_16x16 | MB_TYPE_DIRECT2;                                         // 0.0
/*566 */     }                                                                                           // 0.0
/*568 */ }                                                                                               // 0.0
