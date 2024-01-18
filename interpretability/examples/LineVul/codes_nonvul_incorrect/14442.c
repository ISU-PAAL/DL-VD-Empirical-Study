// commit message FFmpeg@1a3ed056c5 (target=0, prob=0.5538224, correct=False): avcodec/hevc: make check for previous slice segment tighter
/*0   */ static int hls_decode_entry(AVCodecContext *avctxt, void *isFilterThread)                                            // (9) 0.04883
/*2   */ {                                                                                                                    // (20) 0.001955
/*4   */     HEVCContext *s  = avctxt->priv_data;                                                                             // (12) 0.03516
/*6   */     int ctb_size    = 1 << s->sps->log2_ctb_size;                                                                    // (5) 0.05469
/*8   */     int more_data   = 1;                                                                                             // (16) 0.02344
/*10  */     int x_ctb       = 0;                                                                                             // (13) 0.0332
/*12  */     int y_ctb       = 0;                                                                                             // (15) 0.0332
/*14  */     int ctb_addr_ts = s->pps->ctb_addr_rs_to_ts[s->sh.slice_ctb_addr_rs];                                            // (0) 0.07812
/*18  */     if (!ctb_addr_ts && s->sh.dependent_slice_segment_flag) {                                                        // (8) 0.05078
/*20  */         av_log(s->avctx, AV_LOG_ERROR, "Impossible initial tile.\n");                                                // (4) 0.06055
/*22  */         return AVERROR_INVALIDDATA;                                                                                  // (14) 0.0332
/*24  */     }                                                                                                                // (18) 0.007812
/*28  */     if (s->sh.dependent_slice_segment_flag) {                                                                        // (11) 0.03711
/*30  */         int prev_rs = s->pps->ctb_addr_ts_to_rs[ctb_addr_ts - 1];                                                    // (2) 0.07031
/*32  */         if (s->tab_slice_address[prev_rs] == -1) {                                                                   // (7) 0.05078
/*34  */             av_log(s->avctx, AV_LOG_ERROR, "Previous slice segment missing\n");                                      // (3) 0.0664
/*36  */             return AVERROR_INVALIDDATA;                                                                              // (10) 0.04101
/*38  */         }                                                                                                            // (17) 0.01562
/*40  */     }                                                                                                                // (19) 0.007812
/*44  */     while (more_data && ctb_addr_ts < s->sps->ctb_size) {                                                            // (6) 0.05469
/*46  */         int ctb_addr_rs = s->pps->ctb_addr_ts_to_rs[ctb_addr_ts];                                                    // (1) 0.07422
/*50  */         x_ctb = (ctb_addr_rs % ((s->sps->width + ctb_size - 1) >> s->sps->log2_ctb_size)) << s->sps->log2_ctb_size;  // 0.0
/*52  */         y_ctb = (ctb_addr_rs / ((s->sps->width + ctb_size - 1) >> s->sps->log2_ctb_size)) << s->sps->log2_ctb_size;  // 0.0
/*54  */         hls_decode_neighbour(s, x_ctb, y_ctb, ctb_addr_ts);                                                          // 0.0
/*58  */         ff_hevc_cabac_init(s, ctb_addr_ts);                                                                          // 0.0
/*62  */         hls_sao_param(s, x_ctb >> s->sps->log2_ctb_size, y_ctb >> s->sps->log2_ctb_size);                            // 0.0
/*66  */         s->deblock[ctb_addr_rs].beta_offset = s->sh.beta_offset;                                                     // 0.0
/*68  */         s->deblock[ctb_addr_rs].tc_offset   = s->sh.tc_offset;                                                       // 0.0
/*70  */         s->filter_slice_edges[ctb_addr_rs]  = s->sh.slice_loop_filter_across_slices_enabled_flag;                    // 0.0
/*74  */         more_data = hls_coding_quadtree(s, x_ctb, y_ctb, s->sps->log2_ctb_size, 0);                                  // 0.0
/*76  */         if (more_data < 0) {                                                                                         // 0.0
/*78  */             s->tab_slice_address[ctb_addr_rs] = -1;                                                                  // 0.0
/*80  */             return more_data;                                                                                        // 0.0
/*82  */         }                                                                                                            // 0.0
/*88  */         ctb_addr_ts++;                                                                                               // 0.0
/*90  */         ff_hevc_save_states(s, ctb_addr_ts);                                                                         // 0.0
/*92  */         ff_hevc_hls_filters(s, x_ctb, y_ctb, ctb_size);                                                              // 0.0
/*94  */     }                                                                                                                // 0.0
/*98  */     if (x_ctb + ctb_size >= s->sps->width &&                                                                         // 0.0
/*100 */         y_ctb + ctb_size >= s->sps->height)                                                                          // 0.0
/*102 */         ff_hevc_hls_filter(s, x_ctb, y_ctb);                                                                         // 0.0
/*106 */     return ctb_addr_ts;                                                                                              // 0.0
/*108 */ }                                                                                                                    // 0.0
