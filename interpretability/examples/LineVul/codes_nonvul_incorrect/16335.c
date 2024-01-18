// commit message FFmpeg@7cf22c7970 (target=0, prob=0.6966037, correct=False): swscale/output: fix undefined left shifts of negative numbers
/*0   */ yuv2rgba64_full_X_c_template(SwsContext *c, const int16_t *lumFilter,                   // (7) 0.06055
/*2   */                        const int32_t **lumSrc, int lumFilterSize,                       // (4) 0.07422
/*4   */                        const int16_t *chrFilter, const int32_t **chrUSrc,               // (1) 0.08398
/*6   */                        const int32_t **chrVSrc, int chrFilterSize,                      // (3) 0.07617
/*8   */                        const int32_t **alpSrc, uint16_t *dest, int dstW,                // (0) 0.08594
/*10  */                        int y, enum AVPixelFormat target, int hasAlpha, int eightbytes)  // (2) 0.07813
/*12  */ {                                                                                       // (19) 0.001953
/*14  */     int i;                                                                              // (18) 0.01172
/*16  */     int A = 0xffff<<14;                                                                 // (15) 0.02344
/*20  */     for (i = 0; i < dstW; i++) {                                                        // (11) 0.0332
/*22  */         int j;                                                                          // (16) 0.01953
/*24  */         int Y  = -0x40000000;                                                           // (12) 0.0332
/*26  */         int U  = -128 << 23; // 19                                                      // (10) 0.03516
/*28  */         int V  = -128 << 23;                                                            // (13) 0.03125
/*30  */         int R, G, B;                                                                    // (14) 0.02734
/*34  */         for (j = 0; j < lumFilterSize; j++) {                                           // (9) 0.04297
/*36  */             Y += lumSrc[j][i]  * (unsigned)lumFilter[j];                                // (5) 0.0625
/*38  */         }                                                                               // (17) 0.01562
/*40  */         for (j = 0; j < chrFilterSize; j++) {;                                          // (8) 0.04687
/*42  */             U += chrUSrc[j][i] * (unsigned)chrFilter[j];                                // (6) 0.0625
/*44  */             V += chrVSrc[j][i] * (unsigned)chrFilter[j];                                // 0.0
/*46  */         }                                                                               // 0.0
/*50  */         if (hasAlpha) {                                                                 // 0.0
/*52  */             A = -0x40000000;                                                            // 0.0
/*54  */             for (j = 0; j < lumFilterSize; j++) {                                       // 0.0
/*56  */                 A += alpSrc[j][i] * (unsigned)lumFilter[j];                             // 0.0
/*58  */             }                                                                           // 0.0
/*60  */             A >>= 1;                                                                    // 0.0
/*62  */             A += 0x20002000;                                                            // 0.0
/*64  */         }                                                                               // 0.0
/*68  */         // 8bit: 12+15=27; 16-bit: 12+19=31                                             // 0.0
/*70  */         Y  >>= 14; // 10                                                                // 0.0
/*72  */         Y += 0x10000;                                                                   // 0.0
/*74  */         U  >>= 14;                                                                      // 0.0
/*76  */         V  >>= 14;                                                                      // 0.0
/*80  */         // 8bit: 27 -> 17bit, 16bit: 31 - 14 = 17bit                                    // 0.0
/*82  */         Y -= c->yuv2rgb_y_offset;                                                       // 0.0
/*84  */         Y *= c->yuv2rgb_y_coeff;                                                        // 0.0
/*86  */         Y += 1 << 13; // 21                                                             // 0.0
/*88  */         // 8bit: 17 + 13bit = 30bit, 16bit: 17 + 13bit = 30bit                          // 0.0
/*92  */         R = V * c->yuv2rgb_v2r_coeff;                                                   // 0.0
/*94  */         G = V * c->yuv2rgb_v2g_coeff + U * c->yuv2rgb_u2g_coeff;                        // 0.0
/*96  */         B =                            U * c->yuv2rgb_u2b_coeff;                        // 0.0
/*100 */         // 8bit: 30 - 22 = 8bit, 16bit: 30bit - 14 = 16bit                              // 0.0
/*102 */         output_pixel(&dest[0], av_clip_uintp2(R_B + Y, 30) >> 14);                      // 0.0
/*104 */         output_pixel(&dest[1], av_clip_uintp2(  G + Y, 30) >> 14);                      // 0.0
/*106 */         output_pixel(&dest[2], av_clip_uintp2(B_R + Y, 30) >> 14);                      // 0.0
/*108 */         if (eightbytes) {                                                               // 0.0
/*110 */             output_pixel(&dest[3], av_clip_uintp2(A, 30) >> 14);                        // 0.0
/*112 */             dest += 4;                                                                  // 0.0
/*114 */         } else {                                                                        // 0.0
/*116 */             dest += 3;                                                                  // 0.0
/*118 */         }                                                                               // 0.0
/*120 */     }                                                                                   // 0.0
/*122 */ }                                                                                       // 0.0
