// commit message FFmpeg@d6945aeee4 (target=1, prob=0.98950803, correct=True): avcodec/h264addpx_template: Fixes integer overflows
/*0  */ static void FUNCC(ff_h264_add_pixels8)(uint8_t *_dst, int16_t *_src, int stride)  // (0) 0.118
/*2  */ {                                                                                 // (18) 0.003279
/*4  */     int i;                                                                        // (16) 0.01967
/*6  */     pixel *dst = (pixel *) _dst;                                                  // (12) 0.04918
/*8  */     dctcoef *src = (dctcoef *) _src;                                              // (2) 0.0623
/*10 */     stride /= sizeof(pixel);                                                      // (15) 0.03279
/*14 */     for (i = 0; i < 8; i++) {                                                     // (3) 0.05246
/*16 */         dst[0] += src[0];                                                         // (4) 0.05246
/*18 */         dst[1] += src[1];                                                         // (5) 0.05246
/*20 */         dst[2] += src[2];                                                         // (6) 0.05246
/*22 */         dst[3] += src[3];                                                         // (7) 0.05246
/*24 */         dst[4] += src[4];                                                         // (8) 0.05246
/*26 */         dst[5] += src[5];                                                         // (9) 0.05246
/*28 */         dst[6] += src[6];                                                         // (10) 0.05246
/*30 */         dst[7] += src[7];                                                         // (11) 0.05246
/*34 */         dst += stride;                                                            // (13) 0.03607
/*36 */         src += 8;                                                                 // (14) 0.03607
/*38 */     }                                                                             // (17) 0.01311
/*42 */     memset(_src, 0, sizeof(dctcoef) * 64);                                        // (1) 0.06557
/*44 */ }                                                                                 // (19) 0.003279
