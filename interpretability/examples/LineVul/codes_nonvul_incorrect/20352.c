// commit message FFmpeg@70b1dcef2d (target=0, prob=0.68940496, correct=False): h264: tighten the valid range for ref_frame_count
/*0   */ int ff_h264_decode_seq_parameter_set(GetBitContext *gb, AVCodecContext *avctx,                                 // (3) 0.05859
/*2   */                                      H264ParamSets *ps)                                                        // (1) 0.08594
/*4   */ {                                                                                                              // (19) 0.001953
/*6   */     AVBufferRef *sps_buf;                                                                                      // (16) 0.02344
/*8   */     int profile_idc, level_idc, constraint_set_flags = 0;                                                      // (12) 0.04297
/*10  */     unsigned int sps_id;                                                                                       // (17) 0.01953
/*12  */     int i, log2_max_frame_num_minus4;                                                                          // (14) 0.03516
/*14  */     SPS *sps;                                                                                                  // (18) 0.01758
/*18  */     profile_idc           = get_bits(gb, 8);                                                                   // (10) 0.05078
/*20  */     constraint_set_flags |= get_bits1(gb) << 0;   // constraint_set0_flag                                      // (6) 0.05664
/*22  */     constraint_set_flags |= get_bits1(gb) << 1;   // constraint_set1_flag                                      // (8) 0.05664
/*24  */     constraint_set_flags |= get_bits1(gb) << 2;   // constraint_set2_flag                                      // (7) 0.05664
/*26  */     constraint_set_flags |= get_bits1(gb) << 3;   // constraint_set3_flag                                      // (4) 0.05664
/*28  */     constraint_set_flags |= get_bits1(gb) << 4;   // constraint_set4_flag                                      // (9) 0.05664
/*30  */     constraint_set_flags |= get_bits1(gb) << 5;   // constraint_set5_flag                                      // (5) 0.05664
/*32  */     skip_bits(gb, 2);                             // reserved_zero_2bits                                       // (0) 0.08984
/*34  */     level_idc = get_bits(gb, 8);                                                                               // (15) 0.03125
/*36  */     sps_id    = get_ue_golomb_31(gb);                                                                          // (11) 0.04492
/*40  */     if (sps_id >= MAX_SPS_COUNT) {                                                                             // (13) 0.03711
/*42  */         av_log(avctx, AV_LOG_ERROR, "sps_id %u out of range\n", sps_id);                                       // (2) 0.07422
/*44  */         return AVERROR_INVALIDDATA;                                                                            // 0.0
/*46  */     }                                                                                                          // 0.0
/*50  */     sps_buf = av_buffer_allocz(sizeof(*sps));                                                                  // 0.0
/*52  */     if (!sps_buf)                                                                                              // 0.0
/*54  */         return AVERROR(ENOMEM);                                                                                // 0.0
/*56  */     sps = (SPS*)sps_buf->data;                                                                                 // 0.0
/*60  */     sps->sps_id               = sps_id;                                                                        // 0.0
/*62  */     sps->time_offset_length   = 24;                                                                            // 0.0
/*64  */     sps->profile_idc          = profile_idc;                                                                   // 0.0
/*66  */     sps->constraint_set_flags = constraint_set_flags;                                                          // 0.0
/*68  */     sps->level_idc            = level_idc;                                                                     // 0.0
/*72  */     memset(sps->scaling_matrix4, 16, sizeof(sps->scaling_matrix4));                                            // 0.0
/*74  */     memset(sps->scaling_matrix8, 16, sizeof(sps->scaling_matrix8));                                            // 0.0
/*76  */     sps->scaling_matrix_present = 0;                                                                           // 0.0
/*80  */     if (sps->profile_idc == 100 ||  // High profile                                                            // 0.0
/*82  */         sps->profile_idc == 110 ||  // High10 profile                                                          // 0.0
/*84  */         sps->profile_idc == 122 ||  // High422 profile                                                         // 0.0
/*86  */         sps->profile_idc == 244 ||  // High444 Predictive profile                                              // 0.0
/*88  */         sps->profile_idc ==  44 ||  // Cavlc444 profile                                                        // 0.0
/*90  */         sps->profile_idc ==  83 ||  // Scalable Constrained High profile (SVC)                                 // 0.0
/*92  */         sps->profile_idc ==  86 ||  // Scalable High Intra profile (SVC)                                       // 0.0
/*94  */         sps->profile_idc == 118 ||  // Stereo High profile (MVC)                                               // 0.0
/*96  */         sps->profile_idc == 128 ||  // Multiview High profile (MVC)                                            // 0.0
/*98  */         sps->profile_idc == 138 ||  // Multiview Depth High profile (MVCD)                                     // 0.0
/*100 */         sps->profile_idc == 144) {  // old High444 profile                                                     // 0.0
/*102 */         sps->chroma_format_idc = get_ue_golomb_31(gb);                                                         // 0.0
/*104 */         if (sps->chroma_format_idc > 3) {                                                                      // 0.0
/*106 */             avpriv_request_sample(avctx, "chroma_format_idc %u",                                               // 0.0
/*108 */                                   sps->chroma_format_idc);                                                     // 0.0
/*110 */             goto fail;                                                                                         // 0.0
/*112 */         } else if (sps->chroma_format_idc == 3) {                                                              // 0.0
/*114 */             sps->residual_color_transform_flag = get_bits1(gb);                                                // 0.0
/*116 */         }                                                                                                      // 0.0
/*118 */         sps->bit_depth_luma   = get_ue_golomb(gb) + 8;                                                         // 0.0
/*120 */         sps->bit_depth_chroma = get_ue_golomb(gb) + 8;                                                         // 0.0
/*122 */         if (sps->bit_depth_chroma != sps->bit_depth_luma) {                                                    // 0.0
/*124 */             avpriv_request_sample(avctx,                                                                       // 0.0
/*126 */                                   "Different chroma and luma bit depth");                                      // 0.0
/*128 */             goto fail;                                                                                         // 0.0
/*130 */         }                                                                                                      // 0.0
/*132 */         sps->transform_bypass = get_bits1(gb);                                                                 // 0.0
/*134 */         decode_scaling_matrices(gb, sps, NULL, 1,                                                              // 0.0
/*136 */                                 sps->scaling_matrix4, sps->scaling_matrix8);                                   // 0.0
/*138 */     } else {                                                                                                   // 0.0
/*140 */         sps->chroma_format_idc = 1;                                                                            // 0.0
/*142 */         sps->bit_depth_luma    = 8;                                                                            // 0.0
/*144 */         sps->bit_depth_chroma  = 8;                                                                            // 0.0
/*146 */     }                                                                                                          // 0.0
/*150 */     log2_max_frame_num_minus4 = get_ue_golomb(gb);                                                             // 0.0
/*152 */     if (log2_max_frame_num_minus4 < MIN_LOG2_MAX_FRAME_NUM - 4 ||                                              // 0.0
/*154 */         log2_max_frame_num_minus4 > MAX_LOG2_MAX_FRAME_NUM - 4) {                                              // 0.0
/*156 */         av_log(avctx, AV_LOG_ERROR,                                                                            // 0.0
/*158 */                "log2_max_frame_num_minus4 out of range (0-12): %d\n",                                          // 0.0
/*160 */                log2_max_frame_num_minus4);                                                                     // 0.0
/*162 */         goto fail;                                                                                             // 0.0
/*164 */     }                                                                                                          // 0.0
/*166 */     sps->log2_max_frame_num = log2_max_frame_num_minus4 + 4;                                                   // 0.0
/*170 */     sps->poc_type = get_ue_golomb_31(gb);                                                                      // 0.0
/*174 */     if (sps->poc_type == 0) { // FIXME #define                                                                 // 0.0
/*176 */         sps->log2_max_poc_lsb = get_ue_golomb(gb) + 4;                                                         // 0.0
/*178 */     } else if (sps->poc_type == 1) { // FIXME #define                                                          // 0.0
/*180 */         sps->delta_pic_order_always_zero_flag = get_bits1(gb);                                                 // 0.0
/*182 */         sps->offset_for_non_ref_pic           = get_se_golomb(gb);                                             // 0.0
/*184 */         sps->offset_for_top_to_bottom_field   = get_se_golomb(gb);                                             // 0.0
/*186 */         sps->poc_cycle_length                 = get_ue_golomb(gb);                                             // 0.0
/*190 */         if ((unsigned)sps->poc_cycle_length >=                                                                 // 0.0
/*192 */             FF_ARRAY_ELEMS(sps->offset_for_ref_frame)) {                                                       // 0.0
/*194 */             av_log(avctx, AV_LOG_ERROR,                                                                        // 0.0
/*196 */                    "poc_cycle_length overflow %d\n", sps->poc_cycle_length);                                   // 0.0
/*198 */             goto fail;                                                                                         // 0.0
/*200 */         }                                                                                                      // 0.0
/*204 */         for (i = 0; i < sps->poc_cycle_length; i++)                                                            // 0.0
/*206 */             sps->offset_for_ref_frame[i] = get_se_golomb(gb);                                                  // 0.0
/*208 */     } else if (sps->poc_type != 2) {                                                                           // 0.0
/*210 */         av_log(avctx, AV_LOG_ERROR, "illegal POC type %d\n", sps->poc_type);                                   // 0.0
/*212 */         goto fail;                                                                                             // 0.0
/*214 */     }                                                                                                          // 0.0
/*218 */     sps->ref_frame_count = get_ue_golomb_31(gb);                                                               // 0.0
/*220 */     if (sps->ref_frame_count > H264_MAX_PICTURE_COUNT - 2 ||                                                   // 0.0
/*222 */         sps->ref_frame_count >= 32U) {                                                                         // 0.0
/*224 */         av_log(avctx, AV_LOG_ERROR,                                                                            // 0.0
/*226 */                "too many reference frames %d\n", sps->ref_frame_count);                                        // 0.0
/*228 */         goto fail;                                                                                             // 0.0
/*230 */     }                                                                                                          // 0.0
/*232 */     sps->gaps_in_frame_num_allowed_flag = get_bits1(gb);                                                       // 0.0
/*234 */     sps->mb_width                       = get_ue_golomb(gb) + 1;                                               // 0.0
/*236 */     sps->mb_height                      = get_ue_golomb(gb) + 1;                                               // 0.0
/*238 */     if ((unsigned)sps->mb_width  >= INT_MAX / 16 ||                                                            // 0.0
/*240 */         (unsigned)sps->mb_height >= INT_MAX / 16 ||                                                            // 0.0
/*242 */         av_image_check_size(16 * sps->mb_width,                                                                // 0.0
/*244 */                             16 * sps->mb_height, 0, avctx)) {                                                  // 0.0
/*246 */         av_log(avctx, AV_LOG_ERROR, "mb_width/height overflow\n");                                             // 0.0
/*248 */         goto fail;                                                                                             // 0.0
/*250 */     }                                                                                                          // 0.0
/*254 */     sps->frame_mbs_only_flag = get_bits1(gb);                                                                  // 0.0
/*256 */     if (!sps->frame_mbs_only_flag)                                                                             // 0.0
/*258 */         sps->mb_aff = get_bits1(gb);                                                                           // 0.0
/*260 */     else                                                                                                       // 0.0
/*262 */         sps->mb_aff = 0;                                                                                       // 0.0
/*266 */     sps->direct_8x8_inference_flag = get_bits1(gb);                                                            // 0.0
/*268 */     if (!sps->frame_mbs_only_flag && !sps->direct_8x8_inference_flag) {                                        // 0.0
/*270 */         av_log(avctx, AV_LOG_ERROR,                                                                            // 0.0
/*272 */                "This stream was generated by a broken encoder, invalid 8x8 inference\n");                      // 0.0
/*274 */         goto fail;                                                                                             // 0.0
/*276 */     }                                                                                                          // 0.0
/*280 */ #ifndef ALLOW_INTERLACE                                                                                        // 0.0
/*282 */     if (sps->mb_aff)                                                                                           // 0.0
/*284 */         av_log(avctx, AV_LOG_ERROR,                                                                            // 0.0
/*286 */                "MBAFF support not included; enable it at compile-time.\n");                                    // 0.0
/*288 */ #endif                                                                                                         // 0.0
/*290 */     sps->crop = get_bits1(gb);                                                                                 // 0.0
/*292 */     if (sps->crop) {                                                                                           // 0.0
/*294 */         unsigned int crop_left   = get_ue_golomb(gb);                                                          // 0.0
/*296 */         unsigned int crop_right  = get_ue_golomb(gb);                                                          // 0.0
/*298 */         unsigned int crop_top    = get_ue_golomb(gb);                                                          // 0.0
/*300 */         unsigned int crop_bottom = get_ue_golomb(gb);                                                          // 0.0
/*304 */         if (avctx->flags2 & AV_CODEC_FLAG2_IGNORE_CROP) {                                                      // 0.0
/*306 */             av_log(avctx, AV_LOG_DEBUG, "discarding sps cropping, original "                                   // 0.0
/*308 */                                            "values are l:%d r:%d t:%d b:%d\n",                                 // 0.0
/*310 */                    crop_left, crop_right, crop_top, crop_bottom);                                              // 0.0
/*314 */             sps->crop_left   =                                                                                 // 0.0
/*316 */             sps->crop_right  =                                                                                 // 0.0
/*318 */             sps->crop_top    =                                                                                 // 0.0
/*320 */             sps->crop_bottom = 0;                                                                              // 0.0
/*322 */         } else {                                                                                               // 0.0
/*324 */             int vsub   = (sps->chroma_format_idc == 1) ? 1 : 0;                                                // 0.0
/*326 */             int hsub   = (sps->chroma_format_idc == 1 ||                                                       // 0.0
/*328 */                           sps->chroma_format_idc == 2) ? 1 : 0;                                                // 0.0
/*330 */             int step_x = 1 << hsub;                                                                            // 0.0
/*332 */             int step_y = (2 - sps->frame_mbs_only_flag) << vsub;                                               // 0.0
/*336 */             if (crop_left & (0x1F >> (sps->bit_depth_luma > 8)) &&                                             // 0.0
/*338 */                 !(avctx->flags & AV_CODEC_FLAG_UNALIGNED)) {                                                   // 0.0
/*340 */                 crop_left &= ~(0x1F >> (sps->bit_depth_luma > 8));                                             // 0.0
/*342 */                 av_log(avctx, AV_LOG_WARNING,                                                                  // 0.0
/*344 */                        "Reducing left cropping to %d "                                                         // 0.0
/*346 */                        "chroma samples to preserve alignment.\n",                                              // 0.0
/*348 */                        crop_left);                                                                             // 0.0
/*350 */             }                                                                                                  // 0.0
/*354 */             if (INT_MAX / step_x             <= crop_left               ||                                     // 0.0
/*356 */                 INT_MAX / step_x - crop_left <= crop_right              ||                                     // 0.0
/*358 */                 16 * sps->mb_width <= step_x * (crop_left + crop_right) ||                                     // 0.0
/*360 */                 INT_MAX / step_y             <= crop_top                ||                                     // 0.0
/*362 */                 INT_MAX / step_y - crop_top  <= crop_bottom             ||                                     // 0.0
/*364 */                 16 * sps->mb_height <= step_y * (crop_top + crop_bottom)) {                                    // 0.0
/*366 */                 av_log(avctx, AV_LOG_WARNING, "Invalid crop parameters\n");                                    // 0.0
/*368 */                 if (avctx->err_recognition & AV_EF_EXPLODE)                                                    // 0.0
/*370 */                     goto fail;                                                                                 // 0.0
/*372 */                 crop_left = crop_right = crop_top = crop_bottom = 0;                                           // 0.0
/*374 */             }                                                                                                  // 0.0
/*378 */             sps->crop_left   = crop_left   * step_x;                                                           // 0.0
/*380 */             sps->crop_right  = crop_right  * step_x;                                                           // 0.0
/*382 */             sps->crop_top    = crop_top    * step_y;                                                           // 0.0
/*384 */             sps->crop_bottom = crop_bottom * step_y;                                                           // 0.0
/*386 */         }                                                                                                      // 0.0
/*388 */     } else {                                                                                                   // 0.0
/*390 */         sps->crop_left   =                                                                                     // 0.0
/*392 */         sps->crop_right  =                                                                                     // 0.0
/*394 */         sps->crop_top    =                                                                                     // 0.0
/*396 */         sps->crop_bottom =                                                                                     // 0.0
/*398 */         sps->crop        = 0;                                                                                  // 0.0
/*400 */     }                                                                                                          // 0.0
/*404 */     sps->vui_parameters_present_flag = get_bits1(gb);                                                          // 0.0
/*406 */     if (sps->vui_parameters_present_flag) {                                                                    // 0.0
/*408 */         int ret = decode_vui_parameters(gb, avctx, sps);                                                       // 0.0
/*410 */         if (ret < 0 && avctx->err_recognition & AV_EF_EXPLODE)                                                 // 0.0
/*412 */             goto fail;                                                                                         // 0.0
/*414 */     }                                                                                                          // 0.0
/*418 */     /* if the maximum delay is not stored in the SPS, derive it based on the                                   // 0.0
/*420 */      * level */                                                                                                // 0.0
/*422 */     if (!sps->bitstream_restriction_flag &&                                                                    // 0.0
/*424 */         (sps->ref_frame_count || avctx->strict_std_compliance >= FF_COMPLIANCE_STRICT)) {                      // 0.0
/*426 */         sps->num_reorder_frames = MAX_DELAYED_PIC_COUNT - 1;                                                   // 0.0
/*428 */         for (i = 0; i < FF_ARRAY_ELEMS(level_max_dpb_mbs); i++) {                                              // 0.0
/*430 */             if (level_max_dpb_mbs[i][0] == sps->level_idc) {                                                   // 0.0
/*432 */                 sps->num_reorder_frames = FFMIN(level_max_dpb_mbs[i][1] / (sps->mb_width * sps->mb_height),    // 0.0
/*434 */                                                 sps->num_reorder_frames);                                      // 0.0
/*436 */                 break;                                                                                         // 0.0
/*438 */             }                                                                                                  // 0.0
/*440 */         }                                                                                                      // 0.0
/*442 */     }                                                                                                          // 0.0
/*446 */     if (!sps->sar.den)                                                                                         // 0.0
/*448 */         sps->sar.den = 1;                                                                                      // 0.0
/*452 */     if (avctx->debug & FF_DEBUG_PICT_INFO) {                                                                   // 0.0
/*454 */         static const char csp[4][5] = { "Gray", "420", "422", "444" };                                         // 0.0
/*456 */         av_log(avctx, AV_LOG_DEBUG,                                                                            // 0.0
/*458 */                "sps:%u profile:%d/%d poc:%d ref:%d %dx%d %s %s crop:%u/%u/%u/%u %s %s %"PRId32"/%"PRId32"\n",  // 0.0
/*460 */                sps_id, sps->profile_idc, sps->level_idc,                                                       // 0.0
/*462 */                sps->poc_type,                                                                                  // 0.0
/*464 */                sps->ref_frame_count,                                                                           // 0.0
/*466 */                sps->mb_width, sps->mb_height,                                                                  // 0.0
/*468 */                sps->frame_mbs_only_flag ? "FRM" : (sps->mb_aff ? "MB-AFF" : "PIC-AFF"),                        // 0.0
/*470 */                sps->direct_8x8_inference_flag ? "8B8" : "",                                                    // 0.0
/*472 */                sps->crop_left, sps->crop_right,                                                                // 0.0
/*474 */                sps->crop_top, sps->crop_bottom,                                                                // 0.0
/*476 */                sps->vui_parameters_present_flag ? "VUI" : "",                                                  // 0.0
/*478 */                csp[sps->chroma_format_idc],                                                                    // 0.0
/*480 */                sps->timing_info_present_flag ? sps->num_units_in_tick : 0,                                     // 0.0
/*482 */                sps->timing_info_present_flag ? sps->time_scale : 0);                                           // 0.0
/*484 */     }                                                                                                          // 0.0
/*488 */     /* check if this is a repeat of an already parsed SPS, then keep the                                       // 0.0
/*490 */      * original one.                                                                                           // 0.0
/*492 */      * otherwise drop all PPSes that depend on it */                                                           // 0.0
/*494 */     if (ps->sps_list[sps_id] &&                                                                                // 0.0
/*496 */         !memcmp(ps->sps_list[sps_id]->data, sps_buf->data, sps_buf->size)) {                                   // 0.0
/*498 */         av_buffer_unref(&sps_buf);                                                                             // 0.0
/*500 */     } else {                                                                                                   // 0.0
/*502 */         remove_sps(ps, sps_id);                                                                                // 0.0
/*504 */         ps->sps_list[sps_id] = sps_buf;                                                                        // 0.0
/*506 */     }                                                                                                          // 0.0
/*510 */     return 0;                                                                                                  // 0.0
/*514 */ fail:                                                                                                          // 0.0
/*516 */     av_buffer_unref(&sps_buf);                                                                                 // 0.0
/*518 */     return AVERROR_INVALIDDATA;                                                                                // 0.0
/*520 */ }                                                                                                              // 0.0
