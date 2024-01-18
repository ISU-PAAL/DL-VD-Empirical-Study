// commit message FFmpeg@4cec43a9ee (target=0, prob=0.47454342, correct=True): h264: move calculating the POC out of h264_slice_header_parse()
/*0    */ static int h264_slice_header_parse(H264Context *h, H264SliceContext *sl)                                             // (5) 0.04885
/*2    */ {                                                                                                                    // (26) 0.001954
/*4    */     const SPS *sps;                                                                                                  // (19) 0.01953
/*6    */     const PPS *pps;                                                                                                  // (21) 0.01758
/*8    */     unsigned int first_mb_in_slice;                                                                                  // (15) 0.02539
/*10   */     unsigned int pps_id;                                                                                             // (20) 0.01953
/*12   */     int ret;                                                                                                         // (24) 0.01172
/*14   */     unsigned int slice_type, tmp, i;                                                                                 // (14) 0.0254
/*16   */     int last_pic_structure, last_pic_droppable;                                                                      // (9) 0.03711
/*18   */     int needs_reinit = 0;                                                                                            // (18) 0.02148
/*20   */     int field_pic_flag, bottom_field_flag;                                                                           // (11) 0.03125
/*22   */     int frame_num, droppable, picture_structure;                                                                     // (10) 0.0332
/*24   */     int mb_aff_frame = 0;                                                                                            // (16) 0.02539
/*28   */     first_mb_in_slice = get_ue_golomb(&sl->gb);                                                                      // (6) 0.04492
/*32   */     if (first_mb_in_slice == 0) { // FIXME better field boundary detection                                           // (7) 0.04492
/*34   */         if (h->current_slice && h->cur_pic_ptr && FIELD_PICTURE(h)) {                                                // (2) 0.06445
/*36   */             ff_h264_field_end(h, sl, 1);                                                                             // (4) 0.05078
/*38   */         }                                                                                                            // (22) 0.01562
/*42   */         h->current_slice = 0;                                                                                        // (13) 0.02929
/*44   */         if (!h->first_field) {                                                                                       // (12) 0.03125
/*46   */             if (h->cur_pic_ptr && !h->droppable) {                                                                   // (3) 0.05664
/*48   */                 ff_thread_report_progress(&h->cur_pic_ptr->tf, INT_MAX,                                              // (1) 0.07226
/*50   */                                           h->picture_structure == PICT_BOTTOM_FIELD);                                // (0) 0.1113
/*52   */             }                                                                                                        // (17) 0.02344
/*54   */             h->cur_pic_ptr = NULL;                                                                                   // (8) 0.04101
/*56   */         }                                                                                                            // (23) 0.01562
/*58   */     }                                                                                                                // (25) 0.007812
/*62   */     slice_type = get_ue_golomb_31(&sl->gb);                                                                          // 0.0
/*64   */     if (slice_type > 9) {                                                                                            // 0.0
/*66   */         av_log(h->avctx, AV_LOG_ERROR,                                                                               // 0.0
/*68   */                "slice type %d too large at %d\n",                                                                    // 0.0
/*70   */                slice_type, first_mb_in_slice);                                                                       // 0.0
/*72   */         return AVERROR_INVALIDDATA;                                                                                  // 0.0
/*74   */     }                                                                                                                // 0.0
/*76   */     if (slice_type > 4) {                                                                                            // 0.0
/*78   */         slice_type -= 5;                                                                                             // 0.0
/*80   */         sl->slice_type_fixed = 1;                                                                                    // 0.0
/*82   */     } else                                                                                                           // 0.0
/*84   */         sl->slice_type_fixed = 0;                                                                                    // 0.0
/*88   */     slice_type         = ff_h264_golomb_to_pict_type[slice_type];                                                    // 0.0
/*90   */     sl->slice_type     = slice_type;                                                                                 // 0.0
/*92   */     sl->slice_type_nos = slice_type & 3;                                                                             // 0.0
/*96   */     if (h->nal_unit_type  == NAL_IDR_SLICE &&                                                                        // 0.0
/*98   */         sl->slice_type_nos != AV_PICTURE_TYPE_I) {                                                                   // 0.0
/*100  */         av_log(h->avctx, AV_LOG_ERROR, "A non-intra slice in an IDR NAL unit.\n");                                   // 0.0
/*102  */         return AVERROR_INVALIDDATA;                                                                                  // 0.0
/*104  */     }                                                                                                                // 0.0
/*108  */     pps_id = get_ue_golomb(&sl->gb);                                                                                 // 0.0
/*110  */     if (pps_id >= MAX_PPS_COUNT) {                                                                                   // 0.0
/*112  */         av_log(h->avctx, AV_LOG_ERROR, "pps_id %u out of range\n", pps_id);                                          // 0.0
/*114  */         return AVERROR_INVALIDDATA;                                                                                  // 0.0
/*116  */     }                                                                                                                // 0.0
/*118  */     if (!h->ps.pps_list[pps_id]) {                                                                                   // 0.0
/*120  */         av_log(h->avctx, AV_LOG_ERROR,                                                                               // 0.0
/*122  */                "non-existing PPS %u referenced\n",                                                                   // 0.0
/*124  */                pps_id);                                                                                              // 0.0
/*126  */         return AVERROR_INVALIDDATA;                                                                                  // 0.0
/*128  */     }                                                                                                                // 0.0
/*130  */     if (!h->setup_finished) {                                                                                        // 0.0
/*132  */         h->ps.pps = (const PPS*)h->ps.pps_list[pps_id]->data;                                                        // 0.0
/*134  */     } else if (h->ps.pps != (const PPS*)h->ps.pps_list[pps_id]->data) {                                              // 0.0
/*136  */         av_log(h->avctx, AV_LOG_ERROR, "PPS changed between slices\n");                                              // 0.0
/*138  */         return AVERROR_INVALIDDATA;                                                                                  // 0.0
/*140  */     }                                                                                                                // 0.0
/*144  */     if (!h->ps.sps_list[h->ps.pps->sps_id]) {                                                                        // 0.0
/*146  */         av_log(h->avctx, AV_LOG_ERROR,                                                                               // 0.0
/*148  */                "non-existing SPS %u referenced\n",                                                                   // 0.0
/*150  */                h->ps.pps->sps_id);                                                                                   // 0.0
/*152  */         return AVERROR_INVALIDDATA;                                                                                  // 0.0
/*154  */     }                                                                                                                // 0.0
/*158  */     if (h->ps.sps != (const SPS*)h->ps.sps_list[h->ps.pps->sps_id]->data) {                                          // 0.0
/*160  */         h->ps.sps = (SPS*)h->ps.sps_list[h->ps.pps->sps_id]->data;                                                   // 0.0
/*164  */         if (h->bit_depth_luma    != h->ps.sps->bit_depth_luma ||                                                     // 0.0
/*166  */             h->chroma_format_idc != h->ps.sps->chroma_format_idc)                                                    // 0.0
/*168  */             needs_reinit         = 1;                                                                                // 0.0
/*170  */     }                                                                                                                // 0.0
/*174  */     pps = h->ps.pps;                                                                                                 // 0.0
/*176  */     sps = h->ps.sps;                                                                                                 // 0.0
/*180  */     if (!h->setup_finished) {                                                                                        // 0.0
/*182  */         h->avctx->profile = ff_h264_get_profile(sps);                                                                // 0.0
/*184  */         h->avctx->level   = sps->level_idc;                                                                          // 0.0
/*186  */         h->avctx->refs    = sps->ref_frame_count;                                                                    // 0.0
/*190  */         if (h->mb_width  != sps->mb_width ||                                                                         // 0.0
/*192  */             h->mb_height != sps->mb_height * (2 - sps->frame_mbs_only_flag))                                         // 0.0
/*194  */             needs_reinit = 1;                                                                                        // 0.0
/*198  */         h->mb_width  = sps->mb_width;                                                                                // 0.0
/*200  */         h->mb_height = sps->mb_height * (2 - sps->frame_mbs_only_flag);                                              // 0.0
/*202  */         h->mb_num    = h->mb_width * h->mb_height;                                                                   // 0.0
/*204  */         h->mb_stride = h->mb_width + 1;                                                                              // 0.0
/*208  */         h->b_stride = h->mb_width * 4;                                                                               // 0.0
/*212  */         h->chroma_y_shift = sps->chroma_format_idc <= 1; // 400 uses yuv420p                                         // 0.0
/*216  */         h->width  = 16 * h->mb_width;                                                                                // 0.0
/*218  */         h->height = 16 * h->mb_height;                                                                               // 0.0
/*222  */         ret = init_dimensions(h);                                                                                    // 0.0
/*224  */         if (ret < 0)                                                                                                 // 0.0
/*226  */             return ret;                                                                                              // 0.0
/*230  */         if (sps->video_signal_type_present_flag) {                                                                   // 0.0
/*232  */             h->avctx->color_range = sps->full_range ? AVCOL_RANGE_JPEG                                               // 0.0
/*234  */                 : AVCOL_RANGE_MPEG;                                                                                  // 0.0
/*236  */             if (sps->colour_description_present_flag) {                                                              // 0.0
/*238  */                 if (h->avctx->colorspace != sps->colorspace)                                                         // 0.0
/*240  */                     needs_reinit = 1;                                                                                // 0.0
/*242  */                 h->avctx->color_primaries = sps->color_primaries;                                                    // 0.0
/*244  */                 h->avctx->color_trc       = sps->color_trc;                                                          // 0.0
/*246  */                 h->avctx->colorspace      = sps->colorspace;                                                         // 0.0
/*248  */             }                                                                                                        // 0.0
/*250  */         }                                                                                                            // 0.0
/*252  */     }                                                                                                                // 0.0
/*256  */     if (h->context_initialized && needs_reinit) {                                                                    // 0.0
/*258  */         h->context_initialized = 0;                                                                                  // 0.0
/*260  */         if (sl != h->slice_ctx) {                                                                                    // 0.0
/*262  */             av_log(h->avctx, AV_LOG_ERROR,                                                                           // 0.0
/*264  */                    "changing width %d -> %d / height %d -> %d on "                                                   // 0.0
/*266  */                    "slice %d\n",                                                                                     // 0.0
/*268  */                    h->width, h->avctx->coded_width,                                                                  // 0.0
/*270  */                    h->height, h->avctx->coded_height,                                                                // 0.0
/*272  */                    h->current_slice + 1);                                                                            // 0.0
/*274  */             return AVERROR_INVALIDDATA;                                                                              // 0.0
/*276  */         }                                                                                                            // 0.0
/*280  */         ff_h264_flush_change(h);                                                                                     // 0.0
/*284  */         if ((ret = get_pixel_format(h)) < 0)                                                                         // 0.0
/*286  */             return ret;                                                                                              // 0.0
/*288  */         h->avctx->pix_fmt = ret;                                                                                     // 0.0
/*292  */         av_log(h->avctx, AV_LOG_INFO, "Reinit context to %dx%d, "                                                    // 0.0
/*294  */                "pix_fmt: %d\n", h->width, h->height, h->avctx->pix_fmt);                                             // 0.0
/*298  */         if ((ret = h264_slice_header_init(h)) < 0) {                                                                 // 0.0
/*300  */             av_log(h->avctx, AV_LOG_ERROR,                                                                           // 0.0
/*302  */                    "h264_slice_header_init() failed\n");                                                             // 0.0
/*304  */             return ret;                                                                                              // 0.0
/*306  */         }                                                                                                            // 0.0
/*308  */     }                                                                                                                // 0.0
/*310  */     if (!h->context_initialized) {                                                                                   // 0.0
/*312  */         if (sl != h->slice_ctx) {                                                                                    // 0.0
/*314  */             av_log(h->avctx, AV_LOG_ERROR,                                                                           // 0.0
/*316  */                    "Cannot (re-)initialize context during parallel decoding.\n");                                    // 0.0
/*318  */             return AVERROR_PATCHWELCOME;                                                                             // 0.0
/*320  */         }                                                                                                            // 0.0
/*324  */         if ((ret = get_pixel_format(h)) < 0)                                                                         // 0.0
/*326  */             return ret;                                                                                              // 0.0
/*328  */         h->avctx->pix_fmt = ret;                                                                                     // 0.0
/*332  */         if ((ret = h264_slice_header_init(h)) < 0) {                                                                 // 0.0
/*334  */             av_log(h->avctx, AV_LOG_ERROR,                                                                           // 0.0
/*336  */                    "h264_slice_header_init() failed\n");                                                             // 0.0
/*338  */             return ret;                                                                                              // 0.0
/*340  */         }                                                                                                            // 0.0
/*342  */     }                                                                                                                // 0.0
/*346  */     frame_num = get_bits(&sl->gb, sps->log2_max_frame_num);                                                          // 0.0
/*348  */     if (!h->setup_finished)                                                                                          // 0.0
/*350  */         h->poc.frame_num = frame_num;                                                                                // 0.0
/*354  */     sl->mb_mbaff       = 0;                                                                                          // 0.0
/*358  */     last_pic_structure = h->picture_structure;                                                                       // 0.0
/*360  */     last_pic_droppable = h->droppable;                                                                               // 0.0
/*364  */     droppable = h->nal_ref_idc == 0;                                                                                 // 0.0
/*366  */     if (sps->frame_mbs_only_flag) {                                                                                  // 0.0
/*368  */         picture_structure = PICT_FRAME;                                                                              // 0.0
/*370  */     } else {                                                                                                         // 0.0
/*372  */         field_pic_flag = get_bits1(&sl->gb);                                                                         // 0.0
/*374  */         if (field_pic_flag) {                                                                                        // 0.0
/*376  */             bottom_field_flag = get_bits1(&sl->gb);                                                                  // 0.0
/*378  */             picture_structure = PICT_TOP_FIELD + bottom_field_flag;                                                  // 0.0
/*380  */         } else {                                                                                                     // 0.0
/*382  */             picture_structure = PICT_FRAME;                                                                          // 0.0
/*384  */             mb_aff_frame      = sps->mb_aff;                                                                         // 0.0
/*386  */         }                                                                                                            // 0.0
/*388  */     }                                                                                                                // 0.0
/*390  */     if (!h->setup_finished) {                                                                                        // 0.0
/*392  */         h->droppable         = droppable;                                                                            // 0.0
/*394  */         h->picture_structure = picture_structure;                                                                    // 0.0
/*396  */         h->mb_aff_frame      = mb_aff_frame;                                                                         // 0.0
/*398  */     }                                                                                                                // 0.0
/*400  */     sl->mb_field_decoding_flag = h->picture_structure != PICT_FRAME;                                                 // 0.0
/*404  */     if (h->current_slice != 0) {                                                                                     // 0.0
/*406  */         if (last_pic_structure != picture_structure ||                                                               // 0.0
/*408  */             last_pic_droppable != droppable) {                                                                       // 0.0
/*410  */             av_log(h->avctx, AV_LOG_ERROR,                                                                           // 0.0
/*412  */                    "Changing field mode (%d -> %d) between slices is not allowed\n",                                 // 0.0
/*414  */                    last_pic_structure, h->picture_structure);                                                        // 0.0
/*416  */             return AVERROR_INVALIDDATA;                                                                              // 0.0
/*418  */         } else if (!h->cur_pic_ptr) {                                                                                // 0.0
/*420  */             av_log(h->avctx, AV_LOG_ERROR,                                                                           // 0.0
/*422  */                    "unset cur_pic_ptr on slice %d\n",                                                                // 0.0
/*424  */                    h->current_slice + 1);                                                                            // 0.0
/*426  */             return AVERROR_INVALIDDATA;                                                                              // 0.0
/*428  */         }                                                                                                            // 0.0
/*430  */     } else {                                                                                                         // 0.0
/*432  */         /* Shorten frame num gaps so we don't have to allocate reference                                             // 0.0
/*434  */          * frames just to throw them away */                                                                         // 0.0
/*436  */         if (h->poc.frame_num != h->poc.prev_frame_num) {                                                             // 0.0
/*438  */             int unwrap_prev_frame_num = h->poc.prev_frame_num;                                                       // 0.0
/*440  */             int max_frame_num         = 1 << sps->log2_max_frame_num;                                                // 0.0
/*444  */             if (unwrap_prev_frame_num > h->poc.frame_num)                                                            // 0.0
/*446  */                 unwrap_prev_frame_num -= max_frame_num;                                                              // 0.0
/*450  */             if ((h->poc.frame_num - unwrap_prev_frame_num) > sps->ref_frame_count) {                                 // 0.0
/*452  */                 unwrap_prev_frame_num = (h->poc.frame_num - sps->ref_frame_count) - 1;                               // 0.0
/*454  */                 if (unwrap_prev_frame_num < 0)                                                                       // 0.0
/*456  */                     unwrap_prev_frame_num += max_frame_num;                                                          // 0.0
/*460  */                 h->poc.prev_frame_num = unwrap_prev_frame_num;                                                       // 0.0
/*462  */             }                                                                                                        // 0.0
/*464  */         }                                                                                                            // 0.0
/*468  */         /* See if we have a decoded first field looking for a pair...                                                // 0.0
/*470  */          * Here, we're using that to see if we should mark previously                                                // 0.0
/*472  */          * decode frames as "finished".                                                                              // 0.0
/*474  */          * We have to do that before the "dummy" in-between frame allocation,                                        // 0.0
/*476  */          * since that can modify s->current_picture_ptr. */                                                          // 0.0
/*478  */         if (h->first_field) {                                                                                        // 0.0
/*480  */             assert(h->cur_pic_ptr);                                                                                  // 0.0
/*482  */             assert(h->cur_pic_ptr->f->buf[0]);                                                                       // 0.0
/*484  */             assert(h->cur_pic_ptr->reference != DELAYED_PIC_REF);                                                    // 0.0
/*488  */             /* figure out if we have a complementary field pair */                                                   // 0.0
/*490  */             if (!FIELD_PICTURE(h) || h->picture_structure == last_pic_structure) {                                   // 0.0
/*492  */                 /* Previous field is unmatched. Don't display it, but let it                                         // 0.0
/*494  */                  * remain for reference if marked as such. */                                                        // 0.0
/*496  */                 if (!last_pic_droppable && last_pic_structure != PICT_FRAME) {                                       // 0.0
/*498  */                     ff_thread_report_progress(&h->cur_pic_ptr->tf, INT_MAX,                                          // 0.0
/*500  */                                               last_pic_structure == PICT_TOP_FIELD);                                 // 0.0
/*502  */                 }                                                                                                    // 0.0
/*504  */             } else {                                                                                                 // 0.0
/*506  */                 if (h->cur_pic_ptr->frame_num != h->poc.frame_num) {                                                 // 0.0
/*508  */                     /* This and previous field were reference, but had                                               // 0.0
/*510  */                      * different frame_nums. Consider this field first in                                            // 0.0
/*512  */                      * pair. Throw away previous field except for reference                                          // 0.0
/*514  */                      * purposes. */                                                                                  // 0.0
/*516  */                     if (!last_pic_droppable && last_pic_structure != PICT_FRAME) {                                   // 0.0
/*518  */                         ff_thread_report_progress(&h->cur_pic_ptr->tf, INT_MAX,                                      // 0.0
/*520  */                                                   last_pic_structure == PICT_TOP_FIELD);                             // 0.0
/*522  */                     }                                                                                                // 0.0
/*524  */                 } else {                                                                                             // 0.0
/*526  */                     /* Second field in complementary pair */                                                         // 0.0
/*528  */                     if (!((last_pic_structure   == PICT_TOP_FIELD &&                                                 // 0.0
/*530  */                            h->picture_structure == PICT_BOTTOM_FIELD) ||                                             // 0.0
/*532  */                           (last_pic_structure   == PICT_BOTTOM_FIELD &&                                              // 0.0
/*534  */                            h->picture_structure == PICT_TOP_FIELD))) {                                               // 0.0
/*536  */                         av_log(h->avctx, AV_LOG_ERROR,                                                               // 0.0
/*538  */                                "Invalid field mode combination %d/%d\n",                                             // 0.0
/*540  */                                last_pic_structure, h->picture_structure);                                            // 0.0
/*542  */                         h->picture_structure = last_pic_structure;                                                   // 0.0
/*544  */                         h->droppable         = last_pic_droppable;                                                   // 0.0
/*546  */                         return AVERROR_INVALIDDATA;                                                                  // 0.0
/*548  */                     } else if (last_pic_droppable != h->droppable) {                                                 // 0.0
/*550  */                         avpriv_request_sample(h->avctx,                                                              // 0.0
/*552  */                                               "Found reference and non-reference fields in the same frame, which");  // 0.0
/*554  */                         h->picture_structure = last_pic_structure;                                                   // 0.0
/*556  */                         h->droppable         = last_pic_droppable;                                                   // 0.0
/*558  */                         return AVERROR_PATCHWELCOME;                                                                 // 0.0
/*560  */                     }                                                                                                // 0.0
/*562  */                 }                                                                                                    // 0.0
/*564  */             }                                                                                                        // 0.0
/*566  */         }                                                                                                            // 0.0
/*570  */         while (h->poc.frame_num != h->poc.prev_frame_num &&                                                          // 0.0
/*572  */                h->poc.frame_num != (h->poc.prev_frame_num + 1) % (1 << sps->log2_max_frame_num)) {                   // 0.0
/*574  */             H264Picture *prev = h->short_ref_count ? h->short_ref[0] : NULL;                                         // 0.0
/*576  */             av_log(h->avctx, AV_LOG_DEBUG, "Frame num gap %d %d\n",                                                  // 0.0
/*578  */                    h->poc.frame_num, h->poc.prev_frame_num);                                                         // 0.0
/*580  */             ret = initialize_cur_frame(h);                                                                           // 0.0
/*582  */             if (ret < 0) {                                                                                           // 0.0
/*584  */                 h->first_field = 0;                                                                                  // 0.0
/*586  */                 return ret;                                                                                          // 0.0
/*588  */             }                                                                                                        // 0.0
/*592  */             h->poc.prev_frame_num++;                                                                                 // 0.0
/*594  */             h->poc.prev_frame_num        %= 1 << sps->log2_max_frame_num;                                            // 0.0
/*596  */             h->cur_pic_ptr->frame_num = h->poc.prev_frame_num;                                                       // 0.0
/*598  */             ff_thread_report_progress(&h->cur_pic_ptr->tf, INT_MAX, 0);                                              // 0.0
/*600  */             ff_thread_report_progress(&h->cur_pic_ptr->tf, INT_MAX, 1);                                              // 0.0
/*602  */             ret = ff_generate_sliding_window_mmcos(h, 1);                                                            // 0.0
/*604  */             if (ret < 0 && (h->avctx->err_recognition & AV_EF_EXPLODE))                                              // 0.0
/*606  */                 return ret;                                                                                          // 0.0
/*608  */             ret = ff_h264_execute_ref_pic_marking(h, h->mmco, h->mmco_index);                                        // 0.0
/*610  */             if (ret < 0 && (h->avctx->err_recognition & AV_EF_EXPLODE))                                              // 0.0
/*612  */                 return ret;                                                                                          // 0.0
/*614  */             /* Error concealment: If a ref is missing, copy the previous ref                                         // 0.0
/*616  */              * in its place.                                                                                         // 0.0
/*618  */              * FIXME: Avoiding a memcpy would be nice, but ref handling makes                                        // 0.0
/*620  */              * many assumptions about there being no actual duplicates.                                              // 0.0
/*622  */              * FIXME: This does not copy padding for out-of-frame motion                                             // 0.0
/*624  */              * vectors.  Given we are concealing a lost frame, this probably                                         // 0.0
/*626  */              * is not noticeable by comparison, but it should be fixed. */                                           // 0.0
/*628  */             if (h->short_ref_count) {                                                                                // 0.0
/*630  */                 if (prev &&                                                                                          // 0.0
/*632  */                     h->short_ref[0]->f->width == prev->f->width &&                                                   // 0.0
/*634  */                     h->short_ref[0]->f->height == prev->f->height &&                                                 // 0.0
/*636  */                     h->short_ref[0]->f->format == prev->f->format) {                                                 // 0.0
/*638  */                     av_image_copy(h->short_ref[0]->f->data,                                                          // 0.0
/*640  */                                   h->short_ref[0]->f->linesize,                                                      // 0.0
/*642  */                                   (const uint8_t **)prev->f->data,                                                   // 0.0
/*644  */                                   prev->f->linesize,                                                                 // 0.0
/*646  */                                   prev->f->format,                                                                   // 0.0
/*648  */                                   h->mb_width  * 16,                                                                 // 0.0
/*650  */                                   h->mb_height * 16);                                                                // 0.0
/*652  */                     h->short_ref[0]->poc = prev->poc + 2;                                                            // 0.0
/*654  */                 }                                                                                                    // 0.0
/*656  */                 h->short_ref[0]->frame_num = h->poc.prev_frame_num;                                                  // 0.0
/*658  */             }                                                                                                        // 0.0
/*660  */         }                                                                                                            // 0.0
/*664  */         /* See if we have a decoded first field looking for a pair...                                                // 0.0
/*666  */          * We're using that to see whether to continue decoding in that                                              // 0.0
/*668  */          * frame, or to allocate a new one. */                                                                       // 0.0
/*670  */         if (h->first_field) {                                                                                        // 0.0
/*672  */             assert(h->cur_pic_ptr);                                                                                  // 0.0
/*674  */             assert(h->cur_pic_ptr->f->buf[0]);                                                                       // 0.0
/*676  */             assert(h->cur_pic_ptr->reference != DELAYED_PIC_REF);                                                    // 0.0
/*680  */             /* figure out if we have a complementary field pair */                                                   // 0.0
/*682  */             if (!FIELD_PICTURE(h) || h->picture_structure == last_pic_structure) {                                   // 0.0
/*684  */                 /* Previous field is unmatched. Don't display it, but let it                                         // 0.0
/*686  */                  * remain for reference if marked as such. */                                                        // 0.0
/*688  */                 h->cur_pic_ptr = NULL;                                                                               // 0.0
/*690  */                 h->first_field = FIELD_PICTURE(h);                                                                   // 0.0
/*692  */             } else {                                                                                                 // 0.0
/*694  */                 if (h->cur_pic_ptr->frame_num != h->poc.frame_num) {                                                 // 0.0
/*696  */                     /* This and the previous field had different frame_nums.                                         // 0.0
/*698  */                      * Consider this field first in pair. Throw away previous                                        // 0.0
/*700  */                      * one except for reference purposes. */                                                         // 0.0
/*702  */                     h->first_field = 1;                                                                              // 0.0
/*704  */                     h->cur_pic_ptr = NULL;                                                                           // 0.0
/*706  */                 } else {                                                                                             // 0.0
/*708  */                     /* Second field in complementary pair */                                                         // 0.0
/*710  */                     h->first_field = 0;                                                                              // 0.0
/*712  */                 }                                                                                                    // 0.0
/*714  */             }                                                                                                        // 0.0
/*716  */         } else {                                                                                                     // 0.0
/*718  */             /* Frame or first field in a potentially complementary pair */                                           // 0.0
/*720  */             h->first_field = FIELD_PICTURE(h);                                                                       // 0.0
/*722  */         }                                                                                                            // 0.0
/*726  */         if (!FIELD_PICTURE(h) || h->first_field) {                                                                   // 0.0
/*728  */             if (h264_frame_start(h) < 0) {                                                                           // 0.0
/*730  */                 h->first_field = 0;                                                                                  // 0.0
/*732  */                 return AVERROR_INVALIDDATA;                                                                          // 0.0
/*734  */             }                                                                                                        // 0.0
/*736  */         } else {                                                                                                     // 0.0
/*738  */             release_unused_pictures(h, 0);                                                                           // 0.0
/*740  */         }                                                                                                            // 0.0
/*742  */     }                                                                                                                // 0.0
/*746  */     assert(h->mb_num == h->mb_width * h->mb_height);                                                                 // 0.0
/*748  */     if (first_mb_in_slice << FIELD_OR_MBAFF_PICTURE(h) >= h->mb_num ||                                               // 0.0
/*750  */         first_mb_in_slice >= h->mb_num) {                                                                            // 0.0
/*752  */         av_log(h->avctx, AV_LOG_ERROR, "first_mb_in_slice overflow\n");                                              // 0.0
/*754  */         return AVERROR_INVALIDDATA;                                                                                  // 0.0
/*756  */     }                                                                                                                // 0.0
/*758  */     sl->resync_mb_x = sl->mb_x =  first_mb_in_slice % h->mb_width;                                                   // 0.0
/*760  */     sl->resync_mb_y = sl->mb_y = (first_mb_in_slice / h->mb_width) <<                                                // 0.0
/*762  */                                  FIELD_OR_MBAFF_PICTURE(h);                                                          // 0.0
/*764  */     if (h->picture_structure == PICT_BOTTOM_FIELD)                                                                   // 0.0
/*766  */         sl->resync_mb_y = sl->mb_y = sl->mb_y + 1;                                                                   // 0.0
/*768  */     assert(sl->mb_y < h->mb_height);                                                                                 // 0.0
/*772  */     if (h->picture_structure == PICT_FRAME) {                                                                        // 0.0
/*774  */         h->curr_pic_num = h->poc.frame_num;                                                                          // 0.0
/*776  */         h->max_pic_num  = 1 << sps->log2_max_frame_num;                                                              // 0.0
/*778  */     } else {                                                                                                         // 0.0
/*780  */         h->curr_pic_num = 2 * h->poc.frame_num + 1;                                                                  // 0.0
/*782  */         h->max_pic_num  = 1 << (sps->log2_max_frame_num + 1);                                                        // 0.0
/*784  */     }                                                                                                                // 0.0
/*788  */     if (h->nal_unit_type == NAL_IDR_SLICE)                                                                           // 0.0
/*790  */         get_ue_golomb(&sl->gb); /* idr_pic_id */                                                                     // 0.0
/*794  */     if (sps->poc_type == 0) {                                                                                        // 0.0
/*796  */         int poc_lsb = get_bits(&sl->gb, sps->log2_max_poc_lsb);                                                      // 0.0
/*800  */         if (!h->setup_finished)                                                                                      // 0.0
/*802  */             h->poc.poc_lsb = poc_lsb;                                                                                // 0.0
/*806  */         if (pps->pic_order_present == 1 && h->picture_structure == PICT_FRAME) {                                     // 0.0
/*808  */             int delta_poc_bottom = get_se_golomb(&sl->gb);                                                           // 0.0
/*810  */             if (!h->setup_finished)                                                                                  // 0.0
/*812  */                 h->poc.delta_poc_bottom = delta_poc_bottom;                                                          // 0.0
/*814  */         }                                                                                                            // 0.0
/*816  */     }                                                                                                                // 0.0
/*820  */     if (sps->poc_type == 1 && !sps->delta_pic_order_always_zero_flag) {                                              // 0.0
/*822  */         int delta_poc = get_se_golomb(&sl->gb);                                                                      // 0.0
/*826  */         if (!h->setup_finished)                                                                                      // 0.0
/*828  */             h->poc.delta_poc[0] = delta_poc;                                                                         // 0.0
/*832  */         if (pps->pic_order_present == 1 && h->picture_structure == PICT_FRAME) {                                     // 0.0
/*834  */             delta_poc = get_se_golomb(&sl->gb);                                                                      // 0.0
/*838  */             if (!h->setup_finished)                                                                                  // 0.0
/*840  */                 h->poc.delta_poc[1] = delta_poc;                                                                     // 0.0
/*842  */         }                                                                                                            // 0.0
/*844  */     }                                                                                                                // 0.0
/*848  */     if (!h->setup_finished)                                                                                          // 0.0
/*850  */         ff_h264_init_poc(h->cur_pic_ptr->field_poc, &h->cur_pic_ptr->poc,                                            // 0.0
/*852  */                          sps, &h->poc, h->picture_structure, h->nal_ref_idc);                                        // 0.0
/*856  */     if (pps->redundant_pic_cnt_present)                                                                              // 0.0
/*858  */         sl->redundant_pic_count = get_ue_golomb(&sl->gb);                                                            // 0.0
/*862  */     if (sl->slice_type_nos == AV_PICTURE_TYPE_B)                                                                     // 0.0
/*864  */         sl->direct_spatial_mv_pred = get_bits1(&sl->gb);                                                             // 0.0
/*868  */     ret = ff_h264_parse_ref_count(&sl->list_count, sl->ref_count,                                                    // 0.0
/*870  */                                   &sl->gb, pps, sl->slice_type_nos,                                                  // 0.0
/*872  */                                   h->picture_structure);                                                             // 0.0
/*874  */     if (ret < 0)                                                                                                     // 0.0
/*876  */         return ret;                                                                                                  // 0.0
/*880  */     if (sl->slice_type_nos != AV_PICTURE_TYPE_I) {                                                                   // 0.0
/*882  */        ret = ff_h264_decode_ref_pic_list_reordering(h, sl);                                                          // 0.0
/*884  */        if (ret < 0) {                                                                                                // 0.0
/*886  */            sl->ref_count[1] = sl->ref_count[0] = 0;                                                                  // 0.0
/*888  */            return ret;                                                                                               // 0.0
/*890  */        }                                                                                                             // 0.0
/*892  */     }                                                                                                                // 0.0
/*896  */     sl->pwt.use_weight = 0;                                                                                          // 0.0
/*898  */     for (i = 0; i < 2; i++) {                                                                                        // 0.0
/*900  */         sl->pwt.luma_weight_flag[i]   = 0;                                                                           // 0.0
/*902  */         sl->pwt.chroma_weight_flag[i] = 0;                                                                           // 0.0
/*904  */     }                                                                                                                // 0.0
/*906  */     if ((pps->weighted_pred && sl->slice_type_nos == AV_PICTURE_TYPE_P) ||                                           // 0.0
/*908  */         (pps->weighted_bipred_idc == 1 &&                                                                            // 0.0
/*910  */          sl->slice_type_nos == AV_PICTURE_TYPE_B))                                                                   // 0.0
/*912  */         ff_h264_pred_weight_table(&sl->gb, sps, sl->ref_count,                                                       // 0.0
/*914  */                                   sl->slice_type_nos, &sl->pwt);                                                     // 0.0
/*918  */     // If frame-mt is enabled, only update mmco tables for the first slice                                           // 0.0
/*920  */     // in a field. Subsequent slices can temporarily clobber h->mmco_index                                           // 0.0
/*922  */     // or h->mmco, which will cause ref list mix-ups and decoding errors                                             // 0.0
/*924  */     // further down the line. This may break decoding if the first slice is                                          // 0.0
/*926  */     // corrupt, thus we only do this if frame-mt is enabled.                                                         // 0.0
/*928  */     if (h->nal_ref_idc) {                                                                                            // 0.0
/*930  */         ret = ff_h264_decode_ref_pic_marking(h, &sl->gb,                                                             // 0.0
/*932  */                                              !(h->avctx->active_thread_type & FF_THREAD_FRAME) ||                    // 0.0
/*934  */                                              h->current_slice == 0);                                                 // 0.0
/*936  */         if (ret < 0 && (h->avctx->err_recognition & AV_EF_EXPLODE))                                                  // 0.0
/*938  */             return AVERROR_INVALIDDATA;                                                                              // 0.0
/*940  */     }                                                                                                                // 0.0
/*944  */     if (sl->slice_type_nos != AV_PICTURE_TYPE_I && pps->cabac) {                                                     // 0.0
/*946  */         tmp = get_ue_golomb_31(&sl->gb);                                                                             // 0.0
/*948  */         if (tmp > 2) {                                                                                               // 0.0
/*950  */             av_log(h->avctx, AV_LOG_ERROR, "cabac_init_idc %u overflow\n", tmp);                                     // 0.0
/*952  */             return AVERROR_INVALIDDATA;                                                                              // 0.0
/*954  */         }                                                                                                            // 0.0
/*956  */         sl->cabac_init_idc = tmp;                                                                                    // 0.0
/*958  */     }                                                                                                                // 0.0
/*962  */     sl->last_qscale_diff = 0;                                                                                        // 0.0
/*964  */     tmp = pps->init_qp + get_se_golomb(&sl->gb);                                                                     // 0.0
/*966  */     if (tmp > 51 + 6 * (sps->bit_depth_luma - 8)) {                                                                  // 0.0
/*968  */         av_log(h->avctx, AV_LOG_ERROR, "QP %u out of range\n", tmp);                                                 // 0.0
/*970  */         return AVERROR_INVALIDDATA;                                                                                  // 0.0
/*972  */     }                                                                                                                // 0.0
/*974  */     sl->qscale       = tmp;                                                                                          // 0.0
/*976  */     sl->chroma_qp[0] = get_chroma_qp(h, 0, sl->qscale);                                                              // 0.0
/*978  */     sl->chroma_qp[1] = get_chroma_qp(h, 1, sl->qscale);                                                              // 0.0
/*980  */     // FIXME qscale / qp ... stuff                                                                                   // 0.0
/*982  */     if (sl->slice_type == AV_PICTURE_TYPE_SP)                                                                        // 0.0
/*984  */         get_bits1(&sl->gb); /* sp_for_switch_flag */                                                                 // 0.0
/*986  */     if (sl->slice_type == AV_PICTURE_TYPE_SP ||                                                                      // 0.0
/*988  */         sl->slice_type == AV_PICTURE_TYPE_SI)                                                                        // 0.0
/*990  */         get_se_golomb(&sl->gb); /* slice_qs_delta */                                                                 // 0.0
/*994  */     sl->deblocking_filter     = 1;                                                                                   // 0.0
/*996  */     sl->slice_alpha_c0_offset = 0;                                                                                   // 0.0
/*998  */     sl->slice_beta_offset     = 0;                                                                                   // 0.0
/*1000 */     if (pps->deblocking_filter_parameters_present) {                                                                 // 0.0
/*1002 */         tmp = get_ue_golomb_31(&sl->gb);                                                                             // 0.0
/*1004 */         if (tmp > 2) {                                                                                               // 0.0
/*1006 */             av_log(h->avctx, AV_LOG_ERROR,                                                                           // 0.0
/*1008 */                    "deblocking_filter_idc %u out of range\n", tmp);                                                  // 0.0
/*1010 */             return AVERROR_INVALIDDATA;                                                                              // 0.0
/*1012 */         }                                                                                                            // 0.0
/*1014 */         sl->deblocking_filter = tmp;                                                                                 // 0.0
/*1016 */         if (sl->deblocking_filter < 2)                                                                               // 0.0
/*1018 */             sl->deblocking_filter ^= 1;  // 1<->0                                                                    // 0.0
/*1022 */         if (sl->deblocking_filter) {                                                                                 // 0.0
/*1024 */             sl->slice_alpha_c0_offset = get_se_golomb(&sl->gb) * 2;                                                  // 0.0
/*1026 */             sl->slice_beta_offset     = get_se_golomb(&sl->gb) * 2;                                                  // 0.0
/*1028 */             if (sl->slice_alpha_c0_offset >  12 ||                                                                   // 0.0
/*1030 */                 sl->slice_alpha_c0_offset < -12 ||                                                                   // 0.0
/*1032 */                 sl->slice_beta_offset >  12     ||                                                                   // 0.0
/*1034 */                 sl->slice_beta_offset < -12) {                                                                       // 0.0
/*1036 */                 av_log(h->avctx, AV_LOG_ERROR,                                                                       // 0.0
/*1038 */                        "deblocking filter parameters %d %d out of range\n",                                          // 0.0
/*1040 */                        sl->slice_alpha_c0_offset, sl->slice_beta_offset);                                            // 0.0
/*1042 */                 return AVERROR_INVALIDDATA;                                                                          // 0.0
/*1044 */             }                                                                                                        // 0.0
/*1046 */         }                                                                                                            // 0.0
/*1048 */     }                                                                                                                // 0.0
/*1052 */     return 0;                                                                                                        // 0.0
/*1054 */ }                                                                                                                    // 0.0
