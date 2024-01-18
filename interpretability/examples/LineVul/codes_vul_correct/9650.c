// commit message qemu@3d3efba020 (target=1, prob=0.50085235, correct=True): linux-user: Fix race between multiple signals
/*0   */ static void handle_pending_signal(CPUArchState *cpu_env, int sig)                       // (5) 0.04102
/*2   */ {                                                                                       // (31) 0.001953
/*4   */     CPUState *cpu = ENV_GET_CPU(cpu_env);                                               // (7) 0.03711
/*6   */     abi_ulong handler;                                                                  // (21) 0.01953
/*8   */     sigset_t set, old_set;                                                              // (17) 0.02539
/*10  */     target_sigset_t target_old_set;                                                     // (12) 0.03125
/*12  */     struct target_sigaction *sa;                                                        // (18) 0.02344
/*14  */     struct sigqueue *q;                                                                 // (22) 0.01758
/*16  */     TaskState *ts = cpu->opaque;                                                        // (16) 0.02539
/*18  */     struct emulated_sigtable *k = &ts->sigtab[sig - 1];                                 // (2) 0.04883
/*22  */     trace_user_handle_signal(cpu_env, sig);                                             // (8) 0.03516
/*24  */     /* dequeue signal */                                                                // (27) 0.01562
/*26  */     q = k->first;                                                                       // (23) 0.01758
/*28  */     k->first = q->next;                                                                 // (19) 0.02148
/*30  */     if (!k->first)                                                                      // (24) 0.01758
/*32  */         k->pending = 0;                                                                 // (15) 0.02734
/*36  */     sig = gdb_handlesig(cpu, sig);                                                      // (13) 0.03125
/*38  */     if (!sig) {                                                                         // (26) 0.01758
/*40  */         sa = NULL;                                                                      // (20) 0.02148
/*42  */         handler = TARGET_SIG_IGN;                                                       // (10) 0.0332
/*44  */     } else {                                                                            // (28) 0.01172
/*46  */         sa = &sigact_table[sig - 1];                                                    // (6) 0.04102
/*48  */         handler = sa->_sa_handler;                                                      // (14) 0.03125
/*50  */     }                                                                                   // (29) 0.007812
/*54  */     if (ts->sigsegv_blocked && sig == TARGET_SIGSEGV) {                                 // (1) 0.05273
/*56  */         /* Guest has blocked SIGSEGV but we got one anyway. Assume this                 // (4) 0.04492
/*58  */          * is a forced SIGSEGV (ie one the kernel handles via force_sig_info            // (0) 0.05469
/*60  */          * because it got a real MMU fault), and treat as if default handler.           // (3) 0.04883
/*62  */          */                                                                             // (25) 0.01758
/*64  */         handler = TARGET_SIG_DFL;                                                       // (9) 0.03516
/*66  */     }                                                                                   // (30) 0.007812
/*70  */     if (handler == TARGET_SIG_DFL) {                                                    // (11) 0.0332
/*72  */         /* default handler : ignore some signal. The other are job control or fatal */  // 0.0
/*74  */         if (sig == TARGET_SIGTSTP || sig == TARGET_SIGTTIN || sig == TARGET_SIGTTOU) {  // 0.0
/*76  */             kill(getpid(),SIGSTOP);                                                     // 0.0
/*78  */         } else if (sig != TARGET_SIGCHLD &&                                             // 0.0
/*80  */                    sig != TARGET_SIGURG &&                                              // 0.0
/*82  */                    sig != TARGET_SIGWINCH &&                                            // 0.0
/*84  */                    sig != TARGET_SIGCONT) {                                             // 0.0
/*86  */             force_sig(sig);                                                             // 0.0
/*88  */         }                                                                               // 0.0
/*90  */     } else if (handler == TARGET_SIG_IGN) {                                             // 0.0
/*92  */         /* ignore sig */                                                                // 0.0
/*94  */     } else if (handler == TARGET_SIG_ERR) {                                             // 0.0
/*96  */         force_sig(sig);                                                                 // 0.0
/*98  */     } else {                                                                            // 0.0
/*100 */         /* compute the blocked signals during the handler execution */                  // 0.0
/*102 */         target_to_host_sigset(&set, &sa->sa_mask);                                      // 0.0
/*104 */         /* SA_NODEFER indicates that the current signal should not be                   // 0.0
/*106 */            blocked during the handler */                                                // 0.0
/*108 */         if (!(sa->sa_flags & TARGET_SA_NODEFER))                                        // 0.0
/*110 */             sigaddset(&set, target_to_host_signal(sig));                                // 0.0
/*114 */         /* block signals in the handler using Linux */                                  // 0.0
/*116 */         do_sigprocmask(SIG_BLOCK, &set, &old_set);                                      // 0.0
/*118 */         /* save the previous blocked signal state to restore it at the                  // 0.0
/*120 */            end of the signal execution (see do_sigreturn) */                            // 0.0
/*122 */         host_to_target_sigset_internal(&target_old_set, &old_set);                      // 0.0
/*126 */         /* if the CPU is in VM86 mode, we restore the 32 bit values */                  // 0.0
/*128 */ #if defined(TARGET_I386) && !defined(TARGET_X86_64)                                     // 0.0
/*130 */         {                                                                               // 0.0
/*132 */             CPUX86State *env = cpu_env;                                                 // 0.0
/*134 */             if (env->eflags & VM_MASK)                                                  // 0.0
/*136 */                 save_v86_state(env);                                                    // 0.0
/*138 */         }                                                                               // 0.0
/*140 */ #endif                                                                                  // 0.0
/*142 */         /* prepare the stack frame of the virtual CPU */                                // 0.0
/*144 */ #if defined(TARGET_ABI_MIPSN32) || defined(TARGET_ABI_MIPSN64) \                        // 0.0
/*146 */     || defined(TARGET_OPENRISC) || defined(TARGET_TILEGX)                               // 0.0
/*148 */         /* These targets do not have traditional signals.  */                           // 0.0
/*150 */         setup_rt_frame(sig, sa, &q->info, &target_old_set, cpu_env);                    // 0.0
/*152 */ #else                                                                                   // 0.0
/*154 */         if (sa->sa_flags & TARGET_SA_SIGINFO)                                           // 0.0
/*156 */             setup_rt_frame(sig, sa, &q->info, &target_old_set, cpu_env);                // 0.0
/*158 */         else                                                                            // 0.0
/*160 */             setup_frame(sig, sa, &target_old_set, cpu_env);                             // 0.0
/*162 */ #endif                                                                                  // 0.0
/*164 */         if (sa->sa_flags & TARGET_SA_RESETHAND) {                                       // 0.0
/*166 */             sa->_sa_handler = TARGET_SIG_DFL;                                           // 0.0
/*168 */         }                                                                               // 0.0
/*170 */     }                                                                                   // 0.0
/*172 */     if (q != &k->info)                                                                  // 0.0
/*174 */         free_sigqueue(cpu_env, q);                                                      // 0.0
/*176 */ }                                                                                       // 0.0
