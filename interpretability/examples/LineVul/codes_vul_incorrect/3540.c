// commit message qemu@0b1bcb00fb (target=1, prob=0.22350675, correct=False): MIPS signal handling fixes.
/*0   */ void cpu_loop(CPUMIPSState *env)                                                // (17) 0.02346
/*2   */ {                                                                               // (22) 0.001954
/*4   */     target_siginfo_t info;                                                      // (18) 0.02344
/*6   */     int trapnr, ret;                                                            // (20) 0.01758
/*8   */     unsigned int syscall_num;                                                   // (19) 0.02148
/*12  */     for(;;) {                                                                   // (21) 0.01563
/*14  */         trapnr = cpu_mips_exec(env);                                            // (13) 0.03711
/*16  */         switch(trapnr) {                                                        // (16) 0.02539
/*18  */         case EXCP_SYSCALL:                                                      // (14) 0.0293
/*20  */             syscall_num = env->active_tc.gpr[2] - 4000;                         // (3) 0.06055
/*22  */             env->active_tc.PC += 4;                                             // (11) 0.04102
/*24  */             if (syscall_num >= sizeof(mips_syscall_args)) {                     // (6) 0.05664
/*26  */                 ret = -ENOSYS;                                                  // (10) 0.04297
/*28  */             } else {                                                            // (15) 0.02734
/*30  */                 int nb_args;                                                    // (12) 0.04101
/*32  */                 abi_ulong sp_reg;                                               // (8) 0.04687
/*34  */                 abi_ulong arg5 = 0, arg6 = 0, arg7 = 0, arg8 = 0;               // (0) 0.07812
/*38  */                 nb_args = mips_syscall_args[syscall_num];                       // (2) 0.06445
/*40  */                 sp_reg = env->active_tc.gpr[29];                                // (4) 0.05859
/*42  */                 switch (nb_args) {                                              // (9) 0.04297
/*44  */                 /* these arguments are taken from the stack */                  // (7) 0.04687
/*46  */                 /* FIXME - what to do if get_user() fails? */                   // (5) 0.05859
/*48  */                 case 8: get_user_ual(arg8, sp_reg + 28);                        // (1) 0.06445
/*50  */                 case 7: get_user_ual(arg7, sp_reg + 24);                        // 0.0
/*52  */                 case 6: get_user_ual(arg6, sp_reg + 20);                        // 0.0
/*54  */                 case 5: get_user_ual(arg5, sp_reg + 16);                        // 0.0
/*56  */                 default:                                                        // 0.0
/*60  */                 ret = do_syscall(env, env->active_tc.gpr[2],                    // 0.0
/*62  */                                  env->active_tc.gpr[4],                         // 0.0
/*64  */                                  env->active_tc.gpr[5],                         // 0.0
/*66  */                                  env->active_tc.gpr[6],                         // 0.0
/*68  */                                  env->active_tc.gpr[7],                         // 0.0
/*70  */                                  arg5, arg6/*, arg7, arg8*/);                   // 0.0
/*78  */             if ((unsigned int)ret >= (unsigned int)(-1133)) {                   // 0.0
/*80  */                 env->active_tc.gpr[7] = 1; /* error flag */                     // 0.0
/*82  */                 ret = -ret;                                                     // 0.0
/*84  */             } else {                                                            // 0.0
/*86  */                 env->active_tc.gpr[7] = 0; /* error flag */                     // 0.0
/*89  */             env->active_tc.gpr[2] = ret;                                        // 0.0
/*92  */         case EXCP_TLBL:                                                         // 0.0
/*94  */         case EXCP_TLBS:                                                         // 0.0
/*96  */             info.si_signo = TARGET_SIGSEGV;                                     // 0.0
/*98  */             info.si_errno = 0;                                                  // 0.0
/*100 */             /* XXX: check env->error_code */                                    // 0.0
/*102 */             info.si_code = TARGET_SEGV_MAPERR;                                  // 0.0
/*104 */             info._sifields._sigfault._addr = env->CP0_BadVAddr;                 // 0.0
/*106 */             queue_signal(env, info.si_signo, &info);                            // 0.0
/*109 */         case EXCP_CpU:                                                          // 0.0
/*111 */         case EXCP_RI:                                                           // 0.0
/*113 */             info.si_signo = TARGET_SIGILL;                                      // 0.0
/*115 */             info.si_errno = 0;                                                  // 0.0
/*117 */             info.si_code = 0;                                                   // 0.0
/*119 */             queue_signal(env, info.si_signo, &info);                            // 0.0
/*122 */         case EXCP_INTERRUPT:                                                    // 0.0
/*124 */             /* just indicate that signals should be handled asap */             // 0.0
/*127 */         case EXCP_DEBUG:                                                        // 0.0
/*129 */             {                                                                   // 0.0
/*131 */                 int sig;                                                        // 0.0
/*135 */                 sig = gdb_handlesig (env, TARGET_SIGTRAP);                      // 0.0
/*137 */                 if (sig)                                                        // 0.0
/*139 */                   {                                                             // 0.0
/*141 */                     info.si_signo = sig;                                        // 0.0
/*143 */                     info.si_errno = 0;                                          // 0.0
/*145 */                     info.si_code = TARGET_TRAP_BRKPT;                           // 0.0
/*147 */                     queue_signal(env, info.si_signo, &info);                    // 0.0
/*152 */         default:                                                                // 0.0
/*154 */             //        error:                                                    // 0.0
/*156 */             fprintf(stderr, "qemu: unhandled CPU exception 0x%x - aborting\n",  // 0.0
/*158 */                     trapnr);                                                    // 0.0
/*160 */             cpu_dump_state(env, stderr, fprintf, 0);                            // 0.0
/*162 */             abort();                                                            // 0.0
/*165 */         process_pending_signals(env);                                           // 0.0
