// commit message qemu@edf779ffcc (target=0, prob=0.35086545, correct=True): use kernel like macros for user access (will be useful someday to have a better error checking
/*0  */ static void setup_rt_frame(int usig, struct emulated_sigaction *ka,        // (9) 0.04492
/*2  */                            target_siginfo_t *info,                         // (0) 0.07031
/*4  */ 			   target_sigset_t *set, CPUState *env)                                 // (11) 0.03906
/*6  */ {                                                                          // (26) 0.001953
/*8  */ 	struct rt_sigframe *frame = get_sigframe(ka, env, sizeof(*frame));        // (8) 0.04883
/*10 */ 	int err = 0;                                                              // (21) 0.01172
/*14 */ #if 0                                                                      // (22) 0.005859
/*16 */ 	if (!access_ok(VERIFY_WRITE, frame, sizeof (*frame)))                     // (12) 0.03906
/*18 */             return 1;                                                      // (16) 0.02734
/*20 */ #endif                                                                     // (25) 0.003906
/*22 */ 	__put_user_error(&frame->info, (target_ulong *)&frame->pinfo, err);       // (5) 0.05078
/*24 */ 	__put_user_error(&frame->uc, (target_ulong *)&frame->puc, err);           // (6) 0.05078
/*26 */ 	err |= copy_siginfo_to_user(&frame->info, info);                          // (13) 0.03906
/*30 */ 	/* Clear all the bits of the ucontext we don't use.  */                   // (14) 0.0332
/*32 */ 	err |= __clear_user(&frame->uc, offsetof(struct ucontext, uc_mcontext));  // (7) 0.05078
/*36 */ 	err |= setup_sigcontext(&frame->uc.uc_mcontext, /*&frame->fpstate,*/      // (4) 0.05273
/*38 */ 				env, set->sig[0]);                                                     // (17) 0.02539
/*40 */ 	err |= __copy_to_user(&frame->uc.uc_sigmask, set, sizeof(*set));          // (3) 0.05273
/*44 */ 	if (err == 0)                                                             // (20) 0.01367
/*46 */ 		err = setup_return(env, ka, &frame->retcode, frame, usig);               // (10) 0.04492
/*50 */ 	if (err == 0) {                                                           // (19) 0.01563
/*52 */ 		/*                                                                       // (24) 0.005859
/*54 */ 		 * For realtime signals we must also set the second and third            // (15) 0.0293
/*56 */ 		 * arguments for the signal handler.                                     // (18) 0.01758
/*58 */ 		 *   -- Peter Maydell <pmaydell@chiark.greenend.org.uk> 2000-12-06       // (1) 0.06055
/*60 */ 		 */                                                                      // (23) 0.005859
/*62 */             env->regs[1] = (target_ulong)frame->pinfo;                     // (2) 0.05859
/*64 */             env->regs[2] = (target_ulong)frame->puc;                       // 0.0
/*66 */ 	}                                                                         // 0.0
/*70 */         //	return err;                                                     // 0.0
/*72 */ }                                                                          // 0.0
