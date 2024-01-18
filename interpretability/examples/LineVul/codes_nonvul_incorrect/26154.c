// commit message FFmpeg@13a099799e (target=0, prob=0.5902418, correct=False): swscale: change prototypes of scaled YUV output functions.
/*0  */ yuv2rgb_1_c_template(SwsContext *c, const uint16_t *buf0,                               // (9) 0.05273
/*2  */                      const uint16_t *ubuf0, const uint16_t *ubuf1,                      // (3) 0.07812
/*4  */                      const uint16_t *vbuf0, const uint16_t *vbuf1,                      // (2) 0.07812
/*6  */                      const uint16_t *abuf0, uint8_t *dest, int dstW,                    // (1) 0.08008
/*8  */                      int uvalpha, enum PixelFormat dstFormat,                           // (4) 0.06055
/*10 */                      int flags, int y, enum PixelFormat target,                         // (5) 0.06055
/*12 */                      int hasAlpha)                                                      // (13) 0.04688
/*14 */ {                                                                                       // (17) 0.001953
/*16 */     int i;                                                                              // (16) 0.01172
/*20 */     if (uvalpha < 2048) {                                                               // (15) 0.02344
/*22 */         for (i = 0; i < (dstW >> 1); i++) {                                             // (12) 0.04883
/*24 */             int Y1 = buf0[i * 2]     >> 7;                                              // (8) 0.05664
/*26 */             int Y2 = buf0[i * 2 + 1] >> 7;                                              // (10) 0.05273
/*28 */             int U  = ubuf1[i]        >> 7;                                              // (7) 0.06055
/*30 */             int V  = vbuf1[i]        >> 7;                                              // (6) 0.06055
/*32 */             int A1, A2;                                                                 // (14) 0.03516
/*34 */             const void *r =  c->table_rV[V],                                            // (11) 0.05078
/*36 */                        *g = (c->table_gU[U] + c->table_gV[V]),                          // (0) 0.08789
/*38 */                        *b =  c->table_bU[U];                                            // 0.0
/*42 */             if (hasAlpha) {                                                             // 0.0
/*44 */                 A1 = abuf0[i * 2    ] >> 7;                                             // 0.0
/*46 */                 A2 = abuf0[i * 2 + 1] >> 7;                                             // 0.0
/*48 */             }                                                                           // 0.0
/*52 */             yuv2rgb_write(dest, i, Y1, Y2, U, V, hasAlpha ? A1 : 0, hasAlpha ? A2 : 0,  // 0.0
/*54 */                           r, g, b, y, target, hasAlpha);                                // 0.0
/*56 */         }                                                                               // 0.0
/*58 */     } else {                                                                            // 0.0
/*60 */         for (i = 0; i < (dstW >> 1); i++) {                                             // 0.0
/*62 */             int Y1 =  buf0[i * 2]          >> 7;                                        // 0.0
/*64 */             int Y2 =  buf0[i * 2 + 1]      >> 7;                                        // 0.0
/*66 */             int U  = (ubuf0[i] + ubuf1[i]) >> 8;                                        // 0.0
/*68 */             int V  = (vbuf0[i] + vbuf1[i]) >> 8;                                        // 0.0
/*70 */             int A1, A2;                                                                 // 0.0
/*72 */             const void *r =  c->table_rV[V],                                            // 0.0
/*74 */                        *g = (c->table_gU[U] + c->table_gV[V]),                          // 0.0
/*76 */                        *b =  c->table_bU[U];                                            // 0.0
/*80 */             if (hasAlpha) {                                                             // 0.0
/*82 */                 A1 = abuf0[i * 2    ] >> 7;                                             // 0.0
/*84 */                 A2 = abuf0[i * 2 + 1] >> 7;                                             // 0.0
/*86 */             }                                                                           // 0.0
/*90 */             yuv2rgb_write(dest, i, Y1, Y2, U, V, hasAlpha ? A1 : 0, hasAlpha ? A2 : 0,  // 0.0
/*92 */                           r, g, b, y, target, hasAlpha);                                // 0.0
/*94 */         }                                                                               // 0.0
/*96 */     }                                                                                   // 0.0
/*98 */ }                                                                                       // 0.0
