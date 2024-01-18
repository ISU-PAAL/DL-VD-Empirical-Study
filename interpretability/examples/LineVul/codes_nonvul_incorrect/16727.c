// commit message FFmpeg@7cf22c7970 (target=0, prob=0.87463313, correct=False): swscale/output: fix undefined left shifts of negative numbers
/*0   */ yuv2rgba64_full_1_c_template(SwsContext *c, const int32_t *buf0,                                     // (5) 0.05859
/*2   */                        const int32_t *ubuf[2], const int32_t *vbuf[2],                               // (1) 0.08594
/*4   */                        const int32_t *abuf0, uint16_t *dest, int dstW,                               // (2) 0.08398
/*6   */                        int uvalpha, int y, enum AVPixelFormat target, int hasAlpha, int eightbytes)  // (0) 0.08789
/*8   */ {                                                                                                    // (19) 0.001953
/*10  */     const int32_t *ubuf0 = ubuf[0], *vbuf0 = vbuf[0];                                                // (6) 0.05469
/*12  */     int i;                                                                                           // (18) 0.01172
/*14  */     int A = 0xffff<<14;                                                                              // (16) 0.02344
/*18  */     if (uvalpha < 2048) {                                                                            // (17) 0.02344
/*20  */         for (i = 0; i < dstW; i++) {                                                                 // (11) 0.04102
/*22  */             int Y  = (buf0[i]) >> 2;                                                                 // (10) 0.04687
/*24  */             int U  = (ubuf0[i] + (-128 << 11)) >> 2;                                                 // (4) 0.06055
/*26  */             int V  = (vbuf0[i] + (-128 << 11)) >> 2;                                                 // (3) 0.06055
/*28  */             int R, G, B;                                                                             // (13) 0.03516
/*32  */             Y -= c->yuv2rgb_y_offset;                                                                // (9) 0.04883
/*34  */             Y *= c->yuv2rgb_y_coeff;                                                                 // (7) 0.05273
/*36  */             Y += 1 << 13;                                                                            // (15) 0.0332
/*40  */             if (hasAlpha) {                                                                          // (14) 0.0332
/*42  */                 A = abuf0[i] << 11;                                                                  // (8) 0.05078
/*46  */                 A += 1 << 13;                                                                        // (12) 0.04102
/*48  */             }                                                                                        // 0.0
/*52  */             R = V * c->yuv2rgb_v2r_coeff;                                                            // 0.0
/*54  */             G = V * c->yuv2rgb_v2g_coeff + U * c->yuv2rgb_u2g_coeff;                                 // 0.0
/*56  */             B =                            U * c->yuv2rgb_u2b_coeff;                                 // 0.0
/*60  */             output_pixel(&dest[0], av_clip_uintp2(R_B + Y, 30) >> 14);                               // 0.0
/*62  */             output_pixel(&dest[1], av_clip_uintp2(  G + Y, 30) >> 14);                               // 0.0
/*64  */             output_pixel(&dest[2], av_clip_uintp2(B_R + Y, 30) >> 14);                               // 0.0
/*66  */             if (eightbytes) {                                                                        // 0.0
/*68  */                 output_pixel(&dest[3], av_clip_uintp2(A, 30) >> 14);                                 // 0.0
/*70  */                 dest += 4;                                                                           // 0.0
/*72  */             } else {                                                                                 // 0.0
/*74  */                 dest += 3;                                                                           // 0.0
/*76  */             }                                                                                        // 0.0
/*78  */         }                                                                                            // 0.0
/*80  */     } else {                                                                                         // 0.0
/*82  */         const int32_t *ubuf1 = ubuf[1], *vbuf1 = vbuf[1];                                            // 0.0
/*84  */         int A = 0xffff<<14;                                                                          // 0.0
/*86  */         for (i = 0; i < dstW; i++) {                                                                 // 0.0
/*88  */             int Y  = (buf0[i]    ) >> 2;                                                             // 0.0
/*90  */             int U  = (ubuf0[i] + ubuf1[i] + (-128 << 12)) >> 3;                                      // 0.0
/*92  */             int V  = (vbuf0[i] + vbuf1[i] + (-128 << 12)) >> 3;                                      // 0.0
/*94  */             int R, G, B;                                                                             // 0.0
/*98  */             Y -= c->yuv2rgb_y_offset;                                                                // 0.0
/*100 */             Y *= c->yuv2rgb_y_coeff;                                                                 // 0.0
/*102 */             Y += 1 << 13;                                                                            // 0.0
/*106 */             if (hasAlpha) {                                                                          // 0.0
/*108 */                 A = abuf0[i] << 11;                                                                  // 0.0
/*112 */                 A += 1 << 13;                                                                        // 0.0
/*114 */             }                                                                                        // 0.0
/*118 */             R = V * c->yuv2rgb_v2r_coeff;                                                            // 0.0
/*120 */             G = V * c->yuv2rgb_v2g_coeff + U * c->yuv2rgb_u2g_coeff;                                 // 0.0
/*122 */             B =                            U * c->yuv2rgb_u2b_coeff;                                 // 0.0
/*126 */             output_pixel(&dest[0], av_clip_uintp2(R_B + Y, 30) >> 14);                               // 0.0
/*128 */             output_pixel(&dest[1], av_clip_uintp2(  G + Y, 30) >> 14);                               // 0.0
/*130 */             output_pixel(&dest[2], av_clip_uintp2(B_R + Y, 30) >> 14);                               // 0.0
/*132 */             if (eightbytes) {                                                                        // 0.0
/*134 */                 output_pixel(&dest[3], av_clip_uintp2(A, 30) >> 14);                                 // 0.0
/*136 */                 dest += 4;                                                                           // 0.0
/*138 */             } else {                                                                                 // 0.0
/*140 */                 dest += 3;                                                                           // 0.0
/*142 */             }                                                                                        // 0.0
/*144 */         }                                                                                            // 0.0
/*146 */     }                                                                                                // 0.0
/*148 */ }                                                                                                    // 0.0
