// commit message FFmpeg@7f526efd17 (target=1, prob=0.95224446, correct=True): Change unsigned->signed and int->long, this fits the asm code better on 64 bit systems. Also fixes several crashes because (long)-i is incorrect if i is unsigned.
/*0  */ static inline void RENAME(yuy2ToUV)(uint8_t *dstU, uint8_t *dstV, uint8_t *src1, uint8_t *src2, int width)  // (0) 0.09766
/*2  */ {                                                                                                           // (22) 0.001953
/*4  */ #if defined (HAVE_MMX2) || defined (HAVE_3DNOW)                                                             // (8) 0.04102
/*6  */ 	asm volatile(                                                                                              // (21) 0.007813
/*8  */ 		"movq "MANGLE(bm01010101)", %%mm4\n\t"                                                                    // (5) 0.04883
/*10 */ 		"mov %0, %%"REG_a"		\n\t"                                                                                 // (9) 0.04102
/*12 */ 		"1:				\n\t"                                                                                              // (20) 0.02734
/*14 */ 		"movq (%1, %%"REG_a",4), %%mm0	\n\t"                                                                      // (3) 0.05078
/*16 */ 		"movq 8(%1, %%"REG_a",4), %%mm1	\n\t"                                                                     // (2) 0.05469
/*18 */ 		"movq (%2, %%"REG_a",4), %%mm2	\n\t"                                                                      // (4) 0.05078
/*20 */ 		"movq 8(%2, %%"REG_a",4), %%mm3	\n\t"                                                                     // (1) 0.05469
/*22 */ 		PAVGB(%%mm2, %%mm0)                                                                                       // (18) 0.02734
/*24 */ 		PAVGB(%%mm3, %%mm1)                                                                                       // (19) 0.02734
/*26 */ 		"psrlw $8, %%mm0		\n\t"                                                                                   // (14) 0.03711
/*28 */ 		"psrlw $8, %%mm1		\n\t"                                                                                   // (15) 0.03711
/*30 */ 		"packuswb %%mm1, %%mm0		\n\t"                                                                             // (10) 0.03906
/*32 */ 		"movq %%mm0, %%mm1		\n\t"                                                                                 // (12) 0.03906
/*34 */ 		"psrlw $8, %%mm0		\n\t"                                                                                   // (16) 0.03711
/*36 */ 		"pand %%mm4, %%mm1		\n\t"                                                                                 // (17) 0.03711
/*38 */ 		"packuswb %%mm0, %%mm0		\n\t"                                                                             // (11) 0.03906
/*40 */ 		"packuswb %%mm1, %%mm1		\n\t"                                                                             // (13) 0.03906
/*42 */ 		"movd %%mm0, (%4, %%"REG_a")	\n\t"                                                                        // (6) 0.04883
/*44 */ 		"movd %%mm1, (%3, %%"REG_a")	\n\t"                                                                        // (7) 0.04883
/*46 */ 		"add $4, %%"REG_a"		\n\t"                                                                                 // 0.0
/*48 */ 		" js 1b				\n\t"                                                                                          // 0.0
/*50 */ 		: : "g" ((long)-width), "r" (src1+width*4), "r" (src2+width*4), "r" (dstU+width), "r" (dstV+width)        // 0.0
/*52 */ 		: "%"REG_a                                                                                                // 0.0
/*54 */ 	);                                                                                                         // 0.0
/*56 */ #else                                                                                                       // 0.0
/*58 */ 	int i;                                                                                                     // 0.0
/*60 */ 	for(i=0; i<width; i++)                                                                                     // 0.0
/*62 */ 	{                                                                                                          // 0.0
/*64 */ 		dstU[i]= (src1[4*i + 1] + src2[4*i + 1])>>1;                                                              // 0.0
/*66 */ 		dstV[i]= (src1[4*i + 3] + src2[4*i + 3])>>1;                                                              // 0.0
/*68 */ 	}                                                                                                          // 0.0
/*70 */ #endif                                                                                                      // 0.0
/*72 */ }                                                                                                           // 0.0
