// commit message FFmpeg@6e42e6c4b4 (target=1, prob=0.94746536, correct=True): cosmetics attack, part I: Remove all tabs and prettyprint/reindent the code.
/*0   */ static inline int yv12toyuy2_unscaled_altivec(SwsContext *c, uint8_t* src[], int srcStride[], int srcSliceY,  // (1) 0.08789
/*2   */      int srcSliceH, uint8_t* dstParam[], int dstStride_a[]) {                                                 // (4) 0.05469
/*4   */   uint8_t *dst=dstParam[0] + dstStride_a[0]*srcSliceY;                                                        // (3) 0.05859
/*6   */   // yv12toyuy2( src[0],src[1],src[2],dst,c->srcW,srcSliceH,srcStride[0],srcStride[1],dstStride[0] );         // (0) 0.1074
/*8   */   uint8_t *ysrc = src[0];                                                                                     // (9) 0.02539
/*10  */   uint8_t *usrc = src[1];                                                                                     // (10) 0.02539
/*12  */   uint8_t *vsrc = src[2];                                                                                     // (11) 0.02539
/*14  */   const int width = c->srcW;                                                                                  // (17) 0.01953
/*16  */   const int height = srcSliceH;                                                                               // (18) 0.01953
/*18  */   const int lumStride = srcStride[0];                                                                         // (12) 0.02539
/*20  */   const int chromStride = srcStride[1];                                                                       // (13) 0.02539
/*22  */   const int dstStride = dstStride_a[0];                                                                       // (7) 0.0293
/*24  */   const vector unsigned char yperm = vec_lvsl(0, ysrc);                                                       // (6) 0.03516
/*26  */   const int vertLumPerChroma = 2;                                                                             // (14) 0.02344
/*28  */   register unsigned int y;                                                                                    // (25) 0.01172
/*32  */   if(width&15){                                                                                               // (24) 0.01367
/*34  */     yv12toyuy2( ysrc, usrc, vsrc, dst,c->srcW,srcSliceH, lumStride, chromStride, dstStride);                  // (2) 0.08594
/*36  */     return srcSliceH;                                                                                         // (20) 0.01758
/*38  */   }                                                                                                           // (28) 0.003906
/*42  */   /* this code assume:                                                                                        // (26) 0.01172
/*46  */   1) dst is 16 bytes-aligned                                                                                  // (21) 0.01758
/*48  */   2) dstStride is a multiple of 16                                                                            // (15) 0.02148
/*50  */   3) width is a multiple of 16                                                                                // (22) 0.01758
/*52  */   4) lum&chrom stride are multiple of 8                                                                       // (16) 0.02148
/*54  */   */                                                                                                          // (29) 0.003906
/*58  */   for(y=0; y<height; y++)                                                                                     // (8) 0.02539
/*60  */     {                                                                                                         // (27) 0.007813
/*62  */       int i;                                                                                                  // (23) 0.01562
/*64  */       for (i = 0; i < width - 31; i+= 32) {                                                                   // (5) 0.04297
/*66  */ 	const unsigned int j = i >> 1;                                                                               // (19) 0.01953
/*68  */ 	vector unsigned char v_yA = vec_ld(i, ysrc);                                                                 // 0.0
/*70  */ 	vector unsigned char v_yB = vec_ld(i + 16, ysrc);                                                            // 0.0
/*72  */ 	vector unsigned char v_yC = vec_ld(i + 32, ysrc);                                                            // 0.0
/*74  */ 	vector unsigned char v_y1 = vec_perm(v_yA, v_yB, yperm);                                                     // 0.0
/*76  */ 	vector unsigned char v_y2 = vec_perm(v_yB, v_yC, yperm);                                                     // 0.0
/*78  */ 	vector unsigned char v_uA = vec_ld(j, usrc);                                                                 // 0.0
/*80  */ 	vector unsigned char v_uB = vec_ld(j + 16, usrc);                                                            // 0.0
/*82  */ 	vector unsigned char v_u = vec_perm(v_uA, v_uB, vec_lvsl(j, usrc));                                          // 0.0
/*84  */ 	vector unsigned char v_vA = vec_ld(j, vsrc);                                                                 // 0.0
/*86  */ 	vector unsigned char v_vB = vec_ld(j + 16, vsrc);                                                            // 0.0
/*88  */ 	vector unsigned char v_v = vec_perm(v_vA, v_vB, vec_lvsl(j, vsrc));                                          // 0.0
/*90  */ 	vector unsigned char v_uv_a = vec_mergeh(v_u, v_v);                                                          // 0.0
/*92  */ 	vector unsigned char v_uv_b = vec_mergel(v_u, v_v);                                                          // 0.0
/*94  */ 	vector unsigned char v_yuy2_0 = vec_mergeh(v_y1, v_uv_a);                                                    // 0.0
/*96  */ 	vector unsigned char v_yuy2_1 = vec_mergel(v_y1, v_uv_a);                                                    // 0.0
/*98  */ 	vector unsigned char v_yuy2_2 = vec_mergeh(v_y2, v_uv_b);                                                    // 0.0
/*100 */ 	vector unsigned char v_yuy2_3 = vec_mergel(v_y2, v_uv_b);                                                    // 0.0
/*102 */ 	vec_st(v_yuy2_0, (i << 1), dst);                                                                             // 0.0
/*104 */ 	vec_st(v_yuy2_1, (i << 1) + 16, dst);                                                                        // 0.0
/*106 */ 	vec_st(v_yuy2_2, (i << 1) + 32, dst);                                                                        // 0.0
/*108 */ 	vec_st(v_yuy2_3, (i << 1) + 48, dst);                                                                        // 0.0
/*110 */       }                                                                                                       // 0.0
/*112 */       if (i < width) {                                                                                        // 0.0
/*114 */ 	const unsigned int j = i >> 1;                                                                               // 0.0
/*116 */ 	vector unsigned char v_y1 = vec_ld(i, ysrc);                                                                 // 0.0
/*118 */ 	vector unsigned char v_u = vec_ld(j, usrc);                                                                  // 0.0
/*120 */ 	vector unsigned char v_v = vec_ld(j, vsrc);                                                                  // 0.0
/*122 */ 	vector unsigned char v_uv_a = vec_mergeh(v_u, v_v);                                                          // 0.0
/*124 */ 	vector unsigned char v_yuy2_0 = vec_mergeh(v_y1, v_uv_a);                                                    // 0.0
/*126 */ 	vector unsigned char v_yuy2_1 = vec_mergel(v_y1, v_uv_a);                                                    // 0.0
/*128 */ 	vec_st(v_yuy2_0, (i << 1), dst);                                                                             // 0.0
/*130 */ 	vec_st(v_yuy2_1, (i << 1) + 16, dst);                                                                        // 0.0
/*132 */       }                                                                                                       // 0.0
/*134 */       if((y&(vertLumPerChroma-1))==(vertLumPerChroma-1) )                                                     // 0.0
/*136 */ 	{                                                                                                            // 0.0
/*138 */ 	  usrc += chromStride;                                                                                       // 0.0
/*140 */ 	  vsrc += chromStride;                                                                                       // 0.0
/*142 */ 	}                                                                                                            // 0.0
/*144 */       ysrc += lumStride;                                                                                      // 0.0
/*146 */       dst += dstStride;                                                                                       // 0.0
/*148 */     }                                                                                                         // 0.0
/*152 */   return srcSliceH;                                                                                           // 0.0
/*154 */ }                                                                                                             // 0.0
