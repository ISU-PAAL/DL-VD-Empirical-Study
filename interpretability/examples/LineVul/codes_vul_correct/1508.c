// commit message FFmpeg@90540c2d5a (target=1, prob=0.99380684, correct=True): x86: swscale: fix fragile memory accesses
/*0   */ static inline void RENAME(rgb15tobgr24)(const uint8_t *src, uint8_t *dst, int src_size)  // (8) 0.07031
/*2   */ {                                                                                        // (18) 0.001953
/*4   */     const uint16_t *end;                                                                 // (17) 0.02148
/*6   */     const uint16_t *mm_end;                                                              // (12) 0.02539
/*8   */     uint8_t *d = dst;                                                                    // (15) 0.02344
/*10  */     const uint16_t *s = (const uint16_t*)src;                                            // (10) 0.03906
/*12  */     end = s + src_size/2;                                                                // (11) 0.02539
/*14  */     __asm__ volatile(PREFETCH"    %0"::"m"(*s):"memory");                                // (9) 0.05469
/*16  */     mm_end = end - 7;                                                                    // (16) 0.02148
/*18  */     while (s < mm_end) {                                                                 // (13) 0.02344
/*20  */         __asm__ volatile(                                                                // (14) 0.02344
/*22  */             PREFETCH"    32%1           \n\t"                                            // (7) 0.07227
/*24  */             "movq          %1, %%mm0    \n\t"                                            // (2) 0.07422
/*26  */             "movq          %1, %%mm1    \n\t"                                            // (1) 0.07422
/*28  */             "movq          %1, %%mm2    \n\t"                                            // (0) 0.07422
/*30  */             "pand          %2, %%mm0    \n\t"                                            // (6) 0.07227
/*32  */             "pand          %3, %%mm1    \n\t"                                            // (4) 0.07227
/*34  */             "pand          %4, %%mm2    \n\t"                                            // (5) 0.07227
/*36  */             "psllq         $3, %%mm0    \n\t"                                            // (3) 0.07227
/*38  */             "psrlq         $2, %%mm1    \n\t"                                            // 0.0
/*40  */             "psrlq         $7, %%mm2    \n\t"                                            // 0.0
/*42  */             "movq       %%mm0, %%mm3    \n\t"                                            // 0.0
/*44  */             "movq       %%mm1, %%mm4    \n\t"                                            // 0.0
/*46  */             "movq       %%mm2, %%mm5    \n\t"                                            // 0.0
/*48  */             "punpcklwd     %5, %%mm0    \n\t"                                            // 0.0
/*50  */             "punpcklwd     %5, %%mm1    \n\t"                                            // 0.0
/*52  */             "punpcklwd     %5, %%mm2    \n\t"                                            // 0.0
/*54  */             "punpckhwd     %5, %%mm3    \n\t"                                            // 0.0
/*56  */             "punpckhwd     %5, %%mm4    \n\t"                                            // 0.0
/*58  */             "punpckhwd     %5, %%mm5    \n\t"                                            // 0.0
/*60  */             "psllq         $8, %%mm1    \n\t"                                            // 0.0
/*62  */             "psllq        $16, %%mm2    \n\t"                                            // 0.0
/*64  */             "por        %%mm1, %%mm0    \n\t"                                            // 0.0
/*66  */             "por        %%mm2, %%mm0    \n\t"                                            // 0.0
/*68  */             "psllq         $8, %%mm4    \n\t"                                            // 0.0
/*70  */             "psllq        $16, %%mm5    \n\t"                                            // 0.0
/*72  */             "por        %%mm4, %%mm3    \n\t"                                            // 0.0
/*74  */             "por        %%mm5, %%mm3    \n\t"                                            // 0.0
/*78  */             "movq       %%mm0, %%mm6    \n\t"                                            // 0.0
/*80  */             "movq       %%mm3, %%mm7    \n\t"                                            // 0.0
/*84  */             "movq         8%1, %%mm0    \n\t"                                            // 0.0
/*86  */             "movq         8%1, %%mm1    \n\t"                                            // 0.0
/*88  */             "movq         8%1, %%mm2    \n\t"                                            // 0.0
/*90  */             "pand          %2, %%mm0    \n\t"                                            // 0.0
/*92  */             "pand          %3, %%mm1    \n\t"                                            // 0.0
/*94  */             "pand          %4, %%mm2    \n\t"                                            // 0.0
/*96  */             "psllq         $3, %%mm0    \n\t"                                            // 0.0
/*98  */             "psrlq         $2, %%mm1    \n\t"                                            // 0.0
/*100 */             "psrlq         $7, %%mm2    \n\t"                                            // 0.0
/*102 */             "movq       %%mm0, %%mm3    \n\t"                                            // 0.0
/*104 */             "movq       %%mm1, %%mm4    \n\t"                                            // 0.0
/*106 */             "movq       %%mm2, %%mm5    \n\t"                                            // 0.0
/*108 */             "punpcklwd     %5, %%mm0    \n\t"                                            // 0.0
/*110 */             "punpcklwd     %5, %%mm1    \n\t"                                            // 0.0
/*112 */             "punpcklwd     %5, %%mm2    \n\t"                                            // 0.0
/*114 */             "punpckhwd     %5, %%mm3    \n\t"                                            // 0.0
/*116 */             "punpckhwd     %5, %%mm4    \n\t"                                            // 0.0
/*118 */             "punpckhwd     %5, %%mm5    \n\t"                                            // 0.0
/*120 */             "psllq         $8, %%mm1    \n\t"                                            // 0.0
/*122 */             "psllq        $16, %%mm2    \n\t"                                            // 0.0
/*124 */             "por        %%mm1, %%mm0    \n\t"                                            // 0.0
/*126 */             "por        %%mm2, %%mm0    \n\t"                                            // 0.0
/*128 */             "psllq         $8, %%mm4    \n\t"                                            // 0.0
/*130 */             "psllq        $16, %%mm5    \n\t"                                            // 0.0
/*132 */             "por        %%mm4, %%mm3    \n\t"                                            // 0.0
/*134 */             "por        %%mm5, %%mm3    \n\t"                                            // 0.0
/*138 */             :"=m"(*d)                                                                    // 0.0
/*140 */             :"m"(*s),"m"(mask15b),"m"(mask15g),"m"(mask15r), "m"(mmx_null)               // 0.0
/*142 */             :"memory");                                                                  // 0.0
/*144 */         /* borrowed 32 to 24 */                                                          // 0.0
/*146 */         __asm__ volatile(                                                                // 0.0
/*148 */             "movq       %%mm0, %%mm4    \n\t"                                            // 0.0
/*150 */             "movq       %%mm3, %%mm5    \n\t"                                            // 0.0
/*152 */             "movq       %%mm6, %%mm0    \n\t"                                            // 0.0
/*154 */             "movq       %%mm7, %%mm1    \n\t"                                            // 0.0
/*158 */             "movq       %%mm4, %%mm6    \n\t"                                            // 0.0
/*160 */             "movq       %%mm5, %%mm7    \n\t"                                            // 0.0
/*162 */             "movq       %%mm0, %%mm2    \n\t"                                            // 0.0
/*164 */             "movq       %%mm1, %%mm3    \n\t"                                            // 0.0
/*168 */             STORE_BGR24_MMX                                                              // 0.0
/*172 */             :"=m"(*d)                                                                    // 0.0
/*174 */             :"m"(*s)                                                                     // 0.0
/*176 */             :"memory");                                                                  // 0.0
/*178 */         d += 24;                                                                         // 0.0
/*180 */         s += 8;                                                                          // 0.0
/*182 */     }                                                                                    // 0.0
/*184 */     __asm__ volatile(SFENCE:::"memory");                                                 // 0.0
/*186 */     __asm__ volatile(EMMS:::"memory");                                                   // 0.0
/*188 */     while (s < end) {                                                                    // 0.0
/*190 */         register uint16_t bgr;                                                           // 0.0
/*192 */         bgr = *s++;                                                                      // 0.0
/*194 */         *d++ = (bgr&0x1F)<<3;                                                            // 0.0
/*196 */         *d++ = (bgr&0x3E0)>>2;                                                           // 0.0
/*198 */         *d++ = (bgr&0x7C00)>>7;                                                          // 0.0
/*200 */     }                                                                                    // 0.0
/*202 */ }                                                                                        // 0.0
