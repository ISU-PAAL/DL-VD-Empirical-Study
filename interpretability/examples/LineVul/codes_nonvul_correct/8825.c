// commit message FFmpeg@0d21a84605 (target=0, prob=0.40666026, correct=True): dont double check vectors more correct EPZS implementation much faster halfpel ME simplifications / reducing duplicate code 4MV in LQ mode
/*0   */ void ff_estimate_p_frame_motion(MpegEncContext * s,                                                                                           // (8) 0.03711
/*2   */                                 int mb_x, int mb_y)                                                                                           // (0) 0.08398
/*4   */ {                                                                                                                                             // (27) 0.001953
/*6   */     UINT8 *pix, *ppix;                                                                                                                        // (13) 0.02734
/*8   */     int sum, varc, vard, mx, my, range, dmin, xx, yy;                                                                                         // (5) 0.05273
/*10  */     int xmin, ymin, xmax, ymax;                                                                                                               // (10) 0.03125
/*12  */     int rel_xmin, rel_ymin, rel_xmax, rel_ymax;                                                                                               // (6) 0.04687
/*14  */     int pred_x=0, pred_y=0;                                                                                                                   // (9) 0.03125
/*16  */     int P[6][2];                                                                                                                              // (18) 0.01953
/*18  */     const int shift= 1+s->quarter_sample;                                                                                                     // (11) 0.0293
/*20  */     int mb_type=0;                                                                                                                            // (16) 0.02148
/*22  */     uint8_t *ref_picture= s->last_picture[0];                                                                                                 // (7) 0.03906
/*26  */     get_limits(s, &range, &xmin, &ymin, &xmax, &ymax, s->f_code);                                                                             // (4) 0.06641
/*30  */     switch(s->me_method) {                                                                                                                    // (14) 0.02344
/*32  */     case ME_ZERO:                                                                                                                             // (20) 0.01758
/*34  */     default:                                                                                                                                  // (26) 0.009766
/*36  */ 	no_motion_search(s, &mx, &my);                                                                                                               // (12) 0.0293
/*38  */         dmin = 0;                                                                                                                             // (15) 0.02344
/*40  */         break;                                                                                                                                // (21) 0.01758
/*42  */     case ME_FULL:                                                                                                                             // (19) 0.01758
/*44  */ 	dmin = full_motion_search(s, &mx, &my, range, xmin, ymin, xmax, ymax, ref_picture);                                                          // (3) 0.07031
/*46  */         break;                                                                                                                                // (22) 0.01758
/*48  */     case ME_LOG:                                                                                                                              // (25) 0.01562
/*50  */ 	dmin = log_motion_search(s, &mx, &my, range / 2, xmin, ymin, xmax, ymax, ref_picture);                                                       // (2) 0.07422
/*52  */         break;                                                                                                                                // (23) 0.01758
/*54  */     case ME_PHODS:                                                                                                                            // (17) 0.01953
/*56  */ 	dmin = phods_motion_search(s, &mx, &my, range / 2, xmin, ymin, xmax, ymax, ref_picture);                                                     // (1) 0.07617
/*58  */         break;                                                                                                                                // (24) 0.01758
/*60  */     case ME_X1:                                                                                                                               // 0.0
/*62  */     case ME_EPZS:                                                                                                                             // 0.0
/*64  */        {                                                                                                                                      // 0.0
/*66  */             const int mot_stride = s->block_wrap[0];                                                                                          // 0.0
/*68  */             const int mot_xy = s->block_index[0];                                                                                             // 0.0
/*72  */             rel_xmin= xmin - mb_x*16;                                                                                                         // 0.0
/*74  */             rel_xmax= xmax - mb_x*16;                                                                                                         // 0.0
/*76  */             rel_ymin= ymin - mb_y*16;                                                                                                         // 0.0
/*78  */             rel_ymax= ymax - mb_y*16;                                                                                                         // 0.0
/*82  */             P[0][0] = s->motion_val[mot_xy    ][0];                                                                                           // 0.0
/*84  */             P[0][1] = s->motion_val[mot_xy    ][1];                                                                                           // 0.0
/*86  */             P[1][0] = s->motion_val[mot_xy - 1][0];                                                                                           // 0.0
/*88  */             P[1][1] = s->motion_val[mot_xy - 1][1];                                                                                           // 0.0
/*90  */             if(P[1][0] > (rel_xmax<<shift)) P[1][0]= (rel_xmax<<shift);                                                                       // 0.0
/*94  */             /* special case for first line */                                                                                                 // 0.0
/*96  */             if ((mb_y == 0 || s->first_slice_line || s->first_gob_line)) {                                                                    // 0.0
/*98  */                 P[4][0] = P[1][0];                                                                                                            // 0.0
/*100 */                 P[4][1] = P[1][1];                                                                                                            // 0.0
/*102 */             } else {                                                                                                                          // 0.0
/*104 */                 P[2][0] = s->motion_val[mot_xy - mot_stride             ][0];                                                                 // 0.0
/*106 */                 P[2][1] = s->motion_val[mot_xy - mot_stride             ][1];                                                                 // 0.0
/*108 */                 P[3][0] = s->motion_val[mot_xy - mot_stride + 2         ][0];                                                                 // 0.0
/*110 */                 P[3][1] = s->motion_val[mot_xy - mot_stride + 2         ][1];                                                                 // 0.0
/*112 */                 if(P[2][1] > (rel_ymax<<shift)) P[2][1]= (rel_ymax<<shift);                                                                   // 0.0
/*114 */                 if(P[3][0] < (rel_xmin<<shift)) P[3][0]= (rel_xmin<<shift);                                                                   // 0.0
/*116 */                 if(P[3][1] > (rel_ymax<<shift)) P[3][1]= (rel_ymax<<shift);                                                                   // 0.0
/*118 */                                                                                                                                               // 0.0
/*120 */                 P[4][0]= mid_pred(P[1][0], P[2][0], P[3][0]);                                                                                 // 0.0
/*122 */                 P[4][1]= mid_pred(P[1][1], P[2][1], P[3][1]);                                                                                 // 0.0
/*124 */             }                                                                                                                                 // 0.0
/*126 */             if(s->out_format == FMT_H263){                                                                                                    // 0.0
/*128 */                 pred_x = P[4][0];                                                                                                             // 0.0
/*130 */                 pred_y = P[4][1];                                                                                                             // 0.0
/*132 */             }else { /* mpeg1 at least */                                                                                                      // 0.0
/*134 */                 pred_x= P[1][0];                                                                                                              // 0.0
/*136 */                 pred_y= P[1][1];                                                                                                              // 0.0
/*138 */             }                                                                                                                                 // 0.0
/*140 */         }                                                                                                                                     // 0.0
/*142 */         dmin = epzs_motion_search(s, &mx, &my, P, pred_x, pred_y, rel_xmin, rel_ymin, rel_xmax, rel_ymax, ref_picture);                       // 0.0
/*144 */                                                                                                                                               // 0.0
/*146 */         mx+= mb_x*16;                                                                                                                         // 0.0
/*148 */         my+= mb_y*16;                                                                                                                         // 0.0
/*150 */         break;                                                                                                                                // 0.0
/*152 */     }                                                                                                                                         // 0.0
/*154 */                                                                                                                                               // 0.0
/*156 */     if(s->flags&CODEC_FLAG_4MV){                                                                                                              // 0.0
/*158 */         int block;                                                                                                                            // 0.0
/*162 */         mb_type|= MB_TYPE_INTER4V;                                                                                                            // 0.0
/*166 */         for(block=0; block<4; block++){                                                                                                       // 0.0
/*168 */             int mx4, my4;                                                                                                                     // 0.0
/*170 */             int pred_x4, pred_y4;                                                                                                             // 0.0
/*172 */             int dmin4;                                                                                                                        // 0.0
/*174 */             static const int off[4]= {2, 1, 1, -1};                                                                                           // 0.0
/*176 */             const int mot_stride = s->block_wrap[0];                                                                                          // 0.0
/*178 */             const int mot_xy = s->block_index[block];                                                                                         // 0.0
/*180 */             const int block_x= mb_x*2 + (block&1);                                                                                            // 0.0
/*182 */             const int block_y= mb_y*2 + (block>>1);                                                                                           // 0.0
/*186 */             const int rel_xmin4= xmin - block_x*8;                                                                                            // 0.0
/*188 */             const int rel_xmax4= xmax - block_x*8 + 8;                                                                                        // 0.0
/*190 */             const int rel_ymin4= ymin - block_y*8;                                                                                            // 0.0
/*192 */             const int rel_ymax4= ymax - block_y*8 + 8;                                                                                        // 0.0
/*196 */             P[0][0] = s->motion_val[mot_xy    ][0];                                                                                           // 0.0
/*198 */             P[0][1] = s->motion_val[mot_xy    ][1];                                                                                           // 0.0
/*200 */             P[1][0] = s->motion_val[mot_xy - 1][0];                                                                                           // 0.0
/*202 */             P[1][1] = s->motion_val[mot_xy - 1][1];                                                                                           // 0.0
/*204 */             if(P[1][0] > (rel_xmax4<<shift)) P[1][0]= (rel_xmax4<<shift);                                                                     // 0.0
/*208 */             /* special case for first line */                                                                                                 // 0.0
/*210 */             if ((mb_y == 0 || s->first_slice_line || s->first_gob_line) && block<2) {                                                         // 0.0
/*212 */                 P[4][0] = P[1][0];                                                                                                            // 0.0
/*214 */                 P[4][1] = P[1][1];                                                                                                            // 0.0
/*216 */             } else {                                                                                                                          // 0.0
/*218 */                 P[2][0] = s->motion_val[mot_xy - mot_stride             ][0];                                                                 // 0.0
/*220 */                 P[2][1] = s->motion_val[mot_xy - mot_stride             ][1];                                                                 // 0.0
/*222 */                 P[3][0] = s->motion_val[mot_xy - mot_stride + off[block]][0];                                                                 // 0.0
/*224 */                 P[3][1] = s->motion_val[mot_xy - mot_stride + off[block]][1];                                                                 // 0.0
/*226 */                 if(P[2][1] > (rel_ymax4<<shift)) P[2][1]= (rel_ymax4<<shift);                                                                 // 0.0
/*228 */                 if(P[3][0] < (rel_xmin4<<shift)) P[3][0]= (rel_xmin4<<shift);                                                                 // 0.0
/*230 */                 if(P[3][0] > (rel_xmax4<<shift)) P[3][0]= (rel_xmax4<<shift);                                                                 // 0.0
/*232 */                 if(P[3][1] > (rel_ymax4<<shift)) P[3][1]= (rel_ymax4<<shift);                                                                 // 0.0
/*234 */                                                                                                                                               // 0.0
/*236 */                 P[4][0]= mid_pred(P[1][0], P[2][0], P[3][0]);                                                                                 // 0.0
/*238 */                 P[4][1]= mid_pred(P[1][1], P[2][1], P[3][1]);                                                                                 // 0.0
/*240 */             }                                                                                                                                 // 0.0
/*242 */             if(s->out_format == FMT_H263){                                                                                                    // 0.0
/*244 */                 pred_x4 = P[4][0];                                                                                                            // 0.0
/*246 */                 pred_y4 = P[4][1];                                                                                                            // 0.0
/*248 */             }else { /* mpeg1 at least */                                                                                                      // 0.0
/*250 */                 pred_x4= P[1][0];                                                                                                             // 0.0
/*252 */                 pred_y4= P[1][1];                                                                                                             // 0.0
/*254 */             }                                                                                                                                 // 0.0
/*256 */             P[5][0]= mx - mb_x*16;                                                                                                            // 0.0
/*258 */             P[5][1]= my - mb_y*16;                                                                                                            // 0.0
/*262 */             dmin4 = epzs_motion_search4(s, block, &mx4, &my4, P, pred_x4, pred_y4, rel_xmin4, rel_ymin4, rel_xmax4, rel_ymax4, ref_picture);  // 0.0
/*266 */             halfpel_motion_search4(s, &mx4, &my4, dmin4, rel_xmin4, rel_ymin4, rel_xmax4, rel_ymax4,                                          // 0.0
/*268 */                                    pred_x4, pred_y4, block_x, block_y, ref_picture);                                                          // 0.0
/*270 */                                                                                                                                               // 0.0
/*272 */             s->motion_val[ s->block_index[block] ][0]= mx4;                                                                                   // 0.0
/*274 */             s->motion_val[ s->block_index[block] ][1]= my4;                                                                                   // 0.0
/*276 */         }                                                                                                                                     // 0.0
/*278 */     }                                                                                                                                         // 0.0
/*282 */     /* intra / predictive decision */                                                                                                         // 0.0
/*284 */     xx = mb_x * 16;                                                                                                                           // 0.0
/*286 */     yy = mb_y * 16;                                                                                                                           // 0.0
/*290 */     pix = s->new_picture[0] + (yy * s->linesize) + xx;                                                                                        // 0.0
/*292 */     /* At this point (mx,my) are full-pell and the absolute displacement */                                                                   // 0.0
/*294 */     ppix = ref_picture + (my * s->linesize) + mx;                                                                                             // 0.0
/*296 */                                                                                                                                               // 0.0
/*298 */     sum = pix_sum(pix, s->linesize);                                                                                                          // 0.0
/*300 */ #if 0                                                                                                                                         // 0.0
/*302 */     varc = pix_dev(pix, s->linesize, (sum+128)>>8) + INTER_BIAS;                                                                              // 0.0
/*304 */     vard = pix_abs16x16(pix, ppix, s->linesize);                                                                                              // 0.0
/*306 */ #else                                                                                                                                         // 0.0
/*308 */     sum= (sum+8)>>4;                                                                                                                          // 0.0
/*310 */     varc = ((pix_norm1(pix, s->linesize) - sum*sum + 128 + 500)>>8);                                                                          // 0.0
/*312 */     vard = (pix_norm(pix, ppix, s->linesize)+128)>>8;                                                                                         // 0.0
/*314 */ #endif                                                                                                                                        // 0.0
/*318 */     s->mb_var[s->mb_width * mb_y + mb_x] = varc;                                                                                              // 0.0
/*320 */     s->avg_mb_var+= varc;                                                                                                                     // 0.0
/*322 */     s->mc_mb_var += vard;                                                                                                                     // 0.0
/*326 */                                                                                                                                               // 0.0
/*328 */ #if 0                                                                                                                                         // 0.0
/*330 */     printf("varc=%4d avg_var=%4d (sum=%4d) vard=%4d mx=%2d my=%2d\n",                                                                         // 0.0
/*332 */ 	   varc, s->avg_mb_var, sum, vard, mx - xx, my - yy);                                                                                        // 0.0
/*334 */ #endif                                                                                                                                        // 0.0
/*336 */     if(s->flags&CODEC_FLAG_HQ){                                                                                                               // 0.0
/*338 */         if (vard*2 + 200 > varc)                                                                                                              // 0.0
/*340 */             mb_type|= MB_TYPE_INTRA;                                                                                                          // 0.0
/*342 */         if (varc*2 + 200 > vard){                                                                                                             // 0.0
/*344 */             mb_type|= MB_TYPE_INTER;                                                                                                          // 0.0
/*346 */             halfpel_motion_search(s, &mx, &my, dmin, xmin, ymin, xmax, ymax, pred_x, pred_y, ref_picture);                                    // 0.0
/*348 */         }else{                                                                                                                                // 0.0
/*350 */             mx = mx*2 - mb_x*32;                                                                                                              // 0.0
/*352 */             my = my*2 - mb_y*32;                                                                                                              // 0.0
/*354 */         }                                                                                                                                     // 0.0
/*356 */     }else{                                                                                                                                    // 0.0
/*358 */         if (vard <= 64 || vard < varc) {                                                                                                      // 0.0
/*360 */             mb_type|= MB_TYPE_INTER;                                                                                                          // 0.0
/*362 */             if (s->me_method != ME_ZERO) {                                                                                                    // 0.0
/*364 */                 halfpel_motion_search(s, &mx, &my, dmin, xmin, ymin, xmax, ymax, pred_x, pred_y, ref_picture);                                // 0.0
/*366 */             } else {                                                                                                                          // 0.0
/*368 */                 mx -= 16 * mb_x;                                                                                                              // 0.0
/*370 */                 my -= 16 * mb_y;                                                                                                              // 0.0
/*372 */             }                                                                                                                                 // 0.0
/*374 */ #if 0                                                                                                                                         // 0.0
/*376 */             if (vard < 10) {                                                                                                                  // 0.0
/*378 */                 skip++;                                                                                                                       // 0.0
/*380 */                 fprintf(stderr,"\nEarly skip: %d vard: %2d varc: %5d dmin: %d",                                                               // 0.0
/*382 */                                 skip, vard, varc, dmin);                                                                                      // 0.0
/*384 */             }                                                                                                                                 // 0.0
/*386 */ #endif                                                                                                                                        // 0.0
/*388 */         }else{                                                                                                                                // 0.0
/*390 */             mb_type|= MB_TYPE_INTRA;                                                                                                          // 0.0
/*392 */             mx = 0;//mx*2 - 32 * mb_x;                                                                                                        // 0.0
/*394 */             my = 0;//my*2 - 32 * mb_y;                                                                                                        // 0.0
/*396 */         }                                                                                                                                     // 0.0
/*398 */     }                                                                                                                                         // 0.0
/*402 */     s->mb_type[mb_y*s->mb_width + mb_x]= mb_type;                                                                                             // 0.0
/*404 */     set_p_mv_tables(s, mx, my);                                                                                                               // 0.0
/*406 */ }                                                                                                                                             // 0.0
