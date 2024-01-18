// commit message qemu@59800ec8e5 (target=0, prob=0.005328421, correct=True): target-ppc: Add set_fprf Argument to fload_invalid_op_excp()
/*0  */ uint64_t helper_fdiv(CPUPPCState *env, uint64_t arg1, uint64_t arg2)              // (7) 0.06198
/*2  */ {                                                                                 // (20) 0.002066
/*4  */     CPU_DoubleU farg1, farg2;                                                     // (11) 0.03099
/*8  */     farg1.ll = arg1;                                                              // (14) 0.02479
/*10 */     farg2.ll = arg2;                                                              // (15) 0.02479
/*14 */     if (unlikely(float64_is_infinity(farg1.d) &&                                  // (9) 0.04752
/*16 */                  float64_is_infinity(farg2.d))) {                                 // (6) 0.06405
/*18 */         /* Division of infinity by infinity */                                    // (12) 0.02893
/*20 */         farg1.ll = fload_invalid_op_excp(env, POWERPC_EXCP_FP_VXIDI);             // (1) 0.08058
/*22 */     } else if (unlikely(float64_is_zero(farg1.d) && float64_is_zero(farg2.d))) {  // (2) 0.07851
/*24 */         /* Division of zero by zero */                                            // (13) 0.02893
/*26 */         farg1.ll = fload_invalid_op_excp(env, POWERPC_EXCP_FP_VXZDZ);             // (0) 0.08264
/*28 */     } else {                                                                      // (18) 0.0124
/*30 */         if (unlikely(float64_is_signaling_nan(farg1.d) ||                         // (8) 0.05992
/*32 */                      float64_is_signaling_nan(farg2.d))) {                        // (3) 0.07645
/*34 */             /* sNaN division */                                                   // (10) 0.03512
/*36 */             fload_invalid_op_excp(env, POWERPC_EXCP_FP_VXSNAN);                   // (4) 0.07645
/*38 */         }                                                                         // (17) 0.01653
/*40 */         farg1.d = float64_div(farg1.d, farg2.d, &env->fp_status);                 // (5) 0.07645
/*42 */     }                                                                             // (19) 0.008264
/*46 */     return farg1.ll;                                                              // (16) 0.02066
/*48 */ }                                                                                 // (21) 0.002066
