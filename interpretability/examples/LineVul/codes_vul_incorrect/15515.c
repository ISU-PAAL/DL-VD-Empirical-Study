// commit message FFmpeg@d208d1eba3 (target=1, prob=0.119396865, correct=False): hevc_mvs: make sure to always initialize the temporal MV fully
/*0  */ void ff_hevc_luma_mv_merge_mode(HEVCContext *s, int x0, int y0, int nPbW,    // (2) 0.07227
/*2  */                                 int nPbH, int log2_cb_size, int part_idx,    // (0) 0.09961
/*4  */                                 int merge_idx, MvField *mv)                  // (1) 0.08594
/*6  */ {                                                                            // (19) 0.001953
/*8  */     int singleMCLFlag = 0;                                                   // (17) 0.02148
/*10 */     int nCS = 1 << log2_cb_size;                                             // (13) 0.03125
/*12 */     LOCAL_ALIGNED(4, MvField, mergecand_list, [MRG_MAX_NUM_CANDS]);          // (4) 0.0625
/*14 */     int nPbW2 = nPbW;                                                        // (14) 0.0293
/*16 */     int nPbH2 = nPbH;                                                        // (15) 0.0293
/*18 */     HEVCLocalContext *lc = &s->HEVClc;                                       // (11) 0.03711
/*22 */     memset(mergecand_list, 0, MRG_MAX_NUM_CANDS * sizeof(*mergecand_list));  // (5) 0.0625
/*26 */     if (s->pps->log2_parallel_merge_level > 2 && nCS == 8) {                 // (6) 0.05469
/*28 */         singleMCLFlag = 1;                                                   // (16) 0.02734
/*30 */         x0            = lc->cu.x;                                            // (7) 0.05469
/*32 */         y0            = lc->cu.y;                                            // (8) 0.05469
/*34 */         nPbW          = nCS;                                                 // (9) 0.04688
/*36 */         nPbH          = nCS;                                                 // (10) 0.04688
/*38 */         part_idx      = 0;                                                   // (12) 0.03711
/*40 */     }                                                                        // (18) 0.007813
/*44 */     ff_hevc_set_neighbour_available(s, x0, y0, nPbW, nPbH);                  // (3) 0.06641
/*46 */     derive_spatial_merge_candidates(s, x0, y0, nPbW, nPbH, log2_cb_size,     // 0.0
/*48 */                                     singleMCLFlag, part_idx,                 // 0.0
/*50 */                                     merge_idx, mergecand_list);              // 0.0
/*54 */     if (mergecand_list[merge_idx].pred_flag[0] == 1 &&                       // 0.0
/*56 */         mergecand_list[merge_idx].pred_flag[1] == 1 &&                       // 0.0
/*58 */         (nPbW2 + nPbH2) == 12) {                                             // 0.0
/*60 */         mergecand_list[merge_idx].ref_idx[1]   = -1;                         // 0.0
/*62 */         mergecand_list[merge_idx].pred_flag[1] = 0;                          // 0.0
/*64 */     }                                                                        // 0.0
/*68 */     *mv = mergecand_list[merge_idx];                                         // 0.0
/*70 */ }                                                                            // 0.0
