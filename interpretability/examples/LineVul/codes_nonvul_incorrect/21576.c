// commit message FFmpeg@577393321c (target=0, prob=0.61131364, correct=False): intrax8: Carry over the loopfilter value in ff_intrax8_decode_picture
/*0   */ int ff_wmv2_decode_secondary_picture_header(MpegEncContext *s)                                        // (8) 0.04492
/*2   */ {                                                                                                     // (21) 0.001953
/*4   */     Wmv2Context *const w = (Wmv2Context *) s;                                                         // (13) 0.04102
/*8   */     if (s->pict_type == AV_PICTURE_TYPE_I) {                                                          // (11) 0.04297
/*10  */         if (w->j_type_bit)                                                                            // (15) 0.0332
/*12  */             w->j_type = get_bits1(&s->gb);                                                            // (6) 0.05078
/*14  */         else                                                                                          // (19) 0.01562
/*16  */             w->j_type = 0; // FIXME check                                                             // (9) 0.04492
/*20  */         if (!w->j_type) {                                                                             // (16) 0.03125
/*22  */             if (w->per_mb_rl_bit)                                                                     // (10) 0.04492
/*24  */                 s->per_mb_rl_table = get_bits1(&s->gb);                                               // (1) 0.06641
/*26  */             else                                                                                      // (17) 0.02344
/*28  */                 s->per_mb_rl_table = 0;                                                               // (4) 0.05273
/*32  */             if (!s->per_mb_rl_table) {                                                                // (7) 0.04687
/*34  */                 s->rl_chroma_table_index = decode012(&s->gb);                                         // (2) 0.06445
/*36  */                 s->rl_table_index        = decode012(&s->gb);                                         // (0) 0.07227
/*38  */             }                                                                                         // (18) 0.02344
/*42  */             s->dc_table_index = get_bits1(&s->gb);                                                    // (3) 0.05469
/*44  */         }                                                                                             // (20) 0.01562
/*46  */         s->inter_intra_pred = 0;                                                                      // (14) 0.03516
/*48  */         s->no_rounding      = 1;                                                                      // (12) 0.04102
/*50  */         if (s->avctx->debug & FF_DEBUG_PICT_INFO) {                                                   // (5) 0.05078
/*52  */             av_log(s->avctx, AV_LOG_DEBUG,                                                            // 0.0
/*54  */                    "qscale:%d rlc:%d rl:%d dc:%d mbrl:%d j_type:%d \n",                               // 0.0
/*56  */                    s->qscale, s->rl_chroma_table_index, s->rl_table_index,                            // 0.0
/*58  */                    s->dc_table_index, s->per_mb_rl_table, w->j_type);                                 // 0.0
/*60  */         }                                                                                             // 0.0
/*62  */     } else {                                                                                          // 0.0
/*64  */         int cbp_index;                                                                                // 0.0
/*66  */         w->j_type = 0;                                                                                // 0.0
/*70  */         parse_mb_skip(w);                                                                             // 0.0
/*72  */         cbp_index = decode012(&s->gb);                                                                // 0.0
/*74  */         if (s->qscale <= 10) {                                                                        // 0.0
/*76  */             int map[3]         = { 0, 2, 1 };                                                         // 0.0
/*78  */             w->cbp_table_index = map[cbp_index];                                                      // 0.0
/*80  */         } else if (s->qscale <= 20) {                                                                 // 0.0
/*82  */             int map[3]         = { 1, 0, 2 };                                                         // 0.0
/*84  */             w->cbp_table_index = map[cbp_index];                                                      // 0.0
/*86  */         } else {                                                                                      // 0.0
/*88  */             int map[3]         = {2,1,0};                                                             // 0.0
/*90  */             w->cbp_table_index = map[cbp_index];                                                      // 0.0
/*92  */         }                                                                                             // 0.0
/*96  */         if (w->mspel_bit)                                                                             // 0.0
/*98  */             s->mspel = get_bits1(&s->gb);                                                             // 0.0
/*100 */         else                                                                                          // 0.0
/*102 */             s->mspel = 0; // FIXME check                                                              // 0.0
/*106 */         if (w->abt_flag) {                                                                            // 0.0
/*108 */             w->per_mb_abt = get_bits1(&s->gb) ^ 1;                                                    // 0.0
/*110 */             if (!w->per_mb_abt)                                                                       // 0.0
/*112 */                 w->abt_type = decode012(&s->gb);                                                      // 0.0
/*114 */         }                                                                                             // 0.0
/*118 */         if (w->per_mb_rl_bit)                                                                         // 0.0
/*120 */             s->per_mb_rl_table = get_bits1(&s->gb);                                                   // 0.0
/*122 */         else                                                                                          // 0.0
/*124 */             s->per_mb_rl_table = 0;                                                                   // 0.0
/*128 */         if (!s->per_mb_rl_table) {                                                                    // 0.0
/*130 */             s->rl_table_index        = decode012(&s->gb);                                             // 0.0
/*132 */             s->rl_chroma_table_index = s->rl_table_index;                                             // 0.0
/*134 */         }                                                                                             // 0.0
/*138 */         s->dc_table_index   = get_bits1(&s->gb);                                                      // 0.0
/*140 */         s->mv_table_index   = get_bits1(&s->gb);                                                      // 0.0
/*144 */         s->inter_intra_pred = 0; // (s->width * s->height < 320 * 240 && s->bit_rate <= II_BITRATE);  // 0.0
/*146 */         s->no_rounding     ^= 1;                                                                      // 0.0
/*150 */         if (s->avctx->debug & FF_DEBUG_PICT_INFO) {                                                   // 0.0
/*152 */             av_log(s->avctx, AV_LOG_DEBUG,                                                            // 0.0
/*154 */                    "rl:%d rlc:%d dc:%d mv:%d mbrl:%d qp:%d mspel:%d "                                 // 0.0
/*156 */                    "per_mb_abt:%d abt_type:%d cbp:%d ii:%d\n",                                        // 0.0
/*158 */                    s->rl_table_index, s->rl_chroma_table_index,                                       // 0.0
/*160 */                    s->dc_table_index, s->mv_table_index,                                              // 0.0
/*162 */                    s->per_mb_rl_table, s->qscale, s->mspel,                                           // 0.0
/*164 */                    w->per_mb_abt, w->abt_type, w->cbp_table_index,                                    // 0.0
/*166 */                    s->inter_intra_pred);                                                              // 0.0
/*168 */         }                                                                                             // 0.0
/*170 */     }                                                                                                 // 0.0
/*172 */     s->esc3_level_length = 0;                                                                         // 0.0
/*174 */     s->esc3_run_length   = 0;                                                                         // 0.0
/*176 */     s->picture_number++; // FIXME ?                                                                   // 0.0
/*180 */     if (w->j_type) {                                                                                  // 0.0
/*182 */         ff_intrax8_decode_picture(&w->x8, 2 * s->qscale, (s->qscale - 1) | 1);                        // 0.0
/*186 */         ff_er_add_slice(&w->s.er, 0, 0,                                                               // 0.0
/*188 */                         (w->s.mb_x >> 1) - 1, (w->s.mb_y >> 1) - 1,                                   // 0.0
/*190 */                         ER_MB_END);                                                                   // 0.0
/*192 */         return 1;                                                                                     // 0.0
/*194 */     }                                                                                                 // 0.0
/*198 */     return 0;                                                                                         // 0.0
/*200 */ }                                                                                                     // 0.0
