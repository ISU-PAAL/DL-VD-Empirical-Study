// commit message FFmpeg@877f76ad33 (target=1, prob=0.98976, correct=True): swscale: Fix use of uninitialized values (bug probably introduced from a marge of libav)
/*0  */ static inline void hyscale_fast_c(SwsContext *c, int16_t *dst, int dstWidth,  // (2) 0.13
/*2  */                                   const uint8_t *src, int srcW, int xInc)     // (0) 0.2197
/*4  */ {                                                                             // (10) 0.004484
/*6  */     int i;                                                                    // (8) 0.02691
/*8  */     unsigned int xpos=0;                                                      // (7) 0.04484
/*10 */     for (i=0;i<dstWidth;i++) {                                                // (4) 0.08072
/*12 */         register unsigned int xx=xpos>>16;                                    // (5) 0.07623
/*14 */         register unsigned int xalpha=(xpos&0xFFFF)>>9;                        // (3) 0.1031
/*16 */         dst[i]= (src[xx]<<7) + (src[xx+1] - src[xx])*xalpha;                  // (1) 0.1614
/*18 */         xpos+=xInc;                                                           // (6) 0.0583
/*20 */     }                                                                         // (9) 0.01794
/*24 */ }                                                                             // (11) 0.004484
