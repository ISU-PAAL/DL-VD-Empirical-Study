// commit message qemu@7d1b0095bf (target=1, prob=0.996203, correct=True): target-arm: Remove ad-hoc leak checking code
/*0  */ static inline TCGv iwmmxt_load_creg(int reg)                              // (1) 0.2118
/*2  */ {                                                                         // (4) 0.01176
/*4  */     TCGv var = new_tmp();                                                 // (2) 0.1412
/*6  */     tcg_gen_ld_i32(var, cpu_env, offsetof(CPUState, iwmmxt.cregs[reg]));  // (0) 0.4353
/*8  */     return var;                                                           // (3) 0.07059
/*10 */ }                                                                         // (5) 0.01176
