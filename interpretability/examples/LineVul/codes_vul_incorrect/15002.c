// commit message FFmpeg@ef23bd939d (target=1, prob=0.47437268, correct=False): avcodec/hevc: Silence "warning: ref0/1 may be used uninitialized in this function"
/*0   */ static void hls_prediction_unit(HEVCContext *s, int x0, int y0,                                                             // (5) 0.04688
/*2   */                                 int nPbW, int nPbH,                                                                         // (4) 0.08398
/*4   */                                 int log2_cb_size, int partIdx, int idx)                                                     // (2) 0.09375
/*6   */ {                                                                                                                           // (16) 0.001953
/*8   */ #define POS(c_idx, x, y)                                                              \                                     // (0) 0.1465
/*10  */     &s->frame->data[c_idx][((y) >> s->sps->vshift[c_idx]) * s->frame->linesize[c_idx] + \                                   // (3) 0.0918
/*12  */                            (((x) >> s->sps->hshift[c_idx]) << s->sps->pixel_shift)]                                         // (1) 0.1055
/*14  */     HEVCLocalContext *lc = s->HEVClc;                                                                                       // (13) 0.03516
/*16  */     int merge_idx = 0;                                                                                                      // (15) 0.02148
/*18  */     struct MvField current_mv = {{{ 0 }}};                                                                                  // (12) 0.03516
/*22  */     int min_pu_width = s->sps->min_pu_width;                                                                                // (10) 0.04102
/*26  */     MvField *tab_mvf = s->ref->tab_mvf;                                                                                     // (6) 0.04492
/*28  */     RefPicList  *refPicList = s->ref->refPicList;                                                                           // (11) 0.03906
/*30  */     HEVCFrame *ref0, *ref1;                                                                                                 // (14) 0.02734
/*32  */     uint8_t *dst0 = POS(0, x0, y0);                                                                                         // (8) 0.04297
/*34  */     uint8_t *dst1 = POS(1, x0, y0);                                                                                         // (9) 0.04297
/*36  */     uint8_t *dst2 = POS(2, x0, y0);                                                                                         // (7) 0.04297
/*38  */     int log2_min_cb_size = s->sps->log2_min_cb_size;                                                                        // 0.0
/*40  */     int min_cb_width     = s->sps->min_cb_width;                                                                            // 0.0
/*42  */     int x_cb             = x0 >> log2_min_cb_size;                                                                          // 0.0
/*44  */     int y_cb             = y0 >> log2_min_cb_size;                                                                          // 0.0
/*46  */     int x_pu, y_pu;                                                                                                         // 0.0
/*48  */     int i, j;                                                                                                               // 0.0
/*52  */     int skip_flag = SAMPLE_CTB(s->skip_flag, x_cb, y_cb);                                                                   // 0.0
/*56  */     if (!skip_flag)                                                                                                         // 0.0
/*58  */         lc->pu.merge_flag = ff_hevc_merge_flag_decode(s);                                                                   // 0.0
/*62  */     if (skip_flag || lc->pu.merge_flag) {                                                                                   // 0.0
/*64  */         if (s->sh.max_num_merge_cand > 1)                                                                                   // 0.0
/*66  */             merge_idx = ff_hevc_merge_idx_decode(s);                                                                        // 0.0
/*68  */         else                                                                                                                // 0.0
/*70  */             merge_idx = 0;                                                                                                  // 0.0
/*74  */         ff_hevc_luma_mv_merge_mode(s, x0, y0, nPbW, nPbH, log2_cb_size,                                                     // 0.0
/*76  */                                    partIdx, merge_idx, &current_mv);                                                        // 0.0
/*78  */     } else {                                                                                                                // 0.0
/*80  */         hevc_luma_mv_mpv_mode(s, x0, y0, nPbW, nPbH, log2_cb_size,                                                          // 0.0
/*82  */                               partIdx, merge_idx, &current_mv);                                                             // 0.0
/*84  */     }                                                                                                                       // 0.0
/*88  */     x_pu = x0 >> s->sps->log2_min_pu_size;                                                                                  // 0.0
/*90  */     y_pu = y0 >> s->sps->log2_min_pu_size;                                                                                  // 0.0
/*94  */     for (j = 0; j < nPbH >> s->sps->log2_min_pu_size; j++)                                                                  // 0.0
/*96  */         for (i = 0; i < nPbW >> s->sps->log2_min_pu_size; i++)                                                              // 0.0
/*98  */             tab_mvf[(y_pu + j) * min_pu_width + x_pu + i] = current_mv;                                                     // 0.0
/*102 */     if (current_mv.pred_flag & PF_L0) {                                                                                     // 0.0
/*104 */         ref0 = refPicList[0].ref[current_mv.ref_idx[0]];                                                                    // 0.0
/*106 */         if (!ref0)                                                                                                          // 0.0
/*108 */             return;                                                                                                         // 0.0
/*110 */         hevc_await_progress(s, ref0, &current_mv.mv[0], y0, nPbH);                                                          // 0.0
/*112 */     }                                                                                                                       // 0.0
/*114 */     if (current_mv.pred_flag & PF_L1) {                                                                                     // 0.0
/*116 */         ref1 = refPicList[1].ref[current_mv.ref_idx[1]];                                                                    // 0.0
/*118 */         if (!ref1)                                                                                                          // 0.0
/*120 */             return;                                                                                                         // 0.0
/*122 */         hevc_await_progress(s, ref1, &current_mv.mv[1], y0, nPbH);                                                          // 0.0
/*124 */     }                                                                                                                       // 0.0
/*128 */     if (current_mv.pred_flag == PF_L0) {                                                                                    // 0.0
/*130 */         int x0_c = x0 >> s->sps->hshift[1];                                                                                 // 0.0
/*132 */         int y0_c = y0 >> s->sps->vshift[1];                                                                                 // 0.0
/*134 */         int nPbW_c = nPbW >> s->sps->hshift[1];                                                                             // 0.0
/*136 */         int nPbH_c = nPbH >> s->sps->vshift[1];                                                                             // 0.0
/*140 */         luma_mc_uni(s, dst0, s->frame->linesize[0], ref0->frame,                                                            // 0.0
/*142 */                     &current_mv.mv[0], x0, y0, nPbW, nPbH,                                                                  // 0.0
/*144 */                     s->sh.luma_weight_l0[current_mv.ref_idx[0]],                                                            // 0.0
/*146 */                     s->sh.luma_offset_l0[current_mv.ref_idx[0]]);                                                           // 0.0
/*150 */         chroma_mc_uni(s, dst1, s->frame->linesize[1], ref0->frame->data[1], ref0->frame->linesize[1],                       // 0.0
/*152 */                       0, x0_c, y0_c, nPbW_c, nPbH_c, &current_mv,                                                           // 0.0
/*154 */                       s->sh.chroma_weight_l0[current_mv.ref_idx[0]][0], s->sh.chroma_offset_l0[current_mv.ref_idx[0]][0]);  // 0.0
/*156 */         chroma_mc_uni(s, dst2, s->frame->linesize[2], ref0->frame->data[2], ref0->frame->linesize[2],                       // 0.0
/*158 */                       0, x0_c, y0_c, nPbW_c, nPbH_c, &current_mv,                                                           // 0.0
/*160 */                       s->sh.chroma_weight_l0[current_mv.ref_idx[0]][1], s->sh.chroma_offset_l0[current_mv.ref_idx[0]][1]);  // 0.0
/*162 */     } else if (current_mv.pred_flag == PF_L1) {                                                                             // 0.0
/*164 */         int x0_c = x0 >> s->sps->hshift[1];                                                                                 // 0.0
/*166 */         int y0_c = y0 >> s->sps->vshift[1];                                                                                 // 0.0
/*168 */         int nPbW_c = nPbW >> s->sps->hshift[1];                                                                             // 0.0
/*170 */         int nPbH_c = nPbH >> s->sps->vshift[1];                                                                             // 0.0
/*174 */         luma_mc_uni(s, dst0, s->frame->linesize[0], ref1->frame,                                                            // 0.0
/*176 */                     &current_mv.mv[1], x0, y0, nPbW, nPbH,                                                                  // 0.0
/*178 */                     s->sh.luma_weight_l1[current_mv.ref_idx[1]],                                                            // 0.0
/*180 */                     s->sh.luma_offset_l1[current_mv.ref_idx[1]]);                                                           // 0.0
/*184 */         chroma_mc_uni(s, dst1, s->frame->linesize[1], ref1->frame->data[1], ref1->frame->linesize[1],                       // 0.0
/*186 */                       1, x0_c, y0_c, nPbW_c, nPbH_c, &current_mv,                                                           // 0.0
/*188 */                       s->sh.chroma_weight_l1[current_mv.ref_idx[1]][0], s->sh.chroma_offset_l1[current_mv.ref_idx[1]][0]);  // 0.0
/*192 */         chroma_mc_uni(s, dst2, s->frame->linesize[2], ref1->frame->data[2], ref1->frame->linesize[2],                       // 0.0
/*194 */                       1, x0_c, y0_c, nPbW_c, nPbH_c, &current_mv,                                                           // 0.0
/*196 */                       s->sh.chroma_weight_l1[current_mv.ref_idx[1]][1], s->sh.chroma_offset_l1[current_mv.ref_idx[1]][1]);  // 0.0
/*198 */     } else if (current_mv.pred_flag == PF_BI) {                                                                             // 0.0
/*200 */         int x0_c = x0 >> s->sps->hshift[1];                                                                                 // 0.0
/*202 */         int y0_c = y0 >> s->sps->vshift[1];                                                                                 // 0.0
/*204 */         int nPbW_c = nPbW >> s->sps->hshift[1];                                                                             // 0.0
/*206 */         int nPbH_c = nPbH >> s->sps->vshift[1];                                                                             // 0.0
/*210 */         luma_mc_bi(s, dst0, s->frame->linesize[0], ref0->frame,                                                             // 0.0
/*212 */                    &current_mv.mv[0], x0, y0, nPbW, nPbH,                                                                   // 0.0
/*214 */                    ref1->frame, &current_mv.mv[1], &current_mv);                                                            // 0.0
/*218 */         chroma_mc_bi(s, dst1, s->frame->linesize[1], ref0->frame, ref1->frame,                                              // 0.0
/*220 */                      x0_c, y0_c, nPbW_c, nPbH_c, &current_mv, 0);                                                           // 0.0
/*224 */         chroma_mc_bi(s, dst2, s->frame->linesize[2], ref0->frame, ref1->frame,                                              // 0.0
/*226 */                      x0_c, y0_c, nPbW_c, nPbH_c, &current_mv, 1);                                                           // 0.0
/*228 */     }                                                                                                                       // 0.0
/*230 */ }                                                                                                                           // 0.0
