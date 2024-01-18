// commit message qemu@372579427a (target=1, prob=0.56859195, correct=True): tcg: enable thread-per-vCPU
/*0   */ int cpu_exec(CPUState *cpu)                                                        // (22) 0.01953
/*2   */ {                                                                                  // (31) 0.001953
/*4   */     CPUClass *cc = CPU_GET_CLASS(cpu);                                             // (12) 0.03125
/*6   */     int ret;                                                                       // (28) 0.01172
/*8   */     SyncClocks sc;                                                                 // (25) 0.01563
/*12  */     /* replay_interrupt may need current_cpu */                                    // (16) 0.02734
/*14  */     current_cpu = cpu;                                                             // (24) 0.01758
/*18  */     if (cpu_handle_halt(cpu)) {                                                    // (14) 0.0293
/*20  */         return EXCP_HALTED;                                                        // (15) 0.0293
/*22  */     }                                                                              // (30) 0.007813
/*26  */     rcu_read_lock();                                                               // (23) 0.01953
/*30  */     cc->cpu_exec_enter(cpu);                                                       // (19) 0.02539
/*34  */     /* Calculate difference between guest clock and host clock.                    // (17) 0.02734
/*36  */      * This delay includes the delay of the last cycle, so                         // (13) 0.03125
/*38  */      * what we have to do is sleep until it is 0. As for the                       // (5) 0.03906
/*40  */      * advance/delay we gain here, we try to fix it next time.                     // (6) 0.03906
/*42  */      */                                                                            // (29) 0.009766
/*44  */     init_delay_params(&sc, cpu);                                                   // (20) 0.02539
/*48  */     /* prepare setjmp context for exception handling */                            // (18) 0.02539
/*50  */     if (sigsetjmp(cpu->jmp_env, 0) != 0) {                                         // (3) 0.04688
/*52  */ #if defined(__clang__) || !QEMU_GNUC_PREREQ(4, 6)                                  // (2) 0.05078
/*54  */         /* Some compilers wrongly smash all local variables after                  // (9) 0.0332
/*56  */          * siglongjmp. There were bug reports for gcc 4.5.0 and clang.             // (0) 0.05664
/*58  */          * Reload essential local variables here for those compilers.              // (8) 0.03711
/*60  */          * Newer versions of gcc would complain about this code (-Wclobbered). */  // (1) 0.05078
/*62  */         cpu = current_cpu;                                                         // (21) 0.02539
/*64  */         cc = CPU_GET_CLASS(cpu);                                                   // (10) 0.0332
/*66  */ #else /* buggy compiler */                                                         // (26) 0.01172
/*68  */         /* Assert that the compiler does not smash local variables. */             // (7) 0.03906
/*70  */         g_assert(cpu == current_cpu);                                              // (11) 0.0332
/*72  */         g_assert(cc == CPU_GET_CLASS(cpu));                                        // (4) 0.04102
/*74  */ #endif /* buggy compiler */                                                        // (27) 0.01172
/*76  */         cpu->can_do_io = 1;                                                        // 0.0
/*78  */         tb_lock_reset();                                                           // 0.0
/*80  */         if (qemu_mutex_iothread_locked()) {                                        // 0.0
/*82  */             qemu_mutex_unlock_iothread();                                          // 0.0
/*84  */         }                                                                          // 0.0
/*86  */     }                                                                              // 0.0
/*90  */     /* if an exception is pending, we execute it here */                           // 0.0
/*92  */     while (!cpu_handle_exception(cpu, &ret)) {                                     // 0.0
/*94  */         TranslationBlock *last_tb = NULL;                                          // 0.0
/*96  */         int tb_exit = 0;                                                           // 0.0
/*100 */         while (!cpu_handle_interrupt(cpu, &last_tb)) {                             // 0.0
/*102 */             TranslationBlock *tb = tb_find(cpu, last_tb, tb_exit);                 // 0.0
/*104 */             cpu_loop_exec_tb(cpu, tb, &last_tb, &tb_exit, &sc);                    // 0.0
/*106 */             /* Try to align the host and virtual clocks                            // 0.0
/*108 */                if the guest is in advance */                                       // 0.0
/*110 */             align_clocks(&sc, cpu);                                                // 0.0
/*112 */         }                                                                          // 0.0
/*114 */     }                                                                              // 0.0
/*118 */     cc->cpu_exec_exit(cpu);                                                        // 0.0
/*120 */     rcu_read_unlock();                                                             // 0.0
/*124 */     /* fail safe : never use current_cpu outside cpu_exec() */                     // 0.0
/*126 */     current_cpu = NULL;                                                            // 0.0
/*130 */     return ret;                                                                    // 0.0
/*132 */ }                                                                                  // 0.0
