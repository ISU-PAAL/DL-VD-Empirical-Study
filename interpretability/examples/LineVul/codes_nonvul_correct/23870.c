// commit message FFmpeg@80a5d05108 (target=0, prob=0.28803957, correct=True): vaapi_encode: Refactor initialisation
/*0   */ static int vaapi_encode_h265_init_sequence_params(AVCodecContext *avctx)       // (11) 0.04883
/*2   */ {                                                                              // (20) 0.001953
/*4   */     VAAPIEncodeContext                 *ctx = avctx->priv_data;                // (1) 0.06641
/*6   */     VAEncSequenceParameterBufferHEVC  *vseq = ctx->codec_sequence_params;      // (9) 0.05078
/*8   */     VAEncPictureParameterBufferHEVC   *vpic = ctx->codec_picture_params;       // (10) 0.05078
/*10  */     VAAPIEncodeH265Context            *priv = ctx->priv_data;                  // (3) 0.06055
/*12  */     VAAPIEncodeH265MiscSequenceParams *mseq = &priv->misc_sequence_params;     // (7) 0.05469
/*14  */     int i;                                                                     // (18) 0.01172
/*18  */     {                                                                          // (19) 0.007813
/*20  */         // general_profile_space == 0.                                         // (16) 0.03125
/*22  */         vseq->general_profile_idc = 1; // Main profile (ctx->codec_profile?)   // (4) 0.05859
/*24  */         vseq->general_tier_flag = 0;                                           // (14) 0.03516
/*28  */         vseq->general_level_idc = avctx->level * 3;                            // (12) 0.04687
/*32  */         vseq->intra_period = 0;                                                // (15) 0.0332
/*34  */         vseq->intra_idr_period = 0;                                            // (13) 0.03906
/*36  */         vseq->ip_period = 0;                                                   // (17) 0.03125
/*40  */         vseq->pic_width_in_luma_samples  = ctx->aligned_width;                 // (5) 0.05859
/*42  */         vseq->pic_height_in_luma_samples = ctx->aligned_height;                // (6) 0.05664
/*46  */         vseq->seq_fields.bits.chroma_format_idc = 1; // 4:2:0.                 // (2) 0.06445
/*48  */         vseq->seq_fields.bits.separate_colour_plane_flag = 0;                  // (8) 0.05273
/*50  */         vseq->seq_fields.bits.bit_depth_luma_minus8 = 0; // 8-bit luma.        // (0) 0.06836
/*52  */         vseq->seq_fields.bits.bit_depth_chroma_minus8 = 0; // 8-bit chroma.    // 0.0
/*54  */         // Other misc flags all zero.                                          // 0.0
/*58  */         // These have to come from the capabilities of the encoder.  We have   // 0.0
/*60  */         // no way to query it, so just hardcode ones which worked for me...    // 0.0
/*62  */         // CTB size from 8x8 to 32x32.                                         // 0.0
/*64  */         vseq->log2_min_luma_coding_block_size_minus3 = 0;                      // 0.0
/*66  */         vseq->log2_diff_max_min_luma_coding_block_size = 2;                    // 0.0
/*68  */         // Transform size from 4x4 to 32x32.                                   // 0.0
/*70  */         vseq->log2_min_transform_block_size_minus2 = 0;                        // 0.0
/*72  */         vseq->log2_diff_max_min_transform_block_size = 3;                      // 0.0
/*74  */         // Full transform hierarchy allowed (2-5).                             // 0.0
/*76  */         vseq->max_transform_hierarchy_depth_inter = 3;                         // 0.0
/*78  */         vseq->max_transform_hierarchy_depth_intra = 3;                         // 0.0
/*82  */         vseq->vui_parameters_present_flag = 0;                                 // 0.0
/*86  */         vseq->bits_per_second = avctx->bit_rate;                               // 0.0
/*88  */         if (avctx->framerate.num > 0 && avctx->framerate.den > 0) {            // 0.0
/*90  */             vseq->vui_num_units_in_tick = avctx->framerate.num;                // 0.0
/*92  */             vseq->vui_time_scale        = avctx->framerate.den;                // 0.0
/*94  */         } else {                                                               // 0.0
/*96  */             vseq->vui_num_units_in_tick = avctx->time_base.num;                // 0.0
/*98  */             vseq->vui_time_scale        = avctx->time_base.den;                // 0.0
/*100 */         }                                                                      // 0.0
/*104 */         vseq->intra_period     = ctx->p_per_i * (ctx->b_per_p + 1);            // 0.0
/*106 */         vseq->intra_idr_period = vseq->intra_period;                           // 0.0
/*108 */         vseq->ip_period        = ctx->b_per_p + 1;                             // 0.0
/*110 */     }                                                                          // 0.0
/*114 */     {                                                                          // 0.0
/*116 */         vpic->decoded_curr_pic.picture_id = VA_INVALID_ID;                     // 0.0
/*118 */         vpic->decoded_curr_pic.flags      = VA_PICTURE_HEVC_INVALID;           // 0.0
/*122 */         for (i = 0; i < FF_ARRAY_ELEMS(vpic->reference_frames); i++) {         // 0.0
/*124 */             vpic->reference_frames[i].picture_id = VA_INVALID_ID;              // 0.0
/*126 */             vpic->reference_frames[i].flags      = VA_PICTURE_HEVC_INVALID;    // 0.0
/*128 */         }                                                                      // 0.0
/*132 */         vpic->collocated_ref_pic_index = 0xff;                                 // 0.0
/*136 */         vpic->last_picture = 0;                                                // 0.0
/*140 */         vpic->pic_init_qp = priv->fixed_qp_idr;                                // 0.0
/*144 */         vpic->diff_cu_qp_delta_depth = 0;                                      // 0.0
/*146 */         vpic->pps_cb_qp_offset = 0;                                            // 0.0
/*148 */         vpic->pps_cr_qp_offset = 0;                                            // 0.0
/*152 */         // tiles_enabled_flag == 0, so ignore num_tile_(rows|columns)_minus1.  // 0.0
/*156 */         vpic->log2_parallel_merge_level_minus2 = 0;                            // 0.0
/*160 */         // No limit on size.                                                   // 0.0
/*162 */         vpic->ctu_max_bitsize_allowed = 0;                                     // 0.0
/*166 */         vpic->num_ref_idx_l0_default_active_minus1 = 0;                        // 0.0
/*168 */         vpic->num_ref_idx_l1_default_active_minus1 = 0;                        // 0.0
/*172 */         vpic->slice_pic_parameter_set_id = 0;                                  // 0.0
/*176 */         vpic->pic_fields.bits.screen_content_flag = 0;                         // 0.0
/*178 */         vpic->pic_fields.bits.enable_gpu_weighted_prediction = 0;              // 0.0
/*182 */         // Per-CU QP changes are required for non-constant-QP modes.           // 0.0
/*184 */         vpic->pic_fields.bits.cu_qp_delta_enabled_flag =                       // 0.0
/*186 */             ctx->va_rc_mode != VA_RC_CQP;                                      // 0.0
/*188 */     }                                                                          // 0.0
/*192 */     {                                                                          // 0.0
/*194 */         mseq->video_parameter_set_id = 5;                                      // 0.0
/*196 */         mseq->seq_parameter_set_id = 5;                                        // 0.0
/*200 */         mseq->vps_max_layers_minus1 = 0;                                       // 0.0
/*202 */         mseq->vps_max_sub_layers_minus1 = 0;                                   // 0.0
/*204 */         mseq->vps_temporal_id_nesting_flag = 1;                                // 0.0
/*206 */         mseq->sps_max_sub_layers_minus1 = 0;                                   // 0.0
/*208 */         mseq->sps_temporal_id_nesting_flag = 1;                                // 0.0
/*212 */         for (i = 0; i < 32; i++) {                                             // 0.0
/*214 */             mseq->general_profile_compatibility_flag[i] =                      // 0.0
/*216 */                 (i == vseq->general_profile_idc);                              // 0.0
/*218 */         }                                                                      // 0.0
/*222 */         mseq->general_progressive_source_flag    = 1;                          // 0.0
/*224 */         mseq->general_interlaced_source_flag     = 0;                          // 0.0
/*226 */         mseq->general_non_packed_constraint_flag = 0;                          // 0.0
/*228 */         mseq->general_frame_only_constraint_flag = 1;                          // 0.0
/*230 */         mseq->general_inbld_flag = 0;                                          // 0.0
/*234 */         mseq->log2_max_pic_order_cnt_lsb_minus4 = 8;                           // 0.0
/*236 */         mseq->vps_sub_layer_ordering_info_present_flag = 0;                    // 0.0
/*238 */         mseq->vps_max_dec_pic_buffering_minus1[0] = 1;                         // 0.0
/*240 */         mseq->vps_max_num_reorder_pics[0]         = ctx->b_per_p;              // 0.0
/*242 */         mseq->vps_max_latency_increase_plus1[0]   = 0;                         // 0.0
/*244 */         mseq->sps_sub_layer_ordering_info_present_flag = 0;                    // 0.0
/*246 */         mseq->sps_max_dec_pic_buffering_minus1[0] = 1;                         // 0.0
/*248 */         mseq->sps_max_num_reorder_pics[0]         = ctx->b_per_p;              // 0.0
/*250 */         mseq->sps_max_latency_increase_plus1[0]   = 0;                         // 0.0
/*254 */         mseq->vps_timing_info_present_flag = 1;                                // 0.0
/*256 */         mseq->vps_num_units_in_tick = avctx->time_base.num;                    // 0.0
/*258 */         mseq->vps_time_scale        = avctx->time_base.den;                    // 0.0
/*260 */         mseq->vps_poc_proportional_to_timing_flag = 1;                         // 0.0
/*262 */         mseq->vps_num_ticks_poc_diff_minus1 = 0;                               // 0.0
/*266 */         if (ctx->input_width  != ctx->aligned_width ||                         // 0.0
/*268 */             ctx->input_height != ctx->aligned_height) {                        // 0.0
/*270 */             mseq->conformance_window_flag = 1;                                 // 0.0
/*272 */             mseq->conf_win_left_offset   = 0;                                  // 0.0
/*274 */             mseq->conf_win_right_offset  =                                     // 0.0
/*276 */                 (ctx->aligned_width - ctx->input_width) / 2;                   // 0.0
/*278 */             mseq->conf_win_top_offset    = 0;                                  // 0.0
/*280 */             mseq->conf_win_bottom_offset =                                     // 0.0
/*282 */                 (ctx->aligned_height - ctx->input_height) / 2;                 // 0.0
/*284 */         } else {                                                               // 0.0
/*286 */             mseq->conformance_window_flag = 0;                                 // 0.0
/*288 */         }                                                                      // 0.0
/*292 */         mseq->num_short_term_ref_pic_sets = 0;                                 // 0.0
/*294 */         // STRPSs should ideally be here rather than repeated in each slice.   // 0.0
/*298 */         mseq->vui_parameters_present_flag = 1;                                 // 0.0
/*300 */         if (avctx->sample_aspect_ratio.num != 0) {                             // 0.0
/*302 */             mseq->aspect_ratio_info_present_flag = 1;                          // 0.0
/*304 */             if (avctx->sample_aspect_ratio.num ==                              // 0.0
/*306 */                 avctx->sample_aspect_ratio.den) {                              // 0.0
/*308 */                 mseq->aspect_ratio_idc = 1;                                    // 0.0
/*310 */             } else {                                                           // 0.0
/*312 */                 mseq->aspect_ratio_idc = 255; // Extended SAR.                 // 0.0
/*314 */                 mseq->sar_width  = avctx->sample_aspect_ratio.num;             // 0.0
/*316 */                 mseq->sar_height = avctx->sample_aspect_ratio.den;             // 0.0
/*318 */             }                                                                  // 0.0
/*320 */         }                                                                      // 0.0
/*322 */         if (1) {                                                               // 0.0
/*324 */             // Should this be conditional on some of these being set?          // 0.0
/*326 */             mseq->video_signal_type_present_flag = 1;                          // 0.0
/*328 */             mseq->video_format = 5; // Unspecified.                            // 0.0
/*330 */             mseq->video_full_range_flag = 0;                                   // 0.0
/*332 */             mseq->colour_description_present_flag = 1;                         // 0.0
/*334 */             mseq->colour_primaries = avctx->color_primaries;                   // 0.0
/*336 */             mseq->transfer_characteristics = avctx->color_trc;                 // 0.0
/*338 */             mseq->matrix_coeffs = avctx->colorspace;                           // 0.0
/*340 */         }                                                                      // 0.0
/*342 */     }                                                                          // 0.0
/*346 */     return 0;                                                                  // 0.0
/*348 */ }                                                                              // 0.0
