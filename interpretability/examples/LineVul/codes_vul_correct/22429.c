// commit message FFmpeg@7f526efd17 (target=1, prob=0.9542618, correct=True): Change unsigned->signed and int->long, this fits the asm code better on 64 bit systems. Also fixes several crashes because (long)-i is incorrect if i is unsigned.
/*0   */ static inline void RENAME(hScale)(int16_t *dst, int dstW, uint8_t *src, int srcW, int xInc,  // (0) 0.07229
/*2   */ 				  int16_t *filter, int16_t *filterPos, int filterSize)                                   // (8) 0.04687
/*4   */ {                                                                                            // (25) 0.001953
/*6   */ #ifdef HAVE_MMX                                                                              // (22) 0.01367
/*8   */ 	assert(filterSize % 4 == 0 && filterSize>0);                                                // (15) 0.0293
/*10  */ 	if(filterSize==4) // allways true for upscaling, sometimes for down too                     // (13) 0.04101
/*12  */ 	{                                                                                           // (24) 0.003906
/*14  */ 		long counter= -2*dstW;                                                                     // (18) 0.02344
/*16  */ 		filter-= counter*2;                                                                        // (21) 0.01758
/*18  */ 		filterPos-= counter/2;                                                                     // (20) 0.01953
/*20  */ 		dst-= counter/2;                                                                           // (19) 0.01953
/*22  */ 		asm volatile(                                                                              // (23) 0.009766
/*24  */ 			"pxor %%mm7, %%mm7		\n\t"                                                                 // (14) 0.03906
/*26  */ 			"movq "MANGLE(w02)", %%mm6	\n\t"                                                          // (9) 0.04687
/*28  */ 			"push %%"REG_BP"		\n\t" // we use 7 regs here ...                                         // (4) 0.05078
/*30  */ 			"mov %%"REG_a", %%"REG_BP"	\n\t"                                                          // (10) 0.04687
/*32  */ 			".balign 16			\n\t"                                                                       // (16) 0.0293
/*34  */ 			"1:				\n\t"                                                                              // (17) 0.0293
/*36  */ 			"movzwl (%2, %%"REG_BP"), %%eax	\n\t"                                                     // (3) 0.05078
/*38  */ 			"movzwl 2(%2, %%"REG_BP"), %%ebx\n\t"                                                     // (2) 0.05273
/*40  */ 			"movq (%1, %%"REG_BP", 4), %%mm1\n\t"                                                     // (5) 0.05078
/*42  */ 			"movq 8(%1, %%"REG_BP", 4), %%mm3\n\t"                                                    // (1) 0.05469
/*44  */ 			"movd (%3, %%"REG_a"), %%mm0	\n\t"                                                        // (6) 0.04883
/*46  */ 			"movd (%3, %%"REG_b"), %%mm2	\n\t"                                                        // (7) 0.04883
/*48  */ 			"punpcklbw %%mm7, %%mm0		\n\t"                                                            // (12) 0.04492
/*50  */ 			"punpcklbw %%mm7, %%mm2		\n\t"                                                            // (11) 0.04492
/*52  */ 			"pmaddwd %%mm1, %%mm0		\n\t"                                                              // 0.0
/*54  */ 			"pmaddwd %%mm2, %%mm3		\n\t"                                                              // 0.0
/*56  */ 			"psrad $8, %%mm0		\n\t"                                                                   // 0.0
/*58  */ 			"psrad $8, %%mm3		\n\t"                                                                   // 0.0
/*60  */ 			"packssdw %%mm3, %%mm0		\n\t"                                                             // 0.0
/*62  */ 			"pmaddwd %%mm6, %%mm0		\n\t"                                                              // 0.0
/*64  */ 			"packssdw %%mm0, %%mm0		\n\t"                                                             // 0.0
/*66  */ 			"movd %%mm0, (%4, %%"REG_BP")	\n\t"                                                       // 0.0
/*68  */ 			"add $4, %%"REG_BP"		\n\t"                                                                // 0.0
/*70  */ 			" jnc 1b			\n\t"                                                                          // 0.0
/*74  */ 			"pop %%"REG_BP"			\n\t"                                                                   // 0.0
/*76  */ 			: "+a" (counter)                                                                          // 0.0
/*78  */ 			: "c" (filter), "d" (filterPos), "S" (src), "D" (dst)                                     // 0.0
/*80  */ 			: "%"REG_b                                                                                // 0.0
/*82  */ 		);                                                                                         // 0.0
/*84  */ 	}                                                                                           // 0.0
/*86  */ 	else if(filterSize==8)                                                                      // 0.0
/*88  */ 	{                                                                                           // 0.0
/*90  */ 		long counter= -2*dstW;                                                                     // 0.0
/*92  */ 		filter-= counter*4;                                                                        // 0.0
/*94  */ 		filterPos-= counter/2;                                                                     // 0.0
/*96  */ 		dst-= counter/2;                                                                           // 0.0
/*98  */ 		asm volatile(                                                                              // 0.0
/*100 */ 			"pxor %%mm7, %%mm7		\n\t"                                                                 // 0.0
/*102 */ 			"movq "MANGLE(w02)", %%mm6	\n\t"                                                          // 0.0
/*104 */ 			"push %%"REG_BP"		\n\t" // we use 7 regs here ...                                         // 0.0
/*106 */ 			"mov %%"REG_a", %%"REG_BP"	\n\t"                                                          // 0.0
/*108 */ 			".balign 16			\n\t"                                                                       // 0.0
/*110 */ 			"1:				\n\t"                                                                              // 0.0
/*112 */ 			"movzwl (%2, %%"REG_BP"), %%eax	\n\t"                                                     // 0.0
/*114 */ 			"movzwl 2(%2, %%"REG_BP"), %%ebx\n\t"                                                     // 0.0
/*116 */ 			"movq (%1, %%"REG_BP", 8), %%mm1\n\t"                                                     // 0.0
/*118 */ 			"movq 16(%1, %%"REG_BP", 8), %%mm3\n\t"                                                   // 0.0
/*120 */ 			"movd (%3, %%"REG_a"), %%mm0	\n\t"                                                        // 0.0
/*122 */ 			"movd (%3, %%"REG_b"), %%mm2	\n\t"                                                        // 0.0
/*124 */ 			"punpcklbw %%mm7, %%mm0		\n\t"                                                            // 0.0
/*126 */ 			"punpcklbw %%mm7, %%mm2		\n\t"                                                            // 0.0
/*128 */ 			"pmaddwd %%mm1, %%mm0		\n\t"                                                              // 0.0
/*130 */ 			"pmaddwd %%mm2, %%mm3		\n\t"                                                              // 0.0
/*134 */ 			"movq 8(%1, %%"REG_BP", 8), %%mm1\n\t"                                                    // 0.0
/*136 */ 			"movq 24(%1, %%"REG_BP", 8), %%mm5\n\t"                                                   // 0.0
/*138 */ 			"movd 4(%3, %%"REG_a"), %%mm4	\n\t"                                                       // 0.0
/*140 */ 			"movd 4(%3, %%"REG_b"), %%mm2	\n\t"                                                       // 0.0
/*142 */ 			"punpcklbw %%mm7, %%mm4		\n\t"                                                            // 0.0
/*144 */ 			"punpcklbw %%mm7, %%mm2		\n\t"                                                            // 0.0
/*146 */ 			"pmaddwd %%mm1, %%mm4		\n\t"                                                              // 0.0
/*148 */ 			"pmaddwd %%mm2, %%mm5		\n\t"                                                              // 0.0
/*150 */ 			"paddd %%mm4, %%mm0		\n\t"                                                                // 0.0
/*152 */ 			"paddd %%mm5, %%mm3		\n\t"                                                                // 0.0
/*154 */ 						                                                                                       // 0.0
/*156 */ 			"psrad $8, %%mm0		\n\t"                                                                   // 0.0
/*158 */ 			"psrad $8, %%mm3		\n\t"                                                                   // 0.0
/*160 */ 			"packssdw %%mm3, %%mm0		\n\t"                                                             // 0.0
/*162 */ 			"pmaddwd %%mm6, %%mm0		\n\t"                                                              // 0.0
/*164 */ 			"packssdw %%mm0, %%mm0		\n\t"                                                             // 0.0
/*166 */ 			"movd %%mm0, (%4, %%"REG_BP")	\n\t"                                                       // 0.0
/*168 */ 			"add $4, %%"REG_BP"		\n\t"                                                                // 0.0
/*170 */ 			" jnc 1b			\n\t"                                                                          // 0.0
/*174 */ 			"pop %%"REG_BP"			\n\t"                                                                   // 0.0
/*176 */ 			: "+a" (counter)                                                                          // 0.0
/*178 */ 			: "c" (filter), "d" (filterPos), "S" (src), "D" (dst)                                     // 0.0
/*180 */ 			: "%"REG_b                                                                                // 0.0
/*182 */ 		);                                                                                         // 0.0
/*184 */ 	}                                                                                           // 0.0
/*186 */ 	else                                                                                        // 0.0
/*188 */ 	{                                                                                           // 0.0
/*190 */ 		uint8_t *offset = src+filterSize;                                                          // 0.0
/*192 */ 		long counter= -2*dstW;                                                                     // 0.0
/*194 */ //		filter-= counter*filterSize/2;                                                           // 0.0
/*196 */ 		filterPos-= counter/2;                                                                     // 0.0
/*198 */ 		dst-= counter/2;                                                                           // 0.0
/*200 */ 		asm volatile(                                                                              // 0.0
/*202 */ 			"pxor %%mm7, %%mm7		\n\t"                                                                 // 0.0
/*204 */ 			"movq "MANGLE(w02)", %%mm6	\n\t"                                                          // 0.0
/*206 */ 			".balign 16			\n\t"                                                                       // 0.0
/*208 */ 			"1:				\n\t"                                                                              // 0.0
/*210 */ 			"mov %2, %%"REG_c"		\n\t"                                                                 // 0.0
/*212 */ 			"movzwl (%%"REG_c", %0), %%eax	\n\t"                                                      // 0.0
/*214 */ 			"movzwl 2(%%"REG_c", %0), %%ebx	\n\t"                                                     // 0.0
/*216 */ 			"mov %5, %%"REG_c"		\n\t"                                                                 // 0.0
/*218 */ 			"pxor %%mm4, %%mm4		\n\t"                                                                 // 0.0
/*220 */ 			"pxor %%mm5, %%mm5		\n\t"                                                                 // 0.0
/*222 */ 			"2:				\n\t"                                                                              // 0.0
/*224 */ 			"movq (%1), %%mm1		\n\t"                                                                  // 0.0
/*226 */ 			"movq (%1, %6), %%mm3		\n\t"                                                              // 0.0
/*228 */ 			"movd (%%"REG_c", %%"REG_a"), %%mm0\n\t"                                                  // 0.0
/*230 */ 			"movd (%%"REG_c", %%"REG_b"), %%mm2\n\t"                                                  // 0.0
/*232 */ 			"punpcklbw %%mm7, %%mm0		\n\t"                                                            // 0.0
/*234 */ 			"punpcklbw %%mm7, %%mm2		\n\t"                                                            // 0.0
/*236 */ 			"pmaddwd %%mm1, %%mm0		\n\t"                                                              // 0.0
/*238 */ 			"pmaddwd %%mm2, %%mm3		\n\t"                                                              // 0.0
/*240 */ 			"paddd %%mm3, %%mm5		\n\t"                                                                // 0.0
/*242 */ 			"paddd %%mm0, %%mm4		\n\t"                                                                // 0.0
/*244 */ 			"add $8, %1			\n\t"                                                                       // 0.0
/*246 */ 			"add $4, %%"REG_c"		\n\t"                                                                 // 0.0
/*248 */ 			"cmp %4, %%"REG_c"		\n\t"                                                                 // 0.0
/*250 */ 			" jb 2b				\n\t"                                                                          // 0.0
/*252 */ 			"add %6, %1			\n\t"                                                                       // 0.0
/*254 */ 			"psrad $8, %%mm4		\n\t"                                                                   // 0.0
/*256 */ 			"psrad $8, %%mm5		\n\t"                                                                   // 0.0
/*258 */ 			"packssdw %%mm5, %%mm4		\n\t"                                                             // 0.0
/*260 */ 			"pmaddwd %%mm6, %%mm4		\n\t"                                                              // 0.0
/*262 */ 			"packssdw %%mm4, %%mm4		\n\t"                                                             // 0.0
/*264 */ 			"mov %3, %%"REG_a"		\n\t"                                                                 // 0.0
/*266 */ 			"movd %%mm4, (%%"REG_a", %0)	\n\t"                                                        // 0.0
/*268 */ 			"add $4, %0			\n\t"                                                                       // 0.0
/*270 */ 			" jnc 1b			\n\t"                                                                          // 0.0
/*274 */ 			: "+r" (counter), "+r" (filter)                                                           // 0.0
/*276 */ 			: "m" (filterPos), "m" (dst), "m"(offset),                                                // 0.0
/*278 */ 			  "m" (src), "r" ((long)filterSize*2)                                                     // 0.0
/*280 */ 			: "%"REG_b, "%"REG_a, "%"REG_c                                                            // 0.0
/*282 */ 		);                                                                                         // 0.0
/*284 */ 	}                                                                                           // 0.0
/*286 */ #else                                                                                        // 0.0
/*288 */ #ifdef HAVE_ALTIVEC                                                                          // 0.0
/*290 */ 	hScale_altivec_real(dst, dstW, src, srcW, xInc, filter, filterPos, filterSize);             // 0.0
/*292 */ #else                                                                                        // 0.0
/*294 */ 	int i;                                                                                      // 0.0
/*296 */ 	for(i=0; i<dstW; i++)                                                                       // 0.0
/*298 */ 	{                                                                                           // 0.0
/*300 */ 		int j;                                                                                     // 0.0
/*302 */ 		int srcPos= filterPos[i];                                                                  // 0.0
/*304 */ 		int val=0;                                                                                 // 0.0
/*306 */ //		printf("filterPos: %d\n", filterPos[i]);                                                 // 0.0
/*308 */ 		for(j=0; j<filterSize; j++)                                                                // 0.0
/*310 */ 		{                                                                                          // 0.0
/*312 */ //			printf("filter: %d, src: %d\n", filter[i], src[srcPos + j]);                            // 0.0
/*314 */ 			val += ((int)src[srcPos + j])*filter[filterSize*i + j];                                   // 0.0
/*316 */ 		}                                                                                          // 0.0
/*318 */ //		filter += hFilterSize;                                                                   // 0.0
/*320 */ 		dst[i] = MIN(MAX(0, val>>7), (1<<15)-1); // the cubic equation does overflow ...           // 0.0
/*322 */ //		dst[i] = val>>7;                                                                         // 0.0
/*324 */ 	}                                                                                           // 0.0
/*326 */ #endif                                                                                       // 0.0
/*328 */ #endif                                                                                       // 0.0
/*330 */ }                                                                                            // 0.0
