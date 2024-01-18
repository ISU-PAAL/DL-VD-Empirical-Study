// commit message FFmpeg@c56e71309e (target=1, prob=0.67737675, correct=True): In gif encoder, fix uninitialized value, patch by Clément Bœsch, ubitux at gmail dot com
/*0  */ static int gif_image_write_image(AVCodecContext *avctx,               // (11) 0.03516
/*2  */                                  uint8_t **bytestream, uint8_t *end,  // (0) 0.09375
/*4  */                                  const uint8_t *buf, int linesize)    // (1) 0.08594
/*6  */ {                                                                     // (24) 0.001953
/*8  */     GIFContext *s = avctx->priv_data;                                 // (15) 0.0293
/*10 */     int len, height;                                                  // (20) 0.01562
/*12 */     const uint8_t *ptr;                                               // (17) 0.02148
/*14 */     /* image block */                                                 // (21) 0.01367
/*18 */     bytestream_put_byte(bytestream, 0x2c);                            // (9) 0.03906
/*20 */     bytestream_put_le16(bytestream, 0);                               // (12) 0.03516
/*22 */     bytestream_put_le16(bytestream, 0);                               // (13) 0.03516
/*24 */     bytestream_put_le16(bytestream, avctx->width);                    // (7) 0.04102
/*26 */     bytestream_put_le16(bytestream, avctx->height);                   // (8) 0.04102
/*28 */     bytestream_put_byte(bytestream, 0x00); /* flags */                // (6) 0.04297
/*30 */     /* no local clut */                                               // (19) 0.01563
/*34 */     bytestream_put_byte(bytestream, 0x08);                            // (10) 0.03711
/*38 */     ff_lzw_encode_init(s->lzw, s->buf, avctx->width*avctx->height,    // (3) 0.06641
/*40 */                        12, FF_LZW_GIF, put_bits);                     // (2) 0.07227
/*44 */     ptr = buf;                                                        // (22) 0.01367
/*46 */     for (height = avctx->height; height--;) {                         // (14) 0.0332
/*48 */         len += ff_lzw_encode(s->lzw, ptr, avctx->width);              // (4) 0.06055
/*50 */         ptr += linesize;                                              // (16) 0.02344
/*52 */     }                                                                 // (23) 0.007812
/*54 */     len += ff_lzw_encode_flush(s->lzw, flush_put_bits);               // (5) 0.05469
/*58 */     ptr = s->buf;                                                     // (18) 0.01758
/*60 */     while (len > 0) {                                                 // 0.0
/*62 */         int size = FFMIN(255, len);                                   // 0.0
/*64 */         bytestream_put_byte(bytestream, size);                        // 0.0
/*66 */         if (end - *bytestream < size)                                 // 0.0
/*68 */             return -1;                                                // 0.0
/*70 */         bytestream_put_buffer(bytestream, ptr, size);                 // 0.0
/*72 */         ptr += size;                                                  // 0.0
/*74 */         len -= size;                                                  // 0.0
/*76 */     }                                                                 // 0.0
/*78 */     bytestream_put_byte(bytestream, 0x00); /* end of image block */   // 0.0
/*80 */     bytestream_put_byte(bytestream, 0x3b);                            // 0.0
/*82 */     return 0;                                                         // 0.0
/*84 */ }                                                                     // 0.0
