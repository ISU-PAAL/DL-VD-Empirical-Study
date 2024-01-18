// commit message FFmpeg@49cf36f4e3 (target=1, prob=0.8562788, correct=True): sanm: fix undefined behaviour on big-endian.
/*0  */ static int decode_5(SANMVideoContext *ctx)    // (4) 0.06341
/*2  */ {                                             // (15) 0.004878
/*4  */ #if HAVE_BIGENDIAN                            // (9) 0.03902
/*6  */     uint16_t *frm;                            // (7) 0.05366
/*8  */     int npixels;                              // (11) 0.03415
/*10 */ #endif                                        // (13) 0.009756
/*12 */     uint8_t *dst = (uint8_t*)ctx->frm0;       // (0) 0.1122
/*16 */     if (rle_decode(ctx, dst, ctx->buf_size))  // (1) 0.1073
/*18 */         return AVERROR_INVALIDDATA;           // (3) 0.08293
/*22 */ #if HAVE_BIGENDIAN                            // (10) 0.03902
/*24 */     npixels = ctx->npixels;                   // (6) 0.05854
/*26 */     frm = ctx->frm0;                          // (5) 0.06341
/*28 */     while (npixels--)                         // (8) 0.0439
/*30 */         *frm++ = av_bswap16(*frm);            // (2) 0.1073
/*32 */ #endif                                        // (14) 0.009756
/*36 */     return 0;                                 // (12) 0.02927
/*38 */ }                                             // (16) 0.004878
