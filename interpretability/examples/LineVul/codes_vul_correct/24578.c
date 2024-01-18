// commit message qemu@5f9099d9ce (target=1, prob=0.99914753, correct=True): ARM: linux-user: Restore VFP state from ucontext on sigreturn
/*0  */ static int do_sigframe_return_v2(CPUState *env, target_ulong frame_addr,                                                       // (3) 0.08638
/*1  */                                  struct target_ucontext_v2 *uc)                                                                // (1) 0.1429
/*2  */ {                                                                                                                              // (14) 0.003322
/*3  */     sigset_t host_set;                                                                                                         // (10) 0.03654
/*4  */     abi_ulong *regspace;                                                                                                       // (9) 0.03987
/*5  */     target_to_host_sigset(&host_set, &uc->tuc_sigmask);                                                                        // (2) 0.0897
/*6  */     sigprocmask(SIG_SETMASK, &host_set, NULL);                                                                                 // (6) 0.07309
/*7  */     if (restore_sigcontext(env, &uc->tuc_mcontext))                                                                            // (5) 0.07641
/*8  */     if (do_sigaltstack(frame_addr + offsetof(struct target_ucontext_v2, tuc_stack), 0, get_sp_from_cpustate(env)) == -EFAULT)  // (0) 0.1728
/*9  */ #if 0                                                                                                                          // (12) 0.009967
/*10 */     /* Send SIGTRAP if we're single-stepping */                                                                                // (8) 0.05316
/*11 */     if (ptrace_cancel_bpt(current))                                                                                            // (7) 0.05316
/*12 */             send_sig(SIGTRAP, current, 1);                                                                                     // (4) 0.08306
/*13 */ #endif                                                                                                                         // (13) 0.006645
/*14 */     return 0;                                                                                                                  // (11) 0.01993
