// commit message FFmpeg@83fd377c94 (target=0, prob=0.05093974, correct=True): j2k/jpeg2000: merge float DWT and related code
/*0  */ static int put_cod(Jpeg2000EncoderContext *s)                                       // (15) 0.03363
/*2  */ {                                                                                   // (22) 0.002242
/*4  */     Jpeg2000CodingStyle *codsty = &s->codsty;                                       // (13) 0.0426
/*8  */     if (s->buf_end - s->buf < 14)                                                   // (14) 0.03812
/*10 */         return -1;                                                                  // (16) 0.02466
/*14 */     bytestream_put_be16(&s->buf, JPEG2000_COD);                                     // (7) 0.04933
/*16 */     bytestream_put_be16(&s->buf, 12); // Lcod                                       // (10) 0.04709
/*18 */     bytestream_put_byte(&s->buf, 0);  // Scod                                       // (11) 0.04709
/*20 */     // SGcod                                                                        // (19) 0.01345
/*22 */     bytestream_put_byte(&s->buf, 0); // progression level                           // (12) 0.04484
/*24 */     bytestream_put_be16(&s->buf, 1); // num of layers                               // (6) 0.04933
/*26 */     if(s->avctx->pix_fmt == AV_PIX_FMT_YUV444P){                                    // (3) 0.06502
/*28 */         bytestream_put_byte(&s->buf, 2); // ICT                                     // (4) 0.05381
/*30 */     }else{                                                                          // (20) 0.01345
/*32 */         bytestream_put_byte(&s->buf, 0); // unspecified                             // (5) 0.05157
/*34 */     }                                                                               // (21) 0.008969
/*36 */     // SPcod                                                                        // (17) 0.01345
/*38 */     bytestream_put_byte(&s->buf, codsty->nreslevels - 1); // num of decomp. levels  // (2) 0.06726
/*40 */     bytestream_put_byte(&s->buf, codsty->log2_cblk_width-2); // cblk width          // (0) 0.07623
/*42 */     bytestream_put_byte(&s->buf, codsty->log2_cblk_height-2); // cblk height        // (1) 0.07623
/*44 */     bytestream_put_byte(&s->buf, 0); // cblk style                                  // (9) 0.04933
/*46 */     bytestream_put_byte(&s->buf, codsty->transform); // transformation              // (8) 0.04933
/*48 */     return 0;                                                                       // (18) 0.01345
/*50 */ }                                                                                   // (23) 0.002242
