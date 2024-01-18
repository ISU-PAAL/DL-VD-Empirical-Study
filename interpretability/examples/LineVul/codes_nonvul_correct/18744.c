// commit message qemu@59800ec8e5 (target=0, prob=0.0045482353, correct=True): target-ppc: Add set_fprf Argument to fload_invalid_op_excp()
/*0  */ uint64_t helper_fsub(CPUPPCState *env, uint64_t arg1, uint64_t arg2)              // (6) 0.07126
/*2  */ {                                                                                 // (17) 0.002375
/*4  */     CPU_DoubleU farg1, farg2;                                                     // (10) 0.03563
/*8  */     farg1.ll = arg1;                                                              // (11) 0.0285
/*10 */     farg2.ll = arg2;                                                              // (12) 0.0285
/*14 */     if (unlikely(float64_is_infinity(farg1.d) && float64_is_infinity(farg2.d) &&  // (2) 0.09026
/*16 */                  float64_is_neg(farg1.d) == float64_is_neg(farg2.d))) {           // (0) 0.1045
/*18 */         /* Magnitude subtraction of infinities */                                 // (9) 0.04038
/*20 */         farg1.ll = fload_invalid_op_excp(env, POWERPC_EXCP_FP_VXISI);             // (1) 0.09264
/*22 */     } else {                                                                      // (15) 0.01425
/*24 */         if (unlikely(float64_is_signaling_nan(farg1.d) ||                         // (7) 0.06888
/*26 */                      float64_is_signaling_nan(farg2.d))) {                        // (3) 0.08789
/*28 */             /* sNaN subtraction */                                                // (8) 0.04276
/*30 */             fload_invalid_op_excp(env, POWERPC_EXCP_FP_VXSNAN);                   // (4) 0.08789
/*32 */         }                                                                         // (14) 0.019
/*34 */         farg1.d = float64_sub(farg1.d, farg2.d, &env->fp_status);                 // (5) 0.08789
/*36 */     }                                                                             // (16) 0.009501
/*40 */     return farg1.ll;                                                              // (13) 0.02375
/*42 */ }                                                                                 // (18) 0.002375
