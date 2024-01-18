// commit message FFmpeg@7cf22c7970 (target=0, prob=0.8494174, correct=False): swscale/output: fix undefined left shifts of negative numbers
/*0   */ yuv2rgba64_1_c_template(SwsContext *c, const int32_t *buf0,                                          // (6) 0.05469
/*2   */                        const int32_t *ubuf[2], const int32_t *vbuf[2],                               // (1) 0.08594
/*4   */                        const int32_t *abuf0, uint16_t *dest, int dstW,                               // (2) 0.08398
/*6   */                        int uvalpha, int y, enum AVPixelFormat target, int hasAlpha, int eightbytes)  // (0) 0.08789
/*8   */ {                                                                                                    // (17) 0.001953
/*10  */     const int32_t *ubuf0 = ubuf[0], *vbuf0 = vbuf[0];                                                // (8) 0.05469
/*12  */     int i;                                                                                           // (16) 0.01172
/*14  */     int A1 = 0xffff<<14, A2= 0xffff<<14;                                                             // (13) 0.04297
/*18  */     if (uvalpha < 2048) {                                                                            // (15) 0.02344
/*20  */         for (i = 0; i < ((dstW + 1) >> 1); i++) {                                                    // (7) 0.05469
/*22  */             int Y1 = (buf0[i * 2]    ) >> 2;                                                         // (5) 0.05859
/*24  */             int Y2 = (buf0[i * 2 + 1]) >> 2;                                                         // (10) 0.05469
/*26  */             int U  = (ubuf0[i] + (-128 << 11)) >> 2;                                                 // (3) 0.06055
/*28  */             int V  = (vbuf0[i] + (-128 << 11)) >> 2;                                                 // (4) 0.06055
/*30  */             int R, G, B;                                                                             // (14) 0.03516
/*34  */             Y1 -= c->yuv2rgb_y_offset;                                                               // (11) 0.05078
/*36  */             Y2 -= c->yuv2rgb_y_offset;                                                               // (12) 0.05078
/*38  */             Y1 *= c->yuv2rgb_y_coeff;                                                                // (9) 0.05469
/*40  */             Y2 *= c->yuv2rgb_y_coeff;                                                                // 0.0
/*42  */             Y1 += 1 << 13;                                                                           // 0.0
/*44  */             Y2 += 1 << 13;                                                                           // 0.0
/*48  */             if (hasAlpha) {                                                                          // 0.0
/*50  */                 A1 = abuf0[i * 2    ] << 11;                                                         // 0.0
/*52  */                 A2 = abuf0[i * 2 + 1] << 11;                                                         // 0.0
/*56  */                 A1 += 1 << 13;                                                                       // 0.0
/*58  */                 A2 += 1 << 13;                                                                       // 0.0
/*60  */             }                                                                                        // 0.0
/*64  */             R = V * c->yuv2rgb_v2r_coeff;                                                            // 0.0
/*66  */             G = V * c->yuv2rgb_v2g_coeff + U * c->yuv2rgb_u2g_coeff;                                 // 0.0
/*68  */             B =                            U * c->yuv2rgb_u2b_coeff;                                 // 0.0
/*72  */             output_pixel(&dest[0], av_clip_uintp2(R_B + Y1, 30) >> 14);                              // 0.0
/*74  */             output_pixel(&dest[1], av_clip_uintp2(  G + Y1, 30) >> 14);                              // 0.0
/*76  */             output_pixel(&dest[2], av_clip_uintp2(B_R + Y1, 30) >> 14);                              // 0.0
/*78  */             if (eightbytes) {                                                                        // 0.0
/*80  */                 output_pixel(&dest[3], av_clip_uintp2(A1      , 30) >> 14);                          // 0.0
/*82  */                 output_pixel(&dest[4], av_clip_uintp2(R_B + Y2, 30) >> 14);                          // 0.0
/*84  */                 output_pixel(&dest[5], av_clip_uintp2(  G + Y2, 30) >> 14);                          // 0.0
/*86  */                 output_pixel(&dest[6], av_clip_uintp2(B_R + Y2, 30) >> 14);                          // 0.0
/*88  */                 output_pixel(&dest[7], av_clip_uintp2(A2      , 30) >> 14);                          // 0.0
/*90  */                 dest += 8;                                                                           // 0.0
/*92  */             } else {                                                                                 // 0.0
/*94  */                 output_pixel(&dest[3], av_clip_uintp2(R_B + Y2, 30) >> 14);                          // 0.0
/*96  */                 output_pixel(&dest[4], av_clip_uintp2(  G + Y2, 30) >> 14);                          // 0.0
/*98  */                 output_pixel(&dest[5], av_clip_uintp2(B_R + Y2, 30) >> 14);                          // 0.0
/*100 */                 dest += 6;                                                                           // 0.0
/*102 */             }                                                                                        // 0.0
/*104 */         }                                                                                            // 0.0
/*106 */     } else {                                                                                         // 0.0
/*108 */         const int32_t *ubuf1 = ubuf[1], *vbuf1 = vbuf[1];                                            // 0.0
/*110 */         int A1 = 0xffff<<14, A2 = 0xffff<<14;                                                        // 0.0
/*112 */         for (i = 0; i < ((dstW + 1) >> 1); i++) {                                                    // 0.0
/*114 */             int Y1 = (buf0[i * 2]    ) >> 2;                                                         // 0.0
/*116 */             int Y2 = (buf0[i * 2 + 1]) >> 2;                                                         // 0.0
/*118 */             int U  = (ubuf0[i] + ubuf1[i] + (-128 << 12)) >> 3;                                      // 0.0
/*120 */             int V  = (vbuf0[i] + vbuf1[i] + (-128 << 12)) >> 3;                                      // 0.0
/*122 */             int R, G, B;                                                                             // 0.0
/*126 */             Y1 -= c->yuv2rgb_y_offset;                                                               // 0.0
/*128 */             Y2 -= c->yuv2rgb_y_offset;                                                               // 0.0
/*130 */             Y1 *= c->yuv2rgb_y_coeff;                                                                // 0.0
/*132 */             Y2 *= c->yuv2rgb_y_coeff;                                                                // 0.0
/*134 */             Y1 += 1 << 13;                                                                           // 0.0
/*136 */             Y2 += 1 << 13;                                                                           // 0.0
/*140 */             if (hasAlpha) {                                                                          // 0.0
/*142 */                 A1 = abuf0[i * 2    ] << 11;                                                         // 0.0
/*144 */                 A2 = abuf0[i * 2 + 1] << 11;                                                         // 0.0
/*148 */                 A1 += 1 << 13;                                                                       // 0.0
/*150 */                 A2 += 1 << 13;                                                                       // 0.0
/*152 */             }                                                                                        // 0.0
/*156 */             R = V * c->yuv2rgb_v2r_coeff;                                                            // 0.0
/*158 */             G = V * c->yuv2rgb_v2g_coeff + U * c->yuv2rgb_u2g_coeff;                                 // 0.0
/*160 */             B =                            U * c->yuv2rgb_u2b_coeff;                                 // 0.0
/*164 */             output_pixel(&dest[0], av_clip_uintp2(R_B + Y1, 30) >> 14);                              // 0.0
/*166 */             output_pixel(&dest[1], av_clip_uintp2(  G + Y1, 30) >> 14);                              // 0.0
/*168 */             output_pixel(&dest[2], av_clip_uintp2(B_R + Y1, 30) >> 14);                              // 0.0
/*170 */             if (eightbytes) {                                                                        // 0.0
/*172 */                 output_pixel(&dest[3], av_clip_uintp2(A1      , 30) >> 14);                          // 0.0
/*174 */                 output_pixel(&dest[4], av_clip_uintp2(R_B + Y2, 30) >> 14);                          // 0.0
/*176 */                 output_pixel(&dest[5], av_clip_uintp2(  G + Y2, 30) >> 14);                          // 0.0
/*178 */                 output_pixel(&dest[6], av_clip_uintp2(B_R + Y2, 30) >> 14);                          // 0.0
/*180 */                 output_pixel(&dest[7], av_clip_uintp2(A2      , 30) >> 14);                          // 0.0
/*182 */                 dest += 8;                                                                           // 0.0
/*184 */             } else {                                                                                 // 0.0
/*186 */                 output_pixel(&dest[3], av_clip_uintp2(R_B + Y2, 30) >> 14);                          // 0.0
/*188 */                 output_pixel(&dest[4], av_clip_uintp2(  G + Y2, 30) >> 14);                          // 0.0
/*190 */                 output_pixel(&dest[5], av_clip_uintp2(B_R + Y2, 30) >> 14);                          // 0.0
/*192 */                 dest += 6;                                                                           // 0.0
/*194 */             }                                                                                        // 0.0
/*196 */         }                                                                                            // 0.0
/*198 */     }                                                                                                // 0.0
/*200 */ }                                                                                                    // 0.0
