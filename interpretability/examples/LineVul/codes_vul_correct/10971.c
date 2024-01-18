// commit message FFmpeg@9568b2e425 (target=1, prob=0.99910754, correct=True): avcodec/h264_ps: Check chroma_qp_index_offset
/*0   */ int ff_h264_decode_picture_parameter_set(GetBitContext *gb, AVCodecContext *avctx,                          // (3) 0.05859
/*1   */                                          H264ParamSets *ps, int bit_length)                                 // (0) 0.1035
/*2   */ {                                                                                                           // (23) 0.001953
/*3   */     AVBufferRef *pps_buf;                                                                                   // (17) 0.02148
/*4   */     const SPS *sps;                                                                                         // (18) 0.01953
/*5   */     unsigned int pps_id = get_ue_golomb(gb);                                                                // (8) 0.03906
/*6   */     PPS *pps;                                                                                               // (20) 0.01563
/*7   */     int qp_bd_offset;                                                                                       // (16) 0.02148
/*8   */     int bits_left;                                                                                          // (21) 0.01562
/*9   */     int ret;                                                                                                // (22) 0.01172
/*10  */     if (pps_id >= MAX_PPS_COUNT) {                                                                          // (11) 0.03516
/*11  */         av_log(avctx, AV_LOG_ERROR, "pps_id %u out of range\n", pps_id);                                    // (1) 0.07227
/*12  */         return AVERROR_INVALIDDATA;                                                                         // (13) 0.0332
/*13  */     pps_buf = av_buffer_allocz(sizeof(*pps));                                                               // (9) 0.03906
/*14  */     if (!pps_buf)                                                                                           // (19) 0.01758
/*15  */         return AVERROR(ENOMEM);                                                                             // (15) 0.03125
/*16  */     pps = (PPS*)pps_buf->data;                                                                              // (14) 0.03125
/*17  */     pps->data_size = gb->buffer_end - gb->buffer;                                                           // (7) 0.04297
/*18  */     if (pps->data_size > sizeof(pps->data)) {                                                               // (12) 0.03516
/*19  */         av_log(avctx, AV_LOG_WARNING, "Truncating likely oversized PPS "                                    // (4) 0.05664
/*20  */                "(%"SIZE_SPECIFIER" > %"SIZE_SPECIFIER")\n",                                                 // (2) 0.06641
/*21  */                pps->data_size, sizeof(pps->data));                                                          // (5) 0.05273
/*22  */         pps->data_size = sizeof(pps->data);                                                                 // (10) 0.03906
/*23  */     memcpy(pps->data, gb->buffer, pps->data_size);                                                          // (6) 0.04492
/*24  */     pps->sps_id = get_ue_golomb_31(gb);                                                                     // 0.0
/*25  */     if ((unsigned)pps->sps_id >= MAX_SPS_COUNT ||                                                           // 0.0
/*26  */         !ps->sps_list[pps->sps_id]) {                                                                       // 0.0
/*27  */         av_log(avctx, AV_LOG_ERROR, "sps_id %u out of range\n", pps->sps_id);                               // 0.0
/*28  */     sps = (const SPS*)ps->sps_list[pps->sps_id]->data;                                                      // 0.0
/*29  */     if (sps->bit_depth_luma > 14) {                                                                         // 0.0
/*30  */         av_log(avctx, AV_LOG_ERROR,                                                                         // 0.0
/*31  */                "Invalid luma bit depth=%d\n",                                                               // 0.0
/*32  */                sps->bit_depth_luma);                                                                        // 0.0
/*33  */     } else if (sps->bit_depth_luma == 11 || sps->bit_depth_luma == 13) {                                    // 0.0
/*34  */         av_log(avctx, AV_LOG_ERROR,                                                                         // 0.0
/*35  */                "Unimplemented luma bit depth=%d\n",                                                         // 0.0
/*36  */                sps->bit_depth_luma);                                                                        // 0.0
/*37  */         ret = AVERROR_PATCHWELCOME;                                                                         // 0.0
/*38  */     pps->cabac             = get_bits1(gb);                                                                 // 0.0
/*39  */     pps->pic_order_present = get_bits1(gb);                                                                 // 0.0
/*40  */     pps->slice_group_count = get_ue_golomb(gb) + 1;                                                         // 0.0
/*41  */     if (pps->slice_group_count > 1) {                                                                       // 0.0
/*42  */         pps->mb_slice_group_map_type = get_ue_golomb(gb);                                                   // 0.0
/*43  */         av_log(avctx, AV_LOG_ERROR, "FMO not supported\n");                                                 // 0.0
/*44  */         switch (pps->mb_slice_group_map_type) {                                                             // 0.0
/*45  */         case 0:                                                                                             // 0.0
/*46  */ #if 0                                                                                                       // 0.0
/*47  */     |       for (i = 0; i <= num_slice_groups_minus1; i++)  |   |      |                                    // 0.0
/*48  */     |           run_length[i]                               |1  |ue(v) |                                    // 0.0
/*49  */ #endif                                                                                                      // 0.0
/*50  */             break;                                                                                          // 0.0
/*51  */         case 2:                                                                                             // 0.0
/*52  */ #if 0                                                                                                       // 0.0
/*53  */     |       for (i = 0; i < num_slice_groups_minus1; i++) { |   |      |                                    // 0.0
/*54  */     |           top_left_mb[i]                              |1  |ue(v) |                                    // 0.0
/*55  */     |           bottom_right_mb[i]                          |1  |ue(v) |                                    // 0.0
/*56  */     |       }                                               |   |      |                                    // 0.0
/*57  */ #endif                                                                                                      // 0.0
/*58  */             break;                                                                                          // 0.0
/*59  */         case 3:                                                                                             // 0.0
/*60  */         case 4:                                                                                             // 0.0
/*61  */         case 5:                                                                                             // 0.0
/*62  */ #if 0                                                                                                       // 0.0
/*63  */     |       slice_group_change_direction_flag               |1  |u(1)  |                                    // 0.0
/*64  */     |       slice_group_change_rate_minus1                  |1  |ue(v) |                                    // 0.0
/*65  */ #endif                                                                                                      // 0.0
/*66  */             break;                                                                                          // 0.0
/*67  */         case 6:                                                                                             // 0.0
/*68  */ #if 0                                                                                                       // 0.0
/*69  */     |       slice_group_id_cnt_minus1                       |1  |ue(v) |                                    // 0.0
/*70  */     |       for (i = 0; i <= slice_group_id_cnt_minus1; i++)|   |      |                                    // 0.0
/*71  */     |           slice_group_id[i]                           |1  |u(v)  |                                    // 0.0
/*72  */ #endif                                                                                                      // 0.0
/*73  */             break;                                                                                          // 0.0
/*74  */     pps->ref_count[0] = get_ue_golomb(gb) + 1;                                                              // 0.0
/*75  */     pps->ref_count[1] = get_ue_golomb(gb) + 1;                                                              // 0.0
/*76  */     if (pps->ref_count[0] - 1 > 32 - 1 || pps->ref_count[1] - 1 > 32 - 1) {                                 // 0.0
/*77  */         av_log(avctx, AV_LOG_ERROR, "reference overflow (pps)\n");                                          // 0.0
/*78  */     qp_bd_offset = 6 * (sps->bit_depth_luma - 8);                                                           // 0.0
/*79  */     pps->weighted_pred                        = get_bits1(gb);                                              // 0.0
/*80  */     pps->weighted_bipred_idc                  = get_bits(gb, 2);                                            // 0.0
/*81  */     pps->init_qp                              = get_se_golomb(gb) + 26 + qp_bd_offset;                      // 0.0
/*82  */     pps->init_qs                              = get_se_golomb(gb) + 26 + qp_bd_offset;                      // 0.0
/*83  */     pps->chroma_qp_index_offset[0]            = get_se_golomb(gb);                                          // 0.0
/*84  */     pps->deblocking_filter_parameters_present = get_bits1(gb);                                              // 0.0
/*85  */     pps->constrained_intra_pred               = get_bits1(gb);                                              // 0.0
/*86  */     pps->redundant_pic_cnt_present            = get_bits1(gb);                                              // 0.0
/*87  */     pps->transform_8x8_mode = 0;                                                                            // 0.0
/*88  */     memcpy(pps->scaling_matrix4, sps->scaling_matrix4,                                                      // 0.0
/*89  */            sizeof(pps->scaling_matrix4));                                                                   // 0.0
/*90  */     memcpy(pps->scaling_matrix8, sps->scaling_matrix8,                                                      // 0.0
/*91  */            sizeof(pps->scaling_matrix8));                                                                   // 0.0
/*92  */     bits_left = bit_length - get_bits_count(gb);                                                            // 0.0
/*93  */     if (bits_left > 0 && more_rbsp_data_in_pps(sps, avctx)) {                                               // 0.0
/*94  */         pps->transform_8x8_mode = get_bits1(gb);                                                            // 0.0
/*95  */         decode_scaling_matrices(gb, sps, pps, 0,                                                            // 0.0
/*96  */                                 pps->scaling_matrix4, pps->scaling_matrix8);                                // 0.0
/*97  */         // second_chroma_qp_index_offset                                                                    // 0.0
/*98  */         pps->chroma_qp_index_offset[1] = get_se_golomb(gb);                                                 // 0.0
/*99  */         if (pps->chroma_qp_index_offset[1] < -12 || pps->chroma_qp_index_offset[1] > 12) {                  // 0.0
/*100 */     } else {                                                                                                // 0.0
/*101 */         pps->chroma_qp_index_offset[1] = pps->chroma_qp_index_offset[0];                                    // 0.0
/*102 */     build_qp_table(pps, 0, pps->chroma_qp_index_offset[0],                                                  // 0.0
/*103 */                    sps->bit_depth_luma);                                                                    // 0.0
/*104 */     build_qp_table(pps, 1, pps->chroma_qp_index_offset[1],                                                  // 0.0
/*105 */                    sps->bit_depth_luma);                                                                    // 0.0
/*106 */     init_dequant_tables(pps, sps);                                                                          // 0.0
/*107 */     if (pps->chroma_qp_index_offset[0] != pps->chroma_qp_index_offset[1])                                   // 0.0
/*108 */         pps->chroma_qp_diff = 1;                                                                            // 0.0
/*109 */     if (avctx->debug & FF_DEBUG_PICT_INFO) {                                                                // 0.0
/*110 */         av_log(avctx, AV_LOG_DEBUG,                                                                         // 0.0
/*111 */                "pps:%u sps:%u %s slice_groups:%d ref:%u/%u %s qp:%d/%d/%d/%d %s %s %s %s\n",                // 0.0
/*112 */                pps_id, pps->sps_id,                                                                         // 0.0
/*113 */                pps->cabac ? "CABAC" : "CAVLC",                                                              // 0.0
/*114 */                pps->slice_group_count,                                                                      // 0.0
/*115 */                pps->ref_count[0], pps->ref_count[1],                                                        // 0.0
/*116 */                pps->weighted_pred ? "weighted" : "",                                                        // 0.0
/*117 */                pps->init_qp, pps->init_qs, pps->chroma_qp_index_offset[0], pps->chroma_qp_index_offset[1],  // 0.0
/*118 */                pps->deblocking_filter_parameters_present ? "LPAR" : "",                                     // 0.0
/*119 */                pps->constrained_intra_pred ? "CONSTR" : "",                                                 // 0.0
/*120 */                pps->redundant_pic_cnt_present ? "REDU" : "",                                                // 0.0
/*121 */                pps->transform_8x8_mode ? "8x8DCT" : "");                                                    // 0.0
/*122 */     remove_pps(ps, pps_id);                                                                                 // 0.0
/*123 */     ps->pps_list[pps_id] = pps_buf;                                                                         // 0.0
/*124 */     return 0;                                                                                               // 0.0
/*125 */ fail:                                                                                                       // 0.0
/*126 */     av_buffer_unref(&pps_buf);                                                                              // 0.0
/*127 */     return ret;                                                                                             // 0.0
