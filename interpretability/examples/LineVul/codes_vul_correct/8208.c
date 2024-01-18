// commit message FFmpeg@fed92adbb3 (target=1, prob=0.80767906, correct=True): vp8: make mv_min/max thread-local if using partition threading.
/*0   */ void vp8_decode_mvs(VP8Context *s, VP8Macroblock *mb,                                             // (8) 0.04883
/*2   */                     int mb_x, int mb_y, int layout)                                               // (2) 0.06641
/*4   */ {                                                                                                 // (21) 0.001953
/*6   */     VP8Macroblock *mb_edge[3] = { 0      /* top */,                                               // (5) 0.05273
/*8   */                                   mb - 1 /* left */,                                              // (1) 0.08008
/*10  */                                   0      /* top-left */ };                                        // (0) 0.08789
/*12  */     enum { CNT_ZERO, CNT_NEAREST, CNT_NEAR, CNT_SPLITMV };                                        // (3) 0.06445
/*14  */     enum { VP8_EDGE_TOP, VP8_EDGE_LEFT, VP8_EDGE_TOPLEFT };                                       // (4) 0.0625
/*16  */     int idx = CNT_ZERO;                                                                           // (18) 0.02539
/*18  */     int cur_sign_bias = s->sign_bias[mb->ref_frame];                                              // (9) 0.04688
/*20  */     int8_t *sign_bias = s->sign_bias;                                                             // (11) 0.03906
/*22  */     VP56mv near_mv[4];                                                                            // (17) 0.02734
/*24  */     uint8_t cnt[4] = { 0 };                                                                       // (14) 0.03125
/*26  */     VP56RangeCoder *c = &s->c;                                                                    // (15) 0.03125
/*30  */     if (!layout) { // layout is inlined (s->mb_layout is not)                                     // (10) 0.04297
/*32  */         mb_edge[0] = mb + 2;                                                                      // (12) 0.03906
/*34  */         mb_edge[2] = mb + 1;                                                                      // (13) 0.03906
/*36  */     } else {                                                                                      // (19) 0.01172
/*38  */         mb_edge[0] = mb - s->mb_width - 1;                                                        // (6) 0.05078
/*40  */         mb_edge[2] = mb - s->mb_width - 2;                                                        // (7) 0.05078
/*42  */     }                                                                                             // (20) 0.007812
/*46  */     AV_ZERO32(&near_mv[0]);                                                                       // (16) 0.03125
/*48  */     AV_ZERO32(&near_mv[1]);                                                                       // 0.0
/*50  */     AV_ZERO32(&near_mv[2]);                                                                       // 0.0
/*54  */     /* Process MB on top, left and top-left */                                                    // 0.0
/*56  */ #define MV_EDGE_CHECK(n)                                                      \                   // 0.0
/*58  */     {                                                                         \                   // 0.0
/*60  */         VP8Macroblock *edge = mb_edge[n];                                     \                   // 0.0
/*62  */         int edge_ref = edge->ref_frame;                                       \                   // 0.0
/*64  */         if (edge_ref != VP56_FRAME_CURRENT) {                                 \                   // 0.0
/*66  */             uint32_t mv = AV_RN32A(&edge->mv);                                \                   // 0.0
/*68  */             if (mv) {                                                         \                   // 0.0
/*70  */                 if (cur_sign_bias != sign_bias[edge_ref]) {                   \                   // 0.0
/*72  */                     /* SWAR negate of the values in mv. */                    \                   // 0.0
/*74  */                     mv = ~mv;                                                 \                   // 0.0
/*76  */                     mv = ((mv & 0x7fff7fff) +                                 \                   // 0.0
/*78  */                           0x00010001) ^ (mv & 0x80008000);                    \                   // 0.0
/*80  */                 }                                                             \                   // 0.0
/*82  */                 if (!n || mv != AV_RN32A(&near_mv[idx]))                      \                   // 0.0
/*84  */                     AV_WN32A(&near_mv[++idx], mv);                            \                   // 0.0
/*86  */                 cnt[idx] += 1 + (n != 2);                                     \                   // 0.0
/*88  */             } else                                                            \                   // 0.0
/*90  */                 cnt[CNT_ZERO] += 1 + (n != 2);                                \                   // 0.0
/*92  */         }                                                                     \                   // 0.0
/*94  */     }                                                                                             // 0.0
/*98  */     MV_EDGE_CHECK(0)                                                                              // 0.0
/*100 */     MV_EDGE_CHECK(1)                                                                              // 0.0
/*102 */     MV_EDGE_CHECK(2)                                                                              // 0.0
/*106 */     mb->partitioning = VP8_SPLITMVMODE_NONE;                                                      // 0.0
/*108 */     if (vp56_rac_get_prob_branchy(c, vp8_mode_contexts[cnt[CNT_ZERO]][0])) {                      // 0.0
/*110 */         mb->mode = VP8_MVMODE_MV;                                                                 // 0.0
/*114 */         /* If we have three distinct MVs, merge first and last if they're the same */             // 0.0
/*116 */         if (cnt[CNT_SPLITMV] &&                                                                   // 0.0
/*118 */             AV_RN32A(&near_mv[1 + VP8_EDGE_TOP]) == AV_RN32A(&near_mv[1 + VP8_EDGE_TOPLEFT]))     // 0.0
/*120 */             cnt[CNT_NEAREST] += 1;                                                                // 0.0
/*124 */         /* Swap near and nearest if necessary */                                                  // 0.0
/*126 */         if (cnt[CNT_NEAR] > cnt[CNT_NEAREST]) {                                                   // 0.0
/*128 */             FFSWAP(uint8_t,     cnt[CNT_NEAREST],     cnt[CNT_NEAR]);                             // 0.0
/*130 */             FFSWAP( VP56mv, near_mv[CNT_NEAREST], near_mv[CNT_NEAR]);                             // 0.0
/*132 */         }                                                                                         // 0.0
/*136 */         if (vp56_rac_get_prob_branchy(c, vp8_mode_contexts[cnt[CNT_NEAREST]][1])) {               // 0.0
/*138 */             if (vp56_rac_get_prob_branchy(c, vp8_mode_contexts[cnt[CNT_NEAR]][2])) {              // 0.0
/*140 */                 /* Choose the best mv out of 0,0 and the nearest mv */                            // 0.0
/*142 */                 clamp_mv(s, &mb->mv, &near_mv[CNT_ZERO + (cnt[CNT_NEAREST] >= cnt[CNT_ZERO])]);   // 0.0
/*144 */                 cnt[CNT_SPLITMV] = ((mb_edge[VP8_EDGE_LEFT]->mode    == VP8_MVMODE_SPLIT) +       // 0.0
/*146 */                                     (mb_edge[VP8_EDGE_TOP]->mode     == VP8_MVMODE_SPLIT)) * 2 +  // 0.0
/*148 */                                     (mb_edge[VP8_EDGE_TOPLEFT]->mode == VP8_MVMODE_SPLIT);        // 0.0
/*152 */                 if (vp56_rac_get_prob_branchy(c, vp8_mode_contexts[cnt[CNT_SPLITMV]][3])) {       // 0.0
/*154 */                     mb->mode = VP8_MVMODE_SPLIT;                                                  // 0.0
/*156 */                     mb->mv = mb->bmv[decode_splitmvs(s, c, mb, layout, IS_VP8) - 1];              // 0.0
/*158 */                 } else {                                                                          // 0.0
/*160 */                     mb->mv.y  += vp8_read_mv_component(c, s->prob->mvc[0]);                       // 0.0
/*162 */                     mb->mv.x  += vp8_read_mv_component(c, s->prob->mvc[1]);                       // 0.0
/*164 */                     mb->bmv[0] = mb->mv;                                                          // 0.0
/*166 */                 }                                                                                 // 0.0
/*168 */             } else {                                                                              // 0.0
/*170 */                 clamp_mv(s, &mb->mv, &near_mv[CNT_NEAR]);                                         // 0.0
/*172 */                 mb->bmv[0] = mb->mv;                                                              // 0.0
/*174 */             }                                                                                     // 0.0
/*176 */         } else {                                                                                  // 0.0
/*178 */             clamp_mv(s, &mb->mv, &near_mv[CNT_NEAREST]);                                          // 0.0
/*180 */             mb->bmv[0] = mb->mv;                                                                  // 0.0
/*182 */         }                                                                                         // 0.0
/*184 */     } else {                                                                                      // 0.0
/*186 */         mb->mode = VP8_MVMODE_ZERO;                                                               // 0.0
/*188 */         AV_ZERO32(&mb->mv);                                                                       // 0.0
/*190 */         mb->bmv[0] = mb->mv;                                                                      // 0.0
/*192 */     }                                                                                             // 0.0
/*194 */ }                                                                                                 // 0.0
