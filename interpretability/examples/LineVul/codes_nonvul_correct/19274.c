// commit message qemu@185698715d (target=0, prob=0.009413475, correct=True): softfloat: Rename float*_is_nan() functions to float*_is_quiet_nan()
/*0   */ uint32_t helper_compute_fprf (uint64_t arg, uint32_t set_fprf)  // (0) 0.05664
/*2   */ {                                                               // (30) 0.001953
/*4   */     CPU_DoubleU farg;                                           // (21) 0.01953
/*6   */     int isneg;                                                  // (27) 0.01367
/*8   */     int ret;                                                    // (28) 0.01172
/*10  */     farg.ll = arg;                                              // (22) 0.01953
/*12  */     isneg = float64_is_neg(farg.d);                             // (10) 0.03516
/*14  */     if (unlikely(float64_is_nan(farg.d))) {                     // (5) 0.04102
/*16  */         if (float64_is_signaling_nan(farg.d)) {                 // (1) 0.04883
/*18  */             /* Signaling NaN: flags are undefined */            // (6) 0.04102
/*20  */             ret = 0x00;                                         // (11) 0.0332
/*22  */         } else {                                                // (23) 0.01953
/*24  */             /* Quiet NaN */                                     // (15) 0.03125
/*26  */             ret = 0x11;                                         // (12) 0.0332
/*28  */         }                                                       // (25) 0.01562
/*30  */     } else if (unlikely(float64_is_infinity(farg.d))) {         // (2) 0.04688
/*32  */         /* +/- infinity */                                      // (20) 0.02148
/*34  */         if (isneg)                                              // (18) 0.02344
/*36  */             ret = 0x09;                                         // (13) 0.0332
/*38  */         else                                                    // (26) 0.01562
/*40  */             ret = 0x05;                                         // (14) 0.0332
/*42  */     } else {                                                    // (29) 0.01172
/*44  */         if (float64_is_zero(farg.d)) {                          // (3) 0.04297
/*46  */             /* +/- zero */                                      // (17) 0.0293
/*48  */             if (isneg)                                          // (16) 0.03125
/*50  */                 ret = 0x12;                                     // (7) 0.04102
/*52  */             else                                                // (19) 0.02344
/*54  */                 ret = 0x02;                                     // (8) 0.04102
/*56  */         } else {                                                // (24) 0.01953
/*58  */             if (isden(farg.d)) {                                // (4) 0.04297
/*60  */                 /* Denormalized numbers */                      // (9) 0.04102
/*62  */                 ret = 0x10;                                     // 0.0
/*64  */             } else {                                            // 0.0
/*66  */                 /* Normalized numbers */                        // 0.0
/*68  */                 ret = 0x00;                                     // 0.0
/*70  */             }                                                   // 0.0
/*72  */             if (isneg) {                                        // 0.0
/*74  */                 ret |= 0x08;                                    // 0.0
/*76  */             } else {                                            // 0.0
/*78  */                 ret |= 0x04;                                    // 0.0
/*80  */             }                                                   // 0.0
/*82  */         }                                                       // 0.0
/*84  */     }                                                           // 0.0
/*86  */     if (set_fprf) {                                             // 0.0
/*88  */         /* We update FPSCR_FPRF */                              // 0.0
/*90  */         env->fpscr &= ~(0x1F << FPSCR_FPRF);                    // 0.0
/*92  */         env->fpscr |= ret << FPSCR_FPRF;                        // 0.0
/*94  */     }                                                           // 0.0
/*96  */     /* We just need fpcc to update Rc1 */                       // 0.0
/*98  */     return ret & 0xF;                                           // 0.0
/*100 */ }                                                               // 0.0
