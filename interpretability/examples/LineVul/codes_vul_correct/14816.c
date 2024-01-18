// commit message qemu@8d04fb55de (target=1, prob=0.7473712, correct=True): tcg: drop global lock during TCG code execution
/*0  */ void HELPER(set_cp_reg64)(CPUARMState *env, void *rip, uint64_t value)  // (0) 0.3913
/*2  */ {                                                                       // (3) 0.01449
/*4  */     const ARMCPRegInfo *ri = rip;                                       // (2) 0.2029
/*8  */     ri->writefn(env, ri, value);                                        // (1) 0.2319
/*10 */ }                                                                       // (4) 0.01449
