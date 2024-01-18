// commit message FFmpeg@2da0d70d5e (target=1, prob=0.9506774, correct=True): cosmetics attack, part IV: Remove all tabs and prettyprint/reindent the code.
/*0  */ static inline void RENAME(yuy2ToUV)(uint8_t *dstU, uint8_t *dstV, uint8_t *src1, uint8_t *src2, long width)  // (0) 0.09766
/*2  */ {                                                                                                            // (25) 0.001953
/*4  */ #ifdef HAVE_MMX                                                                                              // (20) 0.01367
/*6  */ 	asm volatile(                                                                                               // (21) 0.007812
/*8  */ 		"movq "MANGLE(bm01010101)", %%mm4\n\t"                                                                     // (4) 0.04883
/*10 */ 		"mov %0, %%"REG_a"		\n\t"                                                                                  // (7) 0.04102
/*12 */ 		"1:				\n\t"                                                                                               // (18) 0.02734
/*14 */ 		"movq (%1, %%"REG_a",4), %%mm0	\n\t"                                                                       // (3) 0.05078
/*16 */ 		"movq 8(%1, %%"REG_a",4), %%mm1	\n\t"                                                                      // (2) 0.05469
/*18 */ 		"psrlw $8, %%mm0		\n\t"                                                                                    // (13) 0.03711
/*20 */ 		"psrlw $8, %%mm1		\n\t"                                                                                    // (14) 0.03711
/*22 */ 		"packuswb %%mm1, %%mm0		\n\t"                                                                              // (8) 0.03906
/*24 */ 		"movq %%mm0, %%mm1		\n\t"                                                                                  // (9) 0.03906
/*26 */ 		"psrlw $8, %%mm0		\n\t"                                                                                    // (15) 0.03711
/*28 */ 		"pand %%mm4, %%mm1		\n\t"                                                                                  // (16) 0.03711
/*30 */ 		"packuswb %%mm0, %%mm0		\n\t"                                                                              // (10) 0.03906
/*32 */ 		"packuswb %%mm1, %%mm1		\n\t"                                                                              // (11) 0.03906
/*34 */ 		"movd %%mm0, (%3, %%"REG_a")	\n\t"                                                                         // (5) 0.04883
/*36 */ 		"movd %%mm1, (%2, %%"REG_a")	\n\t"                                                                         // (6) 0.04883
/*38 */ 		"add $4, %%"REG_a"		\n\t"                                                                                  // (12) 0.03906
/*40 */ 		" js 1b				\n\t"                                                                                           // (17) 0.0293
/*42 */ 		: : "g" (-width), "r" (src1+width*4), "r" (dstU+width), "r" (dstV+width)                                   // (1) 0.08008
/*44 */ 		: "%"REG_a                                                                                                 // (19) 0.01562
/*46 */ 	);                                                                                                          // (24) 0.003906
/*48 */ #else                                                                                                        // (23) 0.003906
/*50 */ 	int i;                                                                                                      // (22) 0.007812
/*52 */ 	for(i=0; i<width; i++)                                                                                      // 0.0
/*54 */ 	{                                                                                                           // 0.0
/*56 */ 		dstU[i]= src1[4*i + 1];                                                                                    // 0.0
/*58 */ 		dstV[i]= src1[4*i + 3];                                                                                    // 0.0
/*60 */ 	}                                                                                                           // 0.0
/*62 */ #endif                                                                                                       // 0.0
/*64 */         assert(src1 == src2);                                                                                // 0.0
/*66 */ }                                                                                                            // 0.0
