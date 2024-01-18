// commit message qemu@338c858c94 (target=0, prob=0.24740766, correct=True): linux-user: Support for restarting system calls for Alpha targets
/*0   */ void cpu_loop(CPUAlphaState *env)                                               // (24) 0.02161
/*2   */ {                                                                               // (28) 0.001975
/*4   */     CPUState *cs = CPU(alpha_env_get_cpu(env));                                 // (5) 0.03911
/*6   */     int trapnr;                                                                 // (27) 0.01367
/*8   */     target_siginfo_t info;                                                      // (23) 0.02348
/*10  */     abi_long sysret;                                                            // (25) 0.01954
/*14  */     while (1) {                                                                 // (26) 0.01562
/*16  */         cpu_exec_start(cs);                                                     // (15) 0.02929
/*18  */         trapnr = cpu_alpha_exec(cs);                                            // (12) 0.03515
/*20  */         cpu_exec_end(cs);                                                       // (16) 0.02929
/*24  */         /* All of the traps imply a transition through PALcode, which           // (6) 0.03905
/*26  */            implies an REI instruction has been executed.  Which means           // (3) 0.04295
/*28  */            that the intr_flag should be cleared.  */                            // (4) 0.041
/*30  */         env->intr_flag = 0;                                                     // (14) 0.03124
/*34  */         switch (trapnr) {                                                       // (19) 0.02538
/*36  */         case EXCP_RESET:                                                        // (18) 0.02733
/*38  */             fprintf(stderr, "Reset requested. Exit\n");                         // (1) 0.05271
/*40  */             exit(EXIT_FAILURE);                                                 // (7) 0.03905
/*42  */             break;                                                              // (22) 0.02538
/*44  */         case EXCP_MCHK:                                                         // (17) 0.02929
/*46  */             fprintf(stderr, "Machine check exception. Exit\n");                 // (0) 0.05271
/*48  */             exit(EXIT_FAILURE);                                                 // (8) 0.03905
/*50  */             break;                                                              // (21) 0.02538
/*52  */         case EXCP_SMP_INTERRUPT:                                                // (10) 0.0371
/*54  */         case EXCP_CLK_INTERRUPT:                                                // (11) 0.0371
/*56  */         case EXCP_DEV_INTERRUPT:                                                // (13) 0.03514
/*58  */             fprintf(stderr, "External interrupt. Exit\n");                      // (2) 0.05076
/*60  */             exit(EXIT_FAILURE);                                                 // (9) 0.03905
/*62  */             break;                                                              // (20) 0.02538
/*64  */         case EXCP_MMFAULT:                                                      // 0.0
/*66  */             env->lock_addr = -1;                                                // 0.0
/*68  */             info.si_signo = TARGET_SIGSEGV;                                     // 0.0
/*70  */             info.si_errno = 0;                                                  // 0.0
/*72  */             info.si_code = (page_get_flags(env->trap_arg0) & PAGE_VALID         // 0.0
/*74  */                             ? TARGET_SEGV_ACCERR : TARGET_SEGV_MAPERR);         // 0.0
/*76  */             info._sifields._sigfault._addr = env->trap_arg0;                    // 0.0
/*78  */             queue_signal(env, info.si_signo, &info);                            // 0.0
/*80  */             break;                                                              // 0.0
/*82  */         case EXCP_UNALIGN:                                                      // 0.0
/*84  */             env->lock_addr = -1;                                                // 0.0
/*86  */             info.si_signo = TARGET_SIGBUS;                                      // 0.0
/*88  */             info.si_errno = 0;                                                  // 0.0
/*90  */             info.si_code = TARGET_BUS_ADRALN;                                   // 0.0
/*92  */             info._sifields._sigfault._addr = env->trap_arg0;                    // 0.0
/*94  */             queue_signal(env, info.si_signo, &info);                            // 0.0
/*96  */             break;                                                              // 0.0
/*98  */         case EXCP_OPCDEC:                                                       // 0.0
/*100 */         do_sigill:                                                              // 0.0
/*102 */             env->lock_addr = -1;                                                // 0.0
/*104 */             info.si_signo = TARGET_SIGILL;                                      // 0.0
/*106 */             info.si_errno = 0;                                                  // 0.0
/*108 */             info.si_code = TARGET_ILL_ILLOPC;                                   // 0.0
/*110 */             info._sifields._sigfault._addr = env->pc;                           // 0.0
/*112 */             queue_signal(env, info.si_signo, &info);                            // 0.0
/*114 */             break;                                                              // 0.0
/*116 */         case EXCP_ARITH:                                                        // 0.0
/*118 */             env->lock_addr = -1;                                                // 0.0
/*120 */             info.si_signo = TARGET_SIGFPE;                                      // 0.0
/*122 */             info.si_errno = 0;                                                  // 0.0
/*124 */             info.si_code = TARGET_FPE_FLTINV;                                   // 0.0
/*126 */             info._sifields._sigfault._addr = env->pc;                           // 0.0
/*128 */             queue_signal(env, info.si_signo, &info);                            // 0.0
/*130 */             break;                                                              // 0.0
/*132 */         case EXCP_FEN:                                                          // 0.0
/*134 */             /* No-op.  Linux simply re-enables the FPU.  */                     // 0.0
/*136 */             break;                                                              // 0.0
/*138 */         case EXCP_CALL_PAL:                                                     // 0.0
/*140 */             env->lock_addr = -1;                                                // 0.0
/*142 */             switch (env->error_code) {                                          // 0.0
/*144 */             case 0x80:                                                          // 0.0
/*146 */                 /* BPT */                                                       // 0.0
/*148 */                 info.si_signo = TARGET_SIGTRAP;                                 // 0.0
/*150 */                 info.si_errno = 0;                                              // 0.0
/*152 */                 info.si_code = TARGET_TRAP_BRKPT;                               // 0.0
/*154 */                 info._sifields._sigfault._addr = env->pc;                       // 0.0
/*156 */                 queue_signal(env, info.si_signo, &info);                        // 0.0
/*158 */                 break;                                                          // 0.0
/*160 */             case 0x81:                                                          // 0.0
/*162 */                 /* BUGCHK */                                                    // 0.0
/*164 */                 info.si_signo = TARGET_SIGTRAP;                                 // 0.0
/*166 */                 info.si_errno = 0;                                              // 0.0
/*168 */                 info.si_code = 0;                                               // 0.0
/*170 */                 info._sifields._sigfault._addr = env->pc;                       // 0.0
/*172 */                 queue_signal(env, info.si_signo, &info);                        // 0.0
/*174 */                 break;                                                          // 0.0
/*176 */             case 0x83:                                                          // 0.0
/*178 */                 /* CALLSYS */                                                   // 0.0
/*180 */                 trapnr = env->ir[IR_V0];                                        // 0.0
/*182 */                 sysret = do_syscall(env, trapnr,                                // 0.0
/*184 */                                     env->ir[IR_A0], env->ir[IR_A1],             // 0.0
/*186 */                                     env->ir[IR_A2], env->ir[IR_A3],             // 0.0
/*188 */                                     env->ir[IR_A4], env->ir[IR_A5],             // 0.0
/*190 */                                     0, 0);                                      // 0.0
/*192 */                 if (trapnr == TARGET_NR_sigreturn                               // 0.0
/*194 */                     || trapnr == TARGET_NR_rt_sigreturn) {                      // 0.0
/*196 */                     break;                                                      // 0.0
/*198 */                 }                                                               // 0.0
/*200 */                 /* Syscall writes 0 to V0 to bypass error check, similar        // 0.0
/*202 */                    to how this is handled internal to Linux kernel.             // 0.0
/*204 */                    (Ab)use trapnr temporarily as boolean indicating error.  */  // 0.0
/*206 */                 trapnr = (env->ir[IR_V0] != 0 && sysret < 0);                   // 0.0
/*208 */                 env->ir[IR_V0] = (trapnr ? -sysret : sysret);                   // 0.0
/*210 */                 env->ir[IR_A3] = trapnr;                                        // 0.0
/*212 */                 break;                                                          // 0.0
/*214 */             case 0x86:                                                          // 0.0
/*216 */                 /* IMB */                                                       // 0.0
/*218 */                 /* ??? We can probably elide the code using page_unprotect      // 0.0
/*220 */                    that is checking for self-modifying code.  Instead we        // 0.0
/*222 */                    could simply call tb_flush here.  Until we work out the      // 0.0
/*224 */                    changes required to turn off the extra write protection,     // 0.0
/*226 */                    this can be a no-op.  */                                     // 0.0
/*228 */                 break;                                                          // 0.0
/*230 */             case 0x9E:                                                          // 0.0
/*232 */                 /* RDUNIQUE */                                                  // 0.0
/*234 */                 /* Handled in the translator for usermode.  */                  // 0.0
/*236 */                 abort();                                                        // 0.0
/*238 */             case 0x9F:                                                          // 0.0
/*240 */                 /* WRUNIQUE */                                                  // 0.0
/*242 */                 /* Handled in the translator for usermode.  */                  // 0.0
/*244 */                 abort();                                                        // 0.0
/*246 */             case 0xAA:                                                          // 0.0
/*248 */                 /* GENTRAP */                                                   // 0.0
/*250 */                 info.si_signo = TARGET_SIGFPE;                                  // 0.0
/*252 */                 switch (env->ir[IR_A0]) {                                       // 0.0
/*254 */                 case TARGET_GEN_INTOVF:                                         // 0.0
/*256 */                     info.si_code = TARGET_FPE_INTOVF;                           // 0.0
/*258 */                     break;                                                      // 0.0
/*260 */                 case TARGET_GEN_INTDIV:                                         // 0.0
/*262 */                     info.si_code = TARGET_FPE_INTDIV;                           // 0.0
/*264 */                     break;                                                      // 0.0
/*266 */                 case TARGET_GEN_FLTOVF:                                         // 0.0
/*268 */                     info.si_code = TARGET_FPE_FLTOVF;                           // 0.0
/*270 */                     break;                                                      // 0.0
/*272 */                 case TARGET_GEN_FLTUND:                                         // 0.0
/*274 */                     info.si_code = TARGET_FPE_FLTUND;                           // 0.0
/*276 */                     break;                                                      // 0.0
/*278 */                 case TARGET_GEN_FLTINV:                                         // 0.0
/*280 */                     info.si_code = TARGET_FPE_FLTINV;                           // 0.0
/*282 */                     break;                                                      // 0.0
/*284 */                 case TARGET_GEN_FLTINE:                                         // 0.0
/*286 */                     info.si_code = TARGET_FPE_FLTRES;                           // 0.0
/*288 */                     break;                                                      // 0.0
/*290 */                 case TARGET_GEN_ROPRAND:                                        // 0.0
/*292 */                     info.si_code = 0;                                           // 0.0
/*294 */                     break;                                                      // 0.0
/*296 */                 default:                                                        // 0.0
/*298 */                     info.si_signo = TARGET_SIGTRAP;                             // 0.0
/*300 */                     info.si_code = 0;                                           // 0.0
/*302 */                     break;                                                      // 0.0
/*304 */                 }                                                               // 0.0
/*306 */                 info.si_errno = 0;                                              // 0.0
/*308 */                 info._sifields._sigfault._addr = env->pc;                       // 0.0
/*310 */                 queue_signal(env, info.si_signo, &info);                        // 0.0
/*312 */                 break;                                                          // 0.0
/*314 */             default:                                                            // 0.0
/*316 */                 goto do_sigill;                                                 // 0.0
/*318 */             }                                                                   // 0.0
/*320 */             break;                                                              // 0.0
/*322 */         case EXCP_DEBUG:                                                        // 0.0
/*324 */             info.si_signo = gdb_handlesig(cs, TARGET_SIGTRAP);                  // 0.0
/*326 */             if (info.si_signo) {                                                // 0.0
/*328 */                 env->lock_addr = -1;                                            // 0.0
/*330 */                 info.si_errno = 0;                                              // 0.0
/*332 */                 info.si_code = TARGET_TRAP_BRKPT;                               // 0.0
/*334 */                 queue_signal(env, info.si_signo, &info);                        // 0.0
/*336 */             }                                                                   // 0.0
/*338 */             break;                                                              // 0.0
/*340 */         case EXCP_STL_C:                                                        // 0.0
/*342 */         case EXCP_STQ_C:                                                        // 0.0
/*344 */             do_store_exclusive(env, env->error_code, trapnr - EXCP_STL_C);      // 0.0
/*346 */             break;                                                              // 0.0
/*348 */         case EXCP_INTERRUPT:                                                    // 0.0
/*350 */             /* Just indicate that signals should be handled asap.  */           // 0.0
/*352 */             break;                                                              // 0.0
/*354 */         default:                                                                // 0.0
/*356 */             printf ("Unhandled trap: 0x%x\n", trapnr);                          // 0.0
/*358 */             cpu_dump_state(cs, stderr, fprintf, 0);                             // 0.0
/*360 */             exit(EXIT_FAILURE);                                                 // 0.0
/*362 */         }                                                                       // 0.0
/*364 */         process_pending_signals (env);                                          // 0.0
/*366 */     }                                                                           // 0.0
/*368 */ }                                                                               // 0.0
