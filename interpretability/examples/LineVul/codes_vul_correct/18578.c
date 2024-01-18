// commit message FFmpeg@513a349439 (target=1, prob=0.7334295, correct=True): avcodec/vp56: Fix sign typo
/*0   */ static int vp6_parse_coeff(VP56Context *s)                                                          // (10) 0.0332
/*2   */ {                                                                                                   // (22) 0.001953
/*4   */     VP56RangeCoder *c = s->ccp;                                                                     // (14) 0.03125
/*6   */     VP56Model *model = s->modelp;                                                                   // (18) 0.02734
/*8   */     uint8_t *permute = s->idct_scantable;                                                           // (7) 0.03906
/*10  */     uint8_t *model1, *model2, *model3;                                                              // (9) 0.03711
/*12  */     int coeff, sign, coeff_idx;                                                                     // (16) 0.0293
/*14  */     int b, i, cg, idx, ctx;                                                                         // (11) 0.0332
/*16  */     int pt = 0;    /* plane type (0 for Y, 1 for U or V) */                                         // (3) 0.05078
/*20  */     if (c->end >= c->buffer && c->bits >= 0) {                                                      // (6) 0.03906
/*22  */         av_log(s->avctx, AV_LOG_ERROR, "End of AC stream reached in vp6_parse_coeff\n");            // (0) 0.07812
/*24  */         return AVERROR_INVALIDDATA;                                                                 // (13) 0.0332
/*26  */     }                                                                                               // (21) 0.007812
/*30  */     for (b=0; b<6; b++) {                                                                           // (15) 0.03125
/*32  */         int ct = 1;    /* code type */                                                              // (8) 0.03906
/*34  */         int run = 1;                                                                                // (19) 0.02344
/*38  */         if (b > 3) pt = 1;                                                                          // (12) 0.0332
/*42  */         ctx = s->left_block[ff_vp56_b6to4[b]].not_null_dc                                           // (2) 0.06641
/*44  */               + s->above_blocks[s->above_block_idx[b]].not_null_dc;                                 // (1) 0.07422
/*46  */         model1 = model->coeff_dccv[pt];                                                             // (5) 0.04102
/*48  */         model2 = model->coeff_dcct[pt][ctx];                                                        // (4) 0.04297
/*52  */         coeff_idx = 0;                                                                              // (17) 0.0293
/*54  */         for (;;) {                                                                                  // (20) 0.02344
/*56  */             if ((coeff_idx>1 && ct==0) || vp56_rac_get_prob_branchy(c, model2[0])) {                // 0.0
/*58  */                 /* parse a coeff */                                                                 // 0.0
/*60  */                 if (vp56_rac_get_prob_branchy(c, model2[2])) {                                      // 0.0
/*62  */                     if (vp56_rac_get_prob_branchy(c, model2[3])) {                                  // 0.0
/*64  */                         idx = vp56_rac_get_tree(c, ff_vp56_pc_tree, model1);                        // 0.0
/*66  */                         coeff = ff_vp56_coeff_bias[idx+5];                                          // 0.0
/*68  */                         for (i=ff_vp56_coeff_bit_length[idx]; i>=0; i--)                            // 0.0
/*70  */                             coeff += vp56_rac_get_prob(c, ff_vp56_coeff_parse_table[idx][i]) << i;  // 0.0
/*72  */                     } else {                                                                        // 0.0
/*74  */                         if (vp56_rac_get_prob_branchy(c, model2[4]))                                // 0.0
/*76  */                             coeff = 3 + vp56_rac_get_prob(c, model1[5]);                            // 0.0
/*78  */                         else                                                                        // 0.0
/*80  */                             coeff = 2;                                                              // 0.0
/*82  */                     }                                                                               // 0.0
/*84  */                     ct = 2;                                                                         // 0.0
/*86  */                 } else {                                                                            // 0.0
/*88  */                     ct = 1;                                                                         // 0.0
/*90  */                     coeff = 1;                                                                      // 0.0
/*92  */                 }                                                                                   // 0.0
/*94  */                 sign = vp56_rac_get(c);                                                             // 0.0
/*96  */                 coeff = (coeff ^ -sign) + sign;                                                     // 0.0
/*98  */                 if (coeff_idx)                                                                      // 0.0
/*100 */                     coeff *= s->dequant_ac;                                                         // 0.0
/*102 */                 idx = model->coeff_index_to_pos[coeff_idx];                                         // 0.0
/*104 */                 s->block_coeff[b][permute[idx]] = coeff;                                            // 0.0
/*106 */                 run = 1;                                                                            // 0.0
/*108 */             } else {                                                                                // 0.0
/*110 */                 /* parse a run */                                                                   // 0.0
/*112 */                 ct = 0;                                                                             // 0.0
/*114 */                 if (coeff_idx > 0) {                                                                // 0.0
/*116 */                     if (!vp56_rac_get_prob_branchy(c, model2[1]))                                   // 0.0
/*118 */                         break;                                                                      // 0.0
/*122 */                     model3 = model->coeff_runv[coeff_idx >= 6];                                     // 0.0
/*124 */                     run = vp56_rac_get_tree(c, vp6_pcr_tree, model3);                               // 0.0
/*126 */                     if (!run)                                                                       // 0.0
/*128 */                         for (run=9, i=0; i<6; i++)                                                  // 0.0
/*130 */                             run += vp56_rac_get_prob(c, model3[i+8]) << i;                          // 0.0
/*132 */                 }                                                                                   // 0.0
/*134 */             }                                                                                       // 0.0
/*136 */             coeff_idx += run;                                                                       // 0.0
/*138 */             if (coeff_idx >= 64)                                                                    // 0.0
/*140 */                 break;                                                                              // 0.0
/*142 */             cg = vp6_coeff_groups[coeff_idx];                                                       // 0.0
/*144 */             model1 = model2 = model->coeff_ract[pt][ct][cg];                                        // 0.0
/*146 */         }                                                                                           // 0.0
/*150 */         s->left_block[ff_vp56_b6to4[b]].not_null_dc =                                               // 0.0
/*152 */         s->above_blocks[s->above_block_idx[b]].not_null_dc = !!s->block_coeff[b][0];                // 0.0
/*154 */     }                                                                                               // 0.0
/*156 */     return 0;                                                                                       // 0.0
/*158 */ }                                                                                                   // 0.0
