// commit message FFmpeg@13a099799e (target=0, prob=0.4621865, correct=True): swscale: change prototypes of scaled YUV output functions.
/*0  */ yuv2422_2_c_template(SwsContext *c, const uint16_t *buf0,                         // (8) 0.05078
/*2  */                      const uint16_t *buf1, const uint16_t *ubuf0,                 // (6) 0.07617
/*4  */                      const uint16_t *ubuf1, const uint16_t *vbuf0,                // (4) 0.07812
/*6  */                      const uint16_t *vbuf1, const uint16_t *abuf0,                // (5) 0.07812
/*8  */                      const uint16_t *abuf1, uint8_t *dest, int dstW,              // (3) 0.08008
/*10 */                      int yalpha, int uvalpha, int y,                              // (7) 0.0625
/*12 */                      enum PixelFormat target)                                     // (9) 0.04883
/*14 */ {                                                                                 // (14) 0.001953
/*16 */     int  yalpha1 = 4095 - yalpha;                                                 // (12) 0.0293
/*18 */     int uvalpha1 = 4095 - uvalpha;                                                // (11) 0.03125
/*20 */     int i;                                                                        // (13) 0.01172
/*24 */     for (i = 0; i < (dstW >> 1); i++) {                                           // (10) 0.04102
/*26 */         int Y1 = (buf0[i * 2]     * yalpha1  + buf1[i * 2]     * yalpha)  >> 19;  // (1) 0.09375
/*28 */         int Y2 = (buf0[i * 2 + 1] * yalpha1  + buf1[i * 2 + 1] * yalpha)  >> 19;  // (2) 0.08594
/*30 */         int U  = (ubuf0[i]        * uvalpha1 + ubuf1[i]        * uvalpha) >> 19;  // (0) 0.1016
/*32 */         int V  = (vbuf0[i]        * uvalpha1 + vbuf1[i]        * uvalpha) >> 19;  // 0.0
/*36 */         output_pixels(i * 4, Y1, U, Y2, V);                                       // 0.0
/*38 */     }                                                                             // 0.0
/*40 */ }                                                                                 // 0.0
