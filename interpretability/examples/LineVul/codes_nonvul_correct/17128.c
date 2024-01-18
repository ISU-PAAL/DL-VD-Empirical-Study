// commit message FFmpeg@c8241e730f (target=0, prob=0.24548794, correct=True): vaapi_encode: Refactor initialisation
/*0   */ static int vaapi_encode_h264_init_sequence_params(AVCodecContext *avctx)                // (12) 0.04883
/*2   */ {                                                                                       // (20) 0.001953
/*4   */     VAAPIEncodeContext                 *ctx = avctx->priv_data;                         // (0) 0.06641
/*6   */     VAEncSequenceParameterBufferH264  *vseq = ctx->codec_sequence_params;               // (7) 0.05078
/*8   */     VAEncPictureParameterBufferH264   *vpic = ctx->codec_picture_params;                // (8) 0.05078
/*10  */     VAAPIEncodeH264Context            *priv = ctx->priv_data;                           // (1) 0.06055
/*12  */     VAAPIEncodeH264MiscSequenceParams *mseq = &priv->misc_sequence_params;              // (4) 0.05469
/*14  */     int i;                                                                              // (18) 0.01172
/*18  */     {                                                                                   // (19) 0.007813
/*20  */         vseq->seq_parameter_set_id = 0;                                                 // (15) 0.04102
/*24  */         vseq->level_idc = avctx->level;                                                 // (16) 0.03906
/*28  */         vseq->max_num_ref_frames = 2;                                                   // (17) 0.03906
/*32  */         vseq->picture_width_in_mbs  = priv->mb_width;                                   // (9) 0.05078
/*34  */         vseq->picture_height_in_mbs = priv->mb_height;                                  // (13) 0.04883
/*38  */         vseq->seq_fields.bits.chroma_format_idc = 1;                                    // (10) 0.05078
/*40  */         vseq->seq_fields.bits.frame_mbs_only_flag = 1;                                  // (6) 0.05273
/*42  */         vseq->seq_fields.bits.direct_8x8_inference_flag = 1;                            // (3) 0.05664
/*44  */         vseq->seq_fields.bits.log2_max_frame_num_minus4 = 4;                            // (2) 0.05859
/*46  */         vseq->seq_fields.bits.pic_order_cnt_type = 0;                                   // (5) 0.05273
/*50  */         if (ctx->input_width  != ctx->aligned_width ||                                  // (14) 0.04492
/*52  */             ctx->input_height != ctx->aligned_height) {                                 // (11) 0.05078
/*54  */             vseq->frame_cropping_flag = 1;                                              // 0.0
/*58  */             vseq->frame_crop_left_offset   = 0;                                         // 0.0
/*60  */             vseq->frame_crop_right_offset  =                                            // 0.0
/*62  */                 (ctx->aligned_width - ctx->input_width) / 2;                            // 0.0
/*64  */             vseq->frame_crop_top_offset    = 0;                                         // 0.0
/*66  */             vseq->frame_crop_bottom_offset =                                            // 0.0
/*68  */                 (ctx->aligned_height - ctx->input_height) / 2;                          // 0.0
/*70  */         } else {                                                                        // 0.0
/*72  */             vseq->frame_cropping_flag = 0;                                              // 0.0
/*74  */         }                                                                               // 0.0
/*78  */         vseq->vui_parameters_present_flag = 1;                                          // 0.0
/*80  */         if (avctx->sample_aspect_ratio.num != 0) {                                      // 0.0
/*82  */             vseq->vui_fields.bits.aspect_ratio_info_present_flag = 1;                   // 0.0
/*84  */             // There is a large enum of these which we could support                    // 0.0
/*86  */             // individually rather than using the generic X/Y form?                     // 0.0
/*88  */             if (avctx->sample_aspect_ratio.num ==                                       // 0.0
/*90  */                 avctx->sample_aspect_ratio.den) {                                       // 0.0
/*92  */                 vseq->aspect_ratio_idc = 1;                                             // 0.0
/*94  */             } else {                                                                    // 0.0
/*96  */                 vseq->aspect_ratio_idc = 255; // Extended SAR.                          // 0.0
/*98  */                 vseq->sar_width  = avctx->sample_aspect_ratio.num;                      // 0.0
/*100 */                 vseq->sar_height = avctx->sample_aspect_ratio.den;                      // 0.0
/*102 */             }                                                                           // 0.0
/*104 */         }                                                                               // 0.0
/*106 */         if (avctx->color_primaries != AVCOL_PRI_UNSPECIFIED ||                          // 0.0
/*108 */             avctx->color_trc       != AVCOL_TRC_UNSPECIFIED ||                          // 0.0
/*110 */             avctx->colorspace      != AVCOL_SPC_UNSPECIFIED) {                          // 0.0
/*112 */             mseq->video_signal_type_present_flag = 1;                                   // 0.0
/*114 */             mseq->video_format             = 5; // Unspecified.                         // 0.0
/*116 */             mseq->video_full_range_flag    = 0;                                         // 0.0
/*118 */             mseq->colour_description_present_flag = 1;                                  // 0.0
/*120 */             // These enums are derived from the standard and hence                      // 0.0
/*122 */             // we can just use the values directly.                                     // 0.0
/*124 */             mseq->colour_primaries         = avctx->color_primaries;                    // 0.0
/*126 */             mseq->transfer_characteristics = avctx->color_trc;                          // 0.0
/*128 */             mseq->matrix_coefficients      = avctx->colorspace;                         // 0.0
/*130 */         }                                                                               // 0.0
/*134 */         vseq->bits_per_second = avctx->bit_rate;                                        // 0.0
/*138 */         vseq->vui_fields.bits.timing_info_present_flag = 1;                             // 0.0
/*140 */         if (avctx->framerate.num > 0 && avctx->framerate.den > 0) {                     // 0.0
/*142 */             vseq->num_units_in_tick = avctx->framerate.num;                             // 0.0
/*144 */             vseq->time_scale        = 2 * avctx->framerate.den;                         // 0.0
/*146 */             mseq->fixed_frame_rate_flag = 1;                                            // 0.0
/*148 */         } else {                                                                        // 0.0
/*150 */             vseq->num_units_in_tick = avctx->time_base.num;                             // 0.0
/*152 */             vseq->time_scale        = 2 * avctx->time_base.den;                         // 0.0
/*154 */             mseq->fixed_frame_rate_flag = 0;                                            // 0.0
/*156 */         }                                                                               // 0.0
/*160 */         if (ctx->va_rc_mode == VA_RC_CBR) {                                             // 0.0
/*162 */             priv->send_timing_sei = 1;                                                  // 0.0
/*164 */             mseq->nal_hrd_parameters_present_flag = 1;                                  // 0.0
/*168 */             mseq->cpb_cnt_minus1 = 0;                                                   // 0.0
/*172 */             // Try to scale these to a sensible range so that the                       // 0.0
/*174 */             // golomb encode of the value is not overlong.                              // 0.0
/*176 */             mseq->bit_rate_scale =                                                      // 0.0
/*178 */                 av_clip_uintp2(av_log2(avctx->bit_rate) - 15 - 6, 4);                   // 0.0
/*180 */             mseq->bit_rate_value_minus1[0] =                                            // 0.0
/*182 */                 (avctx->bit_rate >> mseq->bit_rate_scale + 6) - 1;                      // 0.0
/*186 */             mseq->cpb_size_scale =                                                      // 0.0
/*188 */                 av_clip_uintp2(av_log2(priv->hrd_params.hrd.buffer_size) - 15 - 4, 4);  // 0.0
/*190 */             mseq->cpb_size_value_minus1[0] =                                            // 0.0
/*192 */                 (priv->hrd_params.hrd.buffer_size >> mseq->cpb_size_scale + 4) - 1;     // 0.0
/*196 */             // CBR mode isn't actually available here, despite naming.                  // 0.0
/*198 */             mseq->cbr_flag[0] = 0;                                                      // 0.0
/*202 */             mseq->initial_cpb_removal_delay_length_minus1 = 23;                         // 0.0
/*204 */             mseq->cpb_removal_delay_length_minus1         = 23;                         // 0.0
/*206 */             mseq->dpb_output_delay_length_minus1          = 7;                          // 0.0
/*208 */             mseq->time_offset_length = 0;                                               // 0.0
/*212 */             // This calculation can easily overflow 32 bits.                            // 0.0
/*214 */             mseq->initial_cpb_removal_delay = 90000 *                                   // 0.0
/*216 */                 (uint64_t)priv->hrd_params.hrd.initial_buffer_fullness /                // 0.0
/*218 */                 priv->hrd_params.hrd.buffer_size;                                       // 0.0
/*222 */             mseq->initial_cpb_removal_delay_offset = 0;                                 // 0.0
/*224 */         } else {                                                                        // 0.0
/*226 */             priv->send_timing_sei = 0;                                                  // 0.0
/*228 */             mseq->nal_hrd_parameters_present_flag = 0;                                  // 0.0
/*230 */         }                                                                               // 0.0
/*234 */         vseq->intra_period     = ctx->p_per_i * (ctx->b_per_p + 1);                     // 0.0
/*236 */         vseq->intra_idr_period = vseq->intra_period;                                    // 0.0
/*238 */         vseq->ip_period        = ctx->b_per_p + 1;                                      // 0.0
/*240 */     }                                                                                   // 0.0
/*244 */     {                                                                                   // 0.0
/*246 */         vpic->CurrPic.picture_id = VA_INVALID_ID;                                       // 0.0
/*248 */         vpic->CurrPic.flags      = VA_PICTURE_H264_INVALID;                             // 0.0
/*252 */         for (i = 0; i < FF_ARRAY_ELEMS(vpic->ReferenceFrames); i++) {                   // 0.0
/*254 */             vpic->ReferenceFrames[i].picture_id = VA_INVALID_ID;                        // 0.0
/*256 */             vpic->ReferenceFrames[i].flags      = VA_PICTURE_H264_INVALID;              // 0.0
/*258 */         }                                                                               // 0.0
/*262 */         vpic->coded_buf = VA_INVALID_ID;                                                // 0.0
/*266 */         vpic->pic_parameter_set_id = 0;                                                 // 0.0
/*268 */         vpic->seq_parameter_set_id = 0;                                                 // 0.0
/*272 */         vpic->num_ref_idx_l0_active_minus1 = 0;                                         // 0.0
/*274 */         vpic->num_ref_idx_l1_active_minus1 = 0;                                         // 0.0
/*278 */         vpic->pic_fields.bits.entropy_coding_mode_flag =                                // 0.0
/*280 */             ((avctx->profile & 0xff) != 66);                                            // 0.0
/*282 */         vpic->pic_fields.bits.weighted_pred_flag = 0;                                   // 0.0
/*284 */         vpic->pic_fields.bits.weighted_bipred_idc = 0;                                  // 0.0
/*286 */         vpic->pic_fields.bits.transform_8x8_mode_flag =                                 // 0.0
/*288 */             ((avctx->profile & 0xff) >= 100);                                           // 0.0
/*292 */         vpic->pic_init_qp = priv->fixed_qp_idr;                                         // 0.0
/*294 */     }                                                                                   // 0.0
/*298 */     {                                                                                   // 0.0
/*300 */         mseq->profile_idc = avctx->profile & 0xff;                                      // 0.0
/*304 */         if (avctx->profile & FF_PROFILE_H264_CONSTRAINED)                               // 0.0
/*306 */             mseq->constraint_set1_flag = 1;                                             // 0.0
/*308 */         if (avctx->profile & FF_PROFILE_H264_INTRA)                                     // 0.0
/*310 */             mseq->constraint_set3_flag = 1;                                             // 0.0
/*312 */     }                                                                                   // 0.0
/*316 */     return 0;                                                                           // 0.0
/*318 */ }                                                                                       // 0.0
