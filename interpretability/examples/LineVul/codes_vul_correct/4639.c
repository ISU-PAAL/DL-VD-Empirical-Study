// commit message FFmpeg@57d04d3f11 (target=1, prob=0.7665996, correct=True): negative black bugfix
/*0   */ static inline void blockCopy(uint8_t dst[], int dstStride, uint8_t src[], int srcStride,  // (0) 0.05859
/*2   */ 	int numLines, int levelFix)                                                              // (19) 0.01953
/*4   */ {                                                                                         // (25) 0.001953
/*6   */ 	int i;                                                                                   // (23) 0.007813
/*8   */ 	if(levelFix)                                                                             // (22) 0.01172
/*10  */ 	{                                                                                        // (24) 0.003906
/*12  */ #ifdef HAVE_MMX                                                                           // (21) 0.01367
/*14  */ 					asm volatile(                                                                        // (20) 0.01563
/*16  */ 						"movl %4, %%eax \n\t"                                                               // (15) 0.04102
/*18  */ 						"movl %%eax, temp0\n\t"                                                             // (14) 0.04102
/*20  */ 						"pushl %0 \n\t"                                                                     // (16) 0.03125
/*22  */ 						"pushl %1 \n\t"                                                                     // (17) 0.03125
/*24  */ 						"leal (%2,%2), %%eax	\n\t"                                                          // (8) 0.04687
/*26  */ 						"leal (%3,%3), %%ebx	\n\t"                                                          // (7) 0.04687
/*28  */ 						"movq packedYOffset, %%mm2	\n\t"                                                    // (9) 0.04492
/*30  */ 						"movq packedYScale, %%mm3	\n\t"                                                     // (11) 0.04492
/*32  */ 						"pxor %%mm4, %%mm4	\n\t"                                                            // (13) 0.04297
/*36  */ #define SCALED_CPY					\                                                                  // (18) 0.02734
/*38  */ 						"movq (%0), %%mm0	\n\t"\                                                            // (12) 0.04492
/*40  */ 						"movq (%0,%2), %%mm1	\n\t"\                                                         // (2) 0.05078
/*42  */ 						"psubusb %%mm2, %%mm0	\n\t"\                                                        // (5) 0.04688
/*44  */ 						"psubusb %%mm2, %%mm1	\n\t"\                                                        // (4) 0.04688
/*46  */ 						"movq %%mm0, %%mm5	\n\t"\                                                           // (6) 0.04687
/*48  */ 						"punpcklbw %%mm4, %%mm0 \n\t"\                                                      // (3) 0.04883
/*50  */ 						"punpckhbw %%mm4, %%mm5 \n\t"\                                                      // (1) 0.05078
/*52  */ 						"psllw $7, %%mm0	\n\t"\                                                             // (10) 0.04492
/*54  */ 						"psllw $7, %%mm5	\n\t"\                                                             // 0.0
/*56  */ 						"pmulhw %%mm3, %%mm0	\n\t"\                                                         // 0.0
/*58  */ 						"pmulhw %%mm3, %%mm5	\n\t"\                                                         // 0.0
/*60  */ 						"packuswb %%mm5, %%mm0	\n\t"\                                                       // 0.0
/*62  */ 						"movq %%mm0, (%1)	\n\t"\                                                            // 0.0
/*64  */ 						"movq %%mm1, %%mm5	\n\t"\                                                           // 0.0
/*66  */ 						"punpcklbw %%mm4, %%mm1 \n\t"\                                                      // 0.0
/*68  */ 						"punpckhbw %%mm4, %%mm5 \n\t"\                                                      // 0.0
/*70  */ 						"psllw $7, %%mm1	\n\t"\                                                             // 0.0
/*72  */ 						"psllw $7, %%mm5	\n\t"\                                                             // 0.0
/*74  */ 						"pmulhw %%mm3, %%mm1	\n\t"\                                                         // 0.0
/*76  */ 						"pmulhw %%mm3, %%mm5	\n\t"\                                                         // 0.0
/*78  */ 						"packuswb %%mm5, %%mm1	\n\t"\                                                       // 0.0
/*80  */ 						"movq %%mm1, (%1, %3)	\n\t"\                                                        // 0.0
/*84  */ 						"1:			\n\t"                                                                         // 0.0
/*86  */ SCALED_CPY                                                                                // 0.0
/*88  */ 						"addl %%eax, %0		\n\t"                                                              // 0.0
/*90  */ 						"addl %%ebx, %1		\n\t"                                                              // 0.0
/*92  */ SCALED_CPY                                                                                // 0.0
/*94  */ 						"addl %%eax, %0		\n\t"                                                              // 0.0
/*96  */ 						"addl %%ebx, %1		\n\t"                                                              // 0.0
/*98  */ 						"decl temp0		\n\t"                                                                  // 0.0
/*100 */ 						"jnz 1b			\n\t"                                                                     // 0.0
/*104 */ 						"popl %1 \n\t"                                                                      // 0.0
/*106 */ 						"popl %0 \n\t"                                                                      // 0.0
/*108 */ 						: : "r" (src),                                                                      // 0.0
/*110 */ 						"r" (dst),                                                                          // 0.0
/*112 */ 						"r" (srcStride),                                                                    // 0.0
/*114 */ 						"r" (dstStride),                                                                    // 0.0
/*116 */ 						"m" (numLines>>2)                                                                   // 0.0
/*118 */ 						: "%eax", "%ebx"                                                                    // 0.0
/*120 */ 					);                                                                                   // 0.0
/*122 */ #else                                                                                     // 0.0
/*124 */ 				for(i=0; i<numLines; i++)                                                             // 0.0
/*126 */ 					memcpy(	&(dst[dstStride*i]),                                                         // 0.0
/*128 */ 						&(src[srcStride*i]), BLOCK_SIZE);                                                   // 0.0
/*130 */ #endif                                                                                    // 0.0
/*132 */ 	}                                                                                        // 0.0
/*134 */ 	else                                                                                     // 0.0
/*136 */ 	{                                                                                        // 0.0
/*138 */ #ifdef HAVE_MMX                                                                           // 0.0
/*140 */ 					asm volatile(                                                                        // 0.0
/*142 */ 						"movl %4, %%eax \n\t"                                                               // 0.0
/*144 */ 						"movl %%eax, temp0\n\t"                                                             // 0.0
/*146 */ 						"pushl %0 \n\t"                                                                     // 0.0
/*148 */ 						"pushl %1 \n\t"                                                                     // 0.0
/*150 */ 						"leal (%2,%2), %%eax	\n\t"                                                          // 0.0
/*152 */ 						"leal (%3,%3), %%ebx	\n\t"                                                          // 0.0
/*154 */ 						"movq packedYOffset, %%mm2	\n\t"                                                    // 0.0
/*156 */ 						"movq packedYScale, %%mm3	\n\t"                                                     // 0.0
/*160 */ #define SIMPLE_CPY					\                                                                  // 0.0
/*162 */ 						"movq (%0), %%mm0	\n\t"\                                                            // 0.0
/*164 */ 						"movq (%0,%2), %%mm1	\n\t"\                                                         // 0.0
/*166 */ 						"movq %%mm0, (%1)	\n\t"\                                                            // 0.0
/*168 */ 						"movq %%mm1, (%1, %3)	\n\t"\                                                        // 0.0
/*172 */ 						"1:			\n\t"                                                                         // 0.0
/*174 */ SIMPLE_CPY                                                                                // 0.0
/*176 */ 						"addl %%eax, %0		\n\t"                                                              // 0.0
/*178 */ 						"addl %%ebx, %1		\n\t"                                                              // 0.0
/*180 */ SIMPLE_CPY                                                                                // 0.0
/*182 */ 						"addl %%eax, %0		\n\t"                                                              // 0.0
/*184 */ 						"addl %%ebx, %1		\n\t"                                                              // 0.0
/*186 */ 						"decl temp0		\n\t"                                                                  // 0.0
/*188 */ 						"jnz 1b			\n\t"                                                                     // 0.0
/*192 */ 						"popl %1 \n\t"                                                                      // 0.0
/*194 */ 						"popl %0 \n\t"                                                                      // 0.0
/*196 */ 						: : "r" (src),                                                                      // 0.0
/*198 */ 						"r" (dst),                                                                          // 0.0
/*200 */ 						"r" (srcStride),                                                                    // 0.0
/*202 */ 						"r" (dstStride),                                                                    // 0.0
/*204 */ 						"m" (numLines>>2)                                                                   // 0.0
/*206 */ 						: "%eax", "%ebx"                                                                    // 0.0
/*208 */ 					);                                                                                   // 0.0
/*210 */ #else                                                                                     // 0.0
/*212 */ 				for(i=0; i<numLines; i++)                                                             // 0.0
/*214 */ 					memcpy(	&(dst[dstStride*i]),                                                         // 0.0
/*216 */ 						&(src[srcStride*i]), BLOCK_SIZE);                                                   // 0.0
/*218 */ #endif                                                                                    // 0.0
/*220 */ 	}                                                                                        // 0.0
/*222 */ }                                                                                         // 0.0
