// commit message FFmpeg@73dacabfc9 (target=0, prob=0.72747934, correct=False): ffv1: Check memory allocations
/*0  */ av_cold int ffv1_init_slice_contexts(FFV1Context *f)                      // (10) 0.04297
/*2  */ {                                                                         // (18) 0.001953
/*4  */     int i;                                                                // (16) 0.01172
/*8  */     f->slice_count = f->num_h_slices * f->num_v_slices;                   // (7) 0.05664
/*10 */     if (f->slice_count <= 0) {                                            // (15) 0.02734
/*12 */         av_log(f->avctx, AV_LOG_ERROR, "Invalid number of slices\n");     // (6) 0.05859
/*14 */         return AVERROR(EINVAL);                                           // (14) 0.03125
/*16 */     }                                                                     // (17) 0.007812
/*20 */     for (i = 0; i < f->slice_count; i++) {                                // (11) 0.03906
/*22 */         FFV1Context *fs = av_mallocz(sizeof(*fs));                        // (9) 0.04883
/*24 */         int sx          = i % f->num_h_slices;                            // (4) 0.0625
/*26 */         int sy          = i / f->num_h_slices;                            // (5) 0.06055
/*28 */         int sxs         = f->avctx->width  *  sx      / f->num_h_slices;  // (0) 0.08984
/*30 */         int sxe         = f->avctx->width  * (sx + 1) / f->num_h_slices;  // (1) 0.08594
/*32 */         int sys         = f->avctx->height *  sy      / f->num_v_slices;  // (2) 0.08398
/*34 */         int sye         = f->avctx->height * (sy + 1) / f->num_v_slices;  // (3) 0.08203
/*36 */         f->slice_context[i] = fs;                                         // (13) 0.03516
/*38 */         memcpy(fs, f, sizeof(*fs));                                       // (12) 0.03711
/*40 */         memset(fs->rc_stat2, 0, sizeof(fs->rc_stat2));                    // (8) 0.05469
/*44 */         fs->slice_width  = sxe - sxs;                                     // 0.0
/*46 */         fs->slice_height = sye - sys;                                     // 0.0
/*48 */         fs->slice_x      = sxs;                                           // 0.0
/*50 */         fs->slice_y      = sys;                                           // 0.0
/*54 */         fs->sample_buffer = av_malloc(3 * MAX_PLANES * (fs->width + 6) *  // 0.0
/*56 */                                       sizeof(*fs->sample_buffer));        // 0.0
/*58 */         if (!fs->sample_buffer)                                           // 0.0
/*60 */             return AVERROR(ENOMEM);                                       // 0.0
/*62 */     }                                                                     // 0.0
/*64 */     return 0;                                                             // 0.0
/*66 */ }                                                                         // 0.0
