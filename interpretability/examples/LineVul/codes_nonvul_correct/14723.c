// commit message FFmpeg@e22ebd04bc (target=0, prob=0.080228485, correct=True): hevc: Bound check cu_qp_delta
/*0   */ static void hls_transform_tree(HEVCContext *s, int x0, int y0,                           // (9) 0.04492
/*2   */                                int xBase, int yBase, int cb_xBase, int cb_yBase,         // (0) 0.1016
/*4   */                                int log2_cb_size, int log2_trafo_size,                    // (1) 0.0918
/*6   */                                int trafo_depth, int blk_idx)                             // (2) 0.08398
/*8   */ {                                                                                        // (17) 0.001953
/*10  */     HEVCLocalContext *lc = &s->HEVClc;                                                   // (11) 0.03711
/*12  */     uint8_t split_transform_flag;                                                        // (14) 0.02539
/*16  */     if (trafo_depth > 0 && log2_trafo_size == 2) {                                       // (10) 0.04492
/*18  */         SAMPLE_CBF(lc->tt.cbf_cb[trafo_depth], x0, y0) =                                 // (8) 0.06641
/*20  */             SAMPLE_CBF(lc->tt.cbf_cb[trafo_depth - 1], xBase, yBase);                    // (3) 0.07617
/*22  */         SAMPLE_CBF(lc->tt.cbf_cr[trafo_depth], x0, y0) =                                 // (7) 0.06641
/*24  */             SAMPLE_CBF(lc->tt.cbf_cr[trafo_depth - 1], xBase, yBase);                    // (4) 0.07617
/*26  */     } else {                                                                             // (15) 0.01172
/*28  */         SAMPLE_CBF(lc->tt.cbf_cb[trafo_depth], x0, y0) =                                 // (6) 0.06641
/*30  */         SAMPLE_CBF(lc->tt.cbf_cr[trafo_depth], x0, y0) = 0;                              // (5) 0.07031
/*32  */     }                                                                                    // (16) 0.007812
/*36  */     if (lc->cu.intra_split_flag) {                                                       // (12) 0.0332
/*38  */         if (trafo_depth == 1)                                                            // (13) 0.03125
/*40  */             lc->tu.cur_intra_pred_mode = lc->pu.intra_pred_mode[blk_idx];                // 0.0
/*42  */     } else {                                                                             // 0.0
/*44  */         lc->tu.cur_intra_pred_mode = lc->pu.intra_pred_mode[0];                          // 0.0
/*46  */     }                                                                                    // 0.0
/*50  */     lc->tt.cbf_luma = 1;                                                                 // 0.0
/*54  */     lc->tt.inter_split_flag = s->sps->max_transform_hierarchy_depth_inter == 0 &&        // 0.0
/*56  */                               lc->cu.pred_mode == MODE_INTER &&                          // 0.0
/*58  */                               lc->cu.part_mode != PART_2Nx2N &&                          // 0.0
/*60  */                               trafo_depth == 0;                                          // 0.0
/*64  */     if (log2_trafo_size <= s->sps->log2_max_trafo_size &&                                // 0.0
/*66  */         log2_trafo_size >  s->sps->log2_min_tb_size    &&                                // 0.0
/*68  */         trafo_depth     < lc->cu.max_trafo_depth       &&                                // 0.0
/*70  */         !(lc->cu.intra_split_flag && trafo_depth == 0)) {                                // 0.0
/*72  */         split_transform_flag = ff_hevc_split_transform_flag_decode(s, log2_trafo_size);  // 0.0
/*74  */     } else {                                                                             // 0.0
/*76  */         split_transform_flag = log2_trafo_size > s->sps->log2_max_trafo_size ||          // 0.0
/*78  */                                (lc->cu.intra_split_flag && trafo_depth == 0) ||          // 0.0
/*80  */                                lc->tt.inter_split_flag;                                  // 0.0
/*82  */     }                                                                                    // 0.0
/*86  */     if (log2_trafo_size > 2) {                                                           // 0.0
/*88  */         if (trafo_depth == 0 ||                                                          // 0.0
/*90  */             SAMPLE_CBF(lc->tt.cbf_cb[trafo_depth - 1], xBase, yBase)) {                  // 0.0
/*92  */             SAMPLE_CBF(lc->tt.cbf_cb[trafo_depth], x0, y0) =                             // 0.0
/*94  */                 ff_hevc_cbf_cb_cr_decode(s, trafo_depth);                                // 0.0
/*96  */         }                                                                                // 0.0
/*100 */         if (trafo_depth == 0 ||                                                          // 0.0
/*102 */             SAMPLE_CBF(lc->tt.cbf_cr[trafo_depth - 1], xBase, yBase)) {                  // 0.0
/*104 */             SAMPLE_CBF(lc->tt.cbf_cr[trafo_depth], x0, y0) =                             // 0.0
/*106 */                 ff_hevc_cbf_cb_cr_decode(s, trafo_depth);                                // 0.0
/*108 */         }                                                                                // 0.0
/*110 */     }                                                                                    // 0.0
/*114 */     if (split_transform_flag) {                                                          // 0.0
/*116 */         int x1 = x0 + ((1 << log2_trafo_size) >> 1);                                     // 0.0
/*118 */         int y1 = y0 + ((1 << log2_trafo_size) >> 1);                                     // 0.0
/*122 */         hls_transform_tree(s, x0, y0, x0, y0, cb_xBase, cb_yBase, log2_cb_size,          // 0.0
/*124 */                            log2_trafo_size - 1, trafo_depth + 1, 0);                     // 0.0
/*126 */         hls_transform_tree(s, x1, y0, x0, y0, cb_xBase, cb_yBase, log2_cb_size,          // 0.0
/*128 */                            log2_trafo_size - 1, trafo_depth + 1, 1);                     // 0.0
/*130 */         hls_transform_tree(s, x0, y1, x0, y0, cb_xBase, cb_yBase, log2_cb_size,          // 0.0
/*132 */                            log2_trafo_size - 1, trafo_depth + 1, 2);                     // 0.0
/*134 */         hls_transform_tree(s, x1, y1, x0, y0, cb_xBase, cb_yBase, log2_cb_size,          // 0.0
/*136 */                            log2_trafo_size - 1, trafo_depth + 1, 3);                     // 0.0
/*138 */     } else {                                                                             // 0.0
/*140 */         int min_tu_size      = 1 << s->sps->log2_min_tb_size;                            // 0.0
/*142 */         int log2_min_tu_size = s->sps->log2_min_tb_size;                                 // 0.0
/*144 */         int min_tu_width     = s->sps->min_tb_width;                                     // 0.0
/*148 */         if (lc->cu.pred_mode == MODE_INTRA || trafo_depth != 0 ||                        // 0.0
/*150 */             SAMPLE_CBF(lc->tt.cbf_cb[trafo_depth], x0, y0) ||                            // 0.0
/*152 */             SAMPLE_CBF(lc->tt.cbf_cr[trafo_depth], x0, y0)) {                            // 0.0
/*154 */             lc->tt.cbf_luma = ff_hevc_cbf_luma_decode(s, trafo_depth);                   // 0.0
/*156 */         }                                                                                // 0.0
/*160 */         hls_transform_unit(s, x0, y0, xBase, yBase, cb_xBase, cb_yBase,                  // 0.0
/*162 */                            log2_cb_size, log2_trafo_size, trafo_depth, blk_idx);         // 0.0
/*166 */         // TODO: store cbf_luma somewhere else                                           // 0.0
/*168 */         if (lc->tt.cbf_luma) {                                                           // 0.0
/*170 */             int i, j;                                                                    // 0.0
/*172 */             for (i = 0; i < (1 << log2_trafo_size); i += min_tu_size)                    // 0.0
/*174 */                 for (j = 0; j < (1 << log2_trafo_size); j += min_tu_size) {              // 0.0
/*176 */                     int x_tu = (x0 + j) >> log2_min_tu_size;                             // 0.0
/*178 */                     int y_tu = (y0 + i) >> log2_min_tu_size;                             // 0.0
/*180 */                     s->cbf_luma[y_tu * min_tu_width + x_tu] = 1;                         // 0.0
/*182 */                 }                                                                        // 0.0
/*184 */         }                                                                                // 0.0
/*186 */         if (!s->sh.disable_deblocking_filter_flag) {                                     // 0.0
/*188 */             ff_hevc_deblocking_boundary_strengths(s, x0, y0, log2_trafo_size,            // 0.0
/*190 */                                                   lc->slice_or_tiles_up_boundary,        // 0.0
/*192 */                                                   lc->slice_or_tiles_left_boundary);     // 0.0
/*194 */             if (s->pps->transquant_bypass_enable_flag &&                                 // 0.0
/*196 */                 lc->cu.cu_transquant_bypass_flag)                                        // 0.0
/*198 */                 set_deblocking_bypass(s, x0, y0, log2_trafo_size);                       // 0.0
/*200 */         }                                                                                // 0.0
/*202 */     }                                                                                    // 0.0
/*204 */ }                                                                                        // 0.0
