// commit message FFmpeg@d9051f8f3e (target=1, prob=0.6878832, correct=True): avcodec/mimic: Fix runtime error: index 96 out of bounds for type 'const int8_t [64]'
/*0  */ static int vlc_decode_block(MimicContext *ctx, int num_coeffs, int qscale)      // (1) 0.05469
/*2  */ {                                                                               // (25) 0.001954
/*4  */     int16_t *block = ctx->dct_block;                                            // (14) 0.03516
/*6  */     unsigned int pos;                                                           // (24) 0.01367
/*10 */     ctx->bdsp.clear_block(block);                                               // (17) 0.0293
/*14 */     block[0] = get_bits(&ctx->gb, 8) << 3;                                      // (6) 0.04102
/*18 */     for (pos = 1; pos < num_coeffs; pos++) {                                    // (11) 0.03906
/*20 */         uint32_t vlc, num_bits;                                                 // (15) 0.03516
/*22 */         int value;                                                              // (23) 0.01953
/*24 */         int coeff;                                                              // (22) 0.02148
/*28 */         vlc = get_vlc2(&ctx->gb, ctx->vlc.table, ctx->vlc.bits, 3);             // (0) 0.07422
/*30 */         if (!vlc) /* end-of-block code */                                       // (12) 0.03906
/*32 */             return 0;                                                           // (19) 0.02734
/*34 */         if (vlc == -1)                                                          // (18) 0.0293
/*36 */             return AVERROR_INVALIDDATA;                                         // (9) 0.04102
/*40 */         /* pos_add and num_bits are coded in the vlc code */                    // (3) 0.04492
/*42 */         pos     += vlc & 15; // pos_add                                         // (5) 0.04297
/*44 */         num_bits = vlc >> 4; // num_bits                                        // (10) 0.03906
/*48 */         if (pos >= 64)                                                          // (20) 0.02539
/*50 */             return AVERROR_INVALIDDATA;                                         // (8) 0.04102
/*54 */         value = get_bits(&ctx->gb, num_bits);                                   // (7) 0.04102
/*58 */         /* FFmpeg's IDCT behaves somewhat different from the original code, so  // (4) 0.04297
/*60 */          * a factor of 4 was added to the input */                              // (13) 0.03711
/*64 */         coeff = vlcdec_lookup[num_bits][value];                                 // (2) 0.04687
/*66 */         if (pos < 3)                                                            // (21) 0.02539
/*68 */             coeff *= 16;                                                        // (16) 0.0332
/*70 */         else /* TODO Use >> 10 instead of / 1001 */                             // 0.0
/*72 */             coeff = (coeff * qscale) / 1001;                                    // 0.0
/*76 */         block[ctx->scantable.permutated[pos]] = coeff;                          // 0.0
/*78 */     }                                                                           // 0.0
/*82 */     return 0;                                                                   // 0.0
/*84 */ }                                                                               // 0.0
