// commit message qemu@8d04fb55de (target=1, prob=0.99911755, correct=True): tcg: drop global lock during TCG code execution
/*0  */ void arm_cpu_do_interrupt(CPUState *cs)                                        // (16) 0.0293
/*1  */ {                                                                              // (25) 0.001953
/*2  */     ARMCPU *cpu = ARM_CPU(cs);                                                 // (17) 0.0293
/*3  */     CPUARMState *env = &cpu->env;                                              // (18) 0.02734
/*4  */     unsigned int new_el = env->exception.target_el;                            // (10) 0.03516
/*5  */     assert(!arm_feature(env, ARM_FEATURE_M));                                  // (9) 0.03711
/*6  */     arm_log_exception(cs->exception_index);                                    // (14) 0.0332
/*7  */     qemu_log_mask(CPU_LOG_INT, "...from EL%d to EL%d\n", arm_current_el(env),  // (2) 0.07227
/*8  */                   new_el);                                                     // (8) 0.04102
/*9  */     if (qemu_loglevel_mask(CPU_LOG_INT)                                        // (7) 0.04102
/*10 */         && !excp_is_internal(cs->exception_index)) {                           // (5) 0.04687
/*11 */         qemu_log_mask(CPU_LOG_INT, "...with ESR %x/0x%" PRIx32 "\n",           // (1) 0.07422
/*12 */                       env->exception.syndrome >> ARM_EL_EC_SHIFT,              // (0) 0.07617
/*13 */                       env->exception.syndrome);                                // (4) 0.05859
/*14 */     }                                                                          // (24) 0.007812
/*15 */     if (arm_is_psci_call(cpu, cs->exception_index)) {                          // (6) 0.04687
/*16 */         arm_handle_psci_call(cpu);                                             // (11) 0.03516
/*17 */         qemu_log_mask(CPU_LOG_INT, "...handled as PSCI call\n");               // (3) 0.06055
/*18 */         return;                                                                // (20) 0.01758
/*19 */     }                                                                          // (22) 0.007812
/*20 */     /* Semihosting semantics depend on the register width of the               // (15) 0.03125
/*21 */      * code that caused the exception, not the target exception level,         // (12) 0.03321
/*22 */      * so must be handled here.                                                // (19) 0.02148
/*23 */     if (check_for_semihosting(cs)) {                                           // (13) 0.0332
/*24 */         return;                                                                // (21) 0.01758
/*25 */     }                                                                          // (23) 0.007812
/*26 */     assert(!excp_is_internal(cs->exception_index));                            // 0.0
/*27 */     if (arm_el_is_aa64(env, new_el)) {                                         // 0.0
/*28 */         arm_cpu_do_interrupt_aarch64(cs);                                      // 0.0
/*29 */     } else {                                                                   // 0.0
/*30 */         arm_cpu_do_interrupt_aarch32(cs);                                      // 0.0
/*31 */     }                                                                          // 0.0
/*32 */     arm_call_el_change_hook(cpu);                                              // 0.0
/*33 */     if (!kvm_enabled()) {                                                      // 0.0
/*34 */         cs->interrupt_request |= CPU_INTERRUPT_EXITTB;                         // 0.0
/*35 */     }                                                                          // 0.0
/*36 */ }                                                                              // 0.0
