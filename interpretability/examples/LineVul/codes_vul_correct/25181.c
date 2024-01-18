// commit message FFmpeg@0409d33311 (target=1, prob=0.978207, correct=True): avcodec/hevcdsp_template: Fix undefined shift in put_hevc_epel_bi_w_h()
/*0  */ static void FUNC(put_hevc_epel_bi_w_h)(uint8_t *_dst, ptrdiff_t _dststride, uint8_t *_src, ptrdiff_t _srcstride,  // (1) 0.1074
/*2  */                                        int16_t *src2,                                                             // (3) 0.08984
/*4  */                                        int height, int denom, int wx0, int wx1,                                   // (2) 0.1074
/*6  */                                        int ox0, int ox1, intptr_t mx, intptr_t my, int width)                     // (0) 0.1211
/*8  */ {                                                                                                                 // (16) 0.001953
/*10 */     int x, y;                                                                                                     // (15) 0.01562
/*12 */     pixel *src = (pixel *)_src;                                                                                   // (14) 0.02539
/*14 */     ptrdiff_t srcstride  = _srcstride / sizeof(pixel);                                                            // (8) 0.04102
/*16 */     pixel *dst          = (pixel *)_dst;                                                                          // (5) 0.04688
/*18 */     ptrdiff_t dststride = _dststride / sizeof(pixel);                                                             // (9) 0.04102
/*20 */     const int8_t *filter = ff_hevc_epel_filters[mx - 1];                                                          // (4) 0.05078
/*22 */     int shift = 14 + 1 - BIT_DEPTH;                                                                               // (13) 0.0293
/*24 */     int log2Wd = denom + shift - 1;                                                                               // (11) 0.03125
/*28 */     ox0     = ox0 * (1 << (BIT_DEPTH - 8));                                                                       // (7) 0.04687
/*30 */     ox1     = ox1 * (1 << (BIT_DEPTH - 8));                                                                       // (6) 0.04687
/*32 */     for (y = 0; y < height; y++) {                                                                                // (12) 0.03125
/*34 */         for (x = 0; x < width; x++)                                                                               // (10) 0.03711
/*36 */             dst[x] = av_clip_pixel(((EPEL_FILTER(src, 1) >> (BIT_DEPTH - 8)) * wx1 + src2[x] * wx0 +              // 0.0
/*38 */                                     ((ox0 + ox1 + 1) << log2Wd)) >> (log2Wd + 1));                                // 0.0
/*40 */         src  += srcstride;                                                                                        // 0.0
/*42 */         dst  += dststride;                                                                                        // 0.0
/*44 */         src2 += MAX_PB_SIZE;                                                                                      // 0.0
/*46 */     }                                                                                                             // 0.0
/*48 */ }                                                                                                                 // 0.0
