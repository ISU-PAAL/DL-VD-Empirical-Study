// commit message FFmpeg@ca32f7f208 (target=0, prob=0.9032378, correct=False): H.264: eliminate non-transposed scantable support. It was an ugly hack to begin with and didn't give any performance.
/*0   */ void ff_h264_idct8_add_c(uint8_t *dst, DCTELEM *block, int stride){                      // (3) 0.06446
/*2   */     int i;                                                                               // (15) 0.01172
/*4   */     uint8_t *cm = ff_cropTbl + MAX_NEG_CROP;                                             // (8) 0.04688
/*8   */     block[0] += 32;                                                                      // (14) 0.01953
/*12  */     for( i = 0; i < 8; i++ )                                                             // (13) 0.03125
/*14  */     {                                                                                    // (16) 0.007812
/*16  */         const int a0 =  block[0+i*8] + block[4+i*8];                                     // (7) 0.05859
/*18  */         const int a2 =  block[0+i*8] - block[4+i*8];                                     // (6) 0.05859
/*20  */         const int a4 = (block[2+i*8]>>1) - block[6+i*8];                                 // (5) 0.06445
/*22  */         const int a6 = (block[6+i*8]>>1) + block[2+i*8];                                 // (4) 0.06445
/*26  */         const int b0 = a0 + a6;                                                          // (9) 0.03516
/*28  */         const int b2 = a2 + a4;                                                          // (10) 0.03516
/*30  */         const int b4 = a2 - a4;                                                          // (12) 0.03516
/*32  */         const int b6 = a0 - a6;                                                          // (11) 0.03516
/*36  */         const int a1 = -block[3+i*8] + block[5+i*8] - block[7+i*8] - (block[7+i*8]>>1);  // (0) 0.1016
/*38  */         const int a3 =  block[1+i*8] + block[7+i*8] - block[3+i*8] - (block[3+i*8]>>1);  // (2) 0.1016
/*40  */         const int a5 = -block[1+i*8] + block[7+i*8] + block[5+i*8] + (block[5+i*8]>>1);  // (1) 0.1016
/*42  */         const int a7 =  block[3+i*8] + block[5+i*8] + block[1+i*8] + (block[1+i*8]>>1);  // 0.0
/*46  */         const int b1 = (a7>>2) + a1;                                                     // 0.0
/*48  */         const int b3 =  a3 + (a5>>2);                                                    // 0.0
/*50  */         const int b5 = (a3>>2) - a5;                                                     // 0.0
/*52  */         const int b7 =  a7 - (a1>>2);                                                    // 0.0
/*56  */         block[0+i*8] = b0 + b7;                                                          // 0.0
/*58  */         block[7+i*8] = b0 - b7;                                                          // 0.0
/*60  */         block[1+i*8] = b2 + b5;                                                          // 0.0
/*62  */         block[6+i*8] = b2 - b5;                                                          // 0.0
/*64  */         block[2+i*8] = b4 + b3;                                                          // 0.0
/*66  */         block[5+i*8] = b4 - b3;                                                          // 0.0
/*68  */         block[3+i*8] = b6 + b1;                                                          // 0.0
/*70  */         block[4+i*8] = b6 - b1;                                                          // 0.0
/*72  */     }                                                                                    // 0.0
/*74  */     for( i = 0; i < 8; i++ )                                                             // 0.0
/*76  */     {                                                                                    // 0.0
/*78  */         const int a0 =  block[i+0*8] + block[i+4*8];                                     // 0.0
/*80  */         const int a2 =  block[i+0*8] - block[i+4*8];                                     // 0.0
/*82  */         const int a4 = (block[i+2*8]>>1) - block[i+6*8];                                 // 0.0
/*84  */         const int a6 = (block[i+6*8]>>1) + block[i+2*8];                                 // 0.0
/*88  */         const int b0 = a0 + a6;                                                          // 0.0
/*90  */         const int b2 = a2 + a4;                                                          // 0.0
/*92  */         const int b4 = a2 - a4;                                                          // 0.0
/*94  */         const int b6 = a0 - a6;                                                          // 0.0
/*98  */         const int a1 = -block[i+3*8] + block[i+5*8] - block[i+7*8] - (block[i+7*8]>>1);  // 0.0
/*100 */         const int a3 =  block[i+1*8] + block[i+7*8] - block[i+3*8] - (block[i+3*8]>>1);  // 0.0
/*102 */         const int a5 = -block[i+1*8] + block[i+7*8] + block[i+5*8] + (block[i+5*8]>>1);  // 0.0
/*104 */         const int a7 =  block[i+3*8] + block[i+5*8] + block[i+1*8] + (block[i+1*8]>>1);  // 0.0
/*108 */         const int b1 = (a7>>2) + a1;                                                     // 0.0
/*110 */         const int b3 =  a3 + (a5>>2);                                                    // 0.0
/*112 */         const int b5 = (a3>>2) - a5;                                                     // 0.0
/*114 */         const int b7 =  a7 - (a1>>2);                                                    // 0.0
/*118 */         dst[i + 0*stride] = cm[ dst[i + 0*stride] + ((b0 + b7) >> 6) ];                  // 0.0
/*120 */         dst[i + 1*stride] = cm[ dst[i + 1*stride] + ((b2 + b5) >> 6) ];                  // 0.0
/*122 */         dst[i + 2*stride] = cm[ dst[i + 2*stride] + ((b4 + b3) >> 6) ];                  // 0.0
/*124 */         dst[i + 3*stride] = cm[ dst[i + 3*stride] + ((b6 + b1) >> 6) ];                  // 0.0
/*126 */         dst[i + 4*stride] = cm[ dst[i + 4*stride] + ((b6 - b1) >> 6) ];                  // 0.0
/*128 */         dst[i + 5*stride] = cm[ dst[i + 5*stride] + ((b4 - b3) >> 6) ];                  // 0.0
/*130 */         dst[i + 6*stride] = cm[ dst[i + 6*stride] + ((b2 - b5) >> 6) ];                  // 0.0
/*132 */         dst[i + 7*stride] = cm[ dst[i + 7*stride] + ((b0 - b7) >> 6) ];                  // 0.0
/*134 */     }                                                                                    // 0.0
/*136 */ }                                                                                        // 0.0
