// commit message FFmpeg@d1adad3cca (target=0, prob=0.047240466, correct=True): Merge swscale bloatup This will be cleaned up in the next merge
/*0   */ static inline void RENAME(yvu9_to_yuy2)(const uint8_t *src1, const uint8_t *src2, const uint8_t *src3,  // (4) 0.08594
/*2   */                                         uint8_t *dst,                                                   // (2) 0.0918
/*4   */                                         long width, long height,                                        // (3) 0.08789
/*6   */                                         long srcStride1, long srcStride2,                               // (0) 0.09961
/*8   */                                         long srcStride3, long dstStride)                                // (1) 0.09766
/*10  */ {                                                                                                       // (17) 0.001953
/*12  */     x86_reg x;                                                                                          // (16) 0.01758
/*14  */     long y,w,h;                                                                                         // (15) 0.01953
/*16  */     w=width/2; h=height;                                                                                // (13) 0.02539
/*18  */     for (y=0;y<h;y++) {                                                                                 // (11) 0.03125
/*20  */         const uint8_t* yp=src1+srcStride1*y;                                                            // (7) 0.05078
/*22  */         const uint8_t* up=src2+srcStride2*(y>>2);                                                       // (6) 0.05469
/*24  */         const uint8_t* vp=src3+srcStride3*(y>>2);                                                       // (5) 0.05664
/*26  */         uint8_t* d=dst+dstStride*y;                                                                     // (8) 0.04688
/*28  */         x=0;                                                                                            // (14) 0.02148
/*30  */ #if COMPILE_TEMPLATE_MMX                                                                                // (12) 0.02539
/*32  */         for (;x<w-7;x+=8) {                                                                             // (9) 0.04102
/*34  */             __asm__ volatile(                                                                           // (10) 0.03125
/*36  */                 PREFETCH"   32(%1, %0)          \n\t"                                                   // 0.0
/*38  */                 PREFETCH"   32(%2, %0)          \n\t"                                                   // 0.0
/*40  */                 PREFETCH"   32(%3, %0)          \n\t"                                                   // 0.0
/*42  */                 "movq      (%1, %0, 4), %%mm0   \n\t" /* Y0Y1Y2Y3Y4Y5Y6Y7 */                            // 0.0
/*44  */                 "movq         (%2, %0), %%mm1   \n\t" /* U0U1U2U3U4U5U6U7 */                            // 0.0
/*46  */                 "movq         (%3, %0), %%mm2   \n\t" /* V0V1V2V3V4V5V6V7 */                            // 0.0
/*48  */                 "movq            %%mm0, %%mm3   \n\t" /* Y0Y1Y2Y3Y4Y5Y6Y7 */                            // 0.0
/*50  */                 "movq            %%mm1, %%mm4   \n\t" /* U0U1U2U3U4U5U6U7 */                            // 0.0
/*52  */                 "movq            %%mm2, %%mm5   \n\t" /* V0V1V2V3V4V5V6V7 */                            // 0.0
/*54  */                 "punpcklbw       %%mm1, %%mm1   \n\t" /* U0U0 U1U1 U2U2 U3U3 */                         // 0.0
/*56  */                 "punpcklbw       %%mm2, %%mm2   \n\t" /* V0V0 V1V1 V2V2 V3V3 */                         // 0.0
/*58  */                 "punpckhbw       %%mm4, %%mm4   \n\t" /* U4U4 U5U5 U6U6 U7U7 */                         // 0.0
/*60  */                 "punpckhbw       %%mm5, %%mm5   \n\t" /* V4V4 V5V5 V6V6 V7V7 */                         // 0.0
/*64  */                 "movq            %%mm1, %%mm6   \n\t"                                                   // 0.0
/*66  */                 "punpcklbw       %%mm2, %%mm1   \n\t" /* U0V0 U0V0 U1V1 U1V1*/                          // 0.0
/*68  */                 "punpcklbw       %%mm1, %%mm0   \n\t" /* Y0U0 Y1V0 Y2U0 Y3V0*/                          // 0.0
/*70  */                 "punpckhbw       %%mm1, %%mm3   \n\t" /* Y4U1 Y5V1 Y6U1 Y7V1*/                          // 0.0
/*72  */                 MOVNTQ"          %%mm0,  (%4, %0, 8)    \n\t"                                           // 0.0
/*74  */                 MOVNTQ"          %%mm3, 8(%4, %0, 8)    \n\t"                                           // 0.0
/*78  */                 "punpckhbw       %%mm2, %%mm6   \n\t" /* U2V2 U2V2 U3V3 U3V3*/                          // 0.0
/*80  */                 "movq     8(%1, %0, 4), %%mm0   \n\t"                                                   // 0.0
/*82  */                 "movq            %%mm0, %%mm3   \n\t"                                                   // 0.0
/*84  */                 "punpcklbw       %%mm6, %%mm0   \n\t" /* Y U2 Y V2 Y U2 Y V2*/                          // 0.0
/*86  */                 "punpckhbw       %%mm6, %%mm3   \n\t" /* Y U3 Y V3 Y U3 Y V3*/                          // 0.0
/*88  */                 MOVNTQ"          %%mm0, 16(%4, %0, 8)   \n\t"                                           // 0.0
/*90  */                 MOVNTQ"          %%mm3, 24(%4, %0, 8)   \n\t"                                           // 0.0
/*94  */                 "movq            %%mm4, %%mm6   \n\t"                                                   // 0.0
/*96  */                 "movq    16(%1, %0, 4), %%mm0   \n\t"                                                   // 0.0
/*98  */                 "movq            %%mm0, %%mm3   \n\t"                                                   // 0.0
/*100 */                 "punpcklbw       %%mm5, %%mm4   \n\t"                                                   // 0.0
/*102 */                 "punpcklbw       %%mm4, %%mm0   \n\t" /* Y U4 Y V4 Y U4 Y V4*/                          // 0.0
/*104 */                 "punpckhbw       %%mm4, %%mm3   \n\t" /* Y U5 Y V5 Y U5 Y V5*/                          // 0.0
/*106 */                 MOVNTQ"          %%mm0, 32(%4, %0, 8)   \n\t"                                           // 0.0
/*108 */                 MOVNTQ"          %%mm3, 40(%4, %0, 8)   \n\t"                                           // 0.0
/*112 */                 "punpckhbw       %%mm5, %%mm6   \n\t"                                                   // 0.0
/*114 */                 "movq    24(%1, %0, 4), %%mm0   \n\t"                                                   // 0.0
/*116 */                 "movq            %%mm0, %%mm3   \n\t"                                                   // 0.0
/*118 */                 "punpcklbw       %%mm6, %%mm0   \n\t" /* Y U6 Y V6 Y U6 Y V6*/                          // 0.0
/*120 */                 "punpckhbw       %%mm6, %%mm3   \n\t" /* Y U7 Y V7 Y U7 Y V7*/                          // 0.0
/*122 */                 MOVNTQ"          %%mm0, 48(%4, %0, 8)   \n\t"                                           // 0.0
/*124 */                 MOVNTQ"          %%mm3, 56(%4, %0, 8)   \n\t"                                           // 0.0
/*128 */                 : "+r" (x)                                                                              // 0.0
/*130 */                 : "r"(yp), "r" (up), "r"(vp), "r"(d)                                                    // 0.0
/*132 */                 :"memory");                                                                             // 0.0
/*134 */         }                                                                                               // 0.0
/*136 */ #endif                                                                                                  // 0.0
/*138 */         for (; x<w; x++) {                                                                              // 0.0
/*140 */             const long x2 = x<<2;                                                                       // 0.0
/*142 */             d[8*x+0] = yp[x2];                                                                          // 0.0
/*144 */             d[8*x+1] = up[x];                                                                           // 0.0
/*146 */             d[8*x+2] = yp[x2+1];                                                                        // 0.0
/*148 */             d[8*x+3] = vp[x];                                                                           // 0.0
/*150 */             d[8*x+4] = yp[x2+2];                                                                        // 0.0
/*152 */             d[8*x+5] = up[x];                                                                           // 0.0
/*154 */             d[8*x+6] = yp[x2+3];                                                                        // 0.0
/*156 */             d[8*x+7] = vp[x];                                                                           // 0.0
/*158 */         }                                                                                               // 0.0
/*160 */     }                                                                                                   // 0.0
/*162 */ #if COMPILE_TEMPLATE_MMX                                                                                // 0.0
/*164 */     __asm__(                                                                                            // 0.0
/*166 */             EMMS"       \n\t"                                                                           // 0.0
/*168 */             SFENCE"     \n\t"                                                                           // 0.0
/*170 */             ::: "memory"                                                                                // 0.0
/*172 */         );                                                                                              // 0.0
/*174 */ #endif                                                                                                  // 0.0
/*176 */ }                                                                                                       // 0.0
