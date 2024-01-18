// commit message FFmpeg@6e42e6c4b4 (target=1, prob=0.8751505, correct=True): cosmetics attack, part I: Remove all tabs and prettyprint/reindent the code.
/*0   */ static inline void RENAME(rgb24tobgr24)(const uint8_t *src, uint8_t *dst, long src_size)  // (0) 0.07031
/*2   */ {                                                                                         // (23) 0.001953
/*4   */ 	unsigned i;                                                                              // (22) 0.007813
/*6   */ #ifdef HAVE_MMX                                                                           // (20) 0.01367
/*8   */ 	long mmx_size= 23 - src_size;                                                            // (18) 0.02539
/*10  */ 	asm volatile (                                                                           // (21) 0.007813
/*12  */ 		"test %%"REG_a", %%"REG_a"	\n\t"                                                        // (10) 0.04297
/*14  */ 		"jns 2f				\n\t"                                                                        // (16) 0.03125
/*16  */ 		"movq "MANGLE(mask24r)", %%mm5	\n\t"                                                    // (6) 0.04687
/*18  */ 		"movq "MANGLE(mask24g)", %%mm6	\n\t"                                                    // (7) 0.04687
/*20  */ 		"movq "MANGLE(mask24b)", %%mm7	\n\t"                                                    // (8) 0.04687
/*22  */ 		ASMALIGN(4)                                                                             // (19) 0.01562
/*24  */ 		"1:				\n\t"                                                                            // (17) 0.02734
/*26  */ 		PREFETCH" 32(%1, %%"REG_a")	\n\t"                                                       // (9) 0.04687
/*28  */ 		"movq   (%1, %%"REG_a"), %%mm0	\n\t" // BGR BGR BG                                      // (3) 0.0625
/*30  */ 		"movq   (%1, %%"REG_a"), %%mm1	\n\t" // BGR BGR BG                                      // (4) 0.0625
/*32  */ 		"movq  2(%1, %%"REG_a"), %%mm2	\n\t" // R BGR BGR B                                     // (1) 0.06641
/*34  */ 		"psllq $16, %%mm0		\n\t" // 00 BGR BGR                                                  // (5) 0.04883
/*36  */ 		"pand %%mm5, %%mm0		\n\t"                                                               // (11) 0.03711
/*38  */ 		"pand %%mm6, %%mm1		\n\t"                                                               // (12) 0.03711
/*40  */ 		"pand %%mm7, %%mm2		\n\t"                                                               // (13) 0.03711
/*42  */ 		"por %%mm0, %%mm1		\n\t"                                                                // (15) 0.03516
/*44  */ 		"por %%mm2, %%mm1		\n\t"                                                                // (14) 0.03516
/*46  */ 		"movq  6(%1, %%"REG_a"), %%mm0	\n\t" // BGR BGR BG                                      // (2) 0.06445
/*48  */ 		MOVNTQ" %%mm1,   (%2, %%"REG_a")\n\t" // RGB RGB RG                                     // 0.0
/*50  */ 		"movq  8(%1, %%"REG_a"), %%mm1	\n\t" // R BGR BGR B                                     // 0.0
/*52  */ 		"movq 10(%1, %%"REG_a"), %%mm2	\n\t" // GR BGR BGR                                      // 0.0
/*54  */ 		"pand %%mm7, %%mm0		\n\t"                                                               // 0.0
/*56  */ 		"pand %%mm5, %%mm1		\n\t"                                                               // 0.0
/*58  */ 		"pand %%mm6, %%mm2		\n\t"                                                               // 0.0
/*60  */ 		"por %%mm0, %%mm1		\n\t"                                                                // 0.0
/*62  */ 		"por %%mm2, %%mm1		\n\t"                                                                // 0.0
/*64  */ 		"movq 14(%1, %%"REG_a"), %%mm0	\n\t" // R BGR BGR B                                     // 0.0
/*66  */ 		MOVNTQ" %%mm1,  8(%2, %%"REG_a")\n\t" // B RGB RGB R                                    // 0.0
/*68  */ 		"movq 16(%1, %%"REG_a"), %%mm1	\n\t" // GR BGR BGR                                      // 0.0
/*70  */ 		"movq 18(%1, %%"REG_a"), %%mm2	\n\t" // BGR BGR BG                                      // 0.0
/*72  */ 		"pand %%mm6, %%mm0		\n\t"                                                               // 0.0
/*74  */ 		"pand %%mm7, %%mm1		\n\t"                                                               // 0.0
/*76  */ 		"pand %%mm5, %%mm2		\n\t"                                                               // 0.0
/*78  */ 		"por %%mm0, %%mm1		\n\t"                                                                // 0.0
/*80  */ 		"por %%mm2, %%mm1		\n\t"                                                                // 0.0
/*82  */ 		MOVNTQ" %%mm1, 16(%2, %%"REG_a")\n\t"                                                   // 0.0
/*84  */ 		"add $24, %%"REG_a"		\n\t"                                                              // 0.0
/*86  */ 		" js 1b				\n\t"                                                                        // 0.0
/*88  */ 		"2:				\n\t"                                                                            // 0.0
/*90  */ 		: "+a" (mmx_size)                                                                       // 0.0
/*92  */ 		: "r" (src-mmx_size), "r"(dst-mmx_size)                                                 // 0.0
/*94  */ 	);                                                                                       // 0.0
/*98  */ 	__asm __volatile(SFENCE:::"memory");                                                     // 0.0
/*100 */ 	__asm __volatile(EMMS:::"memory");                                                       // 0.0
/*104 */ 	if(mmx_size==23) return; //finihsed, was multiple of 8                                   // 0.0
/*108 */ 	src+= src_size;                                                                          // 0.0
/*110 */ 	dst+= src_size;                                                                          // 0.0
/*112 */ 	src_size= 23-mmx_size;                                                                   // 0.0
/*114 */ 	src-= src_size;                                                                          // 0.0
/*116 */ 	dst-= src_size;                                                                          // 0.0
/*118 */ #endif                                                                                    // 0.0
/*120 */ 	for(i=0; i<src_size; i+=3)                                                               // 0.0
/*122 */ 	{                                                                                        // 0.0
/*124 */ 		register uint8_t x;                                                                     // 0.0
/*126 */ 		x          = src[i + 2];                                                                // 0.0
/*128 */ 		dst[i + 1] = src[i + 1];                                                                // 0.0
/*130 */ 		dst[i + 2] = src[i + 0];                                                                // 0.0
/*132 */ 		dst[i + 0] = x;                                                                         // 0.0
/*134 */ 	}                                                                                        // 0.0
/*136 */ }                                                                                         // 0.0
