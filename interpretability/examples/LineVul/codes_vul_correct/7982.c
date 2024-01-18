// commit message qemu@f8c88bbcda (target=1, prob=0.56457394, correct=True): target-arm: Raw CPSR writes should skip checks and bank switching
/*0  */ static int get_cpsr(QEMUFile *f, void *opaque, size_t size)  // (0) 0.1147
/*2  */ {                                                            // (13) 0.004587
/*4  */     ARMCPU *cpu = opaque;                                    // (9) 0.05046
/*6  */     CPUARMState *env = &cpu->env;                            // (6) 0.06422
/*8  */     uint32_t val = qemu_get_be32(f);                         // (3) 0.09174
/*12 */     env->aarch64 = ((val & PSTATE_nRW) == 0);                // (2) 0.09633
/*16 */     if (is_a64(env)) {                                       // (7) 0.05963
/*18 */         pstate_write(env, val);                              // (5) 0.07339
/*20 */         return 0;                                            // (10) 0.04587
/*22 */     }                                                        // (12) 0.01835
/*26 */     /* Avoid mode switch when restoring CPSR */              // (8) 0.05505
/*28 */     env->uncached_cpsr = val & CPSR_M;                       // (4) 0.08716
/*30 */     cpsr_write(env, val, 0xffffffff, CPSRWriteRaw);          // (1) 0.1055
/*32 */     return 0;                                                // (11) 0.02752
/*34 */ }                                                            // (14) 0.004587
