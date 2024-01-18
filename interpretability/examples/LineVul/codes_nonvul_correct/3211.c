// commit message FFmpeg@3d2c3ef4b4 (target=0, prob=0.016379569, correct=True): Remove slice_table checks from decode_cabac_mb_cbp_luma() and set left/top_cbp so these checks arent needed.
/*0  */ static int decode_cabac_mb_cbp_luma( H264Context *h) {                            // (10) 0.053
/*2  */     int cbp_b, cbp_a, ctx, cbp = 0;                                               // (11) 0.05069
/*6  */     cbp_a = h->slice_table[h->left_mb_xy[0]] == h->slice_num ? h->left_cbp : -1;  // (1) 0.09447
/*8  */     cbp_b = h->slice_table[h->top_mb_xy]     == h->slice_num ? h->top_cbp  : -1;  // (0) 0.1014
/*12 */     ctx = !(cbp_a & 0x02) + 2 * !(cbp_b & 0x04);                                  // (6) 0.07143
/*14 */     cbp |= get_cabac_noinline(&h->cabac, &h->cabac_state[73 + ctx]);              // (5) 0.08295
/*16 */     ctx = !(cbp   & 0x01) + 2 * !(cbp_b & 0x08);                                  // (7) 0.07143
/*18 */     cbp |= get_cabac_noinline(&h->cabac, &h->cabac_state[73 + ctx]) << 1;         // (2) 0.08986
/*20 */     ctx = !(cbp_a & 0x08) + 2 * !(cbp   & 0x01);                                  // (8) 0.07143
/*22 */     cbp |= get_cabac_noinline(&h->cabac, &h->cabac_state[73 + ctx]) << 2;         // (3) 0.08986
/*24 */     ctx = !(cbp   & 0x04) + 2 * !(cbp   & 0x02);                                  // (9) 0.07143
/*26 */     cbp |= get_cabac_noinline(&h->cabac, &h->cabac_state[73 + ctx]) << 3;         // (4) 0.08986
/*28 */     return cbp;                                                                   // (12) 0.01613
/*30 */ }                                                                                 // (13) 0.002304
