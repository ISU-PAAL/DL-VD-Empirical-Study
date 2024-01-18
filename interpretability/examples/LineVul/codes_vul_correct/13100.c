// commit message FFmpeg@c3ab0004ae (target=1, prob=0.7208454, correct=True): Revert r31153. It failed to build on: x86_64 / Mac OS X gcc 4.0.1 x86_64 / Linux icc (all) x86_64 / Linux gcc 4.0.4 x86_64 / OpenBSD gcc 3.3.5 x86_64 / Linux suncc 5.10 and there are some reports of crashes.
/*0  */ inline static void RENAME(hcscale)(SwsContext *c, uint16_t *dst, int dstWidth, const uint8_t *src1, const uint8_t *src2,  // (4) 0.0918
/*2  */                                    int srcW, int xInc, const int16_t *hChrFilter,                                         // (0) 0.1035
/*4  */                                    const int16_t *hChrFilterPos, int hChrFilterSize,                                      // (1) 0.1035
/*6  */                                    uint8_t *formatConvBuffer,                                                             // (5) 0.08594
/*8  */                                    uint32_t *pal)                                                                         // (6) 0.08008
/*10 */ {                                                                                                                         // (16) 0.001953
/*14 */     src1 += c->chrSrcOffset;                                                                                              // (13) 0.02734
/*16 */     src2 += c->chrSrcOffset;                                                                                              // (14) 0.02734
/*20 */     if (c->chrToYV12) {                                                                                                   // (10) 0.0293
/*22 */         c->chrToYV12(formatConvBuffer, formatConvBuffer+VOFW, src1, src2, srcW, pal);                                     // (7) 0.08008
/*24 */         src1= formatConvBuffer;                                                                                           // (11) 0.0293
/*26 */         src2= formatConvBuffer+VOFW;                                                                                      // (8) 0.03711
/*28 */     }                                                                                                                     // (15) 0.007812
/*32 */     if (!c->hcscale_fast) {                                                                                               // (12) 0.02734
/*34 */         c->hScale(dst     , dstWidth, src1, srcW, xInc, hChrFilter, hChrFilterPos, hChrFilterSize);                       // (3) 0.09375
/*36 */         c->hScale(dst+VOFW, dstWidth, src2, srcW, xInc, hChrFilter, hChrFilterPos, hChrFilterSize);                       // (2) 0.09375
/*38 */     } else { // fast bilinear upscale / crap downscale                                                                    // (9) 0.03125
/*40 */         c->hcscale_fast(c, dst, dstWidth, src1, src2, srcW, xInc);                                                        // 0.0
/*42 */     }                                                                                                                     // 0.0
/*46 */     if (c->chrConvertRange)                                                                                               // 0.0
/*48 */         c->chrConvertRange(dst, dstWidth);                                                                                // 0.0
/*50 */ }                                                                                                                         // 0.0
