// commit message FFmpeg@d1adad3cca (target=0, prob=0.06539102, correct=True): Merge swscale bloatup This will be cleaned up in the next merge
/*0   */ static inline void RENAME(yuv2yuv1)(SwsContext *c, const int16_t *lumSrc, const int16_t *chrSrc, const int16_t *alpSrc,      // (2) 0.1035
/*2   */                                     uint8_t *dest, uint8_t *uDest, uint8_t *vDest, uint8_t *aDest, long dstW, long chrDstW)  // (0) 0.1504
/*4   */ {                                                                                                                            // (15) 0.001953
/*6   */     int i;                                                                                                                   // (14) 0.01172
/*8   */ #if COMPILE_TEMPLATE_MMX                                                                                                     // (12) 0.02539
/*10  */     if(!(c->flags & SWS_BITEXACT)) {                                                                                         // (10) 0.03711
/*12  */         long p= 4;                                                                                                           // (13) 0.02344
/*14  */         const int16_t *src[4]= {alpSrc + dstW, lumSrc + dstW, chrSrc + chrDstW, chrSrc + VOFW + chrDstW};                    // (1) 0.1152
/*16  */         uint8_t *dst[4]= {aDest, dest, uDest, vDest};                                                                        // (6) 0.05664
/*18  */         x86_reg counter[4]= {dstW, dstW, chrDstW, chrDstW};                                                                  // (5) 0.06836
/*22  */         if (c->flags & SWS_ACCURATE_RND) {                                                                                   // (7) 0.04687
/*24  */             while(p--) {                                                                                                     // (11) 0.0332
/*26  */                 if (dst[p]) {                                                                                                // (9) 0.04492
/*28  */                     __asm__ volatile(                                                                                        // (8) 0.04687
/*30  */                         YSCALEYUV2YV121_ACCURATE                                                                             // (4) 0.07031
/*32  */                         :: "r" (src[p]), "r" (dst[p] + counter[p]),                                                          // (3) 0.08984
/*34  */                         "g" (-counter[p])                                                                                    // 0.0
/*36  */                         : "%"REG_a                                                                                           // 0.0
/*38  */                     );                                                                                                       // 0.0
/*40  */                 }                                                                                                            // 0.0
/*42  */             }                                                                                                                // 0.0
/*44  */         } else {                                                                                                             // 0.0
/*46  */             while(p--) {                                                                                                     // 0.0
/*48  */                 if (dst[p]) {                                                                                                // 0.0
/*50  */                     __asm__ volatile(                                                                                        // 0.0
/*52  */                         YSCALEYUV2YV121                                                                                      // 0.0
/*54  */                         :: "r" (src[p]), "r" (dst[p] + counter[p]),                                                          // 0.0
/*56  */                         "g" (-counter[p])                                                                                    // 0.0
/*58  */                         : "%"REG_a                                                                                           // 0.0
/*60  */                     );                                                                                                       // 0.0
/*62  */                 }                                                                                                            // 0.0
/*64  */             }                                                                                                                // 0.0
/*66  */         }                                                                                                                    // 0.0
/*68  */         return;                                                                                                              // 0.0
/*70  */     }                                                                                                                        // 0.0
/*72  */ #endif                                                                                                                       // 0.0
/*74  */     for (i=0; i<dstW; i++) {                                                                                                 // 0.0
/*76  */         int val= (lumSrc[i]+64)>>7;                                                                                          // 0.0
/*80  */         if (val&256) {                                                                                                       // 0.0
/*82  */             if (val<0) val=0;                                                                                                // 0.0
/*84  */             else       val=255;                                                                                              // 0.0
/*86  */         }                                                                                                                    // 0.0
/*90  */         dest[i]= val;                                                                                                        // 0.0
/*92  */     }                                                                                                                        // 0.0
/*96  */     if (uDest)                                                                                                               // 0.0
/*98  */         for (i=0; i<chrDstW; i++) {                                                                                          // 0.0
/*100 */             int u=(chrSrc[i       ]+64)>>7;                                                                                  // 0.0
/*102 */             int v=(chrSrc[i + VOFW]+64)>>7;                                                                                  // 0.0
/*106 */             if ((u|v)&256) {                                                                                                 // 0.0
/*108 */                 if (u<0)        u=0;                                                                                         // 0.0
/*110 */                 else if (u>255) u=255;                                                                                       // 0.0
/*112 */                 if (v<0)        v=0;                                                                                         // 0.0
/*114 */                 else if (v>255) v=255;                                                                                       // 0.0
/*116 */             }                                                                                                                // 0.0
/*120 */             uDest[i]= u;                                                                                                     // 0.0
/*122 */             vDest[i]= v;                                                                                                     // 0.0
/*124 */         }                                                                                                                    // 0.0
/*128 */     if (CONFIG_SWSCALE_ALPHA && aDest)                                                                                       // 0.0
/*130 */         for (i=0; i<dstW; i++) {                                                                                             // 0.0
/*132 */             int val= (alpSrc[i]+64)>>7;                                                                                      // 0.0
/*134 */             aDest[i]= av_clip_uint8(val);                                                                                    // 0.0
/*136 */         }                                                                                                                    // 0.0
/*138 */ }                                                                                                                            // 0.0
