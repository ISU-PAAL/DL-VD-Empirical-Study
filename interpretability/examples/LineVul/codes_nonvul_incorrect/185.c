// commit message FFmpeg@3547f8e8f8 (target=0, prob=0.5826796, correct=False): rv34: fix and optimise frame dependency checking
/*0   */ static int rv34_decode_mv(RV34DecContext *r, int block_type)                                                                                                                                    // (6) 0.04883
/*2   */ {                                                                                                                                                                                               // (21) 0.001953
/*4   */     MpegEncContext *s = &r->s;                                                                                                                                                                  // (11) 0.0293
/*6   */     GetBitContext *gb = &s->gb;                                                                                                                                                                 // (12) 0.02734
/*8   */     int i, j, k, l;                                                                                                                                                                             // (16) 0.02344
/*10  */     int mv_pos = s->mb_x * 2 + s->mb_y * 2 * s->b8_stride;                                                                                                                                      // (3) 0.06445
/*12  */     int next_bt;                                                                                                                                                                                // (19) 0.01563
/*16  */     memset(r->dmv, 0, sizeof(r->dmv));                                                                                                                                                          // (9) 0.03906
/*18  */     for(i = 0; i < num_mvs[block_type]; i++){                                                                                                                                                   // (8) 0.04492
/*20  */         r->dmv[i][0] = svq3_get_se_golomb(gb);                                                                                                                                                  // (4) 0.06055
/*22  */         r->dmv[i][1] = svq3_get_se_golomb(gb);                                                                                                                                                  // (5) 0.06055
/*24  */     }                                                                                                                                                                                           // (20) 0.007812
/*26  */     switch(block_type){                                                                                                                                                                         // (18) 0.01758
/*28  */     case RV34_MB_TYPE_INTRA:                                                                                                                                                                    // (13) 0.02734
/*30  */     case RV34_MB_TYPE_INTRA16x16:                                                                                                                                                               // (10) 0.0332
/*32  */         ZERO8x2(s->current_picture_ptr->f.motion_val[0][s->mb_x * 2 + s->mb_y * 2 * s->b8_stride], s->b8_stride);                                                                               // (1) 0.1191
/*34  */         return 0;                                                                                                                                                                               // (17) 0.01953
/*36  */     case RV34_MB_SKIP:                                                                                                                                                                          // (15) 0.02344
/*38  */         if(s->pict_type == AV_PICTURE_TYPE_P){                                                                                                                                                  // (7) 0.04883
/*40  */             ZERO8x2(s->current_picture_ptr->f.motion_val[0][s->mb_x * 2 + s->mb_y * 2 * s->b8_stride], s->b8_stride);                                                                           // (0) 0.127
/*42  */             rv34_mc_1mv (r, block_type, 0, 0, 0, 2, 2, 0);                                                                                                                                      // (2) 0.07617
/*44  */             break;                                                                                                                                                                              // (14) 0.02539
/*46  */         }                                                                                                                                                                                       // 0.0
/*48  */     case RV34_MB_B_DIRECT:                                                                                                                                                                      // 0.0
/*50  */         //surprisingly, it uses motion scheme from next reference frame                                                                                                                         // 0.0
/*52  */         /* wait for the current mb row to be finished */                                                                                                                                        // 0.0
/*54  */         if (HAVE_THREADS && (s->avctx->active_thread_type & FF_THREAD_FRAME))                                                                                                                   // 0.0
/*56  */             ff_thread_await_progress(&s->next_picture_ptr->f, s->mb_y - 1, 0);                                                                                                                  // 0.0
/*60  */         next_bt = s->next_picture_ptr->f.mb_type[s->mb_x + s->mb_y * s->mb_stride];                                                                                                             // 0.0
/*62  */         if(IS_INTRA(next_bt) || IS_SKIP(next_bt)){                                                                                                                                              // 0.0
/*64  */             ZERO8x2(s->current_picture_ptr->f.motion_val[0][s->mb_x * 2 + s->mb_y * 2 * s->b8_stride], s->b8_stride);                                                                           // 0.0
/*66  */             ZERO8x2(s->current_picture_ptr->f.motion_val[1][s->mb_x * 2 + s->mb_y * 2 * s->b8_stride], s->b8_stride);                                                                           // 0.0
/*68  */         }else                                                                                                                                                                                   // 0.0
/*70  */             for(j = 0; j < 2; j++)                                                                                                                                                              // 0.0
/*72  */                 for(i = 0; i < 2; i++)                                                                                                                                                          // 0.0
/*74  */                     for(k = 0; k < 2; k++)                                                                                                                                                      // 0.0
/*76  */                         for(l = 0; l < 2; l++)                                                                                                                                                  // 0.0
/*78  */                             s->current_picture_ptr->f.motion_val[l][mv_pos + i + j*s->b8_stride][k] = calc_add_mv(r, l, s->next_picture_ptr->f.motion_val[0][mv_pos + i + j*s->b8_stride][k]);  // 0.0
/*80  */         if(!(IS_16X8(next_bt) || IS_8X16(next_bt) || IS_8X8(next_bt))) //we can use whole macroblock MC                                                                                         // 0.0
/*82  */             rv34_mc_2mv(r, block_type);                                                                                                                                                         // 0.0
/*84  */         else                                                                                                                                                                                    // 0.0
/*86  */             rv34_mc_2mv_skip(r);                                                                                                                                                                // 0.0
/*88  */         ZERO8x2(s->current_picture_ptr->f.motion_val[0][s->mb_x * 2 + s->mb_y * 2 * s->b8_stride], s->b8_stride);                                                                               // 0.0
/*90  */         break;                                                                                                                                                                                  // 0.0
/*92  */     case RV34_MB_P_16x16:                                                                                                                                                                       // 0.0
/*94  */     case RV34_MB_P_MIX16x16:                                                                                                                                                                    // 0.0
/*96  */         rv34_pred_mv(r, block_type, 0, 0);                                                                                                                                                      // 0.0
/*98  */         rv34_mc_1mv (r, block_type, 0, 0, 0, 2, 2, 0);                                                                                                                                          // 0.0
/*100 */         break;                                                                                                                                                                                  // 0.0
/*102 */     case RV34_MB_B_FORWARD:                                                                                                                                                                     // 0.0
/*104 */     case RV34_MB_B_BACKWARD:                                                                                                                                                                    // 0.0
/*106 */         r->dmv[1][0] = r->dmv[0][0];                                                                                                                                                            // 0.0
/*108 */         r->dmv[1][1] = r->dmv[0][1];                                                                                                                                                            // 0.0
/*110 */         if(r->rv30)                                                                                                                                                                             // 0.0
/*112 */             rv34_pred_mv_rv3(r, block_type, block_type == RV34_MB_B_BACKWARD);                                                                                                                  // 0.0
/*114 */         else                                                                                                                                                                                    // 0.0
/*116 */             rv34_pred_mv_b  (r, block_type, block_type == RV34_MB_B_BACKWARD);                                                                                                                  // 0.0
/*118 */         rv34_mc_1mv     (r, block_type, 0, 0, 0, 2, 2, block_type == RV34_MB_B_BACKWARD);                                                                                                       // 0.0
/*120 */         break;                                                                                                                                                                                  // 0.0
/*122 */     case RV34_MB_P_16x8:                                                                                                                                                                        // 0.0
/*124 */     case RV34_MB_P_8x16:                                                                                                                                                                        // 0.0
/*126 */         rv34_pred_mv(r, block_type, 0, 0);                                                                                                                                                      // 0.0
/*128 */         rv34_pred_mv(r, block_type, 1 + (block_type == RV34_MB_P_16x8), 1);                                                                                                                     // 0.0
/*130 */         if(block_type == RV34_MB_P_16x8){                                                                                                                                                       // 0.0
/*132 */             rv34_mc_1mv(r, block_type, 0, 0, 0,            2, 1, 0);                                                                                                                            // 0.0
/*134 */             rv34_mc_1mv(r, block_type, 0, 8, s->b8_stride, 2, 1, 0);                                                                                                                            // 0.0
/*136 */         }                                                                                                                                                                                       // 0.0
/*138 */         if(block_type == RV34_MB_P_8x16){                                                                                                                                                       // 0.0
/*140 */             rv34_mc_1mv(r, block_type, 0, 0, 0, 1, 2, 0);                                                                                                                                       // 0.0
/*142 */             rv34_mc_1mv(r, block_type, 8, 0, 1, 1, 2, 0);                                                                                                                                       // 0.0
/*144 */         }                                                                                                                                                                                       // 0.0
/*146 */         break;                                                                                                                                                                                  // 0.0
/*148 */     case RV34_MB_B_BIDIR:                                                                                                                                                                       // 0.0
/*150 */         rv34_pred_mv_b  (r, block_type, 0);                                                                                                                                                     // 0.0
/*152 */         rv34_pred_mv_b  (r, block_type, 1);                                                                                                                                                     // 0.0
/*154 */         rv34_mc_2mv     (r, block_type);                                                                                                                                                        // 0.0
/*156 */         break;                                                                                                                                                                                  // 0.0
/*158 */     case RV34_MB_P_8x8:                                                                                                                                                                         // 0.0
/*160 */         for(i=0;i< 4;i++){                                                                                                                                                                      // 0.0
/*162 */             rv34_pred_mv(r, block_type, i, i);                                                                                                                                                  // 0.0
/*164 */             rv34_mc_1mv (r, block_type, (i&1)<<3, (i&2)<<2, (i&1)+(i>>1)*s->b8_stride, 1, 1, 0);                                                                                                // 0.0
/*166 */         }                                                                                                                                                                                       // 0.0
/*168 */         break;                                                                                                                                                                                  // 0.0
/*170 */     }                                                                                                                                                                                           // 0.0
/*174 */     return 0;                                                                                                                                                                                   // 0.0
/*176 */ }                                                                                                                                                                                               // 0.0
