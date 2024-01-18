// commit message qemu@45bbbb466c (target=1, prob=0.97997576, correct=True): added overflow exceptions in divisions
/*0  */ static void idiv64(uint64_t *plow, uint64_t *phigh, int64_t b)  // (0) 0.1474
/*2  */ {                                                               // (13) 0.005263
/*4  */     int sa, sb;                                                 // (9) 0.04737
/*6  */     sa = ((int64_t)*phigh < 0);                                 // (2) 0.08421
/*8  */     if (sa)                                                     // (10) 0.03684
/*10 */         neg128(plow, phigh);                                    // (1) 0.08421
/*12 */     sb = (b < 0);                                               // (7) 0.05789
/*14 */     if (sb)                                                     // (11) 0.03684
/*16 */         b = -b;                                                 // (6) 0.06316
/*18 */     div64(plow, phigh, b);                                      // (5) 0.07368
/*20 */     if (sa ^ sb)                                                // (8) 0.05263
/*22 */         *plow = - *plow;                                        // (3) 0.08421
/*24 */     if (sa)                                                     // (12) 0.03684
/*26 */         *phigh = - *phigh;                                      // (4) 0.08421
/*28 */ }                                                               // (14) 0.005263
