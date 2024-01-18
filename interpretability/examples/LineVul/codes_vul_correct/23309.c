// commit message FFmpeg@e477f09d0b (target=1, prob=0.83194935, correct=True): avcodec/pngdec: Check trns more completely
/*0  */ static int decode_trns_chunk(AVCodecContext *avctx, PNGDecContext *s,                          // (8) 0.04688
/*2  */                              uint32_t length)                                                  // (4) 0.06641
/*4  */ {                                                                                              // (19) 0.001953
/*6  */     int v, i;                                                                                  // (17) 0.01562
/*10 */     if (s->color_type == PNG_COLOR_TYPE_PALETTE) {                                             // (10) 0.04492
/*12 */         if (length > 256 || !(s->state & PNG_PLTE))                                            // (9) 0.04687
/*14 */             return AVERROR_INVALIDDATA;                                                        // (12) 0.04102
/*18 */         for (i = 0; i < length; i++) {                                                         // (15) 0.03906
/*20 */             v = bytestream2_get_byte(&s->gb);                                                  // (7) 0.05078
/*22 */             s->palette[i] = (s->palette[i] & 0x00ffffff) | (v << 24);                          // (1) 0.07812
/*24 */         }                                                                                      // (18) 0.01562
/*26 */     } else if (s->color_type == PNG_COLOR_TYPE_GRAY || s->color_type == PNG_COLOR_TYPE_RGB) {  // (2) 0.07227
/*28 */         if ((s->color_type == PNG_COLOR_TYPE_GRAY && length != 2) ||                           // (6) 0.05664
/*30 */             (s->color_type == PNG_COLOR_TYPE_RGB && length != 6))                              // (5) 0.05859
/*32 */             return AVERROR_INVALIDDATA;                                                        // (13) 0.04102
/*36 */         for (i = 0; i < length / 2; i++) {                                                     // (11) 0.04297
/*38 */             /* only use the least significant bits */                                          // (16) 0.03711
/*40 */             v = av_mod_uintp2(bytestream2_get_be16(&s->gb), s->bit_depth);                     // (0) 0.08008
/*44 */             if (s->bit_depth > 8)                                                              // (14) 0.04102
/*46 */                 AV_WB16(&s->transparent_color_be[2 * i], v);                                   // (3) 0.06836
/*48 */             else                                                                               // 0.0
/*50 */                 s->transparent_color_be[i] = v;                                                // 0.0
/*52 */         }                                                                                      // 0.0
/*54 */     } else {                                                                                   // 0.0
/*56 */         return AVERROR_INVALIDDATA;                                                            // 0.0
/*58 */     }                                                                                          // 0.0
/*62 */     bytestream2_skip(&s->gb, 4); /* crc */                                                     // 0.0
/*64 */     s->has_trns = 1;                                                                           // 0.0
/*68 */     return 0;                                                                                  // 0.0
/*70 */ }                                                                                              // 0.0
