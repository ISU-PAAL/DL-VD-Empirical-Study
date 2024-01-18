// commit message qemu@5d7fd045ca (target=0, prob=0.006278926, correct=True): target-s390: Convert FP LOAD COMPLIMENT, NEGATIVE, POSITIVE
/*0  */ uint32_t HELPER(lcebr)(CPUS390XState *env, uint32_t f1, uint32_t f2)  // (1) 0.3113
/*2  */ {                                                                     // (3) 0.009434
/*4  */     env->fregs[f1].l.upper = float32_chs(env->fregs[f2].l.upper);     // (0) 0.3302
/*8  */     return set_cc_nz_f32(env->fregs[f1].l.upper);                     // (2) 0.2453
/*10 */ }                                                                     // (4) 0.009434
