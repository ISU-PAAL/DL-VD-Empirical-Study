// commit message FFmpeg@40ad05bab2 (target=0, prob=0.04727645, correct=True): checkasm: Cast unsigned to signed
/*0  */ int float_near_ulp(float a, float b, unsigned max_ulp)  // (2) 0.1118
/*2  */ {                                                       // (11) 0.006211
/*4  */     union av_intfloat32 x, y;                           // (4) 0.08075
/*8  */     x.f = a;                                            // (7) 0.0559
/*10 */     y.f = b;                                            // (8) 0.0559
/*14 */     if (is_negative(x) != is_negative(y)) {             // (1) 0.118
/*16 */         // handle -0.0 == +0.0                          // (3) 0.1118
/*18 */         return a == b;                                  // (5) 0.07453
/*20 */     }                                                   // (10) 0.02484
/*24 */     if (abs(x.i - y.i) <= max_ulp)                      // (0) 0.1242
/*26 */         return 1;                                       // (6) 0.06211
/*30 */     return 0;                                           // (9) 0.03727
/*32 */ }                                                       // (12) 0.006211
