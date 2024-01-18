// commit message FFmpeg@bf2cba4532 (target=1, prob=0.75977063, correct=True): swscale: fix crash in 8-bpc bilinear output without alpha.
/*0  */ yuv2rgb_2_c_template(SwsContext *c, const int16_t *buf[2],                          // (9) 0.05469
/*2  */                      const int16_t *ubuf[2], const int16_t *vbuf[2],                // (3) 0.08203
/*4  */                      const int16_t *abuf[2], uint8_t *dest, int dstW,               // (2) 0.08203
/*6  */                      int yalpha, int uvalpha, int y,                                // (7) 0.0625
/*8  */                      enum PixelFormat target, int hasAlpha)                         // (8) 0.05664
/*10 */ {                                                                                   // (15) 0.001954
/*12 */     const int16_t *buf0  = buf[0],  *buf1  = buf[1],                                // (10) 0.05273
/*14 */                   *ubuf0 = ubuf[0], *ubuf1 = ubuf[1],                               // (4) 0.07227
/*16 */                   *vbuf0 = vbuf[0], *vbuf1 = vbuf[1],                               // (5) 0.07227
/*18 */                   *abuf0 = abuf[0], *abuf1 = abuf[1];                               // (6) 0.07227
/*20 */     int  yalpha1 = 4095 - yalpha;                                                   // (13) 0.0293
/*22 */     int uvalpha1 = 4095 - uvalpha;                                                  // (12) 0.03125
/*24 */     int i;                                                                          // (14) 0.01172
/*28 */     for (i = 0; i < (dstW >> 1); i++) {                                             // (11) 0.04102
/*30 */         int Y1 = (buf0[i * 2]     * yalpha1  + buf1[i * 2]     * yalpha)  >> 19;    // (0) 0.09375
/*32 */         int Y2 = (buf0[i * 2 + 1] * yalpha1  + buf1[i * 2 + 1] * yalpha)  >> 19;    // (1) 0.08594
/*34 */         int U  = (ubuf0[i]        * uvalpha1 + ubuf1[i]        * uvalpha) >> 19;    // 0.0
/*36 */         int V  = (vbuf0[i]        * uvalpha1 + vbuf1[i]        * uvalpha) >> 19;    // 0.0
/*38 */         int A1, A2;                                                                 // 0.0
/*40 */         const void *r =  c->table_rV[V],                                            // 0.0
/*42 */                    *g = (c->table_gU[U] + c->table_gV[V]),                          // 0.0
/*44 */                    *b =  c->table_bU[U];                                            // 0.0
/*48 */         if (hasAlpha) {                                                             // 0.0
/*50 */             A1 = (abuf0[i * 2    ] * yalpha1 + abuf1[i * 2    ] * yalpha) >> 19;    // 0.0
/*52 */             A2 = (abuf0[i * 2 + 1] * yalpha1 + abuf1[i * 2 + 1] * yalpha) >> 19;    // 0.0
/*54 */         }                                                                           // 0.0
/*58 */         yuv2rgb_write(dest, i, Y1, Y2, U, V, hasAlpha ? A1 : 0, hasAlpha ? A2 : 0,  // 0.0
/*60 */                       r, g, b, y, target, hasAlpha);                                // 0.0
/*62 */     }                                                                               // 0.0
/*64 */ }                                                                                   // 0.0
