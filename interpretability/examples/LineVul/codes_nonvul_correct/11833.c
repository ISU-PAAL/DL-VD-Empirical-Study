// commit message qemu@ba9c5de5f2 (target=0, prob=0.05102127, correct=True): target-alpha: Set PC correctly for floating-point exceptions
/*0  */ void alpha_cpu_unassigned_access(CPUState *cs, hwaddr addr,                // (2) 0.1061
/*2  */                                  bool is_write, bool is_exec, int unused,  // (0) 0.2273
/*4  */                                  unsigned size)                            // (1) 0.1768
/*6  */ {                                                                          // (8) 0.005051
/*8  */     AlphaCPU *cpu = ALPHA_CPU(cs);                                         // (5) 0.07576
/*10 */     CPUAlphaState *env = &cpu->env;                                        // (6) 0.07071
/*14 */     env->trap_arg0 = addr;                                                 // (7) 0.06061
/*16 */     env->trap_arg1 = is_write ? 1 : 0;                                     // (4) 0.09091
/*18 */     dynamic_excp(env, 0, EXCP_MCHK, 0);                                    // (3) 0.1061
/*20 */ }                                                                          // (9) 0.005051
