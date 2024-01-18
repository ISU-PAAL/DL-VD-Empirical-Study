// commit message FFmpeg@ac4b32df71 (target=1, prob=0.7752545, correct=True): On2 VP7 decoder
/*0   */ void decode_mb_mode(VP8Context *s, VP8Macroblock *mb, int mb_x, int mb_y,                // (7) 0.06445
/*2   */                     uint8_t *segment, uint8_t *ref, int layout)                          // (6) 0.07227
/*4   */ {                                                                                        // (17) 0.001953
/*6   */     VP56RangeCoder *c = &s->c;                                                           // (11) 0.03125
/*10  */     if (s->segmentation.update_map)                                                      // (12) 0.0293
/*12  */         *segment = vp8_rac_get_tree(c, vp8_segmentid_tree, s->prob->segmentid);          // (2) 0.08203
/*14  */     else if (s->segmentation.enabled)                                                    // (13) 0.02734
/*16  */         *segment = ref ? *ref : *segment;                                                // (10) 0.03906
/*18  */     mb->segment = *segment;                                                              // (14) 0.02539
/*22  */     mb->skip = s->mbskip_enabled ? vp56_rac_get_prob(c, s->prob->mbskip) : 0;            // (1) 0.08398
/*26  */     if (s->keyframe) {                                                                   // (15) 0.02148
/*28  */         mb->mode = vp8_rac_get_tree(c, vp8_pred16x16_tree_intra,                         // (4) 0.07422
/*30  */                                     vp8_pred16x16_prob_intra);                           // (0) 0.09766
/*34  */         if (mb->mode == MODE_I4x4) {                                                     // (8) 0.04297
/*36  */             decode_intra4x4_modes(s, c, mb, mb_x, 1, layout);                            // (5) 0.07422
/*38  */         } else {                                                                         // (16) 0.01953
/*40  */             const uint32_t modes = vp8_pred4x4_mode[mb->mode] * 0x01010101u;             // (3) 0.08203
/*42  */             if (s->mb_layout == 1)                                                       // (9) 0.04102
/*44  */                 AV_WN32A(mb->intra4x4_pred_mode_top, modes);                             // 0.0
/*46  */             else                                                                         // 0.0
/*48  */                 AV_WN32A(s->intra4x4_pred_mode_top + 4 * mb_x, modes);                   // 0.0
/*50  */             AV_WN32A(s->intra4x4_pred_mode_left, modes);                                 // 0.0
/*52  */         }                                                                                // 0.0
/*56  */         mb->chroma_pred_mode = vp8_rac_get_tree(c, vp8_pred8x8c_tree,                    // 0.0
/*58  */                                                 vp8_pred8x8c_prob_intra);                // 0.0
/*60  */         mb->ref_frame        = VP56_FRAME_CURRENT;                                       // 0.0
/*62  */     } else if (vp56_rac_get_prob_branchy(c, s->prob->intra)) {                           // 0.0
/*64  */         // inter MB, 16.2                                                                // 0.0
/*66  */         if (vp56_rac_get_prob_branchy(c, s->prob->last))                                 // 0.0
/*68  */             mb->ref_frame =                                                              // 0.0
/*70  */                 vp56_rac_get_prob(c, s->prob->golden) ? VP56_FRAME_GOLDEN2 /* altref */  // 0.0
/*72  */                                                       : VP56_FRAME_GOLDEN;               // 0.0
/*74  */         else                                                                             // 0.0
/*76  */             mb->ref_frame = VP56_FRAME_PREVIOUS;                                         // 0.0
/*78  */         s->ref_count[mb->ref_frame - 1]++;                                               // 0.0
/*82  */         // motion vectors, 16.3                                                          // 0.0
/*84  */         decode_mvs(s, mb, mb_x, mb_y, layout);                                           // 0.0
/*86  */     } else {                                                                             // 0.0
/*88  */         // intra MB, 16.1                                                                // 0.0
/*90  */         mb->mode = vp8_rac_get_tree(c, vp8_pred16x16_tree_inter, s->prob->pred16x16);    // 0.0
/*94  */         if (mb->mode == MODE_I4x4)                                                       // 0.0
/*96  */             decode_intra4x4_modes(s, c, mb, mb_x, 0, layout);                            // 0.0
/*100 */         mb->chroma_pred_mode = vp8_rac_get_tree(c, vp8_pred8x8c_tree,                    // 0.0
/*102 */                                                 s->prob->pred8x8c);                      // 0.0
/*104 */         mb->ref_frame        = VP56_FRAME_CURRENT;                                       // 0.0
/*106 */         mb->partitioning     = VP8_SPLITMVMODE_NONE;                                     // 0.0
/*108 */         AV_ZERO32(&mb->bmv[0]);                                                          // 0.0
/*110 */     }                                                                                    // 0.0
/*112 */ }                                                                                        // 0.0
