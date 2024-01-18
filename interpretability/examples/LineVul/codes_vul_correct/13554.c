// commit message qemu@c24a8a0b6d (target=1, prob=0.662806, correct=True): target-alpha: Raise IOV from CVTTQ
/*0 */ uint64_t helper_cvttq_c(CPUAlphaState *env, uint64_t a)   // (0) 0.4138
/*2 */ {                                                         // (2) 0.01724
/*4 */     return inline_cvttq(env, a, float_round_to_zero, 0);  // (1) 0.4138
/*6 */ }                                                         // (3) 0.01724
