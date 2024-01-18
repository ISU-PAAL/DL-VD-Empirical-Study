// commit message FFmpeg@73f863d751 (target=1, prob=0.71237403, correct=True): fic: set pict_type/key_frame after (instead of during) slice decoding.
/*0  */ static int fic_decode_block(FICContext *ctx, GetBitContext *gb,        // (4) 0.05556
/*2  */                             uint8_t *dst, int stride, int16_t *block)  // (1) 0.1136
/*4  */ {                                                                      // (19) 0.002525
/*6  */     int i, num_coeff;                                                  // (14) 0.02778
/*10 */     /* Is it a skip block? */                                          // (15) 0.02778
/*12 */     if (get_bits1(gb)) {                                               // (12) 0.03283
/*14 */         /* This is a P-frame. */                                       // (10) 0.0404
/*16 */         ctx->frame->key_frame = 0;                                     // (5) 0.04545
/*18 */         ctx->frame->pict_type = AV_PICTURE_TYPE_P;                     // (3) 0.06566
/*22 */         return 0;                                                      // (16) 0.02525
/*24 */     }                                                                  // (18) 0.0101
/*28 */     memset(block, 0, sizeof(*block) * 64);                             // (8) 0.04293
/*32 */     num_coeff = get_bits(gb, 7);                                       // (11) 0.0404
/*34 */     if (num_coeff > 64)                                                // (13) 0.0303
/*36 */         return AVERROR_INVALIDDATA;                                    // (9) 0.04293
/*40 */     for (i = 0; i < num_coeff; i++)                                    // (6) 0.04545
/*42 */         block[ff_zigzag_direct[i]] = get_se_golomb(gb) *               // (2) 0.07576
/*44 */                                      ctx->qmat[ff_zigzag_direct[i]];   // (0) 0.1313
/*48 */     fic_idct_put(dst, stride, block);                                  // (7) 0.04545
/*52 */     return 0;                                                          // (17) 0.01515
/*54 */ }                                                                      // (20) 0.002525
