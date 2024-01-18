// commit message FFmpeg@6e42e6c4b4 (target=1, prob=0.8885267, correct=True): cosmetics attack, part I: Remove all tabs and prettyprint/reindent the code.
/*0   */ static inline void hScale_altivec_real(int16_t *dst, int dstW, uint8_t *src, int srcW, int xInc, int16_t *filter, int16_t *filterPos, int filterSize) {  // (0) 0.1152
/*2   */   register int i;                                                                                                                                        // (25) 0.009766
/*4   */   int __attribute__ ((aligned (16))) tempo[4];                                                                                                           // (14) 0.02734
/*8   */   if (filterSize % 4) {                                                                                                                                  // (21) 0.01758
/*10  */     for(i=0; i<dstW; i++) {                                                                                                                              // (8) 0.03516
/*12  */       register int j;                                                                                                                                    // (22) 0.01758
/*14  */       register int srcPos = filterPos[i];                                                                                                                // (13) 0.0293
/*16  */       register int val = 0;                                                                                                                              // (19) 0.02148
/*18  */       for(j=0; j<filterSize; j++) {                                                                                                                      // (7) 0.03711
/*20  */ 	val += ((int)src[srcPos + j])*filter[filterSize*i + j];                                                                                                 // (4) 0.04492
/*22  */       }                                                                                                                                                  // (24) 0.01172
/*24  */       dst[i] = av_clip(val>>7, 0, (1<<15)-1);                                                                                                            // (2) 0.05273
/*26  */     }                                                                                                                                                    // (26) 0.007812
/*28  */   }                                                                                                                                                      // (30) 0.003906
/*30  */   else                                                                                                                                                   // (29) 0.003906
/*32  */   switch (filterSize) {                                                                                                                                  // (23) 0.01367
/*34  */   case 4:                                                                                                                                                // (28) 0.007812
/*36  */     {                                                                                                                                                    // (27) 0.007812
/*38  */       for(i=0; i<dstW; i++) {                                                                                                                            // (6) 0.03906
/*40  */ 	register int srcPos = filterPos[i];                                                                                                                     // (18) 0.02148
/*44  */ 	vector unsigned char src_v0 = vec_ld(srcPos, src);                                                                                                      // (9) 0.03516
/*46  */ 	vector unsigned char src_v1, src_vF;                                                                                                                    // (15) 0.02734
/*48  */ 	vector signed short src_v, filter_v;                                                                                                                    // (17) 0.02344
/*50  */ 	vector signed int val_vEven, val_s;                                                                                                                     // (16) 0.02539
/*52  */ 	if ((((int)src + srcPos)% 16) > 12) {                                                                                                                   // (11) 0.03516
/*54  */ 	  src_v1 = vec_ld(srcPos + 16, src);                                                                                                                    // (10) 0.03516
/*56  */ 	}                                                                                                                                                       // (31) 0.003906
/*58  */ 	src_vF = vec_perm(src_v0, src_v1, vec_lvsl(srcPos, src));                                                                                               // (1) 0.05859
/*62  */ 	src_v = // vec_unpackh sign-extends...                                                                                                                  // (12) 0.03125
/*64  */ 	  (vector signed short)(vec_mergeh((vector unsigned char)vzero, src_vF));                                                                               // (3) 0.04883
/*66  */ 	// now put our elements in the even slots                                                                                                               // (20) 0.01953
/*68  */ 	src_v = vec_mergeh(src_v, (vector signed short)vzero);                                                                                                  // (5) 0.04492
/*72  */ 	filter_v = vec_ld(i << 3, filter);                                                                                                                      // 0.0
/*74  */         // the 3 above is 2 (filterSize == 4) + 1 (sizeof(short) == 2)                                                                                   // 0.0
/*78  */         // the neat trick : we only care for half the elements,                                                                                          // 0.0
/*80  */         // high or low depending on (i<<3)%16 (it's 0 or 8 here),                                                                                        // 0.0
/*82  */         // and we're going to use vec_mule, so we chose                                                                                                  // 0.0
/*84  */         // carefully how to "unpack" the elements into the even slots                                                                                    // 0.0
/*86  */ 	if ((i << 3) % 16)                                                                                                                                      // 0.0
/*88  */ 	  filter_v = vec_mergel(filter_v,(vector signed short)vzero);                                                                                           // 0.0
/*90  */ 	else                                                                                                                                                    // 0.0
/*92  */ 	  filter_v = vec_mergeh(filter_v,(vector signed short)vzero);                                                                                           // 0.0
/*96  */ 	val_vEven = vec_mule(src_v, filter_v);                                                                                                                  // 0.0
/*98  */ 	val_s = vec_sums(val_vEven, vzero);                                                                                                                     // 0.0
/*100 */ 	vec_st(val_s, 0, tempo);                                                                                                                                // 0.0
/*102 */ 	dst[i] = av_clip(tempo[3]>>7, 0, (1<<15)-1);                                                                                                            // 0.0
/*104 */       }                                                                                                                                                  // 0.0
/*106 */     }                                                                                                                                                    // 0.0
/*108 */     break;                                                                                                                                               // 0.0
/*112 */   case 8:                                                                                                                                                // 0.0
/*114 */     {                                                                                                                                                    // 0.0
/*116 */       for(i=0; i<dstW; i++) {                                                                                                                            // 0.0
/*118 */ 	register int srcPos = filterPos[i];                                                                                                                     // 0.0
/*122 */ 	vector unsigned char src_v0 = vec_ld(srcPos, src);                                                                                                      // 0.0
/*124 */ 	vector unsigned char src_v1, src_vF;                                                                                                                    // 0.0
/*126 */ 	vector signed short src_v, filter_v;                                                                                                                    // 0.0
/*128 */ 	vector signed int val_v, val_s;                                                                                                                         // 0.0
/*130 */ 	if ((((int)src + srcPos)% 16) > 8) {                                                                                                                    // 0.0
/*132 */ 	  src_v1 = vec_ld(srcPos + 16, src);                                                                                                                    // 0.0
/*134 */ 	}                                                                                                                                                       // 0.0
/*136 */ 	src_vF = vec_perm(src_v0, src_v1, vec_lvsl(srcPos, src));                                                                                               // 0.0
/*140 */ 	src_v = // vec_unpackh sign-extends...                                                                                                                  // 0.0
/*142 */ 	  (vector signed short)(vec_mergeh((vector unsigned char)vzero, src_vF));                                                                               // 0.0
/*144 */ 	filter_v = vec_ld(i << 4, filter);                                                                                                                      // 0.0
/*146 */         // the 4 above is 3 (filterSize == 8) + 1 (sizeof(short) == 2)                                                                                   // 0.0
/*150 */ 	val_v = vec_msums(src_v, filter_v, (vector signed int)vzero);                                                                                           // 0.0
/*152 */ 	val_s = vec_sums(val_v, vzero);                                                                                                                         // 0.0
/*154 */ 	vec_st(val_s, 0, tempo);                                                                                                                                // 0.0
/*156 */ 	dst[i] = av_clip(tempo[3]>>7, 0, (1<<15)-1);                                                                                                            // 0.0
/*158 */       }                                                                                                                                                  // 0.0
/*160 */     }                                                                                                                                                    // 0.0
/*162 */     break;                                                                                                                                               // 0.0
/*166 */   case 16:                                                                                                                                               // 0.0
/*168 */     {                                                                                                                                                    // 0.0
/*170 */       for(i=0; i<dstW; i++) {                                                                                                                            // 0.0
/*172 */ 	register int srcPos = filterPos[i];                                                                                                                     // 0.0
/*176 */ 	vector unsigned char src_v0 = vec_ld(srcPos, src);                                                                                                      // 0.0
/*178 */ 	vector unsigned char src_v1 = vec_ld(srcPos + 16, src);                                                                                                 // 0.0
/*180 */ 	vector unsigned char src_vF = vec_perm(src_v0, src_v1, vec_lvsl(srcPos, src));                                                                          // 0.0
/*184 */ 	vector signed short src_vA = // vec_unpackh sign-extends...                                                                                             // 0.0
/*186 */ 	  (vector signed short)(vec_mergeh((vector unsigned char)vzero, src_vF));                                                                               // 0.0
/*188 */ 	vector signed short src_vB = // vec_unpackh sign-extends...                                                                                             // 0.0
/*190 */ 	  (vector signed short)(vec_mergel((vector unsigned char)vzero, src_vF));                                                                               // 0.0
/*194 */ 	vector signed short filter_v0 = vec_ld(i << 5, filter);                                                                                                 // 0.0
/*196 */        	vector signed short filter_v1 = vec_ld((i << 5) + 16, filter);                                                                                   // 0.0
/*198 */         // the 5 above are 4 (filterSize == 16) + 1 (sizeof(short) == 2)                                                                                 // 0.0
/*202 */ 	vector signed int val_acc = vec_msums(src_vA, filter_v0, (vector signed int)vzero);                                                                     // 0.0
/*204 */ 	vector signed int val_v = vec_msums(src_vB, filter_v1, val_acc);                                                                                        // 0.0
/*208 */ 	vector signed int val_s = vec_sums(val_v, vzero);                                                                                                       // 0.0
/*212 */ 	vec_st(val_s, 0, tempo);                                                                                                                                // 0.0
/*214 */ 	dst[i] = av_clip(tempo[3]>>7, 0, (1<<15)-1);                                                                                                            // 0.0
/*216 */       }                                                                                                                                                  // 0.0
/*218 */     }                                                                                                                                                    // 0.0
/*220 */     break;                                                                                                                                               // 0.0
/*224 */   default:                                                                                                                                               // 0.0
/*226 */     {                                                                                                                                                    // 0.0
/*228 */       for(i=0; i<dstW; i++) {                                                                                                                            // 0.0
/*230 */ 	register int j;                                                                                                                                         // 0.0
/*232 */ 	register int srcPos = filterPos[i];                                                                                                                     // 0.0
/*236 */         vector signed int val_s, val_v = (vector signed int)vzero;                                                                                       // 0.0
/*238 */ 	vector signed short filter_v0R = vec_ld(i * 2 * filterSize, filter);                                                                                    // 0.0
/*240 */         vector unsigned char permF = vec_lvsl((i * 2 * filterSize), filter);                                                                             // 0.0
/*244 */         vector unsigned char src_v0 = vec_ld(srcPos, src);                                                                                               // 0.0
/*246 */         vector unsigned char permS = vec_lvsl(srcPos, src);                                                                                              // 0.0
/*250 */         for (j = 0 ; j < filterSize - 15; j += 16) {                                                                                                     // 0.0
/*252 */           vector unsigned char src_v1 = vec_ld(srcPos + j + 16, src);                                                                                    // 0.0
/*254 */           vector unsigned char src_vF = vec_perm(src_v0, src_v1, permS);                                                                                 // 0.0
/*258 */           vector signed short src_vA = // vec_unpackh sign-extends...                                                                                    // 0.0
/*260 */             (vector signed short)(vec_mergeh((vector unsigned char)vzero, src_vF));                                                                      // 0.0
/*262 */           vector signed short src_vB = // vec_unpackh sign-extends...                                                                                    // 0.0
/*264 */             (vector signed short)(vec_mergel((vector unsigned char)vzero, src_vF));                                                                      // 0.0
/*268 */           vector signed short filter_v1R = vec_ld((i * 2 * filterSize) + (j * 2) + 16, filter);                                                          // 0.0
/*270 */           vector signed short filter_v2R = vec_ld((i * 2 * filterSize) + (j * 2) + 32, filter);                                                          // 0.0
/*272 */           vector signed short filter_v0 = vec_perm(filter_v0R, filter_v1R, permF);                                                                       // 0.0
/*274 */           vector signed short filter_v1 = vec_perm(filter_v1R, filter_v2R, permF);                                                                       // 0.0
/*278 */           vector signed int val_acc = vec_msums(src_vA, filter_v0, val_v);                                                                               // 0.0
/*280 */           val_v = vec_msums(src_vB, filter_v1, val_acc);                                                                                                 // 0.0
/*284 */           filter_v0R = filter_v2R;                                                                                                                       // 0.0
/*286 */           src_v0 = src_v1;                                                                                                                               // 0.0
/*288 */         }                                                                                                                                                // 0.0
/*292 */         if (j < (filterSize-7)) {                                                                                                                        // 0.0
/*294 */           // loading src_v0 is useless, it's already done above                                                                                          // 0.0
/*296 */           //vector unsigned char src_v0 = vec_ld(srcPos + j, src);                                                                                       // 0.0
/*298 */           vector unsigned char src_v1, src_vF;                                                                                                           // 0.0
/*300 */           vector signed short src_v, filter_v1R, filter_v;                                                                                               // 0.0
/*302 */           if ((((int)src + srcPos)% 16) > 8) {                                                                                                           // 0.0
/*304 */             src_v1 = vec_ld(srcPos + j + 16, src);                                                                                                       // 0.0
/*306 */           }                                                                                                                                              // 0.0
/*308 */           src_vF = vec_perm(src_v0, src_v1, permS);                                                                                                      // 0.0
/*312 */           src_v = // vec_unpackh sign-extends...                                                                                                         // 0.0
/*314 */             (vector signed short)(vec_mergeh((vector unsigned char)vzero, src_vF));                                                                      // 0.0
/*316 */           // loading filter_v0R is useless, it's already done above                                                                                      // 0.0
/*318 */           //vector signed short filter_v0R = vec_ld((i * 2 * filterSize) + j, filter);                                                                   // 0.0
/*320 */           filter_v1R = vec_ld((i * 2 * filterSize) + (j * 2) + 16, filter);                                                                              // 0.0
/*322 */           filter_v = vec_perm(filter_v0R, filter_v1R, permF);                                                                                            // 0.0
/*326 */           val_v = vec_msums(src_v, filter_v, val_v);                                                                                                     // 0.0
/*328 */         }                                                                                                                                                // 0.0
/*332 */         val_s = vec_sums(val_v, vzero);                                                                                                                  // 0.0
/*336 */         vec_st(val_s, 0, tempo);                                                                                                                         // 0.0
/*338 */         dst[i] = av_clip(tempo[3]>>7, 0, (1<<15)-1);                                                                                                     // 0.0
/*340 */       }                                                                                                                                                  // 0.0
/*344 */     }                                                                                                                                                    // 0.0
/*346 */   }                                                                                                                                                      // 0.0
/*348 */ }                                                                                                                                                        // 0.0
