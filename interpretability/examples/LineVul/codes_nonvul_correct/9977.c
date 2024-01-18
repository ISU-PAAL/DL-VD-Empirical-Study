// commit message FFmpeg@3622988f21 (target=0, prob=0.3776063, correct=True): oops, other half of the vismv patch
/*0   */ static inline void pred_direct_motion(H264Context * const h, int *mb_type){                                                          // (10) 0.04298
/*2   */     MpegEncContext * const s = &h->s;                                                                                                // (13) 0.03125
/*4   */     const int mb_xy =   s->mb_x +   s->mb_y*s->mb_stride;                                                                            // (5) 0.06445
/*6   */     const int b8_xy = 2*s->mb_x + 2*s->mb_y*h->b8_stride;                                                                            // (4) 0.0664
/*8   */     const int b4_xy = 4*s->mb_x + 4*s->mb_y*h->b_stride;                                                                             // (6) 0.06445
/*10  */     const int mb_type_col = h->ref_list[1][0].mb_type[mb_xy];                                                                        // (7) 0.05859
/*12  */     const int16_t (*l1mv0)[2] = (const int16_t (*)[2]) &h->ref_list[1][0].motion_val[0][b4_xy];                                      // (1) 0.09765
/*14  */     const int8_t *l1ref0 = &h->ref_list[1][0].ref_index[0][b8_xy];                                                                   // (2) 0.07031
/*16  */     const int is_b8x8 = IS_8X8(*mb_type);                                                                                            // (11) 0.04297
/*18  */     int sub_mb_type;                                                                                                                 // (15) 0.01953
/*20  */     int i8, i4;                                                                                                                      // (14) 0.01954
/*24  */     if(IS_8X8(mb_type_col) && !h->sps.direct_8x8_inference_flag){                                                                    // (3) 0.06837
/*26  */         /* FIXME save sub mb types from previous frames (or derive from MVs)                                                         // (8) 0.04883
/*28  */          * so we know exactly what block size to use */                                                                              // (12) 0.03711
/*30  */         sub_mb_type = MB_TYPE_8x8|MB_TYPE_P0L0|MB_TYPE_P0L1|MB_TYPE_DIRECT2; /* B_SUB_4x4 */                                         // (0) 0.1113
/*32  */         *mb_type =    MB_TYPE_8x8;                                                                                                   // (9) 0.04492
/*34  */     }else if(!is_b8x8 && (IS_16X16(mb_type_col) || IS_INTRA(mb_type_col))){                                                          // 0.0
/*36  */         sub_mb_type = MB_TYPE_16x16|MB_TYPE_P0L0|MB_TYPE_P0L1|MB_TYPE_DIRECT2; /* B_SUB_8x8 */                                       // 0.0
/*38  */         *mb_type =    MB_TYPE_16x16|MB_TYPE_P0L0|MB_TYPE_P0L1|MB_TYPE_DIRECT2; /* B_16x16 */                                         // 0.0
/*40  */     }else{                                                                                                                           // 0.0
/*42  */         sub_mb_type = MB_TYPE_16x16|MB_TYPE_P0L0|MB_TYPE_P0L1|MB_TYPE_DIRECT2; /* B_SUB_8x8 */                                       // 0.0
/*44  */         *mb_type =    MB_TYPE_8x8;                                                                                                   // 0.0
/*46  */     }                                                                                                                                // (16) 0.007813
/*48  */     if(!is_b8x8)                                                                                                                     // 0.0
/*50  */         *mb_type |= MB_TYPE_DIRECT2;                                                                                                 // 0.0
/*54  */     tprintf("mb_type = %08x, sub_mb_type = %08x, is_b8x8 = %d, mb_type_col = %08x\n", *mb_type, sub_mb_type, is_b8x8, mb_type_col);  // 0.0
/*56  */                                                                                                                                      // 0.0
/*58  */     if(h->direct_spatial_mv_pred){                                                                                                   // 0.0
/*60  */         int ref[2];                                                                                                                  // 0.0
/*62  */         int mv[2][2];                                                                                                                // 0.0
/*64  */         int list;                                                                                                                    // 0.0
/*68  */         /* ref = min(neighbors) */                                                                                                   // 0.0
/*70  */         for(list=0; list<2; list++){                                                                                                 // 0.0
/*72  */             int refa = h->ref_cache[list][scan8[0] - 1];                                                                             // 0.0
/*74  */             int refb = h->ref_cache[list][scan8[0] - 8];                                                                             // 0.0
/*76  */             int refc = h->ref_cache[list][scan8[0] - 8 + 4];                                                                         // 0.0
/*78  */             if(refc == -2)                                                                                                           // 0.0
/*80  */                 refc = h->ref_cache[list][scan8[0] - 8 - 1];                                                                         // 0.0
/*82  */             ref[list] = refa;                                                                                                        // 0.0
/*84  */             if(ref[list] < 0 || (refb < ref[list] && refb >= 0))                                                                     // 0.0
/*86  */                 ref[list] = refb;                                                                                                    // 0.0
/*88  */             if(ref[list] < 0 || (refc < ref[list] && refc >= 0))                                                                     // 0.0
/*90  */                 ref[list] = refc;                                                                                                    // 0.0
/*92  */             if(ref[list] < 0)                                                                                                        // 0.0
/*94  */                 ref[list] = -1;                                                                                                      // 0.0
/*96  */         }                                                                                                                            // 0.0
/*100 */         if(ref[0] < 0 && ref[1] < 0){                                                                                                // 0.0
/*102 */             ref[0] = ref[1] = 0;                                                                                                     // 0.0
/*104 */             mv[0][0] = mv[0][1] =                                                                                                    // 0.0
/*106 */             mv[1][0] = mv[1][1] = 0;                                                                                                 // 0.0
/*108 */         }else{                                                                                                                       // 0.0
/*110 */             for(list=0; list<2; list++){                                                                                             // 0.0
/*112 */                 if(ref[list] >= 0)                                                                                                   // 0.0
/*114 */                     pred_motion(h, 0, 4, list, ref[list], &mv[list][0], &mv[list][1]);                                               // 0.0
/*116 */                 else                                                                                                                 // 0.0
/*118 */                     mv[list][0] = mv[list][1] = 0;                                                                                   // 0.0
/*120 */             }                                                                                                                        // 0.0
/*122 */         }                                                                                                                            // 0.0
/*126 */         if(ref[1] < 0){                                                                                                              // 0.0
/*128 */             *mb_type &= ~MB_TYPE_P0L1;                                                                                               // 0.0
/*130 */             sub_mb_type &= ~MB_TYPE_P0L1;                                                                                            // 0.0
/*132 */         }else if(ref[0] < 0){                                                                                                        // 0.0
/*134 */             *mb_type &= ~MB_TYPE_P0L0;                                                                                               // 0.0
/*136 */             sub_mb_type &= ~MB_TYPE_P0L0;                                                                                            // 0.0
/*138 */         }                                                                                                                            // 0.0
/*142 */         if(IS_16X16(*mb_type)){                                                                                                      // 0.0
/*144 */             fill_rectangle(&h->ref_cache[0][scan8[0]], 4, 4, 8, ref[0], 1);                                                          // 0.0
/*146 */             fill_rectangle(&h->ref_cache[1][scan8[0]], 4, 4, 8, ref[1], 1);                                                          // 0.0
/*148 */             if(!IS_INTRA(mb_type_col) && l1ref0[0] == 0 &&                                                                           // 0.0
/*150 */                 ABS(l1mv0[0][0]) <= 1 && ABS(l1mv0[0][1]) <= 1){                                                                     // 0.0
/*152 */                 if(ref[0] > 0)                                                                                                       // 0.0
/*154 */                     fill_rectangle(&h->mv_cache[0][scan8[0]], 4, 4, 8, pack16to32(mv[0][0],mv[0][1]), 4);                            // 0.0
/*156 */                 else                                                                                                                 // 0.0
/*158 */                     fill_rectangle(&h->mv_cache[0][scan8[0]], 4, 4, 8, 0, 4);                                                        // 0.0
/*160 */                 if(ref[1] > 0)                                                                                                       // 0.0
/*162 */                     fill_rectangle(&h->mv_cache[1][scan8[0]], 4, 4, 8, pack16to32(mv[1][0],mv[1][1]), 4);                            // 0.0
/*164 */                 else                                                                                                                 // 0.0
/*166 */                     fill_rectangle(&h->mv_cache[1][scan8[0]], 4, 4, 8, 0, 4);                                                        // 0.0
/*168 */             }else{                                                                                                                   // 0.0
/*170 */                 fill_rectangle(&h->mv_cache[0][scan8[0]], 4, 4, 8, pack16to32(mv[0][0],mv[0][1]), 4);                                // 0.0
/*172 */                 fill_rectangle(&h->mv_cache[1][scan8[0]], 4, 4, 8, pack16to32(mv[1][0],mv[1][1]), 4);                                // 0.0
/*174 */             }                                                                                                                        // 0.0
/*176 */         }else{                                                                                                                       // 0.0
/*178 */             for(i8=0; i8<4; i8++){                                                                                                   // 0.0
/*180 */                 const int x8 = i8&1;                                                                                                 // 0.0
/*182 */                 const int y8 = i8>>1;                                                                                                // 0.0
/*184 */                                                                                                                                      // 0.0
/*186 */                 if(is_b8x8 && !IS_DIRECT(h->sub_mb_type[i8]))                                                                        // 0.0
/*188 */                     continue;                                                                                                        // 0.0
/*190 */                 h->sub_mb_type[i8] = sub_mb_type;                                                                                    // 0.0
/*192 */                                                                                                                                      // 0.0
/*194 */                 fill_rectangle(&h->mv_cache[0][scan8[i8*4]], 2, 2, 8, pack16to32(mv[0][0],mv[0][1]), 4);                             // 0.0
/*196 */                 fill_rectangle(&h->mv_cache[1][scan8[i8*4]], 2, 2, 8, pack16to32(mv[1][0],mv[1][1]), 4);                             // 0.0
/*198 */                 fill_rectangle(&h->ref_cache[0][scan8[i8*4]], 2, 2, 8, ref[0], 1);                                                   // 0.0
/*200 */                 fill_rectangle(&h->ref_cache[1][scan8[i8*4]], 2, 2, 8, ref[1], 1);                                                   // 0.0
/*202 */                                                                                                                                      // 0.0
/*204 */                 /* col_zero_flag */                                                                                                  // 0.0
/*206 */                 if(!IS_INTRA(mb_type_col) && l1ref0[x8 + y8*h->b8_stride] == 0){                                                     // 0.0
/*208 */                     for(i4=0; i4<4; i4++){                                                                                           // 0.0
/*210 */                         const int16_t *mv_col = l1mv0[x8*2 + (i4&1) + (y8*2 + (i4>>1))*h->b_stride];                                 // 0.0
/*212 */                         if(ABS(mv_col[0]) <= 1 && ABS(mv_col[1]) <= 1){                                                              // 0.0
/*214 */                             if(ref[0] == 0)                                                                                          // 0.0
/*216 */                                 *(uint32_t*)h->mv_cache[0][scan8[i8*4+i4]] = 0;                                                      // 0.0
/*218 */                             if(ref[1] == 0)                                                                                          // 0.0
/*220 */                                 *(uint32_t*)h->mv_cache[1][scan8[i8*4+i4]] = 0;                                                      // 0.0
/*222 */                         }                                                                                                            // 0.0
/*224 */                     }                                                                                                                // 0.0
/*226 */                 }                                                                                                                    // 0.0
/*228 */             }                                                                                                                        // 0.0
/*230 */         }                                                                                                                            // 0.0
/*232 */     }else{ /* direct temporal mv pred */                                                                                             // 0.0
/*234 */         /* FIXME assumes that L1ref0 used the same ref lists as current frame */                                                     // 0.0
/*236 */         if(IS_16X16(*mb_type)){                                                                                                      // 0.0
/*238 */             fill_rectangle(&h->ref_cache[1][scan8[0]], 4, 4, 8, 0, 1);                                                               // 0.0
/*240 */             if(IS_INTRA(mb_type_col)){                                                                                               // 0.0
/*242 */                 fill_rectangle(&h->ref_cache[0][scan8[0]], 4, 4, 8, 0, 1);                                                           // 0.0
/*244 */                 fill_rectangle(&h-> mv_cache[0][scan8[0]], 4, 4, 8, 0, 4);                                                           // 0.0
/*246 */                 fill_rectangle(&h-> mv_cache[1][scan8[0]], 4, 4, 8, 0, 4);                                                           // 0.0
/*248 */             }else{                                                                                                                   // 0.0
/*250 */                 const int ref0 = l1ref0[0];                                                                                          // 0.0
/*252 */                 const int dist_scale_factor = h->dist_scale_factor[ref0];                                                            // 0.0
/*254 */                 const int16_t *mv_col = l1mv0[0];                                                                                    // 0.0
/*256 */                 int mv_l0[2];                                                                                                        // 0.0
/*258 */                 mv_l0[0] = (dist_scale_factor * mv_col[0] + 128) >> 8;                                                               // 0.0
/*260 */                 mv_l0[1] = (dist_scale_factor * mv_col[1] + 128) >> 8;                                                               // 0.0
/*262 */                 fill_rectangle(&h->ref_cache[0][scan8[0]], 4, 4, 8, ref0, 1);                                                        // 0.0
/*264 */                 fill_rectangle(&h-> mv_cache[0][scan8[0]], 4, 4, 8, pack16to32(mv_l0[0],mv_l0[1]), 4);                               // 0.0
/*266 */                 fill_rectangle(&h-> mv_cache[1][scan8[0]], 4, 4, 8, pack16to32(mv_l0[0]-mv_col[0],mv_l0[1]-mv_col[1]), 4);           // 0.0
/*268 */             }                                                                                                                        // 0.0
/*270 */         }else{                                                                                                                       // 0.0
/*272 */             for(i8=0; i8<4; i8++){                                                                                                   // 0.0
/*274 */                 const int x8 = i8&1;                                                                                                 // 0.0
/*276 */                 const int y8 = i8>>1;                                                                                                // 0.0
/*278 */                 int ref0, dist_scale_factor;                                                                                         // 0.0
/*280 */                                                                                                                                      // 0.0
/*282 */                 if(is_b8x8 && !IS_DIRECT(h->sub_mb_type[i8]))                                                                        // 0.0
/*284 */                     continue;                                                                                                        // 0.0
/*286 */                 h->sub_mb_type[i8] = sub_mb_type;                                                                                    // 0.0
/*288 */                 if(IS_INTRA(mb_type_col)){                                                                                           // 0.0
/*290 */                     fill_rectangle(&h->ref_cache[0][scan8[i8*4]], 2, 2, 8, 0, 1);                                                    // 0.0
/*292 */                     fill_rectangle(&h->ref_cache[1][scan8[i8*4]], 2, 2, 8, 0, 1);                                                    // 0.0
/*294 */                     fill_rectangle(&h-> mv_cache[0][scan8[i8*4]], 2, 2, 8, 0, 4);                                                    // 0.0
/*296 */                     fill_rectangle(&h-> mv_cache[1][scan8[i8*4]], 2, 2, 8, 0, 4);                                                    // 0.0
/*298 */                     continue;                                                                                                        // 0.0
/*300 */                 }                                                                                                                    // 0.0
/*302 */                                                                                                                                      // 0.0
/*304 */                 ref0 = l1ref0[x8 + y8*h->b8_stride];                                                                                 // 0.0
/*306 */                 dist_scale_factor = h->dist_scale_factor[ref0];                                                                      // 0.0
/*308 */                                                                                                                                      // 0.0
/*310 */                 fill_rectangle(&h->ref_cache[0][scan8[i8*4]], 2, 2, 8, ref0, 1);                                                     // 0.0
/*312 */                 fill_rectangle(&h->ref_cache[1][scan8[i8*4]], 2, 2, 8, 0, 1);                                                        // 0.0
/*314 */                 for(i4=0; i4<4; i4++){                                                                                               // 0.0
/*316 */                     const int16_t *mv_col = l1mv0[x8*2 + (i4&1) + (y8*2 + (i4>>1))*h->b_stride];                                     // 0.0
/*318 */                     int16_t *mv_l0 = h->mv_cache[0][scan8[i8*4+i4]];                                                                 // 0.0
/*320 */                     mv_l0[0] = (dist_scale_factor * mv_col[0] + 128) >> 8;                                                           // 0.0
/*322 */                     mv_l0[1] = (dist_scale_factor * mv_col[1] + 128) >> 8;                                                           // 0.0
/*324 */                     *(uint32_t*)h->mv_cache[1][scan8[i8*4+i4]] =                                                                     // 0.0
/*326 */                         pack16to32(mv_l0[0]-mv_col[0],mv_l0[1]-mv_col[1]);                                                           // 0.0
/*328 */                 }                                                                                                                    // 0.0
/*330 */             }                                                                                                                        // 0.0
/*332 */         }                                                                                                                            // 0.0
/*334 */     }                                                                                                                                // 0.0
/*336 */ }                                                                                                                                    // 0.0
