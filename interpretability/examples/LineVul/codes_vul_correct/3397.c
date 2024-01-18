// commit message FFmpeg@2254b559cb (target=1, prob=0.89359236, correct=True): swscale: make filterPos 32bit.
/*0  */ static av_always_inline void hcscale(SwsContext *c, int16_t *dst1, int16_t *dst2, int dstWidth,  // (6) 0.07617
/*2  */                                      const uint8_t *src_in[4],                                   // (3) 0.09375
/*4  */                                      int srcW, int xInc, const int16_t *hChrFilter,              // (0) 0.1074
/*6  */                                      const int16_t *hChrFilterPos, int hChrFilterSize,           // (1) 0.1074
/*8  */                                      uint8_t *formatConvBuffer, uint32_t *pal)                   // (2) 0.1035
/*10 */ {                                                                                                // (14) 0.001953
/*12 */     const uint8_t *src1 = src_in[1], *src2 = src_in[2];                                          // (9) 0.05469
/*14 */     if (c->chrToYV12) {                                                                          // (11) 0.0293
/*16 */         uint8_t *buf2 = formatConvBuffer + FFALIGN(srcW * FFALIGN(c->srcBpc, 8) >> 3, 16);       // (4) 0.08594
/*18 */         c->chrToYV12(formatConvBuffer, buf2, src1, src2, srcW, pal);                             // (7) 0.06836
/*20 */         src1= formatConvBuffer;                                                                  // (12) 0.0293
/*22 */         src2= buf2;                                                                              // (13) 0.02539
/*24 */     } else if (c->readChrPlanar) {                                                               // (10) 0.03125
/*26 */         uint8_t *buf2 = formatConvBuffer + FFALIGN(srcW * FFALIGN(c->srcBpc, 8) >> 3, 16);       // (5) 0.08594
/*28 */         c->readChrPlanar(formatConvBuffer, buf2, src_in, srcW);                                  // (8) 0.05859
/*30 */         src1= formatConvBuffer;                                                                  // 0.0
/*32 */         src2= buf2;                                                                              // 0.0
/*34 */     }                                                                                            // 0.0
/*38 */     if (!c->hcscale_fast) {                                                                      // 0.0
/*40 */         c->hcScale(c, dst1, dstWidth, src1, hChrFilter, hChrFilterPos, hChrFilterSize);          // 0.0
/*42 */         c->hcScale(c, dst2, dstWidth, src2, hChrFilter, hChrFilterPos, hChrFilterSize);          // 0.0
/*44 */     } else { // fast bilinear upscale / crap downscale                                           // 0.0
/*46 */         c->hcscale_fast(c, dst1, dst2, dstWidth, src1, src2, srcW, xInc);                        // 0.0
/*48 */     }                                                                                            // 0.0
/*52 */     if (c->chrConvertRange)                                                                      // 0.0
/*54 */         c->chrConvertRange(dst1, dst2, dstWidth);                                                // 0.0
/*56 */ }                                                                                                // 0.0
