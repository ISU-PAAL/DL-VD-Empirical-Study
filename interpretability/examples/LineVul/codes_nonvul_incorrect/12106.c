// commit message FFmpeg@7104c23bd1 (target=0, prob=0.56179255, correct=False): rv34: clean a bit availability checks.
/*0  */ static void rv34_pred_mv_rv3(RV34DecContext *r, int block_type, int dir)                       // (6) 0.06055
/*2  */ {                                                                                              // (20) 0.001953
/*4  */     MpegEncContext *s = &r->s;                                                                 // (13) 0.0293
/*6  */     int mv_pos = s->mb_x * 2 + s->mb_y * 2 * s->b8_stride;                                     // (5) 0.06445
/*8  */     int A[2] = {0}, B[2], C[2];                                                                // (8) 0.03906
/*10 */     int i, j, k;                                                                               // (15) 0.01953
/*12 */     int mx, my;                                                                                // (16) 0.01758
/*14 */     int avail_index = avail_indexes[0];                                                        // (14) 0.0293
/*18 */     if(r->avail_cache[avail_index - 1]){                                                       // (9) 0.03906
/*20 */         A[0] = s->current_picture_ptr->f.motion_val[0][mv_pos - 1][0];                         // (3) 0.07227
/*22 */         A[1] = s->current_picture_ptr->f.motion_val[0][mv_pos - 1][1];                         // (4) 0.07227
/*24 */     }                                                                                          // (18) 0.007812
/*26 */     if(r->avail_cache[avail_index - 4]){                                                       // (10) 0.03906
/*28 */         B[0] = s->current_picture_ptr->f.motion_val[0][mv_pos - s->b8_stride][0];              // (0) 0.08398
/*30 */         B[1] = s->current_picture_ptr->f.motion_val[0][mv_pos - s->b8_stride][1];              // (1) 0.08398
/*32 */     }else{                                                                                     // (17) 0.01172
/*34 */         B[0] = A[0];                                                                           // (11) 0.03125
/*36 */         B[1] = A[1];                                                                           // (12) 0.03125
/*38 */     }                                                                                          // (19) 0.007812
/*40 */     if(!r->avail_cache[avail_index - 4 + 2]){                                                  // (7) 0.04492
/*42 */         if(r->avail_cache[avail_index - 4] && (r->avail_cache[avail_index - 1])){              // (2) 0.08008
/*44 */             C[0] = s->current_picture_ptr->f.motion_val[0][mv_pos - s->b8_stride - 1][0];      // 0.0
/*46 */             C[1] = s->current_picture_ptr->f.motion_val[0][mv_pos - s->b8_stride - 1][1];      // 0.0
/*48 */         }else{                                                                                 // 0.0
/*50 */             C[0] = A[0];                                                                       // 0.0
/*52 */             C[1] = A[1];                                                                       // 0.0
/*54 */         }                                                                                      // 0.0
/*56 */     }else{                                                                                     // 0.0
/*58 */         C[0] = s->current_picture_ptr->f.motion_val[0][mv_pos - s->b8_stride + 2][0];          // 0.0
/*60 */         C[1] = s->current_picture_ptr->f.motion_val[0][mv_pos - s->b8_stride + 2][1];          // 0.0
/*62 */     }                                                                                          // 0.0
/*64 */     mx = mid_pred(A[0], B[0], C[0]);                                                           // 0.0
/*66 */     my = mid_pred(A[1], B[1], C[1]);                                                           // 0.0
/*68 */     mx += r->dmv[0][0];                                                                        // 0.0
/*70 */     my += r->dmv[0][1];                                                                        // 0.0
/*72 */     for(j = 0; j < 2; j++){                                                                    // 0.0
/*74 */         for(i = 0; i < 2; i++){                                                                // 0.0
/*76 */             for(k = 0; k < 2; k++){                                                            // 0.0
/*78 */                 s->current_picture_ptr->f.motion_val[k][mv_pos + i + j*s->b8_stride][0] = mx;  // 0.0
/*80 */                 s->current_picture_ptr->f.motion_val[k][mv_pos + i + j*s->b8_stride][1] = my;  // 0.0
/*82 */             }                                                                                  // 0.0
/*84 */         }                                                                                      // 0.0
/*86 */     }                                                                                          // 0.0
/*88 */ }                                                                                              // 0.0
