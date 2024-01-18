// commit message FFmpeg@0d21a84605 (target=0, prob=0.18711746, correct=True): dont double check vectors more correct EPZS implementation much faster halfpel ME simplifications / reducing duplicate code 4MV in LQ mode
/*0   */ int ff_estimate_motion_b(MpegEncContext * s,                                                                             // (8) 0.0332
/*2   */                        int mb_x, int mb_y, int16_t (*mv_table)[2], uint8_t *ref_picture, int f_code)                     // (0) 0.1172
/*4   */ {                                                                                                                        // (27) 0.001953
/*6   */     int mx, my, range, dmin;                                                                                             // (13) 0.02734
/*8   */     int xmin, ymin, xmax, ymax;                                                                                          // (10) 0.03125
/*10  */     int rel_xmin, rel_ymin, rel_xmax, rel_ymax;                                                                          // (6) 0.04688
/*12  */     int pred_x=0, pred_y=0;                                                                                              // (9) 0.03125
/*14  */     int P[6][2];                                                                                                         // (16) 0.01953
/*16  */     const int shift= 1+s->quarter_sample;                                                                                // (12) 0.0293
/*18  */     const int mot_stride = s->mb_width + 2;                                                                              // (7) 0.03516
/*20  */     const int mot_xy = (mb_y + 1)*mot_stride + mb_x + 1;                                                                 // (5) 0.05469
/*22  */                                                                                                                          // (25) 0.007812
/*24  */     get_limits(s, &range, &xmin, &ymin, &xmax, &ymax, f_code);                                                           // (4) 0.0625
/*28  */     switch(s->me_method) {                                                                                               // (14) 0.02344
/*30  */     case ME_ZERO:                                                                                                        // (18) 0.01758
/*32  */     default:                                                                                                             // (24) 0.009766
/*34  */ 	no_motion_search(s, &mx, &my);                                                                                          // (11) 0.0293
/*36  */         dmin = 0;                                                                                                        // (15) 0.02344
/*38  */         break;                                                                                                           // (19) 0.01758
/*40  */     case ME_FULL:                                                                                                        // (20) 0.01758
/*42  */ 	dmin = full_motion_search(s, &mx, &my, range, xmin, ymin, xmax, ymax, ref_picture);                                     // (3) 0.07031
/*44  */         break;                                                                                                           // (21) 0.01758
/*46  */     case ME_LOG:                                                                                                         // (23) 0.01563
/*48  */ 	dmin = log_motion_search(s, &mx, &my, range / 2, xmin, ymin, xmax, ymax, ref_picture);                                  // (2) 0.07422
/*50  */         break;                                                                                                           // (22) 0.01758
/*52  */     case ME_PHODS:                                                                                                       // (17) 0.01953
/*54  */ 	dmin = phods_motion_search(s, &mx, &my, range / 2, xmin, ymin, xmax, ymax, ref_picture);                                // (1) 0.07617
/*56  */         break;                                                                                                           // 0.0
/*58  */     case ME_X1:                                                                                                          // 0.0
/*60  */     case ME_EPZS:                                                                                                        // 0.0
/*62  */        {                                                                                                                 // 0.0
/*66  */             rel_xmin= xmin - mb_x*16;                                                                                    // 0.0
/*68  */             rel_xmax= xmax - mb_x*16;                                                                                    // 0.0
/*70  */             rel_ymin= ymin - mb_y*16;                                                                                    // 0.0
/*72  */             rel_ymax= ymax - mb_y*16;                                                                                    // 0.0
/*76  */             P[0][0] = mv_table[mot_xy    ][0];                                                                           // 0.0
/*78  */             P[0][1] = mv_table[mot_xy    ][1];                                                                           // 0.0
/*80  */             P[1][0] = mv_table[mot_xy - 1][0];                                                                           // 0.0
/*82  */             P[1][1] = mv_table[mot_xy - 1][1];                                                                           // 0.0
/*84  */             if(P[1][0] > (rel_xmax<<shift)) P[1][0]= (rel_xmax<<shift);                                                  // 0.0
/*88  */             /* special case for first line */                                                                            // 0.0
/*90  */             if ((mb_y == 0 || s->first_slice_line || s->first_gob_line)) {                                               // 0.0
/*92  */                 P[4][0] = P[1][0];                                                                                       // 0.0
/*94  */                 P[4][1] = P[1][1];                                                                                       // 0.0
/*96  */             } else {                                                                                                     // 0.0
/*98  */                 P[2][0] = mv_table[mot_xy - mot_stride             ][0];                                                 // 0.0
/*100 */                 P[2][1] = mv_table[mot_xy - mot_stride             ][1];                                                 // 0.0
/*102 */                 P[3][0] = mv_table[mot_xy - mot_stride + 1         ][0];                                                 // 0.0
/*104 */                 P[3][1] = mv_table[mot_xy - mot_stride + 1         ][1];                                                 // 0.0
/*106 */                 if(P[2][1] > (rel_ymax<<shift)) P[2][1]= (rel_ymax<<shift);                                              // 0.0
/*108 */                 if(P[3][0] < (rel_xmin<<shift)) P[3][0]= (rel_xmin<<shift);                                              // 0.0
/*110 */                 if(P[3][1] > (rel_ymax<<shift)) P[3][1]= (rel_ymax<<shift);                                              // 0.0
/*112 */                                                                                                                          // 0.0
/*114 */                 P[4][0]= mid_pred(P[1][0], P[2][0], P[3][0]);                                                            // 0.0
/*116 */                 P[4][1]= mid_pred(P[1][1], P[2][1], P[3][1]);                                                            // 0.0
/*118 */             }                                                                                                            // 0.0
/*120 */             pred_x= P[1][0];                                                                                             // 0.0
/*122 */             pred_y= P[1][1];                                                                                             // 0.0
/*124 */         }                                                                                                                // 0.0
/*126 */         dmin = epzs_motion_search(s, &mx, &my, P, pred_x, pred_y, rel_xmin, rel_ymin, rel_xmax, rel_ymax, ref_picture);  // 0.0
/*128 */                                                                                                                          // (28) 0.001953
/*130 */         mx+= mb_x*16;                                                                                                    // 0.0
/*132 */         my+= mb_y*16;                                                                                                    // 0.0
/*134 */         break;                                                                                                           // 0.0
/*136 */     }                                                                                                                    // 0.0
/*138 */                                                                                                                          // (26) 0.007812
/*140 */     /* intra / predictive decision */                                                                                    // 0.0
/*142 */ //    xx = mb_x * 16;                                                                                                    // 0.0
/*144 */ //    yy = mb_y * 16;                                                                                                    // 0.0
/*148 */ //    pix = s->new_picture[0] + (yy * s->linesize) + xx;                                                                 // 0.0
/*150 */     /* At this point (mx,my) are full-pell and the absolute displacement */                                              // 0.0
/*152 */ //    ppix = ref_picture + (my * s->linesize) + mx;                                                                      // 0.0
/*154 */                                                                                                                          // 0.0
/*156 */     dmin= halfpel_motion_search(s, &mx, &my, dmin, xmin, ymin, xmax, ymax, pred_x, pred_y, ref_picture);                 // 0.0
/*160 */ //    s->mb_type[mb_y*s->mb_width + mb_x]= mb_type;                                                                      // 0.0
/*162 */     mv_table[mot_xy][0]= mx;                                                                                             // 0.0
/*164 */     mv_table[mot_xy][1]= my;                                                                                             // 0.0
/*166 */     return dmin;                                                                                                         // 0.0
/*168 */ }                                                                                                                        // 0.0
