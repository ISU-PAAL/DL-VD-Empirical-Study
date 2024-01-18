// commit message FFmpeg@c3ab0004ae (target=1, prob=0.027401766, correct=False): Revert r31153. It failed to build on: x86_64 / Mac OS X gcc 4.0.1 x86_64 / Linux icc (all) x86_64 / Linux gcc 4.0.4 x86_64 / OpenBSD gcc 3.3.5 x86_64 / Linux suncc 5.10 and there are some reports of crashes.
/*0  */ static inline void RENAME(bgr24ToY)(uint8_t *dst, const uint8_t *src, int width, uint32_t *unused)  // (1) 0.1569
/*2  */ {                                                                                                   // (12) 0.003922
/*4  */ #if COMPILE_TEMPLATE_MMX                                                                            // (8) 0.05098
/*6  */     RENAME(bgr24ToY_mmx)(dst, src, width, PIX_FMT_BGR24);                                           // (2) 0.1294
/*8  */ #else                                                                                               // (11) 0.007843
/*10 */     int i;                                                                                          // (9) 0.02353
/*12 */     for (i=0; i<width; i++) {                                                                       // (6) 0.06275
/*14 */         int b= src[i*3+0];                                                                          // (3) 0.07059
/*16 */         int g= src[i*3+1];                                                                          // (5) 0.07059
/*18 */         int r= src[i*3+2];                                                                          // (4) 0.07059
/*22 */         dst[i]= ((RY*r + GY*g + BY*b + (33<<(RGB2YUV_SHIFT-1)))>>RGB2YUV_SHIFT);                    // (0) 0.1882
/*24 */     }                                                                                               // (10) 0.01569
/*26 */ #endif /* COMPILE_TEMPLATE_MMX */                                                                   // (7) 0.05882
/*28 */ }                                                                                                   // (13) 0.003922
