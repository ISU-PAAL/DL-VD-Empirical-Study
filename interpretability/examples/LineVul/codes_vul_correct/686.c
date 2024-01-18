// commit message qemu@6f2d897872 (target=1, prob=0.998312, correct=True): Fix usage of the -1 constant in the PowerPC target code: fix invalid size casts and/or sign-extensions.
/*0  */ void do_POWER_maskg (void)                              // (6) 0.05473
/*2  */ {                                                       // (11) 0.004975
/*4  */     uint32_t ret;                                       // (7) 0.04478
/*8  */     if ((uint32_t)T0 == (uint32_t)(T1 + 1)) {           // (3) 0.1244
/*10 */         ret = -1;                                       // (5) 0.0597
/*12 */     } else {                                            // (9) 0.02985
/*14 */         ret = (((uint32_t)(-1)) >> ((uint32_t)T0)) ^    // (1) 0.1493
/*16 */             (((uint32_t)(-1) >> ((uint32_t)T1)) >> 1);  // (0) 0.1692
/*18 */         if ((uint32_t)T0 > (uint32_t)T1)                // (2) 0.1294
/*20 */             ret = ~ret;                                 // (4) 0.0796
/*22 */     }                                                   // (10) 0.0199
/*24 */     T0 = ret;                                           // (8) 0.0398
/*26 */ }                                                       // (12) 0.004975
