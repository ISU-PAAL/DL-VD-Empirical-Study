// commit message qemu@e511b4d783 (target=0, prob=0.31181273, correct=True): cpu-exec: reset exception_index correctly
/*0   */ int cpu_exec(CPUArchState *env)                                                 // (23) 0.02148
/*2   */ {                                                                               // (35) 0.001953
/*4   */     CPUState *cpu = ENV_GET_CPU(env);                                           // (7) 0.0332
/*6   */     CPUClass *cc = CPU_GET_CLASS(cpu);                                          // (12) 0.03125
/*8   */ #ifdef TARGET_I386                                                              // (29) 0.01563
/*10  */     X86CPU *x86_cpu = X86_CPU(cpu);                                             // (4) 0.03711
/*12  */ #endif                                                                          // (34) 0.003906
/*14  */     int ret, interrupt_request;                                                 // (25) 0.01953
/*16  */     TranslationBlock *tb;                                                       // (26) 0.01758
/*18  */     uint8_t *tc_ptr;                                                            // (21) 0.02344
/*20  */     uintptr_t next_tb;                                                          // (22) 0.02344
/*22  */     SyncClocks sc;                                                              // (30) 0.01562
/*26  */     /* This must be volatile so it is not trashed by longjmp() */               // (2) 0.03906
/*28  */     volatile bool have_tb_lock = false;                                         // (16) 0.02734
/*32  */     if (cpu->halted) {                                                          // (24) 0.02148
/*34  */         if (!cpu_has_work(cpu)) {                                               // (6) 0.03516
/*36  */             return EXCP_HALTED;                                                 // (5) 0.03711
/*38  */         }                                                                       // (31) 0.01562
/*42  */         cpu->halted = 0;                                                        // (17) 0.02734
/*44  */     }                                                                           // (33) 0.007812
/*48  */     current_cpu = cpu;                                                          // (27) 0.01758
/*52  */     /* As long as current_cpu is null, up to the assignment just above,         // (1) 0.03906
/*54  */      * requests by other threads to exit the execution loop are expected to     // (8) 0.0332
/*56  */      * be issued using the exit_request global. We must make sure that our      // (3) 0.03906
/*58  */      * evaluation of the global value is performed past the current_cpu         // (10) 0.0332
/*60  */      * value transition point, which requires a memory barrier as well as       // (9) 0.0332
/*62  */      * an instruction scheduling constraint on modern architectures.  */        // (13) 0.0293
/*64  */     smp_mb();                                                                   // (28) 0.01563
/*68  */     if (unlikely(exit_request)) {                                               // (20) 0.02539
/*70  */         cpu->exit_request = 1;                                                  // (14) 0.0293
/*72  */     }                                                                           // (32) 0.007812
/*76  */     cc->cpu_exec_enter(cpu);                                                    // (18) 0.02539
/*78  */     cpu->exception_index = -1;                                                  // (19) 0.02539
/*82  */     /* Calculate difference between guest clock and host clock.                 // (15) 0.02734
/*84  */      * This delay includes the delay of the last cycle, so                      // (11) 0.03125
/*86  */      * what we have to do is sleep until it is 0. As for the                    // (0) 0.03906
/*88  */      * advance/delay we gain here, we try to fix it next time.                  // 0.0
/*90  */      */                                                                         // 0.0
/*92  */     init_delay_params(&sc, cpu);                                                // 0.0
/*96  */     /* prepare setjmp context for exception handling */                         // 0.0
/*98  */     for(;;) {                                                                   // 0.0
/*100 */         if (sigsetjmp(cpu->jmp_env, 0) == 0) {                                  // 0.0
/*102 */             /* if an exception is pending, we execute it here */                // 0.0
/*104 */             if (cpu->exception_index >= 0) {                                    // 0.0
/*106 */                 if (cpu->exception_index >= EXCP_INTERRUPT) {                   // 0.0
/*108 */                     /* exit request from the cpu execution loop */              // 0.0
/*110 */                     ret = cpu->exception_index;                                 // 0.0
/*112 */                     if (ret == EXCP_DEBUG) {                                    // 0.0
/*114 */                         cpu_handle_debug_exception(env);                        // 0.0
/*116 */                     }                                                           // 0.0
/*118 */                     break;                                                      // 0.0
/*120 */                 } else {                                                        // 0.0
/*122 */ #if defined(CONFIG_USER_ONLY)                                                   // 0.0
/*124 */                     /* if user mode only, we simulate a fake exception          // 0.0
/*126 */                        which will be handled outside the cpu execution          // 0.0
/*128 */                        loop */                                                  // 0.0
/*130 */ #if defined(TARGET_I386)                                                        // 0.0
/*132 */                     cc->do_interrupt(cpu);                                      // 0.0
/*134 */ #endif                                                                          // 0.0
/*136 */                     ret = cpu->exception_index;                                 // 0.0
/*138 */                     break;                                                      // 0.0
/*140 */ #else                                                                           // 0.0
/*142 */                     cc->do_interrupt(cpu);                                      // 0.0
/*144 */                     cpu->exception_index = -1;                                  // 0.0
/*146 */ #endif                                                                          // 0.0
/*148 */                 }                                                               // 0.0
/*150 */             }                                                                   // 0.0
/*154 */             next_tb = 0; /* force lookup of first TB */                         // 0.0
/*156 */             for(;;) {                                                           // 0.0
/*158 */                 interrupt_request = cpu->interrupt_request;                     // 0.0
/*160 */                 if (unlikely(interrupt_request)) {                              // 0.0
/*162 */                     if (unlikely(cpu->singlestep_enabled & SSTEP_NOIRQ)) {      // 0.0
/*164 */                         /* Mask out external interrupts for this step. */       // 0.0
/*166 */                         interrupt_request &= ~CPU_INTERRUPT_SSTEP_MASK;         // 0.0
/*168 */                     }                                                           // 0.0
/*170 */                     if (interrupt_request & CPU_INTERRUPT_DEBUG) {              // 0.0
/*172 */                         cpu->interrupt_request &= ~CPU_INTERRUPT_DEBUG;         // 0.0
/*174 */                         cpu->exception_index = EXCP_DEBUG;                      // 0.0
/*176 */                         cpu_loop_exit(cpu);                                     // 0.0
/*178 */                     }                                                           // 0.0
/*180 */                     if (interrupt_request & CPU_INTERRUPT_HALT) {               // 0.0
/*182 */                         cpu->interrupt_request &= ~CPU_INTERRUPT_HALT;          // 0.0
/*184 */                         cpu->halted = 1;                                        // 0.0
/*186 */                         cpu->exception_index = EXCP_HLT;                        // 0.0
/*188 */                         cpu_loop_exit(cpu);                                     // 0.0
/*190 */                     }                                                           // 0.0
/*192 */ #if defined(TARGET_I386)                                                        // 0.0
/*194 */                     if (interrupt_request & CPU_INTERRUPT_INIT) {               // 0.0
/*196 */                         cpu_svm_check_intercept_param(env, SVM_EXIT_INIT, 0);   // 0.0
/*198 */                         do_cpu_init(x86_cpu);                                   // 0.0
/*200 */                         cpu->exception_index = EXCP_HALTED;                     // 0.0
/*202 */                         cpu_loop_exit(cpu);                                     // 0.0
/*204 */                     }                                                           // 0.0
/*206 */ #else                                                                           // 0.0
/*208 */                     if (interrupt_request & CPU_INTERRUPT_RESET) {              // 0.0
/*210 */                         cpu_reset(cpu);                                         // 0.0
/*212 */                     }                                                           // 0.0
/*214 */ #endif                                                                          // 0.0
/*216 */                     /* The target hook has 3 exit conditions:                   // 0.0
/*218 */                        False when the interrupt isn't processed,                // 0.0
/*220 */                        True when it is, and we should restart on a new TB,      // 0.0
/*222 */                        and via longjmp via cpu_loop_exit.  */                   // 0.0
/*224 */                     if (cc->cpu_exec_interrupt(cpu, interrupt_request)) {       // 0.0
/*226 */                         next_tb = 0;                                            // 0.0
/*228 */                     }                                                           // 0.0
/*230 */                     /* Don't use the cached interrupt_request value,            // 0.0
/*232 */                        do_interrupt may have updated the EXITTB flag. */        // 0.0
/*234 */                     if (cpu->interrupt_request & CPU_INTERRUPT_EXITTB) {        // 0.0
/*236 */                         cpu->interrupt_request &= ~CPU_INTERRUPT_EXITTB;        // 0.0
/*238 */                         /* ensure that no TB jump will be modified as           // 0.0
/*240 */                            the program flow was changed */                      // 0.0
/*242 */                         next_tb = 0;                                            // 0.0
/*244 */                     }                                                           // 0.0
/*246 */                 }                                                               // 0.0
/*248 */                 if (unlikely(cpu->exit_request)) {                              // 0.0
/*250 */                     cpu->exit_request = 0;                                      // 0.0
/*252 */                     cpu->exception_index = EXCP_INTERRUPT;                      // 0.0
/*254 */                     cpu_loop_exit(cpu);                                         // 0.0
/*256 */                 }                                                               // 0.0
/*258 */                 spin_lock(&tcg_ctx.tb_ctx.tb_lock);                             // 0.0
/*260 */                 have_tb_lock = true;                                            // 0.0
/*262 */                 tb = tb_find_fast(env);                                         // 0.0
/*264 */                 /* Note: we do it here to avoid a gcc bug on Mac OS X when      // 0.0
/*266 */                    doing it in tb_find_slow */                                  // 0.0
/*268 */                 if (tcg_ctx.tb_ctx.tb_invalidated_flag) {                       // 0.0
/*270 */                     /* as some TB could have been invalidated because           // 0.0
/*272 */                        of memory exceptions while generating the code, we       // 0.0
/*274 */                        must recompute the hash index here */                    // 0.0
/*276 */                     next_tb = 0;                                                // 0.0
/*278 */                     tcg_ctx.tb_ctx.tb_invalidated_flag = 0;                     // 0.0
/*280 */                 }                                                               // 0.0
/*282 */                 if (qemu_loglevel_mask(CPU_LOG_EXEC)) {                         // 0.0
/*284 */                     qemu_log("Trace %p [" TARGET_FMT_lx "] %s\n",               // 0.0
/*286 */                              tb->tc_ptr, tb->pc, lookup_symbol(tb->pc));        // 0.0
/*288 */                 }                                                               // 0.0
/*290 */                 /* see if we can patch the calling TB. When the TB              // 0.0
/*292 */                    spans two pages, we cannot safely do a direct                // 0.0
/*294 */                    jump. */                                                     // 0.0
/*296 */                 if (next_tb != 0 && tb->page_addr[1] == -1) {                   // 0.0
/*298 */                     tb_add_jump((TranslationBlock *)(next_tb & ~TB_EXIT_MASK),  // 0.0
/*300 */                                 next_tb & TB_EXIT_MASK, tb);                    // 0.0
/*302 */                 }                                                               // 0.0
/*304 */                 have_tb_lock = false;                                           // 0.0
/*306 */                 spin_unlock(&tcg_ctx.tb_ctx.tb_lock);                           // 0.0
/*310 */                 /* cpu_interrupt might be called while translating the          // 0.0
/*312 */                    TB, but before it is linked into a potentially               // 0.0
/*314 */                    infinite loop and becomes env->current_tb. Avoid             // 0.0
/*316 */                    starting execution if there is a pending interrupt. */       // 0.0
/*318 */                 cpu->current_tb = tb;                                           // 0.0
/*320 */                 barrier();                                                      // 0.0
/*322 */                 if (likely(!cpu->exit_request)) {                               // 0.0
/*324 */                     trace_exec_tb(tb, tb->pc);                                  // 0.0
/*326 */                     tc_ptr = tb->tc_ptr;                                        // 0.0
/*328 */                     /* execute the generated code */                            // 0.0
/*330 */                     next_tb = cpu_tb_exec(cpu, tc_ptr);                         // 0.0
/*332 */                     switch (next_tb & TB_EXIT_MASK) {                           // 0.0
/*334 */                     case TB_EXIT_REQUESTED:                                     // 0.0
/*336 */                         /* Something asked us to stop executing                 // 0.0
/*338 */                          * chained TBs; just continue round the main            // 0.0
/*340 */                          * loop. Whatever requested the exit will also          // 0.0
/*342 */                          * have set something else (eg exit_request or          // 0.0
/*344 */                          * interrupt_request) which we will handle              // 0.0
/*346 */                          * next time around the loop.                           // 0.0
/*348 */                          */                                                     // 0.0
/*350 */                         tb = (TranslationBlock *)(next_tb & ~TB_EXIT_MASK);     // 0.0
/*352 */                         next_tb = 0;                                            // 0.0
/*354 */                         break;                                                  // 0.0
/*356 */                     case TB_EXIT_ICOUNT_EXPIRED:                                // 0.0
/*358 */                     {                                                           // 0.0
/*360 */                         /* Instruction counter expired.  */                     // 0.0
/*362 */                         int insns_left;                                         // 0.0
/*364 */                         tb = (TranslationBlock *)(next_tb & ~TB_EXIT_MASK);     // 0.0
/*366 */                         insns_left = cpu->icount_decr.u32;                      // 0.0
/*368 */                         if (cpu->icount_extra && insns_left >= 0) {             // 0.0
/*370 */                             /* Refill decrementer and continue execution.  */   // 0.0
/*372 */                             cpu->icount_extra += insns_left;                    // 0.0
/*374 */                             if (cpu->icount_extra > 0xffff) {                   // 0.0
/*376 */                                 insns_left = 0xffff;                            // 0.0
/*378 */                             } else {                                            // 0.0
/*380 */                                 insns_left = cpu->icount_extra;                 // 0.0
/*382 */                             }                                                   // 0.0
/*384 */                             cpu->icount_extra -= insns_left;                    // 0.0
/*386 */                             cpu->icount_decr.u16.low = insns_left;              // 0.0
/*388 */                         } else {                                                // 0.0
/*390 */                             if (insns_left > 0) {                               // 0.0
/*392 */                                 /* Execute remaining instructions.  */          // 0.0
/*394 */                                 cpu_exec_nocache(env, insns_left, tb);          // 0.0
/*396 */                                 align_clocks(&sc, cpu);                         // 0.0
/*398 */                             }                                                   // 0.0
/*400 */                             cpu->exception_index = EXCP_INTERRUPT;              // 0.0
/*402 */                             next_tb = 0;                                        // 0.0
/*404 */                             cpu_loop_exit(cpu);                                 // 0.0
/*406 */                         }                                                       // 0.0
/*408 */                         break;                                                  // 0.0
/*410 */                     }                                                           // 0.0
/*412 */                     default:                                                    // 0.0
/*414 */                         break;                                                  // 0.0
/*416 */                     }                                                           // 0.0
/*418 */                 }                                                               // 0.0
/*420 */                 cpu->current_tb = NULL;                                         // 0.0
/*422 */                 /* Try to align the host and virtual clocks                     // 0.0
/*424 */                    if the guest is in advance */                                // 0.0
/*426 */                 align_clocks(&sc, cpu);                                         // 0.0
/*428 */                 /* reset soft MMU for next block (it can currently              // 0.0
/*430 */                    only be set by a memory fault) */                            // 0.0
/*432 */             } /* for(;;) */                                                     // 0.0
/*434 */         } else {                                                                // 0.0
/*436 */             /* Reload env after longjmp - the compiler may have smashed all     // 0.0
/*438 */              * local variables as longjmp is marked 'noreturn'. */              // 0.0
/*440 */             cpu = current_cpu;                                                  // 0.0
/*442 */             env = cpu->env_ptr;                                                 // 0.0
/*444 */             cc = CPU_GET_CLASS(cpu);                                            // 0.0
/*446 */ #ifdef TARGET_I386                                                              // 0.0
/*448 */             x86_cpu = X86_CPU(cpu);                                             // 0.0
/*450 */ #endif                                                                          // 0.0
/*452 */             if (have_tb_lock) {                                                 // 0.0
/*454 */                 spin_unlock(&tcg_ctx.tb_ctx.tb_lock);                           // 0.0
/*456 */                 have_tb_lock = false;                                           // 0.0
/*458 */             }                                                                   // 0.0
/*460 */         }                                                                       // 0.0
/*462 */     } /* for(;;) */                                                             // 0.0
/*466 */     cc->cpu_exec_exit(cpu);                                                     // 0.0
/*470 */     /* fail safe : never use current_cpu outside cpu_exec() */                  // 0.0
/*472 */     current_cpu = NULL;                                                         // 0.0
/*474 */     return ret;                                                                 // 0.0
/*476 */ }                                                                               // 0.0
