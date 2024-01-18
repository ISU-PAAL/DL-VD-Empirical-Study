// commit message qemu@9bb234b3b1 (target=1, prob=0.99883777, correct=True): Fix qemu crash due to sparc division-by-zero, by Aurelien Jarno.
/*0  */ void OPPROTO op_udiv_T1_T0(void)            // (1) 0.1111
/*1  */ {                                           // (13) 0.006536
/*2  */     uint64_t x0;                            // (4) 0.06536
/*3  */     uint32_t x1;                            // (5) 0.06536
/*4  */     x0 = T0 | ((uint64_t) (env->y) << 32);  // (0) 0.1503
/*5  */     x1 = T1;                                // (6) 0.05882
/*6  */     x0 = x0 / x1;                           // (3) 0.07843
/*7  */     if (x0 > 0xffffffff) {                  // (2) 0.0915
/*8  */ 	T0 = 0xffffffff;                           // (7) 0.05882
/*9  */ 	T1 = 1;                                    // (10) 0.03922
/*10 */     } else {                                // (11) 0.03922
/*11 */ 	T0 = x0;                                   // (9) 0.04575
/*12 */ 	T1 = 0;                                    // (12) 0.03922
/*13 */     FORCE_RET();                            // (8) 0.05229
