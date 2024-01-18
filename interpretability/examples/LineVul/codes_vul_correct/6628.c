// commit message qemu@d96391c1ff (target=1, prob=0.8805246, correct=True): target-mips: Fix RDHWR exception host PC
/*0 */ target_ulong helper_rdhwr_cpunum(CPUMIPSState *env)  // (0) 0.3387
/*2 */ {                                                    // (3) 0.01613
/*4 */     check_hwrena(env, 0);                            // (2) 0.2097
/*6 */     return env->CP0_EBase & 0x3ff;                   // (1) 0.2742
/*8 */ }                                                    // (4) 0.01613
