// commit message FFmpeg@6e42e6c4b4 (target=1, prob=0.9385782, correct=True): cosmetics attack, part I: Remove all tabs and prettyprint/reindent the code.
/*0   */ static inline void RENAME(vu9_to_vu12)(const uint8_t *src1, const uint8_t *src2,  // (0) 0.06446
/*2   */ 			uint8_t *dst1, uint8_t *dst2,                                                  // (9) 0.04102
/*4   */ 			long width, long height,                                                       // (20) 0.01758
/*6   */ 			long srcStride1, long srcStride2,                                              // (15) 0.0293
/*8   */ 			long dstStride1, long dstStride2)                                              // (12) 0.0293
/*10  */ {                                                                                 // (28) 0.001954
/*12  */     long y,x,w,h;                                                                 // (19) 0.02344
/*14  */     w=width/2; h=height/2;                                                        // (14) 0.0293
/*16  */ #ifdef HAVE_MMX                                                                   // (23) 0.01367
/*18  */     asm volatile(                                                                 // (22) 0.01367
/*20  */ 	PREFETCH" %0\n\t"                                                                // (17) 0.02539
/*22  */ 	PREFETCH" %1\n\t"                                                                // (18) 0.02539
/*24  */ 	::"m"(*(src1+srcStride1)),"m"(*(src2+srcStride2)):"memory");                     // (1) 0.0625
/*26  */ #endif                                                                            // (26) 0.003906
/*28  */     for(y=0;y<h;y++){                                                             // (11) 0.03125
/*30  */ 	const uint8_t* s1=src1+srcStride1*(y>>1);                                        // (8) 0.04492
/*32  */ 	uint8_t* d=dst1+dstStride1*y;                                                    // (10) 0.03906
/*34  */ 	x=0;                                                                             // (25) 0.009766
/*36  */ #ifdef HAVE_MMX                                                                   // (24) 0.01367
/*38  */ 	for(;x<w-31;x+=32)                                                               // (16) 0.02734
/*40  */ 	{                                                                                // (27) 0.003906
/*42  */ 	    asm volatile(                                                                // (21) 0.01562
/*44  */ 		PREFETCH" 32%1\n\t"                                                             // (13) 0.0293
/*46  */ 	        "movq	%1, %%mm0\n\t"                                                     // (7) 0.04687
/*48  */ 	        "movq	8%1, %%mm2\n\t"                                                    // (6) 0.04883
/*50  */ 	        "movq	16%1, %%mm4\n\t"                                                   // (2) 0.04883
/*52  */ 	        "movq	24%1, %%mm6\n\t"                                                   // (4) 0.04883
/*54  */ 	        "movq	%%mm0, %%mm1\n\t"                                                  // (5) 0.04883
/*56  */ 	        "movq	%%mm2, %%mm3\n\t"                                                  // (3) 0.04883
/*58  */ 	        "movq	%%mm4, %%mm5\n\t"                                                  // 0.0
/*60  */ 	        "movq	%%mm6, %%mm7\n\t"                                                  // 0.0
/*62  */ 		"punpcklbw %%mm0, %%mm0\n\t"                                                    // 0.0
/*64  */ 		"punpckhbw %%mm1, %%mm1\n\t"                                                    // 0.0
/*66  */ 		"punpcklbw %%mm2, %%mm2\n\t"                                                    // 0.0
/*68  */ 		"punpckhbw %%mm3, %%mm3\n\t"                                                    // 0.0
/*70  */ 		"punpcklbw %%mm4, %%mm4\n\t"                                                    // 0.0
/*72  */ 		"punpckhbw %%mm5, %%mm5\n\t"                                                    // 0.0
/*74  */ 		"punpcklbw %%mm6, %%mm6\n\t"                                                    // 0.0
/*76  */ 		"punpckhbw %%mm7, %%mm7\n\t"                                                    // 0.0
/*78  */ 		MOVNTQ"	%%mm0, %0\n\t"                                                          // 0.0
/*80  */ 		MOVNTQ"	%%mm1, 8%0\n\t"                                                         // 0.0
/*82  */ 		MOVNTQ"	%%mm2, 16%0\n\t"                                                        // 0.0
/*84  */ 		MOVNTQ"	%%mm3, 24%0\n\t"                                                        // 0.0
/*86  */ 		MOVNTQ"	%%mm4, 32%0\n\t"                                                        // 0.0
/*88  */ 		MOVNTQ"	%%mm5, 40%0\n\t"                                                        // 0.0
/*90  */ 		MOVNTQ"	%%mm6, 48%0\n\t"                                                        // 0.0
/*92  */ 		MOVNTQ"	%%mm7, 56%0"                                                            // 0.0
/*94  */ 		:"=m"(d[2*x])                                                                   // 0.0
/*96  */ 		:"m"(s1[x])                                                                     // 0.0
/*98  */ 		:"memory");                                                                     // 0.0
/*100 */ 	}                                                                                // 0.0
/*102 */ #endif                                                                            // 0.0
/*104 */ 	for(;x<w;x++) d[2*x]=d[2*x+1]=s1[x];                                             // 0.0
/*106 */     }                                                                             // 0.0
/*108 */     for(y=0;y<h;y++){                                                             // 0.0
/*110 */ 	const uint8_t* s2=src2+srcStride2*(y>>1);                                        // 0.0
/*112 */ 	uint8_t* d=dst2+dstStride2*y;                                                    // 0.0
/*114 */ 	x=0;                                                                             // 0.0
/*116 */ #ifdef HAVE_MMX                                                                   // 0.0
/*118 */ 	for(;x<w-31;x+=32)                                                               // 0.0
/*120 */ 	{                                                                                // 0.0
/*122 */ 	    asm volatile(                                                                // 0.0
/*124 */ 		PREFETCH" 32%1\n\t"                                                             // 0.0
/*126 */ 	        "movq	%1, %%mm0\n\t"                                                     // 0.0
/*128 */ 	        "movq	8%1, %%mm2\n\t"                                                    // 0.0
/*130 */ 	        "movq	16%1, %%mm4\n\t"                                                   // 0.0
/*132 */ 	        "movq	24%1, %%mm6\n\t"                                                   // 0.0
/*134 */ 	        "movq	%%mm0, %%mm1\n\t"                                                  // 0.0
/*136 */ 	        "movq	%%mm2, %%mm3\n\t"                                                  // 0.0
/*138 */ 	        "movq	%%mm4, %%mm5\n\t"                                                  // 0.0
/*140 */ 	        "movq	%%mm6, %%mm7\n\t"                                                  // 0.0
/*142 */ 		"punpcklbw %%mm0, %%mm0\n\t"                                                    // 0.0
/*144 */ 		"punpckhbw %%mm1, %%mm1\n\t"                                                    // 0.0
/*146 */ 		"punpcklbw %%mm2, %%mm2\n\t"                                                    // 0.0
/*148 */ 		"punpckhbw %%mm3, %%mm3\n\t"                                                    // 0.0
/*150 */ 		"punpcklbw %%mm4, %%mm4\n\t"                                                    // 0.0
/*152 */ 		"punpckhbw %%mm5, %%mm5\n\t"                                                    // 0.0
/*154 */ 		"punpcklbw %%mm6, %%mm6\n\t"                                                    // 0.0
/*156 */ 		"punpckhbw %%mm7, %%mm7\n\t"                                                    // 0.0
/*158 */ 		MOVNTQ"	%%mm0, %0\n\t"                                                          // 0.0
/*160 */ 		MOVNTQ"	%%mm1, 8%0\n\t"                                                         // 0.0
/*162 */ 		MOVNTQ"	%%mm2, 16%0\n\t"                                                        // 0.0
/*164 */ 		MOVNTQ"	%%mm3, 24%0\n\t"                                                        // 0.0
/*166 */ 		MOVNTQ"	%%mm4, 32%0\n\t"                                                        // 0.0
/*168 */ 		MOVNTQ"	%%mm5, 40%0\n\t"                                                        // 0.0
/*170 */ 		MOVNTQ"	%%mm6, 48%0\n\t"                                                        // 0.0
/*172 */ 		MOVNTQ"	%%mm7, 56%0"                                                            // 0.0
/*174 */ 		:"=m"(d[2*x])                                                                   // 0.0
/*176 */ 		:"m"(s2[x])                                                                     // 0.0
/*178 */ 		:"memory");                                                                     // 0.0
/*180 */ 	}                                                                                // 0.0
/*182 */ #endif                                                                            // 0.0
/*184 */ 	for(;x<w;x++) d[2*x]=d[2*x+1]=s2[x];                                             // 0.0
/*186 */     }                                                                             // 0.0
/*188 */ #ifdef HAVE_MMX                                                                   // 0.0
/*190 */ 	asm(                                                                             // 0.0
/*192 */ 		EMMS" \n\t"                                                                     // 0.0
/*194 */ 		SFENCE" \n\t"                                                                   // 0.0
/*196 */ 		::: "memory"                                                                    // 0.0
/*198 */ 		);                                                                              // 0.0
/*200 */ #endif                                                                            // 0.0
/*202 */ }                                                                                 // 0.0
