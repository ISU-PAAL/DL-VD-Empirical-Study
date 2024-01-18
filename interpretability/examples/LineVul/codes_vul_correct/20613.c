// commit message FFmpeg@2254b559cb (target=1, prob=0.7637303, correct=True): swscale: make filterPos 32bit.
/*0  */ static av_always_inline void hyscale(SwsContext *c, int16_t *dst, int dstWidth,                           // (7) 0.05664
/*2  */                                      const uint8_t *src_in[4], int srcW, int xInc,                        // (0) 0.1094
/*4  */                                      const int16_t *hLumFilter,                                           // (4) 0.0918
/*6  */                                      const int16_t *hLumFilterPos, int hLumFilterSize,                    // (1) 0.1074
/*8  */                                      uint8_t *formatConvBuffer,                                           // (5) 0.08984
/*10 */                                      uint32_t *pal, int isAlpha)                                          // (3) 0.0918
/*12 */ {                                                                                                         // (14) 0.001953
/*14 */     void (*toYV12)(uint8_t *, const uint8_t *, int, uint32_t *) = isAlpha ? c->alpToYV12 : c->lumToYV12;  // (2) 0.1016
/*16 */     void (*convertRange)(int16_t *, int) = isAlpha ? NULL : c->lumConvertRange;                           // (6) 0.06055
/*18 */     const uint8_t *src = src_in[isAlpha ? 3 : 0];                                                         // (10) 0.04297
/*22 */     if (toYV12) {                                                                                         // (13) 0.02148
/*24 */         toYV12(formatConvBuffer, src, srcW, pal);                                                         // (9) 0.04688
/*26 */         src= formatConvBuffer;                                                                            // (12) 0.02734
/*28 */     } else if (c->readLumPlanar && !isAlpha) {                                                            // (11) 0.03906
/*30 */         c->readLumPlanar(formatConvBuffer, src_in, srcW);                                                 // (8) 0.05273
/*32 */         src = formatConvBuffer;                                                                           // 0.0
/*34 */     }                                                                                                     // 0.0
/*38 */     if (!c->hyscale_fast) {                                                                               // 0.0
/*40 */         c->hyScale(c, dst, dstWidth, src, hLumFilter, hLumFilterPos, hLumFilterSize);                     // 0.0
/*42 */     } else { // fast bilinear upscale / crap downscale                                                    // 0.0
/*44 */         c->hyscale_fast(c, dst, dstWidth, src, srcW, xInc);                                               // 0.0
/*46 */     }                                                                                                     // 0.0
/*50 */     if (convertRange)                                                                                     // 0.0
/*52 */         convertRange(dst, dstWidth);                                                                      // 0.0
/*54 */ }                                                                                                         // 0.0
