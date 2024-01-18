// commit message FFmpeg@a70c27e813 (target=1, prob=0.94211596, correct=True): Fix overflows in bicubic interpolation.
/*0  */ static always_inline uint8_t vc1_mspel_filter(const uint8_t *src, int stride, int mode, int r)  // (3) 0.1236
/*2  */ {                                                                                               // (12) 0.003636
/*4  */     switch(mode){                                                                               // (10) 0.02545
/*6  */     case 0: //no shift                                                                          // (9) 0.03273
/*8  */         return src[0];                                                                          // (4) 0.04364
/*10 */     case 1: // 1/4 shift                                                                        // (5) 0.04
/*12 */         return (-4*src[-stride] + 53*src[0] + 18*src[stride] - 3*src[stride*2] + 32 - r) >> 6;  // (0) 0.1818
/*14 */     case 2: // 1/2 shift                                                                        // (6) 0.04
/*16 */         return (-src[-stride] + 9*src[0] + 9*src[stride] - src[stride*2] + 8 - r) >> 4;         // (2) 0.1673
/*18 */     case 3: // 3/4 shift                                                                        // (7) 0.04
/*20 */         return (-3*src[-stride] + 18*src[0] + 53*src[stride] - 4*src[stride*2] + 32 - r) >> 6;  // (1) 0.1818
/*22 */     }                                                                                           // (11) 0.01455
/*24 */     return 0; //should not occur                                                                // (8) 0.03636
/*26 */ }                                                                                               // (13) 0.003636
