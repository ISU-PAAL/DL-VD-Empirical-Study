// commit message FFmpeg@2caf19e90f (target=1, prob=0.9934389, correct=True): h264pred: fix aliasing violations.
/*0  */ static void FUNCC(pred8x8_left_dc)(uint8_t *_src, int stride){  // (4) 0.0672
/*2  */     int i;                                                      // (17) 0.01613
/*4  */     int dc0, dc2;                                               // (16) 0.02688
/*6  */     pixel4 dc0splat, dc2splat;                                  // (12) 0.04032
/*8  */     pixel *src = (pixel*)_src;                                  // (13) 0.03495
/*10 */     stride /= sizeof(pixel);                                    // (15) 0.02688
/*14 */     dc0=dc2=0;                                                  // (14) 0.02957
/*16 */     for(i=0;i<4; i++){                                          // (10) 0.04301
/*18 */         dc0+= src[-1+i*stride];                                 // (8) 0.05376
/*20 */         dc2+= src[-1+(i+4)*stride];                             // (7) 0.05914
/*22 */     }                                                           // (18) 0.01075
/*24 */     dc0splat = PIXEL_SPLAT_X4((dc0 + 2)>>2);                    // (0) 0.07258
/*26 */     dc2splat = PIXEL_SPLAT_X4((dc2 + 2)>>2);                    // (1) 0.07258
/*30 */     for(i=0; i<4; i++){                                         // (11) 0.04301
/*32 */         ((pixel4*)(src+i*stride))[0]=                           // (5) 0.05914
/*34 */         ((pixel4*)(src+i*stride))[1]= dc0splat;                 // (2) 0.07258
/*36 */     }                                                           // (20) 0.01075
/*38 */     for(i=4; i<8; i++){                                         // (9) 0.04301
/*40 */         ((pixel4*)(src+i*stride))[0]=                           // (6) 0.05914
/*42 */         ((pixel4*)(src+i*stride))[1]= dc2splat;                 // (3) 0.07258
/*44 */     }                                                           // (19) 0.01075
/*46 */ }                                                               // (21) 0.002688
