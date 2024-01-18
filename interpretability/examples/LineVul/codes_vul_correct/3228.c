// commit message qemu@0fcec41eec (target=1, prob=0.9973017, correct=True): target-sparc: fix udiv(cc) and sdiv(cc)
/*0  */ target_ulong helper_sdiv(target_ulong a, target_ulong b)  // (2) 0.08367
/*2  */ {                                                         // (16) 0.003984
/*4  */     int64_t x0;                                           // (11) 0.03984
/*6  */     int32_t x1;                                           // (12) 0.03984
/*10 */     x0 = (a & 0xffffffff) | ((int64_t) (env->y) << 32);   // (0) 0.1155
/*12 */     x1 = (b & 0xffffffff);                                // (7) 0.05578
/*16 */     if (x1 == 0) {                                        // (9) 0.04382
/*18 */         raise_exception(TT_DIV_ZERO);                     // (3) 0.0757
/*20 */     }                                                     // (14) 0.01594
/*24 */     x0 = x0 / x1;                                         // (8) 0.04781
/*26 */     if ((int32_t) x0 != x0) {                             // (4) 0.06773
/*28 */         env->cc_src2 = 1;                                 // (5) 0.06375
/*30 */         return x0 < 0? 0x80000000: 0x7fffffff;            // (1) 0.09562
/*32 */     } else {                                              // (13) 0.0239
/*34 */         env->cc_src2 = 0;                                 // (6) 0.06375
/*36 */         return x0;                                        // (10) 0.04382
/*38 */     }                                                     // (15) 0.01594
/*40 */ }                                                         // (17) 0.003984
