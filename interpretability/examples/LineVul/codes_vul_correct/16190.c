// commit message FFmpeg@7f526efd17 (target=1, prob=0.90477055, correct=True): Change unsigned->signed and int->long, this fits the asm code better on 64 bit systems. Also fixes several crashes because (long)-i is incorrect if i is unsigned.
/*0   */ static inline void RENAME(yuy2toyv12)(const uint8_t *src, uint8_t *ydst, uint8_t *udst, uint8_t *vdst,  // (0) 0.0918
/*2   */ 	unsigned int width, unsigned int height,                                                               // (16) 0.01758
/*4   */ 	int lumStride, int chromStride, int srcStride)                                                         // (11) 0.03125
/*6   */ {                                                                                                       // (21) 0.001953
/*8   */ 	unsigned y;                                                                                            // (19) 0.007813
/*10  */ 	const unsigned chromWidth= width>>1;                                                                   // (15) 0.01953
/*12  */ 	for(y=0; y<height; y+=2)                                                                               // (12) 0.0293
/*14  */ 	{                                                                                                      // (20) 0.003906
/*16  */ #ifdef HAVE_MMX                                                                                         // (17) 0.01367
/*18  */ 		asm volatile(                                                                                         // (18) 0.009766
/*20  */ 			"xor %%"REG_a", %%"REG_a"	\n\t"                                                                      // (9) 0.04687
/*22  */ 			"pcmpeqw %%mm7, %%mm7		\n\t"                                                                         // (10) 0.04492
/*24  */ 			"psrlw $8, %%mm7		\n\t" // FF,00,FF,00...                                                            // (7) 0.05664
/*26  */ 			".balign 16			\n\t"                                                                                  // (13) 0.0293
/*28  */ 			"1:				\n\t"                                                                                         // (14) 0.0293
/*30  */ 			PREFETCH" 64(%0, %%"REG_a", 4)	\n\t"                                                                 // (8) 0.05273
/*32  */ 			"movq (%0, %%"REG_a", 4), %%mm0	\n\t" // YUYV YUYV(0)                                                // (2) 0.07617
/*34  */ 			"movq 8(%0, %%"REG_a", 4), %%mm1\n\t" // YUYV YUYV(4)                                                // (1) 0.07812
/*36  */ 			"movq %%mm0, %%mm2		\n\t" // YUYV YUYV(0)                                                            // (4) 0.06445
/*38  */ 			"movq %%mm1, %%mm3		\n\t" // YUYV YUYV(4)                                                            // (3) 0.06445
/*40  */ 			"psrlw $8, %%mm0		\n\t" // U0V0 U0V0(0)                                                              // (6) 0.0625
/*42  */ 			"psrlw $8, %%mm1		\n\t" // U0V0 U0V0(4)                                                              // (5) 0.0625
/*44  */ 			"pand %%mm7, %%mm2		\n\t" // Y0Y0 Y0Y0(0)                                                            // 0.0
/*46  */ 			"pand %%mm7, %%mm3		\n\t" // Y0Y0 Y0Y0(4)                                                            // 0.0
/*48  */ 			"packuswb %%mm1, %%mm0		\n\t" // UVUV UVUV(0)                                                        // 0.0
/*50  */ 			"packuswb %%mm3, %%mm2		\n\t" // YYYY YYYY(0)                                                        // 0.0
/*54  */ 			MOVNTQ" %%mm2, (%1, %%"REG_a", 2)\n\t"                                                               // 0.0
/*58  */ 			"movq 16(%0, %%"REG_a", 4), %%mm1\n\t" // YUYV YUYV(8)                                               // 0.0
/*60  */ 			"movq 24(%0, %%"REG_a", 4), %%mm2\n\t" // YUYV YUYV(12)                                              // 0.0
/*62  */ 			"movq %%mm1, %%mm3		\n\t" // YUYV YUYV(8)                                                            // 0.0
/*64  */ 			"movq %%mm2, %%mm4		\n\t" // YUYV YUYV(12)                                                           // 0.0
/*66  */ 			"psrlw $8, %%mm1		\n\t" // U0V0 U0V0(8)                                                              // 0.0
/*68  */ 			"psrlw $8, %%mm2		\n\t" // U0V0 U0V0(12)                                                             // 0.0
/*70  */ 			"pand %%mm7, %%mm3		\n\t" // Y0Y0 Y0Y0(8)                                                            // 0.0
/*72  */ 			"pand %%mm7, %%mm4		\n\t" // Y0Y0 Y0Y0(12)                                                           // 0.0
/*74  */ 			"packuswb %%mm2, %%mm1		\n\t" // UVUV UVUV(8)                                                        // 0.0
/*76  */ 			"packuswb %%mm4, %%mm3		\n\t" // YYYY YYYY(8)                                                        // 0.0
/*80  */ 			MOVNTQ" %%mm3, 8(%1, %%"REG_a", 2)\n\t"                                                              // 0.0
/*84  */ 			"movq %%mm0, %%mm2		\n\t" // UVUV UVUV(0)                                                            // 0.0
/*86  */ 			"movq %%mm1, %%mm3		\n\t" // UVUV UVUV(8)                                                            // 0.0
/*88  */ 			"psrlw $8, %%mm0		\n\t" // V0V0 V0V0(0)                                                              // 0.0
/*90  */ 			"psrlw $8, %%mm1		\n\t" // V0V0 V0V0(8)                                                              // 0.0
/*92  */ 			"pand %%mm7, %%mm2		\n\t" // U0U0 U0U0(0)                                                            // 0.0
/*94  */ 			"pand %%mm7, %%mm3		\n\t" // U0U0 U0U0(8)                                                            // 0.0
/*96  */ 			"packuswb %%mm1, %%mm0		\n\t" // VVVV VVVV(0)                                                        // 0.0
/*98  */ 			"packuswb %%mm3, %%mm2		\n\t" // UUUU UUUU(0)                                                        // 0.0
/*102 */ 			MOVNTQ" %%mm0, (%3, %%"REG_a")	\n\t"                                                                 // 0.0
/*104 */ 			MOVNTQ" %%mm2, (%2, %%"REG_a")	\n\t"                                                                 // 0.0
/*108 */ 			"add $8, %%"REG_a"		\n\t"                                                                            // 0.0
/*110 */ 			"cmp %4, %%"REG_a"		\n\t"                                                                            // 0.0
/*112 */ 			" jb 1b				\n\t"                                                                                     // 0.0
/*114 */ 			::"r"(src), "r"(ydst), "r"(udst), "r"(vdst), "g" ((long)chromWidth)                                  // 0.0
/*116 */ 			: "memory", "%"REG_a                                                                                 // 0.0
/*118 */ 		);                                                                                                    // 0.0
/*122 */ 		ydst += lumStride;                                                                                    // 0.0
/*124 */ 		src  += srcStride;                                                                                    // 0.0
/*128 */ 		asm volatile(                                                                                         // 0.0
/*130 */ 			"xor %%"REG_a", %%"REG_a"	\n\t"                                                                      // 0.0
/*132 */ 			".balign 16			\n\t"                                                                                  // 0.0
/*134 */ 			"1:				\n\t"                                                                                         // 0.0
/*136 */ 			PREFETCH" 64(%0, %%"REG_a", 4)	\n\t"                                                                 // 0.0
/*138 */ 			"movq (%0, %%"REG_a", 4), %%mm0	\n\t" // YUYV YUYV(0)                                                // 0.0
/*140 */ 			"movq 8(%0, %%"REG_a", 4), %%mm1\n\t" // YUYV YUYV(4)                                                // 0.0
/*142 */ 			"movq 16(%0, %%"REG_a", 4), %%mm2\n\t" // YUYV YUYV(8)                                               // 0.0
/*144 */ 			"movq 24(%0, %%"REG_a", 4), %%mm3\n\t" // YUYV YUYV(12)                                              // 0.0
/*146 */ 			"pand %%mm7, %%mm0		\n\t" // Y0Y0 Y0Y0(0)                                                            // 0.0
/*148 */ 			"pand %%mm7, %%mm1		\n\t" // Y0Y0 Y0Y0(4)                                                            // 0.0
/*150 */ 			"pand %%mm7, %%mm2		\n\t" // Y0Y0 Y0Y0(8)                                                            // 0.0
/*152 */ 			"pand %%mm7, %%mm3		\n\t" // Y0Y0 Y0Y0(12)                                                           // 0.0
/*154 */ 			"packuswb %%mm1, %%mm0		\n\t" // YYYY YYYY(0)                                                        // 0.0
/*156 */ 			"packuswb %%mm3, %%mm2		\n\t" // YYYY YYYY(8)                                                        // 0.0
/*160 */ 			MOVNTQ" %%mm0, (%1, %%"REG_a", 2)\n\t"                                                               // 0.0
/*162 */ 			MOVNTQ" %%mm2, 8(%1, %%"REG_a", 2)\n\t"                                                              // 0.0
/*166 */ 			"add $8, %%"REG_a"		\n\t"                                                                            // 0.0
/*168 */ 			"cmp %4, %%"REG_a"		\n\t"                                                                            // 0.0
/*170 */ 			" jb 1b				\n\t"                                                                                     // 0.0
/*174 */ 			::"r"(src), "r"(ydst), "r"(udst), "r"(vdst), "g" ((long)chromWidth)                                  // 0.0
/*176 */ 			: "memory", "%"REG_a                                                                                 // 0.0
/*178 */ 		);                                                                                                    // 0.0
/*180 */ #else                                                                                                   // 0.0
/*182 */ 		unsigned i;                                                                                           // 0.0
/*184 */ 		for(i=0; i<chromWidth; i++)                                                                           // 0.0
/*186 */ 		{                                                                                                     // 0.0
/*188 */ 			ydst[2*i+0] 	= src[4*i+0];                                                                           // 0.0
/*190 */ 			udst[i] 	= src[4*i+1];                                                                               // 0.0
/*192 */ 			ydst[2*i+1] 	= src[4*i+2];                                                                           // 0.0
/*194 */ 			vdst[i] 	= src[4*i+3];                                                                               // 0.0
/*196 */ 		}                                                                                                     // 0.0
/*198 */ 		ydst += lumStride;                                                                                    // 0.0
/*200 */ 		src  += srcStride;                                                                                    // 0.0
/*204 */ 		for(i=0; i<chromWidth; i++)                                                                           // 0.0
/*206 */ 		{                                                                                                     // 0.0
/*208 */ 			ydst[2*i+0] 	= src[4*i+0];                                                                           // 0.0
/*210 */ 			ydst[2*i+1] 	= src[4*i+2];                                                                           // 0.0
/*212 */ 		}                                                                                                     // 0.0
/*214 */ #endif                                                                                                  // 0.0
/*216 */ 		udst += chromStride;                                                                                  // 0.0
/*218 */ 		vdst += chromStride;                                                                                  // 0.0
/*220 */ 		ydst += lumStride;                                                                                    // 0.0
/*222 */ 		src  += srcStride;                                                                                    // 0.0
/*224 */ 	}                                                                                                      // 0.0
/*226 */ #ifdef HAVE_MMX                                                                                         // 0.0
/*228 */ asm volatile(   EMMS" \n\t"                                                                             // 0.0
/*230 */         	SFENCE" \n\t"                                                                                  // 0.0
/*232 */         	:::"memory");                                                                                  // 0.0
/*234 */ #endif                                                                                                  // 0.0
/*236 */ }                                                                                                       // 0.0
