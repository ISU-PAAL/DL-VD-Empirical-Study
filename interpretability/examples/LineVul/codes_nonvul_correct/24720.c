// commit message qemu@edf779ffcc (target=0, prob=0.48953432, correct=True): use kernel like macros for user access (will be useful someday to have a better error checking
/*0   */ static void setup_frame(int sig, struct emulated_sigaction *ka,       // (9) 0.03711
/*2   */ 			target_sigset_t *set, CPUX86State *env)                            // (7) 0.03906
/*4   */ {                                                                     // (32) 0.001953
/*6   */ 	struct sigframe *frame;                                              // (23) 0.01367
/*8   */ 	int err = 0;                                                         // (24) 0.01172
/*12  */ 	frame = get_sigframe(ka, env, sizeof(*frame));                       // (10) 0.0332
/*16  */ #if 0                                                                 // (29) 0.005859
/*18  */ 	if (!access_ok(VERIFY_WRITE, frame, sizeof(*frame)))                 // (8) 0.03906
/*20  */ 		goto give_sigsegv;                                                  // (18) 0.02344
/*22  */ #endif                                                                // (30) 0.003906
/*24  */ 	err |= __put_user((/*current->exec_domain                            // (16) 0.0293
/*26  */ 		           && current->exec_domain->signal_invmap                   // (4) 0.04687
/*28  */ 		           && sig < 32                                              // (15) 0.03125
/*30  */ 		           ? current->exec_domain->signal_invmap[sig]               // (0) 0.05469
/*32  */ 		           : */ sig),                                               // (14) 0.03125
/*34  */ 		          &frame->sig);                                             // (12) 0.0332
/*36  */ 	if (err)                                                             // (25) 0.009766
/*38  */ 		goto give_sigsegv;                                                  // (19) 0.02344
/*42  */ 	setup_sigcontext(&frame->sc, &frame->fpstate, env, set->sig[0]);     // (1) 0.05078
/*44  */ 	if (err)                                                             // (26) 0.009766
/*46  */ 		goto give_sigsegv;                                                  // (20) 0.02344
/*50  */ 	if (TARGET_NSIG_WORDS > 1) {                                         // (17) 0.0293
/*52  */ 		err |= __copy_to_user(frame->extramask, &set->sig[1],               // (2) 0.05078
/*54  */ 				      sizeof(frame->extramask));                                  // (13) 0.0332
/*56  */ 	}                                                                    // (31) 0.003906
/*58  */ 	if (err)                                                             // (27) 0.009766
/*60  */ 		goto give_sigsegv;                                                  // (21) 0.02344
/*64  */ 	/* Set up to return from userspace.  If provided, use a stub         // (11) 0.0332
/*66  */ 	   already in userspace.  */                                         // (22) 0.01953
/*68  */ 	if (ka->sa.sa_flags & TARGET_SA_RESTORER) {                          // (5) 0.04297
/*70  */ 		err |= __put_user(ka->sa.sa_restorer, &frame->pretcode);            // (3) 0.04883
/*72  */ 	} else {                                                             // (28) 0.007812
/*74  */ 		err |= __put_user(frame->retcode, &frame->pretcode);                // (6) 0.04102
/*76  */ 		/* This is popl %eax ; movl $,%eax ; int $0x80 */                   // 0.0
/*78  */ 		err |= __put_user(0xb858, (short *)(frame->retcode+0));             // 0.0
/*80  */ 		err |= __put_user(TARGET_NR_sigreturn, (int *)(frame->retcode+2));  // 0.0
/*82  */ 		err |= __put_user(0x80cd, (short *)(frame->retcode+6));             // 0.0
/*84  */ 	}                                                                    // 0.0
/*88  */ 	if (err)                                                             // 0.0
/*90  */ 		goto give_sigsegv;                                                  // 0.0
/*94  */ 	/* Set up registers for signal handler */                            // 0.0
/*96  */ 	env->regs[R_ESP] = (unsigned long) frame;                            // 0.0
/*98  */ 	env->eip = (unsigned long) ka->sa._sa_handler;                       // 0.0
/*102 */         cpu_x86_load_seg(env, R_DS, __USER_DS);                       // 0.0
/*104 */         cpu_x86_load_seg(env, R_ES, __USER_DS);                       // 0.0
/*106 */         cpu_x86_load_seg(env, R_SS, __USER_DS);                       // 0.0
/*108 */         cpu_x86_load_seg(env, R_CS, __USER_CS);                       // 0.0
/*110 */ 	env->eflags &= ~TF_MASK;                                             // 0.0
/*114 */ 	return;                                                              // 0.0
/*118 */ give_sigsegv:                                                         // 0.0
/*120 */ 	if (sig == TARGET_SIGSEGV)                                           // 0.0
/*122 */ 		ka->sa._sa_handler = TARGET_SIG_DFL;                                // 0.0
/*124 */ 	force_sig(TARGET_SIGSEGV /* , current */);                           // 0.0
/*126 */ }                                                                     // 0.0
