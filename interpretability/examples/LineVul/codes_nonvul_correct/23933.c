// commit message qemu@b0fd8d1868 (target=0, prob=0.44964996, correct=True): signal/all: remove return value from copy_siginfo_to_user
/*0   */ static void setup_rt_frame(int sig, struct target_sigaction *ka,              // (13) 0.03906
/*2   */                            target_siginfo_t *info,                            // (1) 0.07031
/*4   */                            target_sigset_t *set, CPUAlphaState *env)          // (0) 0.08203
/*6   */ {                                                                             // (21) 0.001953
/*8   */     abi_ulong frame_addr, r26;                                                // (17) 0.0293
/*10  */     struct target_rt_sigframe *frame;                                         // (18) 0.02734
/*12  */     int i, err = 0;                                                           // (19) 0.01953
/*16  */     frame_addr = get_sigframe(ka, env, sizeof(*frame));                       // (10) 0.04102
/*18  */     if (!lock_user_struct(VERIFY_WRITE, frame, frame_addr, 0)) {              // (7) 0.05273
/*20  */         goto give_sigsegv;                                                    // (16) 0.03125
/*22  */     }                                                                         // (20) 0.007812
/*26  */     err |= copy_siginfo_to_user(&frame->info, info);                          // (9) 0.04297
/*30  */     __put_user(0, &frame->uc.tuc_flags);                                      // (15) 0.03906
/*32  */     __put_user(0, &frame->uc.tuc_link);                                       // (14) 0.03906
/*34  */     __put_user(set->sig[0], &frame->uc.tuc_osf_sigmask);                      // (3) 0.05859
/*36  */     __put_user(target_sigaltstack_used.ss_sp,                                 // (12) 0.04102
/*38  */                &frame->uc.tuc_stack.ss_sp);                                   // (4) 0.05469
/*40  */     __put_user(sas_ss_flags(env->ir[IR_SP]),                                  // (8) 0.04492
/*42  */                &frame->uc.tuc_stack.ss_flags);                                // (5) 0.05469
/*44  */     __put_user(target_sigaltstack_used.ss_size,                               // (11) 0.04102
/*46  */                &frame->uc.tuc_stack.ss_size);                                 // (6) 0.05469
/*48  */     err |= setup_sigcontext(&frame->uc.tuc_mcontext, env, frame_addr, set);   // (2) 0.05859
/*50  */     for (i = 0; i < TARGET_NSIG_WORDS; ++i) {                                 // 0.0
/*52  */         __put_user(set->sig[i], &frame->uc.tuc_sigmask.sig[i]);               // 0.0
/*54  */     }                                                                         // 0.0
/*58  */     if (ka->sa_restorer) {                                                    // 0.0
/*60  */         r26 = ka->sa_restorer;                                                // 0.0
/*62  */     } else {                                                                  // 0.0
/*64  */         __put_user(INSN_MOV_R30_R16, &frame->retcode[0]);                     // 0.0
/*66  */         __put_user(INSN_LDI_R0 + TARGET_NR_rt_sigreturn,                      // 0.0
/*68  */                    &frame->retcode[1]);                                       // 0.0
/*70  */         __put_user(INSN_CALLSYS, &frame->retcode[2]);                         // 0.0
/*72  */         /* imb(); */                                                          // 0.0
/*74  */         r26 = frame_addr;                                                     // 0.0
/*76  */     }                                                                         // 0.0
/*80  */     if (err) {                                                                // 0.0
/*82  */     give_sigsegv:                                                             // 0.0
/*84  */        if (sig == TARGET_SIGSEGV) {                                           // 0.0
/*86  */             ka->_sa_handler = TARGET_SIG_DFL;                                 // 0.0
/*88  */         }                                                                     // 0.0
/*90  */         force_sig(TARGET_SIGSEGV);                                            // 0.0
/*92  */     }                                                                         // 0.0
/*96  */     env->ir[IR_RA] = r26;                                                     // 0.0
/*98  */     env->ir[IR_PV] = env->pc = ka->_sa_handler;                               // 0.0
/*100 */     env->ir[IR_A0] = sig;                                                     // 0.0
/*102 */     env->ir[IR_A1] = frame_addr + offsetof(struct target_rt_sigframe, info);  // 0.0
/*104 */     env->ir[IR_A2] = frame_addr + offsetof(struct target_rt_sigframe, uc);    // 0.0
/*106 */     env->ir[IR_SP] = frame_addr;                                              // 0.0
/*108 */ }                                                                             // 0.0
