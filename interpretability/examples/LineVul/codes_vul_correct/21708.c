// commit message FFmpeg@ae3da0ae55 (target=1, prob=0.6559372, correct=True): indeo4/5: check empty tile size in decode_mb_info().
/*0   */ static int decode_band(IVI45DecContext *ctx, int plane_num,                                            // (12) 0.03711
/*2   */                        IVIBandDesc *band, AVCodecContext *avctx)                                       // (0) 0.07226
/*4   */ {                                                                                                      // (25) 0.001954
/*6   */     int         result, i, t, idx1, idx2, pos;                                                         // (4) 0.05469
/*8   */     IVITile     *tile;                                                                                 // (17) 0.02541
/*12  */     band->buf     = band->bufs[ctx->dst_buf];                                                          // (7) 0.04492
/*14  */     if (!band->buf) {                                                                                  // (19) 0.01953
/*16  */         av_log(avctx, AV_LOG_ERROR, "Band buffer points to no data!\n");                               // (2) 0.06055
/*18  */         return AVERROR_INVALIDDATA;                                                                    // (13) 0.0332
/*20  */     }                                                                                                  // (24) 0.007812
/*22  */     band->ref_buf = band->bufs[ctx->ref_buf];                                                          // (10) 0.03906
/*24  */     band->data_ptr = ctx->frame_data + (get_bits_count(&ctx->gb) >> 3);                                // (3) 0.05859
/*28  */     result = ctx->decode_band_hdr(ctx, band, avctx);                                                   // (8) 0.04492
/*30  */     if (result) {                                                                                      // (21) 0.01562
/*32  */         av_log(avctx, AV_LOG_ERROR, "Error while decoding band header: %d\n",                          // (1) 0.0625
/*34  */                result);                                                                                // (16) 0.03125
/*36  */         return result;                                                                                 // (20) 0.01953
/*38  */     }                                                                                                  // (23) 0.007812
/*42  */     if (band->is_empty) {                                                                              // (18) 0.02344
/*44  */         av_log(avctx, AV_LOG_ERROR, "Empty band encountered!\n");                                      // (6) 0.05469
/*46  */         return AVERROR_INVALIDDATA;                                                                    // (14) 0.0332
/*48  */     }                                                                                                  // (22) 0.007812
/*52  */     band->rv_map = &ctx->rvmap_tabs[band->rvmap_sel];                                                  // (5) 0.05469
/*56  */     /* apply corrections to the selected rvmap table if present */                                     // (15) 0.03125
/*58  */     for (i = 0; i < band->num_corr; i++) {                                                             // (9) 0.04101
/*60  */         idx1 = band->corr[i * 2];                                                                      // (11) 0.03906
/*62  */         idx2 = band->corr[i * 2 + 1];                                                                  // 0.0
/*64  */         FFSWAP(uint8_t, band->rv_map->runtab[idx1], band->rv_map->runtab[idx2]);                       // 0.0
/*66  */         FFSWAP(int16_t, band->rv_map->valtab[idx1], band->rv_map->valtab[idx2]);                       // 0.0
/*68  */     }                                                                                                  // 0.0
/*72  */     pos = get_bits_count(&ctx->gb);                                                                    // 0.0
/*76  */     for (t = 0; t < band->num_tiles; t++) {                                                            // 0.0
/*78  */         tile = &band->tiles[t];                                                                        // 0.0
/*82  */         if (tile->mb_size != band->mb_size) {                                                          // 0.0
/*84  */             av_log(avctx, AV_LOG_ERROR, "MB sizes mismatch: %d vs. %d\n",                              // 0.0
/*86  */                    band->mb_size, tile->mb_size);                                                      // 0.0
/*88  */             return AVERROR_INVALIDDATA;                                                                // 0.0
/*90  */         }                                                                                              // 0.0
/*92  */         tile->is_empty = get_bits1(&ctx->gb);                                                          // 0.0
/*94  */         if (tile->is_empty) {                                                                          // 0.0
/*96  */             ivi_process_empty_tile(avctx, band, tile,                                                  // 0.0
/*98  */                                       (ctx->planes[0].bands[0].mb_size >> 3) - (band->mb_size >> 3));  // 0.0
/*100 */             av_dlog(avctx, "Empty tile encountered!\n");                                               // 0.0
/*102 */         } else {                                                                                       // 0.0
/*104 */             tile->data_size = ff_ivi_dec_tile_data_size(&ctx->gb);                                     // 0.0
/*106 */             if (!tile->data_size) {                                                                    // 0.0
/*108 */                 av_log(avctx, AV_LOG_ERROR, "Tile data size is zero!\n");                              // 0.0
/*110 */                 return AVERROR_INVALIDDATA;                                                            // 0.0
/*112 */             }                                                                                          // 0.0
/*116 */             result = ctx->decode_mb_info(ctx, band, tile, avctx);                                      // 0.0
/*118 */             if (result < 0)                                                                            // 0.0
/*120 */                 break;                                                                                 // 0.0
/*124 */             result = ff_ivi_decode_blocks(&ctx->gb, band, tile);                                       // 0.0
/*126 */             if (result < 0 || ((get_bits_count(&ctx->gb) - pos) >> 3) != tile->data_size) {            // 0.0
/*128 */                 av_log(avctx, AV_LOG_ERROR, "Corrupted tile data encountered!\n");                     // 0.0
/*130 */                 break;                                                                                 // 0.0
/*132 */             }                                                                                          // 0.0
/*136 */             pos += tile->data_size << 3; // skip to next tile                                          // 0.0
/*138 */         }                                                                                              // 0.0
/*140 */     }                                                                                                  // 0.0
/*144 */     /* restore the selected rvmap table by applying its corrections in reverse order */                // 0.0
/*146 */     for (i = band->num_corr-1; i >= 0; i--) {                                                          // 0.0
/*148 */         idx1 = band->corr[i*2];                                                                        // 0.0
/*150 */         idx2 = band->corr[i*2+1];                                                                      // 0.0
/*152 */         FFSWAP(uint8_t, band->rv_map->runtab[idx1], band->rv_map->runtab[idx2]);                       // 0.0
/*154 */         FFSWAP(int16_t, band->rv_map->valtab[idx1], band->rv_map->valtab[idx2]);                       // 0.0
/*156 */     }                                                                                                  // 0.0
/*160 */ #ifdef DEBUG                                                                                           // 0.0
/*162 */     if (band->checksum_present) {                                                                      // 0.0
/*164 */         uint16_t chksum = ivi_calc_band_checksum(band);                                                // 0.0
/*166 */         if (chksum != band->checksum) {                                                                // 0.0
/*168 */             av_log(avctx, AV_LOG_ERROR,                                                                // 0.0
/*170 */                    "Band checksum mismatch! Plane %d, band %d, received: %x, calculated: %x\n",        // 0.0
/*172 */                    band->plane, band->band_num, band->checksum, chksum);                               // 0.0
/*174 */         }                                                                                              // 0.0
/*176 */     }                                                                                                  // 0.0
/*178 */ #endif                                                                                                 // 0.0
/*182 */     align_get_bits(&ctx->gb);                                                                          // 0.0
/*186 */     return result;                                                                                     // 0.0
/*188 */ }                                                                                                      // 0.0
