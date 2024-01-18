// commit message FFmpeg@428098165d (target=1, prob=0.4525377, correct=False): cosmetics attack, part III: Remove all tabs and prettyprint/reindent the code.
/*0   */ static inline int RENAME(yuv420_rgb16)(SwsContext *c, uint8_t* src[], int srcStride[], int srcSliceY,                                // (1) 0.08001
/*2   */              int srcSliceH, uint8_t* dst[], int dstStride[]){                                                                        // (2) 0.06439
/*4   */     int y, h_size;                                                                                                                   // (19) 0.01951
/*8   */     if(c->srcFormat == PIX_FMT_YUV422P){                                                                                             // (10) 0.04098
/*10  */ 	srcStride[1] *= 2;                                                                                                                  // (18) 0.02146
/*12  */ 	srcStride[2] *= 2;                                                                                                                  // (17) 0.02146
/*14  */     }                                                                                                                                // (20) 0.007806
/*18  */     h_size= (c->dstW+7)&~7;                                                                                                          // (12) 0.03902
/*20  */     if(h_size*2 > FFABS(dstStride[0])) h_size-=8;                                                                                    // (3) 0.05853
/*24  */     __asm__ __volatile__ ("pxor %mm4, %mm4;" /* zero mm4 */ );                                                                       // (5) 0.05269
/*26  */ //printf("%X %X %X %X %X %X %X %X %X %X\n", (int)&c->redDither, (int)&b5Dither, (int)src[0], (int)src[1], (int)src[2], (int)dst[0],  // (0) 0.1445
/*28  */ //srcStride[0],srcStride[1],srcStride[2],dstStride[0]);                                                                              // (6) 0.05109
/*30  */     for (y= 0; y<srcSliceH; y++ ) {                                                                                                  // (11) 0.03902
/*32  */ 	uint8_t *_image = dst[0] + (y+srcSliceY)*dstStride[0];                                                                              // (4) 0.05658
/*34  */ 	uint8_t *_py = src[0] + y*srcStride[0];                                                                                             // (9) 0.04292
/*36  */ 	uint8_t *_pu = src[1] + (y>>1)*srcStride[1];                                                                                        // (8) 0.04878
/*38  */ 	uint8_t *_pv = src[2] + (y>>1)*srcStride[2];                                                                                        // (7) 0.05073
/*40  */ 	long index= -h_size/2;                                                                                                              // (16) 0.02147
/*44  */ 	b5Dither= dither8[y&1];                                                                                                             // (13) 0.02732
/*46  */ 	g6Dither= dither4[y&1];                                                                                                             // (15) 0.02731
/*48  */ 	g5Dither= dither8[y&1];                                                                                                             // (14) 0.02732
/*50  */ 	r5Dither= dither8[(y+1)&1];                                                                                                         // 0.0
/*52  */ 	    /* this mmx assembly code deals with SINGLE scan line at a time, it convert 8                                                   // 0.0
/*54  */ 	       pixels in each iteration */                                                                                                  // 0.0
/*56  */ 	    __asm__ __volatile__ (                                                                                                          // 0.0
/*58  */ 	/* load data for start of next scan line */                                                                                         // 0.0
/*60  */ 		     "movd (%2, %0), %%mm0;" /* Load 4 Cb 00 00 00 00 u3 u2 u1 u0 */                                                               // 0.0
/*62  */ 		     "movd (%3, %0), %%mm1;" /* Load 4 Cr 00 00 00 00 v3 v2 v1 v0 */                                                               // 0.0
/*64  */ 		     "movq (%5, %0, 2), %%mm6;" /* Load 8  Y Y7 Y6 Y5 Y4 Y3 Y2 Y1 Y0 */                                                            // 0.0
/*66  */ //		    ".balign 16			\n\t"                                                                                                          // 0.0
/*68  */ 		    "1:				\n\t"                                                                                                                   // 0.0
/*70  */ /* no speed diference on my p3@500 with prefetch,                                                                                    // 0.0
/*72  */  * if it is faster for anyone with -benchmark then tell me                                                                           // 0.0
/*74  */ 			PREFETCH" 64(%0) \n\t"                                                                                                            // 0.0
/*76  */ 			PREFETCH" 64(%1) \n\t"                                                                                                            // 0.0
/*78  */ 			PREFETCH" 64(%2) \n\t"                                                                                                            // 0.0
/*80  */ */                                                                                                                                   // 0.0
/*82  */ YUV2RGB                                                                                                                              // 0.0
/*86  */ #ifdef DITHER1XBPP                                                                                                                   // 0.0
/*88  */ 			"paddusb "MANGLE(b5Dither)", %%mm0;"                                                                                              // 0.0
/*90  */ 			"paddusb "MANGLE(g6Dither)", %%mm2;"                                                                                              // 0.0
/*92  */ 			"paddusb "MANGLE(r5Dither)", %%mm1;"                                                                                              // 0.0
/*94  */ #endif                                                                                                                               // 0.0
/*96  */ 		     /* mask unneeded bits off */                                                                                                  // 0.0
/*98  */ 		     "pand "MANGLE(mmx_redmask)", %%mm0;" /* b7b6b5b4 b3_0_0_0 b7b6b5b4 b3_0_0_0 */                                                // 0.0
/*100 */ 		     "pand "MANGLE(mmx_grnmask)", %%mm2;" /* g7g6g5g4 g3g2_0_0 g7g6g5g4 g3g2_0_0 */                                                // 0.0
/*102 */ 		     "pand "MANGLE(mmx_redmask)", %%mm1;" /* r7r6r5r4 r3_0_0_0 r7r6r5r4 r3_0_0_0 */                                                // 0.0
/*106 */ 		     "psrlw $3,%%mm0;" /* 0_0_0_b7 b6b5b4b3 0_0_0_b7 b6b5b4b3 */                                                                   // 0.0
/*108 */ 		     "pxor %%mm4, %%mm4;" /* zero mm4 */                                                                                           // 0.0
/*112 */ 		     "movq %%mm0, %%mm5;" /* Copy B7-B0 */                                                                                         // 0.0
/*114 */ 		     "movq %%mm2, %%mm7;" /* Copy G7-G0 */                                                                                         // 0.0
/*118 */ 		     /* convert rgb24 plane to rgb16 pack for pixel 0-3 */                                                                         // 0.0
/*120 */ 		     "punpcklbw %%mm4, %%mm2;" /* 0_0_0_0 0_0_0_0 g7g6g5g4 g3g2_0_0 */                                                             // 0.0
/*122 */ 		     "punpcklbw %%mm1, %%mm0;" /* r7r6r5r4 r3_0_0_0 0_0_0_b7 b6b5b4b3 */                                                           // 0.0
/*126 */ 		     "psllw $3, %%mm2;" /* 0_0_0_0 0_g7g6g5 g4g3g2_0 0_0_0_0 */                                                                    // 0.0
/*128 */ 		     "por %%mm2, %%mm0;" /* r7r6r5r4 r3g7g6g5 g4g3g2b7 b6b5b4b3 */                                                                 // 0.0
/*132 */ 		     "movq 8 (%5, %0, 2), %%mm6;" /* Load 8 Y Y7 Y6 Y5 Y4 Y3 Y2 Y1 Y0 */                                                           // 0.0
/*134 */ 		     MOVNTQ " %%mm0, (%1);" /* store pixel 0-3 */                                                                                  // 0.0
/*138 */ 		     /* convert rgb24 plane to rgb16 pack for pixel 0-3 */                                                                         // 0.0
/*140 */ 		     "punpckhbw %%mm4, %%mm7;" /* 0_0_0_0 0_0_0_0 g7g6g5g4 g3g2_0_0 */                                                             // 0.0
/*142 */ 		     "punpckhbw %%mm1, %%mm5;" /* r7r6r5r4 r3_0_0_0 0_0_0_b7 b6b5b4b3 */                                                           // 0.0
/*146 */ 		     "psllw $3, %%mm7;" /* 0_0_0_0 0_g7g6g5 g4g3g2_0 0_0_0_0 */                                                                    // 0.0
/*148 */ 		     "movd 4 (%2, %0), %%mm0;" /* Load 4 Cb 00 00 00 00 u3 u2 u1 u0 */                                                             // 0.0
/*152 */ 		     "por %%mm7, %%mm5;" /* r7r6r5r4 r3g7g6g5 g4g3g2b7 b6b5b4b3 */                                                                 // 0.0
/*154 */ 		     "movd 4 (%3, %0), %%mm1;" /* Load 4 Cr 00 00 00 00 v3 v2 v1 v0 */                                                             // 0.0
/*158 */ 		     MOVNTQ " %%mm5, 8 (%1);" /* store pixel 4-7 */                                                                                // 0.0
/*162 */ 		     "add $16, %1			\n\t"                                                                                                          // 0.0
/*164 */ 		     "add $4, %0			\n\t"                                                                                                           // 0.0
/*166 */ 		     " js 1b				\n\t"                                                                                                              // 0.0
/*170 */ 		     : "+r" (index), "+r" (_image)                                                                                                 // 0.0
/*172 */ 		     : "r" (_pu - index), "r" (_pv - index), "r"(&c->redDither), "r" (_py - 2*index)                                               // 0.0
/*174 */ 		     );                                                                                                                            // 0.0
/*176 */     }                                                                                                                                // 0.0
/*180 */     __asm__ __volatile__ (EMMS);                                                                                                     // 0.0
/*184 */     return srcSliceH;                                                                                                                // 0.0
/*186 */ }                                                                                                                                    // 0.0
