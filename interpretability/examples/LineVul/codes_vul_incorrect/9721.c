// commit message qemu@f5f601afce (target=1, prob=0.41225168, correct=False): signal/all/do_sigreturn - remove __get_user checks
/*0  */ long do_sigreturn(CPUCRISState *env)                            // (8) 0.03774
/*2  */ {                                                               // (25) 0.002695
/*4  */ 	struct target_signal_frame *frame;                             // (14) 0.02965
/*6  */ 	abi_ulong frame_addr;                                          // (15) 0.02426
/*8  */ 	target_sigset_t target_set;                                    // (13) 0.03235
/*10 */ 	sigset_t set;                                                  // (17) 0.02156
/*12 */ 	int i;                                                         // (22) 0.01078
/*16 */ 	frame_addr = env->regs[R_SP];                                  // (9) 0.03774
/*18 */ 	/* Make sure the guest isn't playing games.  */                // (12) 0.03504
/*20 */ 	if (!lock_user_struct(VERIFY_WRITE, frame, frame_addr, 1))     // (3) 0.06469
/*22 */ 		goto badframe;                                                // (19) 0.01887
/*26 */ 	/* Restore blocked signals */                                  // (21) 0.01617
/*28 */ 	if (__get_user(target_set.sig[0], &frame->sc.oldmask))         // (2) 0.06739
/*30 */ 		goto badframe;                                                // (20) 0.01887
/*32 */ 	for(i = 1; i < TARGET_NSIG_WORDS; i++) {                       // (4) 0.0566
/*34 */ 		if (__get_user(target_set.sig[i], &frame->extramask[i - 1]))  // (0) 0.08086
/*36 */ 			goto badframe;                                               // (18) 0.02156
/*38 */ 	}                                                              // (24) 0.005391
/*40 */ 	target_to_host_sigset_internal(&set, &target_set);             // (5) 0.05391
/*42 */         do_sigprocmask(SIG_SETMASK, &set, NULL);                // (1) 0.07278
/*46 */ 	restore_sigcontext(&frame->sc, env);                           // (10) 0.03774
/*48 */ 	unlock_user_struct(frame, frame_addr, 0);                      // (6) 0.04313
/*50 */ 	return env->regs[10];                                          // (16) 0.02426
/*52 */   badframe:                                                     // (23) 0.01078
/*54 */ 	unlock_user_struct(frame, frame_addr, 0);                      // (7) 0.04313
/*56 */ 	force_sig(TARGET_SIGSEGV);                                     // (11) 0.03774
/*58 */ }                                                               // (26) 0.002695
