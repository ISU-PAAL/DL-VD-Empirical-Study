// commit message qemu@966439a678 (target=1, prob=0.9983473, correct=True): PowerPC flags update/use fixes: - fix confusion between overflow/summary overflow, as reported by S Bansal. - reset carry in addic. optimized case (as it was already done in addic).
/*0  */ void do_divwuo (void)                      // (6) 0.06618
/*2  */ {                                          // (9) 0.007353
/*4  */     if (likely((uint32_t)T1 != 0)) {       // (1) 0.1324
/*6  */         xer_ov = 0;                        // (2) 0.1029
/*8  */         T0 = (uint32_t)T0 / (uint32_t)T1;  // (0) 0.2059
/*10 */     } else {                               // (7) 0.04412
/*12 */         xer_so = 1;                        // (3) 0.1029
/*14 */         xer_ov = 1;                        // (4) 0.1029
/*16 */         T0 = 0;                            // (5) 0.08824
/*18 */     }                                      // (8) 0.02941
/*20 */ }                                          // (10) 0.007353
