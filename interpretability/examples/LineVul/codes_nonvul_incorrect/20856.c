// commit message FFmpeg@13a099799e (target=0, prob=0.5332913, correct=False): swscale: change prototypes of scaled YUV output functions.
/*0  */ static void RENAME(yuv2yuvX)(SwsContext *c, const int16_t *lumFilter,                     // (9) 0.05664
/*2  */                              const int16_t **lumSrc, int lumFilterSize,                   // (5) 0.08594
/*4  */                              const int16_t *chrFilter, const int16_t **chrUSrc,           // (2) 0.0957
/*6  */                              const int16_t **chrVSrc,                                     // (7) 0.07617
/*8  */                              int chrFilterSize, const int16_t **alpSrc,                   // (4) 0.08789
/*10 */                              uint8_t *dest, uint8_t *uDest, uint8_t *vDest,               // (1) 0.09961
/*12 */                              uint8_t *aDest, int dstW, int chrDstW)                       // (3) 0.0918
/*14 */ {                                                                                         // (14) 0.001953
/*16 */     if (uDest) {                                                                          // (12) 0.01758
/*18 */         x86_reg uv_off = c->uv_off;                                                       // (10) 0.04297
/*20 */         YSCALEYUV2YV12X(CHR_MMX_FILTER_OFFSET, uDest, chrDstW, 0)                         // (6) 0.07812
/*22 */         YSCALEYUV2YV12X(CHR_MMX_FILTER_OFFSET, vDest - uv_off, chrDstW + uv_off, uv_off)  // (0) 0.1035
/*24 */     }                                                                                     // (13) 0.007812
/*26 */     if (CONFIG_SWSCALE_ALPHA && aDest) {                                                  // (11) 0.03906
/*28 */         YSCALEYUV2YV12X(ALP_MMX_FILTER_OFFSET, aDest, dstW, 0)                            // (8) 0.07422
/*30 */     }                                                                                     // 0.0
/*34 */     YSCALEYUV2YV12X(LUM_MMX_FILTER_OFFSET, dest, dstW, 0)                                 // 0.0
/*36 */ }                                                                                         // 0.0
