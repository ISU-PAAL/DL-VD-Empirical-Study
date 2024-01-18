// commit message FFmpeg@28bf81c90d (target=1, prob=0.8688792, correct=True): removed global vars so that multiple swscalers can be used experimental upscaling mode (-sws 3) general convolution filters support (unfinished) bugfix for bicubic upscaling assertion checking if defined MP_DEBUG checking of the input/output size instead of segfault if its very large
/*0   */ static inline void RENAME(hyscale)(uint16_t *dst, int dstWidth, uint8_t *src, int srcW, int xInc)  // (1) 0.07422
/*2   */ {                                                                                                  // (28) 0.001953
/*4   */ #ifdef HAVE_MMX                                                                                    // (19) 0.01367
/*6   */ 	// use the new MMX scaler if th mmx2 cant be used (its faster than the x86asm one)                // (4) 0.05273
/*8   */     if(sws_flags != SWS_FAST_BILINEAR || (!canMMX2BeUsed))                                         // (2) 0.05469
/*10  */ #else                                                                                              // (26) 0.003906
/*12  */     if(sws_flags != SWS_FAST_BILINEAR)                                                             // (11) 0.03906
/*14  */ #endif                                                                                             // (25) 0.003906
/*16  */     {                                                                                              // (22) 0.007812
/*18  */     	RENAME(hScale)(dst, dstWidth, src, srcW, xInc, hLumFilter, hLumFilterPos, hLumFilterSize);    // (0) 0.08398
/*20  */     }                                                                                              // (23) 0.007812
/*22  */     else // Fast Bilinear upscale / crap downscale                                                 // (15) 0.02734
/*24  */     {                                                                                              // (21) 0.007813
/*26  */ #ifdef ARCH_X86                                                                                    // (17) 0.01563
/*28  */ #ifdef HAVE_MMX2                                                                                   // (18) 0.01562
/*30  */ 	int i;                                                                                            // (24) 0.007812
/*32  */ 	if(canMMX2BeUsed)                                                                                 // (16) 0.01953
/*34  */ 	{                                                                                                 // (27) 0.003906
/*36  */ 		asm volatile(                                                                                    // (20) 0.009766
/*38  */ 			"pxor %%mm7, %%mm7		\n\t"                                                                       // (12) 0.03906
/*40  */ 			"pxor %%mm2, %%mm2		\n\t" // 2*xalpha                                                           // (5) 0.04883
/*42  */ 			"movd %5, %%mm6			\n\t" // xInc&0xFFFF                                                          // (3) 0.05469
/*44  */ 			"punpcklwd %%mm6, %%mm6		\n\t"                                                                  // (7) 0.04492
/*46  */ 			"punpcklwd %%mm6, %%mm6		\n\t"                                                                  // (6) 0.04492
/*48  */ 			"movq %%mm6, %%mm2		\n\t"                                                                       // (8) 0.04102
/*50  */ 			"psllq $16, %%mm2		\n\t"                                                                        // (13) 0.03906
/*52  */ 			"paddw %%mm6, %%mm2		\n\t"                                                                      // (9) 0.04102
/*54  */ 			"psllq $16, %%mm2		\n\t"                                                                        // (14) 0.03906
/*56  */ 			"paddw %%mm6, %%mm2		\n\t"                                                                      // (10) 0.04102
/*58  */ 			"psllq $16, %%mm2		\n\t" //0,t,2t,3t		t=xInc&0xFF                                               // 0.0
/*60  */ 			"movq %%mm2, "MANGLE(temp0)"	\n\t"                                                              // 0.0
/*62  */ 			"movd %4, %%mm6			\n\t" //(xInc*4)&0xFFFF                                                       // 0.0
/*64  */ 			"punpcklwd %%mm6, %%mm6		\n\t"                                                                  // 0.0
/*66  */ 			"punpcklwd %%mm6, %%mm6		\n\t"                                                                  // 0.0
/*68  */ 			"xorl %%eax, %%eax		\n\t" // i                                                                  // 0.0
/*70  */ 			"movl %0, %%esi			\n\t" // src                                                                  // 0.0
/*72  */ 			"movl %1, %%edi			\n\t" // buf1                                                                 // 0.0
/*74  */ 			"movl %3, %%edx			\n\t" // (xInc*4)>>16                                                         // 0.0
/*76  */ 			"xorl %%ecx, %%ecx		\n\t"                                                                       // 0.0
/*78  */ 			"xorl %%ebx, %%ebx		\n\t"                                                                       // 0.0
/*80  */ 			"movw %4, %%bx			\n\t" // (xInc*4)&0xFFFF                                                       // 0.0
/*84  */ #define FUNNY_Y_CODE \                                                                             // 0.0
/*86  */ 			PREFETCH" 1024(%%esi)		\n\t"\                                                                   // 0.0
/*88  */ 			PREFETCH" 1056(%%esi)		\n\t"\                                                                   // 0.0
/*90  */ 			PREFETCH" 1088(%%esi)		\n\t"\                                                                   // 0.0
/*92  */ 			"call "MANGLE(funnyYCode)"	\n\t"\                                                               // 0.0
/*94  */ 			"movq "MANGLE(temp0)", %%mm2	\n\t"\                                                             // 0.0
/*96  */ 			"xorl %%ecx, %%ecx		\n\t"                                                                       // 0.0
/*100 */ FUNNY_Y_CODE                                                                                       // 0.0
/*102 */ FUNNY_Y_CODE                                                                                       // 0.0
/*104 */ FUNNY_Y_CODE                                                                                       // 0.0
/*106 */ FUNNY_Y_CODE                                                                                       // 0.0
/*108 */ FUNNY_Y_CODE                                                                                       // 0.0
/*110 */ FUNNY_Y_CODE                                                                                       // 0.0
/*112 */ FUNNY_Y_CODE                                                                                       // 0.0
/*114 */ FUNNY_Y_CODE                                                                                       // 0.0
/*118 */ 			:: "m" (src), "m" (dst), "m" (dstWidth), "m" ((xInc*4)>>16),                                    // 0.0
/*120 */ 			"m" ((xInc*4)&0xFFFF), "m" (xInc&0xFFFF)                                                        // 0.0
/*122 */ 			: "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi"                                                // 0.0
/*124 */ 		);                                                                                               // 0.0
/*126 */ 		for(i=dstWidth-1; (i*xInc)>>16 >=srcW-1; i--) dst[i] = src[srcW-1]*128;                          // 0.0
/*128 */ 	}                                                                                                 // 0.0
/*130 */ 	else                                                                                              // 0.0
/*132 */ 	{                                                                                                 // 0.0
/*134 */ #endif                                                                                             // 0.0
/*136 */ 	//NO MMX just normal asm ...                                                                      // 0.0
/*138 */ 	asm volatile(                                                                                     // 0.0
/*140 */ 		"xorl %%eax, %%eax		\n\t" // i                                                                   // 0.0
/*142 */ 		"xorl %%ebx, %%ebx		\n\t" // xx                                                                  // 0.0
/*144 */ 		"xorl %%ecx, %%ecx		\n\t" // 2*xalpha                                                            // 0.0
/*146 */ 		".balign 16			\n\t"                                                                              // 0.0
/*148 */ 		"1:				\n\t"                                                                                     // 0.0
/*150 */ 		"movzbl  (%0, %%ebx), %%edi	\n\t" //src[xx]                                                      // 0.0
/*152 */ 		"movzbl 1(%0, %%ebx), %%esi	\n\t" //src[xx+1]                                                    // 0.0
/*154 */ 		"subl %%edi, %%esi		\n\t" //src[xx+1] - src[xx]                                                  // 0.0
/*156 */ 		"imull %%ecx, %%esi		\n\t" //(src[xx+1] - src[xx])*2*xalpha                                      // 0.0
/*158 */ 		"shll $16, %%edi		\n\t"                                                                          // 0.0
/*160 */ 		"addl %%edi, %%esi		\n\t" //src[xx+1]*2*xalpha + src[xx]*(1-2*xalpha)                            // 0.0
/*162 */ 		"movl %1, %%edi			\n\t"                                                                          // 0.0
/*164 */ 		"shrl $9, %%esi			\n\t"                                                                          // 0.0
/*166 */ 		"movw %%si, (%%edi, %%eax, 2)	\n\t"                                                              // 0.0
/*168 */ 		"addw %4, %%cx			\n\t" //2*xalpha += xInc&0xFF                                                   // 0.0
/*170 */ 		"adcl %3, %%ebx			\n\t" //xx+= xInc>>8 + carry                                                   // 0.0
/*174 */ 		"movzbl (%0, %%ebx), %%edi	\n\t" //src[xx]                                                       // 0.0
/*176 */ 		"movzbl 1(%0, %%ebx), %%esi	\n\t" //src[xx+1]                                                    // 0.0
/*178 */ 		"subl %%edi, %%esi		\n\t" //src[xx+1] - src[xx]                                                  // 0.0
/*180 */ 		"imull %%ecx, %%esi		\n\t" //(src[xx+1] - src[xx])*2*xalpha                                      // 0.0
/*182 */ 		"shll $16, %%edi		\n\t"                                                                          // 0.0
/*184 */ 		"addl %%edi, %%esi		\n\t" //src[xx+1]*2*xalpha + src[xx]*(1-2*xalpha)                            // 0.0
/*186 */ 		"movl %1, %%edi			\n\t"                                                                          // 0.0
/*188 */ 		"shrl $9, %%esi			\n\t"                                                                          // 0.0
/*190 */ 		"movw %%si, 2(%%edi, %%eax, 2)	\n\t"                                                             // 0.0
/*192 */ 		"addw %4, %%cx			\n\t" //2*xalpha += xInc&0xFF                                                   // 0.0
/*194 */ 		"adcl %3, %%ebx			\n\t" //xx+= xInc>>8 + carry                                                   // 0.0
/*200 */ 		"addl $2, %%eax			\n\t"                                                                          // 0.0
/*202 */ 		"cmpl %2, %%eax			\n\t"                                                                          // 0.0
/*204 */ 		" jb 1b				\n\t"                                                                                 // 0.0
/*210 */ 		:: "r" (src), "m" (dst), "m" (dstWidth), "m" (xInc>>16), "m" (xInc&0xFFFF)                       // 0.0
/*212 */ 		: "%eax", "%ebx", "%ecx", "%edi", "%esi"                                                         // 0.0
/*214 */ 		);                                                                                               // 0.0
/*216 */ #ifdef HAVE_MMX2                                                                                   // 0.0
/*218 */ 	} //if MMX2 cant be used                                                                          // 0.0
/*220 */ #endif                                                                                             // 0.0
/*222 */ #else                                                                                              // 0.0
/*224 */ 	int i;                                                                                            // 0.0
/*226 */ 	unsigned int xpos=0;                                                                              // 0.0
/*228 */ 	for(i=0;i<dstWidth;i++)                                                                           // 0.0
/*230 */ 	{                                                                                                 // 0.0
/*232 */ 		register unsigned int xx=xpos>>16;                                                               // 0.0
/*234 */ 		register unsigned int xalpha=(xpos&0xFFFF)>>9;                                                   // 0.0
/*236 */ 		dst[i]= (src[xx]<<7) + (src[xx+1] - src[xx])*xalpha;                                             // 0.0
/*238 */ 		xpos+=xInc;                                                                                      // 0.0
/*240 */ 	}                                                                                                 // 0.0
/*242 */ #endif                                                                                             // 0.0
/*244 */     }                                                                                              // 0.0
/*246 */ }                                                                                                  // 0.0
