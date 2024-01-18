// commit message FFmpeg@7e7e594092 (target=0, prob=0.28960314, correct=True): almost exhaustive image conversion support
/*0  */ static void rgb24_to_yuv444p(AVPicture *dst, AVPicture *src,  // (4) 0.05488
/*2  */                              int width, int height)           // (0) 0.06911
/*4  */ {                                                             // (26) 0.002033
/*6  */     int src_wrap, x, y;                                       // (17) 0.02439
/*8  */     int r, g, b;                                              // (23) 0.02033
/*10 */     uint8_t *lum, *cb, *cr;                                   // (11) 0.03455
/*12 */     const uint8_t *p;                                         // (19) 0.02236
/*16 */     lum = dst->data[0];                                       // (20) 0.02236
/*18 */     cb = dst->data[1];                                        // (18) 0.02439
/*20 */     cr = dst->data[2];                                        // (21) 0.02236
/*24 */     src_wrap = src->linesize[0] - width * BPP;                // (6) 0.04065
/*26 */     p = src->data[0];                                         // (22) 0.02236
/*28 */     for(y=0;y<height;y++) {                                   // (12) 0.03252
/*30 */         for(x=0;x<width;x++) {                                // (7) 0.04065
/*32 */             RGB_IN(r, g, b, p);                               // (5) 0.04675
/*34 */             lum[0] = RGB_TO_Y_CCIR(r, g, b);                  // (3) 0.06301
/*36 */             cb[0] = RGB_TO_U_CCIR(r, g, b, 0);                // (1) 0.06911
/*38 */             cr[0] = RGB_TO_V_CCIR(r, g, b, 0);                // (2) 0.06707
/*40 */             cb++;                                             // (13) 0.02846
/*42 */             cr++;                                             // (14) 0.02642
/*44 */             lum++;                                            // (15) 0.02642
/*46 */         }                                                     // (24) 0.01626
/*48 */         p += src_wrap;                                        // (16) 0.02642
/*50 */         lum += dst->linesize[0] - width;                      // (9) 0.03862
/*52 */         cb += dst->linesize[1] - width;                       // (8) 0.04065
/*54 */         cr += dst->linesize[2] - width;                       // (10) 0.03862
/*56 */     }                                                         // (25) 0.00813
/*58 */ }                                                             // (27) 0.002033
