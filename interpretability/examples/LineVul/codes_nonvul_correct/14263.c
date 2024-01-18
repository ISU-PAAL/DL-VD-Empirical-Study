// commit message FFmpeg@6202e2fede (target=0, prob=0.4833466, correct=True): indeo4: Rework stream analysis report
/*0   */ static int decode_band_hdr(IVI45DecContext *ctx, IVIBandDesc *band,                        // (4) 0.04688
/*2   */                            AVCodecContext *avctx)                                          // (1) 0.06641
/*4   */ {                                                                                          // (24) 0.001953
/*6   */     int plane, band_num, indx, transform_id, scan_indx;                                    // (7) 0.04297
/*8   */     int i;                                                                                 // (22) 0.01172
/*12  */     plane    = get_bits(&ctx->gb, 2);                                                      // (13) 0.03516
/*14  */     band_num = get_bits(&ctx->gb, 4);                                                      // (16) 0.0332
/*16  */     if (band->plane != plane || band->band_num != band_num) {                              // (8) 0.04297
/*18  */         av_log(avctx, AV_LOG_ERROR, "Invalid band header sequence!\n");                    // (2) 0.05664
/*20  */         return AVERROR_INVALIDDATA;                                                        // (17) 0.0332
/*22  */     }                                                                                      // (23) 0.007812
/*26  */     band->is_empty = get_bits1(&ctx->gb);                                                  // (14) 0.03516
/*28  */     if (!band->is_empty) {                                                                 // (19) 0.02344
/*30  */         int old_blk_size = band->blk_size;                                                 // (9) 0.04297
/*32  */         /* skip header size                                                                // (20) 0.02148
/*34  */          * If header size is not given, header size is 4 bytes. */                         // (6) 0.04492
/*36  */         if (get_bits1(&ctx->gb))                                                           // (15) 0.03516
/*38  */             skip_bits(&ctx->gb, 16);                                                       // (11) 0.04102
/*42  */         band->is_halfpel = get_bits(&ctx->gb, 2);                                          // (5) 0.04687
/*44  */         if (band->is_halfpel >= 2) {                                                       // (12) 0.03711
/*46  */             av_log(avctx, AV_LOG_ERROR, "Invalid/unsupported mv resolution: %d!\n",        // (0) 0.07617
/*48  */                    band->is_halfpel);                                                      // (3) 0.04883
/*50  */             return AVERROR_INVALIDDATA;                                                    // (10) 0.04102
/*52  */         }                                                                                  // (21) 0.01562
/*54  */ #if IVI4_STREAM_ANALYSER                                                                   // (18) 0.02539
/*56  */         if (!band->is_halfpel)                                                             // 0.0
/*58  */             ctx->uses_fullpel = 1;                                                         // 0.0
/*60  */ #endif                                                                                     // 0.0
/*64  */         band->checksum_present = get_bits1(&ctx->gb);                                      // 0.0
/*66  */         if (band->checksum_present)                                                        // 0.0
/*68  */             band->checksum = get_bits(&ctx->gb, 16);                                       // 0.0
/*72  */         indx = get_bits(&ctx->gb, 2);                                                      // 0.0
/*74  */         if (indx == 3) {                                                                   // 0.0
/*76  */             av_log(avctx, AV_LOG_ERROR, "Invalid block size!\n");                          // 0.0
/*78  */             return AVERROR_INVALIDDATA;                                                    // 0.0
/*80  */         }                                                                                  // 0.0
/*82  */         band->mb_size  = 16 >> indx;                                                       // 0.0
/*84  */         band->blk_size = 8 >> (indx >> 1);                                                 // 0.0
/*88  */         band->inherit_mv     = get_bits1(&ctx->gb);                                        // 0.0
/*90  */         band->inherit_qdelta = get_bits1(&ctx->gb);                                        // 0.0
/*94  */         band->glob_quant = get_bits(&ctx->gb, 5);                                          // 0.0
/*98  */         if (!get_bits1(&ctx->gb) || ctx->frame_type == IVI4_FRAMETYPE_INTRA) {             // 0.0
/*100 */             transform_id = get_bits(&ctx->gb, 5);                                          // 0.0
/*102 */             if (transform_id >= FF_ARRAY_ELEMS(transforms) ||                              // 0.0
/*104 */                 !transforms[transform_id].inv_trans) {                                     // 0.0
/*106 */                 avpriv_request_sample(avctx, "Transform %d", transform_id);                // 0.0
/*108 */                 return AVERROR_PATCHWELCOME;                                               // 0.0
/*110 */             }                                                                              // 0.0
/*112 */             if ((transform_id >= 7 && transform_id <= 9) ||                                // 0.0
/*114 */                  transform_id == 17) {                                                     // 0.0
/*116 */                 avpriv_request_sample(avctx, "DCT transform");                             // 0.0
/*118 */                 return AVERROR_PATCHWELCOME;                                               // 0.0
/*120 */             }                                                                              // 0.0
/*124 */ #if IVI4_STREAM_ANALYSER                                                                   // 0.0
/*126 */             if ((transform_id >= 0 && transform_id <= 2) || transform_id == 10)            // 0.0
/*128 */                 ctx->uses_haar = 1;                                                        // 0.0
/*130 */ #endif                                                                                     // 0.0
/*134 */             band->inv_transform = transforms[transform_id].inv_trans;                      // 0.0
/*136 */             band->dc_transform  = transforms[transform_id].dc_trans;                       // 0.0
/*138 */             band->is_2d_trans   = transforms[transform_id].is_2d_trans;                    // 0.0
/*140 */             if (transform_id < 10)                                                         // 0.0
/*142 */                 band->transform_size = 8;                                                  // 0.0
/*144 */             else                                                                           // 0.0
/*146 */                 band->transform_size = 4;                                                  // 0.0
/*150 */             if (band->blk_size != band->transform_size)                                    // 0.0
/*152 */                 return AVERROR_INVALIDDATA;                                                // 0.0
/*156 */             scan_indx = get_bits(&ctx->gb, 4);                                             // 0.0
/*158 */             if (scan_indx == 15) {                                                         // 0.0
/*160 */                 av_log(avctx, AV_LOG_ERROR, "Custom scan pattern encountered!\n");         // 0.0
/*162 */                 return AVERROR_INVALIDDATA;                                                // 0.0
/*164 */             }                                                                              // 0.0
/*166 */             if (scan_indx > 4 && scan_indx < 10) {                                         // 0.0
/*168 */                 if (band->blk_size != 4)                                                   // 0.0
/*170 */                     return AVERROR_INVALIDDATA;                                            // 0.0
/*172 */             } else if (band->blk_size != 8)                                                // 0.0
/*174 */                 return AVERROR_INVALIDDATA;                                                // 0.0
/*178 */             band->scan = scan_index_to_tab[scan_indx];                                     // 0.0
/*182 */             band->quant_mat = get_bits(&ctx->gb, 5);                                       // 0.0
/*184 */             if (band->quant_mat >= FF_ARRAY_ELEMS(quant_index_to_tab)) {                   // 0.0
/*188 */                 if (band->quant_mat == 31)                                                 // 0.0
/*190 */                     av_log(avctx, AV_LOG_ERROR,                                            // 0.0
/*192 */                            "Custom quant matrix encountered!\n");                          // 0.0
/*194 */                 else                                                                       // 0.0
/*196 */                     avpriv_request_sample(avctx, "Quantization matrix %d",                 // 0.0
/*198 */                                           band->quant_mat);                                // 0.0
/*200 */                 band->quant_mat = -1;                                                      // 0.0
/*202 */                 return AVERROR_INVALIDDATA;                                                // 0.0
/*204 */             }                                                                              // 0.0
/*206 */         } else {                                                                           // 0.0
/*208 */             if (old_blk_size != band->blk_size) {                                          // 0.0
/*210 */                 av_log(avctx, AV_LOG_ERROR,                                                // 0.0
/*212 */                        "The band block size does not match the configuration "             // 0.0
/*214 */                        "inherited\n");                                                     // 0.0
/*216 */                 return AVERROR_INVALIDDATA;                                                // 0.0
/*218 */             }                                                                              // 0.0
/*220 */             if (band->quant_mat < 0) {                                                     // 0.0
/*222 */                 av_log(avctx, AV_LOG_ERROR, "Invalid quant_mat inherited\n");              // 0.0
/*224 */                 return AVERROR_INVALIDDATA;                                                // 0.0
/*226 */             }                                                                              // 0.0
/*228 */         }                                                                                  // 0.0
/*232 */         /* decode block huffman codebook */                                                // 0.0
/*234 */         if (!get_bits1(&ctx->gb))                                                          // 0.0
/*236 */             band->blk_vlc.tab = ctx->blk_vlc.tab;                                          // 0.0
/*238 */         else                                                                               // 0.0
/*240 */             if (ff_ivi_dec_huff_desc(&ctx->gb, 1, IVI_BLK_HUFF,                            // 0.0
/*242 */                                      &band->blk_vlc, avctx))                               // 0.0
/*244 */                 return AVERROR_INVALIDDATA;                                                // 0.0
/*248 */         /* select appropriate rvmap table for this band */                                 // 0.0
/*250 */         band->rvmap_sel = get_bits1(&ctx->gb) ? get_bits(&ctx->gb, 3) : 8;                 // 0.0
/*254 */         /* decode rvmap probability corrections if any */                                  // 0.0
/*256 */         band->num_corr = 0; /* there is no corrections */                                  // 0.0
/*258 */         if (get_bits1(&ctx->gb)) {                                                         // 0.0
/*260 */             band->num_corr = get_bits(&ctx->gb, 8); /* get number of correction pairs */   // 0.0
/*262 */             if (band->num_corr > 61) {                                                     // 0.0
/*264 */                 av_log(avctx, AV_LOG_ERROR, "Too many corrections: %d\n",                  // 0.0
/*266 */                        band->num_corr);                                                    // 0.0
/*268 */                 return AVERROR_INVALIDDATA;                                                // 0.0
/*270 */             }                                                                              // 0.0
/*274 */             /* read correction pairs */                                                    // 0.0
/*276 */             for (i = 0; i < band->num_corr * 2; i++)                                       // 0.0
/*278 */                 band->corr[i] = get_bits(&ctx->gb, 8);                                     // 0.0
/*280 */         }                                                                                  // 0.0
/*282 */     }                                                                                      // 0.0
/*286 */     if (band->blk_size == 8) {                                                             // 0.0
/*288 */         band->intra_base = &ivi4_quant_8x8_intra[quant_index_to_tab[band->quant_mat]][0];  // 0.0
/*290 */         band->inter_base = &ivi4_quant_8x8_inter[quant_index_to_tab[band->quant_mat]][0];  // 0.0
/*292 */     } else {                                                                               // 0.0
/*294 */         band->intra_base = &ivi4_quant_4x4_intra[quant_index_to_tab[band->quant_mat]][0];  // 0.0
/*296 */         band->inter_base = &ivi4_quant_4x4_inter[quant_index_to_tab[band->quant_mat]][0];  // 0.0
/*298 */     }                                                                                      // 0.0
/*302 */     /* Indeo 4 doesn't use scale tables */                                                 // 0.0
/*304 */     band->intra_scale = NULL;                                                              // 0.0
/*306 */     band->inter_scale = NULL;                                                              // 0.0
/*310 */     align_get_bits(&ctx->gb);                                                              // 0.0
/*314 */     return 0;                                                                              // 0.0
/*316 */ }                                                                                          // 0.0
