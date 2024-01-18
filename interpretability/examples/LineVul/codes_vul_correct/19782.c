// commit message FFmpeg@6e42e6c4b4 (target=1, prob=0.9911265, correct=True): cosmetics attack, part I: Remove all tabs and prettyprint/reindent the code.
/*0   */ static inline void RENAME(planar2x)(const uint8_t *src, uint8_t *dst, long srcWidth, long srcHeight, long srcStride, long dstStride)  // (0) 0.08984
/*2   */ {                                                                                                                                     // (24) 0.001953
/*4   */ 	long x,y;                                                                                                                            // (20) 0.01172
/*8   */ 	dst[0]= src[0];                                                                                                                      // (19) 0.01953
/*12  */ 	// first line                                                                                                                        // (22) 0.007812
/*14  */ 	for(x=0; x<srcWidth-1; x++){                                                                                                         // (14) 0.0332
/*16  */ 		dst[2*x+1]= (3*src[x] +   src[x+1])>>2;                                                                                             // (1) 0.05859
/*18  */ 		dst[2*x+2]= (  src[x] + 3*src[x+1])>>2;                                                                                             // (2) 0.05664
/*20  */ 	}                                                                                                                                    // (23) 0.003906
/*22  */ 	dst[2*srcWidth-1]= src[srcWidth-1];                                                                                                  // (13) 0.03516
/*26  */         dst+= dstStride;                                                                                                              // (18) 0.02539
/*30  */ 	for(y=1; y<srcHeight; y++){                                                                                                          // (15) 0.0293
/*32  */ #if defined (HAVE_MMX2) || defined (HAVE_3DNOW)                                                                                       // (10) 0.04102
/*34  */ 		const long mmxSize= srcWidth&~15;                                                                                                   // (17) 0.02734
/*36  */ 		asm volatile(                                                                                                                       // (21) 0.009766
/*38  */ 			"mov %4, %%"REG_a"		\n\t"                                                                                                          // (9) 0.04297
/*40  */ 			"1:				\n\t"                                                                                                                       // (16) 0.0293
/*42  */ 			"movq (%0, %%"REG_a"), %%mm0	\n\t"                                                                                                 // (7) 0.04883
/*44  */ 			"movq (%1, %%"REG_a"), %%mm1	\n\t"                                                                                                 // (8) 0.04883
/*46  */ 			"movq 1(%0, %%"REG_a"), %%mm2	\n\t"                                                                                                // (5) 0.05273
/*48  */ 			"movq 1(%1, %%"REG_a"), %%mm3	\n\t"                                                                                                // (6) 0.05273
/*50  */ 			"movq -1(%0, %%"REG_a"), %%mm4	\n\t"                                                                                               // (3) 0.05469
/*52  */ 			"movq -1(%1, %%"REG_a"), %%mm5	\n\t"                                                                                               // (4) 0.05469
/*54  */ 			PAVGB" %%mm0, %%mm5		\n\t"                                                                                                         // (11) 0.04102
/*56  */ 			PAVGB" %%mm0, %%mm3		\n\t"                                                                                                         // (12) 0.04102
/*58  */ 			PAVGB" %%mm0, %%mm5		\n\t"                                                                                                         // 0.0
/*60  */ 			PAVGB" %%mm0, %%mm3		\n\t"                                                                                                         // 0.0
/*62  */ 			PAVGB" %%mm1, %%mm4		\n\t"                                                                                                         // 0.0
/*64  */ 			PAVGB" %%mm1, %%mm2		\n\t"                                                                                                         // 0.0
/*66  */ 			PAVGB" %%mm1, %%mm4		\n\t"                                                                                                         // 0.0
/*68  */ 			PAVGB" %%mm1, %%mm2		\n\t"                                                                                                         // 0.0
/*70  */ 			"movq %%mm5, %%mm7		\n\t"                                                                                                          // 0.0
/*72  */ 			"movq %%mm4, %%mm6		\n\t"                                                                                                          // 0.0
/*74  */ 			"punpcklbw %%mm3, %%mm5		\n\t"                                                                                                     // 0.0
/*76  */ 			"punpckhbw %%mm3, %%mm7		\n\t"                                                                                                     // 0.0
/*78  */ 			"punpcklbw %%mm2, %%mm4		\n\t"                                                                                                     // 0.0
/*80  */ 			"punpckhbw %%mm2, %%mm6		\n\t"                                                                                                     // 0.0
/*82  */ #if 1                                                                                                                                 // 0.0
/*84  */ 			MOVNTQ" %%mm5, (%2, %%"REG_a", 2)\n\t"                                                                                             // 0.0
/*86  */ 			MOVNTQ" %%mm7, 8(%2, %%"REG_a", 2)\n\t"                                                                                            // 0.0
/*88  */ 			MOVNTQ" %%mm4, (%3, %%"REG_a", 2)\n\t"                                                                                             // 0.0
/*90  */ 			MOVNTQ" %%mm6, 8(%3, %%"REG_a", 2)\n\t"                                                                                            // 0.0
/*92  */ #else                                                                                                                                 // 0.0
/*94  */ 			"movq %%mm5, (%2, %%"REG_a", 2)	\n\t"                                                                                              // 0.0
/*96  */ 			"movq %%mm7, 8(%2, %%"REG_a", 2)\n\t"                                                                                              // 0.0
/*98  */ 			"movq %%mm4, (%3, %%"REG_a", 2)	\n\t"                                                                                              // 0.0
/*100 */ 			"movq %%mm6, 8(%3, %%"REG_a", 2)\n\t"                                                                                              // 0.0
/*102 */ #endif                                                                                                                                // 0.0
/*104 */ 			"add $8, %%"REG_a"		\n\t"                                                                                                          // 0.0
/*106 */ 			" js 1b				\n\t"                                                                                                                   // 0.0
/*108 */ 			:: "r" (src + mmxSize  ), "r" (src + srcStride + mmxSize  ),                                                                       // 0.0
/*110 */ 			   "r" (dst + mmxSize*2), "r" (dst + dstStride + mmxSize*2),                                                                       // 0.0
/*112 */ 			   "g" (-mmxSize)                                                                                                                  // 0.0
/*114 */ 			: "%"REG_a                                                                                                                         // 0.0
/*118 */ 		);                                                                                                                                  // 0.0
/*120 */ #else                                                                                                                                 // 0.0
/*122 */ 		const long mmxSize=1;                                                                                                               // 0.0
/*124 */ #endif                                                                                                                                // 0.0
/*126 */ 		dst[0        ]= (3*src[0] +   src[srcStride])>>2;                                                                                   // 0.0
/*128 */ 		dst[dstStride]= (  src[0] + 3*src[srcStride])>>2;                                                                                   // 0.0
/*132 */ 		for(x=mmxSize-1; x<srcWidth-1; x++){                                                                                                // 0.0
/*134 */ 			dst[2*x          +1]= (3*src[x+0] +   src[x+srcStride+1])>>2;                                                                      // 0.0
/*136 */ 			dst[2*x+dstStride+2]= (  src[x+0] + 3*src[x+srcStride+1])>>2;                                                                      // 0.0
/*138 */ 			dst[2*x+dstStride+1]= (  src[x+1] + 3*src[x+srcStride  ])>>2;                                                                      // 0.0
/*140 */ 			dst[2*x          +2]= (3*src[x+1] +   src[x+srcStride  ])>>2;                                                                      // 0.0
/*142 */ 		}                                                                                                                                   // 0.0
/*144 */ 		dst[srcWidth*2 -1            ]= (3*src[srcWidth-1] +   src[srcWidth-1 + srcStride])>>2;                                             // 0.0
/*146 */ 		dst[srcWidth*2 -1 + dstStride]= (  src[srcWidth-1] + 3*src[srcWidth-1 + srcStride])>>2;                                             // 0.0
/*150 */ 		dst+=dstStride*2;                                                                                                                   // 0.0
/*152 */ 		src+=srcStride;                                                                                                                     // 0.0
/*154 */ 	}                                                                                                                                    // 0.0
/*158 */ 	// last line                                                                                                                         // 0.0
/*160 */ #if 1                                                                                                                                 // 0.0
/*162 */ 	dst[0]= src[0];                                                                                                                      // 0.0
/*166 */ 	for(x=0; x<srcWidth-1; x++){                                                                                                         // 0.0
/*168 */ 		dst[2*x+1]= (3*src[x] +   src[x+1])>>2;                                                                                             // 0.0
/*170 */ 		dst[2*x+2]= (  src[x] + 3*src[x+1])>>2;                                                                                             // 0.0
/*172 */ 	}                                                                                                                                    // 0.0
/*174 */ 	dst[2*srcWidth-1]= src[srcWidth-1];                                                                                                  // 0.0
/*176 */ #else                                                                                                                                 // 0.0
/*178 */ 	for(x=0; x<srcWidth; x++){                                                                                                           // 0.0
/*180 */ 		dst[2*x+0]=                                                                                                                         // 0.0
/*182 */ 		dst[2*x+1]= src[x];                                                                                                                 // 0.0
/*184 */ 	}                                                                                                                                    // 0.0
/*186 */ #endif                                                                                                                                // 0.0
/*190 */ #ifdef HAVE_MMX                                                                                                                       // 0.0
/*192 */ asm volatile(   EMMS" \n\t"                                                                                                           // 0.0
/*194 */         	SFENCE" \n\t"                                                                                                                // 0.0
/*196 */         	:::"memory");                                                                                                                // 0.0
/*198 */ #endif                                                                                                                                // 0.0
/*200 */ }                                                                                                                                     // 0.0
