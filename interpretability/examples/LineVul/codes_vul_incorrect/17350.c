// commit message FFmpeg@ae4c9ddebc (target=1, prob=0.40105274, correct=False): vf_psnr: sse2 optimizations for sum-squared-error.
/*0  */ static AVFrame *do_psnr(AVFilterContext *ctx, AVFrame *main,                                       // (12) 0.03906
/*2  */                         const AVFrame *ref)                                                        // (4) 0.05664
/*4  */ {                                                                                                  // (20) 0.001953
/*6  */     PSNRContext *s = ctx->priv;                                                                    // (16) 0.02734
/*8  */     double comp_mse[4], mse = 0;                                                                   // (15) 0.03125
/*10 */     int j, c;                                                                                      // (19) 0.01562
/*12 */     AVDictionary **metadata = avpriv_frame_get_metadatap(main);                                    // (8) 0.04492
/*16 */     s->compute_mse(s, (const uint8_t **)main->data, main->linesize,                                // (3) 0.05859
/*18 */                       (const uint8_t **)ref->data, ref->linesize,                                  // (0) 0.07422
/*20 */                        main->width, main->height, comp_mse);                                       // (2) 0.06836
/*24 */     for (j = 0; j < s->nb_components; j++)                                                         // (13) 0.03906
/*26 */         mse += comp_mse[j] * s->planeweight[j];                                                    // (6) 0.05078
/*30 */     s->min_mse = FFMIN(s->min_mse, mse);                                                           // (9) 0.04492
/*32 */     s->max_mse = FFMAX(s->max_mse, mse);                                                           // (10) 0.04492
/*36 */     s->mse += mse;                                                                                 // (17) 0.02148
/*38 */     for (j = 0; j < s->nb_components; j++)                                                         // (14) 0.03906
/*40 */         s->mse_comp[j] += comp_mse[j];                                                             // (7) 0.04688
/*42 */     s->nb_frames++;                                                                                // (18) 0.01758
/*46 */     for (j = 0; j < s->nb_components; j++) {                                                       // (11) 0.04102
/*48 */         c = s->is_rgb ? s->rgba_map[j] : j;                                                        // (5) 0.05469
/*50 */         set_meta(metadata, "lavfi.psnr.mse.", s->comps[j], comp_mse[c]);                           // (1) 0.07227
/*52 */         set_meta(metadata, "lavfi.psnr.psnr.", s->comps[j], get_psnr(comp_mse[c], 1, s->max[c]));  // 0.0
/*54 */     }                                                                                              // 0.0
/*56 */     set_meta(metadata, "lavfi.psnr.mse_avg", 0, mse);                                              // 0.0
/*58 */     set_meta(metadata, "lavfi.psnr.psnr_avg", 0, get_psnr(mse, 1, s->average_max));                // 0.0
/*62 */     if (s->stats_file) {                                                                           // 0.0
/*64 */         fprintf(s->stats_file, "n:%"PRId64" mse_avg:%0.2f ", s->nb_frames, mse);                   // 0.0
/*66 */         for (j = 0; j < s->nb_components; j++) {                                                   // 0.0
/*68 */             c = s->is_rgb ? s->rgba_map[j] : j;                                                    // 0.0
/*70 */             fprintf(s->stats_file, "mse_%c:%0.2f ", s->comps[j], comp_mse[c]);                     // 0.0
/*72 */         }                                                                                          // 0.0
/*74 */         for (j = 0; j < s->nb_components; j++) {                                                   // 0.0
/*76 */             c = s->is_rgb ? s->rgba_map[j] : j;                                                    // 0.0
/*78 */             fprintf(s->stats_file, "psnr_%c:%0.2f ", s->comps[j],                                  // 0.0
/*80 */                     get_psnr(comp_mse[c], 1, s->max[c]));                                          // 0.0
/*82 */         }                                                                                          // 0.0
/*84 */         fprintf(s->stats_file, "\n");                                                              // 0.0
/*86 */     }                                                                                              // 0.0
/*90 */     return main;                                                                                   // 0.0
/*92 */ }                                                                                                  // 0.0
