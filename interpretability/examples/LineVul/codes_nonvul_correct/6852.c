// commit message qemu@185698715d (target=0, prob=0.0053948, correct=True): softfloat: Rename float*_is_nan() functions to float*_is_quiet_nan()
/*0  */ uint32_t helper_fcmp_un(uint32_t a, uint32_t b)                              // (2) 0.109
/*2  */ {                                                                            // (13) 0.004739
/*4  */     CPU_FloatU fa, fb;                                                       // (4) 0.05687
/*6  */     uint32_t r = 0;                                                          // (5) 0.05213
/*10 */     fa.l = a;                                                                // (9) 0.04265
/*12 */     fb.l = b;                                                                // (8) 0.04739
/*16 */     if (float32_is_signaling_nan(fa.f) || float32_is_signaling_nan(fb.f)) {  // (0) 0.1659
/*18 */         update_fpu_flags(float_flag_invalid);                                // (3) 0.09953
/*20 */         r = 1;                                                               // (6) 0.05213
/*22 */     }                                                                        // (11) 0.01896
/*26 */     if (float32_is_nan(fa.f) || float32_is_nan(fb.f)) {                      // (1) 0.1374
/*28 */         r = 1;                                                               // (7) 0.05213
/*30 */     }                                                                        // (12) 0.01896
/*34 */     return r;                                                                // (10) 0.02844
/*36 */ }                                                                            // (14) 0.004739
