// commit message FFmpeg@90540c2d5a (target=1, prob=0.993112, correct=True): x86: swscale: fix fragile memory accesses
/*0  */ static inline void RENAME(rgb15to32)(const uint8_t *src, uint8_t *dst, int src_size)  // (6) 0.06641
/*2  */ {                                                                                     // (18) 0.001953
/*4  */     const uint16_t *end;                                                              // (16) 0.02148
/*6  */     const uint16_t *mm_end;                                                           // (12) 0.02539
/*8  */     uint8_t *d = dst;                                                                 // (14) 0.02344
/*10 */     const uint16_t *s = (const uint16_t *)src;                                        // (10) 0.03906
/*12 */     end = s + src_size/2;                                                             // (11) 0.02539
/*14 */     __asm__ volatile(PREFETCH"    %0"::"m"(*s):"memory");                             // (9) 0.05469
/*16 */     __asm__ volatile("pxor    %%mm7,%%mm7    \n\t":::"memory");                       // (7) 0.0625
/*18 */     __asm__ volatile("pcmpeqd %%mm6,%%mm6    \n\t":::"memory");                       // (8) 0.0625
/*20 */     mm_end = end - 3;                                                                 // (17) 0.02148
/*22 */     while (s < mm_end) {                                                              // (13) 0.02344
/*24 */         __asm__ volatile(                                                             // (15) 0.02344
/*26 */             PREFETCH"    32%1           \n\t"                                         // (5) 0.07227
/*28 */             "movq          %1, %%mm0    \n\t"                                         // (2) 0.07422
/*30 */             "movq          %1, %%mm1    \n\t"                                         // (1) 0.07422
/*32 */             "movq          %1, %%mm2    \n\t"                                         // (0) 0.07422
/*34 */             "pand          %2, %%mm0    \n\t"                                         // (4) 0.07227
/*36 */             "pand          %3, %%mm1    \n\t"                                         // (3) 0.07227
/*38 */             "pand          %4, %%mm2    \n\t"                                         // 0.0
/*40 */             "psllq         $3, %%mm0    \n\t"                                         // 0.0
/*42 */             "psrlq         $2, %%mm1    \n\t"                                         // 0.0
/*44 */             "psrlq         $7, %%mm2    \n\t"                                         // 0.0
/*46 */             PACK_RGB32                                                                // 0.0
/*48 */             :"=m"(*d)                                                                 // 0.0
/*50 */             :"m"(*s),"m"(mask15b),"m"(mask15g),"m"(mask15r)                           // 0.0
/*52 */             :"memory");                                                               // 0.0
/*54 */         d += 16;                                                                      // 0.0
/*56 */         s += 4;                                                                       // 0.0
/*58 */     }                                                                                 // 0.0
/*60 */     __asm__ volatile(SFENCE:::"memory");                                              // 0.0
/*62 */     __asm__ volatile(EMMS:::"memory");                                                // 0.0
/*64 */     while (s < end) {                                                                 // 0.0
/*66 */         register uint16_t bgr;                                                        // 0.0
/*68 */         bgr = *s++;                                                                   // 0.0
/*70 */         *d++ = (bgr&0x1F)<<3;                                                         // 0.0
/*72 */         *d++ = (bgr&0x3E0)>>2;                                                        // 0.0
/*74 */         *d++ = (bgr&0x7C00)>>7;                                                       // 0.0
/*76 */         *d++ = 255;                                                                   // 0.0
/*78 */     }                                                                                 // 0.0
/*80 */ }                                                                                     // 0.0
