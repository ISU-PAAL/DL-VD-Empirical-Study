// commit message FFmpeg@066fff755a (target=0, prob=0.40828267, correct=True): vp6: Check for huffman tree build errors
/*0   */ static void vp6_parse_coeff_models(VP56Context *s)                                                                                                                       // (9) 0.03711
/*2   */ {                                                                                                                                                                        // (20) 0.001953
/*4   */     VP56RangeCoder *c = &s->c;                                                                                                                                           // (12) 0.03125
/*6   */     VP56Model *model = s->modelp;                                                                                                                                        // (17) 0.02734
/*8   */     int def_prob[11];                                                                                                                                                    // (19) 0.02148
/*10  */     int node, cg, ctx, pos;                                                                                                                                              // (15) 0.02734
/*12  */     int ct;    /* code type */                                                                                                                                           // (16) 0.02734
/*14  */     int pt;    /* plane type (0 for Y, 1 for U or V) */                                                                                                                  // (7) 0.04688
/*18  */     memset(def_prob, 0x80, sizeof(def_prob));                                                                                                                            // (8) 0.04297
/*22  */     for (pt=0; pt<2; pt++)                                                                                                                                               // (14) 0.0293
/*24  */         for (node=0; node<11; node++)                                                                                                                                    // (10) 0.03711
/*26  */             if (vp56_rac_get_prob(c, vp6_dccv_pct[pt][node])) {                                                                                                          // (0) 0.08203
/*28  */                 def_prob[node] = vp56_rac_gets_nn(c, 7);                                                                                                                 // (3) 0.07227
/*30  */                 model->coeff_dccv[pt][node] = def_prob[node];                                                                                                            // (4) 0.07031
/*32  */             } else if (s->framep[VP56_FRAME_CURRENT]->key_frame) {                                                                                                       // (6) 0.06836
/*34  */                 model->coeff_dccv[pt][node] = def_prob[node];                                                                                                            // (5) 0.07031
/*36  */             }                                                                                                                                                            // (18) 0.02344
/*40  */     if (vp56_rac_get(c)) {                                                                                                                                               // (13) 0.0293
/*42  */         for (pos=1; pos<64; pos++)                                                                                                                                       // (11) 0.03711
/*44  */             if (vp56_rac_get_prob(c, vp6_coeff_reorder_pct[pos]))                                                                                                        // (1) 0.08008
/*46  */                 model->coeff_reorder[pos] = vp56_rac_gets(c, 4);                                                                                                         // (2) 0.07422
/*48  */         vp6_coeff_order_table_init(s);                                                                                                                                   // 0.0
/*50  */     }                                                                                                                                                                    // 0.0
/*54  */     for (cg=0; cg<2; cg++)                                                                                                                                               // 0.0
/*56  */         for (node=0; node<14; node++)                                                                                                                                    // 0.0
/*58  */             if (vp56_rac_get_prob(c, vp6_runv_pct[cg][node]))                                                                                                            // 0.0
/*60  */                 model->coeff_runv[cg][node] = vp56_rac_gets_nn(c, 7);                                                                                                    // 0.0
/*64  */     for (ct=0; ct<3; ct++)                                                                                                                                               // 0.0
/*66  */         for (pt=0; pt<2; pt++)                                                                                                                                           // 0.0
/*68  */             for (cg=0; cg<6; cg++)                                                                                                                                       // 0.0
/*70  */                 for (node=0; node<11; node++)                                                                                                                            // 0.0
/*72  */                     if (vp56_rac_get_prob(c, vp6_ract_pct[ct][pt][cg][node])) {                                                                                          // 0.0
/*74  */                         def_prob[node] = vp56_rac_gets_nn(c, 7);                                                                                                         // 0.0
/*76  */                         model->coeff_ract[pt][ct][cg][node] = def_prob[node];                                                                                            // 0.0
/*78  */                     } else if (s->framep[VP56_FRAME_CURRENT]->key_frame) {                                                                                               // 0.0
/*80  */                         model->coeff_ract[pt][ct][cg][node] = def_prob[node];                                                                                            // 0.0
/*82  */                     }                                                                                                                                                    // 0.0
/*86  */     if (s->use_huffman) {                                                                                                                                                // 0.0
/*88  */         for (pt=0; pt<2; pt++) {                                                                                                                                         // 0.0
/*90  */             vp6_build_huff_tree(s, model->coeff_dccv[pt],                                                                                                                // 0.0
/*92  */                                 vp6_huff_coeff_map, 12, &s->dccv_vlc[pt]);                                                                                               // 0.0
/*94  */             vp6_build_huff_tree(s, model->coeff_runv[pt],                                                                                                                // 0.0
/*96  */                                 vp6_huff_run_map, 9, &s->runv_vlc[pt]);                                                                                                  // 0.0
/*98  */             for (ct=0; ct<3; ct++)                                                                                                                                       // 0.0
/*100 */                 for (cg = 0; cg < 6; cg++)                                                                                                                               // 0.0
/*102 */                     vp6_build_huff_tree(s, model->coeff_ract[pt][ct][cg],                                                                                                // 0.0
/*104 */                                         vp6_huff_coeff_map, 12,                                                                                                          // 0.0
/*106 */                                         &s->ract_vlc[pt][ct][cg]);                                                                                                       // 0.0
/*108 */         }                                                                                                                                                                // 0.0
/*110 */         memset(s->nb_null, 0, sizeof(s->nb_null));                                                                                                                       // 0.0
/*112 */     } else {                                                                                                                                                             // 0.0
/*114 */     /* coeff_dcct is a linear combination of coeff_dccv */                                                                                                               // 0.0
/*116 */     for (pt=0; pt<2; pt++)                                                                                                                                               // 0.0
/*118 */         for (ctx=0; ctx<3; ctx++)                                                                                                                                        // 0.0
/*120 */             for (node=0; node<5; node++)                                                                                                                                 // 0.0
/*122 */                 model->coeff_dcct[pt][ctx][node] = av_clip(((model->coeff_dccv[pt][node] * vp6_dccv_lc[ctx][node][0] + 128) >> 8) + vp6_dccv_lc[ctx][node][1], 1, 255);  // 0.0
/*124 */     }                                                                                                                                                                    // 0.0
/*126 */ }                                                                                                                                                                        // 0.0
