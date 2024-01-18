// commit message FFmpeg@92fabca427 (target=0, prob=0.06778269, correct=True): avcodec/x86/hpeldsp_rnd_template: silence -Wunused-function on --disable-mmx
/*0  */ static void DEF(put, pixels16_x2)(uint8_t *block, const uint8_t *pixels, ptrdiff_t line_size, int h)  // (1) 0.07617
/*2  */ {                                                                                                     // (14) 0.001953
/*4  */     MOVQ_BFE(mm6);                                                                                    // (12) 0.02344
/*6  */     __asm__ volatile(                                                                                 // (13) 0.01563
/*8  */         "lea        (%3, %3), %%"REG_a" \n\t"                                                         // (11) 0.06641
/*10 */         ".p2align 3                     \n\t"                                                         // (3) 0.07227
/*12 */         "1:                             \n\t"                                                         // (0) 0.08398
/*14 */         "movq   (%1), %%mm0             \n\t"                                                         // (7) 0.07031
/*16 */         "movq   1(%1), %%mm1            \n\t"                                                         // (6) 0.07227
/*18 */         "movq   (%1, %3), %%mm2         \n\t"                                                         // (10) 0.06836
/*20 */         "movq   1(%1, %3), %%mm3        \n\t"                                                         // (9) 0.07031
/*22 */         PAVGBP(%%mm0, %%mm1, %%mm4,   %%mm2, %%mm3, %%mm5)                                            // (2) 0.07422
/*24 */         "movq   %%mm4, (%2)             \n\t"                                                         // (5) 0.07227
/*26 */         "movq   %%mm5, (%2, %3)         \n\t"                                                         // (8) 0.07031
/*28 */         "movq   8(%1), %%mm0            \n\t"                                                         // (4) 0.07227
/*30 */         "movq   9(%1), %%mm1            \n\t"                                                         // 0.0
/*32 */         "movq   8(%1, %3), %%mm2        \n\t"                                                         // 0.0
/*34 */         "movq   9(%1, %3), %%mm3        \n\t"                                                         // 0.0
/*36 */         PAVGBP(%%mm0, %%mm1, %%mm4,   %%mm2, %%mm3, %%mm5)                                            // 0.0
/*38 */         "movq   %%mm4, 8(%2)            \n\t"                                                         // 0.0
/*40 */         "movq   %%mm5, 8(%2, %3)        \n\t"                                                         // 0.0
/*42 */         "add    %%"REG_a", %1           \n\t"                                                         // 0.0
/*44 */         "add    %%"REG_a", %2           \n\t"                                                         // 0.0
/*46 */         "movq   (%1), %%mm0             \n\t"                                                         // 0.0
/*48 */         "movq   1(%1), %%mm1            \n\t"                                                         // 0.0
/*50 */         "movq   (%1, %3), %%mm2         \n\t"                                                         // 0.0
/*52 */         "movq   1(%1, %3), %%mm3        \n\t"                                                         // 0.0
/*54 */         PAVGBP(%%mm0, %%mm1, %%mm4,   %%mm2, %%mm3, %%mm5)                                            // 0.0
/*56 */         "movq   %%mm4, (%2)             \n\t"                                                         // 0.0
/*58 */         "movq   %%mm5, (%2, %3)         \n\t"                                                         // 0.0
/*60 */         "movq   8(%1), %%mm0            \n\t"                                                         // 0.0
/*62 */         "movq   9(%1), %%mm1            \n\t"                                                         // 0.0
/*64 */         "movq   8(%1, %3), %%mm2        \n\t"                                                         // 0.0
/*66 */         "movq   9(%1, %3), %%mm3        \n\t"                                                         // 0.0
/*68 */         PAVGBP(%%mm0, %%mm1, %%mm4,   %%mm2, %%mm3, %%mm5)                                            // 0.0
/*70 */         "movq   %%mm4, 8(%2)            \n\t"                                                         // 0.0
/*72 */         "movq   %%mm5, 8(%2, %3)        \n\t"                                                         // 0.0
/*74 */         "add    %%"REG_a", %1           \n\t"                                                         // 0.0
/*76 */         "add    %%"REG_a", %2           \n\t"                                                         // 0.0
/*78 */         "subl   $4, %0                  \n\t"                                                         // 0.0
/*80 */         "jnz    1b                      \n\t"                                                         // 0.0
/*82 */         :"+g"(h), "+S"(pixels), "+D"(block)                                                           // 0.0
/*84 */         :"r"((x86_reg)line_size)                                                                      // 0.0
/*86 */         :REG_a, "memory");                                                                            // 0.0
/*88 */ }                                                                                                     // 0.0
