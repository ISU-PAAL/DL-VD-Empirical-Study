// commit message FFmpeg@c23acbaed4 (target=1, prob=0.9862925, correct=True): Don't use ff_cropTbl[] for IDCT.
/*0  */ void FUNCC(ff_h264_idct_add)(uint8_t *_dst, DCTELEM *_block, int stride)  // (1) 0.06836
/*2  */ {                                                                         // (21) 0.001953
/*4  */     int i;                                                                // (19) 0.01172
/*6  */     INIT_CLIP                                                             // (18) 0.01563
/*8  */     pixel *dst = (pixel*)_dst;                                            // (15) 0.0293
/*10 */     dctcoef *block = (dctcoef*)_block;                                    // (12) 0.03711
/*12 */     stride /= sizeof(pixel);                                              // (17) 0.01953
/*16 */     block[0] += 1 << 5;                                                   // (16) 0.02344
/*20 */     for(i=0; i<4; i++){                                                   // (13) 0.03125
/*22 */         const int z0=  block[i + 4*0]     +  block[i + 4*2];              // (4) 0.06836
/*24 */         const int z1=  block[i + 4*0]     -  block[i + 4*2];              // (2) 0.06836
/*26 */         const int z2= (block[i + 4*1]>>1) -  block[i + 4*3];              // (6) 0.06641
/*28 */         const int z3=  block[i + 4*1]     + (block[i + 4*3]>>1);          // (0) 0.07422
/*32 */         block[i + 4*0]= z0 + z3;                                          // (8) 0.04102
/*34 */         block[i + 4*1]= z1 + z2;                                          // (9) 0.04102
/*36 */         block[i + 4*2]= z1 - z2;                                          // (10) 0.04102
/*38 */         block[i + 4*3]= z0 - z3;                                          // (11) 0.04102
/*40 */     }                                                                     // (20) 0.007812
/*44 */     for(i=0; i<4; i++){                                                   // (14) 0.03125
/*46 */         const int z0=  block[0 + 4*i]     +  block[2 + 4*i];              // (3) 0.06836
/*48 */         const int z1=  block[0 + 4*i]     -  block[2 + 4*i];              // (5) 0.06836
/*50 */         const int z2= (block[1 + 4*i]>>1) -  block[3 + 4*i];              // (7) 0.06641
/*52 */         const int z3=  block[1 + 4*i]     + (block[3 + 4*i]>>1);          // 0.0
/*56 */         dst[i + 0*stride]= CLIP(dst[i + 0*stride] + ((z0 + z3) >> 6));    // 0.0
/*58 */         dst[i + 1*stride]= CLIP(dst[i + 1*stride] + ((z1 + z2) >> 6));    // 0.0
/*60 */         dst[i + 2*stride]= CLIP(dst[i + 2*stride] + ((z1 - z2) >> 6));    // 0.0
/*62 */         dst[i + 3*stride]= CLIP(dst[i + 3*stride] + ((z0 - z3) >> 6));    // 0.0
/*64 */     }                                                                     // 0.0
/*66 */ }                                                                         // 0.0
