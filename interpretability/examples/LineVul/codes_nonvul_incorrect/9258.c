// commit message FFmpeg@c94d551ea7 (target=0, prob=0.89813644, correct=False): avcodec/pixlet: Reorder rlen check
/*0   */ static int read_low_coeffs(AVCodecContext *avctx, int16_t *dst, int size, int width, ptrdiff_t stride)  // (0) 0.07423
/*2   */ {                                                                                                       // (24) 0.001955
/*4   */     PixletContext *ctx = avctx->priv_data;                                                              // (13) 0.03125
/*6   */     GetBitContext *b = &ctx->gbit;                                                                      // (15) 0.0293
/*8   */     unsigned cnt1, nbits, k, j = 0, i = 0;                                                              // (9) 0.04102
/*10  */     int64_t value, state = 3;                                                                           // (18) 0.02539
/*12  */     int rlen, escape, flag = 0;                                                                         // (17) 0.02539
/*16  */     while (i < size) {                                                                                  // (20) 0.01953
/*18  */         nbits = FFMIN(ff_clz((state >> 8) + 3) ^ 0x1F, 14);                                             // (2) 0.06445
/*22  */         cnt1 = get_unary(b, 0, 8);                                                                      // (7) 0.04297
/*24  */         if (cnt1 < 8) {                                                                                 // (14) 0.03125
/*26  */             value = show_bits(b, nbits);                                                                // (8) 0.04297
/*28  */             if (value <= 1) {                                                                           // (12) 0.03516
/*30  */                 skip_bits(b, nbits - 1);                                                                // (4) 0.05078
/*32  */                 escape = ((1 << nbits) - 1) * cnt1;                                                     // (3) 0.06055
/*34  */             } else {                                                                                    // (16) 0.02734
/*36  */                 skip_bits(b, nbits);                                                                    // (6) 0.04687
/*38  */                 escape = value + ((1 << nbits) - 1) * cnt1 - 1;                                         // (1) 0.06836
/*40  */             }                                                                                           // (19) 0.02344
/*42  */         } else {                                                                                        // (21) 0.01953
/*44  */             escape = get_bits(b, 16);                                                                   // (11) 0.04101
/*46  */         }                                                                                               // (23) 0.01562
/*50  */         value = -((escape + flag) & 1) | 1;                                                             // (10) 0.04101
/*52  */         dst[j++] = value * ((escape + flag + 1) >> 1);                                                  // (5) 0.04883
/*54  */         i++;                                                                                            // (22) 0.01758
/*56  */         if (j == width) {                                                                               // 0.0
/*58  */             j = 0;                                                                                      // 0.0
/*60  */             dst += stride;                                                                              // 0.0
/*62  */         }                                                                                               // 0.0
/*64  */         state = 120 * (escape + flag) + state - (120 * state >> 8);                                     // 0.0
/*66  */         flag = 0;                                                                                       // 0.0
/*70  */         if (state * 4 > 0xFF || i >= size)                                                              // 0.0
/*72  */             continue;                                                                                   // 0.0
/*76  */         nbits = ((state + 8) >> 5) + (state ? ff_clz(state) : 32) - 24;                                 // 0.0
/*78  */         escape = av_mod_uintp2(16383, nbits);                                                           // 0.0
/*80  */         cnt1 = get_unary(b, 0, 8);                                                                      // 0.0
/*82  */         if (cnt1 > 7) {                                                                                 // 0.0
/*84  */             rlen = get_bits(b, 16);                                                                     // 0.0
/*86  */         } else {                                                                                        // 0.0
/*88  */             value = show_bits(b, nbits);                                                                // 0.0
/*90  */             if (value > 1) {                                                                            // 0.0
/*92  */                 skip_bits(b, nbits);                                                                    // 0.0
/*94  */                 rlen = value + escape * cnt1 - 1;                                                       // 0.0
/*96  */             } else {                                                                                    // 0.0
/*98  */                 skip_bits(b, nbits - 1);                                                                // 0.0
/*100 */                 rlen = escape * cnt1;                                                                   // 0.0
/*102 */             }                                                                                           // 0.0
/*104 */         }                                                                                               // 0.0
/*108 */         if (i + rlen > size)                                                                            // 0.0
/*110 */             return AVERROR_INVALIDDATA;                                                                 // 0.0
/*112 */         i += rlen;                                                                                      // 0.0
/*116 */         for (k = 0; k < rlen; k++) {                                                                    // 0.0
/*118 */             dst[j++] = 0;                                                                               // 0.0
/*120 */             if (j == width) {                                                                           // 0.0
/*122 */                 j = 0;                                                                                  // 0.0
/*124 */                 dst += stride;                                                                          // 0.0
/*126 */             }                                                                                           // 0.0
/*128 */         }                                                                                               // 0.0
/*132 */         state = 0;                                                                                      // 0.0
/*134 */         flag = rlen < 0xFFFF ? 1 : 0;                                                                   // 0.0
/*136 */     }                                                                                                   // 0.0
/*140 */     align_get_bits(b);                                                                                  // 0.0
/*142 */     return get_bits_count(b) >> 3;                                                                      // 0.0
/*144 */ }                                                                                                       // 0.0
