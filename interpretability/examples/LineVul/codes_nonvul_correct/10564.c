// commit message FFmpeg@d1adad3cca (target=0, prob=0.029792866, correct=True): Merge swscale bloatup This will be cleaned up in the next merge
/*0   */ static inline void RENAME(yuy2toyv12)(const uint8_t *src, uint8_t *ydst, uint8_t *udst, uint8_t *vdst,  // (5) 0.0918
/*2   */                                       long width, long height,                                          // (6) 0.08398
/*4   */                                       long lumStride, long chromStride, long srcStride)                 // (2) 0.1016
/*6   */ {                                                                                                       // (13) 0.001953
/*8   */     long y;                                                                                             // (12) 0.01172
/*10  */     const x86_reg chromWidth= width>>1;                                                                 // (9) 0.0293
/*12  */     for (y=0; y<height; y+=2) {                                                                         // (8) 0.03516
/*14  */ #if COMPILE_TEMPLATE_MMX                                                                                // (10) 0.02539
/*16  */         __asm__ volatile(                                                                               // (11) 0.02344
/*18  */             "xor                 %%"REG_a", %%"REG_a"   \n\t"                                           // (4) 0.0957
/*20  */             "pcmpeqw                 %%mm7, %%mm7       \n\t"                                           // (3) 0.09961
/*22  */             "psrlw                      $8, %%mm7       \n\t" // FF,00,FF,00...                         // (0) 0.1211
/*24  */             ".p2align                    4              \n\t"                                           // (1) 0.1035
/*26  */             "1:                \n\t"                                                                    // (7) 0.06641
/*28  */             PREFETCH" 64(%0, %%"REG_a", 4)              \n\t"                                           // 0.0
/*30  */             "movq       (%0, %%"REG_a", 4), %%mm0       \n\t" // YUYV YUYV(0)                           // 0.0
/*32  */             "movq      8(%0, %%"REG_a", 4), %%mm1       \n\t" // YUYV YUYV(4)                           // 0.0
/*34  */             "movq                    %%mm0, %%mm2       \n\t" // YUYV YUYV(0)                           // 0.0
/*36  */             "movq                    %%mm1, %%mm3       \n\t" // YUYV YUYV(4)                           // 0.0
/*38  */             "psrlw                      $8, %%mm0       \n\t" // U0V0 U0V0(0)                           // 0.0
/*40  */             "psrlw                      $8, %%mm1       \n\t" // U0V0 U0V0(4)                           // 0.0
/*42  */             "pand                    %%mm7, %%mm2       \n\t" // Y0Y0 Y0Y0(0)                           // 0.0
/*44  */             "pand                    %%mm7, %%mm3       \n\t" // Y0Y0 Y0Y0(4)                           // 0.0
/*46  */             "packuswb                %%mm1, %%mm0       \n\t" // UVUV UVUV(0)                           // 0.0
/*48  */             "packuswb                %%mm3, %%mm2       \n\t" // YYYY YYYY(0)                           // 0.0
/*52  */             MOVNTQ"                  %%mm2, (%1, %%"REG_a", 2)  \n\t"                                   // 0.0
/*56  */             "movq     16(%0, %%"REG_a", 4), %%mm1       \n\t" // YUYV YUYV(8)                           // 0.0
/*58  */             "movq     24(%0, %%"REG_a", 4), %%mm2       \n\t" // YUYV YUYV(12)                          // 0.0
/*60  */             "movq                    %%mm1, %%mm3       \n\t" // YUYV YUYV(8)                           // 0.0
/*62  */             "movq                    %%mm2, %%mm4       \n\t" // YUYV YUYV(12)                          // 0.0
/*64  */             "psrlw                      $8, %%mm1       \n\t" // U0V0 U0V0(8)                           // 0.0
/*66  */             "psrlw                      $8, %%mm2       \n\t" // U0V0 U0V0(12)                          // 0.0
/*68  */             "pand                    %%mm7, %%mm3       \n\t" // Y0Y0 Y0Y0(8)                           // 0.0
/*70  */             "pand                    %%mm7, %%mm4       \n\t" // Y0Y0 Y0Y0(12)                          // 0.0
/*72  */             "packuswb                %%mm2, %%mm1       \n\t" // UVUV UVUV(8)                           // 0.0
/*74  */             "packuswb                %%mm4, %%mm3       \n\t" // YYYY YYYY(8)                           // 0.0
/*78  */             MOVNTQ"                  %%mm3, 8(%1, %%"REG_a", 2) \n\t"                                   // 0.0
/*82  */             "movq                    %%mm0, %%mm2       \n\t" // UVUV UVUV(0)                           // 0.0
/*84  */             "movq                    %%mm1, %%mm3       \n\t" // UVUV UVUV(8)                           // 0.0
/*86  */             "psrlw                      $8, %%mm0       \n\t" // V0V0 V0V0(0)                           // 0.0
/*88  */             "psrlw                      $8, %%mm1       \n\t" // V0V0 V0V0(8)                           // 0.0
/*90  */             "pand                    %%mm7, %%mm2       \n\t" // U0U0 U0U0(0)                           // 0.0
/*92  */             "pand                    %%mm7, %%mm3       \n\t" // U0U0 U0U0(8)                           // 0.0
/*94  */             "packuswb                %%mm1, %%mm0       \n\t" // VVVV VVVV(0)                           // 0.0
/*96  */             "packuswb                %%mm3, %%mm2       \n\t" // UUUU UUUU(0)                           // 0.0
/*100 */             MOVNTQ"                  %%mm0, (%3, %%"REG_a")     \n\t"                                   // 0.0
/*102 */             MOVNTQ"                  %%mm2, (%2, %%"REG_a")     \n\t"                                   // 0.0
/*106 */             "add                        $8, %%"REG_a"   \n\t"                                           // 0.0
/*108 */             "cmp                        %4, %%"REG_a"   \n\t"                                           // 0.0
/*110 */             " jb                        1b              \n\t"                                           // 0.0
/*112 */             ::"r"(src), "r"(ydst), "r"(udst), "r"(vdst), "g" (chromWidth)                               // 0.0
/*114 */             : "memory", "%"REG_a                                                                        // 0.0
/*116 */         );                                                                                              // 0.0
/*120 */         ydst += lumStride;                                                                              // 0.0
/*122 */         src  += srcStride;                                                                              // 0.0
/*126 */         __asm__ volatile(                                                                               // 0.0
/*128 */             "xor                 %%"REG_a", %%"REG_a"   \n\t"                                           // 0.0
/*130 */             ".p2align                    4              \n\t"                                           // 0.0
/*132 */             "1:                                         \n\t"                                           // 0.0
/*134 */             PREFETCH" 64(%0, %%"REG_a", 4)              \n\t"                                           // 0.0
/*136 */             "movq       (%0, %%"REG_a", 4), %%mm0       \n\t" // YUYV YUYV(0)                           // 0.0
/*138 */             "movq      8(%0, %%"REG_a", 4), %%mm1       \n\t" // YUYV YUYV(4)                           // 0.0
/*140 */             "movq     16(%0, %%"REG_a", 4), %%mm2       \n\t" // YUYV YUYV(8)                           // 0.0
/*142 */             "movq     24(%0, %%"REG_a", 4), %%mm3       \n\t" // YUYV YUYV(12)                          // 0.0
/*144 */             "pand                    %%mm7, %%mm0       \n\t" // Y0Y0 Y0Y0(0)                           // 0.0
/*146 */             "pand                    %%mm7, %%mm1       \n\t" // Y0Y0 Y0Y0(4)                           // 0.0
/*148 */             "pand                    %%mm7, %%mm2       \n\t" // Y0Y0 Y0Y0(8)                           // 0.0
/*150 */             "pand                    %%mm7, %%mm3       \n\t" // Y0Y0 Y0Y0(12)                          // 0.0
/*152 */             "packuswb                %%mm1, %%mm0       \n\t" // YYYY YYYY(0)                           // 0.0
/*154 */             "packuswb                %%mm3, %%mm2       \n\t" // YYYY YYYY(8)                           // 0.0
/*158 */             MOVNTQ"                  %%mm0,  (%1, %%"REG_a", 2) \n\t"                                   // 0.0
/*160 */             MOVNTQ"                  %%mm2, 8(%1, %%"REG_a", 2) \n\t"                                   // 0.0
/*164 */             "add                        $8, %%"REG_a"   \n\t"                                           // 0.0
/*166 */             "cmp                        %4, %%"REG_a"   \n\t"                                           // 0.0
/*168 */             " jb                        1b              \n\t"                                           // 0.0
/*172 */             ::"r"(src), "r"(ydst), "r"(udst), "r"(vdst), "g" (chromWidth)                               // 0.0
/*174 */             : "memory", "%"REG_a                                                                        // 0.0
/*176 */         );                                                                                              // 0.0
/*178 */ #else                                                                                                   // 0.0
/*180 */         long i;                                                                                         // 0.0
/*182 */         for (i=0; i<chromWidth; i++) {                                                                  // 0.0
/*184 */             ydst[2*i+0]     = src[4*i+0];                                                               // 0.0
/*186 */             udst[i]     = src[4*i+1];                                                                   // 0.0
/*188 */             ydst[2*i+1]     = src[4*i+2];                                                               // 0.0
/*190 */             vdst[i]     = src[4*i+3];                                                                   // 0.0
/*192 */         }                                                                                               // 0.0
/*194 */         ydst += lumStride;                                                                              // 0.0
/*196 */         src  += srcStride;                                                                              // 0.0
/*200 */         for (i=0; i<chromWidth; i++) {                                                                  // 0.0
/*202 */             ydst[2*i+0]     = src[4*i+0];                                                               // 0.0
/*204 */             ydst[2*i+1]     = src[4*i+2];                                                               // 0.0
/*206 */         }                                                                                               // 0.0
/*208 */ #endif                                                                                                  // 0.0
/*210 */         udst += chromStride;                                                                            // 0.0
/*212 */         vdst += chromStride;                                                                            // 0.0
/*214 */         ydst += lumStride;                                                                              // 0.0
/*216 */         src  += srcStride;                                                                              // 0.0
/*218 */     }                                                                                                   // 0.0
/*220 */ #if COMPILE_TEMPLATE_MMX                                                                                // 0.0
/*222 */     __asm__ volatile(EMMS"       \n\t"                                                                  // 0.0
/*224 */                      SFENCE"     \n\t"                                                                  // 0.0
/*226 */                      :::"memory");                                                                      // 0.0
/*228 */ #endif                                                                                                  // 0.0
/*230 */ }                                                                                                       // 0.0
