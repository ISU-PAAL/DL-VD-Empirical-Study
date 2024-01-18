// commit message FFmpeg@d0dce15da3 (target=1, prob=0.32830292, correct=False): quickdraw: Make the palette opaque
/*0  */ static int parse_palette(AVCodecContext *avctx, GetByteContext *gbc,     // (6) 0.0514
/*2  */                          uint32_t *pal, int colors)                      // (1) 0.07944
/*4  */ {                                                                        // (21) 0.002336
/*6  */     int i;                                                               // (18) 0.01402
/*10 */     for (i = 0; i <= colors; i++) {                                      // (14) 0.03738
/*12 */         uint8_t r, g, b;                                                 // (13) 0.03972
/*14 */         unsigned int idx = bytestream2_get_be16(gbc); /* color index */  // (2) 0.06776
/*16 */         if (idx > 255) {                                                 // (15) 0.03505
/*18 */             av_log(avctx, AV_LOG_WARNING,                                // (4) 0.05607
/*20 */                    "Palette index out of range: %u\n", idx);             // (0) 0.07944
/*22 */             bytestream2_skip(gbc, 6);                                    // (5) 0.05374
/*24 */             continue;                                                    // (16) 0.03037
/*26 */         }                                                                // (17) 0.01869
/*28 */         r = bytestream2_get_byte(gbc);                                   // (7) 0.04907
/*30 */         bytestream2_skip(gbc, 1);                                        // (10) 0.04439
/*32 */         g = bytestream2_get_byte(gbc);                                   // (8) 0.04907
/*34 */         bytestream2_skip(gbc, 1);                                        // (11) 0.04439
/*36 */         b = bytestream2_get_byte(gbc);                                   // (9) 0.04907
/*38 */         bytestream2_skip(gbc, 1);                                        // (12) 0.04439
/*40 */         pal[idx] = (r << 16) | (g << 8) | b;                             // (3) 0.06308
/*42 */     }                                                                    // (20) 0.009346
/*44 */     return 0;                                                            // (19) 0.01402
/*46 */ }                                                                        // (22) 0.002336
