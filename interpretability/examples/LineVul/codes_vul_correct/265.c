// commit message FFmpeg@478f1c3d5e (target=1, prob=0.72696084, correct=True): png: split header state and data state in two separate variables.
/*0  */ static int decode_plte_chunk(AVCodecContext *avctx, PNGDecContext *s,  // (2) 0.0678
/*2  */                              uint32_t length)                          // (1) 0.09605
/*4  */ {                                                                      // (18) 0.002825
/*6  */     int n, i, r, g, b;                                                 // (11) 0.03955
/*10 */     if ((length % 3) != 0 || length > 256 * 3)                         // (8) 0.05085
/*12 */         return AVERROR_INVALIDDATA;                                    // (9) 0.04802
/*14 */     /* read the palette */                                             // (15) 0.0226
/*16 */     n = length / 3;                                                    // (14) 0.02542
/*18 */     for (i = 0; i < n; i++) {                                          // (10) 0.0452
/*20 */         r = bytestream2_get_byte(&s->gb);                              // (5) 0.06215
/*22 */         g = bytestream2_get_byte(&s->gb);                              // (6) 0.06215
/*24 */         b = bytestream2_get_byte(&s->gb);                              // (7) 0.06215
/*26 */         s->palette[i] = (0xFFU << 24) | (r << 16) | (g << 8) | b;      // (0) 0.1073
/*28 */     }                                                                  // (17) 0.0113
/*30 */     for (; i < 256; i++)                                               // (13) 0.0339
/*32 */         s->palette[i] = (0xFFU << 24);                                 // (4) 0.06497
/*34 */     s->state |= PNG_PLTE;                                              // (12) 0.03672
/*36 */     bytestream2_skip(&s->gb, 4);     /* crc */                         // (3) 0.0678
/*40 */     return 0;                                                          // (16) 0.01695
/*42 */ }                                                                      // (19) 0.002825
