// commit message FFmpeg@39d607e5bb (target=1, prob=0.6377835, correct=True): swscale: Commits that could not be pulled earlier due to bugs #2
/*0  */ static inline void RENAME(yuv2yuvX_ar)(SwsContext *c, const int16_t *lumFilter,                 // (8) 0.0625
/*2  */                                        const int16_t **lumSrc, int lumFilterSize,               // (4) 0.1055
/*4  */                                        const int16_t *chrFilter, const int16_t **chrUSrc,       // (1) 0.1152
/*6  */                                        const int16_t **chrVSrc,                                 // (6) 0.0957
/*8  */                                        int chrFilterSize, const int16_t **alpSrc,               // (3) 0.1074
/*10 */                                        uint8_t *dest, uint8_t *uDest, uint8_t *vDest,           // (0) 0.1191
/*12 */                                        uint8_t *aDest, long dstW, long chrDstW)                 // (2) 0.1113
/*14 */ {                                                                                               // (11) 0.001953
/*16 */     if (uDest) {                                                                                // (9) 0.01758
/*18 */         YSCALEYUV2YV12X_ACCURATE(CHR_MMX_FILTER_OFFSET, uDest, chrDstW, 0)                      // (7) 0.08594
/*20 */         YSCALEYUV2YV12X_ACCURATE(CHR_MMX_FILTER_OFFSET, vDest, chrDstW + c->uv_off, c->uv_off)  // (5) 0.1055
/*22 */     }                                                                                           // (10) 0.007812
/*24 */     if (CONFIG_SWSCALE_ALPHA && aDest) {                                                        // 0.0
/*26 */         YSCALEYUV2YV12X_ACCURATE(ALP_MMX_FILTER_OFFSET, aDest, dstW, 0)                         // 0.0
/*28 */     }                                                                                           // 0.0
/*32 */     YSCALEYUV2YV12X_ACCURATE(LUM_MMX_FILTER_OFFSET, dest, dstW, 0)                              // 0.0
/*34 */ }                                                                                               // 0.0
