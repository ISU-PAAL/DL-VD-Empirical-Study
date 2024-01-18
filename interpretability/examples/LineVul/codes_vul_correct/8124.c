// commit message FFmpeg@ab80d3fb3a (target=1, prob=0.81067675, correct=True): swscale/output: fix null pointer dereference in yuv2ya8_2_c()
/*0  */ yuv2ya8_2_c(SwsContext *c, const int16_t *buf[2],                        // (7) 0.05285
/*2  */             const int16_t *ubuf[2], const int16_t *vbuf[2],              // (3) 0.06707
/*4  */             const int16_t *abuf[2], uint8_t *dest, int dstW,             // (2) 0.06707
/*6  */             int yalpha, int uvalpha, int y)                              // (8) 0.04675
/*8  */ {                                                                        // (21) 0.002033
/*10 */     int hasAlpha = abuf[0] && abuf[1];                                   // (13) 0.03659
/*12 */     const int16_t *buf0  = buf[0],  *buf1  = buf[1],                     // (6) 0.05488
/*14 */                   *abuf0 = hasAlpha ? abuf[0] : NULL,                    // (4) 0.06707
/*16 */                   *abuf1 = hasAlpha ? abuf[1] : NULL;                    // (5) 0.06707
/*18 */     int  yalpha1 = 4096 - yalpha;                                        // (15) 0.02846
/*20 */     int i;                                                               // (19) 0.0122
/*24 */     for (i = 0; i < dstW; i++) {                                         // (14) 0.03455
/*26 */         int Y = (buf0[i * 2] * yalpha1 + buf1[i * 2] * yalpha) >> 19;    // (1) 0.0752
/*28 */         int A;                                                           // (17) 0.02033
/*32 */         Y = av_clip_uint8(Y);                                            // (12) 0.03659
/*36 */         if (hasAlpha) {                                                  // (16) 0.02642
/*38 */             A = (abuf0[i * 2] * yalpha1 + abuf1[i * 2] * yalpha) >> 19;  // (0) 0.08537
/*40 */             A = av_clip_uint8(A);                                        // (10) 0.04472
/*42 */         }                                                                // (18) 0.01626
/*46 */         dest[i * 2    ] = Y;                                             // (11) 0.03862
/*48 */         dest[i * 2 + 1] = hasAlpha ? A : 255;                            // (9) 0.04675
/*50 */     }                                                                    // (20) 0.00813
/*52 */ }                                                                        // (22) 0.002033
