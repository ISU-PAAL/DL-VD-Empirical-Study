// commit message qemu@59800ec8e5 (target=0, prob=0.004665302, correct=True): target-ppc: Add set_fprf Argument to fload_invalid_op_excp()
/*0  */ uint64_t helper_frsp(CPUPPCState *env, uint64_t arg)         // (4) 0.1058
/*2  */ {                                                            // (11) 0.004808
/*4  */     CPU_DoubleU farg;                                        // (6) 0.04808
/*6  */     float32 f32;                                             // (9) 0.03846
/*10 */     farg.ll = arg;                                           // (7) 0.04808
/*14 */     if (unlikely(float64_is_signaling_nan(farg.d))) {        // (3) 0.1154
/*16 */         /* sNaN square root */                               // (5) 0.06731
/*18 */         fload_invalid_op_excp(env, POWERPC_EXCP_FP_VXSNAN);  // (0) 0.1587
/*20 */     }                                                        // (10) 0.01923
/*22 */     f32 = float64_to_float32(farg.d, &env->fp_status);       // (1) 0.125
/*24 */     farg.d = float32_to_float64(f32, &env->fp_status);       // (2) 0.125
/*28 */     return farg.ll;                                          // (8) 0.04327
/*30 */ }                                                            // (12) 0.004808
