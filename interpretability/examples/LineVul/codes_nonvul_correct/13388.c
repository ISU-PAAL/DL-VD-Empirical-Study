// commit message FFmpeg@3176217c60 (target=0, prob=0.17934054, correct=True): h264: decouple h264_ps from the h264 decoder
/*0   */ static inline int decode_vui_parameters(H264Context *h, SPS *sps)                                  // (10) 0.04492
/*2   */ {                                                                                                  // (22) 0.001953
/*4   */     int aspect_ratio_info_present_flag;                                                            // (15) 0.0293
/*6   */     unsigned int aspect_ratio_idc;                                                                 // (17) 0.02539
/*10  */     aspect_ratio_info_present_flag = get_bits1(&h->gb);                                            // (11) 0.04492
/*14  */     if (aspect_ratio_info_present_flag) {                                                          // (13) 0.03516
/*16  */         aspect_ratio_idc = get_bits(&h->gb, 8);                                                    // (8) 0.04883
/*18  */         if (aspect_ratio_idc == EXTENDED_SAR) {                                                    // (9) 0.04883
/*20  */             sps->sar.num = get_bits(&h->gb, 16);                                                   // (3) 0.05664
/*22  */             sps->sar.den = get_bits(&h->gb, 16);                                                   // (4) 0.05664
/*24  */         } else if (aspect_ratio_idc < FF_ARRAY_ELEMS(pixel_aspect)) {                              // (0) 0.06836
/*26  */             sps->sar = pixel_aspect[aspect_ratio_idc];                                             // (2) 0.06055
/*28  */         } else {                                                                                   // (18) 0.01953
/*30  */             av_log(h->avctx, AV_LOG_ERROR, "illegal aspect ratio\n");                              // (1) 0.06445
/*32  */             return AVERROR_INVALIDDATA;                                                            // (12) 0.04102
/*34  */         }                                                                                          // (19) 0.01562
/*36  */     } else {                                                                                       // (20) 0.01172
/*38  */         sps->sar.num =                                                                             // (16) 0.0293
/*40  */         sps->sar.den = 0;                                                                          // (14) 0.0332
/*42  */     }                                                                                              // (21) 0.007812
/*46  */     if (get_bits1(&h->gb))      /* overscan_info_present_flag */                                   // (5) 0.05664
/*48  */         get_bits1(&h->gb);      /* overscan_appropriate_flag */                                    // (6) 0.05664
/*52  */     sps->video_signal_type_present_flag = get_bits1(&h->gb);                                       // (7) 0.05078
/*54  */     if (sps->video_signal_type_present_flag) {                                                     // 0.0
/*56  */         get_bits(&h->gb, 3);                 /* video_format */                                    // 0.0
/*58  */         sps->full_range = get_bits1(&h->gb); /* video_full_range_flag */                           // 0.0
/*62  */         sps->colour_description_present_flag = get_bits1(&h->gb);                                  // 0.0
/*64  */         if (sps->colour_description_present_flag) {                                                // 0.0
/*66  */             sps->color_primaries = get_bits(&h->gb, 8); /* colour_primaries */                     // 0.0
/*68  */             sps->color_trc       = get_bits(&h->gb, 8); /* transfer_characteristics */             // 0.0
/*70  */             sps->colorspace      = get_bits(&h->gb, 8); /* matrix_coefficients */                  // 0.0
/*72  */             if (sps->color_primaries >= AVCOL_PRI_NB)                                              // 0.0
/*74  */                 sps->color_primaries = AVCOL_PRI_UNSPECIFIED;                                      // 0.0
/*76  */             if (sps->color_trc >= AVCOL_TRC_NB)                                                    // 0.0
/*78  */                 sps->color_trc = AVCOL_TRC_UNSPECIFIED;                                            // 0.0
/*80  */             if (sps->colorspace >= AVCOL_SPC_NB)                                                   // 0.0
/*82  */                 sps->colorspace = AVCOL_SPC_UNSPECIFIED;                                           // 0.0
/*84  */         }                                                                                          // 0.0
/*86  */     }                                                                                              // 0.0
/*90  */     /* chroma_location_info_present_flag */                                                        // 0.0
/*92  */     if (get_bits1(&h->gb)) {                                                                       // 0.0
/*94  */         /* chroma_sample_location_type_top_field */                                                // 0.0
/*96  */         h->avctx->chroma_sample_location = get_ue_golomb(&h->gb) + 1;                              // 0.0
/*98  */         get_ue_golomb(&h->gb);  /* chroma_sample_location_type_bottom_field */                     // 0.0
/*100 */     }                                                                                              // 0.0
/*104 */     sps->timing_info_present_flag = get_bits1(&h->gb);                                             // 0.0
/*106 */     if (sps->timing_info_present_flag) {                                                           // 0.0
/*108 */         sps->num_units_in_tick = get_bits_long(&h->gb, 32);                                        // 0.0
/*110 */         sps->time_scale        = get_bits_long(&h->gb, 32);                                        // 0.0
/*112 */         if (!sps->num_units_in_tick || !sps->time_scale) {                                         // 0.0
/*114 */             av_log(h->avctx, AV_LOG_ERROR,                                                         // 0.0
/*116 */                    "time_scale/num_units_in_tick invalid or unsupported (%"PRIu32"/%"PRIu32")\n",  // 0.0
/*118 */                    sps->time_scale, sps->num_units_in_tick);                                       // 0.0
/*120 */             return AVERROR_INVALIDDATA;                                                            // 0.0
/*122 */         }                                                                                          // 0.0
/*124 */         sps->fixed_frame_rate_flag = get_bits1(&h->gb);                                            // 0.0
/*126 */     }                                                                                              // 0.0
/*130 */     sps->nal_hrd_parameters_present_flag = get_bits1(&h->gb);                                      // 0.0
/*132 */     if (sps->nal_hrd_parameters_present_flag)                                                      // 0.0
/*134 */         if (decode_hrd_parameters(h, sps) < 0)                                                     // 0.0
/*136 */             return AVERROR_INVALIDDATA;                                                            // 0.0
/*138 */     sps->vcl_hrd_parameters_present_flag = get_bits1(&h->gb);                                      // 0.0
/*140 */     if (sps->vcl_hrd_parameters_present_flag)                                                      // 0.0
/*142 */         if (decode_hrd_parameters(h, sps) < 0)                                                     // 0.0
/*144 */             return AVERROR_INVALIDDATA;                                                            // 0.0
/*146 */     if (sps->nal_hrd_parameters_present_flag ||                                                    // 0.0
/*148 */         sps->vcl_hrd_parameters_present_flag)                                                      // 0.0
/*150 */         get_bits1(&h->gb);     /* low_delay_hrd_flag */                                            // 0.0
/*152 */     sps->pic_struct_present_flag = get_bits1(&h->gb);                                              // 0.0
/*156 */     sps->bitstream_restriction_flag = get_bits1(&h->gb);                                           // 0.0
/*158 */     if (sps->bitstream_restriction_flag) {                                                         // 0.0
/*160 */         get_bits1(&h->gb);     /* motion_vectors_over_pic_boundaries_flag */                       // 0.0
/*162 */         get_ue_golomb(&h->gb); /* max_bytes_per_pic_denom */                                       // 0.0
/*164 */         get_ue_golomb(&h->gb); /* max_bits_per_mb_denom */                                         // 0.0
/*166 */         get_ue_golomb(&h->gb); /* log2_max_mv_length_horizontal */                                 // 0.0
/*168 */         get_ue_golomb(&h->gb); /* log2_max_mv_length_vertical */                                   // 0.0
/*170 */         sps->num_reorder_frames = get_ue_golomb(&h->gb);                                           // 0.0
/*172 */         get_ue_golomb(&h->gb); /*max_dec_frame_buffering*/                                         // 0.0
/*176 */         if (get_bits_left(&h->gb) < 0) {                                                           // 0.0
/*178 */             sps->num_reorder_frames         = 0;                                                   // 0.0
/*180 */             sps->bitstream_restriction_flag = 0;                                                   // 0.0
/*182 */         }                                                                                          // 0.0
/*186 */         if (sps->num_reorder_frames > 16U                                                          // 0.0
/*188 */             /* max_dec_frame_buffering || max_dec_frame_buffering > 16 */) {                       // 0.0
/*190 */             av_log(h->avctx, AV_LOG_ERROR,                                                         // 0.0
/*192 */                    "Clipping illegal num_reorder_frames %d\n",                                     // 0.0
/*194 */                    sps->num_reorder_frames);                                                       // 0.0
/*196 */             sps->num_reorder_frames = 16;                                                          // 0.0
/*198 */             return AVERROR_INVALIDDATA;                                                            // 0.0
/*200 */         }                                                                                          // 0.0
/*202 */     }                                                                                              // 0.0
/*204 */     if (get_bits_left(&h->gb) < 0) {                                                               // 0.0
/*206 */         av_log(h->avctx, AV_LOG_ERROR,                                                             // 0.0
/*208 */                "Overread VUI by %d bits\n", -get_bits_left(&h->gb));                               // 0.0
/*210 */         return AVERROR_INVALIDDATA;                                                                // 0.0
/*212 */     }                                                                                              // 0.0
/*216 */     return 0;                                                                                      // 0.0
/*218 */ }                                                                                                  // 0.0
