// commit message qemu@185698715d (target=0, prob=0.0042149015, correct=True): softfloat: Rename float*_is_nan() functions to float*_is_quiet_nan()
/*0  */ uint64_t helper_efdctuidz (uint64_t val)                            // (2) 0.1406
/*2  */ {                                                                   // (7) 0.007813
/*4  */     CPU_DoubleU u;                                                  // (5) 0.07031
/*8  */     u.ll = val;                                                     // (6) 0.07031
/*10 */     /* NaN are not treated the same way IEEE 754 does */            // (3) 0.1328
/*12 */     if (unlikely(float64_is_nan(u.d)))                              // (1) 0.1484
/*14 */         return 0;                                                   // (4) 0.07813
/*18 */     return float64_to_uint64_round_to_zero(u.d, &env->vec_status);  // (0) 0.2266
/*20 */ }                                                                   // (8) 0.007812
