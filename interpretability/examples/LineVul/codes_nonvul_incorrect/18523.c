// commit message FFmpeg@20da77449d (target=0, prob=0.6543966, correct=False): negative stride and h_size-=8 fix
/*0   */ static inline int RENAME(yuv420_rgb24)(SwsContext *c, uint8_t* src[], int srcStride[], int srcSliceY,  // (0) 0.08008
/*2   */              int srcSliceH, uint8_t* dst[], int dstStride[]){                                          // (3) 0.06445
/*4   */     int y, h_size;                                                                                     // (20) 0.01953
/*8   */     if(c->srcFormat == PIX_FMT_YUV422P){                                                               // (11) 0.04102
/*10  */ 	srcStride[1] *= 2;                                                                                    // (19) 0.02148
/*12  */ 	srcStride[2] *= 2;                                                                                    // (18) 0.02148
/*14  */     }                                                                                                  // (21) 0.007813
/*18  */     h_size= (c->dstW+7)&~7;                                                                            // (13) 0.03906
/*20  */     if(h_size*3 > dstStride[0]) h_size-=8;                                                             // (9) 0.04687
/*22  */                                                                                                        // (22) 0.007812
/*24  */     __asm__ __volatile__ ("pxor %mm4, %mm4;" /* zero mm4 */ );                                         // (5) 0.05273
/*28  */     for (y= 0; y<srcSliceH; y++ ) {                                                                    // (12) 0.03906
/*30  */ 	uint8_t *_image = dst[0] + (y+srcSliceY)*dstStride[0];                                                // (4) 0.05664
/*32  */ 	uint8_t *_py = src[0] + y*srcStride[0];                                                               // (10) 0.04297
/*34  */ 	uint8_t *_pu = src[1] + (y>>1)*srcStride[1];                                                          // (7) 0.04883
/*36  */ 	uint8_t *_pv = src[2] + (y>>1)*srcStride[2];                                                          // (6) 0.05078
/*38  */ 	long index= -h_size/2;                                                                                // (16) 0.02148
/*42  */ 	    /* this mmx assembly code deals with SINGLE scan line at a time, it convert 8                     // (8) 0.04688
/*44  */ 	       pixels in each iteration */                                                                    // (14) 0.02344
/*46  */ 	    __asm__ __volatile__ (                                                                            // (15) 0.02344
/*48  */ 	/* load data for start of next scan line */                                                           // (17) 0.02148
/*50  */ 		     "movd (%2, %0), %%mm0;" /* Load 4 Cb 00 00 00 00 u3 u2 u1 u0 */                                 // (1) 0.07422
/*52  */ 		     "movd (%3, %0), %%mm1;" /* Load 4 Cr 00 00 00 00 v3 v2 v1 v0 */                                 // (2) 0.07227
/*54  */ 		     "movq (%5, %0, 2), %%mm6;" /* Load 8  Y Y7 Y6 Y5 Y4 Y3 Y2 Y1 Y0 */                              // 0.0
/*56  */ //		    ".balign 16			\n\t"                                                                            // 0.0
/*58  */ 		    "1:				\n\t"                                                                                     // 0.0
/*60  */ YUV2RGB                                                                                                // 0.0
/*62  */ 	/* mm0=B, %%mm2=G, %%mm1=R */                                                                         // 0.0
/*64  */ #ifdef HAVE_MMX2                                                                                       // 0.0
/*66  */ 			"movq "MANGLE(M24A)", %%mm4	\n\t"                                                                   // 0.0
/*68  */ 			"movq "MANGLE(M24C)", %%mm7	\n\t"                                                                   // 0.0
/*70  */ 			"pshufw $0x50, %%mm0, %%mm5	\n\t" /* B3 B2 B3 B2  B1 B0 B1 B0 */                                    // 0.0
/*72  */ 			"pshufw $0x50, %%mm2, %%mm3	\n\t" /* G3 G2 G3 G2  G1 G0 G1 G0 */                                    // 0.0
/*74  */ 			"pshufw $0x00, %%mm1, %%mm6	\n\t" /* R1 R0 R1 R0  R1 R0 R1 R0 */                                    // 0.0
/*78  */ 			"pand %%mm4, %%mm5		\n\t" /*    B2        B1       B0 */                                            // 0.0
/*80  */ 			"pand %%mm4, %%mm3		\n\t" /*    G2        G1       G0 */                                            // 0.0
/*82  */ 			"pand %%mm7, %%mm6		\n\t" /*       R1        R0       */                                            // 0.0
/*86  */ 			"psllq $8, %%mm3		\n\t" /* G2        G1       G0    */                                              // 0.0
/*88  */ 			"por %%mm5, %%mm6		\n\t"                                                                            // 0.0
/*90  */ 			"por %%mm3, %%mm6		\n\t"                                                                            // 0.0
/*92  */ 			MOVNTQ" %%mm6, (%1)		\n\t"                                                                          // 0.0
/*96  */ 			"psrlq $8, %%mm2		\n\t" /* 00 G7 G6 G5  G4 G3 G2 G1 */                                              // 0.0
/*98  */ 			"pshufw $0xA5, %%mm0, %%mm5	\n\t" /* B5 B4 B5 B4  B3 B2 B3 B2 */                                    // 0.0
/*100 */ 			"pshufw $0x55, %%mm2, %%mm3	\n\t" /* G4 G3 G4 G3  G4 G3 G4 G3 */                                    // 0.0
/*102 */ 			"pshufw $0xA5, %%mm1, %%mm6	\n\t" /* R5 R4 R5 R4  R3 R2 R3 R2 */                                    // 0.0
/*106 */ 			"pand "MANGLE(M24B)", %%mm5	\n\t" /* B5       B4        B3    */                                    // 0.0
/*108 */ 			"pand %%mm7, %%mm3		\n\t" /*       G4        G3       */                                            // 0.0
/*110 */ 			"pand %%mm4, %%mm6		\n\t" /*    R4        R3       R2 */                                            // 0.0
/*114 */ 			"por %%mm5, %%mm3		\n\t" /* B5    G4 B4     G3 B3    */                                             // 0.0
/*116 */ 			"por %%mm3, %%mm6		\n\t"                                                                            // 0.0
/*118 */ 			MOVNTQ" %%mm6, 8(%1)		\n\t"                                                                         // 0.0
/*122 */ 			"pshufw $0xFF, %%mm0, %%mm5	\n\t" /* B7 B6 B7 B6  B7 B6 B6 B7 */                                    // 0.0
/*124 */ 			"pshufw $0xFA, %%mm2, %%mm3	\n\t" /* 00 G7 00 G7  G6 G5 G6 G5 */                                    // 0.0
/*126 */ 			"pshufw $0xFA, %%mm1, %%mm6	\n\t" /* R7 R6 R7 R6  R5 R4 R5 R4 */                                    // 0.0
/*128 */ 			"movd 4 (%2, %0), %%mm0;" /* Load 4 Cb 00 00 00 00 u3 u2 u1 u0 */                                   // 0.0
/*132 */ 			"pand %%mm7, %%mm5		\n\t" /*       B7        B6       */                                            // 0.0
/*134 */ 			"pand %%mm4, %%mm3		\n\t" /*    G7        G6       G5 */                                            // 0.0
/*136 */ 			"pand "MANGLE(M24B)", %%mm6	\n\t" /* R7       R6        R5    */                                    // 0.0
/*138 */ 			"movd 4 (%3, %0), %%mm1;" /* Load 4 Cr 00 00 00 00 v3 v2 v1 v0 */                                   // 0.0
/*140 */ \                                                                                                      // 0.0
/*142 */ 			"por %%mm5, %%mm3		\n\t"                                                                            // 0.0
/*144 */ 			"por %%mm3, %%mm6		\n\t"                                                                            // 0.0
/*146 */ 			MOVNTQ" %%mm6, 16(%1)		\n\t"                                                                        // 0.0
/*148 */ 			"movq 8 (%5, %0, 2), %%mm6;" /* Load 8 Y Y7 Y6 Y5 Y4 Y3 Y2 Y1 Y0 */                                 // 0.0
/*150 */ 			"pxor %%mm4, %%mm4		\n\t"                                                                           // 0.0
/*154 */ #else                                                                                                  // 0.0
/*158 */ 			"pxor %%mm4, %%mm4		\n\t"                                                                           // 0.0
/*160 */ 			"movq %%mm0, %%mm5		\n\t" /* B */                                                                   // 0.0
/*162 */ 			"movq %%mm1, %%mm6		\n\t" /* R */                                                                   // 0.0
/*164 */ 			"punpcklbw %%mm2, %%mm0		\n\t" /* GBGBGBGB 0 */                                                     // 0.0
/*166 */ 			"punpcklbw %%mm4, %%mm1		\n\t" /* 0R0R0R0R 0 */                                                     // 0.0
/*168 */ 			"punpckhbw %%mm2, %%mm5		\n\t" /* GBGBGBGB 2 */                                                     // 0.0
/*170 */ 			"punpckhbw %%mm4, %%mm6		\n\t" /* 0R0R0R0R 2 */                                                     // 0.0
/*172 */ 			"movq %%mm0, %%mm7		\n\t" /* GBGBGBGB 0 */                                                          // 0.0
/*174 */ 			"movq %%mm5, %%mm3		\n\t" /* GBGBGBGB 2 */                                                          // 0.0
/*176 */ 			"punpcklwd %%mm1, %%mm7		\n\t" /* 0RGB0RGB 0 */                                                     // 0.0
/*178 */ 			"punpckhwd %%mm1, %%mm0		\n\t" /* 0RGB0RGB 1 */                                                     // 0.0
/*180 */ 			"punpcklwd %%mm6, %%mm5		\n\t" /* 0RGB0RGB 2 */                                                     // 0.0
/*182 */ 			"punpckhwd %%mm6, %%mm3		\n\t" /* 0RGB0RGB 3 */                                                     // 0.0
/*186 */ 			"movq %%mm7, %%mm2		\n\t" /* 0RGB0RGB 0 */                                                          // 0.0
/*188 */ 			"movq %%mm0, %%mm6		\n\t" /* 0RGB0RGB 1 */                                                          // 0.0
/*190 */ 			"movq %%mm5, %%mm1		\n\t" /* 0RGB0RGB 2 */                                                          // 0.0
/*192 */ 			"movq %%mm3, %%mm4		\n\t" /* 0RGB0RGB 3 */                                                          // 0.0
/*196 */ 			"psllq $40, %%mm7		\n\t" /* RGB00000 0 */                                                           // 0.0
/*198 */ 			"psllq $40, %%mm0		\n\t" /* RGB00000 1 */                                                           // 0.0
/*200 */ 			"psllq $40, %%mm5		\n\t" /* RGB00000 2 */                                                           // 0.0
/*202 */ 			"psllq $40, %%mm3		\n\t" /* RGB00000 3 */                                                           // 0.0
/*206 */ 			"punpckhdq %%mm2, %%mm7		\n\t" /* 0RGBRGB0 0 */                                                     // 0.0
/*208 */ 			"punpckhdq %%mm6, %%mm0		\n\t" /* 0RGBRGB0 1 */                                                     // 0.0
/*210 */ 			"punpckhdq %%mm1, %%mm5		\n\t" /* 0RGBRGB0 2 */                                                     // 0.0
/*212 */ 			"punpckhdq %%mm4, %%mm3		\n\t" /* 0RGBRGB0 3 */                                                     // 0.0
/*216 */ 			"psrlq $8, %%mm7		\n\t" /* 00RGBRGB 0 */                                                            // 0.0
/*218 */ 			"movq %%mm0, %%mm6		\n\t" /* 0RGBRGB0 1 */                                                          // 0.0
/*220 */ 			"psllq $40, %%mm0		\n\t" /* GB000000 1 */                                                           // 0.0
/*222 */ 			"por %%mm0, %%mm7		\n\t" /* GBRGBRGB 0 */                                                           // 0.0
/*224 */ 			MOVNTQ" %%mm7, (%1)		\n\t"                                                                          // 0.0
/*228 */ 			"movd 4 (%2, %0), %%mm0;" /* Load 4 Cb 00 00 00 00 u3 u2 u1 u0 */                                   // 0.0
/*232 */ 			"psrlq $24, %%mm6		\n\t" /* 0000RGBR 1 */                                                           // 0.0
/*234 */ 			"movq %%mm5, %%mm1		\n\t" /* 0RGBRGB0 2 */                                                          // 0.0
/*236 */ 			"psllq $24, %%mm5		\n\t" /* BRGB0000 2 */                                                           // 0.0
/*238 */ 			"por %%mm5, %%mm6		\n\t" /* BRGBRGBR 1 */                                                           // 0.0
/*240 */ 			MOVNTQ" %%mm6, 8(%1)		\n\t"                                                                         // 0.0
/*244 */ 			"movq 8 (%5, %0, 2), %%mm6;" /* Load 8 Y Y7 Y6 Y5 Y4 Y3 Y2 Y1 Y0 */                                 // 0.0
/*248 */ 			"psrlq $40, %%mm1		\n\t" /* 000000RG 2 */                                                           // 0.0
/*250 */ 			"psllq $8, %%mm3		\n\t" /* RGBRGB00 3 */                                                            // 0.0
/*252 */ 			"por %%mm3, %%mm1		\n\t" /* RGBRGBRG 2 */                                                           // 0.0
/*254 */ 			MOVNTQ" %%mm1, 16(%1)		\n\t"                                                                        // 0.0
/*258 */ 			"movd 4 (%3, %0), %%mm1;" /* Load 4 Cr 00 00 00 00 v3 v2 v1 v0 */                                   // 0.0
/*260 */ 			"pxor %%mm4, %%mm4		\n\t"                                                                           // 0.0
/*262 */ #endif                                                                                                 // 0.0
/*264 */ 		                                                                                                     // 0.0
/*266 */ 		     "add $24, %1			\n\t"                                                                            // 0.0
/*268 */ 		     "add $4, %0			\n\t"                                                                             // 0.0
/*270 */ 		     " js 1b				\n\t"                                                                                // 0.0
/*272 */ 		                                                                                                     // 0.0
/*274 */ 		     : "+r" (index), "+r" (_image)                                                                   // 0.0
/*276 */ 		     : "r" (_pu - index), "r" (_pv - index), "r"(&c->redDither), "r" (_py - 2*index)                 // 0.0
/*278 */ 		     );                                                                                              // 0.0
/*280 */     }                                                                                                  // 0.0
/*284 */     __asm__ __volatile__ (EMMS);                                                                       // 0.0
/*286 */     return srcSliceH;                                                                                  // 0.0
/*288 */ }                                                                                                      // 0.0
