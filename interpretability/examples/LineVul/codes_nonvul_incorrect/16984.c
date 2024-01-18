// commit message FFmpeg@b00fb157ba (target=0, prob=0.87761563, correct=False): avcodec/sgirledec: fix infinite loop in decode_sgirle8()
/*0  */ static int decode_sgirle8(AVCodecContext *avctx, uint8_t *dst, const uint8_t *src, int src_size, int width, int height, int linesize)  // (0) 0.09375
/*2  */ {                                                                                                                                      // (26) 0.001953
/*4  */     const uint8_t *src_end = src + src_size;                                                                                           // (8) 0.03711
/*6  */     int x = 0, y = 0;                                                                                                                  // (19) 0.02344
/*10 */ #define INC_XY(n) \                                                                                                                    // (23) 0.01758
/*12 */     x += n; \                                                                                                                          // (24) 0.01562
/*14 */     if (x >= width) { \                                                                                                                // (21) 0.02148
/*16 */         y++; \                                                                                                                         // (22) 0.01953
/*18 */         if (y >= height) \                                                                                                             // (14) 0.02734
/*20 */             return 0; \                                                                                                                // (13) 0.0293
/*22 */         x = 0; \                                                                                                                       // (20) 0.02344
/*24 */     }                                                                                                                                  // (25) 0.007812
/*28 */     while (src_end - src >= 2) {                                                                                                       // (15) 0.02734
/*30 */         uint8_t v = *src++;                                                                                                            // (12) 0.03125
/*32 */         if (v > 0 && v < 0xC0) {                                                                                                       // (5) 0.04102
/*34 */             do {                                                                                                                       // (16) 0.02539
/*36 */                 int length = FFMIN(v, width - x);                                                                                      // (3) 0.05273
/*38 */                 memset(dst + y*linesize + x, RGB332_TO_BGR8(*src), length);                                                            // (1) 0.08008
/*40 */                 INC_XY(length);                                                                                                        // (6) 0.04102
/*42 */                 v   -= length;                                                                                                         // (7) 0.04102
/*44 */             } while (v > 0);                                                                                                           // (10) 0.03516
/*46 */             src++;                                                                                                                     // (17) 0.02539
/*48 */         } else if (v >= 0xC1) {                                                                                                        // (9) 0.03711
/*50 */             v -= 0xC0;                                                                                                                 // (11) 0.03516
/*52 */             do {                                                                                                                       // (18) 0.02539
/*54 */                 int length = FFMIN3(v, width - x, src_end - src);                                                                      // (2) 0.06641
/*56 */                 if (src_end - src < length)                                                                                            // (4) 0.04883
/*58 */                     break;                                                                                                             // 0.0
/*60 */                 memcpy_rgb332_to_bgr8(dst + y*linesize + x, src, length);                                                              // 0.0
/*62 */                 INC_XY(length);                                                                                                        // 0.0
/*64 */                 src += length;                                                                                                         // 0.0
/*66 */                 v   -= length;                                                                                                         // 0.0
/*68 */             } while (v > 0);                                                                                                           // 0.0
/*70 */         } else {                                                                                                                       // 0.0
/*72 */             avpriv_request_sample(avctx, "opcode %d", v);                                                                              // 0.0
/*74 */             return AVERROR_PATCHWELCOME;                                                                                               // 0.0
/*76 */         }                                                                                                                              // 0.0
/*78 */     }                                                                                                                                  // 0.0
/*80 */     return 0;                                                                                                                          // 0.0
/*82 */ }                                                                                                                                      // 0.0
