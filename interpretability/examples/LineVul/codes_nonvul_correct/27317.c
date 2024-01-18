// commit message FFmpeg@7104c23bd1 (target=0, prob=0.38253948, correct=True): rv34: clean a bit availability checks.
/*0  */ static void rv34_pred_mv(RV34DecContext *r, int block_type, int subblock_no, int dmv_no)      // (2) 0.07227
/*2  */ {                                                                                             // (22) 0.001953
/*4  */     MpegEncContext *s = &r->s;                                                                // (14) 0.0293
/*6  */     int mv_pos = s->mb_x * 2 + s->mb_y * 2 * s->b8_stride;                                    // (5) 0.06445
/*8  */     int A[2] = {0}, B[2], C[2];                                                               // (9) 0.03906
/*10 */     int i, j;                                                                                 // (18) 0.01562
/*12 */     int mx, my;                                                                               // (17) 0.01758
/*14 */     int avail_index = avail_indexes[subblock_no];                                             // (11) 0.03516
/*16 */     int c_off = part_sizes_w[block_type];                                                     // (10) 0.03711
/*20 */     mv_pos += (subblock_no & 1) + (subblock_no >> 1)*s->b8_stride;                            // (6) 0.06445
/*22 */     if(subblock_no == 3)                                                                      // (16) 0.02344
/*24 */         c_off = -1;                                                                           // (15) 0.02734
/*28 */     if(r->avail_cache[avail_index - 1]){                                                      // (7) 0.03906
/*30 */         A[0] = s->current_picture_ptr->f.motion_val[0][mv_pos-1][0];                          // (3) 0.07227
/*32 */         A[1] = s->current_picture_ptr->f.motion_val[0][mv_pos-1][1];                          // (4) 0.07227
/*34 */     }                                                                                         // (20) 0.007812
/*36 */     if(r->avail_cache[avail_index - 4]){                                                      // (8) 0.03906
/*38 */         B[0] = s->current_picture_ptr->f.motion_val[0][mv_pos-s->b8_stride][0];               // (1) 0.08398
/*40 */         B[1] = s->current_picture_ptr->f.motion_val[0][mv_pos-s->b8_stride][1];               // (0) 0.08398
/*42 */     }else{                                                                                    // (19) 0.01172
/*44 */         B[0] = A[0];                                                                          // (12) 0.03125
/*46 */         B[1] = A[1];                                                                          // (13) 0.03125
/*48 */     }                                                                                         // (21) 0.007812
/*50 */     if(!r->avail_cache[avail_index - 4 + c_off]){                                             // 0.0
/*52 */         if(r->avail_cache[avail_index - 4] && (r->avail_cache[avail_index - 1] || r->rv30)){  // 0.0
/*54 */             C[0] = s->current_picture_ptr->f.motion_val[0][mv_pos-s->b8_stride-1][0];         // 0.0
/*56 */             C[1] = s->current_picture_ptr->f.motion_val[0][mv_pos-s->b8_stride-1][1];         // 0.0
/*58 */         }else{                                                                                // 0.0
/*60 */             C[0] = A[0];                                                                      // 0.0
/*62 */             C[1] = A[1];                                                                      // 0.0
/*64 */         }                                                                                     // 0.0
/*66 */     }else{                                                                                    // 0.0
/*68 */         C[0] = s->current_picture_ptr->f.motion_val[0][mv_pos-s->b8_stride+c_off][0];         // 0.0
/*70 */         C[1] = s->current_picture_ptr->f.motion_val[0][mv_pos-s->b8_stride+c_off][1];         // 0.0
/*72 */     }                                                                                         // 0.0
/*74 */     mx = mid_pred(A[0], B[0], C[0]);                                                          // 0.0
/*76 */     my = mid_pred(A[1], B[1], C[1]);                                                          // 0.0
/*78 */     mx += r->dmv[dmv_no][0];                                                                  // 0.0
/*80 */     my += r->dmv[dmv_no][1];                                                                  // 0.0
/*82 */     for(j = 0; j < part_sizes_h[block_type]; j++){                                            // 0.0
/*84 */         for(i = 0; i < part_sizes_w[block_type]; i++){                                        // 0.0
/*86 */             s->current_picture_ptr->f.motion_val[0][mv_pos + i + j*s->b8_stride][0] = mx;     // 0.0
/*88 */             s->current_picture_ptr->f.motion_val[0][mv_pos + i + j*s->b8_stride][1] = my;     // 0.0
/*90 */         }                                                                                     // 0.0
/*92 */     }                                                                                         // 0.0
/*94 */ }                                                                                             // 0.0
