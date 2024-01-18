// commit message FFmpeg@659d4ba5af (target=0, prob=0.482039, correct=True): dsputil: x86: Convert h263 loop filter to yasm
/*0   */ static void h263_h_loop_filter_mmx(uint8_t *src, int stride, int qscale)  // (3) 0.05469
/*2   */ {                                                                         // (19) 0.001953
/*4   */     if (CONFIG_H263_DECODER || CONFIG_H263_ENCODER) {                     // (8) 0.04883
/*6   */         const int strength = ff_h263_loop_filter_strength[qscale];        // (7) 0.04883
/*8   */         DECLARE_ALIGNED(8, uint64_t, temp)[4];                            // (6) 0.05078
/*10  */         uint8_t *btemp = (uint8_t*)temp;                                  // (10) 0.04492
/*14  */         src -= 2;                                                         // (18) 0.02148
/*18  */         transpose4x4(btemp,     src,              8, stride);             // (2) 0.07617
/*20  */         transpose4x4(btemp + 4, src + 4 * stride, 8, stride);             // (5) 0.05469
/*22  */         __asm__ volatile (                                                // (15) 0.02344
/*24  */             H263_LOOP_FILTER // 5 3 4 6                                   // (9) 0.04688
/*28  */             : "+m"(temp[0]),                                              // (14) 0.03711
/*30  */               "+m"(temp[1]),                                              // (11) 0.03906
/*32  */               "+m"(temp[2]),                                              // (12) 0.03906
/*34  */               "+m"(temp[3])                                               // (13) 0.03906
/*36  */             : "g"(2 * strength), "m"(ff_pb_FC)                            // (4) 0.05469
/*38  */             );                                                            // (17) 0.02344
/*42  */         __asm__ volatile (                                                // (16) 0.02344
/*44  */             "movq      %%mm5, %%mm1         \n\t"                         // (0) 0.07812
/*46  */             "movq      %%mm4, %%mm0         \n\t"                         // (1) 0.07812
/*48  */             "punpcklbw %%mm3, %%mm5         \n\t"                         // 0.0
/*50  */             "punpcklbw %%mm6, %%mm4         \n\t"                         // 0.0
/*52  */             "punpckhbw %%mm3, %%mm1         \n\t"                         // 0.0
/*54  */             "punpckhbw %%mm6, %%mm0         \n\t"                         // 0.0
/*56  */             "movq      %%mm5, %%mm3         \n\t"                         // 0.0
/*58  */             "movq      %%mm1, %%mm6         \n\t"                         // 0.0
/*60  */             "punpcklwd %%mm4, %%mm5         \n\t"                         // 0.0
/*62  */             "punpcklwd %%mm0, %%mm1         \n\t"                         // 0.0
/*64  */             "punpckhwd %%mm4, %%mm3         \n\t"                         // 0.0
/*66  */             "punpckhwd %%mm0, %%mm6         \n\t"                         // 0.0
/*68  */             "movd      %%mm5, (%0)          \n\t"                         // 0.0
/*70  */             "punpckhdq %%mm5, %%mm5         \n\t"                         // 0.0
/*72  */             "movd      %%mm5, (%0, %2)      \n\t"                         // 0.0
/*74  */             "movd      %%mm3, (%0, %2, 2)   \n\t"                         // 0.0
/*76  */             "punpckhdq %%mm3, %%mm3         \n\t"                         // 0.0
/*78  */             "movd      %%mm3, (%0, %3)      \n\t"                         // 0.0
/*80  */             "movd      %%mm1, (%1)          \n\t"                         // 0.0
/*82  */             "punpckhdq %%mm1, %%mm1         \n\t"                         // 0.0
/*84  */             "movd      %%mm1, (%1, %2)      \n\t"                         // 0.0
/*86  */             "movd      %%mm6, (%1, %2, 2)   \n\t"                         // 0.0
/*88  */             "punpckhdq %%mm6, %%mm6         \n\t"                         // 0.0
/*90  */             "movd      %%mm6, (%1, %3)      \n\t"                         // 0.0
/*92  */             :: "r"(src),                                                  // 0.0
/*94  */                "r"(src + 4 * stride),                                     // 0.0
/*96  */                "r"((x86_reg)stride),                                      // 0.0
/*98  */                "r"((x86_reg)(3 * stride))                                 // 0.0
/*100 */             );                                                            // 0.0
/*102 */     }                                                                     // 0.0
/*104 */ }                                                                         // 0.0
