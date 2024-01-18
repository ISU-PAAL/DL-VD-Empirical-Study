// commit message FFmpeg@81cc7d0bd1 (target=1, prob=0.99509346, correct=True): swscale: fix another yuv range conversion overflow in 16bit scaling.
/*0  */ static void lumRangeToJpeg16_c(int16_t *_dst, int width)              // (1) 0.1949
/*2  */ {                                                                     // (5) 0.008475
/*4  */     int i;                                                            // (4) 0.05085
/*6  */     int32_t *dst = (int32_t *) _dst;                                  // (2) 0.178
/*8  */     for (i = 0; i < width; i++)                                       // (3) 0.1271
/*10 */         dst[i] = (FFMIN(dst[i],30189<<4)*19077 - (39057361<<4))>>14;  // (0) 0.339
/*12 */ }                                                                     // (6) 0.008475
