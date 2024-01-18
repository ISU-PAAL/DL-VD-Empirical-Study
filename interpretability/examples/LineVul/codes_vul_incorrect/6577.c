// commit message qemu@61c7480fa3 (target=1, prob=0.40316838, correct=False): linux-user: fix broken cpu_copy()
/*0  */ CPUArchState *cpu_copy(CPUArchState *env)                                     // (12) 0.03794
/*2  */ {                                                                             // (21) 0.00271
/*4  */     CPUState *cpu = ENV_GET_CPU(env);                                         // (8) 0.04607
/*6  */     CPUState *new_cpu = cpu_init(cpu_model);                                  // (7) 0.04878
/*8  */     CPUArchState *new_env = cpu->env_ptr;                                     // (9) 0.04607
/*10 */     CPUBreakpoint *bp;                                                        // (16) 0.02439
/*12 */     CPUWatchpoint *wp;                                                        // (17) 0.02439
/*16 */     /* Reset non arch specific state */                                       // (15) 0.0271
/*18 */     cpu_reset(new_cpu);                                                       // (13) 0.02981
/*22 */     memcpy(new_env, env, sizeof(CPUArchState));                               // (6) 0.05149
/*26 */     /* Clone all break/watchpoints.                                           // (14) 0.02981
/*28 */        Note: Once we support ptrace with hw-debug register access, make sure  // (2) 0.06233
/*30 */        BP_CPU break/watchpoints are handled correctly on clone. */            // (5) 0.0542
/*32 */     QTAILQ_INIT(&cpu->breakpoints);                                           // (10) 0.04336
/*34 */     QTAILQ_INIT(&cpu->watchpoints);                                           // (11) 0.04336
/*36 */     QTAILQ_FOREACH(bp, &cpu->breakpoints, entry) {                            // (4) 0.05962
/*38 */         cpu_breakpoint_insert(new_cpu, bp->pc, bp->flags, NULL);              // (1) 0.0813
/*40 */     }                                                                         // (19) 0.01084
/*42 */     QTAILQ_FOREACH(wp, &cpu->watchpoints, entry) {                            // (3) 0.05962
/*44 */         cpu_watchpoint_insert(new_cpu, wp->vaddr, wp->len, wp->flags, NULL);  // (0) 0.09756
/*46 */     }                                                                         // (20) 0.01084
/*50 */     return new_env;                                                           // (18) 0.02168
/*52 */ }                                                                             // (22) 0.00271
