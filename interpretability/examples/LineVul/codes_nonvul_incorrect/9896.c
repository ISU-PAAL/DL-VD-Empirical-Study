// commit message FFmpeg@c95fefa042 (target=0, prob=0.93565285, correct=False): dsicinvideo: validate buffer offset before copying pixels.
/*0  */ static void cin_decode_lzss(const unsigned char *src, int src_size, unsigned char *dst, int dst_size)  // (1) 0.06641
/*2  */ {                                                                                                      // (22) 0.001953
/*4  */     uint16_t cmd;                                                                                      // (21) 0.01758
/*6  */     int i, sz, offset, code;                                                                           // (18) 0.02539
/*8  */     unsigned char *dst_end = dst + dst_size;                                                           // (14) 0.0332
/*10 */     const unsigned char *src_end = src + src_size;                                                     // (15) 0.0332
/*14 */     while (src < src_end && dst < dst_end) {                                                           // (13) 0.03516
/*16 */         code = *src++;                                                                                 // (19) 0.02344
/*18 */         for (i = 0; i < 8 && src < src_end && dst < dst_end; ++i) {                                    // (2) 0.06445
/*20 */             if (code & (1 << i)) {                                                                     // (11) 0.04102
/*22 */                 *dst++ = *src++;                                                                       // (9) 0.04492
/*24 */             } else {                                                                                   // (17) 0.02734
/*26 */                 cmd = AV_RL16(src); src += 2;                                                          // (5) 0.05469
/*28 */                 offset = cmd >> 4;                                                                     // (12) 0.04102
/*30 */                 sz = (cmd & 0xF) + 2;                                                                  // (6) 0.05469
/*32 */                 /* don't use memcpy/memmove here as the decoding routine (ab)uses */                   // (0) 0.06836
/*34 */                 /* buffer overlappings to repeat bytes in the destination */                           // (7) 0.05078
/*36 */                 sz = FFMIN(sz, dst_end - dst);                                                         // (4) 0.05859
/*38 */                 while (sz--) {                                                                         // (10) 0.04297
/*40 */                     *dst = *(dst - offset - 1);                                                        // (3) 0.0625
/*42 */                     ++dst;                                                                             // (8) 0.04492
/*44 */                 }                                                                                      // (16) 0.03125
/*46 */             }                                                                                          // (20) 0.02344
/*48 */         }                                                                                              // 0.0
/*50 */     }                                                                                                  // 0.0
/*52 */ }                                                                                                      // 0.0
