// commit message FFmpeg@90540c2d5a (target=1, prob=0.99658257, correct=True): x86: swscale: fix fragile memory accesses
/*0   */ static inline void RENAME(rgb24tobgr15)(const uint8_t *src, uint8_t *dst, int src_size)  // (3) 0.07031
/*2   */ {                                                                                        // (20) 0.001953
/*4   */     const uint8_t *s = src;                                                              // (12) 0.02539
/*6   */     const uint8_t *end;                                                                  // (18) 0.02148
/*8   */     const uint8_t *mm_end;                                                               // (13) 0.02539
/*10  */     uint16_t *d = (uint16_t *)dst;                                                       // (11) 0.03711
/*12  */     end = s + src_size;                                                                  // (17) 0.02148
/*14  */     __asm__ volatile(PREFETCH"    %0"::"m"(*src):"memory");                              // (9) 0.05469
/*16  */     __asm__ volatile(                                                                    // (19) 0.01562
/*18  */         "movq          %0, %%mm7    \n\t"                                                // (8) 0.06641
/*20  */         "movq          %1, %%mm6    \n\t"                                                // (7) 0.06641
/*22  */         ::"m"(red_15mask),"m"(green_15mask));                                            // (10) 0.04492
/*24  */     mm_end = end - 11;                                                                   // (16) 0.02148
/*26  */     while (s < mm_end) {                                                                 // (14) 0.02344
/*28  */         __asm__ volatile(                                                                // (15) 0.02344
/*30  */             PREFETCH"    32%1           \n\t"                                            // (2) 0.07227
/*32  */             "movd          %1, %%mm0    \n\t"                                            // (0) 0.07422
/*34  */             "movd         3%1, %%mm3    \n\t"                                            // (1) 0.07422
/*36  */             "punpckldq    6%1, %%mm0    \n\t"                                            // (5) 0.06836
/*38  */             "punpckldq    9%1, %%mm3    \n\t"                                            // (6) 0.06836
/*40  */             "movq       %%mm0, %%mm1    \n\t"                                            // (4) 0.07031
/*42  */             "movq       %%mm0, %%mm2    \n\t"                                            // 0.0
/*44  */             "movq       %%mm3, %%mm4    \n\t"                                            // 0.0
/*46  */             "movq       %%mm3, %%mm5    \n\t"                                            // 0.0
/*48  */             "psrlq         $3, %%mm0    \n\t"                                            // 0.0
/*50  */             "psrlq         $3, %%mm3    \n\t"                                            // 0.0
/*52  */             "pand          %2, %%mm0    \n\t"                                            // 0.0
/*54  */             "pand          %2, %%mm3    \n\t"                                            // 0.0
/*56  */             "psrlq         $6, %%mm1    \n\t"                                            // 0.0
/*58  */             "psrlq         $6, %%mm4    \n\t"                                            // 0.0
/*60  */             "pand       %%mm6, %%mm1    \n\t"                                            // 0.0
/*62  */             "pand       %%mm6, %%mm4    \n\t"                                            // 0.0
/*64  */             "psrlq         $9, %%mm2    \n\t"                                            // 0.0
/*66  */             "psrlq         $9, %%mm5    \n\t"                                            // 0.0
/*68  */             "pand       %%mm7, %%mm2    \n\t"                                            // 0.0
/*70  */             "pand       %%mm7, %%mm5    \n\t"                                            // 0.0
/*72  */             "por        %%mm1, %%mm0    \n\t"                                            // 0.0
/*74  */             "por        %%mm4, %%mm3    \n\t"                                            // 0.0
/*76  */             "por        %%mm2, %%mm0    \n\t"                                            // 0.0
/*78  */             "por        %%mm5, %%mm3    \n\t"                                            // 0.0
/*80  */             "psllq        $16, %%mm3    \n\t"                                            // 0.0
/*82  */             "por        %%mm3, %%mm0    \n\t"                                            // 0.0
/*84  */             MOVNTQ"     %%mm0, %0       \n\t"                                            // 0.0
/*86  */             :"=m"(*d):"m"(*s),"m"(blue_15mask):"memory");                                // 0.0
/*88  */         d += 4;                                                                          // 0.0
/*90  */         s += 12;                                                                         // 0.0
/*92  */     }                                                                                    // 0.0
/*94  */     __asm__ volatile(SFENCE:::"memory");                                                 // 0.0
/*96  */     __asm__ volatile(EMMS:::"memory");                                                   // 0.0
/*98  */     while (s < end) {                                                                    // 0.0
/*100 */         const int b = *s++;                                                              // 0.0
/*102 */         const int g = *s++;                                                              // 0.0
/*104 */         const int r = *s++;                                                              // 0.0
/*106 */         *d++ = (b>>3) | ((g&0xF8)<<2) | ((r&0xF8)<<7);                                   // 0.0
/*108 */     }                                                                                    // 0.0
/*110 */ }                                                                                        // 0.0
