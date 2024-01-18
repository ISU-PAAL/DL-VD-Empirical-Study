// commit message FFmpeg@cec9395977 (target=1, prob=0.26482373, correct=False): fix some potential arithmetic overflows in pred_direct_motion() and ff_h264_weight_WxH_mmx2().
/*0   */ static inline void pred_direct_motion(H264Context * const h, int *mb_type){                                                          // (10) 0.04297
/*2   */     MpegEncContext * const s = &h->s;                                                                                                // (13) 0.03125
/*4   */     const int mb_xy =   s->mb_x +   s->mb_y*s->mb_stride;                                                                            // (6) 0.06445
/*6   */     const int b8_xy = 2*s->mb_x + 2*s->mb_y*h->b8_stride;                                                                            // (5) 0.06641
/*8   */     const int b4_xy = 4*s->mb_x + 4*s->mb_y*h->b_stride;                                                                             // (7) 0.06445
/*10  */     const int mb_type_col = h->ref_list[1][0].mb_type[mb_xy];                                                                        // (8) 0.05859
/*12  */     const int16_t (*l1mv0)[2] = (const int16_t (*)[2]) &h->ref_list[1][0].motion_val[0][b4_xy];                                      // (0) 0.09766
/*14  */     const int16_t (*l1mv1)[2] = (const int16_t (*)[2]) &h->ref_list[1][0].motion_val[1][b4_xy];                                      // (1) 0.09766
/*16  */     const int8_t *l1ref0 = &h->ref_list[1][0].ref_index[0][b8_xy];                                                                   // (3) 0.07031
/*18  */     const int8_t *l1ref1 = &h->ref_list[1][0].ref_index[1][b8_xy];                                                                   // (2) 0.07031
/*20  */     const int is_b8x8 = IS_8X8(*mb_type);                                                                                            // (11) 0.04297
/*22  */     int sub_mb_type;                                                                                                                 // (15) 0.01953
/*24  */     int i8, i4;                                                                                                                      // (14) 0.01953
/*28  */     if(IS_8X8(mb_type_col) && !h->sps.direct_8x8_inference_flag){                                                                    // (4) 0.06836
/*30  */         /* FIXME save sub mb types from previous frames (or derive from MVs)                                                         // (9) 0.04883
/*32  */          * so we know exactly what block size to use */                                                                              // (12) 0.03711
/*34  */         sub_mb_type = MB_TYPE_8x8|MB_TYPE_P0L0|MB_TYPE_P0L1|MB_TYPE_DIRECT2; /* B_SUB_4x4 */                                         // 0.0
/*36  */         *mb_type =    MB_TYPE_8x8|MB_TYPE_L0L1;                                                                                      // 0.0
/*38  */     }else if(!is_b8x8 && (IS_16X16(mb_type_col) || IS_INTRA(mb_type_col))){                                                          // 0.0
/*40  */         sub_mb_type = MB_TYPE_16x16|MB_TYPE_P0L0|MB_TYPE_P0L1|MB_TYPE_DIRECT2; /* B_SUB_8x8 */                                       // 0.0
/*42  */         *mb_type =    MB_TYPE_16x16|MB_TYPE_P0L0|MB_TYPE_P0L1|MB_TYPE_DIRECT2; /* B_16x16 */                                         // 0.0
/*44  */     }else{                                                                                                                           // 0.0
/*46  */         sub_mb_type = MB_TYPE_16x16|MB_TYPE_P0L0|MB_TYPE_P0L1|MB_TYPE_DIRECT2; /* B_SUB_8x8 */                                       // 0.0
/*48  */         *mb_type =    MB_TYPE_8x8|MB_TYPE_L0L1;                                                                                      // 0.0
/*50  */     }                                                                                                                                // 0.0
/*52  */     if(!is_b8x8)                                                                                                                     // 0.0
/*54  */         *mb_type |= MB_TYPE_DIRECT2;                                                                                                 // 0.0
/*58  */     tprintf("mb_type = %08x, sub_mb_type = %08x, is_b8x8 = %d, mb_type_col = %08x\n", *mb_type, sub_mb_type, is_b8x8, mb_type_col);  // 0.0
/*62  */     if(h->direct_spatial_mv_pred){                                                                                                   // 0.0
/*64  */         int ref[2];                                                                                                                  // 0.0
/*66  */         int mv[2][2];                                                                                                                // 0.0
/*68  */         int list;                                                                                                                    // 0.0
/*72  */         /* ref = min(neighbors) */                                                                                                   // 0.0
/*74  */         for(list=0; list<2; list++){                                                                                                 // 0.0
/*76  */             int refa = h->ref_cache[list][scan8[0] - 1];                                                                             // 0.0
/*78  */             int refb = h->ref_cache[list][scan8[0] - 8];                                                                             // 0.0
/*80  */             int refc = h->ref_cache[list][scan8[0] - 8 + 4];                                                                         // 0.0
/*82  */             if(refc == -2)                                                                                                           // 0.0
/*84  */                 refc = h->ref_cache[list][scan8[0] - 8 - 1];                                                                         // 0.0
/*86  */             ref[list] = refa;                                                                                                        // 0.0
/*88  */             if(ref[list] < 0 || (refb < ref[list] && refb >= 0))                                                                     // 0.0
/*90  */                 ref[list] = refb;                                                                                                    // 0.0
/*92  */             if(ref[list] < 0 || (refc < ref[list] && refc >= 0))                                                                     // 0.0
/*94  */                 ref[list] = refc;                                                                                                    // 0.0
/*96  */             if(ref[list] < 0)                                                                                                        // 0.0
/*98  */                 ref[list] = -1;                                                                                                      // 0.0
/*100 */         }                                                                                                                            // 0.0
/*104 */         if(ref[0] < 0 && ref[1] < 0){                                                                                                // 0.0
/*106 */             ref[0] = ref[1] = 0;                                                                                                     // 0.0
/*108 */             mv[0][0] = mv[0][1] =                                                                                                    // 0.0
/*110 */             mv[1][0] = mv[1][1] = 0;                                                                                                 // 0.0
/*112 */         }else{                                                                                                                       // 0.0
/*114 */             for(list=0; list<2; list++){                                                                                             // 0.0
/*116 */                 if(ref[list] >= 0)                                                                                                   // 0.0
/*118 */                     pred_motion(h, 0, 4, list, ref[list], &mv[list][0], &mv[list][1]);                                               // 0.0
/*120 */                 else                                                                                                                 // 0.0
/*122 */                     mv[list][0] = mv[list][1] = 0;                                                                                   // 0.0
/*124 */             }                                                                                                                        // 0.0
/*126 */         }                                                                                                                            // 0.0
/*130 */         if(ref[1] < 0){                                                                                                              // 0.0
/*132 */             *mb_type &= ~MB_TYPE_P0L1;                                                                                               // 0.0
/*134 */             sub_mb_type &= ~MB_TYPE_P0L1;                                                                                            // 0.0
/*136 */         }else if(ref[0] < 0){                                                                                                        // 0.0
/*138 */             *mb_type &= ~MB_TYPE_P0L0;                                                                                               // 0.0
/*140 */             sub_mb_type &= ~MB_TYPE_P0L0;                                                                                            // 0.0
/*142 */         }                                                                                                                            // 0.0
/*146 */         if(IS_16X16(*mb_type)){                                                                                                      // 0.0
/*148 */             fill_rectangle(&h->ref_cache[0][scan8[0]], 4, 4, 8, ref[0], 1);                                                          // 0.0
/*150 */             fill_rectangle(&h->ref_cache[1][scan8[0]], 4, 4, 8, ref[1], 1);                                                          // 0.0
/*152 */             if(!IS_INTRA(mb_type_col)                                                                                                // 0.0
/*154 */                && (   (l1ref0[0] == 0 && ABS(l1mv0[0][0]) <= 1 && ABS(l1mv0[0][1]) <= 1)                                             // 0.0
/*156 */                    || (l1ref0[0]  < 0 && l1ref1[0] == 0 && ABS(l1mv1[0][0]) <= 1 && ABS(l1mv1[0][1]) <= 1                            // 0.0
/*158 */                        && (h->x264_build>33 || !h->x264_build)))){                                                                   // 0.0
/*160 */                 if(ref[0] > 0)                                                                                                       // 0.0
/*162 */                     fill_rectangle(&h->mv_cache[0][scan8[0]], 4, 4, 8, pack16to32(mv[0][0],mv[0][1]), 4);                            // 0.0
/*164 */                 else                                                                                                                 // 0.0
/*166 */                     fill_rectangle(&h->mv_cache[0][scan8[0]], 4, 4, 8, 0, 4);                                                        // 0.0
/*168 */                 if(ref[1] > 0)                                                                                                       // 0.0
/*170 */                     fill_rectangle(&h->mv_cache[1][scan8[0]], 4, 4, 8, pack16to32(mv[1][0],mv[1][1]), 4);                            // 0.0
/*172 */                 else                                                                                                                 // 0.0
/*174 */                     fill_rectangle(&h->mv_cache[1][scan8[0]], 4, 4, 8, 0, 4);                                                        // 0.0
/*176 */             }else{                                                                                                                   // 0.0
/*178 */                 fill_rectangle(&h->mv_cache[0][scan8[0]], 4, 4, 8, pack16to32(mv[0][0],mv[0][1]), 4);                                // 0.0
/*180 */                 fill_rectangle(&h->mv_cache[1][scan8[0]], 4, 4, 8, pack16to32(mv[1][0],mv[1][1]), 4);                                // 0.0
/*182 */             }                                                                                                                        // 0.0
/*184 */         }else{                                                                                                                       // 0.0
/*186 */             for(i8=0; i8<4; i8++){                                                                                                   // 0.0
/*188 */                 const int x8 = i8&1;                                                                                                 // 0.0
/*190 */                 const int y8 = i8>>1;                                                                                                // 0.0
/*194 */                 if(is_b8x8 && !IS_DIRECT(h->sub_mb_type[i8]))                                                                        // 0.0
/*196 */                     continue;                                                                                                        // 0.0
/*198 */                 h->sub_mb_type[i8] = sub_mb_type;                                                                                    // 0.0
/*202 */                 fill_rectangle(&h->mv_cache[0][scan8[i8*4]], 2, 2, 8, pack16to32(mv[0][0],mv[0][1]), 4);                             // 0.0
/*204 */                 fill_rectangle(&h->mv_cache[1][scan8[i8*4]], 2, 2, 8, pack16to32(mv[1][0],mv[1][1]), 4);                             // 0.0
/*206 */                 fill_rectangle(&h->ref_cache[0][scan8[i8*4]], 2, 2, 8, ref[0], 1);                                                   // 0.0
/*208 */                 fill_rectangle(&h->ref_cache[1][scan8[i8*4]], 2, 2, 8, ref[1], 1);                                                   // 0.0
/*212 */                 /* col_zero_flag */                                                                                                  // 0.0
/*214 */                 if(!IS_INTRA(mb_type_col) && (   l1ref0[x8 + y8*h->b8_stride] == 0                                                   // 0.0
/*216 */                                               || (l1ref0[x8 + y8*h->b8_stride] < 0 && l1ref1[x8 + y8*h->b8_stride] == 0              // 0.0
/*218 */                                                   && (h->x264_build>33 || !h->x264_build)))){                                        // 0.0
/*220 */                     const int16_t (*l1mv)[2]= l1ref0[x8 + y8*h->b8_stride] == 0 ? l1mv0 : l1mv1;                                     // 0.0
/*222 */                     for(i4=0; i4<4; i4++){                                                                                           // 0.0
/*224 */                         const int16_t *mv_col = l1mv[x8*2 + (i4&1) + (y8*2 + (i4>>1))*h->b_stride];                                  // 0.0
/*226 */                         if(ABS(mv_col[0]) <= 1 && ABS(mv_col[1]) <= 1){                                                              // 0.0
/*228 */                             if(ref[0] == 0)                                                                                          // 0.0
/*230 */                                 *(uint32_t*)h->mv_cache[0][scan8[i8*4+i4]] = 0;                                                      // 0.0
/*232 */                             if(ref[1] == 0)                                                                                          // 0.0
/*234 */                                 *(uint32_t*)h->mv_cache[1][scan8[i8*4+i4]] = 0;                                                      // 0.0
/*236 */                         }                                                                                                            // 0.0
/*238 */                     }                                                                                                                // 0.0
/*240 */                 }                                                                                                                    // 0.0
/*242 */             }                                                                                                                        // 0.0
/*244 */         }                                                                                                                            // 0.0
/*246 */     }else{ /* direct temporal mv pred */                                                                                             // 0.0
/*248 */         if(IS_16X16(*mb_type)){                                                                                                      // 0.0
/*250 */             fill_rectangle(&h->ref_cache[1][scan8[0]], 4, 4, 8, 0, 1);                                                               // 0.0
/*252 */             if(IS_INTRA(mb_type_col)){                                                                                               // 0.0
/*254 */                 fill_rectangle(&h->ref_cache[0][scan8[0]], 4, 4, 8, 0, 1);                                                           // 0.0
/*256 */                 fill_rectangle(&h-> mv_cache[0][scan8[0]], 4, 4, 8, 0, 4);                                                           // 0.0
/*258 */                 fill_rectangle(&h-> mv_cache[1][scan8[0]], 4, 4, 8, 0, 4);                                                           // 0.0
/*260 */             }else{                                                                                                                   // 0.0
/*262 */                 const int ref0 = l1ref0[0] >= 0 ? h->map_col_to_list0[0][l1ref0[0]]                                                  // 0.0
/*264 */                                                 : h->map_col_to_list0[1][l1ref1[0]];                                                 // 0.0
/*266 */                 const int dist_scale_factor = h->dist_scale_factor[ref0];                                                            // 0.0
/*268 */                 const int16_t *mv_col = l1ref0[0] >= 0 ? l1mv0[0] : l1mv1[0];                                                        // 0.0
/*270 */                 int mv_l0[2];                                                                                                        // 0.0
/*272 */                 mv_l0[0] = (dist_scale_factor * mv_col[0] + 128) >> 8;                                                               // 0.0
/*274 */                 mv_l0[1] = (dist_scale_factor * mv_col[1] + 128) >> 8;                                                               // 0.0
/*276 */                 fill_rectangle(&h->ref_cache[0][scan8[0]], 4, 4, 8, ref0, 1);                                                        // 0.0
/*278 */                 fill_rectangle(&h-> mv_cache[0][scan8[0]], 4, 4, 8, pack16to32(mv_l0[0],mv_l0[1]), 4);                               // 0.0
/*280 */                 fill_rectangle(&h-> mv_cache[1][scan8[0]], 4, 4, 8, pack16to32(mv_l0[0]-mv_col[0],mv_l0[1]-mv_col[1]), 4);           // 0.0
/*282 */             }                                                                                                                        // 0.0
/*284 */         }else{                                                                                                                       // 0.0
/*286 */             for(i8=0; i8<4; i8++){                                                                                                   // 0.0
/*288 */                 const int x8 = i8&1;                                                                                                 // 0.0
/*290 */                 const int y8 = i8>>1;                                                                                                // 0.0
/*292 */                 int ref0, dist_scale_factor;                                                                                         // 0.0
/*294 */                 const int16_t (*l1mv)[2]= l1mv0;                                                                                     // 0.0
/*298 */                 if(is_b8x8 && !IS_DIRECT(h->sub_mb_type[i8]))                                                                        // 0.0
/*300 */                     continue;                                                                                                        // 0.0
/*302 */                 h->sub_mb_type[i8] = sub_mb_type;                                                                                    // 0.0
/*304 */                 if(IS_INTRA(mb_type_col)){                                                                                           // 0.0
/*306 */                     fill_rectangle(&h->ref_cache[0][scan8[i8*4]], 2, 2, 8, 0, 1);                                                    // 0.0
/*308 */                     fill_rectangle(&h->ref_cache[1][scan8[i8*4]], 2, 2, 8, 0, 1);                                                    // 0.0
/*310 */                     fill_rectangle(&h-> mv_cache[0][scan8[i8*4]], 2, 2, 8, 0, 4);                                                    // 0.0
/*312 */                     fill_rectangle(&h-> mv_cache[1][scan8[i8*4]], 2, 2, 8, 0, 4);                                                    // 0.0
/*314 */                     continue;                                                                                                        // 0.0
/*316 */                 }                                                                                                                    // 0.0
/*320 */                 ref0 = l1ref0[x8 + y8*h->b8_stride];                                                                                 // 0.0
/*322 */                 if(ref0 >= 0)                                                                                                        // 0.0
/*324 */                     ref0 = h->map_col_to_list0[0][ref0];                                                                             // 0.0
/*326 */                 else{                                                                                                                // 0.0
/*328 */                     ref0 = h->map_col_to_list0[1][l1ref1[x8 + y8*h->b8_stride]];                                                     // 0.0
/*330 */                     l1mv= l1mv1;                                                                                                     // 0.0
/*332 */                 }                                                                                                                    // 0.0
/*334 */                 dist_scale_factor = h->dist_scale_factor[ref0];                                                                      // 0.0
/*338 */                 fill_rectangle(&h->ref_cache[0][scan8[i8*4]], 2, 2, 8, ref0, 1);                                                     // 0.0
/*340 */                 fill_rectangle(&h->ref_cache[1][scan8[i8*4]], 2, 2, 8, 0, 1);                                                        // 0.0
/*342 */                 for(i4=0; i4<4; i4++){                                                                                               // 0.0
/*344 */                     const int16_t *mv_col = l1mv[x8*2 + (i4&1) + (y8*2 + (i4>>1))*h->b_stride];                                      // 0.0
/*346 */                     int16_t *mv_l0 = h->mv_cache[0][scan8[i8*4+i4]];                                                                 // 0.0
/*348 */                     mv_l0[0] = (dist_scale_factor * mv_col[0] + 128) >> 8;                                                           // 0.0
/*350 */                     mv_l0[1] = (dist_scale_factor * mv_col[1] + 128) >> 8;                                                           // 0.0
/*352 */                     *(uint32_t*)h->mv_cache[1][scan8[i8*4+i4]] =                                                                     // 0.0
/*354 */                         pack16to32(mv_l0[0]-mv_col[0],mv_l0[1]-mv_col[1]);                                                           // 0.0
/*356 */                 }                                                                                                                    // 0.0
/*358 */             }                                                                                                                        // 0.0
/*360 */         }                                                                                                                            // 0.0
/*362 */     }                                                                                                                                // 0.0
/*364 */ }                                                                                                                                    // 0.0
