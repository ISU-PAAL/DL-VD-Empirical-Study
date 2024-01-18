// commit message qemu@016d2e1dfa (target=1, prob=0.42308044, correct=False): signal/all: remove return value from restore_sigcontext
/*0  */ long do_sigreturn(CPUSH4State *regs)                              // (11) 0.0324
/*2  */ {                                                                 // (30) 0.00216
/*4  */     struct target_sigframe *frame;                                // (14) 0.02592
/*6  */     abi_ulong frame_addr;                                         // (15) 0.02592
/*8  */     sigset_t blocked;                                             // (19) 0.01944
/*10 */     target_sigset_t target_set;                                   // (13) 0.03024
/*12 */     target_ulong r0;                                              // (18) 0.0216
/*14 */     int i;                                                        // (25) 0.01296
/*16 */     int err = 0;                                                  // (22) 0.01728
/*20 */ #if defined(DEBUG_SIGNAL)                                         // (20) 0.01944
/*22 */     fprintf(stderr, "do_sigreturn\n");                            // (7) 0.04104
/*24 */ #endif                                                            // (29) 0.00432
/*26 */     frame_addr = regs->gregs[15];                                 // (12) 0.0324
/*28 */     if (!lock_user_struct(VERIFY_READ, frame, frame_addr, 1))     // (1) 0.054
/*30 */    	goto badframe;                                                // (21) 0.01944
/*34 */     __get_user(target_set.sig[0], &frame->sc.oldmask);            // (2) 0.054
/*36 */     for(i = 1; i < TARGET_NSIG_WORDS; i++) {                      // (5) 0.04968
/*38 */         __get_user(target_set.sig[i], &frame->extramask[i - 1]);  // (0) 0.06911
/*40 */     }                                                             // (27) 0.008639
/*44 */     if (err)                                                      // (23) 0.01512
/*46 */         goto badframe;                                            // (16) 0.02376
/*50 */     target_to_host_sigset_internal(&blocked, &target_set);        // (6) 0.04968
/*52 */     do_sigprocmask(SIG_SETMASK, &blocked, NULL);                  // (3) 0.05184
/*56 */     if (restore_sigcontext(regs, &frame->sc, &r0))                // (4) 0.05184
/*58 */         goto badframe;                                            // (17) 0.02376
/*62 */     unlock_user_struct(frame, frame_addr, 0);                     // (8) 0.03672
/*64 */     return r0;                                                    // (24) 0.01512
/*68 */ badframe:                                                         // (28) 0.006479
/*70 */     unlock_user_struct(frame, frame_addr, 0);                     // (9) 0.03672
/*72 */     force_sig(TARGET_SIGSEGV);                                    // (10) 0.03456
/*74 */     return 0;                                                     // (26) 0.01296
/*76 */ }                                                                 // (31) 0.00216
