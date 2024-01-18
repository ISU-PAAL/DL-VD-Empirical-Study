// commit message qemu@3d6f761713 (target=0, prob=0.32595617, correct=True): target-arm: Fix wrong AArch64 entry offset for EL2/EL3 target
/*0   */ static void arm_cpu_do_interrupt_aarch64(CPUState *cs)                           // (6) 0.03906
/*2   */ {                                                                                // (28) 0.001953
/*4   */     ARMCPU *cpu = ARM_CPU(cs);                                                   // (12) 0.0293
/*6   */     CPUARMState *env = &cpu->env;                                                // (14) 0.02734
/*8   */     unsigned int new_el = env->exception.target_el;                              // (8) 0.03516
/*10  */     target_ulong addr = env->cp15.vbar_el[new_el];                               // (4) 0.04492
/*12  */     unsigned int new_mode = aarch64_pstate_mode(new_el, true);                   // (3) 0.04688
/*16  */     if (arm_current_el(env) < new_el) {                                          // (7) 0.03711
/*18  */         if (env->aarch64) {                                                      // (11) 0.03125
/*20  */             addr += 0x400;                                                       // (9) 0.0332
/*22  */         } else {                                                                 // (21) 0.01953
/*24  */             addr += 0x600;                                                       // (10) 0.0332
/*26  */         }                                                                        // (26) 0.01562
/*28  */     } else if (pstate_read(env) & PSTATE_SP) {                                   // (5) 0.04102
/*30  */         addr += 0x200;                                                           // (15) 0.02539
/*32  */     }                                                                            // (27) 0.007812
/*36  */     switch (cs->exception_index) {                                               // (16) 0.02539
/*38  */     case EXCP_PREFETCH_ABORT:                                                    // (13) 0.0293
/*40  */     case EXCP_DATA_ABORT:                                                        // (18) 0.02344
/*42  */         env->cp15.far_el[new_el] = env->exception.vaddress;                      // (2) 0.05664
/*44  */         qemu_log_mask(CPU_LOG_INT, "...with FAR 0x%" PRIx64 "\n",                // (0) 0.06641
/*46  */                       env->cp15.far_el[new_el]);                                 // (1) 0.06641
/*48  */         /* fall through */                                                       // (19) 0.02148
/*50  */     case EXCP_BKPT:                                                              // (20) 0.02148
/*52  */     case EXCP_UDEF:                                                              // (22) 0.01953
/*54  */     case EXCP_SWI:                                                               // (23) 0.01953
/*56  */     case EXCP_HVC:                                                               // (24) 0.01953
/*58  */     case EXCP_HYP_TRAP:                                                          // (17) 0.02539
/*60  */     case EXCP_SMC:                                                               // (25) 0.01953
/*62  */         env->cp15.esr_el[new_el] = env->exception.syndrome;                      // 0.0
/*64  */         break;                                                                   // 0.0
/*66  */     case EXCP_IRQ:                                                               // 0.0
/*68  */     case EXCP_VIRQ:                                                              // 0.0
/*70  */         addr += 0x80;                                                            // 0.0
/*72  */         break;                                                                   // 0.0
/*74  */     case EXCP_FIQ:                                                               // 0.0
/*76  */     case EXCP_VFIQ:                                                              // 0.0
/*78  */         addr += 0x100;                                                           // 0.0
/*80  */         break;                                                                   // 0.0
/*82  */     case EXCP_SEMIHOST:                                                          // 0.0
/*84  */         qemu_log_mask(CPU_LOG_INT,                                               // 0.0
/*86  */                       "...handling as semihosting call 0x%" PRIx64 "\n",         // 0.0
/*88  */                       env->xregs[0]);                                            // 0.0
/*90  */         env->xregs[0] = do_arm_semihosting(env);                                 // 0.0
/*92  */         return;                                                                  // 0.0
/*94  */     default:                                                                     // 0.0
/*96  */         cpu_abort(cs, "Unhandled exception 0x%x\n", cs->exception_index);        // 0.0
/*98  */     }                                                                            // 0.0
/*102 */     if (is_a64(env)) {                                                           // 0.0
/*104 */         env->banked_spsr[aarch64_banked_spsr_index(new_el)] = pstate_read(env);  // 0.0
/*106 */         aarch64_save_sp(env, arm_current_el(env));                               // 0.0
/*108 */         env->elr_el[new_el] = env->pc;                                           // 0.0
/*110 */     } else {                                                                     // 0.0
/*112 */         env->banked_spsr[aarch64_banked_spsr_index(new_el)] = cpsr_read(env);    // 0.0
/*114 */         if (!env->thumb) {                                                       // 0.0
/*116 */             env->cp15.esr_el[new_el] |= 1 << 25;                                 // 0.0
/*118 */         }                                                                        // 0.0
/*120 */         env->elr_el[new_el] = env->regs[15];                                     // 0.0
/*124 */         aarch64_sync_32_to_64(env);                                              // 0.0
/*128 */         env->condexec_bits = 0;                                                  // 0.0
/*130 */     }                                                                            // 0.0
/*132 */     qemu_log_mask(CPU_LOG_INT, "...with ELR 0x%" PRIx64 "\n",                    // 0.0
/*134 */                   env->elr_el[new_el]);                                          // 0.0
/*138 */     pstate_write(env, PSTATE_DAIF | new_mode);                                   // 0.0
/*140 */     env->aarch64 = 1;                                                            // 0.0
/*142 */     aarch64_restore_sp(env, new_el);                                             // 0.0
/*146 */     env->pc = addr;                                                              // 0.0
/*150 */     qemu_log_mask(CPU_LOG_INT, "...to EL%d PC 0x%" PRIx64 " PSTATE 0x%x\n",      // 0.0
/*152 */                   new_el, env->pc, pstate_read(env));                            // 0.0
/*154 */ }                                                                                // 0.0
