// commit message FFmpeg@d1adad3cca (target=0, prob=0.07157836, correct=True): Merge swscale bloatup This will be cleaned up in the next merge
/*0  */ static inline void RENAME(yuy2ToUV)(uint8_t *dstU, uint8_t *dstV, const uint8_t *src1, const uint8_t *src2, long width, uint32_t *unused)  // (0) 0.1172
/*2  */ {                                                                                                                                          // (11) 0.001953
/*4  */ #if COMPILE_TEMPLATE_MMX                                                                                                                   // (9) 0.02539
/*6  */     __asm__ volatile(                                                                                                                      // (10) 0.01563
/*8  */         "movq "MANGLE(bm01010101)", %%mm4           \n\t"                                                                                  // (8) 0.07812
/*10 */         "mov                    %0, %%"REG_a"       \n\t"                                                                                  // (4) 0.0957
/*12 */         "1:                                         \n\t"                                                                                  // (1) 0.1074
/*14 */         "movq    (%1, %%"REG_a",4), %%mm0           \n\t"                                                                                  // (7) 0.08398
/*16 */         "movq   8(%1, %%"REG_a",4), %%mm1           \n\t"                                                                                  // (6) 0.08594
/*18 */         "psrlw                  $8, %%mm0           \n\t"                                                                                  // (3) 0.0957
/*20 */         "psrlw                  $8, %%mm1           \n\t"                                                                                  // (2) 0.0957
/*22 */         "packuswb            %%mm1, %%mm0           \n\t"                                                                                  // (5) 0.08594
/*24 */         "movq                %%mm0, %%mm1           \n\t"                                                                                  // 0.0
/*26 */         "psrlw                  $8, %%mm0           \n\t"                                                                                  // 0.0
/*28 */         "pand                %%mm4, %%mm1           \n\t"                                                                                  // 0.0
/*30 */         "packuswb            %%mm0, %%mm0           \n\t"                                                                                  // 0.0
/*32 */         "packuswb            %%mm1, %%mm1           \n\t"                                                                                  // 0.0
/*34 */         "movd                %%mm0, (%3, %%"REG_a") \n\t"                                                                                  // 0.0
/*36 */         "movd                %%mm1, (%2, %%"REG_a") \n\t"                                                                                  // 0.0
/*38 */         "add                    $4, %%"REG_a"       \n\t"                                                                                  // 0.0
/*40 */         " js                    1b                  \n\t"                                                                                  // 0.0
/*42 */         : : "g" ((x86_reg)-width), "r" (src1+width*4), "r" (dstU+width), "r" (dstV+width)                                                  // 0.0
/*44 */         : "%"REG_a                                                                                                                         // 0.0
/*46 */     );                                                                                                                                     // 0.0
/*48 */ #else                                                                                                                                      // 0.0
/*50 */     int i;                                                                                                                                 // 0.0
/*52 */     for (i=0; i<width; i++) {                                                                                                              // 0.0
/*54 */         dstU[i]= src1[4*i + 1];                                                                                                            // 0.0
/*56 */         dstV[i]= src1[4*i + 3];                                                                                                            // 0.0
/*58 */     }                                                                                                                                      // 0.0
/*60 */ #endif                                                                                                                                     // 0.0
/*62 */     assert(src1 == src2);                                                                                                                  // 0.0
/*64 */ }                                                                                                                                          // 0.0
