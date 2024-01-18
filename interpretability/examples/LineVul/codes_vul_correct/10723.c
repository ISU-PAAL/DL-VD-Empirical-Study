// commit message FFmpeg@5a446bc88e (target=1, prob=0.97909045, correct=True): fix an overflow in vc1 intra overlap filter
/*0  */ static void vc1_v_overlap_c(uint8_t* src, int stride)  // (1) 0.07302
/*2  */ {                                                      // (19) 0.003175
/*4  */     int i;                                             // (17) 0.01905
/*6  */     int a, b, c, d;                                    // (13) 0.0381
/*8  */     int d1, d2;                                        // (14) 0.03175
/*10 */     int rnd = 1;                                       // (15) 0.02857
/*12 */     for(i = 0; i < 8; i++) {                           // (8) 0.05079
/*14 */         a = src[-2*stride];                            // (6) 0.05397
/*16 */         b = src[-stride];                              // (9) 0.04762
/*18 */         c = src[0];                                    // (12) 0.04127
/*20 */         d = src[stride];                               // (11) 0.04444
/*22 */         d1 = (a - d + 3 + rnd) >> 3;                   // (2) 0.07302
/*24 */         d2 = (a - d + b - c + 4 - rnd) >> 3;           // (0) 0.08571
/*28 */         src[-2*stride] = a - d1;                       // (3) 0.06667
/*30 */         src[-stride] = b - d2;                         // (4) 0.06032
/*32 */         src[0] = c + d2;                               // (7) 0.05397
/*34 */         src[stride] = d + d1;                          // (5) 0.05714
/*36 */         src++;                                         // (16) 0.02857
/*38 */         rnd = !rnd;                                    // (10) 0.04444
/*40 */     }                                                  // (18) 0.0127
/*42 */ }                                                      // (20) 0.003175
