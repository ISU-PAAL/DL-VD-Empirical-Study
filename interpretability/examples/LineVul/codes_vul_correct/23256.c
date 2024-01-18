// commit message FFmpeg@b7d9b4a1f1 (target=1, prob=0.99910706, correct=True): avcodec/ituh263dec: Check cbpy in ff_h263_decode_mb()
/*0   */ int ff_h263_decode_mb(MpegEncContext *s,                                                             // (15) 0.03516
/*1   */                       int16_t block[6][64])                                                          // (3) 0.06055
/*2   */ {                                                                                                    // (19) 0.001953
/*3   */     int cbpc, cbpy, i, cbp, pred_x, pred_y, mx, my, dquant;                                          // (1) 0.06445
/*4   */     int16_t *mot_val;                                                                                // (17) 0.02344
/*5   */     const int xy= s->mb_x + s->mb_y * s->mb_stride;                                                  // (8) 0.05273
/*6   */     int cbpb = 0, pb_mv_count = 0;                                                                   // (13) 0.03906
/*7   */     av_assert2(!s->h263_pred);                                                                       // (16) 0.03125
/*8   */     if (s->pict_type == AV_PICTURE_TYPE_P) {                                                         // (12) 0.04297
/*9   */         do{                                                                                          // (18) 0.01758
/*10  */             if (get_bits1(&s->gb)) {                                                                 // (11) 0.04492
/*11  */                 /* skip mb */                                                                        // (14) 0.03906
/*12  */                 s->mb_intra = 0;                                                                     // (10) 0.04687
/*13  */                 for(i=0;i<6;i++)                                                                     // (9) 0.05273
/*14  */                     s->block_last_index[i] = -1;                                                     // (2) 0.06445
/*15  */                 s->mv_dir = MV_DIR_FORWARD;                                                          // (5) 0.05664
/*16  */                 s->mv_type = MV_TYPE_16X16;                                                          // (4) 0.05859
/*17  */                 s->current_picture.mb_type[xy] = MB_TYPE_SKIP | MB_TYPE_16x16 | MB_TYPE_L0;          // (0) 0.09766
/*18  */                 s->mv[0][0][0] = 0;                                                                  // (6) 0.05664
/*19  */                 s->mv[0][0][1] = 0;                                                                  // (7) 0.05664
/*20  */                 s->mb_skipped = !(s->obmc | s->loop_filter);                                         // 0.0
/*21  */                 goto end;                                                                            // 0.0
/*22  */             cbpc = get_vlc2(&s->gb, ff_h263_inter_MCBPC_vlc.table, INTER_MCBPC_VLC_BITS, 2);         // 0.0
/*23  */             if (cbpc < 0){                                                                           // 0.0
/*24  */                 av_log(s->avctx, AV_LOG_ERROR, "cbpc damaged at %d %d\n", s->mb_x, s->mb_y);         // 0.0
/*25  */         }while(cbpc == 20);                                                                          // 0.0
/*26  */         s->bdsp.clear_blocks(s->block[0]);                                                           // 0.0
/*27  */         dquant = cbpc & 8;                                                                           // 0.0
/*28  */         s->mb_intra = ((cbpc & 4) != 0);                                                             // 0.0
/*29  */         if (s->mb_intra) goto intra;                                                                 // 0.0
/*30  */         if(s->pb_frame && get_bits1(&s->gb))                                                         // 0.0
/*31  */             pb_mv_count = h263_get_modb(&s->gb, s->pb_frame, &cbpb);                                 // 0.0
/*32  */         cbpy = get_vlc2(&s->gb, ff_h263_cbpy_vlc.table, CBPY_VLC_BITS, 1);                           // 0.0
/*33  */         if(s->alt_inter_vlc==0 || (cbpc & 3)!=3)                                                     // 0.0
/*34  */             cbpy ^= 0xF;                                                                             // 0.0
/*35  */         cbp = (cbpc & 3) | (cbpy << 2);                                                              // 0.0
/*36  */         if (dquant) {                                                                                // 0.0
/*37  */             h263_decode_dquant(s);                                                                   // 0.0
/*38  */         s->mv_dir = MV_DIR_FORWARD;                                                                  // 0.0
/*39  */         if ((cbpc & 16) == 0) {                                                                      // 0.0
/*40  */             s->current_picture.mb_type[xy] = MB_TYPE_16x16 | MB_TYPE_L0;                             // 0.0
/*41  */             /* 16x16 motion prediction */                                                            // 0.0
/*42  */             s->mv_type = MV_TYPE_16X16;                                                              // 0.0
/*43  */             ff_h263_pred_motion(s, 0, 0, &pred_x, &pred_y);                                          // 0.0
/*44  */             if (s->umvplus)                                                                          // 0.0
/*45  */                mx = h263p_decode_umotion(s, pred_x);                                                 // 0.0
/*46  */             else                                                                                     // 0.0
/*47  */                mx = ff_h263_decode_motion(s, pred_x, 1);                                             // 0.0
/*48  */             if (mx >= 0xffff)                                                                        // 0.0
/*49  */             if (s->umvplus)                                                                          // 0.0
/*50  */                my = h263p_decode_umotion(s, pred_y);                                                 // 0.0
/*51  */             else                                                                                     // 0.0
/*52  */                my = ff_h263_decode_motion(s, pred_y, 1);                                             // 0.0
/*53  */             if (my >= 0xffff)                                                                        // 0.0
/*54  */             s->mv[0][0][0] = mx;                                                                     // 0.0
/*55  */             s->mv[0][0][1] = my;                                                                     // 0.0
/*56  */             if (s->umvplus && (mx - pred_x) == 1 && (my - pred_y) == 1)                              // 0.0
/*57  */                skip_bits1(&s->gb); /* Bit stuffing to prevent PSC */                                 // 0.0
/*58  */         } else {                                                                                     // 0.0
/*59  */             s->current_picture.mb_type[xy] = MB_TYPE_8x8 | MB_TYPE_L0;                               // 0.0
/*60  */             s->mv_type = MV_TYPE_8X8;                                                                // 0.0
/*61  */             for(i=0;i<4;i++) {                                                                       // 0.0
/*62  */                 mot_val = ff_h263_pred_motion(s, i, 0, &pred_x, &pred_y);                            // 0.0
/*63  */                 if (s->umvplus)                                                                      // 0.0
/*64  */                     mx = h263p_decode_umotion(s, pred_x);                                            // 0.0
/*65  */                 else                                                                                 // 0.0
/*66  */                     mx = ff_h263_decode_motion(s, pred_x, 1);                                        // 0.0
/*67  */                 if (mx >= 0xffff)                                                                    // 0.0
/*68  */                 if (s->umvplus)                                                                      // 0.0
/*69  */                     my = h263p_decode_umotion(s, pred_y);                                            // 0.0
/*70  */                 else                                                                                 // 0.0
/*71  */                     my = ff_h263_decode_motion(s, pred_y, 1);                                        // 0.0
/*72  */                 if (my >= 0xffff)                                                                    // 0.0
/*73  */                 s->mv[0][i][0] = mx;                                                                 // 0.0
/*74  */                 s->mv[0][i][1] = my;                                                                 // 0.0
/*75  */                 if (s->umvplus && (mx - pred_x) == 1 && (my - pred_y) == 1)                          // 0.0
/*76  */                   skip_bits1(&s->gb); /* Bit stuffing to prevent PSC */                              // 0.0
/*77  */                 mot_val[0] = mx;                                                                     // 0.0
/*78  */                 mot_val[1] = my;                                                                     // 0.0
/*79  */     } else if(s->pict_type==AV_PICTURE_TYPE_B) {                                                     // 0.0
/*80  */         int mb_type;                                                                                 // 0.0
/*81  */         const int stride= s->b8_stride;                                                              // 0.0
/*82  */         int16_t *mot_val0 = s->current_picture.motion_val[0][2 * (s->mb_x + s->mb_y * stride)];      // 0.0
/*83  */         int16_t *mot_val1 = s->current_picture.motion_val[1][2 * (s->mb_x + s->mb_y * stride)];      // 0.0
/*84  */ //        const int mv_xy= s->mb_x + 1 + s->mb_y * s->mb_stride;                                     // 0.0
/*85  */         //FIXME ugly                                                                                 // 0.0
/*86  */         mot_val0[0       ]= mot_val0[2       ]= mot_val0[0+2*stride]= mot_val0[2+2*stride]=          // 0.0
/*87  */         mot_val0[1       ]= mot_val0[3       ]= mot_val0[1+2*stride]= mot_val0[3+2*stride]=          // 0.0
/*88  */         mot_val1[0       ]= mot_val1[2       ]= mot_val1[0+2*stride]= mot_val1[2+2*stride]=          // 0.0
/*89  */         mot_val1[1       ]= mot_val1[3       ]= mot_val1[1+2*stride]= mot_val1[3+2*stride]= 0;       // 0.0
/*90  */         do{                                                                                          // 0.0
/*91  */             mb_type= get_vlc2(&s->gb, h263_mbtype_b_vlc.table, H263_MBTYPE_B_VLC_BITS, 2);           // 0.0
/*92  */             if (mb_type < 0){                                                                        // 0.0
/*93  */                 av_log(s->avctx, AV_LOG_ERROR, "b mb_type damaged at %d %d\n", s->mb_x, s->mb_y);    // 0.0
/*94  */             mb_type= h263_mb_type_b_map[ mb_type ];                                                  // 0.0
/*95  */         }while(!mb_type);                                                                            // 0.0
/*96  */         s->mb_intra = IS_INTRA(mb_type);                                                             // 0.0
/*97  */         if(HAS_CBP(mb_type)){                                                                        // 0.0
/*98  */             s->bdsp.clear_blocks(s->block[0]);                                                       // 0.0
/*99  */             cbpc = get_vlc2(&s->gb, cbpc_b_vlc.table, CBPC_B_VLC_BITS, 1);                           // 0.0
/*100 */             if(s->mb_intra){                                                                         // 0.0
/*101 */                 dquant = IS_QUANT(mb_type);                                                          // 0.0
/*102 */                 goto intra;                                                                          // 0.0
/*103 */             cbpy = get_vlc2(&s->gb, ff_h263_cbpy_vlc.table, CBPY_VLC_BITS, 1);                       // 0.0
/*104 */             if (cbpy < 0){                                                                           // 0.0
/*105 */                 av_log(s->avctx, AV_LOG_ERROR, "b cbpy damaged at %d %d\n", s->mb_x, s->mb_y);       // 0.0
/*106 */             if(s->alt_inter_vlc==0 || (cbpc & 3)!=3)                                                 // 0.0
/*107 */                 cbpy ^= 0xF;                                                                         // 0.0
/*108 */             cbp = (cbpc & 3) | (cbpy << 2);                                                          // 0.0
/*109 */         }else                                                                                        // 0.0
/*110 */             cbp=0;                                                                                   // 0.0
/*111 */         av_assert2(!s->mb_intra);                                                                    // 0.0
/*112 */         if(IS_QUANT(mb_type)){                                                                       // 0.0
/*113 */             h263_decode_dquant(s);                                                                   // 0.0
/*114 */         if(IS_DIRECT(mb_type)){                                                                      // 0.0
/*115 */             s->mv_dir = MV_DIR_FORWARD | MV_DIR_BACKWARD | MV_DIRECT;                                // 0.0
/*116 */             mb_type |= set_direct_mv(s);                                                             // 0.0
/*117 */         }else{                                                                                       // 0.0
/*118 */             s->mv_dir = 0;                                                                           // 0.0
/*119 */             s->mv_type= MV_TYPE_16X16;                                                               // 0.0
/*120 */ //FIXME UMV                                                                                          // 0.0
/*121 */             if(USES_LIST(mb_type, 0)){                                                               // 0.0
/*122 */                 int16_t *mot_val= ff_h263_pred_motion(s, 0, 0, &pred_x, &pred_y);                    // 0.0
/*123 */                 s->mv_dir = MV_DIR_FORWARD;                                                          // 0.0
/*124 */                 if (s->umvplus)                                                                      // 0.0
/*125 */                     mx = h263p_decode_umotion(s, pred_x);                                            // 0.0
/*126 */                 else                                                                                 // 0.0
/*127 */                     mx = ff_h263_decode_motion(s, pred_x, 1);                                        // 0.0
/*128 */                 if (mx >= 0xffff)                                                                    // 0.0
/*129 */                 if (s->umvplus)                                                                      // 0.0
/*130 */                     my = h263p_decode_umotion(s, pred_y);                                            // 0.0
/*131 */                 else                                                                                 // 0.0
/*132 */                     my = ff_h263_decode_motion(s, pred_y, 1);                                        // 0.0
/*133 */                 if (my >= 0xffff)                                                                    // 0.0
/*134 */                 if (s->umvplus && (mx - pred_x) == 1 && (my - pred_y) == 1)                          // 0.0
/*135 */                     skip_bits1(&s->gb); /* Bit stuffing to prevent PSC */                            // 0.0
/*136 */                 s->mv[0][0][0] = mx;                                                                 // 0.0
/*137 */                 s->mv[0][0][1] = my;                                                                 // 0.0
/*138 */                 mot_val[0       ]= mot_val[2       ]= mot_val[0+2*stride]= mot_val[2+2*stride]= mx;  // 0.0
/*139 */                 mot_val[1       ]= mot_val[3       ]= mot_val[1+2*stride]= mot_val[3+2*stride]= my;  // 0.0
/*140 */             if(USES_LIST(mb_type, 1)){                                                               // 0.0
/*141 */                 int16_t *mot_val= ff_h263_pred_motion(s, 0, 1, &pred_x, &pred_y);                    // 0.0
/*142 */                 s->mv_dir |= MV_DIR_BACKWARD;                                                        // 0.0
/*143 */                 if (s->umvplus)                                                                      // 0.0
/*144 */                     mx = h263p_decode_umotion(s, pred_x);                                            // 0.0
/*145 */                 else                                                                                 // 0.0
/*146 */                     mx = ff_h263_decode_motion(s, pred_x, 1);                                        // 0.0
/*147 */                 if (mx >= 0xffff)                                                                    // 0.0
/*148 */                 if (s->umvplus)                                                                      // 0.0
/*149 */                     my = h263p_decode_umotion(s, pred_y);                                            // 0.0
/*150 */                 else                                                                                 // 0.0
/*151 */                     my = ff_h263_decode_motion(s, pred_y, 1);                                        // 0.0
/*152 */                 if (my >= 0xffff)                                                                    // 0.0
/*153 */                 if (s->umvplus && (mx - pred_x) == 1 && (my - pred_y) == 1)                          // 0.0
/*154 */                     skip_bits1(&s->gb); /* Bit stuffing to prevent PSC */                            // 0.0
/*155 */                 s->mv[1][0][0] = mx;                                                                 // 0.0
/*156 */                 s->mv[1][0][1] = my;                                                                 // 0.0
/*157 */                 mot_val[0       ]= mot_val[2       ]= mot_val[0+2*stride]= mot_val[2+2*stride]= mx;  // 0.0
/*158 */                 mot_val[1       ]= mot_val[3       ]= mot_val[1+2*stride]= mot_val[3+2*stride]= my;  // 0.0
/*159 */         s->current_picture.mb_type[xy] = mb_type;                                                    // 0.0
/*160 */     } else { /* I-Frame */                                                                           // 0.0
/*161 */         do{                                                                                          // 0.0
/*162 */             cbpc = get_vlc2(&s->gb, ff_h263_intra_MCBPC_vlc.table, INTRA_MCBPC_VLC_BITS, 2);         // 0.0
/*163 */             if (cbpc < 0){                                                                           // 0.0
/*164 */                 av_log(s->avctx, AV_LOG_ERROR, "I cbpc damaged at %d %d\n", s->mb_x, s->mb_y);       // 0.0
/*165 */         }while(cbpc == 8);                                                                           // 0.0
/*166 */         s->bdsp.clear_blocks(s->block[0]);                                                           // 0.0
/*167 */         dquant = cbpc & 4;                                                                           // 0.0
/*168 */         s->mb_intra = 1;                                                                             // 0.0
/*169 */ intra:                                                                                               // 0.0
/*170 */         s->current_picture.mb_type[xy] = MB_TYPE_INTRA;                                              // 0.0
/*171 */         if (s->h263_aic) {                                                                           // 0.0
/*172 */             s->ac_pred = get_bits1(&s->gb);                                                          // 0.0
/*173 */             if(s->ac_pred){                                                                          // 0.0
/*174 */                 s->current_picture.mb_type[xy] = MB_TYPE_INTRA | MB_TYPE_ACPRED;                     // 0.0
/*175 */                 s->h263_aic_dir = get_bits1(&s->gb);                                                 // 0.0
/*176 */         }else                                                                                        // 0.0
/*177 */             s->ac_pred = 0;                                                                          // 0.0
/*178 */         if(s->pb_frame && get_bits1(&s->gb))                                                         // 0.0
/*179 */             pb_mv_count = h263_get_modb(&s->gb, s->pb_frame, &cbpb);                                 // 0.0
/*180 */         cbpy = get_vlc2(&s->gb, ff_h263_cbpy_vlc.table, CBPY_VLC_BITS, 1);                           // 0.0
/*181 */         if(cbpy<0){                                                                                  // 0.0
/*182 */             av_log(s->avctx, AV_LOG_ERROR, "I cbpy damaged at %d %d\n", s->mb_x, s->mb_y);           // 0.0
/*183 */         cbp = (cbpc & 3) | (cbpy << 2);                                                              // 0.0
/*184 */         if (dquant) {                                                                                // 0.0
/*185 */             h263_decode_dquant(s);                                                                   // 0.0
/*186 */         pb_mv_count += !!s->pb_frame;                                                                // 0.0
/*187 */     while(pb_mv_count--){                                                                            // 0.0
/*188 */         ff_h263_decode_motion(s, 0, 1);                                                              // 0.0
/*189 */         ff_h263_decode_motion(s, 0, 1);                                                              // 0.0
/*190 */     /* decode each block */                                                                          // 0.0
/*191 */     for (i = 0; i < 6; i++) {                                                                        // 0.0
/*192 */         if (h263_decode_block(s, block[i], i, cbp&32) < 0)                                           // 0.0
/*193 */             return -1;                                                                               // 0.0
/*194 */         cbp+=cbp;                                                                                    // 0.0
/*195 */     if(s->pb_frame && h263_skip_b_part(s, cbpb) < 0)                                                 // 0.0
/*196 */         return -1;                                                                                   // 0.0
/*197 */     if(s->obmc && !s->mb_intra){                                                                     // 0.0
/*198 */         if(s->pict_type == AV_PICTURE_TYPE_P && s->mb_x+1<s->mb_width && s->mb_num_left != 1)        // 0.0
/*199 */             preview_obmc(s);                                                                         // 0.0
/*200 */ end:                                                                                                 // 0.0
/*201 */         /* per-MB end of slice check */                                                              // 0.0
/*202 */     {                                                                                                // 0.0
/*203 */         int v= show_bits(&s->gb, 16);                                                                // 0.0
/*204 */         if (get_bits_left(&s->gb) < 16) {                                                            // 0.0
/*205 */             v >>= 16 - get_bits_left(&s->gb);                                                        // 0.0
/*206 */         if(v==0)                                                                                     // 0.0
/*207 */             return SLICE_END;                                                                        // 0.0
/*208 */     return SLICE_OK;                                                                                 // 0.0
