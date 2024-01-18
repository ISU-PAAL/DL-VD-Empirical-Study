// commit message qemu@edf779ffcc (target=0, prob=0.39186028, correct=True): use kernel like macros for user access (will be useful someday to have a better error checking
/*0   */ static void setup_rt_frame(int sig, struct emulated_sigaction *ka,              // (7) 0.04297
/*2   */                            target_siginfo_t *info,                              // (0) 0.07031
/*4   */ 			   target_sigset_t *set, CPUX86State *env)                                   // (6) 0.04297
/*6   */ {                                                                               // (27) 0.001953
/*8   */ 	struct rt_sigframe *frame;                                                     // (19) 0.02148
/*10  */ 	int err = 0;                                                                   // (23) 0.01172
/*14  */ 	frame = get_sigframe(ka, env, sizeof(*frame));                                 // (13) 0.0332
/*18  */ #if 0                                                                           // (25) 0.005859
/*20  */ 	if (!access_ok(VERIFY_WRITE, frame, sizeof(*frame)))                           // (9) 0.03906
/*22  */ 		goto give_sigsegv;                                                            // (17) 0.02344
/*24  */ #endif                                                                          // (26) 0.003906
/*28  */ 	err |= __put_user((/*current->exec_domain                                      // (15) 0.0293
/*30  */ 		    	   && current->exec_domain->signal_invmap                                // (8) 0.04102
/*32  */ 		    	   && sig < 32                                                           // (16) 0.02539
/*34  */ 		    	   ? current->exec_domain->signal_invmap[sig]                            // (2) 0.04883
/*36  */ 			   : */sig),                                                                 // (20) 0.01953
/*38  */ 			  &frame->sig);                                                              // (21) 0.01953
/*40  */ 	err |= __put_user((target_ulong)&frame->info, &frame->pinfo);                  // (3) 0.04883
/*42  */ 	err |= __put_user((target_ulong)&frame->uc, &frame->puc);                      // (4) 0.04883
/*44  */ 	err |= copy_siginfo_to_user(&frame->info, info);                               // (10) 0.03906
/*46  */ 	if (err)                                                                       // (24) 0.009766
/*48  */ 		goto give_sigsegv;                                                            // (18) 0.02344
/*52  */ 	/* Create the ucontext.  */                                                    // (22) 0.01758
/*54  */ 	err |= __put_user(0, &frame->uc.uc_flags);                                     // (11) 0.03906
/*56  */ 	err |= __put_user(0, &frame->uc.uc_link);                                      // (12) 0.03906
/*58  */ 	err |= __put_user(/*current->sas_ss_sp*/ 0, &frame->uc.uc_stack.ss_sp);        // (1) 0.06641
/*60  */ 	err |= __put_user(/* sas_ss_flags(regs->esp) */ 0,                             // (5) 0.04883
/*62  */ 			  &frame->uc.uc_stack.ss_flags);                                             // (14) 0.0332
/*64  */ 	err |= __put_user(/* current->sas_ss_size */ 0, &frame->uc.uc_stack.ss_size);  // 0.0
/*66  */ 	err |= setup_sigcontext(&frame->uc.uc_mcontext, &frame->fpstate,               // 0.0
/*68  */ 			        env, set->sig[0]);                                                   // 0.0
/*70  */ 	err |= __copy_to_user(&frame->uc.uc_sigmask, set, sizeof(*set));               // 0.0
/*72  */ 	if (err)                                                                       // 0.0
/*74  */ 		goto give_sigsegv;                                                            // 0.0
/*78  */ 	/* Set up to return from userspace.  If provided, use a stub                   // 0.0
/*80  */ 	   already in userspace.  */                                                   // 0.0
/*82  */ 	if (ka->sa.sa_flags & TARGET_SA_RESTORER) {                                    // 0.0
/*84  */ 		err |= __put_user(ka->sa.sa_restorer, &frame->pretcode);                      // 0.0
/*86  */ 	} else {                                                                       // 0.0
/*88  */ 		err |= __put_user(frame->retcode, &frame->pretcode);                          // 0.0
/*90  */ 		/* This is movl $,%eax ; int $0x80 */                                         // 0.0
/*92  */ 		err |= __put_user(0xb8, (char *)(frame->retcode+0));                          // 0.0
/*94  */ 		err |= __put_user(TARGET_NR_rt_sigreturn, (int *)(frame->retcode+1));         // 0.0
/*96  */ 		err |= __put_user(0x80cd, (short *)(frame->retcode+5));                       // 0.0
/*98  */ 	}                                                                              // 0.0
/*102 */ 	if (err)                                                                       // 0.0
/*104 */ 		goto give_sigsegv;                                                            // 0.0
/*108 */ 	/* Set up registers for signal handler */                                      // 0.0
/*110 */ 	env->regs[R_ESP] = (unsigned long) frame;                                      // 0.0
/*112 */ 	env->eip = (unsigned long) ka->sa._sa_handler;                                 // 0.0
/*116 */         cpu_x86_load_seg(env, R_DS, __USER_DS);                                 // 0.0
/*118 */         cpu_x86_load_seg(env, R_ES, __USER_DS);                                 // 0.0
/*120 */         cpu_x86_load_seg(env, R_SS, __USER_DS);                                 // 0.0
/*122 */         cpu_x86_load_seg(env, R_CS, __USER_CS);                                 // 0.0
/*124 */ 	env->eflags &= ~TF_MASK;                                                       // 0.0
/*128 */ 	return;                                                                        // 0.0
/*132 */ give_sigsegv:                                                                   // 0.0
/*134 */ 	if (sig == TARGET_SIGSEGV)                                                     // 0.0
/*136 */ 		ka->sa._sa_handler = TARGET_SIG_DFL;                                          // 0.0
/*138 */ 	force_sig(TARGET_SIGSEGV /* , current */);                                     // 0.0
/*140 */ }                                                                               // 0.0
