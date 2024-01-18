// commit message FFmpeg@b25e84b739 (target=1, prob=0.9990717, correct=True): hevc: check that the VCL NAL types are the same for all slice segments of a frame
/*0  */ static int hevc_frame_start(HEVCContext *s)                                        // (13) 0.0293
/*2  */ {                                                                                  // (21) 0.001953
/*4  */     HEVCLocalContext *lc = &s->HEVClc;                                             // (8) 0.03711
/*6  */     int ret;                                                                       // (19) 0.01172
/*10 */     memset(s->horizontal_bs, 0, 2 * s->bs_width * (s->bs_height + 1));             // (7) 0.0625
/*12 */     memset(s->vertical_bs,   0, 2 * s->bs_width * (s->bs_height + 1));             // (4) 0.06641
/*14 */     memset(s->cbf_luma,      0, s->sps->min_tb_width * s->sps->min_tb_height);     // (0) 0.08789
/*16 */     memset(s->is_pcm,        0, s->sps->min_pu_width * s->sps->min_pu_height);     // (1) 0.08594
/*20 */     lc->start_of_tiles_x = 0;                                                      // (11) 0.0332
/*22 */     s->is_decoded        = 0;                                                      // (9) 0.03711
/*27 */     if (s->pps->tiles_enabled_flag)                                                // (12) 0.03125
/*29 */         lc->end_of_tiles_x = s->pps->column_width[0] << s->sps->log2_ctb_size;     // (2) 0.08398
/*33 */     ret = ff_hevc_set_new_ref(s, s->sps->sao_enabled ? &s->sao_frame : &s->frame,  // (3) 0.08008
/*35 */                               s->poc);                                             // (5) 0.06641
/*37 */     if (ret < 0)                                                                   // (18) 0.01758
/*39 */         goto fail;                                                                 // (15) 0.01953
/*43 */     ret = ff_hevc_frame_rps(s);                                                    // (10) 0.0332
/*45 */     if (ret < 0) {                                                                 // (17) 0.01953
/*47 */         av_log(s->avctx, AV_LOG_ERROR, "Error constructing the frame RPS.\n");     // (6) 0.06445
/*49 */         goto fail;                                                                 // (16) 0.01953
/*51 */     }                                                                              // (20) 0.007812
/*55 */     ret = set_side_data(s);                                                        // (14) 0.02539
/*57 */     if (ret < 0)                                                                   // 0.0
/*59 */         goto fail;                                                                 // 0.0
/*63 */     av_frame_unref(s->output_frame);                                               // 0.0
/*65 */     ret = ff_hevc_output_frame(s, s->output_frame, 0);                             // 0.0
/*67 */     if (ret < 0)                                                                   // 0.0
/*69 */         goto fail;                                                                 // 0.0
/*73 */     ff_thread_finish_setup(s->avctx);                                              // 0.0
/*77 */     return 0;                                                                      // 0.0
/*81 */ fail:                                                                              // 0.0
/*83 */     if (s->ref)                                                                    // 0.0
/*85 */         ff_thread_report_progress(&s->ref->tf, INT_MAX, 0);                        // 0.0
/*87 */     s->ref = NULL;                                                                 // 0.0
/*89 */     return ret;                                                                    // 0.0
/*91 */ }                                                                                  // 0.0
