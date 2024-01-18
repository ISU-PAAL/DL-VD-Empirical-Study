// commit message FFmpeg@7f2fe444a3 (target=0, prob=0.41227397, correct=True): single coefficient elimination prequantization more readable malloc & check if NULL error concealment / error resilience b_quant_offset (unfinished, should be 0 for now) data partitioning
/*0   */ void MPV_decode_mb(MpegEncContext *s, DCTELEM block[6][64])                                                        // (4) 0.05273
/*2   */ {                                                                                                                  // (25) 0.001953
/*4   */     int mb_x, mb_y;                                                                                                // (15) 0.02734
/*6   */     int dct_linesize, dct_offset;                                                                                  // (12) 0.0293
/*8   */     op_pixels_func *op_pix;                                                                                        // (13) 0.0293
/*10  */     qpel_mc_func *op_qpix;                                                                                         // (11) 0.03125
/*14  */     mb_x = s->mb_x;                                                                                                // (17) 0.02734
/*16  */     mb_y = s->mb_y;                                                                                                // (16) 0.02734
/*20  */ #ifdef FF_POSTPROCESS                                                                                              // (22) 0.01758
/*22  */     quant_store[mb_y][mb_x]=s->qscale;                                                                             // (9) 0.03906
/*24  */     //printf("[%02d][%02d] %d\n",mb_x,mb_y,s->qscale);                                                             // (3) 0.06445
/*26  */ #endif                                                                                                             // (24) 0.003906
/*30  */     /* update DC predictors for P macroblocks */                                                                   // (18) 0.02539
/*32  */     if (!s->mb_intra) {                                                                                            // (19) 0.02539
/*34  */         if (s->h263_pred || s->h263_aic) {                                                                         // (7) 0.04687
/*36  */           if(s->mbintra_table[mb_x + mb_y*s->mb_width])                                                            // (2) 0.06641
/*38  */           {                                                                                                        // (21) 0.01953
/*40  */             int wrap, xy, v;                                                                                       // (10) 0.03711
/*42  */             s->mbintra_table[mb_x + mb_y*s->mb_width]=0;                                                           // (1) 0.07031
/*44  */             wrap = 2 * s->mb_width + 2;                                                                            // (8) 0.04492
/*46  */             xy = 2 * mb_x + 1 +  (2 * mb_y + 1) * wrap;                                                            // (0) 0.07227
/*48  */             v = 1024;                                                                                              // (14) 0.0293
/*50  */                                                                                                                    // (20) 0.02344
/*52  */             s->dc_val[0][xy] = v;                                                                                  // (6) 0.04687
/*54  */             s->dc_val[0][xy + 1] = v;                                                                              // (5) 0.05078
/*56  */             s->dc_val[0][xy + wrap] = v;                                                                           // 0.0
/*58  */             s->dc_val[0][xy + 1 + wrap] = v;                                                                       // 0.0
/*60  */             /* ac pred */                                                                                          // 0.0
/*62  */             memset(s->ac_val[0][xy], 0, 16 * sizeof(INT16));                                                       // 0.0
/*64  */             memset(s->ac_val[0][xy + 1], 0, 16 * sizeof(INT16));                                                   // 0.0
/*66  */             memset(s->ac_val[0][xy + wrap], 0, 16 * sizeof(INT16));                                                // 0.0
/*68  */             memset(s->ac_val[0][xy + 1 + wrap], 0, 16 * sizeof(INT16));                                            // 0.0
/*70  */             if (s->h263_msmpeg4) {                                                                                 // 0.0
/*72  */                 s->coded_block[xy] = 0;                                                                            // 0.0
/*74  */                 s->coded_block[xy + 1] = 0;                                                                        // 0.0
/*76  */                 s->coded_block[xy + wrap] = 0;                                                                     // 0.0
/*78  */                 s->coded_block[xy + 1 + wrap] = 0;                                                                 // 0.0
/*80  */             }                                                                                                      // 0.0
/*82  */             /* chroma */                                                                                           // 0.0
/*84  */             wrap = s->mb_width + 2;                                                                                // 0.0
/*86  */             xy = mb_x + 1 + (mb_y + 1) * wrap;                                                                     // 0.0
/*88  */             s->dc_val[1][xy] = v;                                                                                  // 0.0
/*90  */             s->dc_val[2][xy] = v;                                                                                  // 0.0
/*92  */             /* ac pred */                                                                                          // 0.0
/*94  */             memset(s->ac_val[1][xy], 0, 16 * sizeof(INT16));                                                       // 0.0
/*96  */             memset(s->ac_val[2][xy], 0, 16 * sizeof(INT16));                                                       // 0.0
/*98  */           }                                                                                                        // 0.0
/*100 */         } else {                                                                                                   // 0.0
/*102 */             s->last_dc[0] = 128 << s->intra_dc_precision;                                                          // 0.0
/*104 */             s->last_dc[1] = 128 << s->intra_dc_precision;                                                          // 0.0
/*106 */             s->last_dc[2] = 128 << s->intra_dc_precision;                                                          // 0.0
/*108 */         }                                                                                                          // 0.0
/*110 */     }                                                                                                              // 0.0
/*112 */     else if (s->h263_pred || s->h263_aic)                                                                          // 0.0
/*114 */         s->mbintra_table[mb_x + mb_y*s->mb_width]=1;                                                               // 0.0
/*118 */     /* update motion predictor, not for B-frames as they need the motion_val from the last P/S-Frame */            // 0.0
/*120 */     if (s->out_format == FMT_H263) { //FIXME move into h263.c if possible, format specific stuff shouldnt be here  // 0.0
/*122 */       if(s->pict_type!=B_TYPE){                                                                                    // 0.0
/*124 */         int xy, wrap, motion_x, motion_y;                                                                          // 0.0
/*126 */                                                                                                                    // (23) 0.01562
/*128 */         wrap = 2 * s->mb_width + 2;                                                                                // 0.0
/*130 */         xy = 2 * mb_x + 1 + (2 * mb_y + 1) * wrap;                                                                 // 0.0
/*132 */         if (s->mb_intra) {                                                                                         // 0.0
/*134 */             motion_x = 0;                                                                                          // 0.0
/*136 */             motion_y = 0;                                                                                          // 0.0
/*138 */             goto motion_init;                                                                                      // 0.0
/*140 */         } else if (s->mv_type == MV_TYPE_16X16) {                                                                  // 0.0
/*142 */             motion_x = s->mv[0][0][0];                                                                             // 0.0
/*144 */             motion_y = s->mv[0][0][1];                                                                             // 0.0
/*146 */         motion_init:                                                                                               // 0.0
/*148 */             /* no update if 8X8 because it has been done during parsing */                                         // 0.0
/*150 */             s->motion_val[xy][0] = motion_x;                                                                       // 0.0
/*152 */             s->motion_val[xy][1] = motion_y;                                                                       // 0.0
/*154 */             s->motion_val[xy + 1][0] = motion_x;                                                                   // 0.0
/*156 */             s->motion_val[xy + 1][1] = motion_y;                                                                   // 0.0
/*158 */             s->motion_val[xy + wrap][0] = motion_x;                                                                // 0.0
/*160 */             s->motion_val[xy + wrap][1] = motion_y;                                                                // 0.0
/*162 */             s->motion_val[xy + 1 + wrap][0] = motion_x;                                                            // 0.0
/*164 */             s->motion_val[xy + 1 + wrap][1] = motion_y;                                                            // 0.0
/*166 */         }                                                                                                          // 0.0
/*168 */       }                                                                                                            // 0.0
/*170 */     }                                                                                                              // 0.0
/*172 */                                                                                                                    // 0.0
/*174 */     if (!(s->encoding && (s->intra_only || s->pict_type==B_TYPE))) {                                               // 0.0
/*176 */         UINT8 *dest_y, *dest_cb, *dest_cr;                                                                         // 0.0
/*178 */         UINT8 *mbskip_ptr;                                                                                         // 0.0
/*182 */         /* avoid copy if macroblock skipped in last frame too                                                      // 0.0
/*184 */            dont touch it for B-frames as they need the skip info from the next p-frame */                          // 0.0
/*186 */         if (s->pict_type != B_TYPE) {                                                                              // 0.0
/*188 */             mbskip_ptr = &s->mbskip_table[s->mb_y * s->mb_width + s->mb_x];                                        // 0.0
/*190 */             if (s->mb_skiped) {                                                                                    // 0.0
/*192 */                 s->mb_skiped = 0;                                                                                  // 0.0
/*194 */                 /* if previous was skipped too, then nothing to do !                                               // 0.0
/*196 */                    skip only during decoding as we might trash the buffers during encoding a bit */                // 0.0
/*198 */                 if (*mbskip_ptr != 0 && !s->encoding)                                                              // 0.0
/*200 */                     goto the_end;                                                                                  // 0.0
/*202 */                 *mbskip_ptr = 1; /* indicate that this time we skiped it */                                        // 0.0
/*204 */             } else {                                                                                               // 0.0
/*206 */                 *mbskip_ptr = 0; /* not skipped */                                                                 // 0.0
/*208 */             }                                                                                                      // 0.0
/*210 */         }                                                                                                          // 0.0
/*214 */         dest_y = s->current_picture[0] + (mb_y * 16 * s->linesize) + mb_x * 16;                                    // 0.0
/*216 */         dest_cb = s->current_picture[1] + (mb_y * 8 * (s->linesize >> 1)) + mb_x * 8;                              // 0.0
/*218 */         dest_cr = s->current_picture[2] + (mb_y * 8 * (s->linesize >> 1)) + mb_x * 8;                              // 0.0
/*222 */         if (s->interlaced_dct) {                                                                                   // 0.0
/*224 */             dct_linesize = s->linesize * 2;                                                                        // 0.0
/*226 */             dct_offset = s->linesize;                                                                              // 0.0
/*228 */         } else {                                                                                                   // 0.0
/*230 */             dct_linesize = s->linesize;                                                                            // 0.0
/*232 */             dct_offset = s->linesize * 8;                                                                          // 0.0
/*234 */         }                                                                                                          // 0.0
/*238 */         if (!s->mb_intra) {                                                                                        // 0.0
/*240 */             /* motion handling */                                                                                  // 0.0
/*242 */             if((s->flags&CODEC_FLAG_HQ) || (!s->encoding)){                                                        // 0.0
/*244 */                 if ((!s->no_rounding) || s->pict_type==B_TYPE){                                                    // 0.0
/*246 */                     op_pix = put_pixels_tab;                                                                       // 0.0
/*248 */                     op_qpix= qpel_mc_rnd_tab;                                                                      // 0.0
/*250 */                 }else{                                                                                             // 0.0
/*252 */                     op_pix = put_no_rnd_pixels_tab;                                                                // 0.0
/*254 */                     op_qpix= qpel_mc_no_rnd_tab;                                                                   // 0.0
/*256 */                 }                                                                                                  // 0.0
/*260 */                 if (s->mv_dir & MV_DIR_FORWARD) {                                                                  // 0.0
/*262 */                     MPV_motion(s, dest_y, dest_cb, dest_cr, 0, s->last_picture, op_pix, op_qpix);                  // 0.0
/*264 */                     if ((!s->no_rounding) || s->pict_type==B_TYPE)                                                 // 0.0
/*266 */                         op_pix = avg_pixels_tab;                                                                   // 0.0
/*268 */                     else                                                                                           // 0.0
/*270 */                         op_pix = avg_no_rnd_pixels_tab;                                                            // 0.0
/*272 */                 }                                                                                                  // 0.0
/*274 */                 if (s->mv_dir & MV_DIR_BACKWARD) {                                                                 // 0.0
/*276 */                     MPV_motion(s, dest_y, dest_cb, dest_cr, 1, s->next_picture, op_pix, op_qpix);                  // 0.0
/*278 */                 }                                                                                                  // 0.0
/*280 */             }                                                                                                      // 0.0
/*284 */             /* add dct residue */                                                                                  // 0.0
/*286 */             add_dct(s, block[0], 0, dest_y, dct_linesize);                                                         // 0.0
/*288 */             add_dct(s, block[1], 1, dest_y + 8, dct_linesize);                                                     // 0.0
/*290 */             add_dct(s, block[2], 2, dest_y + dct_offset, dct_linesize);                                            // 0.0
/*292 */             add_dct(s, block[3], 3, dest_y + dct_offset + 8, dct_linesize);                                        // 0.0
/*296 */             add_dct(s, block[4], 4, dest_cb, s->linesize >> 1);                                                    // 0.0
/*298 */             add_dct(s, block[5], 5, dest_cr, s->linesize >> 1);                                                    // 0.0
/*300 */         } else {                                                                                                   // 0.0
/*302 */             /* dct only in intra block */                                                                          // 0.0
/*304 */             put_dct(s, block[0], 0, dest_y, dct_linesize);                                                         // 0.0
/*306 */             put_dct(s, block[1], 1, dest_y + 8, dct_linesize);                                                     // 0.0
/*308 */             put_dct(s, block[2], 2, dest_y + dct_offset, dct_linesize);                                            // 0.0
/*310 */             put_dct(s, block[3], 3, dest_y + dct_offset + 8, dct_linesize);                                        // 0.0
/*314 */             put_dct(s, block[4], 4, dest_cb, s->linesize >> 1);                                                    // 0.0
/*316 */             put_dct(s, block[5], 5, dest_cr, s->linesize >> 1);                                                    // 0.0
/*318 */         }                                                                                                          // 0.0
/*320 */     }                                                                                                              // 0.0
/*322 */  the_end:                                                                                                          // 0.0
/*324 */     emms_c(); //FIXME remove                                                                                       // 0.0
/*326 */ }                                                                                                                  // 0.0
