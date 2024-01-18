// commit message FFmpeg@8772d2511a (target=1, prob=0.62902707, correct=True): g723_1: fix off-by-one error in normalize_bits()
/*0  */ static int normalize_bits(int num, int width)  // (1) 0.1287
/*2  */ {                                              // (8) 0.009901
/*4  */     if (!num)                                  // (7) 0.06931
/*6  */         return 0;                              // (5) 0.09901
/*8  */     if (num == -1)                             // (3) 0.09901
/*10 */         return width;                          // (4) 0.09901
/*12 */     if (num < 0)                               // (6) 0.08911
/*14 */         num = ~num;                            // (2) 0.1188
/*18 */     return width - av_log2(num);               // (0) 0.1287
/*20 */ }                                              // (9) 0.009901
