// commit message FFmpeg@c3ab0004ae (target=1, prob=0.06019228, correct=False): Revert r31153. It failed to build on: x86_64 / Mac OS X gcc 4.0.1 x86_64 / Linux icc (all) x86_64 / Linux gcc 4.0.4 x86_64 / OpenBSD gcc 3.3.5 x86_64 / Linux suncc 5.10 and there are some reports of crashes.
/*0  */ static inline void RENAME(uyvyToY)(uint8_t *dst, const uint8_t *src, int width, uint32_t *unused)  // (9) 0.07618
/*2  */ {                                                                                                  // (12) 0.001953
/*4  */ #if COMPILE_TEMPLATE_MMX                                                                           // (10) 0.02539
/*6  */     __asm__ volatile(                                                                              // (11) 0.01563
/*8  */         "mov                  %0, %%"REG_a"         \n\t"                                          // (1) 0.0957
/*10 */         "1:                                         \n\t"                                          // (0) 0.1074
/*12 */         "movq  (%1, %%"REG_a",2), %%mm0             \n\t"                                          // (8) 0.08398
/*14 */         "movq 8(%1, %%"REG_a",2), %%mm1             \n\t"                                          // (7) 0.08594
/*16 */         "psrlw                $8, %%mm0             \n\t"                                          // (2) 0.0957
/*18 */         "psrlw                $8, %%mm1             \n\t"                                          // (3) 0.0957
/*20 */         "packuswb          %%mm1, %%mm0             \n\t"                                          // (5) 0.08594
/*22 */         "movq              %%mm0, (%2, %%"REG_a")   \n\t"                                          // (6) 0.08594
/*24 */         "add                  $8, %%"REG_a"         \n\t"                                          // (4) 0.09375
/*26 */         " js                  1b                    \n\t"                                          // 0.0
/*28 */         : : "g" ((x86_reg)-width), "r" (src+width*2), "r" (dst+width)                              // 0.0
/*30 */         : "%"REG_a                                                                                 // 0.0
/*32 */     );                                                                                             // 0.0
/*34 */ #else                                                                                              // 0.0
/*36 */     int i;                                                                                         // 0.0
/*38 */     for (i=0; i<width; i++)                                                                        // 0.0
/*40 */         dst[i]= src[2*i+1];                                                                        // 0.0
/*42 */ #endif                                                                                             // 0.0
/*44 */ }                                                                                                  // 0.0
