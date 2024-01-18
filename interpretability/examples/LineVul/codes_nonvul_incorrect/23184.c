// commit message FFmpeg@dbc1163b20 (target=0, prob=0.55063415, correct=False): prores: Extend the padding check to 16bit
/*0  */ static inline int decode_ac_coeffs(GetBitContext *gb, int16_t *out,                // (9) 0.04688
/*2  */                                    int blocks_per_slice,                           // (2) 0.08007
/*4  */                                    int plane_size_factor,                          // (1) 0.08007
/*6  */                                    const uint8_t *scan)                            // (0) 0.08202
/*8  */ {                                                                                  // (20) 0.001954
/*10 */     int pos, block_mask, run, level, sign, run_cb_index, lev_cb_index;             // (7) 0.05469
/*12 */     int max_coeffs, bits_left;                                                     // (14) 0.02734
/*16 */     /* set initial prediction values */                                            // (17) 0.01758
/*18 */     run   = 4;                                                                     // (18) 0.01758
/*20 */     level = 2;                                                                     // (19) 0.01367
/*24 */     max_coeffs = blocks_per_slice << 6;                                            // (12) 0.0332
/*26 */     block_mask = blocks_per_slice - 1;                                             // (13) 0.0293
/*30 */     for (pos = blocks_per_slice - 1; pos < max_coeffs;) {                          // (8) 0.04888
/*32 */         run_cb_index = ff_prores_run_to_cb_index[FFMIN(run, 15)];                  // (4) 0.0664
/*34 */         lev_cb_index = ff_prores_lev_to_cb_index[FFMIN(level, 9)];                 // (5) 0.0664
/*38 */         bits_left = get_bits_left(gb);                                             // (11) 0.0371
/*40 */         if (bits_left <= 0 || (bits_left <= 8 && !show_bits(gb, bits_left)))       // (6) 0.06445
/*42 */             return 0;                                                              // (15) 0.02734
/*46 */         run = decode_vlc_codeword(gb, ff_prores_ac_codebook[run_cb_index]);        // (3) 0.0703
/*48 */         if (run < 0)                                                               // (16) 0.02539
/*50 */             return AVERROR_INVALIDDATA;                                            // (10) 0.04101
/*54 */         bits_left = get_bits_left(gb);                                             // 0.0
/*56 */         if (bits_left <= 0 || (bits_left <= 8 && !show_bits(gb, bits_left)))       // 0.0
/*58 */             return AVERROR_INVALIDDATA;                                            // 0.0
/*62 */         level = decode_vlc_codeword(gb, ff_prores_ac_codebook[lev_cb_index]) + 1;  // 0.0
/*64 */         if (level < 0)                                                             // 0.0
/*66 */             return AVERROR_INVALIDDATA;                                            // 0.0
/*70 */         pos += run + 1;                                                            // 0.0
/*72 */         if (pos >= max_coeffs)                                                     // 0.0
/*74 */             break;                                                                 // 0.0
/*78 */         sign = get_sbits(gb, 1);                                                   // 0.0
/*80 */         out[((pos & block_mask) << 6) + scan[pos >> plane_size_factor]] =          // 0.0
/*82 */             (level ^ sign) - sign;                                                 // 0.0
/*84 */     }                                                                              // 0.0
/*88 */     return 0;                                                                      // 0.0
/*90 */ }                                                                                  // 0.0
