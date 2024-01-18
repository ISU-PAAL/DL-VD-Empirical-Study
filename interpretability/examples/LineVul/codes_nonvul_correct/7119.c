// commit message qemu@a7812ae412 (target=0, prob=0.005825364, correct=True): TCG variable type checking.
/*0  */ static inline void gen_neon_addl_saturate(TCGv op0, TCGv op1, int size)        // (2) 0.2128
/*2  */ {                                                                              // (6) 0.007092
/*4  */     switch (size) {                                                            // (3) 0.05674
/*6  */     case 1: gen_helper_neon_addl_saturate_s32(op0, cpu_env, op0, op1); break;  // (0) 0.2766
/*8  */     case 2: gen_helper_neon_addl_saturate_s64(op0, cpu_env, op0, op1); break;  // (1) 0.2766
/*10 */     default: abort();                                                          // (4) 0.04965
/*12 */     }                                                                          // (5) 0.02837
/*14 */ }                                                                              // (7) 0.007092
