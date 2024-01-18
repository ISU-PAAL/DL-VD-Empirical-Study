// commit message FFmpeg@4bb1070c15 (target=0, prob=0.65469676, correct=False): ffv1: Explicitly name the coder type
/*0   */ static int decode_slice_header(FFV1Context *f, FFV1Context *fs)                  // (10) 0.04297
/*2   */ {                                                                                // (21) 0.001953
/*4   */     RangeCoder *c = &fs->c;                                                      // (14) 0.02734
/*6   */     uint8_t state[CONTEXT_SIZE];                                                 // (16) 0.02734
/*8   */     unsigned ps, i, context_count;                                               // (17) 0.02344
/*10  */     memset(state, 128, sizeof(state));                                           // (15) 0.02734
/*14  */     if (fs->ac > 1) {                                                            // (18) 0.02344
/*16  */         for (i = 1; i < 256; i++) {                                              // (12) 0.03906
/*18  */             fs->c.one_state[i]        = f->state_transition[i];                  // (0) 0.07422
/*20  */             fs->c.zero_state[256 - i] = 256 - fs->c.one_state[i];                // (1) 0.07031
/*22  */         }                                                                        // (19) 0.01562
/*24  */     }                                                                            // (20) 0.007812
/*28  */     fs->slice_x      = get_symbol(c, state, 0) * f->width;                       // (6) 0.05859
/*30  */     fs->slice_y      = get_symbol(c, state, 0) * f->height;                      // (7) 0.05859
/*32  */     fs->slice_width  = (get_symbol(c, state, 0) + 1) * f->width + fs->slice_x;   // (2) 0.07031
/*34  */     fs->slice_height = (get_symbol(c, state, 0) + 1) * f->height + fs->slice_y;  // (3) 0.06836
/*38  */     fs->slice_x     /= f->num_h_slices;                                          // (8) 0.04687
/*40  */     fs->slice_y     /= f->num_v_slices;                                          // (9) 0.04687
/*42  */     fs->slice_width  = fs->slice_width / f->num_h_slices - fs->slice_x;          // (4) 0.0625
/*44  */     fs->slice_height = fs->slice_height / f->num_v_slices - fs->slice_y;         // (5) 0.06055
/*46  */     if ((unsigned)fs->slice_width  > f->width ||                                 // (13) 0.03516
/*48  */         (unsigned)fs->slice_height > f->height)                                  // (11) 0.03906
/*50  */         return AVERROR_INVALIDDATA;                                              // 0.0
/*52  */     if ((unsigned)fs->slice_x + (uint64_t)fs->slice_width  > f->width ||         // 0.0
/*54  */         (unsigned)fs->slice_y + (uint64_t)fs->slice_height > f->height)          // 0.0
/*56  */         return AVERROR_INVALIDDATA;                                              // 0.0
/*60  */     for (i = 0; i < f->plane_count; i++) {                                       // 0.0
/*62  */         PlaneContext *const p = &fs->plane[i];                                   // 0.0
/*64  */         int idx               = get_symbol(c, state, 0);                         // 0.0
/*66  */         if (idx > (unsigned)f->quant_table_count) {                              // 0.0
/*68  */             av_log(f->avctx, AV_LOG_ERROR, "quant_table_index out of range\n");  // 0.0
/*70  */             return AVERROR_INVALIDDATA;                                          // 0.0
/*72  */         }                                                                        // 0.0
/*74  */         p->quant_table_index = idx;                                              // 0.0
/*76  */         memcpy(p->quant_table, f->quant_tables[idx], sizeof(p->quant_table));    // 0.0
/*78  */         context_count = f->context_count[idx];                                   // 0.0
/*82  */         if (p->context_count < context_count) {                                  // 0.0
/*84  */             av_freep(&p->state);                                                 // 0.0
/*86  */             av_freep(&p->vlc_state);                                             // 0.0
/*88  */         }                                                                        // 0.0
/*90  */         p->context_count = context_count;                                        // 0.0
/*92  */     }                                                                            // 0.0
/*96  */     ps = get_symbol(c, state, 0);                                                // 0.0
/*98  */     if (ps == 1) {                                                               // 0.0
/*100 */         f->cur->interlaced_frame = 1;                                            // 0.0
/*102 */         f->cur->top_field_first  = 1;                                            // 0.0
/*104 */     } else if (ps == 2) {                                                        // 0.0
/*106 */         f->cur->interlaced_frame = 1;                                            // 0.0
/*108 */         f->cur->top_field_first  = 0;                                            // 0.0
/*110 */     } else if (ps == 3) {                                                        // 0.0
/*112 */         f->cur->interlaced_frame = 0;                                            // 0.0
/*114 */     }                                                                            // 0.0
/*116 */     f->cur->sample_aspect_ratio.num = get_symbol(c, state, 0);                   // 0.0
/*118 */     f->cur->sample_aspect_ratio.den = get_symbol(c, state, 0);                   // 0.0
/*122 */     if (av_image_check_sar(f->width, f->height,                                  // 0.0
/*124 */                            f->cur->sample_aspect_ratio) < 0) {                   // 0.0
/*126 */         av_log(f->avctx, AV_LOG_WARNING, "ignoring invalid SAR: %u/%u\n",        // 0.0
/*128 */                f->cur->sample_aspect_ratio.num,                                  // 0.0
/*130 */                f->cur->sample_aspect_ratio.den);                                 // 0.0
/*132 */         f->cur->sample_aspect_ratio = (AVRational){ 0, 1 };                      // 0.0
/*134 */     }                                                                            // 0.0
/*138 */     return 0;                                                                    // 0.0
/*140 */ }                                                                                // 0.0
