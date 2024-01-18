// commit message FFmpeg@c43485f707 (target=1, prob=0.399276, correct=False): diracdec: rewrite HQ slice decoding
/*0  */ static int decode_hq_slice(AVCodecContext *avctx, void *arg)                                                 // (7) 0.04102
/*2  */ {                                                                                                            // (24) 0.001953
/*4  */     int i, quant, level, orientation, quant_idx;                                                             // (14) 0.0332
/*6  */     uint8_t quants[MAX_DWT_LEVELS][4];                                                                       // (10) 0.04102
/*8  */     DiracContext *s = avctx->priv_data;                                                                      // (15) 0.03125
/*10 */     DiracSlice *slice = arg;                                                                                 // (19) 0.02344
/*12 */     GetBitContext *gb = &slice->gb;                                                                          // (18) 0.02734
/*16 */     skip_bits_long(gb, 8*s->highquality.prefix_bytes);                                                       // (4) 0.04297
/*18 */     quant_idx = get_bits(gb, 8);                                                                             // (16) 0.03125
/*22 */     /* Slice quantization (slice_quantizers() in the specs) */                                               // (11) 0.03711
/*24 */     for (level = 0; level < s->wavelet_depth; level++) {                                                     // (9) 0.04102
/*26 */         for (orientation = !!level; orientation < 4; orientation++) {                                        // (6) 0.04297
/*28 */             quant = FFMAX(quant_idx - s->lowdelay.quant[level][orientation], 0);                             // (0) 0.06836
/*30 */             quants[level][orientation] = quant;                                                              // (5) 0.04297
/*32 */         }                                                                                                    // (21) 0.01562
/*34 */     }                                                                                                        // (23) 0.007812
/*38 */     /* Luma + 2 Chroma planes */                                                                             // (20) 0.02344
/*40 */     for (i = 0; i < 3; i++) {                                                                                // (17) 0.03125
/*42 */         int64_t length = s->highquality.size_scaler * get_bits(gb, 8);                                       // (2) 0.06055
/*44 */         int64_t bits_left = 8 * length;                                                                      // (12) 0.03711
/*46 */         int64_t bits_end = get_bits_count(gb) + bits_left;                                                   // (3) 0.05469
/*50 */         if (bits_end >= INT_MAX) {                                                                           // (13) 0.03516
/*52 */             av_log(s->avctx, AV_LOG_ERROR, "end too far away\n");                                            // (1) 0.06641
/*54 */             return AVERROR_INVALIDDATA;                                                                      // (8) 0.04102
/*56 */         }                                                                                                    // (22) 0.01562
/*60 */         for (level = 0; level < s->wavelet_depth; level++) {                                                 // 0.0
/*62 */             for (orientation = !!level; orientation < 4; orientation++) {                                    // 0.0
/*64 */                 decode_subband(s, gb, quants[level][orientation], slice->slice_x, slice->slice_y, bits_end,  // 0.0
/*66 */                                &s->plane[i].band[level][orientation], NULL);                                 // 0.0
/*68 */             }                                                                                                // 0.0
/*70 */         }                                                                                                    // 0.0
/*72 */         skip_bits_long(gb, bits_end - get_bits_count(gb));                                                   // 0.0
/*74 */     }                                                                                                        // 0.0
/*78 */     return 0;                                                                                                // 0.0
/*80 */ }                                                                                                            // 0.0
