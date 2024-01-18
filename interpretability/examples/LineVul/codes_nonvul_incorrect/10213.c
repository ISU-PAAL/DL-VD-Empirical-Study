// commit message FFmpeg@979bea1300 (target=0, prob=0.5448244, correct=False): check all svq3_get_ue_golomb() returns.
/*0  */ static int rv40_decode_mb_info(RV34DecContext *r)                         // (7) 0.04102
/*2  */ {                                                                         // (25) 0.001953
/*4  */     MpegEncContext *s = &r->s;                                            // (19) 0.0293
/*6  */     GetBitContext *gb = &s->gb;                                           // (20) 0.02734
/*8  */     int q, i;                                                             // (22) 0.01562
/*10 */     int prev_type = 0;                                                    // (21) 0.01953
/*12 */     int mb_pos = s->mb_x + s->mb_y * s->mb_stride;                        // (3) 0.05469
/*14 */     int blocks[RV34_MB_TYPES] = {0};                                      // (8) 0.03906
/*16 */     int count = 0;                                                        // (23) 0.01562
/*20 */     if(!r->s.mb_skip_run)                                                 // (15) 0.03125
/*22 */         r->s.mb_skip_run = svq3_get_ue_golomb(gb) + 1;                    // (0) 0.06641
/*26 */     if(--r->s.mb_skip_run)                                                // (16) 0.03125
/*28 */          return RV34_MB_SKIP;                                             // (11) 0.0332
/*32 */     if(r->avail_cache[6-1])                                               // (17) 0.03125
/*34 */         blocks[r->mb_type[mb_pos - 1]]++;                                 // (6) 0.04297
/*36 */     if(r->avail_cache[6-4]){                                              // (12) 0.0332
/*38 */         blocks[r->mb_type[mb_pos - s->mb_stride]]++;                      // (4) 0.05273
/*40 */         if(r->avail_cache[6-2])                                           // (9) 0.03906
/*42 */             blocks[r->mb_type[mb_pos - s->mb_stride + 1]]++;              // (2) 0.06445
/*44 */         if(r->avail_cache[6-5])                                           // (10) 0.03906
/*46 */             blocks[r->mb_type[mb_pos - s->mb_stride - 1]]++;              // (1) 0.06445
/*48 */     }                                                                     // (24) 0.007812
/*52 */     for(i = 0; i < RV34_MB_TYPES; i++){                                   // (5) 0.04492
/*54 */         if(blocks[i] > count){                                            // (18) 0.03125
/*56 */             count = blocks[i];                                            // (13) 0.0332
/*58 */             prev_type = i;                                                // (14) 0.0332
/*60 */         }                                                                 // 0.0
/*62 */     }                                                                     // 0.0
/*64 */     if(s->pict_type == AV_PICTURE_TYPE_P){                                // 0.0
/*66 */         prev_type = block_num_to_ptype_vlc_num[prev_type];                // 0.0
/*68 */         q = get_vlc2(gb, ptype_vlc[prev_type].table, PTYPE_VLC_BITS, 1);  // 0.0
/*70 */         if(q < PBTYPE_ESCAPE)                                             // 0.0
/*72 */             return q;                                                     // 0.0
/*74 */         q = get_vlc2(gb, ptype_vlc[prev_type].table, PTYPE_VLC_BITS, 1);  // 0.0
/*76 */         av_log(s->avctx, AV_LOG_ERROR, "Dquant for P-frame\n");           // 0.0
/*78 */     }else{                                                                // 0.0
/*80 */         prev_type = block_num_to_btype_vlc_num[prev_type];                // 0.0
/*82 */         q = get_vlc2(gb, btype_vlc[prev_type].table, BTYPE_VLC_BITS, 1);  // 0.0
/*84 */         if(q < PBTYPE_ESCAPE)                                             // 0.0
/*86 */             return q;                                                     // 0.0
/*88 */         q = get_vlc2(gb, btype_vlc[prev_type].table, BTYPE_VLC_BITS, 1);  // 0.0
/*90 */         av_log(s->avctx, AV_LOG_ERROR, "Dquant for B-frame\n");           // 0.0
/*92 */     }                                                                     // 0.0
/*94 */     return 0;                                                             // 0.0
/*96 */ }                                                                         // 0.0
