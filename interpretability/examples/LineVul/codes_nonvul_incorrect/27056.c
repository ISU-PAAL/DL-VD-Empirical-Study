// commit message qemu@6049f4f831 (target=0, prob=0.52095205, correct=False): alpha-linux-user: Implement signals.
/*0    */ abi_long do_syscall(void *cpu_env, int num, abi_long arg1,                                                                                                // (3) 0.04688
/*2    */                     abi_long arg2, abi_long arg3, abi_long arg4,                                                                                          // (0) 0.07812
/*4    */                     abi_long arg5, abi_long arg6)                                                                                                         // (1) 0.06445
/*6    */ {                                                                                                                                                         // (29) 0.001953
/*8    */     abi_long ret;                                                                                                                                         // (23) 0.01758
/*10   */     struct stat st;                                                                                                                                       // (26) 0.01367
/*12   */     struct statfs stfs;                                                                                                                                   // (22) 0.01758
/*14   */     void *p;                                                                                                                                              // (25) 0.01367
/*18   */ #ifdef DEBUG                                                                                                                                              // (27) 0.007813
/*20   */     gemu_log("syscall %d", num);                                                                                                                          // (12) 0.0293
/*22   */ #endif                                                                                                                                                    // (28) 0.003906
/*24   */     if(do_strace)                                                                                                                                         // (21) 0.01953
/*26   */         print_syscall(num, arg1, arg2, arg3, arg4, arg5, arg6);                                                                                           // (2) 0.0625
/*30   */     switch(num) {                                                                                                                                         // (24) 0.01562
/*32   */     case TARGET_NR_exit:                                                                                                                                  // (19) 0.02148
/*34   */ #ifdef CONFIG_USE_NPTL                                                                                                                                    // (20) 0.01953
/*36   */       /* In old applications this may be used to implement _exit(2).                                                                                      // (7) 0.03906
/*38   */          However in threaded applictions it is used for thread termination,                                                                               // (8) 0.03906
/*40   */          and _exit_group is used for application termination.                                                                                             // (9) 0.03711
/*42   */          Do thread termination if we have more then one thread.  */                                                                                       // (6) 0.04102
/*44   */       /* FIXME: This probably breaks if a signal arrives.  We should probably                                                                             // (5) 0.04102
/*46   */          be disabling signals.  */                                                                                                                        // (17) 0.02734
/*48   */       if (first_cpu->next_cpu) {                                                                                                                          // (11) 0.03125
/*50   */           TaskState *ts;                                                                                                                                  // (16) 0.02734
/*52   */           CPUState **lastp;                                                                                                                               // (13) 0.0293
/*54   */           CPUState *p;                                                                                                                                    // (18) 0.02734
/*58   */           cpu_list_lock();                                                                                                                                // (14) 0.0293
/*60   */           lastp = &first_cpu;                                                                                                                             // (10) 0.0332
/*62   */           p = first_cpu;                                                                                                                                  // (15) 0.0293
/*64   */           while (p && p != (CPUState *)cpu_env) {                                                                                                         // (4) 0.04687
/*66   */               lastp = &p->next_cpu;                                                                                                                       // 0.0
/*68   */               p = p->next_cpu;                                                                                                                            // 0.0
/*70   */           }                                                                                                                                               // 0.0
/*72   */           /* If we didn't find the CPU for this thread then something is                                                                                  // 0.0
/*74   */              horribly wrong.  */                                                                                                                          // 0.0
/*76   */           if (!p)                                                                                                                                         // 0.0
/*78   */               abort();                                                                                                                                    // 0.0
/*80   */           /* Remove the CPU from the list.  */                                                                                                            // 0.0
/*82   */           *lastp = p->next_cpu;                                                                                                                           // 0.0
/*84   */           cpu_list_unlock();                                                                                                                              // 0.0
/*86   */           ts = ((CPUState *)cpu_env)->opaque;                                                                                                             // 0.0
/*88   */           if (ts->child_tidptr) {                                                                                                                         // 0.0
/*90   */               put_user_u32(0, ts->child_tidptr);                                                                                                          // 0.0
/*92   */               sys_futex(g2h(ts->child_tidptr), FUTEX_WAKE, INT_MAX,                                                                                       // 0.0
/*94   */                         NULL, NULL, 0);                                                                                                                   // 0.0
/*96   */           }                                                                                                                                               // 0.0
/*98   */           /* TODO: Free CPU state.  */                                                                                                                    // 0.0
/*100  */           pthread_exit(NULL);                                                                                                                             // 0.0
/*102  */       }                                                                                                                                                   // 0.0
/*104  */ #endif                                                                                                                                                    // 0.0
/*106  */ #ifdef TARGET_GPROF                                                                                                                                       // 0.0
/*108  */         _mcleanup();                                                                                                                                      // 0.0
/*110  */ #endif                                                                                                                                                    // 0.0
/*112  */         gdb_exit(cpu_env, arg1);                                                                                                                          // 0.0
/*114  */         _exit(arg1);                                                                                                                                      // 0.0
/*116  */         ret = 0; /* avoid warning */                                                                                                                      // 0.0
/*118  */         break;                                                                                                                                            // 0.0
/*120  */     case TARGET_NR_read:                                                                                                                                  // 0.0
/*122  */         if (arg3 == 0)                                                                                                                                    // 0.0
/*124  */             ret = 0;                                                                                                                                      // 0.0
/*126  */         else {                                                                                                                                            // 0.0
/*128  */             if (!(p = lock_user(VERIFY_WRITE, arg2, arg3, 0)))                                                                                            // 0.0
/*130  */                 goto efault;                                                                                                                              // 0.0
/*132  */             ret = get_errno(read(arg1, p, arg3));                                                                                                         // 0.0
/*134  */             unlock_user(p, arg2, ret);                                                                                                                    // 0.0
/*136  */         }                                                                                                                                                 // 0.0
/*138  */         break;                                                                                                                                            // 0.0
/*140  */     case TARGET_NR_write:                                                                                                                                 // 0.0
/*142  */         if (!(p = lock_user(VERIFY_READ, arg2, arg3, 1)))                                                                                                 // 0.0
/*144  */             goto efault;                                                                                                                                  // 0.0
/*146  */         ret = get_errno(write(arg1, p, arg3));                                                                                                            // 0.0
/*148  */         unlock_user(p, arg2, 0);                                                                                                                          // 0.0
/*150  */         break;                                                                                                                                            // 0.0
/*152  */     case TARGET_NR_open:                                                                                                                                  // 0.0
/*154  */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*156  */             goto efault;                                                                                                                                  // 0.0
/*158  */         ret = get_errno(open(path(p),                                                                                                                     // 0.0
/*160  */                              target_to_host_bitmask(arg2, fcntl_flags_tbl),                                                                               // 0.0
/*162  */                              arg3));                                                                                                                      // 0.0
/*164  */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*166  */         break;                                                                                                                                            // 0.0
/*168  */ #if defined(TARGET_NR_openat) && defined(__NR_openat)                                                                                                     // 0.0
/*170  */     case TARGET_NR_openat:                                                                                                                                // 0.0
/*172  */         if (!(p = lock_user_string(arg2)))                                                                                                                // 0.0
/*174  */             goto efault;                                                                                                                                  // 0.0
/*176  */         ret = get_errno(sys_openat(arg1,                                                                                                                  // 0.0
/*178  */                                    path(p),                                                                                                               // 0.0
/*180  */                                    target_to_host_bitmask(arg3, fcntl_flags_tbl),                                                                         // 0.0
/*182  */                                    arg4));                                                                                                                // 0.0
/*184  */         unlock_user(p, arg2, 0);                                                                                                                          // 0.0
/*186  */         break;                                                                                                                                            // 0.0
/*188  */ #endif                                                                                                                                                    // 0.0
/*190  */     case TARGET_NR_close:                                                                                                                                 // 0.0
/*192  */         ret = get_errno(close(arg1));                                                                                                                     // 0.0
/*194  */         break;                                                                                                                                            // 0.0
/*196  */     case TARGET_NR_brk:                                                                                                                                   // 0.0
/*198  */         ret = do_brk(arg1);                                                                                                                               // 0.0
/*200  */         break;                                                                                                                                            // 0.0
/*202  */     case TARGET_NR_fork:                                                                                                                                  // 0.0
/*204  */         ret = get_errno(do_fork(cpu_env, SIGCHLD, 0, 0, 0, 0));                                                                                           // 0.0
/*206  */         break;                                                                                                                                            // 0.0
/*208  */ #ifdef TARGET_NR_waitpid                                                                                                                                  // 0.0
/*210  */     case TARGET_NR_waitpid:                                                                                                                               // 0.0
/*212  */         {                                                                                                                                                 // 0.0
/*214  */             int status;                                                                                                                                   // 0.0
/*216  */             ret = get_errno(waitpid(arg1, &status, arg3));                                                                                                // 0.0
/*218  */             if (!is_error(ret) && arg2                                                                                                                    // 0.0
/*220  */                 && put_user_s32(host_to_target_waitstatus(status), arg2))                                                                                 // 0.0
/*222  */                 goto efault;                                                                                                                              // 0.0
/*224  */         }                                                                                                                                                 // 0.0
/*226  */         break;                                                                                                                                            // 0.0
/*228  */ #endif                                                                                                                                                    // 0.0
/*230  */ #ifdef TARGET_NR_waitid                                                                                                                                   // 0.0
/*232  */     case TARGET_NR_waitid:                                                                                                                                // 0.0
/*234  */         {                                                                                                                                                 // 0.0
/*236  */             siginfo_t info;                                                                                                                               // 0.0
/*238  */             info.si_pid = 0;                                                                                                                              // 0.0
/*240  */             ret = get_errno(waitid(arg1, arg2, &info, arg4));                                                                                             // 0.0
/*242  */             if (!is_error(ret) && arg3 && info.si_pid != 0) {                                                                                             // 0.0
/*244  */                 if (!(p = lock_user(VERIFY_WRITE, arg3, sizeof(target_siginfo_t), 0)))                                                                    // 0.0
/*246  */                     goto efault;                                                                                                                          // 0.0
/*248  */                 host_to_target_siginfo(p, &info);                                                                                                         // 0.0
/*250  */                 unlock_user(p, arg3, sizeof(target_siginfo_t));                                                                                           // 0.0
/*252  */             }                                                                                                                                             // 0.0
/*254  */         }                                                                                                                                                 // 0.0
/*256  */         break;                                                                                                                                            // 0.0
/*258  */ #endif                                                                                                                                                    // 0.0
/*260  */ #ifdef TARGET_NR_creat /* not on alpha */                                                                                                                 // 0.0
/*262  */     case TARGET_NR_creat:                                                                                                                                 // 0.0
/*264  */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*266  */             goto efault;                                                                                                                                  // 0.0
/*268  */         ret = get_errno(creat(p, arg2));                                                                                                                  // 0.0
/*270  */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*272  */         break;                                                                                                                                            // 0.0
/*274  */ #endif                                                                                                                                                    // 0.0
/*276  */     case TARGET_NR_link:                                                                                                                                  // 0.0
/*278  */         {                                                                                                                                                 // 0.0
/*280  */             void * p2;                                                                                                                                    // 0.0
/*282  */             p = lock_user_string(arg1);                                                                                                                   // 0.0
/*284  */             p2 = lock_user_string(arg2);                                                                                                                  // 0.0
/*286  */             if (!p || !p2)                                                                                                                                // 0.0
/*288  */                 ret = -TARGET_EFAULT;                                                                                                                     // 0.0
/*290  */             else                                                                                                                                          // 0.0
/*292  */                 ret = get_errno(link(p, p2));                                                                                                             // 0.0
/*294  */             unlock_user(p2, arg2, 0);                                                                                                                     // 0.0
/*296  */             unlock_user(p, arg1, 0);                                                                                                                      // 0.0
/*298  */         }                                                                                                                                                 // 0.0
/*300  */         break;                                                                                                                                            // 0.0
/*302  */ #if defined(TARGET_NR_linkat) && defined(__NR_linkat)                                                                                                     // 0.0
/*304  */     case TARGET_NR_linkat:                                                                                                                                // 0.0
/*306  */         {                                                                                                                                                 // 0.0
/*308  */             void * p2 = NULL;                                                                                                                             // 0.0
/*310  */             if (!arg2 || !arg4)                                                                                                                           // 0.0
/*312  */                 goto efault;                                                                                                                              // 0.0
/*314  */             p  = lock_user_string(arg2);                                                                                                                  // 0.0
/*316  */             p2 = lock_user_string(arg4);                                                                                                                  // 0.0
/*318  */             if (!p || !p2)                                                                                                                                // 0.0
/*320  */                 ret = -TARGET_EFAULT;                                                                                                                     // 0.0
/*322  */             else                                                                                                                                          // 0.0
/*324  */                 ret = get_errno(sys_linkat(arg1, p, arg3, p2, arg5));                                                                                     // 0.0
/*326  */             unlock_user(p, arg2, 0);                                                                                                                      // 0.0
/*328  */             unlock_user(p2, arg4, 0);                                                                                                                     // 0.0
/*330  */         }                                                                                                                                                 // 0.0
/*332  */         break;                                                                                                                                            // 0.0
/*334  */ #endif                                                                                                                                                    // 0.0
/*336  */     case TARGET_NR_unlink:                                                                                                                                // 0.0
/*338  */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*340  */             goto efault;                                                                                                                                  // 0.0
/*342  */         ret = get_errno(unlink(p));                                                                                                                       // 0.0
/*344  */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*346  */         break;                                                                                                                                            // 0.0
/*348  */ #if defined(TARGET_NR_unlinkat) && defined(__NR_unlinkat)                                                                                                 // 0.0
/*350  */     case TARGET_NR_unlinkat:                                                                                                                              // 0.0
/*352  */         if (!(p = lock_user_string(arg2)))                                                                                                                // 0.0
/*354  */             goto efault;                                                                                                                                  // 0.0
/*356  */         ret = get_errno(sys_unlinkat(arg1, p, arg3));                                                                                                     // 0.0
/*358  */         unlock_user(p, arg2, 0);                                                                                                                          // 0.0
/*360  */         break;                                                                                                                                            // 0.0
/*362  */ #endif                                                                                                                                                    // 0.0
/*364  */     case TARGET_NR_execve:                                                                                                                                // 0.0
/*366  */         {                                                                                                                                                 // 0.0
/*368  */             char **argp, **envp;                                                                                                                          // 0.0
/*370  */             int argc, envc;                                                                                                                               // 0.0
/*372  */             abi_ulong gp;                                                                                                                                 // 0.0
/*374  */             abi_ulong guest_argp;                                                                                                                         // 0.0
/*376  */             abi_ulong guest_envp;                                                                                                                         // 0.0
/*378  */             abi_ulong addr;                                                                                                                               // 0.0
/*380  */             char **q;                                                                                                                                     // 0.0
/*384  */             argc = 0;                                                                                                                                     // 0.0
/*386  */             guest_argp = arg2;                                                                                                                            // 0.0
/*388  */             for (gp = guest_argp; gp; gp += sizeof(abi_ulong)) {                                                                                          // 0.0
/*390  */                 if (get_user_ual(addr, gp))                                                                                                               // 0.0
/*392  */                     goto efault;                                                                                                                          // 0.0
/*394  */                 if (!addr)                                                                                                                                // 0.0
/*396  */                     break;                                                                                                                                // 0.0
/*398  */                 argc++;                                                                                                                                   // 0.0
/*400  */             }                                                                                                                                             // 0.0
/*402  */             envc = 0;                                                                                                                                     // 0.0
/*404  */             guest_envp = arg3;                                                                                                                            // 0.0
/*406  */             for (gp = guest_envp; gp; gp += sizeof(abi_ulong)) {                                                                                          // 0.0
/*408  */                 if (get_user_ual(addr, gp))                                                                                                               // 0.0
/*410  */                     goto efault;                                                                                                                          // 0.0
/*412  */                 if (!addr)                                                                                                                                // 0.0
/*414  */                     break;                                                                                                                                // 0.0
/*416  */                 envc++;                                                                                                                                   // 0.0
/*418  */             }                                                                                                                                             // 0.0
/*422  */             argp = alloca((argc + 1) * sizeof(void *));                                                                                                   // 0.0
/*424  */             envp = alloca((envc + 1) * sizeof(void *));                                                                                                   // 0.0
/*428  */             for (gp = guest_argp, q = argp; gp;                                                                                                           // 0.0
/*430  */                   gp += sizeof(abi_ulong), q++) {                                                                                                         // 0.0
/*432  */                 if (get_user_ual(addr, gp))                                                                                                               // 0.0
/*434  */                     goto execve_efault;                                                                                                                   // 0.0
/*436  */                 if (!addr)                                                                                                                                // 0.0
/*438  */                     break;                                                                                                                                // 0.0
/*440  */                 if (!(*q = lock_user_string(addr)))                                                                                                       // 0.0
/*442  */                     goto execve_efault;                                                                                                                   // 0.0
/*444  */             }                                                                                                                                             // 0.0
/*446  */             *q = NULL;                                                                                                                                    // 0.0
/*450  */             for (gp = guest_envp, q = envp; gp;                                                                                                           // 0.0
/*452  */                   gp += sizeof(abi_ulong), q++) {                                                                                                         // 0.0
/*454  */                 if (get_user_ual(addr, gp))                                                                                                               // 0.0
/*456  */                     goto execve_efault;                                                                                                                   // 0.0
/*458  */                 if (!addr)                                                                                                                                // 0.0
/*460  */                     break;                                                                                                                                // 0.0
/*462  */                 if (!(*q = lock_user_string(addr)))                                                                                                       // 0.0
/*464  */                     goto execve_efault;                                                                                                                   // 0.0
/*466  */             }                                                                                                                                             // 0.0
/*468  */             *q = NULL;                                                                                                                                    // 0.0
/*472  */             if (!(p = lock_user_string(arg1)))                                                                                                            // 0.0
/*474  */                 goto execve_efault;                                                                                                                       // 0.0
/*476  */             ret = get_errno(execve(p, argp, envp));                                                                                                       // 0.0
/*478  */             unlock_user(p, arg1, 0);                                                                                                                      // 0.0
/*482  */             goto execve_end;                                                                                                                              // 0.0
/*486  */         execve_efault:                                                                                                                                    // 0.0
/*488  */             ret = -TARGET_EFAULT;                                                                                                                         // 0.0
/*492  */         execve_end:                                                                                                                                       // 0.0
/*494  */             for (gp = guest_argp, q = argp; *q;                                                                                                           // 0.0
/*496  */                   gp += sizeof(abi_ulong), q++) {                                                                                                         // 0.0
/*498  */                 if (get_user_ual(addr, gp)                                                                                                                // 0.0
/*500  */                     || !addr)                                                                                                                             // 0.0
/*502  */                     break;                                                                                                                                // 0.0
/*504  */                 unlock_user(*q, addr, 0);                                                                                                                 // 0.0
/*506  */             }                                                                                                                                             // 0.0
/*508  */             for (gp = guest_envp, q = envp; *q;                                                                                                           // 0.0
/*510  */                   gp += sizeof(abi_ulong), q++) {                                                                                                         // 0.0
/*512  */                 if (get_user_ual(addr, gp)                                                                                                                // 0.0
/*514  */                     || !addr)                                                                                                                             // 0.0
/*516  */                     break;                                                                                                                                // 0.0
/*518  */                 unlock_user(*q, addr, 0);                                                                                                                 // 0.0
/*520  */             }                                                                                                                                             // 0.0
/*522  */         }                                                                                                                                                 // 0.0
/*524  */         break;                                                                                                                                            // 0.0
/*526  */     case TARGET_NR_chdir:                                                                                                                                 // 0.0
/*528  */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*530  */             goto efault;                                                                                                                                  // 0.0
/*532  */         ret = get_errno(chdir(p));                                                                                                                        // 0.0
/*534  */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*536  */         break;                                                                                                                                            // 0.0
/*538  */ #ifdef TARGET_NR_time                                                                                                                                     // 0.0
/*540  */     case TARGET_NR_time:                                                                                                                                  // 0.0
/*542  */         {                                                                                                                                                 // 0.0
/*544  */             time_t host_time;                                                                                                                             // 0.0
/*546  */             ret = get_errno(time(&host_time));                                                                                                            // 0.0
/*548  */             if (!is_error(ret)                                                                                                                            // 0.0
/*550  */                 && arg1                                                                                                                                   // 0.0
/*552  */                 && put_user_sal(host_time, arg1))                                                                                                         // 0.0
/*554  */                 goto efault;                                                                                                                              // 0.0
/*556  */         }                                                                                                                                                 // 0.0
/*558  */         break;                                                                                                                                            // 0.0
/*560  */ #endif                                                                                                                                                    // 0.0
/*562  */     case TARGET_NR_mknod:                                                                                                                                 // 0.0
/*564  */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*566  */             goto efault;                                                                                                                                  // 0.0
/*568  */         ret = get_errno(mknod(p, arg2, arg3));                                                                                                            // 0.0
/*570  */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*572  */         break;                                                                                                                                            // 0.0
/*574  */ #if defined(TARGET_NR_mknodat) && defined(__NR_mknodat)                                                                                                   // 0.0
/*576  */     case TARGET_NR_mknodat:                                                                                                                               // 0.0
/*578  */         if (!(p = lock_user_string(arg2)))                                                                                                                // 0.0
/*580  */             goto efault;                                                                                                                                  // 0.0
/*582  */         ret = get_errno(sys_mknodat(arg1, p, arg3, arg4));                                                                                                // 0.0
/*584  */         unlock_user(p, arg2, 0);                                                                                                                          // 0.0
/*586  */         break;                                                                                                                                            // 0.0
/*588  */ #endif                                                                                                                                                    // 0.0
/*590  */     case TARGET_NR_chmod:                                                                                                                                 // 0.0
/*592  */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*594  */             goto efault;                                                                                                                                  // 0.0
/*596  */         ret = get_errno(chmod(p, arg2));                                                                                                                  // 0.0
/*598  */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*600  */         break;                                                                                                                                            // 0.0
/*602  */ #ifdef TARGET_NR_break                                                                                                                                    // 0.0
/*604  */     case TARGET_NR_break:                                                                                                                                 // 0.0
/*606  */         goto unimplemented;                                                                                                                               // 0.0
/*608  */ #endif                                                                                                                                                    // 0.0
/*610  */ #ifdef TARGET_NR_oldstat                                                                                                                                  // 0.0
/*612  */     case TARGET_NR_oldstat:                                                                                                                               // 0.0
/*614  */         goto unimplemented;                                                                                                                               // 0.0
/*616  */ #endif                                                                                                                                                    // 0.0
/*618  */     case TARGET_NR_lseek:                                                                                                                                 // 0.0
/*620  */         ret = get_errno(lseek(arg1, arg2, arg3));                                                                                                         // 0.0
/*622  */         break;                                                                                                                                            // 0.0
/*624  */ #ifdef TARGET_NR_getxpid                                                                                                                                  // 0.0
/*626  */     case TARGET_NR_getxpid:                                                                                                                               // 0.0
/*628  */ #else                                                                                                                                                     // 0.0
/*630  */     case TARGET_NR_getpid:                                                                                                                                // 0.0
/*632  */ #endif                                                                                                                                                    // 0.0
/*634  */         ret = get_errno(getpid());                                                                                                                        // 0.0
/*636  */         break;                                                                                                                                            // 0.0
/*638  */     case TARGET_NR_mount:                                                                                                                                 // 0.0
/*640  */ 		{                                                                                                                                                       // 0.0
/*642  */ 			/* need to look at the data field */                                                                                                                   // 0.0
/*644  */ 			void *p2, *p3;                                                                                                                                         // 0.0
/*646  */ 			p = lock_user_string(arg1);                                                                                                                            // 0.0
/*648  */ 			p2 = lock_user_string(arg2);                                                                                                                           // 0.0
/*650  */ 			p3 = lock_user_string(arg3);                                                                                                                           // 0.0
/*652  */                         if (!p || !p2 || !p3)                                                                                                             // 0.0
/*654  */                             ret = -TARGET_EFAULT;                                                                                                         // 0.0
/*656  */                         else {                                                                                                                            // 0.0
/*658  */                             /* FIXME - arg5 should be locked, but it isn't clear how to                                                                   // 0.0
/*660  */                              * do that since it's not guaranteed to be a NULL-terminated                                                                  // 0.0
/*662  */                              * string.                                                                                                                    // 0.0
/*664  */                              */                                                                                                                           // 0.0
/*666  */                             if ( ! arg5 )                                                                                                                 // 0.0
/*668  */                                 ret = get_errno(mount(p, p2, p3, (unsigned long)arg4, NULL));                                                             // 0.0
/*670  */                             else                                                                                                                          // 0.0
/*672  */                                 ret = get_errno(mount(p, p2, p3, (unsigned long)arg4, g2h(arg5)));                                                        // 0.0
/*674  */                         }                                                                                                                                 // 0.0
/*676  */                         unlock_user(p, arg1, 0);                                                                                                          // 0.0
/*678  */                         unlock_user(p2, arg2, 0);                                                                                                         // 0.0
/*680  */                         unlock_user(p3, arg3, 0);                                                                                                         // 0.0
/*682  */ 			break;                                                                                                                                                 // 0.0
/*684  */ 		}                                                                                                                                                       // 0.0
/*686  */ #ifdef TARGET_NR_umount                                                                                                                                   // 0.0
/*688  */     case TARGET_NR_umount:                                                                                                                                // 0.0
/*690  */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*692  */             goto efault;                                                                                                                                  // 0.0
/*694  */         ret = get_errno(umount(p));                                                                                                                       // 0.0
/*696  */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*698  */         break;                                                                                                                                            // 0.0
/*700  */ #endif                                                                                                                                                    // 0.0
/*702  */ #ifdef TARGET_NR_stime /* not on alpha */                                                                                                                 // 0.0
/*704  */     case TARGET_NR_stime:                                                                                                                                 // 0.0
/*706  */         {                                                                                                                                                 // 0.0
/*708  */             time_t host_time;                                                                                                                             // 0.0
/*710  */             if (get_user_sal(host_time, arg1))                                                                                                            // 0.0
/*712  */                 goto efault;                                                                                                                              // 0.0
/*714  */             ret = get_errno(stime(&host_time));                                                                                                           // 0.0
/*716  */         }                                                                                                                                                 // 0.0
/*718  */         break;                                                                                                                                            // 0.0
/*720  */ #endif                                                                                                                                                    // 0.0
/*722  */     case TARGET_NR_ptrace:                                                                                                                                // 0.0
/*724  */         goto unimplemented;                                                                                                                               // 0.0
/*726  */ #ifdef TARGET_NR_alarm /* not on alpha */                                                                                                                 // 0.0
/*728  */     case TARGET_NR_alarm:                                                                                                                                 // 0.0
/*730  */         ret = alarm(arg1);                                                                                                                                // 0.0
/*732  */         break;                                                                                                                                            // 0.0
/*734  */ #endif                                                                                                                                                    // 0.0
/*736  */ #ifdef TARGET_NR_oldfstat                                                                                                                                 // 0.0
/*738  */     case TARGET_NR_oldfstat:                                                                                                                              // 0.0
/*740  */         goto unimplemented;                                                                                                                               // 0.0
/*742  */ #endif                                                                                                                                                    // 0.0
/*744  */ #ifdef TARGET_NR_pause /* not on alpha */                                                                                                                 // 0.0
/*746  */     case TARGET_NR_pause:                                                                                                                                 // 0.0
/*748  */         ret = get_errno(pause());                                                                                                                         // 0.0
/*750  */         break;                                                                                                                                            // 0.0
/*752  */ #endif                                                                                                                                                    // 0.0
/*754  */ #ifdef TARGET_NR_utime                                                                                                                                    // 0.0
/*756  */     case TARGET_NR_utime:                                                                                                                                 // 0.0
/*758  */         {                                                                                                                                                 // 0.0
/*760  */             struct utimbuf tbuf, *host_tbuf;                                                                                                              // 0.0
/*762  */             struct target_utimbuf *target_tbuf;                                                                                                           // 0.0
/*764  */             if (arg2) {                                                                                                                                   // 0.0
/*766  */                 if (!lock_user_struct(VERIFY_READ, target_tbuf, arg2, 1))                                                                                 // 0.0
/*768  */                     goto efault;                                                                                                                          // 0.0
/*770  */                 tbuf.actime = tswapl(target_tbuf->actime);                                                                                                // 0.0
/*772  */                 tbuf.modtime = tswapl(target_tbuf->modtime);                                                                                              // 0.0
/*774  */                 unlock_user_struct(target_tbuf, arg2, 0);                                                                                                 // 0.0
/*776  */                 host_tbuf = &tbuf;                                                                                                                        // 0.0
/*778  */             } else {                                                                                                                                      // 0.0
/*780  */                 host_tbuf = NULL;                                                                                                                         // 0.0
/*782  */             }                                                                                                                                             // 0.0
/*784  */             if (!(p = lock_user_string(arg1)))                                                                                                            // 0.0
/*786  */                 goto efault;                                                                                                                              // 0.0
/*788  */             ret = get_errno(utime(p, host_tbuf));                                                                                                         // 0.0
/*790  */             unlock_user(p, arg1, 0);                                                                                                                      // 0.0
/*792  */         }                                                                                                                                                 // 0.0
/*794  */         break;                                                                                                                                            // 0.0
/*796  */ #endif                                                                                                                                                    // 0.0
/*798  */     case TARGET_NR_utimes:                                                                                                                                // 0.0
/*800  */         {                                                                                                                                                 // 0.0
/*802  */             struct timeval *tvp, tv[2];                                                                                                                   // 0.0
/*804  */             if (arg2) {                                                                                                                                   // 0.0
/*806  */                 if (copy_from_user_timeval(&tv[0], arg2)                                                                                                  // 0.0
/*808  */                     || copy_from_user_timeval(&tv[1],                                                                                                     // 0.0
/*810  */                                               arg2 + sizeof(struct target_timeval)))                                                                      // 0.0
/*812  */                     goto efault;                                                                                                                          // 0.0
/*814  */                 tvp = tv;                                                                                                                                 // 0.0
/*816  */             } else {                                                                                                                                      // 0.0
/*818  */                 tvp = NULL;                                                                                                                               // 0.0
/*820  */             }                                                                                                                                             // 0.0
/*822  */             if (!(p = lock_user_string(arg1)))                                                                                                            // 0.0
/*824  */                 goto efault;                                                                                                                              // 0.0
/*826  */             ret = get_errno(utimes(p, tvp));                                                                                                              // 0.0
/*828  */             unlock_user(p, arg1, 0);                                                                                                                      // 0.0
/*830  */         }                                                                                                                                                 // 0.0
/*832  */         break;                                                                                                                                            // 0.0
/*834  */ #if defined(TARGET_NR_futimesat) && defined(__NR_futimesat)                                                                                               // 0.0
/*836  */     case TARGET_NR_futimesat:                                                                                                                             // 0.0
/*838  */         {                                                                                                                                                 // 0.0
/*840  */             struct timeval *tvp, tv[2];                                                                                                                   // 0.0
/*842  */             if (arg3) {                                                                                                                                   // 0.0
/*844  */                 if (copy_from_user_timeval(&tv[0], arg3)                                                                                                  // 0.0
/*846  */                     || copy_from_user_timeval(&tv[1],                                                                                                     // 0.0
/*848  */                                               arg3 + sizeof(struct target_timeval)))                                                                      // 0.0
/*850  */                     goto efault;                                                                                                                          // 0.0
/*852  */                 tvp = tv;                                                                                                                                 // 0.0
/*854  */             } else {                                                                                                                                      // 0.0
/*856  */                 tvp = NULL;                                                                                                                               // 0.0
/*858  */             }                                                                                                                                             // 0.0
/*860  */             if (!(p = lock_user_string(arg2)))                                                                                                            // 0.0
/*862  */                 goto efault;                                                                                                                              // 0.0
/*864  */             ret = get_errno(sys_futimesat(arg1, path(p), tvp));                                                                                           // 0.0
/*866  */             unlock_user(p, arg2, 0);                                                                                                                      // 0.0
/*868  */         }                                                                                                                                                 // 0.0
/*870  */         break;                                                                                                                                            // 0.0
/*872  */ #endif                                                                                                                                                    // 0.0
/*874  */ #ifdef TARGET_NR_stty                                                                                                                                     // 0.0
/*876  */     case TARGET_NR_stty:                                                                                                                                  // 0.0
/*878  */         goto unimplemented;                                                                                                                               // 0.0
/*880  */ #endif                                                                                                                                                    // 0.0
/*882  */ #ifdef TARGET_NR_gtty                                                                                                                                     // 0.0
/*884  */     case TARGET_NR_gtty:                                                                                                                                  // 0.0
/*886  */         goto unimplemented;                                                                                                                               // 0.0
/*888  */ #endif                                                                                                                                                    // 0.0
/*890  */     case TARGET_NR_access:                                                                                                                                // 0.0
/*892  */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*894  */             goto efault;                                                                                                                                  // 0.0
/*896  */         ret = get_errno(access(path(p), arg2));                                                                                                           // 0.0
/*898  */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*900  */         break;                                                                                                                                            // 0.0
/*902  */ #if defined(TARGET_NR_faccessat) && defined(__NR_faccessat)                                                                                               // 0.0
/*904  */     case TARGET_NR_faccessat:                                                                                                                             // 0.0
/*906  */         if (!(p = lock_user_string(arg2)))                                                                                                                // 0.0
/*908  */             goto efault;                                                                                                                                  // 0.0
/*910  */         ret = get_errno(sys_faccessat(arg1, p, arg3));                                                                                                    // 0.0
/*912  */         unlock_user(p, arg2, 0);                                                                                                                          // 0.0
/*914  */         break;                                                                                                                                            // 0.0
/*916  */ #endif                                                                                                                                                    // 0.0
/*918  */ #ifdef TARGET_NR_nice /* not on alpha */                                                                                                                  // 0.0
/*920  */     case TARGET_NR_nice:                                                                                                                                  // 0.0
/*922  */         ret = get_errno(nice(arg1));                                                                                                                      // 0.0
/*924  */         break;                                                                                                                                            // 0.0
/*926  */ #endif                                                                                                                                                    // 0.0
/*928  */ #ifdef TARGET_NR_ftime                                                                                                                                    // 0.0
/*930  */     case TARGET_NR_ftime:                                                                                                                                 // 0.0
/*932  */         goto unimplemented;                                                                                                                               // 0.0
/*934  */ #endif                                                                                                                                                    // 0.0
/*936  */     case TARGET_NR_sync:                                                                                                                                  // 0.0
/*938  */         sync();                                                                                                                                           // 0.0
/*940  */         ret = 0;                                                                                                                                          // 0.0
/*942  */         break;                                                                                                                                            // 0.0
/*944  */     case TARGET_NR_kill:                                                                                                                                  // 0.0
/*946  */         ret = get_errno(kill(arg1, target_to_host_signal(arg2)));                                                                                         // 0.0
/*948  */         break;                                                                                                                                            // 0.0
/*950  */     case TARGET_NR_rename:                                                                                                                                // 0.0
/*952  */         {                                                                                                                                                 // 0.0
/*954  */             void *p2;                                                                                                                                     // 0.0
/*956  */             p = lock_user_string(arg1);                                                                                                                   // 0.0
/*958  */             p2 = lock_user_string(arg2);                                                                                                                  // 0.0
/*960  */             if (!p || !p2)                                                                                                                                // 0.0
/*962  */                 ret = -TARGET_EFAULT;                                                                                                                     // 0.0
/*964  */             else                                                                                                                                          // 0.0
/*966  */                 ret = get_errno(rename(p, p2));                                                                                                           // 0.0
/*968  */             unlock_user(p2, arg2, 0);                                                                                                                     // 0.0
/*970  */             unlock_user(p, arg1, 0);                                                                                                                      // 0.0
/*972  */         }                                                                                                                                                 // 0.0
/*974  */         break;                                                                                                                                            // 0.0
/*976  */ #if defined(TARGET_NR_renameat) && defined(__NR_renameat)                                                                                                 // 0.0
/*978  */     case TARGET_NR_renameat:                                                                                                                              // 0.0
/*980  */         {                                                                                                                                                 // 0.0
/*982  */             void *p2;                                                                                                                                     // 0.0
/*984  */             p  = lock_user_string(arg2);                                                                                                                  // 0.0
/*986  */             p2 = lock_user_string(arg4);                                                                                                                  // 0.0
/*988  */             if (!p || !p2)                                                                                                                                // 0.0
/*990  */                 ret = -TARGET_EFAULT;                                                                                                                     // 0.0
/*992  */             else                                                                                                                                          // 0.0
/*994  */                 ret = get_errno(sys_renameat(arg1, p, arg3, p2));                                                                                         // 0.0
/*996  */             unlock_user(p2, arg4, 0);                                                                                                                     // 0.0
/*998  */             unlock_user(p, arg2, 0);                                                                                                                      // 0.0
/*1000 */         }                                                                                                                                                 // 0.0
/*1002 */         break;                                                                                                                                            // 0.0
/*1004 */ #endif                                                                                                                                                    // 0.0
/*1006 */     case TARGET_NR_mkdir:                                                                                                                                 // 0.0
/*1008 */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*1010 */             goto efault;                                                                                                                                  // 0.0
/*1012 */         ret = get_errno(mkdir(p, arg2));                                                                                                                  // 0.0
/*1014 */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*1016 */         break;                                                                                                                                            // 0.0
/*1018 */ #if defined(TARGET_NR_mkdirat) && defined(__NR_mkdirat)                                                                                                   // 0.0
/*1020 */     case TARGET_NR_mkdirat:                                                                                                                               // 0.0
/*1022 */         if (!(p = lock_user_string(arg2)))                                                                                                                // 0.0
/*1024 */             goto efault;                                                                                                                                  // 0.0
/*1026 */         ret = get_errno(sys_mkdirat(arg1, p, arg3));                                                                                                      // 0.0
/*1028 */         unlock_user(p, arg2, 0);                                                                                                                          // 0.0
/*1030 */         break;                                                                                                                                            // 0.0
/*1032 */ #endif                                                                                                                                                    // 0.0
/*1034 */     case TARGET_NR_rmdir:                                                                                                                                 // 0.0
/*1036 */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*1038 */             goto efault;                                                                                                                                  // 0.0
/*1040 */         ret = get_errno(rmdir(p));                                                                                                                        // 0.0
/*1042 */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*1044 */         break;                                                                                                                                            // 0.0
/*1046 */     case TARGET_NR_dup:                                                                                                                                   // 0.0
/*1048 */         ret = get_errno(dup(arg1));                                                                                                                       // 0.0
/*1050 */         break;                                                                                                                                            // 0.0
/*1052 */     case TARGET_NR_pipe:                                                                                                                                  // 0.0
/*1054 */         ret = do_pipe(cpu_env, arg1, 0);                                                                                                                  // 0.0
/*1056 */         break;                                                                                                                                            // 0.0
/*1058 */ #ifdef TARGET_NR_pipe2                                                                                                                                    // 0.0
/*1060 */     case TARGET_NR_pipe2:                                                                                                                                 // 0.0
/*1062 */         ret = do_pipe(cpu_env, arg1, arg2);                                                                                                               // 0.0
/*1064 */         break;                                                                                                                                            // 0.0
/*1066 */ #endif                                                                                                                                                    // 0.0
/*1068 */     case TARGET_NR_times:                                                                                                                                 // 0.0
/*1070 */         {                                                                                                                                                 // 0.0
/*1072 */             struct target_tms *tmsp;                                                                                                                      // 0.0
/*1074 */             struct tms tms;                                                                                                                               // 0.0
/*1076 */             ret = get_errno(times(&tms));                                                                                                                 // 0.0
/*1078 */             if (arg1) {                                                                                                                                   // 0.0
/*1080 */                 tmsp = lock_user(VERIFY_WRITE, arg1, sizeof(struct target_tms), 0);                                                                       // 0.0
/*1082 */                 if (!tmsp)                                                                                                                                // 0.0
/*1084 */                     goto efault;                                                                                                                          // 0.0
/*1086 */                 tmsp->tms_utime = tswapl(host_to_target_clock_t(tms.tms_utime));                                                                          // 0.0
/*1088 */                 tmsp->tms_stime = tswapl(host_to_target_clock_t(tms.tms_stime));                                                                          // 0.0
/*1090 */                 tmsp->tms_cutime = tswapl(host_to_target_clock_t(tms.tms_cutime));                                                                        // 0.0
/*1092 */                 tmsp->tms_cstime = tswapl(host_to_target_clock_t(tms.tms_cstime));                                                                        // 0.0
/*1094 */             }                                                                                                                                             // 0.0
/*1096 */             if (!is_error(ret))                                                                                                                           // 0.0
/*1098 */                 ret = host_to_target_clock_t(ret);                                                                                                        // 0.0
/*1100 */         }                                                                                                                                                 // 0.0
/*1102 */         break;                                                                                                                                            // 0.0
/*1104 */ #ifdef TARGET_NR_prof                                                                                                                                     // 0.0
/*1106 */     case TARGET_NR_prof:                                                                                                                                  // 0.0
/*1108 */         goto unimplemented;                                                                                                                               // 0.0
/*1110 */ #endif                                                                                                                                                    // 0.0
/*1112 */ #ifdef TARGET_NR_signal                                                                                                                                   // 0.0
/*1114 */     case TARGET_NR_signal:                                                                                                                                // 0.0
/*1116 */         goto unimplemented;                                                                                                                               // 0.0
/*1118 */ #endif                                                                                                                                                    // 0.0
/*1120 */     case TARGET_NR_acct:                                                                                                                                  // 0.0
/*1122 */         if (arg1 == 0) {                                                                                                                                  // 0.0
/*1124 */             ret = get_errno(acct(NULL));                                                                                                                  // 0.0
/*1126 */         } else {                                                                                                                                          // 0.0
/*1128 */             if (!(p = lock_user_string(arg1)))                                                                                                            // 0.0
/*1130 */                 goto efault;                                                                                                                              // 0.0
/*1132 */             ret = get_errno(acct(path(p)));                                                                                                               // 0.0
/*1134 */             unlock_user(p, arg1, 0);                                                                                                                      // 0.0
/*1136 */         }                                                                                                                                                 // 0.0
/*1138 */         break;                                                                                                                                            // 0.0
/*1140 */ #ifdef TARGET_NR_umount2 /* not on alpha */                                                                                                               // 0.0
/*1142 */     case TARGET_NR_umount2:                                                                                                                               // 0.0
/*1144 */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*1146 */             goto efault;                                                                                                                                  // 0.0
/*1148 */         ret = get_errno(umount2(p, arg2));                                                                                                                // 0.0
/*1150 */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*1152 */         break;                                                                                                                                            // 0.0
/*1154 */ #endif                                                                                                                                                    // 0.0
/*1156 */ #ifdef TARGET_NR_lock                                                                                                                                     // 0.0
/*1158 */     case TARGET_NR_lock:                                                                                                                                  // 0.0
/*1160 */         goto unimplemented;                                                                                                                               // 0.0
/*1162 */ #endif                                                                                                                                                    // 0.0
/*1164 */     case TARGET_NR_ioctl:                                                                                                                                 // 0.0
/*1166 */         ret = do_ioctl(arg1, arg2, arg3);                                                                                                                 // 0.0
/*1168 */         break;                                                                                                                                            // 0.0
/*1170 */     case TARGET_NR_fcntl:                                                                                                                                 // 0.0
/*1172 */         ret = do_fcntl(arg1, arg2, arg3);                                                                                                                 // 0.0
/*1174 */         break;                                                                                                                                            // 0.0
/*1176 */ #ifdef TARGET_NR_mpx                                                                                                                                      // 0.0
/*1178 */     case TARGET_NR_mpx:                                                                                                                                   // 0.0
/*1180 */         goto unimplemented;                                                                                                                               // 0.0
/*1182 */ #endif                                                                                                                                                    // 0.0
/*1184 */     case TARGET_NR_setpgid:                                                                                                                               // 0.0
/*1186 */         ret = get_errno(setpgid(arg1, arg2));                                                                                                             // 0.0
/*1188 */         break;                                                                                                                                            // 0.0
/*1190 */ #ifdef TARGET_NR_ulimit                                                                                                                                   // 0.0
/*1192 */     case TARGET_NR_ulimit:                                                                                                                                // 0.0
/*1194 */         goto unimplemented;                                                                                                                               // 0.0
/*1196 */ #endif                                                                                                                                                    // 0.0
/*1198 */ #ifdef TARGET_NR_oldolduname                                                                                                                              // 0.0
/*1200 */     case TARGET_NR_oldolduname:                                                                                                                           // 0.0
/*1202 */         goto unimplemented;                                                                                                                               // 0.0
/*1204 */ #endif                                                                                                                                                    // 0.0
/*1206 */     case TARGET_NR_umask:                                                                                                                                 // 0.0
/*1208 */         ret = get_errno(umask(arg1));                                                                                                                     // 0.0
/*1210 */         break;                                                                                                                                            // 0.0
/*1212 */     case TARGET_NR_chroot:                                                                                                                                // 0.0
/*1214 */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*1216 */             goto efault;                                                                                                                                  // 0.0
/*1218 */         ret = get_errno(chroot(p));                                                                                                                       // 0.0
/*1220 */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*1222 */         break;                                                                                                                                            // 0.0
/*1224 */     case TARGET_NR_ustat:                                                                                                                                 // 0.0
/*1226 */         goto unimplemented;                                                                                                                               // 0.0
/*1228 */     case TARGET_NR_dup2:                                                                                                                                  // 0.0
/*1230 */         ret = get_errno(dup2(arg1, arg2));                                                                                                                // 0.0
/*1232 */         break;                                                                                                                                            // 0.0
/*1234 */ #if defined(CONFIG_DUP3) && defined(TARGET_NR_dup3)                                                                                                       // 0.0
/*1236 */     case TARGET_NR_dup3:                                                                                                                                  // 0.0
/*1238 */         ret = get_errno(dup3(arg1, arg2, arg3));                                                                                                          // 0.0
/*1240 */         break;                                                                                                                                            // 0.0
/*1242 */ #endif                                                                                                                                                    // 0.0
/*1244 */ #ifdef TARGET_NR_getppid /* not on alpha */                                                                                                               // 0.0
/*1246 */     case TARGET_NR_getppid:                                                                                                                               // 0.0
/*1248 */         ret = get_errno(getppid());                                                                                                                       // 0.0
/*1250 */         break;                                                                                                                                            // 0.0
/*1252 */ #endif                                                                                                                                                    // 0.0
/*1254 */     case TARGET_NR_getpgrp:                                                                                                                               // 0.0
/*1256 */         ret = get_errno(getpgrp());                                                                                                                       // 0.0
/*1258 */         break;                                                                                                                                            // 0.0
/*1260 */     case TARGET_NR_setsid:                                                                                                                                // 0.0
/*1262 */         ret = get_errno(setsid());                                                                                                                        // 0.0
/*1264 */         break;                                                                                                                                            // 0.0
/*1266 */ #ifdef TARGET_NR_sigaction                                                                                                                                // 0.0
/*1268 */     case TARGET_NR_sigaction:                                                                                                                             // 0.0
/*1270 */         {                                                                                                                                                 // 0.0
/*1272 */ #if !defined(TARGET_MIPS)                                                                                                                                 // 0.0
/*1274 */             struct target_old_sigaction *old_act;                                                                                                         // 0.0
/*1276 */             struct target_sigaction act, oact, *pact;                                                                                                     // 0.0
/*1278 */             if (arg2) {                                                                                                                                   // 0.0
/*1280 */                 if (!lock_user_struct(VERIFY_READ, old_act, arg2, 1))                                                                                     // 0.0
/*1282 */                     goto efault;                                                                                                                          // 0.0
/*1284 */                 act._sa_handler = old_act->_sa_handler;                                                                                                   // 0.0
/*1286 */                 target_siginitset(&act.sa_mask, old_act->sa_mask);                                                                                        // 0.0
/*1288 */                 act.sa_flags = old_act->sa_flags;                                                                                                         // 0.0
/*1290 */                 act.sa_restorer = old_act->sa_restorer;                                                                                                   // 0.0
/*1292 */                 unlock_user_struct(old_act, arg2, 0);                                                                                                     // 0.0
/*1294 */                 pact = &act;                                                                                                                              // 0.0
/*1296 */             } else {                                                                                                                                      // 0.0
/*1298 */                 pact = NULL;                                                                                                                              // 0.0
/*1300 */             }                                                                                                                                             // 0.0
/*1302 */             ret = get_errno(do_sigaction(arg1, pact, &oact));                                                                                             // 0.0
/*1304 */             if (!is_error(ret) && arg3) {                                                                                                                 // 0.0
/*1306 */                 if (!lock_user_struct(VERIFY_WRITE, old_act, arg3, 0))                                                                                    // 0.0
/*1308 */                     goto efault;                                                                                                                          // 0.0
/*1310 */                 old_act->_sa_handler = oact._sa_handler;                                                                                                  // 0.0
/*1312 */                 old_act->sa_mask = oact.sa_mask.sig[0];                                                                                                   // 0.0
/*1314 */                 old_act->sa_flags = oact.sa_flags;                                                                                                        // 0.0
/*1316 */                 old_act->sa_restorer = oact.sa_restorer;                                                                                                  // 0.0
/*1318 */                 unlock_user_struct(old_act, arg3, 1);                                                                                                     // 0.0
/*1320 */             }                                                                                                                                             // 0.0
/*1322 */ #else                                                                                                                                                     // 0.0
/*1324 */ 	    struct target_sigaction act, oact, *pact, *old_act;                                                                                                  // 0.0
/*1328 */ 	    if (arg2) {                                                                                                                                          // 0.0
/*1330 */                 if (!lock_user_struct(VERIFY_READ, old_act, arg2, 1))                                                                                     // 0.0
/*1332 */                     goto efault;                                                                                                                          // 0.0
/*1334 */ 		act._sa_handler = old_act->_sa_handler;                                                                                                                 // 0.0
/*1336 */ 		target_siginitset(&act.sa_mask, old_act->sa_mask.sig[0]);                                                                                               // 0.0
/*1338 */ 		act.sa_flags = old_act->sa_flags;                                                                                                                       // 0.0
/*1340 */ 		unlock_user_struct(old_act, arg2, 0);                                                                                                                   // 0.0
/*1342 */ 		pact = &act;                                                                                                                                            // 0.0
/*1344 */ 	    } else {                                                                                                                                             // 0.0
/*1346 */ 		pact = NULL;                                                                                                                                            // 0.0
/*1348 */ 	    }                                                                                                                                                    // 0.0
/*1352 */ 	    ret = get_errno(do_sigaction(arg1, pact, &oact));                                                                                                    // 0.0
/*1356 */ 	    if (!is_error(ret) && arg3) {                                                                                                                        // 0.0
/*1358 */                 if (!lock_user_struct(VERIFY_WRITE, old_act, arg3, 0))                                                                                    // 0.0
/*1360 */                     goto efault;                                                                                                                          // 0.0
/*1362 */ 		old_act->_sa_handler = oact._sa_handler;                                                                                                                // 0.0
/*1364 */ 		old_act->sa_flags = oact.sa_flags;                                                                                                                      // 0.0
/*1366 */ 		old_act->sa_mask.sig[0] = oact.sa_mask.sig[0];                                                                                                          // 0.0
/*1368 */ 		old_act->sa_mask.sig[1] = 0;                                                                                                                            // 0.0
/*1370 */ 		old_act->sa_mask.sig[2] = 0;                                                                                                                            // 0.0
/*1372 */ 		old_act->sa_mask.sig[3] = 0;                                                                                                                            // 0.0
/*1374 */ 		unlock_user_struct(old_act, arg3, 1);                                                                                                                   // 0.0
/*1376 */ 	    }                                                                                                                                                    // 0.0
/*1378 */ #endif                                                                                                                                                    // 0.0
/*1380 */         }                                                                                                                                                 // 0.0
/*1382 */         break;                                                                                                                                            // 0.0
/*1384 */ #endif                                                                                                                                                    // 0.0
/*1386 */     case TARGET_NR_rt_sigaction:                                                                                                                          // 0.0
/*1388 */         {                                                                                                                                                 // 0.0
/*1390 */             struct target_sigaction *act;                                                                                                                 // 0.0
/*1392 */             struct target_sigaction *oact;                                                                                                                // 0.0
/*1396 */             if (arg2) {                                                                                                                                   // 0.0
/*1398 */                 if (!lock_user_struct(VERIFY_READ, act, arg2, 1))                                                                                         // 0.0
/*1400 */                     goto efault;                                                                                                                          // 0.0
/*1402 */             } else                                                                                                                                        // 0.0
/*1404 */                 act = NULL;                                                                                                                               // 0.0
/*1406 */             if (arg3) {                                                                                                                                   // 0.0
/*1408 */                 if (!lock_user_struct(VERIFY_WRITE, oact, arg3, 0)) {                                                                                     // 0.0
/*1410 */                     ret = -TARGET_EFAULT;                                                                                                                 // 0.0
/*1412 */                     goto rt_sigaction_fail;                                                                                                               // 0.0
/*1414 */                 }                                                                                                                                         // 0.0
/*1416 */             } else                                                                                                                                        // 0.0
/*1418 */                 oact = NULL;                                                                                                                              // 0.0
/*1420 */             ret = get_errno(do_sigaction(arg1, act, oact));                                                                                               // 0.0
/*1422 */ 	rt_sigaction_fail:                                                                                                                                       // 0.0
/*1424 */             if (act)                                                                                                                                      // 0.0
/*1426 */                 unlock_user_struct(act, arg2, 0);                                                                                                         // 0.0
/*1428 */             if (oact)                                                                                                                                     // 0.0
/*1430 */                 unlock_user_struct(oact, arg3, 1);                                                                                                        // 0.0
/*1432 */         }                                                                                                                                                 // 0.0
/*1434 */         break;                                                                                                                                            // 0.0
/*1436 */ #ifdef TARGET_NR_sgetmask /* not on alpha */                                                                                                              // 0.0
/*1438 */     case TARGET_NR_sgetmask:                                                                                                                              // 0.0
/*1440 */         {                                                                                                                                                 // 0.0
/*1442 */             sigset_t cur_set;                                                                                                                             // 0.0
/*1444 */             abi_ulong target_set;                                                                                                                         // 0.0
/*1446 */             sigprocmask(0, NULL, &cur_set);                                                                                                               // 0.0
/*1448 */             host_to_target_old_sigset(&target_set, &cur_set);                                                                                             // 0.0
/*1450 */             ret = target_set;                                                                                                                             // 0.0
/*1452 */         }                                                                                                                                                 // 0.0
/*1454 */         break;                                                                                                                                            // 0.0
/*1456 */ #endif                                                                                                                                                    // 0.0
/*1458 */ #ifdef TARGET_NR_ssetmask /* not on alpha */                                                                                                              // 0.0
/*1460 */     case TARGET_NR_ssetmask:                                                                                                                              // 0.0
/*1462 */         {                                                                                                                                                 // 0.0
/*1464 */             sigset_t set, oset, cur_set;                                                                                                                  // 0.0
/*1466 */             abi_ulong target_set = arg1;                                                                                                                  // 0.0
/*1468 */             sigprocmask(0, NULL, &cur_set);                                                                                                               // 0.0
/*1470 */             target_to_host_old_sigset(&set, &target_set);                                                                                                 // 0.0
/*1472 */             sigorset(&set, &set, &cur_set);                                                                                                               // 0.0
/*1474 */             sigprocmask(SIG_SETMASK, &set, &oset);                                                                                                        // 0.0
/*1476 */             host_to_target_old_sigset(&target_set, &oset);                                                                                                // 0.0
/*1478 */             ret = target_set;                                                                                                                             // 0.0
/*1480 */         }                                                                                                                                                 // 0.0
/*1482 */         break;                                                                                                                                            // 0.0
/*1484 */ #endif                                                                                                                                                    // 0.0
/*1486 */ #ifdef TARGET_NR_sigprocmask                                                                                                                              // 0.0
/*1488 */     case TARGET_NR_sigprocmask:                                                                                                                           // 0.0
/*1490 */         {                                                                                                                                                 // 0.0
/*1492 */             int how = arg1;                                                                                                                               // 0.0
/*1494 */             sigset_t set, oldset, *set_ptr;                                                                                                               // 0.0
/*1498 */             if (arg2) {                                                                                                                                   // 0.0
/*1500 */                 switch(how) {                                                                                                                             // 0.0
/*1502 */                 case TARGET_SIG_BLOCK:                                                                                                                    // 0.0
/*1504 */                     how = SIG_BLOCK;                                                                                                                      // 0.0
/*1506 */                     break;                                                                                                                                // 0.0
/*1508 */                 case TARGET_SIG_UNBLOCK:                                                                                                                  // 0.0
/*1510 */                     how = SIG_UNBLOCK;                                                                                                                    // 0.0
/*1512 */                     break;                                                                                                                                // 0.0
/*1514 */                 case TARGET_SIG_SETMASK:                                                                                                                  // 0.0
/*1516 */                     how = SIG_SETMASK;                                                                                                                    // 0.0
/*1518 */                     break;                                                                                                                                // 0.0
/*1520 */                 default:                                                                                                                                  // 0.0
/*1522 */                     ret = -TARGET_EINVAL;                                                                                                                 // 0.0
/*1524 */                     goto fail;                                                                                                                            // 0.0
/*1526 */                 }                                                                                                                                         // 0.0
/*1528 */                 if (!(p = lock_user(VERIFY_READ, arg2, sizeof(target_sigset_t), 1)))                                                                      // 0.0
/*1530 */                     goto efault;                                                                                                                          // 0.0
/*1532 */                 target_to_host_old_sigset(&set, p);                                                                                                       // 0.0
/*1534 */                 unlock_user(p, arg2, 0);                                                                                                                  // 0.0
/*1536 */                 set_ptr = &set;                                                                                                                           // 0.0
/*1538 */             } else {                                                                                                                                      // 0.0
/*1540 */                 how = 0;                                                                                                                                  // 0.0
/*1542 */                 set_ptr = NULL;                                                                                                                           // 0.0
/*1544 */             }                                                                                                                                             // 0.0
/*1546 */             ret = get_errno(sigprocmask(arg1, set_ptr, &oldset));                                                                                         // 0.0
/*1548 */             if (!is_error(ret) && arg3) {                                                                                                                 // 0.0
/*1550 */                 if (!(p = lock_user(VERIFY_WRITE, arg3, sizeof(target_sigset_t), 0)))                                                                     // 0.0
/*1552 */                     goto efault;                                                                                                                          // 0.0
/*1554 */                 host_to_target_old_sigset(p, &oldset);                                                                                                    // 0.0
/*1556 */                 unlock_user(p, arg3, sizeof(target_sigset_t));                                                                                            // 0.0
/*1558 */             }                                                                                                                                             // 0.0
/*1560 */         }                                                                                                                                                 // 0.0
/*1562 */         break;                                                                                                                                            // 0.0
/*1564 */ #endif                                                                                                                                                    // 0.0
/*1566 */     case TARGET_NR_rt_sigprocmask:                                                                                                                        // 0.0
/*1568 */         {                                                                                                                                                 // 0.0
/*1570 */             int how = arg1;                                                                                                                               // 0.0
/*1572 */             sigset_t set, oldset, *set_ptr;                                                                                                               // 0.0
/*1576 */             if (arg2) {                                                                                                                                   // 0.0
/*1578 */                 switch(how) {                                                                                                                             // 0.0
/*1580 */                 case TARGET_SIG_BLOCK:                                                                                                                    // 0.0
/*1582 */                     how = SIG_BLOCK;                                                                                                                      // 0.0
/*1584 */                     break;                                                                                                                                // 0.0
/*1586 */                 case TARGET_SIG_UNBLOCK:                                                                                                                  // 0.0
/*1588 */                     how = SIG_UNBLOCK;                                                                                                                    // 0.0
/*1590 */                     break;                                                                                                                                // 0.0
/*1592 */                 case TARGET_SIG_SETMASK:                                                                                                                  // 0.0
/*1594 */                     how = SIG_SETMASK;                                                                                                                    // 0.0
/*1596 */                     break;                                                                                                                                // 0.0
/*1598 */                 default:                                                                                                                                  // 0.0
/*1600 */                     ret = -TARGET_EINVAL;                                                                                                                 // 0.0
/*1602 */                     goto fail;                                                                                                                            // 0.0
/*1604 */                 }                                                                                                                                         // 0.0
/*1606 */                 if (!(p = lock_user(VERIFY_READ, arg2, sizeof(target_sigset_t), 1)))                                                                      // 0.0
/*1608 */                     goto efault;                                                                                                                          // 0.0
/*1610 */                 target_to_host_sigset(&set, p);                                                                                                           // 0.0
/*1612 */                 unlock_user(p, arg2, 0);                                                                                                                  // 0.0
/*1614 */                 set_ptr = &set;                                                                                                                           // 0.0
/*1616 */             } else {                                                                                                                                      // 0.0
/*1618 */                 how = 0;                                                                                                                                  // 0.0
/*1620 */                 set_ptr = NULL;                                                                                                                           // 0.0
/*1622 */             }                                                                                                                                             // 0.0
/*1624 */             ret = get_errno(sigprocmask(how, set_ptr, &oldset));                                                                                          // 0.0
/*1626 */             if (!is_error(ret) && arg3) {                                                                                                                 // 0.0
/*1628 */                 if (!(p = lock_user(VERIFY_WRITE, arg3, sizeof(target_sigset_t), 0)))                                                                     // 0.0
/*1630 */                     goto efault;                                                                                                                          // 0.0
/*1632 */                 host_to_target_sigset(p, &oldset);                                                                                                        // 0.0
/*1634 */                 unlock_user(p, arg3, sizeof(target_sigset_t));                                                                                            // 0.0
/*1636 */             }                                                                                                                                             // 0.0
/*1638 */         }                                                                                                                                                 // 0.0
/*1640 */         break;                                                                                                                                            // 0.0
/*1642 */ #ifdef TARGET_NR_sigpending                                                                                                                               // 0.0
/*1644 */     case TARGET_NR_sigpending:                                                                                                                            // 0.0
/*1646 */         {                                                                                                                                                 // 0.0
/*1648 */             sigset_t set;                                                                                                                                 // 0.0
/*1650 */             ret = get_errno(sigpending(&set));                                                                                                            // 0.0
/*1652 */             if (!is_error(ret)) {                                                                                                                         // 0.0
/*1654 */                 if (!(p = lock_user(VERIFY_WRITE, arg1, sizeof(target_sigset_t), 0)))                                                                     // 0.0
/*1656 */                     goto efault;                                                                                                                          // 0.0
/*1658 */                 host_to_target_old_sigset(p, &set);                                                                                                       // 0.0
/*1660 */                 unlock_user(p, arg1, sizeof(target_sigset_t));                                                                                            // 0.0
/*1662 */             }                                                                                                                                             // 0.0
/*1664 */         }                                                                                                                                                 // 0.0
/*1666 */         break;                                                                                                                                            // 0.0
/*1668 */ #endif                                                                                                                                                    // 0.0
/*1670 */     case TARGET_NR_rt_sigpending:                                                                                                                         // 0.0
/*1672 */         {                                                                                                                                                 // 0.0
/*1674 */             sigset_t set;                                                                                                                                 // 0.0
/*1676 */             ret = get_errno(sigpending(&set));                                                                                                            // 0.0
/*1678 */             if (!is_error(ret)) {                                                                                                                         // 0.0
/*1680 */                 if (!(p = lock_user(VERIFY_WRITE, arg1, sizeof(target_sigset_t), 0)))                                                                     // 0.0
/*1682 */                     goto efault;                                                                                                                          // 0.0
/*1684 */                 host_to_target_sigset(p, &set);                                                                                                           // 0.0
/*1686 */                 unlock_user(p, arg1, sizeof(target_sigset_t));                                                                                            // 0.0
/*1688 */             }                                                                                                                                             // 0.0
/*1690 */         }                                                                                                                                                 // 0.0
/*1692 */         break;                                                                                                                                            // 0.0
/*1694 */ #ifdef TARGET_NR_sigsuspend                                                                                                                               // 0.0
/*1696 */     case TARGET_NR_sigsuspend:                                                                                                                            // 0.0
/*1698 */         {                                                                                                                                                 // 0.0
/*1700 */             sigset_t set;                                                                                                                                 // 0.0
/*1702 */             if (!(p = lock_user(VERIFY_READ, arg1, sizeof(target_sigset_t), 1)))                                                                          // 0.0
/*1704 */                 goto efault;                                                                                                                              // 0.0
/*1706 */             target_to_host_old_sigset(&set, p);                                                                                                           // 0.0
/*1708 */             unlock_user(p, arg1, 0);                                                                                                                      // 0.0
/*1710 */             ret = get_errno(sigsuspend(&set));                                                                                                            // 0.0
/*1712 */         }                                                                                                                                                 // 0.0
/*1714 */         break;                                                                                                                                            // 0.0
/*1716 */ #endif                                                                                                                                                    // 0.0
/*1718 */     case TARGET_NR_rt_sigsuspend:                                                                                                                         // 0.0
/*1720 */         {                                                                                                                                                 // 0.0
/*1722 */             sigset_t set;                                                                                                                                 // 0.0
/*1724 */             if (!(p = lock_user(VERIFY_READ, arg1, sizeof(target_sigset_t), 1)))                                                                          // 0.0
/*1726 */                 goto efault;                                                                                                                              // 0.0
/*1728 */             target_to_host_sigset(&set, p);                                                                                                               // 0.0
/*1730 */             unlock_user(p, arg1, 0);                                                                                                                      // 0.0
/*1732 */             ret = get_errno(sigsuspend(&set));                                                                                                            // 0.0
/*1734 */         }                                                                                                                                                 // 0.0
/*1736 */         break;                                                                                                                                            // 0.0
/*1738 */     case TARGET_NR_rt_sigtimedwait:                                                                                                                       // 0.0
/*1740 */         {                                                                                                                                                 // 0.0
/*1742 */             sigset_t set;                                                                                                                                 // 0.0
/*1744 */             struct timespec uts, *puts;                                                                                                                   // 0.0
/*1746 */             siginfo_t uinfo;                                                                                                                              // 0.0
/*1750 */             if (!(p = lock_user(VERIFY_READ, arg1, sizeof(target_sigset_t), 1)))                                                                          // 0.0
/*1752 */                 goto efault;                                                                                                                              // 0.0
/*1754 */             target_to_host_sigset(&set, p);                                                                                                               // 0.0
/*1756 */             unlock_user(p, arg1, 0);                                                                                                                      // 0.0
/*1758 */             if (arg3) {                                                                                                                                   // 0.0
/*1760 */                 puts = &uts;                                                                                                                              // 0.0
/*1762 */                 target_to_host_timespec(puts, arg3);                                                                                                      // 0.0
/*1764 */             } else {                                                                                                                                      // 0.0
/*1766 */                 puts = NULL;                                                                                                                              // 0.0
/*1768 */             }                                                                                                                                             // 0.0
/*1770 */             ret = get_errno(sigtimedwait(&set, &uinfo, puts));                                                                                            // 0.0
/*1772 */             if (!is_error(ret) && arg2) {                                                                                                                 // 0.0
/*1774 */                 if (!(p = lock_user(VERIFY_WRITE, arg2, sizeof(target_siginfo_t), 0)))                                                                    // 0.0
/*1776 */                     goto efault;                                                                                                                          // 0.0
/*1778 */                 host_to_target_siginfo(p, &uinfo);                                                                                                        // 0.0
/*1780 */                 unlock_user(p, arg2, sizeof(target_siginfo_t));                                                                                           // 0.0
/*1782 */             }                                                                                                                                             // 0.0
/*1784 */         }                                                                                                                                                 // 0.0
/*1786 */         break;                                                                                                                                            // 0.0
/*1788 */     case TARGET_NR_rt_sigqueueinfo:                                                                                                                       // 0.0
/*1790 */         {                                                                                                                                                 // 0.0
/*1792 */             siginfo_t uinfo;                                                                                                                              // 0.0
/*1794 */             if (!(p = lock_user(VERIFY_READ, arg3, sizeof(target_sigset_t), 1)))                                                                          // 0.0
/*1796 */                 goto efault;                                                                                                                              // 0.0
/*1798 */             target_to_host_siginfo(&uinfo, p);                                                                                                            // 0.0
/*1800 */             unlock_user(p, arg1, 0);                                                                                                                      // 0.0
/*1802 */             ret = get_errno(sys_rt_sigqueueinfo(arg1, arg2, &uinfo));                                                                                     // 0.0
/*1804 */         }                                                                                                                                                 // 0.0
/*1806 */         break;                                                                                                                                            // 0.0
/*1808 */ #ifdef TARGET_NR_sigreturn                                                                                                                                // 0.0
/*1810 */     case TARGET_NR_sigreturn:                                                                                                                             // 0.0
/*1812 */         /* NOTE: ret is eax, so not transcoding must be done */                                                                                           // 0.0
/*1814 */         ret = do_sigreturn(cpu_env);                                                                                                                      // 0.0
/*1816 */         break;                                                                                                                                            // 0.0
/*1818 */ #endif                                                                                                                                                    // 0.0
/*1820 */     case TARGET_NR_rt_sigreturn:                                                                                                                          // 0.0
/*1822 */         /* NOTE: ret is eax, so not transcoding must be done */                                                                                           // 0.0
/*1824 */         ret = do_rt_sigreturn(cpu_env);                                                                                                                   // 0.0
/*1826 */         break;                                                                                                                                            // 0.0
/*1828 */     case TARGET_NR_sethostname:                                                                                                                           // 0.0
/*1830 */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*1832 */             goto efault;                                                                                                                                  // 0.0
/*1834 */         ret = get_errno(sethostname(p, arg2));                                                                                                            // 0.0
/*1836 */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*1838 */         break;                                                                                                                                            // 0.0
/*1840 */     case TARGET_NR_setrlimit:                                                                                                                             // 0.0
/*1842 */         {                                                                                                                                                 // 0.0
/*1844 */             /* XXX: convert resource ? */                                                                                                                 // 0.0
/*1846 */             int resource = arg1;                                                                                                                          // 0.0
/*1848 */             struct target_rlimit *target_rlim;                                                                                                            // 0.0
/*1850 */             struct rlimit rlim;                                                                                                                           // 0.0
/*1852 */             if (!lock_user_struct(VERIFY_READ, target_rlim, arg2, 1))                                                                                     // 0.0
/*1854 */                 goto efault;                                                                                                                              // 0.0
/*1856 */             rlim.rlim_cur = tswapl(target_rlim->rlim_cur);                                                                                                // 0.0
/*1858 */             rlim.rlim_max = tswapl(target_rlim->rlim_max);                                                                                                // 0.0
/*1860 */             unlock_user_struct(target_rlim, arg2, 0);                                                                                                     // 0.0
/*1862 */             ret = get_errno(setrlimit(resource, &rlim));                                                                                                  // 0.0
/*1864 */         }                                                                                                                                                 // 0.0
/*1866 */         break;                                                                                                                                            // 0.0
/*1868 */     case TARGET_NR_getrlimit:                                                                                                                             // 0.0
/*1870 */         {                                                                                                                                                 // 0.0
/*1872 */             /* XXX: convert resource ? */                                                                                                                 // 0.0
/*1874 */             int resource = arg1;                                                                                                                          // 0.0
/*1876 */             struct target_rlimit *target_rlim;                                                                                                            // 0.0
/*1878 */             struct rlimit rlim;                                                                                                                           // 0.0
/*1882 */             ret = get_errno(getrlimit(resource, &rlim));                                                                                                  // 0.0
/*1884 */             if (!is_error(ret)) {                                                                                                                         // 0.0
/*1886 */                 if (!lock_user_struct(VERIFY_WRITE, target_rlim, arg2, 0))                                                                                // 0.0
/*1888 */                     goto efault;                                                                                                                          // 0.0
/*1890 */                 target_rlim->rlim_cur = tswapl(rlim.rlim_cur);                                                                                            // 0.0
/*1892 */                 target_rlim->rlim_max = tswapl(rlim.rlim_max);                                                                                            // 0.0
/*1894 */                 unlock_user_struct(target_rlim, arg2, 1);                                                                                                 // 0.0
/*1896 */             }                                                                                                                                             // 0.0
/*1898 */         }                                                                                                                                                 // 0.0
/*1900 */         break;                                                                                                                                            // 0.0
/*1902 */     case TARGET_NR_getrusage:                                                                                                                             // 0.0
/*1904 */         {                                                                                                                                                 // 0.0
/*1906 */             struct rusage rusage;                                                                                                                         // 0.0
/*1908 */             ret = get_errno(getrusage(arg1, &rusage));                                                                                                    // 0.0
/*1910 */             if (!is_error(ret)) {                                                                                                                         // 0.0
/*1912 */                 host_to_target_rusage(arg2, &rusage);                                                                                                     // 0.0
/*1914 */             }                                                                                                                                             // 0.0
/*1916 */         }                                                                                                                                                 // 0.0
/*1918 */         break;                                                                                                                                            // 0.0
/*1920 */     case TARGET_NR_gettimeofday:                                                                                                                          // 0.0
/*1922 */         {                                                                                                                                                 // 0.0
/*1924 */             struct timeval tv;                                                                                                                            // 0.0
/*1926 */             ret = get_errno(gettimeofday(&tv, NULL));                                                                                                     // 0.0
/*1928 */             if (!is_error(ret)) {                                                                                                                         // 0.0
/*1930 */                 if (copy_to_user_timeval(arg1, &tv))                                                                                                      // 0.0
/*1932 */                     goto efault;                                                                                                                          // 0.0
/*1934 */             }                                                                                                                                             // 0.0
/*1936 */         }                                                                                                                                                 // 0.0
/*1938 */         break;                                                                                                                                            // 0.0
/*1940 */     case TARGET_NR_settimeofday:                                                                                                                          // 0.0
/*1942 */         {                                                                                                                                                 // 0.0
/*1944 */             struct timeval tv;                                                                                                                            // 0.0
/*1946 */             if (copy_from_user_timeval(&tv, arg1))                                                                                                        // 0.0
/*1948 */                 goto efault;                                                                                                                              // 0.0
/*1950 */             ret = get_errno(settimeofday(&tv, NULL));                                                                                                     // 0.0
/*1952 */         }                                                                                                                                                 // 0.0
/*1954 */         break;                                                                                                                                            // 0.0
/*1956 */ #ifdef TARGET_NR_select                                                                                                                                   // 0.0
/*1958 */     case TARGET_NR_select:                                                                                                                                // 0.0
/*1960 */         {                                                                                                                                                 // 0.0
/*1962 */             struct target_sel_arg_struct *sel;                                                                                                            // 0.0
/*1964 */             abi_ulong inp, outp, exp, tvp;                                                                                                                // 0.0
/*1966 */             long nsel;                                                                                                                                    // 0.0
/*1970 */             if (!lock_user_struct(VERIFY_READ, sel, arg1, 1))                                                                                             // 0.0
/*1972 */                 goto efault;                                                                                                                              // 0.0
/*1974 */             nsel = tswapl(sel->n);                                                                                                                        // 0.0
/*1976 */             inp = tswapl(sel->inp);                                                                                                                       // 0.0
/*1978 */             outp = tswapl(sel->outp);                                                                                                                     // 0.0
/*1980 */             exp = tswapl(sel->exp);                                                                                                                       // 0.0
/*1982 */             tvp = tswapl(sel->tvp);                                                                                                                       // 0.0
/*1984 */             unlock_user_struct(sel, arg1, 0);                                                                                                             // 0.0
/*1986 */             ret = do_select(nsel, inp, outp, exp, tvp);                                                                                                   // 0.0
/*1988 */         }                                                                                                                                                 // 0.0
/*1990 */         break;                                                                                                                                            // 0.0
/*1992 */ #endif                                                                                                                                                    // 0.0
/*1994 */     case TARGET_NR_symlink:                                                                                                                               // 0.0
/*1996 */         {                                                                                                                                                 // 0.0
/*1998 */             void *p2;                                                                                                                                     // 0.0
/*2000 */             p = lock_user_string(arg1);                                                                                                                   // 0.0
/*2002 */             p2 = lock_user_string(arg2);                                                                                                                  // 0.0
/*2004 */             if (!p || !p2)                                                                                                                                // 0.0
/*2006 */                 ret = -TARGET_EFAULT;                                                                                                                     // 0.0
/*2008 */             else                                                                                                                                          // 0.0
/*2010 */                 ret = get_errno(symlink(p, p2));                                                                                                          // 0.0
/*2012 */             unlock_user(p2, arg2, 0);                                                                                                                     // 0.0
/*2014 */             unlock_user(p, arg1, 0);                                                                                                                      // 0.0
/*2016 */         }                                                                                                                                                 // 0.0
/*2018 */         break;                                                                                                                                            // 0.0
/*2020 */ #if defined(TARGET_NR_symlinkat) && defined(__NR_symlinkat)                                                                                               // 0.0
/*2022 */     case TARGET_NR_symlinkat:                                                                                                                             // 0.0
/*2024 */         {                                                                                                                                                 // 0.0
/*2026 */             void *p2;                                                                                                                                     // 0.0
/*2028 */             p  = lock_user_string(arg1);                                                                                                                  // 0.0
/*2030 */             p2 = lock_user_string(arg3);                                                                                                                  // 0.0
/*2032 */             if (!p || !p2)                                                                                                                                // 0.0
/*2034 */                 ret = -TARGET_EFAULT;                                                                                                                     // 0.0
/*2036 */             else                                                                                                                                          // 0.0
/*2038 */                 ret = get_errno(sys_symlinkat(p, arg2, p2));                                                                                              // 0.0
/*2040 */             unlock_user(p2, arg3, 0);                                                                                                                     // 0.0
/*2042 */             unlock_user(p, arg1, 0);                                                                                                                      // 0.0
/*2044 */         }                                                                                                                                                 // 0.0
/*2046 */         break;                                                                                                                                            // 0.0
/*2048 */ #endif                                                                                                                                                    // 0.0
/*2050 */ #ifdef TARGET_NR_oldlstat                                                                                                                                 // 0.0
/*2052 */     case TARGET_NR_oldlstat:                                                                                                                              // 0.0
/*2054 */         goto unimplemented;                                                                                                                               // 0.0
/*2056 */ #endif                                                                                                                                                    // 0.0
/*2058 */     case TARGET_NR_readlink:                                                                                                                              // 0.0
/*2060 */         {                                                                                                                                                 // 0.0
/*2062 */             void *p2, *temp;                                                                                                                              // 0.0
/*2064 */             p = lock_user_string(arg1);                                                                                                                   // 0.0
/*2066 */             p2 = lock_user(VERIFY_WRITE, arg2, arg3, 0);                                                                                                  // 0.0
/*2068 */             if (!p || !p2)                                                                                                                                // 0.0
/*2070 */                 ret = -TARGET_EFAULT;                                                                                                                     // 0.0
/*2072 */             else {                                                                                                                                        // 0.0
/*2074 */                 if (strncmp((const char *)p, "/proc/self/exe", 14) == 0) {                                                                                // 0.0
/*2076 */                     char real[PATH_MAX];                                                                                                                  // 0.0
/*2078 */                     temp = realpath(exec_path,real);                                                                                                      // 0.0
/*2080 */                     ret = (temp==NULL) ? get_errno(-1) : strlen(real) ;                                                                                   // 0.0
/*2082 */                     snprintf((char *)p2, arg3, "%s", real);                                                                                               // 0.0
/*2084 */                     }                                                                                                                                     // 0.0
/*2086 */                 else                                                                                                                                      // 0.0
/*2088 */                     ret = get_errno(readlink(path(p), p2, arg3));                                                                                         // 0.0
/*2090 */             }                                                                                                                                             // 0.0
/*2092 */             unlock_user(p2, arg2, ret);                                                                                                                   // 0.0
/*2094 */             unlock_user(p, arg1, 0);                                                                                                                      // 0.0
/*2096 */         }                                                                                                                                                 // 0.0
/*2098 */         break;                                                                                                                                            // 0.0
/*2100 */ #if defined(TARGET_NR_readlinkat) && defined(__NR_readlinkat)                                                                                             // 0.0
/*2102 */     case TARGET_NR_readlinkat:                                                                                                                            // 0.0
/*2104 */         {                                                                                                                                                 // 0.0
/*2106 */             void *p2;                                                                                                                                     // 0.0
/*2108 */             p  = lock_user_string(arg2);                                                                                                                  // 0.0
/*2110 */             p2 = lock_user(VERIFY_WRITE, arg3, arg4, 0);                                                                                                  // 0.0
/*2112 */             if (!p || !p2)                                                                                                                                // 0.0
/*2114 */         	ret = -TARGET_EFAULT;                                                                                                                            // 0.0
/*2116 */             else                                                                                                                                          // 0.0
/*2118 */                 ret = get_errno(sys_readlinkat(arg1, path(p), p2, arg4));                                                                                 // 0.0
/*2120 */             unlock_user(p2, arg3, ret);                                                                                                                   // 0.0
/*2122 */             unlock_user(p, arg2, 0);                                                                                                                      // 0.0
/*2124 */         }                                                                                                                                                 // 0.0
/*2126 */         break;                                                                                                                                            // 0.0
/*2128 */ #endif                                                                                                                                                    // 0.0
/*2130 */ #ifdef TARGET_NR_uselib                                                                                                                                   // 0.0
/*2132 */     case TARGET_NR_uselib:                                                                                                                                // 0.0
/*2134 */         goto unimplemented;                                                                                                                               // 0.0
/*2136 */ #endif                                                                                                                                                    // 0.0
/*2138 */ #ifdef TARGET_NR_swapon                                                                                                                                   // 0.0
/*2140 */     case TARGET_NR_swapon:                                                                                                                                // 0.0
/*2142 */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*2144 */             goto efault;                                                                                                                                  // 0.0
/*2146 */         ret = get_errno(swapon(p, arg2));                                                                                                                 // 0.0
/*2148 */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*2150 */         break;                                                                                                                                            // 0.0
/*2152 */ #endif                                                                                                                                                    // 0.0
/*2154 */     case TARGET_NR_reboot:                                                                                                                                // 0.0
/*2156 */         goto unimplemented;                                                                                                                               // 0.0
/*2158 */ #ifdef TARGET_NR_readdir                                                                                                                                  // 0.0
/*2160 */     case TARGET_NR_readdir:                                                                                                                               // 0.0
/*2162 */         goto unimplemented;                                                                                                                               // 0.0
/*2164 */ #endif                                                                                                                                                    // 0.0
/*2166 */ #ifdef TARGET_NR_mmap                                                                                                                                     // 0.0
/*2168 */     case TARGET_NR_mmap:                                                                                                                                  // 0.0
/*2170 */ #if (defined(TARGET_I386) && defined(TARGET_ABI32)) || defined(TARGET_ARM) || defined(TARGET_M68K) || defined(TARGET_CRIS) || defined(TARGET_MICROBLAZE)  // 0.0
/*2172 */         {                                                                                                                                                 // 0.0
/*2174 */             abi_ulong *v;                                                                                                                                 // 0.0
/*2176 */             abi_ulong v1, v2, v3, v4, v5, v6;                                                                                                             // 0.0
/*2178 */             if (!(v = lock_user(VERIFY_READ, arg1, 6 * sizeof(abi_ulong), 1)))                                                                            // 0.0
/*2180 */                 goto efault;                                                                                                                              // 0.0
/*2182 */             v1 = tswapl(v[0]);                                                                                                                            // 0.0
/*2184 */             v2 = tswapl(v[1]);                                                                                                                            // 0.0
/*2186 */             v3 = tswapl(v[2]);                                                                                                                            // 0.0
/*2188 */             v4 = tswapl(v[3]);                                                                                                                            // 0.0
/*2190 */             v5 = tswapl(v[4]);                                                                                                                            // 0.0
/*2192 */             v6 = tswapl(v[5]);                                                                                                                            // 0.0
/*2194 */             unlock_user(v, arg1, 0);                                                                                                                      // 0.0
/*2196 */             ret = get_errno(target_mmap(v1, v2, v3,                                                                                                       // 0.0
/*2198 */                                         target_to_host_bitmask(v4, mmap_flags_tbl),                                                                       // 0.0
/*2200 */                                         v5, v6));                                                                                                         // 0.0
/*2202 */         }                                                                                                                                                 // 0.0
/*2204 */ #else                                                                                                                                                     // 0.0
/*2206 */         ret = get_errno(target_mmap(arg1, arg2, arg3,                                                                                                     // 0.0
/*2208 */                                     target_to_host_bitmask(arg4, mmap_flags_tbl),                                                                         // 0.0
/*2210 */                                     arg5,                                                                                                                 // 0.0
/*2212 */                                     arg6));                                                                                                               // 0.0
/*2214 */ #endif                                                                                                                                                    // 0.0
/*2216 */         break;                                                                                                                                            // 0.0
/*2218 */ #endif                                                                                                                                                    // 0.0
/*2220 */ #ifdef TARGET_NR_mmap2                                                                                                                                    // 0.0
/*2222 */     case TARGET_NR_mmap2:                                                                                                                                 // 0.0
/*2224 */ #ifndef MMAP_SHIFT                                                                                                                                        // 0.0
/*2226 */ #define MMAP_SHIFT 12                                                                                                                                     // 0.0
/*2228 */ #endif                                                                                                                                                    // 0.0
/*2230 */         ret = get_errno(target_mmap(arg1, arg2, arg3,                                                                                                     // 0.0
/*2232 */                                     target_to_host_bitmask(arg4, mmap_flags_tbl),                                                                         // 0.0
/*2234 */                                     arg5,                                                                                                                 // 0.0
/*2236 */                                     arg6 << MMAP_SHIFT));                                                                                                 // 0.0
/*2238 */         break;                                                                                                                                            // 0.0
/*2240 */ #endif                                                                                                                                                    // 0.0
/*2242 */     case TARGET_NR_munmap:                                                                                                                                // 0.0
/*2244 */         ret = get_errno(target_munmap(arg1, arg2));                                                                                                       // 0.0
/*2246 */         break;                                                                                                                                            // 0.0
/*2248 */     case TARGET_NR_mprotect:                                                                                                                              // 0.0
/*2250 */         ret = get_errno(target_mprotect(arg1, arg2, arg3));                                                                                               // 0.0
/*2252 */         break;                                                                                                                                            // 0.0
/*2254 */ #ifdef TARGET_NR_mremap                                                                                                                                   // 0.0
/*2256 */     case TARGET_NR_mremap:                                                                                                                                // 0.0
/*2258 */         ret = get_errno(target_mremap(arg1, arg2, arg3, arg4, arg5));                                                                                     // 0.0
/*2260 */         break;                                                                                                                                            // 0.0
/*2262 */ #endif                                                                                                                                                    // 0.0
/*2264 */         /* ??? msync/mlock/munlock are broken for softmmu.  */                                                                                            // 0.0
/*2266 */ #ifdef TARGET_NR_msync                                                                                                                                    // 0.0
/*2268 */     case TARGET_NR_msync:                                                                                                                                 // 0.0
/*2270 */         ret = get_errno(msync(g2h(arg1), arg2, arg3));                                                                                                    // 0.0
/*2272 */         break;                                                                                                                                            // 0.0
/*2274 */ #endif                                                                                                                                                    // 0.0
/*2276 */ #ifdef TARGET_NR_mlock                                                                                                                                    // 0.0
/*2278 */     case TARGET_NR_mlock:                                                                                                                                 // 0.0
/*2280 */         ret = get_errno(mlock(g2h(arg1), arg2));                                                                                                          // 0.0
/*2282 */         break;                                                                                                                                            // 0.0
/*2284 */ #endif                                                                                                                                                    // 0.0
/*2286 */ #ifdef TARGET_NR_munlock                                                                                                                                  // 0.0
/*2288 */     case TARGET_NR_munlock:                                                                                                                               // 0.0
/*2290 */         ret = get_errno(munlock(g2h(arg1), arg2));                                                                                                        // 0.0
/*2292 */         break;                                                                                                                                            // 0.0
/*2294 */ #endif                                                                                                                                                    // 0.0
/*2296 */ #ifdef TARGET_NR_mlockall                                                                                                                                 // 0.0
/*2298 */     case TARGET_NR_mlockall:                                                                                                                              // 0.0
/*2300 */         ret = get_errno(mlockall(arg1));                                                                                                                  // 0.0
/*2302 */         break;                                                                                                                                            // 0.0
/*2304 */ #endif                                                                                                                                                    // 0.0
/*2306 */ #ifdef TARGET_NR_munlockall                                                                                                                               // 0.0
/*2308 */     case TARGET_NR_munlockall:                                                                                                                            // 0.0
/*2310 */         ret = get_errno(munlockall());                                                                                                                    // 0.0
/*2312 */         break;                                                                                                                                            // 0.0
/*2314 */ #endif                                                                                                                                                    // 0.0
/*2316 */     case TARGET_NR_truncate:                                                                                                                              // 0.0
/*2318 */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*2320 */             goto efault;                                                                                                                                  // 0.0
/*2322 */         ret = get_errno(truncate(p, arg2));                                                                                                               // 0.0
/*2324 */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*2326 */         break;                                                                                                                                            // 0.0
/*2328 */     case TARGET_NR_ftruncate:                                                                                                                             // 0.0
/*2330 */         ret = get_errno(ftruncate(arg1, arg2));                                                                                                           // 0.0
/*2332 */         break;                                                                                                                                            // 0.0
/*2334 */     case TARGET_NR_fchmod:                                                                                                                                // 0.0
/*2336 */         ret = get_errno(fchmod(arg1, arg2));                                                                                                              // 0.0
/*2338 */         break;                                                                                                                                            // 0.0
/*2340 */ #if defined(TARGET_NR_fchmodat) && defined(__NR_fchmodat)                                                                                                 // 0.0
/*2342 */     case TARGET_NR_fchmodat:                                                                                                                              // 0.0
/*2344 */         if (!(p = lock_user_string(arg2)))                                                                                                                // 0.0
/*2346 */             goto efault;                                                                                                                                  // 0.0
/*2348 */         ret = get_errno(sys_fchmodat(arg1, p, arg3));                                                                                                     // 0.0
/*2350 */         unlock_user(p, arg2, 0);                                                                                                                          // 0.0
/*2352 */         break;                                                                                                                                            // 0.0
/*2354 */ #endif                                                                                                                                                    // 0.0
/*2356 */     case TARGET_NR_getpriority:                                                                                                                           // 0.0
/*2358 */         /* libc does special remapping of the return value of                                                                                             // 0.0
/*2360 */          * sys_getpriority() so it's just easiest to call                                                                                                 // 0.0
/*2362 */          * sys_getpriority() directly rather than through libc. */                                                                                        // 0.0
/*2364 */         ret = get_errno(sys_getpriority(arg1, arg2));                                                                                                     // 0.0
/*2366 */         break;                                                                                                                                            // 0.0
/*2368 */     case TARGET_NR_setpriority:                                                                                                                           // 0.0
/*2370 */         ret = get_errno(setpriority(arg1, arg2, arg3));                                                                                                   // 0.0
/*2372 */         break;                                                                                                                                            // 0.0
/*2374 */ #ifdef TARGET_NR_profil                                                                                                                                   // 0.0
/*2376 */     case TARGET_NR_profil:                                                                                                                                // 0.0
/*2378 */         goto unimplemented;                                                                                                                               // 0.0
/*2380 */ #endif                                                                                                                                                    // 0.0
/*2382 */     case TARGET_NR_statfs:                                                                                                                                // 0.0
/*2384 */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*2386 */             goto efault;                                                                                                                                  // 0.0
/*2388 */         ret = get_errno(statfs(path(p), &stfs));                                                                                                          // 0.0
/*2390 */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*2392 */     convert_statfs:                                                                                                                                       // 0.0
/*2394 */         if (!is_error(ret)) {                                                                                                                             // 0.0
/*2396 */             struct target_statfs *target_stfs;                                                                                                            // 0.0
/*2400 */             if (!lock_user_struct(VERIFY_WRITE, target_stfs, arg2, 0))                                                                                    // 0.0
/*2402 */                 goto efault;                                                                                                                              // 0.0
/*2404 */             __put_user(stfs.f_type, &target_stfs->f_type);                                                                                                // 0.0
/*2406 */             __put_user(stfs.f_bsize, &target_stfs->f_bsize);                                                                                              // 0.0
/*2408 */             __put_user(stfs.f_blocks, &target_stfs->f_blocks);                                                                                            // 0.0
/*2410 */             __put_user(stfs.f_bfree, &target_stfs->f_bfree);                                                                                              // 0.0
/*2412 */             __put_user(stfs.f_bavail, &target_stfs->f_bavail);                                                                                            // 0.0
/*2414 */             __put_user(stfs.f_files, &target_stfs->f_files);                                                                                              // 0.0
/*2416 */             __put_user(stfs.f_ffree, &target_stfs->f_ffree);                                                                                              // 0.0
/*2418 */             __put_user(stfs.f_fsid.__val[0], &target_stfs->f_fsid.val[0]);                                                                                // 0.0
/*2420 */             __put_user(stfs.f_fsid.__val[1], &target_stfs->f_fsid.val[1]);                                                                                // 0.0
/*2422 */             __put_user(stfs.f_namelen, &target_stfs->f_namelen);                                                                                          // 0.0
/*2424 */             unlock_user_struct(target_stfs, arg2, 1);                                                                                                     // 0.0
/*2426 */         }                                                                                                                                                 // 0.0
/*2428 */         break;                                                                                                                                            // 0.0
/*2430 */     case TARGET_NR_fstatfs:                                                                                                                               // 0.0
/*2432 */         ret = get_errno(fstatfs(arg1, &stfs));                                                                                                            // 0.0
/*2434 */         goto convert_statfs;                                                                                                                              // 0.0
/*2436 */ #ifdef TARGET_NR_statfs64                                                                                                                                 // 0.0
/*2438 */     case TARGET_NR_statfs64:                                                                                                                              // 0.0
/*2440 */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*2442 */             goto efault;                                                                                                                                  // 0.0
/*2444 */         ret = get_errno(statfs(path(p), &stfs));                                                                                                          // 0.0
/*2446 */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*2448 */     convert_statfs64:                                                                                                                                     // 0.0
/*2450 */         if (!is_error(ret)) {                                                                                                                             // 0.0
/*2452 */             struct target_statfs64 *target_stfs;                                                                                                          // 0.0
/*2456 */             if (!lock_user_struct(VERIFY_WRITE, target_stfs, arg3, 0))                                                                                    // 0.0
/*2458 */                 goto efault;                                                                                                                              // 0.0
/*2460 */             __put_user(stfs.f_type, &target_stfs->f_type);                                                                                                // 0.0
/*2462 */             __put_user(stfs.f_bsize, &target_stfs->f_bsize);                                                                                              // 0.0
/*2464 */             __put_user(stfs.f_blocks, &target_stfs->f_blocks);                                                                                            // 0.0
/*2466 */             __put_user(stfs.f_bfree, &target_stfs->f_bfree);                                                                                              // 0.0
/*2468 */             __put_user(stfs.f_bavail, &target_stfs->f_bavail);                                                                                            // 0.0
/*2470 */             __put_user(stfs.f_files, &target_stfs->f_files);                                                                                              // 0.0
/*2472 */             __put_user(stfs.f_ffree, &target_stfs->f_ffree);                                                                                              // 0.0
/*2474 */             __put_user(stfs.f_fsid.__val[0], &target_stfs->f_fsid.val[0]);                                                                                // 0.0
/*2476 */             __put_user(stfs.f_fsid.__val[1], &target_stfs->f_fsid.val[1]);                                                                                // 0.0
/*2478 */             __put_user(stfs.f_namelen, &target_stfs->f_namelen);                                                                                          // 0.0
/*2480 */             unlock_user_struct(target_stfs, arg3, 1);                                                                                                     // 0.0
/*2482 */         }                                                                                                                                                 // 0.0
/*2484 */         break;                                                                                                                                            // 0.0
/*2486 */     case TARGET_NR_fstatfs64:                                                                                                                             // 0.0
/*2488 */         ret = get_errno(fstatfs(arg1, &stfs));                                                                                                            // 0.0
/*2490 */         goto convert_statfs64;                                                                                                                            // 0.0
/*2492 */ #endif                                                                                                                                                    // 0.0
/*2494 */ #ifdef TARGET_NR_ioperm                                                                                                                                   // 0.0
/*2496 */     case TARGET_NR_ioperm:                                                                                                                                // 0.0
/*2498 */         goto unimplemented;                                                                                                                               // 0.0
/*2500 */ #endif                                                                                                                                                    // 0.0
/*2502 */ #ifdef TARGET_NR_socketcall                                                                                                                               // 0.0
/*2504 */     case TARGET_NR_socketcall:                                                                                                                            // 0.0
/*2506 */         ret = do_socketcall(arg1, arg2);                                                                                                                  // 0.0
/*2508 */         break;                                                                                                                                            // 0.0
/*2510 */ #endif                                                                                                                                                    // 0.0
/*2512 */ #ifdef TARGET_NR_accept                                                                                                                                   // 0.0
/*2514 */     case TARGET_NR_accept:                                                                                                                                // 0.0
/*2516 */         ret = do_accept(arg1, arg2, arg3);                                                                                                                // 0.0
/*2518 */         break;                                                                                                                                            // 0.0
/*2520 */ #endif                                                                                                                                                    // 0.0
/*2522 */ #ifdef TARGET_NR_bind                                                                                                                                     // 0.0
/*2524 */     case TARGET_NR_bind:                                                                                                                                  // 0.0
/*2526 */         ret = do_bind(arg1, arg2, arg3);                                                                                                                  // 0.0
/*2528 */         break;                                                                                                                                            // 0.0
/*2530 */ #endif                                                                                                                                                    // 0.0
/*2532 */ #ifdef TARGET_NR_connect                                                                                                                                  // 0.0
/*2534 */     case TARGET_NR_connect:                                                                                                                               // 0.0
/*2536 */         ret = do_connect(arg1, arg2, arg3);                                                                                                               // 0.0
/*2538 */         break;                                                                                                                                            // 0.0
/*2540 */ #endif                                                                                                                                                    // 0.0
/*2542 */ #ifdef TARGET_NR_getpeername                                                                                                                              // 0.0
/*2544 */     case TARGET_NR_getpeername:                                                                                                                           // 0.0
/*2546 */         ret = do_getpeername(arg1, arg2, arg3);                                                                                                           // 0.0
/*2548 */         break;                                                                                                                                            // 0.0
/*2550 */ #endif                                                                                                                                                    // 0.0
/*2552 */ #ifdef TARGET_NR_getsockname                                                                                                                              // 0.0
/*2554 */     case TARGET_NR_getsockname:                                                                                                                           // 0.0
/*2556 */         ret = do_getsockname(arg1, arg2, arg3);                                                                                                           // 0.0
/*2558 */         break;                                                                                                                                            // 0.0
/*2560 */ #endif                                                                                                                                                    // 0.0
/*2562 */ #ifdef TARGET_NR_getsockopt                                                                                                                               // 0.0
/*2564 */     case TARGET_NR_getsockopt:                                                                                                                            // 0.0
/*2566 */         ret = do_getsockopt(arg1, arg2, arg3, arg4, arg5);                                                                                                // 0.0
/*2568 */         break;                                                                                                                                            // 0.0
/*2570 */ #endif                                                                                                                                                    // 0.0
/*2572 */ #ifdef TARGET_NR_listen                                                                                                                                   // 0.0
/*2574 */     case TARGET_NR_listen:                                                                                                                                // 0.0
/*2576 */         ret = get_errno(listen(arg1, arg2));                                                                                                              // 0.0
/*2578 */         break;                                                                                                                                            // 0.0
/*2580 */ #endif                                                                                                                                                    // 0.0
/*2582 */ #ifdef TARGET_NR_recv                                                                                                                                     // 0.0
/*2584 */     case TARGET_NR_recv:                                                                                                                                  // 0.0
/*2586 */         ret = do_recvfrom(arg1, arg2, arg3, arg4, 0, 0);                                                                                                  // 0.0
/*2588 */         break;                                                                                                                                            // 0.0
/*2590 */ #endif                                                                                                                                                    // 0.0
/*2592 */ #ifdef TARGET_NR_recvfrom                                                                                                                                 // 0.0
/*2594 */     case TARGET_NR_recvfrom:                                                                                                                              // 0.0
/*2596 */         ret = do_recvfrom(arg1, arg2, arg3, arg4, arg5, arg6);                                                                                            // 0.0
/*2598 */         break;                                                                                                                                            // 0.0
/*2600 */ #endif                                                                                                                                                    // 0.0
/*2602 */ #ifdef TARGET_NR_recvmsg                                                                                                                                  // 0.0
/*2604 */     case TARGET_NR_recvmsg:                                                                                                                               // 0.0
/*2606 */         ret = do_sendrecvmsg(arg1, arg2, arg3, 0);                                                                                                        // 0.0
/*2608 */         break;                                                                                                                                            // 0.0
/*2610 */ #endif                                                                                                                                                    // 0.0
/*2612 */ #ifdef TARGET_NR_send                                                                                                                                     // 0.0
/*2614 */     case TARGET_NR_send:                                                                                                                                  // 0.0
/*2616 */         ret = do_sendto(arg1, arg2, arg3, arg4, 0, 0);                                                                                                    // 0.0
/*2618 */         break;                                                                                                                                            // 0.0
/*2620 */ #endif                                                                                                                                                    // 0.0
/*2622 */ #ifdef TARGET_NR_sendmsg                                                                                                                                  // 0.0
/*2624 */     case TARGET_NR_sendmsg:                                                                                                                               // 0.0
/*2626 */         ret = do_sendrecvmsg(arg1, arg2, arg3, 1);                                                                                                        // 0.0
/*2628 */         break;                                                                                                                                            // 0.0
/*2630 */ #endif                                                                                                                                                    // 0.0
/*2632 */ #ifdef TARGET_NR_sendto                                                                                                                                   // 0.0
/*2634 */     case TARGET_NR_sendto:                                                                                                                                // 0.0
/*2636 */         ret = do_sendto(arg1, arg2, arg3, arg4, arg5, arg6);                                                                                              // 0.0
/*2638 */         break;                                                                                                                                            // 0.0
/*2640 */ #endif                                                                                                                                                    // 0.0
/*2642 */ #ifdef TARGET_NR_shutdown                                                                                                                                 // 0.0
/*2644 */     case TARGET_NR_shutdown:                                                                                                                              // 0.0
/*2646 */         ret = get_errno(shutdown(arg1, arg2));                                                                                                            // 0.0
/*2648 */         break;                                                                                                                                            // 0.0
/*2650 */ #endif                                                                                                                                                    // 0.0
/*2652 */ #ifdef TARGET_NR_socket                                                                                                                                   // 0.0
/*2654 */     case TARGET_NR_socket:                                                                                                                                // 0.0
/*2656 */         ret = do_socket(arg1, arg2, arg3);                                                                                                                // 0.0
/*2658 */         break;                                                                                                                                            // 0.0
/*2660 */ #endif                                                                                                                                                    // 0.0
/*2662 */ #ifdef TARGET_NR_socketpair                                                                                                                               // 0.0
/*2664 */     case TARGET_NR_socketpair:                                                                                                                            // 0.0
/*2666 */         ret = do_socketpair(arg1, arg2, arg3, arg4);                                                                                                      // 0.0
/*2668 */         break;                                                                                                                                            // 0.0
/*2670 */ #endif                                                                                                                                                    // 0.0
/*2672 */ #ifdef TARGET_NR_setsockopt                                                                                                                               // 0.0
/*2674 */     case TARGET_NR_setsockopt:                                                                                                                            // 0.0
/*2676 */         ret = do_setsockopt(arg1, arg2, arg3, arg4, (socklen_t) arg5);                                                                                    // 0.0
/*2678 */         break;                                                                                                                                            // 0.0
/*2680 */ #endif                                                                                                                                                    // 0.0
/*2684 */     case TARGET_NR_syslog:                                                                                                                                // 0.0
/*2686 */         if (!(p = lock_user_string(arg2)))                                                                                                                // 0.0
/*2688 */             goto efault;                                                                                                                                  // 0.0
/*2690 */         ret = get_errno(sys_syslog((int)arg1, p, (int)arg3));                                                                                             // 0.0
/*2692 */         unlock_user(p, arg2, 0);                                                                                                                          // 0.0
/*2694 */         break;                                                                                                                                            // 0.0
/*2698 */     case TARGET_NR_setitimer:                                                                                                                             // 0.0
/*2700 */         {                                                                                                                                                 // 0.0
/*2702 */             struct itimerval value, ovalue, *pvalue;                                                                                                      // 0.0
/*2706 */             if (arg2) {                                                                                                                                   // 0.0
/*2708 */                 pvalue = &value;                                                                                                                          // 0.0
/*2710 */                 if (copy_from_user_timeval(&pvalue->it_interval, arg2)                                                                                    // 0.0
/*2712 */                     || copy_from_user_timeval(&pvalue->it_value,                                                                                          // 0.0
/*2714 */                                               arg2 + sizeof(struct target_timeval)))                                                                      // 0.0
/*2716 */                     goto efault;                                                                                                                          // 0.0
/*2718 */             } else {                                                                                                                                      // 0.0
/*2720 */                 pvalue = NULL;                                                                                                                            // 0.0
/*2722 */             }                                                                                                                                             // 0.0
/*2724 */             ret = get_errno(setitimer(arg1, pvalue, &ovalue));                                                                                            // 0.0
/*2726 */             if (!is_error(ret) && arg3) {                                                                                                                 // 0.0
/*2728 */                 if (copy_to_user_timeval(arg3,                                                                                                            // 0.0
/*2730 */                                          &ovalue.it_interval)                                                                                             // 0.0
/*2732 */                     || copy_to_user_timeval(arg3 + sizeof(struct target_timeval),                                                                         // 0.0
/*2734 */                                             &ovalue.it_value))                                                                                            // 0.0
/*2736 */                     goto efault;                                                                                                                          // 0.0
/*2738 */             }                                                                                                                                             // 0.0
/*2740 */         }                                                                                                                                                 // 0.0
/*2742 */         break;                                                                                                                                            // 0.0
/*2744 */     case TARGET_NR_getitimer:                                                                                                                             // 0.0
/*2746 */         {                                                                                                                                                 // 0.0
/*2748 */             struct itimerval value;                                                                                                                       // 0.0
/*2752 */             ret = get_errno(getitimer(arg1, &value));                                                                                                     // 0.0
/*2754 */             if (!is_error(ret) && arg2) {                                                                                                                 // 0.0
/*2756 */                 if (copy_to_user_timeval(arg2,                                                                                                            // 0.0
/*2758 */                                          &value.it_interval)                                                                                              // 0.0
/*2760 */                     || copy_to_user_timeval(arg2 + sizeof(struct target_timeval),                                                                         // 0.0
/*2762 */                                             &value.it_value))                                                                                             // 0.0
/*2764 */                     goto efault;                                                                                                                          // 0.0
/*2766 */             }                                                                                                                                             // 0.0
/*2768 */         }                                                                                                                                                 // 0.0
/*2770 */         break;                                                                                                                                            // 0.0
/*2772 */     case TARGET_NR_stat:                                                                                                                                  // 0.0
/*2774 */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*2776 */             goto efault;                                                                                                                                  // 0.0
/*2778 */         ret = get_errno(stat(path(p), &st));                                                                                                              // 0.0
/*2780 */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*2782 */         goto do_stat;                                                                                                                                     // 0.0
/*2784 */     case TARGET_NR_lstat:                                                                                                                                 // 0.0
/*2786 */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*2788 */             goto efault;                                                                                                                                  // 0.0
/*2790 */         ret = get_errno(lstat(path(p), &st));                                                                                                             // 0.0
/*2792 */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*2794 */         goto do_stat;                                                                                                                                     // 0.0
/*2796 */     case TARGET_NR_fstat:                                                                                                                                 // 0.0
/*2798 */         {                                                                                                                                                 // 0.0
/*2800 */             ret = get_errno(fstat(arg1, &st));                                                                                                            // 0.0
/*2802 */         do_stat:                                                                                                                                          // 0.0
/*2804 */             if (!is_error(ret)) {                                                                                                                         // 0.0
/*2806 */                 struct target_stat *target_st;                                                                                                            // 0.0
/*2810 */                 if (!lock_user_struct(VERIFY_WRITE, target_st, arg2, 0))                                                                                  // 0.0
/*2812 */                     goto efault;                                                                                                                          // 0.0
/*2814 */                 memset(target_st, 0, sizeof(*target_st));                                                                                                 // 0.0
/*2816 */                 __put_user(st.st_dev, &target_st->st_dev);                                                                                                // 0.0
/*2818 */                 __put_user(st.st_ino, &target_st->st_ino);                                                                                                // 0.0
/*2820 */                 __put_user(st.st_mode, &target_st->st_mode);                                                                                              // 0.0
/*2822 */                 __put_user(st.st_uid, &target_st->st_uid);                                                                                                // 0.0
/*2824 */                 __put_user(st.st_gid, &target_st->st_gid);                                                                                                // 0.0
/*2826 */                 __put_user(st.st_nlink, &target_st->st_nlink);                                                                                            // 0.0
/*2828 */                 __put_user(st.st_rdev, &target_st->st_rdev);                                                                                              // 0.0
/*2830 */                 __put_user(st.st_size, &target_st->st_size);                                                                                              // 0.0
/*2832 */                 __put_user(st.st_blksize, &target_st->st_blksize);                                                                                        // 0.0
/*2834 */                 __put_user(st.st_blocks, &target_st->st_blocks);                                                                                          // 0.0
/*2836 */                 __put_user(st.st_atime, &target_st->target_st_atime);                                                                                     // 0.0
/*2838 */                 __put_user(st.st_mtime, &target_st->target_st_mtime);                                                                                     // 0.0
/*2840 */                 __put_user(st.st_ctime, &target_st->target_st_ctime);                                                                                     // 0.0
/*2842 */                 unlock_user_struct(target_st, arg2, 1);                                                                                                   // 0.0
/*2844 */             }                                                                                                                                             // 0.0
/*2846 */         }                                                                                                                                                 // 0.0
/*2848 */         break;                                                                                                                                            // 0.0
/*2850 */ #ifdef TARGET_NR_olduname                                                                                                                                 // 0.0
/*2852 */     case TARGET_NR_olduname:                                                                                                                              // 0.0
/*2854 */         goto unimplemented;                                                                                                                               // 0.0
/*2856 */ #endif                                                                                                                                                    // 0.0
/*2858 */ #ifdef TARGET_NR_iopl                                                                                                                                     // 0.0
/*2860 */     case TARGET_NR_iopl:                                                                                                                                  // 0.0
/*2862 */         goto unimplemented;                                                                                                                               // 0.0
/*2864 */ #endif                                                                                                                                                    // 0.0
/*2866 */     case TARGET_NR_vhangup:                                                                                                                               // 0.0
/*2868 */         ret = get_errno(vhangup());                                                                                                                       // 0.0
/*2870 */         break;                                                                                                                                            // 0.0
/*2872 */ #ifdef TARGET_NR_idle                                                                                                                                     // 0.0
/*2874 */     case TARGET_NR_idle:                                                                                                                                  // 0.0
/*2876 */         goto unimplemented;                                                                                                                               // 0.0
/*2878 */ #endif                                                                                                                                                    // 0.0
/*2880 */ #ifdef TARGET_NR_syscall                                                                                                                                  // 0.0
/*2882 */     case TARGET_NR_syscall:                                                                                                                               // 0.0
/*2884 */     	ret = do_syscall(cpu_env,arg1 & 0xffff,arg2,arg3,arg4,arg5,arg6,0);                                                                                  // 0.0
/*2886 */     	break;                                                                                                                                               // 0.0
/*2888 */ #endif                                                                                                                                                    // 0.0
/*2890 */     case TARGET_NR_wait4:                                                                                                                                 // 0.0
/*2892 */         {                                                                                                                                                 // 0.0
/*2894 */             int status;                                                                                                                                   // 0.0
/*2896 */             abi_long status_ptr = arg2;                                                                                                                   // 0.0
/*2898 */             struct rusage rusage, *rusage_ptr;                                                                                                            // 0.0
/*2900 */             abi_ulong target_rusage = arg4;                                                                                                               // 0.0
/*2902 */             if (target_rusage)                                                                                                                            // 0.0
/*2904 */                 rusage_ptr = &rusage;                                                                                                                     // 0.0
/*2906 */             else                                                                                                                                          // 0.0
/*2908 */                 rusage_ptr = NULL;                                                                                                                        // 0.0
/*2910 */             ret = get_errno(wait4(arg1, &status, arg3, rusage_ptr));                                                                                      // 0.0
/*2912 */             if (!is_error(ret)) {                                                                                                                         // 0.0
/*2914 */                 if (status_ptr) {                                                                                                                         // 0.0
/*2916 */                     status = host_to_target_waitstatus(status);                                                                                           // 0.0
/*2918 */                     if (put_user_s32(status, status_ptr))                                                                                                 // 0.0
/*2920 */                         goto efault;                                                                                                                      // 0.0
/*2922 */                 }                                                                                                                                         // 0.0
/*2924 */                 if (target_rusage)                                                                                                                        // 0.0
/*2926 */                     host_to_target_rusage(target_rusage, &rusage);                                                                                        // 0.0
/*2928 */             }                                                                                                                                             // 0.0
/*2930 */         }                                                                                                                                                 // 0.0
/*2932 */         break;                                                                                                                                            // 0.0
/*2934 */ #ifdef TARGET_NR_swapoff                                                                                                                                  // 0.0
/*2936 */     case TARGET_NR_swapoff:                                                                                                                               // 0.0
/*2938 */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*2940 */             goto efault;                                                                                                                                  // 0.0
/*2942 */         ret = get_errno(swapoff(p));                                                                                                                      // 0.0
/*2944 */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*2946 */         break;                                                                                                                                            // 0.0
/*2948 */ #endif                                                                                                                                                    // 0.0
/*2950 */     case TARGET_NR_sysinfo:                                                                                                                               // 0.0
/*2952 */         {                                                                                                                                                 // 0.0
/*2954 */             struct target_sysinfo *target_value;                                                                                                          // 0.0
/*2956 */             struct sysinfo value;                                                                                                                         // 0.0
/*2958 */             ret = get_errno(sysinfo(&value));                                                                                                             // 0.0
/*2960 */             if (!is_error(ret) && arg1)                                                                                                                   // 0.0
/*2962 */             {                                                                                                                                             // 0.0
/*2964 */                 if (!lock_user_struct(VERIFY_WRITE, target_value, arg1, 0))                                                                               // 0.0
/*2966 */                     goto efault;                                                                                                                          // 0.0
/*2968 */                 __put_user(value.uptime, &target_value->uptime);                                                                                          // 0.0
/*2970 */                 __put_user(value.loads[0], &target_value->loads[0]);                                                                                      // 0.0
/*2972 */                 __put_user(value.loads[1], &target_value->loads[1]);                                                                                      // 0.0
/*2974 */                 __put_user(value.loads[2], &target_value->loads[2]);                                                                                      // 0.0
/*2976 */                 __put_user(value.totalram, &target_value->totalram);                                                                                      // 0.0
/*2978 */                 __put_user(value.freeram, &target_value->freeram);                                                                                        // 0.0
/*2980 */                 __put_user(value.sharedram, &target_value->sharedram);                                                                                    // 0.0
/*2982 */                 __put_user(value.bufferram, &target_value->bufferram);                                                                                    // 0.0
/*2984 */                 __put_user(value.totalswap, &target_value->totalswap);                                                                                    // 0.0
/*2986 */                 __put_user(value.freeswap, &target_value->freeswap);                                                                                      // 0.0
/*2988 */                 __put_user(value.procs, &target_value->procs);                                                                                            // 0.0
/*2990 */                 __put_user(value.totalhigh, &target_value->totalhigh);                                                                                    // 0.0
/*2992 */                 __put_user(value.freehigh, &target_value->freehigh);                                                                                      // 0.0
/*2994 */                 __put_user(value.mem_unit, &target_value->mem_unit);                                                                                      // 0.0
/*2996 */                 unlock_user_struct(target_value, arg1, 1);                                                                                                // 0.0
/*2998 */             }                                                                                                                                             // 0.0
/*3000 */         }                                                                                                                                                 // 0.0
/*3002 */         break;                                                                                                                                            // 0.0
/*3004 */ #ifdef TARGET_NR_ipc                                                                                                                                      // 0.0
/*3006 */     case TARGET_NR_ipc:                                                                                                                                   // 0.0
/*3008 */ 	ret = do_ipc(arg1, arg2, arg3, arg4, arg5, arg6);                                                                                                        // 0.0
/*3010 */ 	break;                                                                                                                                                   // 0.0
/*3012 */ #endif                                                                                                                                                    // 0.0
/*3014 */ #ifdef TARGET_NR_semget                                                                                                                                   // 0.0
/*3016 */     case TARGET_NR_semget:                                                                                                                                // 0.0
/*3018 */         ret = get_errno(semget(arg1, arg2, arg3));                                                                                                        // 0.0
/*3020 */         break;                                                                                                                                            // 0.0
/*3022 */ #endif                                                                                                                                                    // 0.0
/*3024 */ #ifdef TARGET_NR_semop                                                                                                                                    // 0.0
/*3026 */     case TARGET_NR_semop:                                                                                                                                 // 0.0
/*3028 */         ret = get_errno(do_semop(arg1, arg2, arg3));                                                                                                      // 0.0
/*3030 */         break;                                                                                                                                            // 0.0
/*3032 */ #endif                                                                                                                                                    // 0.0
/*3034 */ #ifdef TARGET_NR_semctl                                                                                                                                   // 0.0
/*3036 */     case TARGET_NR_semctl:                                                                                                                                // 0.0
/*3038 */         ret = do_semctl(arg1, arg2, arg3, (union target_semun)(abi_ulong)arg4);                                                                           // 0.0
/*3040 */         break;                                                                                                                                            // 0.0
/*3042 */ #endif                                                                                                                                                    // 0.0
/*3044 */ #ifdef TARGET_NR_msgctl                                                                                                                                   // 0.0
/*3046 */     case TARGET_NR_msgctl:                                                                                                                                // 0.0
/*3048 */         ret = do_msgctl(arg1, arg2, arg3);                                                                                                                // 0.0
/*3050 */         break;                                                                                                                                            // 0.0
/*3052 */ #endif                                                                                                                                                    // 0.0
/*3054 */ #ifdef TARGET_NR_msgget                                                                                                                                   // 0.0
/*3056 */     case TARGET_NR_msgget:                                                                                                                                // 0.0
/*3058 */         ret = get_errno(msgget(arg1, arg2));                                                                                                              // 0.0
/*3060 */         break;                                                                                                                                            // 0.0
/*3062 */ #endif                                                                                                                                                    // 0.0
/*3064 */ #ifdef TARGET_NR_msgrcv                                                                                                                                   // 0.0
/*3066 */     case TARGET_NR_msgrcv:                                                                                                                                // 0.0
/*3068 */         ret = do_msgrcv(arg1, arg2, arg3, arg4, arg5);                                                                                                    // 0.0
/*3070 */         break;                                                                                                                                            // 0.0
/*3072 */ #endif                                                                                                                                                    // 0.0
/*3074 */ #ifdef TARGET_NR_msgsnd                                                                                                                                   // 0.0
/*3076 */     case TARGET_NR_msgsnd:                                                                                                                                // 0.0
/*3078 */         ret = do_msgsnd(arg1, arg2, arg3, arg4);                                                                                                          // 0.0
/*3080 */         break;                                                                                                                                            // 0.0
/*3082 */ #endif                                                                                                                                                    // 0.0
/*3084 */ #ifdef TARGET_NR_shmget                                                                                                                                   // 0.0
/*3086 */     case TARGET_NR_shmget:                                                                                                                                // 0.0
/*3088 */         ret = get_errno(shmget(arg1, arg2, arg3));                                                                                                        // 0.0
/*3090 */         break;                                                                                                                                            // 0.0
/*3092 */ #endif                                                                                                                                                    // 0.0
/*3094 */ #ifdef TARGET_NR_shmctl                                                                                                                                   // 0.0
/*3096 */     case TARGET_NR_shmctl:                                                                                                                                // 0.0
/*3098 */         ret = do_shmctl(arg1, arg2, arg3);                                                                                                                // 0.0
/*3100 */         break;                                                                                                                                            // 0.0
/*3102 */ #endif                                                                                                                                                    // 0.0
/*3104 */ #ifdef TARGET_NR_shmat                                                                                                                                    // 0.0
/*3106 */     case TARGET_NR_shmat:                                                                                                                                 // 0.0
/*3108 */         ret = do_shmat(arg1, arg2, arg3);                                                                                                                 // 0.0
/*3110 */         break;                                                                                                                                            // 0.0
/*3112 */ #endif                                                                                                                                                    // 0.0
/*3114 */ #ifdef TARGET_NR_shmdt                                                                                                                                    // 0.0
/*3116 */     case TARGET_NR_shmdt:                                                                                                                                 // 0.0
/*3118 */         ret = do_shmdt(arg1);                                                                                                                             // 0.0
/*3120 */         break;                                                                                                                                            // 0.0
/*3122 */ #endif                                                                                                                                                    // 0.0
/*3124 */     case TARGET_NR_fsync:                                                                                                                                 // 0.0
/*3126 */         ret = get_errno(fsync(arg1));                                                                                                                     // 0.0
/*3128 */         break;                                                                                                                                            // 0.0
/*3130 */     case TARGET_NR_clone:                                                                                                                                 // 0.0
/*3132 */ #if defined(TARGET_SH4)                                                                                                                                   // 0.0
/*3134 */         ret = get_errno(do_fork(cpu_env, arg1, arg2, arg3, arg5, arg4));                                                                                  // 0.0
/*3136 */ #elif defined(TARGET_CRIS)                                                                                                                                // 0.0
/*3138 */         ret = get_errno(do_fork(cpu_env, arg2, arg1, arg3, arg4, arg5));                                                                                  // 0.0
/*3140 */ #else                                                                                                                                                     // 0.0
/*3142 */         ret = get_errno(do_fork(cpu_env, arg1, arg2, arg3, arg4, arg5));                                                                                  // 0.0
/*3144 */ #endif                                                                                                                                                    // 0.0
/*3146 */         break;                                                                                                                                            // 0.0
/*3148 */ #ifdef __NR_exit_group                                                                                                                                    // 0.0
/*3150 */         /* new thread calls */                                                                                                                            // 0.0
/*3152 */     case TARGET_NR_exit_group:                                                                                                                            // 0.0
/*3154 */ #ifdef TARGET_GPROF                                                                                                                                       // 0.0
/*3156 */         _mcleanup();                                                                                                                                      // 0.0
/*3158 */ #endif                                                                                                                                                    // 0.0
/*3160 */         gdb_exit(cpu_env, arg1);                                                                                                                          // 0.0
/*3162 */         ret = get_errno(exit_group(arg1));                                                                                                                // 0.0
/*3164 */         break;                                                                                                                                            // 0.0
/*3166 */ #endif                                                                                                                                                    // 0.0
/*3168 */     case TARGET_NR_setdomainname:                                                                                                                         // 0.0
/*3170 */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*3172 */             goto efault;                                                                                                                                  // 0.0
/*3174 */         ret = get_errno(setdomainname(p, arg2));                                                                                                          // 0.0
/*3176 */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*3178 */         break;                                                                                                                                            // 0.0
/*3180 */     case TARGET_NR_uname:                                                                                                                                 // 0.0
/*3182 */         /* no need to transcode because we use the linux syscall */                                                                                       // 0.0
/*3184 */         {                                                                                                                                                 // 0.0
/*3186 */             struct new_utsname * buf;                                                                                                                     // 0.0
/*3190 */             if (!lock_user_struct(VERIFY_WRITE, buf, arg1, 0))                                                                                            // 0.0
/*3192 */                 goto efault;                                                                                                                              // 0.0
/*3194 */             ret = get_errno(sys_uname(buf));                                                                                                              // 0.0
/*3196 */             if (!is_error(ret)) {                                                                                                                         // 0.0
/*3198 */                 /* Overrite the native machine name with whatever is being                                                                                // 0.0
/*3200 */                    emulated. */                                                                                                                           // 0.0
/*3202 */                 strcpy (buf->machine, cpu_to_uname_machine(cpu_env));                                                                                     // 0.0
/*3204 */                 /* Allow the user to override the reported release.  */                                                                                   // 0.0
/*3206 */                 if (qemu_uname_release && *qemu_uname_release)                                                                                            // 0.0
/*3208 */                   strcpy (buf->release, qemu_uname_release);                                                                                              // 0.0
/*3210 */             }                                                                                                                                             // 0.0
/*3212 */             unlock_user_struct(buf, arg1, 1);                                                                                                             // 0.0
/*3214 */         }                                                                                                                                                 // 0.0
/*3216 */         break;                                                                                                                                            // 0.0
/*3218 */ #ifdef TARGET_I386                                                                                                                                        // 0.0
/*3220 */     case TARGET_NR_modify_ldt:                                                                                                                            // 0.0
/*3222 */         ret = do_modify_ldt(cpu_env, arg1, arg2, arg3);                                                                                                   // 0.0
/*3224 */         break;                                                                                                                                            // 0.0
/*3226 */ #if !defined(TARGET_X86_64)                                                                                                                               // 0.0
/*3228 */     case TARGET_NR_vm86old:                                                                                                                               // 0.0
/*3230 */         goto unimplemented;                                                                                                                               // 0.0
/*3232 */     case TARGET_NR_vm86:                                                                                                                                  // 0.0
/*3234 */         ret = do_vm86(cpu_env, arg1, arg2);                                                                                                               // 0.0
/*3236 */         break;                                                                                                                                            // 0.0
/*3238 */ #endif                                                                                                                                                    // 0.0
/*3240 */ #endif                                                                                                                                                    // 0.0
/*3242 */     case TARGET_NR_adjtimex:                                                                                                                              // 0.0
/*3244 */         goto unimplemented;                                                                                                                               // 0.0
/*3246 */ #ifdef TARGET_NR_create_module                                                                                                                            // 0.0
/*3248 */     case TARGET_NR_create_module:                                                                                                                         // 0.0
/*3250 */ #endif                                                                                                                                                    // 0.0
/*3252 */     case TARGET_NR_init_module:                                                                                                                           // 0.0
/*3254 */     case TARGET_NR_delete_module:                                                                                                                         // 0.0
/*3256 */ #ifdef TARGET_NR_get_kernel_syms                                                                                                                          // 0.0
/*3258 */     case TARGET_NR_get_kernel_syms:                                                                                                                       // 0.0
/*3260 */ #endif                                                                                                                                                    // 0.0
/*3262 */         goto unimplemented;                                                                                                                               // 0.0
/*3264 */     case TARGET_NR_quotactl:                                                                                                                              // 0.0
/*3266 */         goto unimplemented;                                                                                                                               // 0.0
/*3268 */     case TARGET_NR_getpgid:                                                                                                                               // 0.0
/*3270 */         ret = get_errno(getpgid(arg1));                                                                                                                   // 0.0
/*3272 */         break;                                                                                                                                            // 0.0
/*3274 */     case TARGET_NR_fchdir:                                                                                                                                // 0.0
/*3276 */         ret = get_errno(fchdir(arg1));                                                                                                                    // 0.0
/*3278 */         break;                                                                                                                                            // 0.0
/*3280 */ #ifdef TARGET_NR_bdflush /* not on x86_64 */                                                                                                              // 0.0
/*3282 */     case TARGET_NR_bdflush:                                                                                                                               // 0.0
/*3284 */         goto unimplemented;                                                                                                                               // 0.0
/*3286 */ #endif                                                                                                                                                    // 0.0
/*3288 */ #ifdef TARGET_NR_sysfs                                                                                                                                    // 0.0
/*3290 */     case TARGET_NR_sysfs:                                                                                                                                 // 0.0
/*3292 */         goto unimplemented;                                                                                                                               // 0.0
/*3294 */ #endif                                                                                                                                                    // 0.0
/*3296 */     case TARGET_NR_personality:                                                                                                                           // 0.0
/*3298 */         ret = get_errno(personality(arg1));                                                                                                               // 0.0
/*3300 */         break;                                                                                                                                            // 0.0
/*3302 */ #ifdef TARGET_NR_afs_syscall                                                                                                                              // 0.0
/*3304 */     case TARGET_NR_afs_syscall:                                                                                                                           // 0.0
/*3306 */         goto unimplemented;                                                                                                                               // 0.0
/*3308 */ #endif                                                                                                                                                    // 0.0
/*3310 */ #ifdef TARGET_NR__llseek /* Not on alpha */                                                                                                               // 0.0
/*3312 */     case TARGET_NR__llseek:                                                                                                                               // 0.0
/*3314 */         {                                                                                                                                                 // 0.0
/*3316 */ #if defined (__x86_64__)                                                                                                                                  // 0.0
/*3318 */             ret = get_errno(lseek(arg1, ((uint64_t )arg2 << 32) | arg3, arg5));                                                                           // 0.0
/*3320 */             if (put_user_s64(ret, arg4))                                                                                                                  // 0.0
/*3322 */                 goto efault;                                                                                                                              // 0.0
/*3324 */ #else                                                                                                                                                     // 0.0
/*3326 */             int64_t res;                                                                                                                                  // 0.0
/*3328 */             ret = get_errno(_llseek(arg1, arg2, arg3, &res, arg5));                                                                                       // 0.0
/*3330 */             if (put_user_s64(res, arg4))                                                                                                                  // 0.0
/*3332 */                 goto efault;                                                                                                                              // 0.0
/*3334 */ #endif                                                                                                                                                    // 0.0
/*3336 */         }                                                                                                                                                 // 0.0
/*3338 */         break;                                                                                                                                            // 0.0
/*3340 */ #endif                                                                                                                                                    // 0.0
/*3342 */     case TARGET_NR_getdents:                                                                                                                              // 0.0
/*3344 */ #if TARGET_ABI_BITS == 32 && HOST_LONG_BITS == 64                                                                                                         // 0.0
/*3346 */         {                                                                                                                                                 // 0.0
/*3348 */             struct target_dirent *target_dirp;                                                                                                            // 0.0
/*3350 */             struct linux_dirent *dirp;                                                                                                                    // 0.0
/*3352 */             abi_long count = arg3;                                                                                                                        // 0.0
/*3356 */ 	    dirp = malloc(count);                                                                                                                                // 0.0
/*3358 */ 	    if (!dirp) {                                                                                                                                         // 0.0
/*3360 */                 ret = -TARGET_ENOMEM;                                                                                                                     // 0.0
/*3362 */                 goto fail;                                                                                                                                // 0.0
/*3364 */             }                                                                                                                                             // 0.0
/*3368 */             ret = get_errno(sys_getdents(arg1, dirp, count));                                                                                             // 0.0
/*3370 */             if (!is_error(ret)) {                                                                                                                         // 0.0
/*3372 */                 struct linux_dirent *de;                                                                                                                  // 0.0
/*3374 */ 		struct target_dirent *tde;                                                                                                                              // 0.0
/*3376 */                 int len = ret;                                                                                                                            // 0.0
/*3378 */                 int reclen, treclen;                                                                                                                      // 0.0
/*3380 */ 		int count1, tnamelen;                                                                                                                                   // 0.0
/*3384 */ 		count1 = 0;                                                                                                                                             // 0.0
/*3386 */                 de = dirp;                                                                                                                                // 0.0
/*3388 */                 if (!(target_dirp = lock_user(VERIFY_WRITE, arg2, count, 0)))                                                                             // 0.0
/*3390 */                     goto efault;                                                                                                                          // 0.0
/*3392 */ 		tde = target_dirp;                                                                                                                                      // 0.0
/*3394 */                 while (len > 0) {                                                                                                                         // 0.0
/*3396 */                     reclen = de->d_reclen;                                                                                                                // 0.0
/*3398 */ 		    treclen = reclen - (2 * (sizeof(long) - sizeof(abi_long)));                                                                                         // 0.0
/*3400 */                     tde->d_reclen = tswap16(treclen);                                                                                                     // 0.0
/*3402 */                     tde->d_ino = tswapl(de->d_ino);                                                                                                       // 0.0
/*3404 */                     tde->d_off = tswapl(de->d_off);                                                                                                       // 0.0
/*3406 */ 		    tnamelen = treclen - (2 * sizeof(abi_long) + 2);                                                                                                    // 0.0
/*3408 */ 		    if (tnamelen > 256)                                                                                                                                 // 0.0
/*3410 */                         tnamelen = 256;                                                                                                                   // 0.0
/*3412 */                     /* XXX: may not be correct */                                                                                                         // 0.0
/*3414 */                     pstrcpy(tde->d_name, tnamelen, de->d_name);                                                                                           // 0.0
/*3416 */                     de = (struct linux_dirent *)((char *)de + reclen);                                                                                    // 0.0
/*3418 */                     len -= reclen;                                                                                                                        // 0.0
/*3420 */                     tde = (struct target_dirent *)((char *)tde + treclen);                                                                                // 0.0
/*3422 */ 		    count1 += treclen;                                                                                                                                  // 0.0
/*3424 */                 }                                                                                                                                         // 0.0
/*3426 */ 		ret = count1;                                                                                                                                           // 0.0
/*3428 */                 unlock_user(target_dirp, arg2, ret);                                                                                                      // 0.0
/*3430 */             }                                                                                                                                             // 0.0
/*3432 */ 	    free(dirp);                                                                                                                                          // 0.0
/*3434 */         }                                                                                                                                                 // 0.0
/*3436 */ #else                                                                                                                                                     // 0.0
/*3438 */         {                                                                                                                                                 // 0.0
/*3440 */             struct linux_dirent *dirp;                                                                                                                    // 0.0
/*3442 */             abi_long count = arg3;                                                                                                                        // 0.0
/*3446 */             if (!(dirp = lock_user(VERIFY_WRITE, arg2, count, 0)))                                                                                        // 0.0
/*3448 */                 goto efault;                                                                                                                              // 0.0
/*3450 */             ret = get_errno(sys_getdents(arg1, dirp, count));                                                                                             // 0.0
/*3452 */             if (!is_error(ret)) {                                                                                                                         // 0.0
/*3454 */                 struct linux_dirent *de;                                                                                                                  // 0.0
/*3456 */                 int len = ret;                                                                                                                            // 0.0
/*3458 */                 int reclen;                                                                                                                               // 0.0
/*3460 */                 de = dirp;                                                                                                                                // 0.0
/*3462 */                 while (len > 0) {                                                                                                                         // 0.0
/*3464 */                     reclen = de->d_reclen;                                                                                                                // 0.0
/*3466 */                     if (reclen > len)                                                                                                                     // 0.0
/*3468 */                         break;                                                                                                                            // 0.0
/*3470 */                     de->d_reclen = tswap16(reclen);                                                                                                       // 0.0
/*3472 */                     tswapls(&de->d_ino);                                                                                                                  // 0.0
/*3474 */                     tswapls(&de->d_off);                                                                                                                  // 0.0
/*3476 */                     de = (struct linux_dirent *)((char *)de + reclen);                                                                                    // 0.0
/*3478 */                     len -= reclen;                                                                                                                        // 0.0
/*3480 */                 }                                                                                                                                         // 0.0
/*3482 */             }                                                                                                                                             // 0.0
/*3484 */             unlock_user(dirp, arg2, ret);                                                                                                                 // 0.0
/*3486 */         }                                                                                                                                                 // 0.0
/*3488 */ #endif                                                                                                                                                    // 0.0
/*3490 */         break;                                                                                                                                            // 0.0
/*3492 */ #if defined(TARGET_NR_getdents64) && defined(__NR_getdents64)                                                                                             // 0.0
/*3494 */     case TARGET_NR_getdents64:                                                                                                                            // 0.0
/*3496 */         {                                                                                                                                                 // 0.0
/*3498 */             struct linux_dirent64 *dirp;                                                                                                                  // 0.0
/*3500 */             abi_long count = arg3;                                                                                                                        // 0.0
/*3502 */             if (!(dirp = lock_user(VERIFY_WRITE, arg2, count, 0)))                                                                                        // 0.0
/*3504 */                 goto efault;                                                                                                                              // 0.0
/*3506 */             ret = get_errno(sys_getdents64(arg1, dirp, count));                                                                                           // 0.0
/*3508 */             if (!is_error(ret)) {                                                                                                                         // 0.0
/*3510 */                 struct linux_dirent64 *de;                                                                                                                // 0.0
/*3512 */                 int len = ret;                                                                                                                            // 0.0
/*3514 */                 int reclen;                                                                                                                               // 0.0
/*3516 */                 de = dirp;                                                                                                                                // 0.0
/*3518 */                 while (len > 0) {                                                                                                                         // 0.0
/*3520 */                     reclen = de->d_reclen;                                                                                                                // 0.0
/*3522 */                     if (reclen > len)                                                                                                                     // 0.0
/*3524 */                         break;                                                                                                                            // 0.0
/*3526 */                     de->d_reclen = tswap16(reclen);                                                                                                       // 0.0
/*3528 */                     tswap64s((uint64_t *)&de->d_ino);                                                                                                     // 0.0
/*3530 */                     tswap64s((uint64_t *)&de->d_off);                                                                                                     // 0.0
/*3532 */                     de = (struct linux_dirent64 *)((char *)de + reclen);                                                                                  // 0.0
/*3534 */                     len -= reclen;                                                                                                                        // 0.0
/*3536 */                 }                                                                                                                                         // 0.0
/*3538 */             }                                                                                                                                             // 0.0
/*3540 */             unlock_user(dirp, arg2, ret);                                                                                                                 // 0.0
/*3542 */         }                                                                                                                                                 // 0.0
/*3544 */         break;                                                                                                                                            // 0.0
/*3546 */ #endif /* TARGET_NR_getdents64 */                                                                                                                         // 0.0
/*3548 */ #ifdef TARGET_NR__newselect                                                                                                                               // 0.0
/*3550 */     case TARGET_NR__newselect:                                                                                                                            // 0.0
/*3552 */         ret = do_select(arg1, arg2, arg3, arg4, arg5);                                                                                                    // 0.0
/*3554 */         break;                                                                                                                                            // 0.0
/*3556 */ #endif                                                                                                                                                    // 0.0
/*3558 */ #ifdef TARGET_NR_poll                                                                                                                                     // 0.0
/*3560 */     case TARGET_NR_poll:                                                                                                                                  // 0.0
/*3562 */         {                                                                                                                                                 // 0.0
/*3564 */             struct target_pollfd *target_pfd;                                                                                                             // 0.0
/*3566 */             unsigned int nfds = arg2;                                                                                                                     // 0.0
/*3568 */             int timeout = arg3;                                                                                                                           // 0.0
/*3570 */             struct pollfd *pfd;                                                                                                                           // 0.0
/*3572 */             unsigned int i;                                                                                                                               // 0.0
/*3576 */             target_pfd = lock_user(VERIFY_WRITE, arg1, sizeof(struct target_pollfd) * nfds, 1);                                                           // 0.0
/*3578 */             if (!target_pfd)                                                                                                                              // 0.0
/*3580 */                 goto efault;                                                                                                                              // 0.0
/*3582 */             pfd = alloca(sizeof(struct pollfd) * nfds);                                                                                                   // 0.0
/*3584 */             for(i = 0; i < nfds; i++) {                                                                                                                   // 0.0
/*3586 */                 pfd[i].fd = tswap32(target_pfd[i].fd);                                                                                                    // 0.0
/*3588 */                 pfd[i].events = tswap16(target_pfd[i].events);                                                                                            // 0.0
/*3590 */             }                                                                                                                                             // 0.0
/*3592 */             ret = get_errno(poll(pfd, nfds, timeout));                                                                                                    // 0.0
/*3594 */             if (!is_error(ret)) {                                                                                                                         // 0.0
/*3596 */                 for(i = 0; i < nfds; i++) {                                                                                                               // 0.0
/*3598 */                     target_pfd[i].revents = tswap16(pfd[i].revents);                                                                                      // 0.0
/*3600 */                 }                                                                                                                                         // 0.0
/*3602 */                 ret += nfds * (sizeof(struct target_pollfd)                                                                                               // 0.0
/*3604 */                                - sizeof(struct pollfd));                                                                                                  // 0.0
/*3606 */             }                                                                                                                                             // 0.0
/*3608 */             unlock_user(target_pfd, arg1, ret);                                                                                                           // 0.0
/*3610 */         }                                                                                                                                                 // 0.0
/*3612 */         break;                                                                                                                                            // 0.0
/*3614 */ #endif                                                                                                                                                    // 0.0
/*3616 */     case TARGET_NR_flock:                                                                                                                                 // 0.0
/*3618 */         /* NOTE: the flock constant seems to be the same for every                                                                                        // 0.0
/*3620 */            Linux platform */                                                                                                                              // 0.0
/*3622 */         ret = get_errno(flock(arg1, arg2));                                                                                                               // 0.0
/*3624 */         break;                                                                                                                                            // 0.0
/*3626 */     case TARGET_NR_readv:                                                                                                                                 // 0.0
/*3628 */         {                                                                                                                                                 // 0.0
/*3630 */             int count = arg3;                                                                                                                             // 0.0
/*3632 */             struct iovec *vec;                                                                                                                            // 0.0
/*3636 */             vec = alloca(count * sizeof(struct iovec));                                                                                                   // 0.0
/*3638 */             if (lock_iovec(VERIFY_WRITE, vec, arg2, count, 0) < 0)                                                                                        // 0.0
/*3640 */                 goto efault;                                                                                                                              // 0.0
/*3642 */             ret = get_errno(readv(arg1, vec, count));                                                                                                     // 0.0
/*3644 */             unlock_iovec(vec, arg2, count, 1);                                                                                                            // 0.0
/*3646 */         }                                                                                                                                                 // 0.0
/*3648 */         break;                                                                                                                                            // 0.0
/*3650 */     case TARGET_NR_writev:                                                                                                                                // 0.0
/*3652 */         {                                                                                                                                                 // 0.0
/*3654 */             int count = arg3;                                                                                                                             // 0.0
/*3656 */             struct iovec *vec;                                                                                                                            // 0.0
/*3660 */             vec = alloca(count * sizeof(struct iovec));                                                                                                   // 0.0
/*3662 */             if (lock_iovec(VERIFY_READ, vec, arg2, count, 1) < 0)                                                                                         // 0.0
/*3664 */                 goto efault;                                                                                                                              // 0.0
/*3666 */             ret = get_errno(writev(arg1, vec, count));                                                                                                    // 0.0
/*3668 */             unlock_iovec(vec, arg2, count, 0);                                                                                                            // 0.0
/*3670 */         }                                                                                                                                                 // 0.0
/*3672 */         break;                                                                                                                                            // 0.0
/*3674 */     case TARGET_NR_getsid:                                                                                                                                // 0.0
/*3676 */         ret = get_errno(getsid(arg1));                                                                                                                    // 0.0
/*3678 */         break;                                                                                                                                            // 0.0
/*3680 */ #if defined(TARGET_NR_fdatasync) /* Not on alpha (osf_datasync ?) */                                                                                      // 0.0
/*3682 */     case TARGET_NR_fdatasync:                                                                                                                             // 0.0
/*3684 */         ret = get_errno(fdatasync(arg1));                                                                                                                 // 0.0
/*3686 */         break;                                                                                                                                            // 0.0
/*3688 */ #endif                                                                                                                                                    // 0.0
/*3690 */     case TARGET_NR__sysctl:                                                                                                                               // 0.0
/*3692 */         /* We don't implement this, but ENOTDIR is always a safe                                                                                          // 0.0
/*3694 */            return value. */                                                                                                                               // 0.0
/*3696 */         ret = -TARGET_ENOTDIR;                                                                                                                            // 0.0
/*3698 */         break;                                                                                                                                            // 0.0
/*3700 */     case TARGET_NR_sched_setparam:                                                                                                                        // 0.0
/*3702 */         {                                                                                                                                                 // 0.0
/*3704 */             struct sched_param *target_schp;                                                                                                              // 0.0
/*3706 */             struct sched_param schp;                                                                                                                      // 0.0
/*3710 */             if (!lock_user_struct(VERIFY_READ, target_schp, arg2, 1))                                                                                     // 0.0
/*3712 */                 goto efault;                                                                                                                              // 0.0
/*3714 */             schp.sched_priority = tswap32(target_schp->sched_priority);                                                                                   // 0.0
/*3716 */             unlock_user_struct(target_schp, arg2, 0);                                                                                                     // 0.0
/*3718 */             ret = get_errno(sched_setparam(arg1, &schp));                                                                                                 // 0.0
/*3720 */         }                                                                                                                                                 // 0.0
/*3722 */         break;                                                                                                                                            // 0.0
/*3724 */     case TARGET_NR_sched_getparam:                                                                                                                        // 0.0
/*3726 */         {                                                                                                                                                 // 0.0
/*3728 */             struct sched_param *target_schp;                                                                                                              // 0.0
/*3730 */             struct sched_param schp;                                                                                                                      // 0.0
/*3732 */             ret = get_errno(sched_getparam(arg1, &schp));                                                                                                 // 0.0
/*3734 */             if (!is_error(ret)) {                                                                                                                         // 0.0
/*3736 */                 if (!lock_user_struct(VERIFY_WRITE, target_schp, arg2, 0))                                                                                // 0.0
/*3738 */                     goto efault;                                                                                                                          // 0.0
/*3740 */                 target_schp->sched_priority = tswap32(schp.sched_priority);                                                                               // 0.0
/*3742 */                 unlock_user_struct(target_schp, arg2, 1);                                                                                                 // 0.0
/*3744 */             }                                                                                                                                             // 0.0
/*3746 */         }                                                                                                                                                 // 0.0
/*3748 */         break;                                                                                                                                            // 0.0
/*3750 */     case TARGET_NR_sched_setscheduler:                                                                                                                    // 0.0
/*3752 */         {                                                                                                                                                 // 0.0
/*3754 */             struct sched_param *target_schp;                                                                                                              // 0.0
/*3756 */             struct sched_param schp;                                                                                                                      // 0.0
/*3758 */             if (!lock_user_struct(VERIFY_READ, target_schp, arg3, 1))                                                                                     // 0.0
/*3760 */                 goto efault;                                                                                                                              // 0.0
/*3762 */             schp.sched_priority = tswap32(target_schp->sched_priority);                                                                                   // 0.0
/*3764 */             unlock_user_struct(target_schp, arg3, 0);                                                                                                     // 0.0
/*3766 */             ret = get_errno(sched_setscheduler(arg1, arg2, &schp));                                                                                       // 0.0
/*3768 */         }                                                                                                                                                 // 0.0
/*3770 */         break;                                                                                                                                            // 0.0
/*3772 */     case TARGET_NR_sched_getscheduler:                                                                                                                    // 0.0
/*3774 */         ret = get_errno(sched_getscheduler(arg1));                                                                                                        // 0.0
/*3776 */         break;                                                                                                                                            // 0.0
/*3778 */     case TARGET_NR_sched_yield:                                                                                                                           // 0.0
/*3780 */         ret = get_errno(sched_yield());                                                                                                                   // 0.0
/*3782 */         break;                                                                                                                                            // 0.0
/*3784 */     case TARGET_NR_sched_get_priority_max:                                                                                                                // 0.0
/*3786 */         ret = get_errno(sched_get_priority_max(arg1));                                                                                                    // 0.0
/*3788 */         break;                                                                                                                                            // 0.0
/*3790 */     case TARGET_NR_sched_get_priority_min:                                                                                                                // 0.0
/*3792 */         ret = get_errno(sched_get_priority_min(arg1));                                                                                                    // 0.0
/*3794 */         break;                                                                                                                                            // 0.0
/*3796 */     case TARGET_NR_sched_rr_get_interval:                                                                                                                 // 0.0
/*3798 */         {                                                                                                                                                 // 0.0
/*3800 */             struct timespec ts;                                                                                                                           // 0.0
/*3802 */             ret = get_errno(sched_rr_get_interval(arg1, &ts));                                                                                            // 0.0
/*3804 */             if (!is_error(ret)) {                                                                                                                         // 0.0
/*3806 */                 host_to_target_timespec(arg2, &ts);                                                                                                       // 0.0
/*3808 */             }                                                                                                                                             // 0.0
/*3810 */         }                                                                                                                                                 // 0.0
/*3812 */         break;                                                                                                                                            // 0.0
/*3814 */     case TARGET_NR_nanosleep:                                                                                                                             // 0.0
/*3816 */         {                                                                                                                                                 // 0.0
/*3818 */             struct timespec req, rem;                                                                                                                     // 0.0
/*3820 */             target_to_host_timespec(&req, arg1);                                                                                                          // 0.0
/*3822 */             ret = get_errno(nanosleep(&req, &rem));                                                                                                       // 0.0
/*3824 */             if (is_error(ret) && arg2) {                                                                                                                  // 0.0
/*3826 */                 host_to_target_timespec(arg2, &rem);                                                                                                      // 0.0
/*3828 */             }                                                                                                                                             // 0.0
/*3830 */         }                                                                                                                                                 // 0.0
/*3832 */         break;                                                                                                                                            // 0.0
/*3834 */ #ifdef TARGET_NR_query_module                                                                                                                             // 0.0
/*3836 */     case TARGET_NR_query_module:                                                                                                                          // 0.0
/*3838 */         goto unimplemented;                                                                                                                               // 0.0
/*3840 */ #endif                                                                                                                                                    // 0.0
/*3842 */ #ifdef TARGET_NR_nfsservctl                                                                                                                               // 0.0
/*3844 */     case TARGET_NR_nfsservctl:                                                                                                                            // 0.0
/*3846 */         goto unimplemented;                                                                                                                               // 0.0
/*3848 */ #endif                                                                                                                                                    // 0.0
/*3850 */     case TARGET_NR_prctl:                                                                                                                                 // 0.0
/*3852 */         switch (arg1)                                                                                                                                     // 0.0
/*3854 */             {                                                                                                                                             // 0.0
/*3856 */             case PR_GET_PDEATHSIG:                                                                                                                        // 0.0
/*3858 */                 {                                                                                                                                         // 0.0
/*3860 */                     int deathsig;                                                                                                                         // 0.0
/*3862 */                     ret = get_errno(prctl(arg1, &deathsig, arg3, arg4, arg5));                                                                            // 0.0
/*3864 */                     if (!is_error(ret) && arg2                                                                                                            // 0.0
/*3866 */                         && put_user_ual(deathsig, arg2))                                                                                                  // 0.0
/*3868 */                         goto efault;                                                                                                                      // 0.0
/*3870 */                 }                                                                                                                                         // 0.0
/*3872 */                 break;                                                                                                                                    // 0.0
/*3874 */             default:                                                                                                                                      // 0.0
/*3876 */                 ret = get_errno(prctl(arg1, arg2, arg3, arg4, arg5));                                                                                     // 0.0
/*3878 */                 break;                                                                                                                                    // 0.0
/*3880 */             }                                                                                                                                             // 0.0
/*3882 */         break;                                                                                                                                            // 0.0
/*3884 */ #ifdef TARGET_NR_arch_prctl                                                                                                                               // 0.0
/*3886 */     case TARGET_NR_arch_prctl:                                                                                                                            // 0.0
/*3888 */ #if defined(TARGET_I386) && !defined(TARGET_ABI32)                                                                                                        // 0.0
/*3890 */         ret = do_arch_prctl(cpu_env, arg1, arg2);                                                                                                         // 0.0
/*3892 */         break;                                                                                                                                            // 0.0
/*3894 */ #else                                                                                                                                                     // 0.0
/*3896 */         goto unimplemented;                                                                                                                               // 0.0
/*3898 */ #endif                                                                                                                                                    // 0.0
/*3900 */ #endif                                                                                                                                                    // 0.0
/*3902 */ #ifdef TARGET_NR_pread                                                                                                                                    // 0.0
/*3904 */     case TARGET_NR_pread:                                                                                                                                 // 0.0
/*3906 */ #ifdef TARGET_ARM                                                                                                                                         // 0.0
/*3908 */         if (((CPUARMState *)cpu_env)->eabi)                                                                                                               // 0.0
/*3910 */             arg4 = arg5;                                                                                                                                  // 0.0
/*3912 */ #endif                                                                                                                                                    // 0.0
/*3914 */         if (!(p = lock_user(VERIFY_WRITE, arg2, arg3, 0)))                                                                                                // 0.0
/*3916 */             goto efault;                                                                                                                                  // 0.0
/*3918 */         ret = get_errno(pread(arg1, p, arg3, arg4));                                                                                                      // 0.0
/*3920 */         unlock_user(p, arg2, ret);                                                                                                                        // 0.0
/*3922 */         break;                                                                                                                                            // 0.0
/*3924 */     case TARGET_NR_pwrite:                                                                                                                                // 0.0
/*3926 */ #ifdef TARGET_ARM                                                                                                                                         // 0.0
/*3928 */         if (((CPUARMState *)cpu_env)->eabi)                                                                                                               // 0.0
/*3930 */             arg4 = arg5;                                                                                                                                  // 0.0
/*3932 */ #endif                                                                                                                                                    // 0.0
/*3934 */         if (!(p = lock_user(VERIFY_READ, arg2, arg3, 1)))                                                                                                 // 0.0
/*3936 */             goto efault;                                                                                                                                  // 0.0
/*3938 */         ret = get_errno(pwrite(arg1, p, arg3, arg4));                                                                                                     // 0.0
/*3940 */         unlock_user(p, arg2, 0);                                                                                                                          // 0.0
/*3942 */         break;                                                                                                                                            // 0.0
/*3944 */ #endif                                                                                                                                                    // 0.0
/*3946 */ #ifdef TARGET_NR_pread64                                                                                                                                  // 0.0
/*3948 */     case TARGET_NR_pread64:                                                                                                                               // 0.0
/*3950 */         if (!(p = lock_user(VERIFY_WRITE, arg2, arg3, 0)))                                                                                                // 0.0
/*3952 */             goto efault;                                                                                                                                  // 0.0
/*3954 */         ret = get_errno(pread64(arg1, p, arg3, target_offset64(arg4, arg5)));                                                                             // 0.0
/*3956 */         unlock_user(p, arg2, ret);                                                                                                                        // 0.0
/*3958 */         break;                                                                                                                                            // 0.0
/*3960 */     case TARGET_NR_pwrite64:                                                                                                                              // 0.0
/*3962 */         if (!(p = lock_user(VERIFY_READ, arg2, arg3, 1)))                                                                                                 // 0.0
/*3964 */             goto efault;                                                                                                                                  // 0.0
/*3966 */         ret = get_errno(pwrite64(arg1, p, arg3, target_offset64(arg4, arg5)));                                                                            // 0.0
/*3968 */         unlock_user(p, arg2, 0);                                                                                                                          // 0.0
/*3970 */         break;                                                                                                                                            // 0.0
/*3972 */ #endif                                                                                                                                                    // 0.0
/*3974 */     case TARGET_NR_getcwd:                                                                                                                                // 0.0
/*3976 */         if (!(p = lock_user(VERIFY_WRITE, arg1, arg2, 0)))                                                                                                // 0.0
/*3978 */             goto efault;                                                                                                                                  // 0.0
/*3980 */         ret = get_errno(sys_getcwd1(p, arg2));                                                                                                            // 0.0
/*3982 */         unlock_user(p, arg1, ret);                                                                                                                        // 0.0
/*3984 */         break;                                                                                                                                            // 0.0
/*3986 */     case TARGET_NR_capget:                                                                                                                                // 0.0
/*3988 */         goto unimplemented;                                                                                                                               // 0.0
/*3990 */     case TARGET_NR_capset:                                                                                                                                // 0.0
/*3992 */         goto unimplemented;                                                                                                                               // 0.0
/*3994 */     case TARGET_NR_sigaltstack:                                                                                                                           // 0.0
/*3996 */ #if defined(TARGET_I386) || defined(TARGET_ARM) || defined(TARGET_MIPS) || \                                                                              // 0.0
/*3998 */     defined(TARGET_SPARC) || defined(TARGET_PPC) || defined(TARGET_ALPHA) || \                                                                            // 0.0
/*4000 */     defined(TARGET_M68K)                                                                                                                                  // 0.0
/*4002 */         ret = do_sigaltstack(arg1, arg2, get_sp_from_cpustate((CPUState *)cpu_env));                                                                      // 0.0
/*4004 */         break;                                                                                                                                            // 0.0
/*4006 */ #else                                                                                                                                                     // 0.0
/*4008 */         goto unimplemented;                                                                                                                               // 0.0
/*4010 */ #endif                                                                                                                                                    // 0.0
/*4012 */     case TARGET_NR_sendfile:                                                                                                                              // 0.0
/*4014 */         goto unimplemented;                                                                                                                               // 0.0
/*4016 */ #ifdef TARGET_NR_getpmsg                                                                                                                                  // 0.0
/*4018 */     case TARGET_NR_getpmsg:                                                                                                                               // 0.0
/*4020 */         goto unimplemented;                                                                                                                               // 0.0
/*4022 */ #endif                                                                                                                                                    // 0.0
/*4024 */ #ifdef TARGET_NR_putpmsg                                                                                                                                  // 0.0
/*4026 */     case TARGET_NR_putpmsg:                                                                                                                               // 0.0
/*4028 */         goto unimplemented;                                                                                                                               // 0.0
/*4030 */ #endif                                                                                                                                                    // 0.0
/*4032 */ #ifdef TARGET_NR_vfork                                                                                                                                    // 0.0
/*4034 */     case TARGET_NR_vfork:                                                                                                                                 // 0.0
/*4036 */         ret = get_errno(do_fork(cpu_env, CLONE_VFORK | CLONE_VM | SIGCHLD,                                                                                // 0.0
/*4038 */                         0, 0, 0, 0));                                                                                                                     // 0.0
/*4040 */         break;                                                                                                                                            // 0.0
/*4042 */ #endif                                                                                                                                                    // 0.0
/*4044 */ #ifdef TARGET_NR_ugetrlimit                                                                                                                               // 0.0
/*4046 */     case TARGET_NR_ugetrlimit:                                                                                                                            // 0.0
/*4048 */     {                                                                                                                                                     // 0.0
/*4050 */ 	struct rlimit rlim;                                                                                                                                      // 0.0
/*4052 */ 	ret = get_errno(getrlimit(arg1, &rlim));                                                                                                                 // 0.0
/*4054 */ 	if (!is_error(ret)) {                                                                                                                                    // 0.0
/*4056 */ 	    struct target_rlimit *target_rlim;                                                                                                                   // 0.0
/*4058 */             if (!lock_user_struct(VERIFY_WRITE, target_rlim, arg2, 0))                                                                                    // 0.0
/*4060 */                 goto efault;                                                                                                                              // 0.0
/*4062 */ 	    target_rlim->rlim_cur = tswapl(rlim.rlim_cur);                                                                                                       // 0.0
/*4064 */ 	    target_rlim->rlim_max = tswapl(rlim.rlim_max);                                                                                                       // 0.0
/*4066 */             unlock_user_struct(target_rlim, arg2, 1);                                                                                                     // 0.0
/*4068 */ 	}                                                                                                                                                        // 0.0
/*4070 */ 	break;                                                                                                                                                   // 0.0
/*4072 */     }                                                                                                                                                     // 0.0
/*4074 */ #endif                                                                                                                                                    // 0.0
/*4076 */ #ifdef TARGET_NR_truncate64                                                                                                                               // 0.0
/*4078 */     case TARGET_NR_truncate64:                                                                                                                            // 0.0
/*4080 */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*4082 */             goto efault;                                                                                                                                  // 0.0
/*4084 */ 	ret = target_truncate64(cpu_env, p, arg2, arg3, arg4);                                                                                                   // 0.0
/*4086 */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*4088 */ 	break;                                                                                                                                                   // 0.0
/*4090 */ #endif                                                                                                                                                    // 0.0
/*4092 */ #ifdef TARGET_NR_ftruncate64                                                                                                                              // 0.0
/*4094 */     case TARGET_NR_ftruncate64:                                                                                                                           // 0.0
/*4096 */ 	ret = target_ftruncate64(cpu_env, arg1, arg2, arg3, arg4);                                                                                               // 0.0
/*4098 */ 	break;                                                                                                                                                   // 0.0
/*4100 */ #endif                                                                                                                                                    // 0.0
/*4102 */ #ifdef TARGET_NR_stat64                                                                                                                                   // 0.0
/*4104 */     case TARGET_NR_stat64:                                                                                                                                // 0.0
/*4106 */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*4108 */             goto efault;                                                                                                                                  // 0.0
/*4110 */         ret = get_errno(stat(path(p), &st));                                                                                                              // 0.0
/*4112 */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*4114 */         if (!is_error(ret))                                                                                                                               // 0.0
/*4116 */             ret = host_to_target_stat64(cpu_env, arg2, &st);                                                                                              // 0.0
/*4118 */         break;                                                                                                                                            // 0.0
/*4120 */ #endif                                                                                                                                                    // 0.0
/*4122 */ #ifdef TARGET_NR_lstat64                                                                                                                                  // 0.0
/*4124 */     case TARGET_NR_lstat64:                                                                                                                               // 0.0
/*4126 */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*4128 */             goto efault;                                                                                                                                  // 0.0
/*4130 */         ret = get_errno(lstat(path(p), &st));                                                                                                             // 0.0
/*4132 */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*4134 */         if (!is_error(ret))                                                                                                                               // 0.0
/*4136 */             ret = host_to_target_stat64(cpu_env, arg2, &st);                                                                                              // 0.0
/*4138 */         break;                                                                                                                                            // 0.0
/*4140 */ #endif                                                                                                                                                    // 0.0
/*4142 */ #ifdef TARGET_NR_fstat64                                                                                                                                  // 0.0
/*4144 */     case TARGET_NR_fstat64:                                                                                                                               // 0.0
/*4146 */         ret = get_errno(fstat(arg1, &st));                                                                                                                // 0.0
/*4148 */         if (!is_error(ret))                                                                                                                               // 0.0
/*4150 */             ret = host_to_target_stat64(cpu_env, arg2, &st);                                                                                              // 0.0
/*4152 */         break;                                                                                                                                            // 0.0
/*4154 */ #endif                                                                                                                                                    // 0.0
/*4156 */ #if (defined(TARGET_NR_fstatat64) || defined(TARGET_NR_newfstatat)) && \                                                                                  // 0.0
/*4158 */         (defined(__NR_fstatat64) || defined(__NR_newfstatat))                                                                                             // 0.0
/*4160 */ #ifdef TARGET_NR_fstatat64                                                                                                                                // 0.0
/*4162 */     case TARGET_NR_fstatat64:                                                                                                                             // 0.0
/*4164 */ #endif                                                                                                                                                    // 0.0
/*4166 */ #ifdef TARGET_NR_newfstatat                                                                                                                               // 0.0
/*4168 */     case TARGET_NR_newfstatat:                                                                                                                            // 0.0
/*4170 */ #endif                                                                                                                                                    // 0.0
/*4172 */         if (!(p = lock_user_string(arg2)))                                                                                                                // 0.0
/*4174 */             goto efault;                                                                                                                                  // 0.0
/*4176 */ #ifdef __NR_fstatat64                                                                                                                                     // 0.0
/*4178 */         ret = get_errno(sys_fstatat64(arg1, path(p), &st, arg4));                                                                                         // 0.0
/*4180 */ #else                                                                                                                                                     // 0.0
/*4182 */         ret = get_errno(sys_newfstatat(arg1, path(p), &st, arg4));                                                                                        // 0.0
/*4184 */ #endif                                                                                                                                                    // 0.0
/*4186 */         if (!is_error(ret))                                                                                                                               // 0.0
/*4188 */             ret = host_to_target_stat64(cpu_env, arg3, &st);                                                                                              // 0.0
/*4190 */         break;                                                                                                                                            // 0.0
/*4192 */ #endif                                                                                                                                                    // 0.0
/*4194 */ #ifdef USE_UID16                                                                                                                                          // 0.0
/*4196 */     case TARGET_NR_lchown:                                                                                                                                // 0.0
/*4198 */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*4200 */             goto efault;                                                                                                                                  // 0.0
/*4202 */         ret = get_errno(lchown(p, low2highuid(arg2), low2highgid(arg3)));                                                                                 // 0.0
/*4204 */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*4206 */         break;                                                                                                                                            // 0.0
/*4208 */     case TARGET_NR_getuid:                                                                                                                                // 0.0
/*4210 */         ret = get_errno(high2lowuid(getuid()));                                                                                                           // 0.0
/*4212 */         break;                                                                                                                                            // 0.0
/*4214 */     case TARGET_NR_getgid:                                                                                                                                // 0.0
/*4216 */         ret = get_errno(high2lowgid(getgid()));                                                                                                           // 0.0
/*4218 */         break;                                                                                                                                            // 0.0
/*4220 */     case TARGET_NR_geteuid:                                                                                                                               // 0.0
/*4222 */         ret = get_errno(high2lowuid(geteuid()));                                                                                                          // 0.0
/*4224 */         break;                                                                                                                                            // 0.0
/*4226 */     case TARGET_NR_getegid:                                                                                                                               // 0.0
/*4228 */         ret = get_errno(high2lowgid(getegid()));                                                                                                          // 0.0
/*4230 */         break;                                                                                                                                            // 0.0
/*4232 */     case TARGET_NR_setreuid:                                                                                                                              // 0.0
/*4234 */         ret = get_errno(setreuid(low2highuid(arg1), low2highuid(arg2)));                                                                                  // 0.0
/*4236 */         break;                                                                                                                                            // 0.0
/*4238 */     case TARGET_NR_setregid:                                                                                                                              // 0.0
/*4240 */         ret = get_errno(setregid(low2highgid(arg1), low2highgid(arg2)));                                                                                  // 0.0
/*4242 */         break;                                                                                                                                            // 0.0
/*4244 */     case TARGET_NR_getgroups:                                                                                                                             // 0.0
/*4246 */         {                                                                                                                                                 // 0.0
/*4248 */             int gidsetsize = arg1;                                                                                                                        // 0.0
/*4250 */             uint16_t *target_grouplist;                                                                                                                   // 0.0
/*4252 */             gid_t *grouplist;                                                                                                                             // 0.0
/*4254 */             int i;                                                                                                                                        // 0.0
/*4258 */             grouplist = alloca(gidsetsize * sizeof(gid_t));                                                                                               // 0.0
/*4260 */             ret = get_errno(getgroups(gidsetsize, grouplist));                                                                                            // 0.0
/*4262 */             if (gidsetsize == 0)                                                                                                                          // 0.0
/*4264 */                 break;                                                                                                                                    // 0.0
/*4266 */             if (!is_error(ret)) {                                                                                                                         // 0.0
/*4268 */                 target_grouplist = lock_user(VERIFY_WRITE, arg2, gidsetsize * 2, 0);                                                                      // 0.0
/*4270 */                 if (!target_grouplist)                                                                                                                    // 0.0
/*4272 */                     goto efault;                                                                                                                          // 0.0
/*4274 */                 for(i = 0;i < ret; i++)                                                                                                                   // 0.0
/*4276 */                     target_grouplist[i] = tswap16(grouplist[i]);                                                                                          // 0.0
/*4278 */                 unlock_user(target_grouplist, arg2, gidsetsize * 2);                                                                                      // 0.0
/*4280 */             }                                                                                                                                             // 0.0
/*4282 */         }                                                                                                                                                 // 0.0
/*4284 */         break;                                                                                                                                            // 0.0
/*4286 */     case TARGET_NR_setgroups:                                                                                                                             // 0.0
/*4288 */         {                                                                                                                                                 // 0.0
/*4290 */             int gidsetsize = arg1;                                                                                                                        // 0.0
/*4292 */             uint16_t *target_grouplist;                                                                                                                   // 0.0
/*4294 */             gid_t *grouplist;                                                                                                                             // 0.0
/*4296 */             int i;                                                                                                                                        // 0.0
/*4300 */             grouplist = alloca(gidsetsize * sizeof(gid_t));                                                                                               // 0.0
/*4302 */             target_grouplist = lock_user(VERIFY_READ, arg2, gidsetsize * 2, 1);                                                                           // 0.0
/*4304 */             if (!target_grouplist) {                                                                                                                      // 0.0
/*4306 */                 ret = -TARGET_EFAULT;                                                                                                                     // 0.0
/*4308 */                 goto fail;                                                                                                                                // 0.0
/*4310 */             }                                                                                                                                             // 0.0
/*4312 */             for(i = 0;i < gidsetsize; i++)                                                                                                                // 0.0
/*4314 */                 grouplist[i] = tswap16(target_grouplist[i]);                                                                                              // 0.0
/*4316 */             unlock_user(target_grouplist, arg2, 0);                                                                                                       // 0.0
/*4318 */             ret = get_errno(setgroups(gidsetsize, grouplist));                                                                                            // 0.0
/*4320 */         }                                                                                                                                                 // 0.0
/*4322 */         break;                                                                                                                                            // 0.0
/*4324 */     case TARGET_NR_fchown:                                                                                                                                // 0.0
/*4326 */         ret = get_errno(fchown(arg1, low2highuid(arg2), low2highgid(arg3)));                                                                              // 0.0
/*4328 */         break;                                                                                                                                            // 0.0
/*4330 */ #if defined(TARGET_NR_fchownat) && defined(__NR_fchownat)                                                                                                 // 0.0
/*4332 */     case TARGET_NR_fchownat:                                                                                                                              // 0.0
/*4334 */         if (!(p = lock_user_string(arg2)))                                                                                                                // 0.0
/*4336 */             goto efault;                                                                                                                                  // 0.0
/*4338 */         ret = get_errno(sys_fchownat(arg1, p, low2highuid(arg3), low2highgid(arg4), arg5));                                                               // 0.0
/*4340 */         unlock_user(p, arg2, 0);                                                                                                                          // 0.0
/*4342 */         break;                                                                                                                                            // 0.0
/*4344 */ #endif                                                                                                                                                    // 0.0
/*4346 */ #ifdef TARGET_NR_setresuid                                                                                                                                // 0.0
/*4348 */     case TARGET_NR_setresuid:                                                                                                                             // 0.0
/*4350 */         ret = get_errno(setresuid(low2highuid(arg1),                                                                                                      // 0.0
/*4352 */                                   low2highuid(arg2),                                                                                                      // 0.0
/*4354 */                                   low2highuid(arg3)));                                                                                                    // 0.0
/*4356 */         break;                                                                                                                                            // 0.0
/*4358 */ #endif                                                                                                                                                    // 0.0
/*4360 */ #ifdef TARGET_NR_getresuid                                                                                                                                // 0.0
/*4362 */     case TARGET_NR_getresuid:                                                                                                                             // 0.0
/*4364 */         {                                                                                                                                                 // 0.0
/*4366 */             uid_t ruid, euid, suid;                                                                                                                       // 0.0
/*4368 */             ret = get_errno(getresuid(&ruid, &euid, &suid));                                                                                              // 0.0
/*4370 */             if (!is_error(ret)) {                                                                                                                         // 0.0
/*4372 */                 if (put_user_u16(high2lowuid(ruid), arg1)                                                                                                 // 0.0
/*4374 */                     || put_user_u16(high2lowuid(euid), arg2)                                                                                              // 0.0
/*4376 */                     || put_user_u16(high2lowuid(suid), arg3))                                                                                             // 0.0
/*4378 */                     goto efault;                                                                                                                          // 0.0
/*4380 */             }                                                                                                                                             // 0.0
/*4382 */         }                                                                                                                                                 // 0.0
/*4384 */         break;                                                                                                                                            // 0.0
/*4386 */ #endif                                                                                                                                                    // 0.0
/*4388 */ #ifdef TARGET_NR_getresgid                                                                                                                                // 0.0
/*4390 */     case TARGET_NR_setresgid:                                                                                                                             // 0.0
/*4392 */         ret = get_errno(setresgid(low2highgid(arg1),                                                                                                      // 0.0
/*4394 */                                   low2highgid(arg2),                                                                                                      // 0.0
/*4396 */                                   low2highgid(arg3)));                                                                                                    // 0.0
/*4398 */         break;                                                                                                                                            // 0.0
/*4400 */ #endif                                                                                                                                                    // 0.0
/*4402 */ #ifdef TARGET_NR_getresgid                                                                                                                                // 0.0
/*4404 */     case TARGET_NR_getresgid:                                                                                                                             // 0.0
/*4406 */         {                                                                                                                                                 // 0.0
/*4408 */             gid_t rgid, egid, sgid;                                                                                                                       // 0.0
/*4410 */             ret = get_errno(getresgid(&rgid, &egid, &sgid));                                                                                              // 0.0
/*4412 */             if (!is_error(ret)) {                                                                                                                         // 0.0
/*4414 */                 if (put_user_u16(high2lowgid(rgid), arg1)                                                                                                 // 0.0
/*4416 */                     || put_user_u16(high2lowgid(egid), arg2)                                                                                              // 0.0
/*4418 */                     || put_user_u16(high2lowgid(sgid), arg3))                                                                                             // 0.0
/*4420 */                     goto efault;                                                                                                                          // 0.0
/*4422 */             }                                                                                                                                             // 0.0
/*4424 */         }                                                                                                                                                 // 0.0
/*4426 */         break;                                                                                                                                            // 0.0
/*4428 */ #endif                                                                                                                                                    // 0.0
/*4430 */     case TARGET_NR_chown:                                                                                                                                 // 0.0
/*4432 */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*4434 */             goto efault;                                                                                                                                  // 0.0
/*4436 */         ret = get_errno(chown(p, low2highuid(arg2), low2highgid(arg3)));                                                                                  // 0.0
/*4438 */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*4440 */         break;                                                                                                                                            // 0.0
/*4442 */     case TARGET_NR_setuid:                                                                                                                                // 0.0
/*4444 */         ret = get_errno(setuid(low2highuid(arg1)));                                                                                                       // 0.0
/*4446 */         break;                                                                                                                                            // 0.0
/*4448 */     case TARGET_NR_setgid:                                                                                                                                // 0.0
/*4450 */         ret = get_errno(setgid(low2highgid(arg1)));                                                                                                       // 0.0
/*4452 */         break;                                                                                                                                            // 0.0
/*4454 */     case TARGET_NR_setfsuid:                                                                                                                              // 0.0
/*4456 */         ret = get_errno(setfsuid(arg1));                                                                                                                  // 0.0
/*4458 */         break;                                                                                                                                            // 0.0
/*4460 */     case TARGET_NR_setfsgid:                                                                                                                              // 0.0
/*4462 */         ret = get_errno(setfsgid(arg1));                                                                                                                  // 0.0
/*4464 */         break;                                                                                                                                            // 0.0
/*4466 */ #endif /* USE_UID16 */                                                                                                                                    // 0.0
/*4470 */ #ifdef TARGET_NR_lchown32                                                                                                                                 // 0.0
/*4472 */     case TARGET_NR_lchown32:                                                                                                                              // 0.0
/*4474 */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*4476 */             goto efault;                                                                                                                                  // 0.0
/*4478 */         ret = get_errno(lchown(p, arg2, arg3));                                                                                                           // 0.0
/*4480 */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*4482 */         break;                                                                                                                                            // 0.0
/*4484 */ #endif                                                                                                                                                    // 0.0
/*4486 */ #ifdef TARGET_NR_getuid32                                                                                                                                 // 0.0
/*4488 */     case TARGET_NR_getuid32:                                                                                                                              // 0.0
/*4490 */         ret = get_errno(getuid());                                                                                                                        // 0.0
/*4492 */         break;                                                                                                                                            // 0.0
/*4494 */ #endif                                                                                                                                                    // 0.0
/*4498 */ #if defined(TARGET_NR_getxuid) && defined(TARGET_ALPHA)                                                                                                   // 0.0
/*4500 */    /* Alpha specific */                                                                                                                                   // 0.0
/*4502 */     case TARGET_NR_getxuid:                                                                                                                               // 0.0
/*4504 */          {                                                                                                                                                // 0.0
/*4506 */             uid_t euid;                                                                                                                                   // 0.0
/*4508 */             euid=geteuid();                                                                                                                               // 0.0
/*4510 */             ((CPUAlphaState *)cpu_env)->ir[IR_A4]=euid;                                                                                                   // 0.0
/*4512 */          }                                                                                                                                                // 0.0
/*4514 */         ret = get_errno(getuid());                                                                                                                        // 0.0
/*4516 */         break;                                                                                                                                            // 0.0
/*4518 */ #endif                                                                                                                                                    // 0.0
/*4520 */ #if defined(TARGET_NR_getxgid) && defined(TARGET_ALPHA)                                                                                                   // 0.0
/*4522 */    /* Alpha specific */                                                                                                                                   // 0.0
/*4524 */     case TARGET_NR_getxgid:                                                                                                                               // 0.0
/*4526 */          {                                                                                                                                                // 0.0
/*4528 */             uid_t egid;                                                                                                                                   // 0.0
/*4530 */             egid=getegid();                                                                                                                               // 0.0
/*4532 */             ((CPUAlphaState *)cpu_env)->ir[IR_A4]=egid;                                                                                                   // 0.0
/*4534 */          }                                                                                                                                                // 0.0
/*4536 */         ret = get_errno(getgid());                                                                                                                        // 0.0
/*4538 */         break;                                                                                                                                            // 0.0
/*4540 */ #endif                                                                                                                                                    // 0.0
/*4542 */ #if defined(TARGET_NR_osf_getsysinfo) && defined(TARGET_ALPHA)                                                                                            // 0.0
/*4544 */     /* Alpha specific */                                                                                                                                  // 0.0
/*4546 */     case TARGET_NR_osf_getsysinfo:                                                                                                                        // 0.0
/*4548 */         ret = -TARGET_EOPNOTSUPP;                                                                                                                         // 0.0
/*4550 */         switch (arg1) {                                                                                                                                   // 0.0
/*4552 */           case TARGET_GSI_IEEE_FP_CONTROL:                                                                                                                // 0.0
/*4554 */             {                                                                                                                                             // 0.0
/*4556 */                 uint64_t swcr, fpcr = cpu_alpha_load_fpcr (cpu_env);                                                                                      // 0.0
/*4560 */                 /* Copied from linux ieee_fpcr_to_swcr.  */                                                                                               // 0.0
/*4562 */                 swcr = (fpcr >> 35) & SWCR_STATUS_MASK;                                                                                                   // 0.0
/*4564 */                 swcr |= (fpcr >> 36) & SWCR_MAP_DMZ;                                                                                                      // 0.0
/*4566 */                 swcr |= (~fpcr >> 48) & (SWCR_TRAP_ENABLE_INV                                                                                             // 0.0
/*4568 */                                         | SWCR_TRAP_ENABLE_DZE                                                                                            // 0.0
/*4570 */                                         | SWCR_TRAP_ENABLE_OVF);                                                                                          // 0.0
/*4572 */                 swcr |= (~fpcr >> 57) & (SWCR_TRAP_ENABLE_UNF                                                                                             // 0.0
/*4574 */                                         | SWCR_TRAP_ENABLE_INE);                                                                                          // 0.0
/*4576 */                 swcr |= (fpcr >> 47) & SWCR_MAP_UMZ;                                                                                                      // 0.0
/*4578 */                 swcr |= (~fpcr >> 41) & SWCR_TRAP_ENABLE_DNO;                                                                                             // 0.0
/*4582 */                 if (put_user_u64 (swcr, arg2))                                                                                                            // 0.0
/*4584 */                         goto efault;                                                                                                                      // 0.0
/*4586 */                 ret = 0;                                                                                                                                  // 0.0
/*4588 */             }                                                                                                                                             // 0.0
/*4590 */             break;                                                                                                                                        // 0.0
/*4594 */           /* case GSI_IEEE_STATE_AT_SIGNAL:                                                                                                               // 0.0
/*4596 */              -- Not implemented in linux kernel.                                                                                                          // 0.0
/*4598 */              case GSI_UACPROC:                                                                                                                            // 0.0
/*4600 */              -- Retrieves current unaligned access state; not much used.                                                                                  // 0.0
/*4602 */              case GSI_PROC_TYPE:                                                                                                                          // 0.0
/*4604 */              -- Retrieves implver information; surely not used.                                                                                           // 0.0
/*4606 */              case GSI_GET_HWRPB:                                                                                                                          // 0.0
/*4608 */              -- Grabs a copy of the HWRPB; surely not used.                                                                                               // 0.0
/*4610 */           */                                                                                                                                              // 0.0
/*4612 */         }                                                                                                                                                 // 0.0
/*4614 */         break;                                                                                                                                            // 0.0
/*4616 */ #endif                                                                                                                                                    // 0.0
/*4618 */ #if defined(TARGET_NR_osf_setsysinfo) && defined(TARGET_ALPHA)                                                                                            // 0.0
/*4620 */     /* Alpha specific */                                                                                                                                  // 0.0
/*4622 */     case TARGET_NR_osf_setsysinfo:                                                                                                                        // 0.0
/*4624 */         ret = -TARGET_EOPNOTSUPP;                                                                                                                         // 0.0
/*4626 */         switch (arg1) {                                                                                                                                   // 0.0
/*4628 */           case TARGET_SSI_IEEE_FP_CONTROL:                                                                                                                // 0.0
/*4630 */           case TARGET_SSI_IEEE_RAISE_EXCEPTION:                                                                                                           // 0.0
/*4632 */             {                                                                                                                                             // 0.0
/*4634 */                 uint64_t swcr, fpcr, orig_fpcr;                                                                                                           // 0.0
/*4638 */                 if (get_user_u64 (swcr, arg2))                                                                                                            // 0.0
/*4640 */                     goto efault;                                                                                                                          // 0.0
/*4642 */                 orig_fpcr = cpu_alpha_load_fpcr (cpu_env);                                                                                                // 0.0
/*4644 */                 fpcr = orig_fpcr & FPCR_DYN_MASK;                                                                                                         // 0.0
/*4648 */                 /* Copied from linux ieee_swcr_to_fpcr.  */                                                                                               // 0.0
/*4650 */                 fpcr |= (swcr & SWCR_STATUS_MASK) << 35;                                                                                                  // 0.0
/*4652 */                 fpcr |= (swcr & SWCR_MAP_DMZ) << 36;                                                                                                      // 0.0
/*4654 */                 fpcr |= (~swcr & (SWCR_TRAP_ENABLE_INV                                                                                                    // 0.0
/*4656 */                                   | SWCR_TRAP_ENABLE_DZE                                                                                                  // 0.0
/*4658 */                                   | SWCR_TRAP_ENABLE_OVF)) << 48;                                                                                         // 0.0
/*4660 */                 fpcr |= (~swcr & (SWCR_TRAP_ENABLE_UNF                                                                                                    // 0.0
/*4662 */                                   | SWCR_TRAP_ENABLE_INE)) << 57;                                                                                         // 0.0
/*4664 */                 fpcr |= (swcr & SWCR_MAP_UMZ ? FPCR_UNDZ | FPCR_UNFD : 0);                                                                                // 0.0
/*4666 */                 fpcr |= (~swcr & SWCR_TRAP_ENABLE_DNO) << 41;                                                                                             // 0.0
/*4670 */                 cpu_alpha_store_fpcr (cpu_env, fpcr);                                                                                                     // 0.0
/*4672 */                 ret = 0;                                                                                                                                  // 0.0
/*4676 */                 if (arg1 == TARGET_SSI_IEEE_RAISE_EXCEPTION) {                                                                                            // 0.0
/*4678 */                     /* Old exceptions are not signaled.  */                                                                                               // 0.0
/*4680 */                     fpcr &= ~(orig_fpcr & FPCR_STATUS_MASK);                                                                                              // 0.0
/*4684 */                     /* If any exceptions set by this call, and are unmasked,                                                                              // 0.0
/*4686 */                        send a signal.  */                                                                                                                 // 0.0
/*4688 */                     /* ??? FIXME */                                                                                                                       // 0.0
/*4690 */                 }                                                                                                                                         // 0.0
/*4692 */             }                                                                                                                                             // 0.0
/*4694 */             break;                                                                                                                                        // 0.0
/*4698 */           /* case SSI_NVPAIRS:                                                                                                                            // 0.0
/*4700 */              -- Used with SSIN_UACPROC to enable unaligned accesses.                                                                                      // 0.0
/*4702 */              case SSI_IEEE_STATE_AT_SIGNAL:                                                                                                               // 0.0
/*4704 */              case SSI_IEEE_IGNORE_STATE_AT_SIGNAL:                                                                                                        // 0.0
/*4706 */              -- Not implemented in linux kernel                                                                                                           // 0.0
/*4708 */           */                                                                                                                                              // 0.0
/*4710 */         }                                                                                                                                                 // 0.0
/*4712 */         break;                                                                                                                                            // 0.0
/*4714 */ #endif                                                                                                                                                    // 0.0
/*4716 */ #ifdef TARGET_NR_osf_sigprocmask                                                                                                                          // 0.0
/*4718 */     /* Alpha specific.  */                                                                                                                                // 0.0
/*4720 */     case TARGET_NR_osf_sigprocmask:                                                                                                                       // 0.0
/*4722 */         {                                                                                                                                                 // 0.0
/*4724 */             abi_ulong mask;                                                                                                                               // 0.0
/*4726 */             int how = arg1;                                                                                                                               // 0.0
/*4728 */             sigset_t set, oldset;                                                                                                                         // 0.0
/*4732 */             switch(arg1) {                                                                                                                                // 0.0
/*4734 */             case TARGET_SIG_BLOCK:                                                                                                                        // 0.0
/*4736 */                 how = SIG_BLOCK;                                                                                                                          // 0.0
/*4738 */                 break;                                                                                                                                    // 0.0
/*4740 */             case TARGET_SIG_UNBLOCK:                                                                                                                      // 0.0
/*4742 */                 how = SIG_UNBLOCK;                                                                                                                        // 0.0
/*4744 */                 break;                                                                                                                                    // 0.0
/*4746 */             case TARGET_SIG_SETMASK:                                                                                                                      // 0.0
/*4748 */                 how = SIG_SETMASK;                                                                                                                        // 0.0
/*4750 */                 break;                                                                                                                                    // 0.0
/*4752 */             default:                                                                                                                                      // 0.0
/*4754 */                 ret = -TARGET_EINVAL;                                                                                                                     // 0.0
/*4756 */                 goto fail;                                                                                                                                // 0.0
/*4758 */             }                                                                                                                                             // 0.0
/*4760 */             mask = arg2;                                                                                                                                  // 0.0
/*4762 */             target_to_host_old_sigset(&set, &mask);                                                                                                       // 0.0
/*4764 */             sigprocmask(arg1, &set, &oldset);                                                                                                             // 0.0
/*4766 */             host_to_target_old_sigset(&mask, &oldset);                                                                                                    // 0.0
/*4768 */             ret = mask;                                                                                                                                   // 0.0
/*4770 */         }                                                                                                                                                 // 0.0
/*4772 */         break;                                                                                                                                            // 0.0
/*4774 */ #endif                                                                                                                                                    // 0.0
/*4778 */ #ifdef TARGET_NR_getgid32                                                                                                                                 // 0.0
/*4780 */     case TARGET_NR_getgid32:                                                                                                                              // 0.0
/*4782 */         ret = get_errno(getgid());                                                                                                                        // 0.0
/*4784 */         break;                                                                                                                                            // 0.0
/*4786 */ #endif                                                                                                                                                    // 0.0
/*4788 */ #ifdef TARGET_NR_geteuid32                                                                                                                                // 0.0
/*4790 */     case TARGET_NR_geteuid32:                                                                                                                             // 0.0
/*4792 */         ret = get_errno(geteuid());                                                                                                                       // 0.0
/*4794 */         break;                                                                                                                                            // 0.0
/*4796 */ #endif                                                                                                                                                    // 0.0
/*4798 */ #ifdef TARGET_NR_getegid32                                                                                                                                // 0.0
/*4800 */     case TARGET_NR_getegid32:                                                                                                                             // 0.0
/*4802 */         ret = get_errno(getegid());                                                                                                                       // 0.0
/*4804 */         break;                                                                                                                                            // 0.0
/*4806 */ #endif                                                                                                                                                    // 0.0
/*4808 */ #ifdef TARGET_NR_setreuid32                                                                                                                               // 0.0
/*4810 */     case TARGET_NR_setreuid32:                                                                                                                            // 0.0
/*4812 */         ret = get_errno(setreuid(arg1, arg2));                                                                                                            // 0.0
/*4814 */         break;                                                                                                                                            // 0.0
/*4816 */ #endif                                                                                                                                                    // 0.0
/*4818 */ #ifdef TARGET_NR_setregid32                                                                                                                               // 0.0
/*4820 */     case TARGET_NR_setregid32:                                                                                                                            // 0.0
/*4822 */         ret = get_errno(setregid(arg1, arg2));                                                                                                            // 0.0
/*4824 */         break;                                                                                                                                            // 0.0
/*4826 */ #endif                                                                                                                                                    // 0.0
/*4828 */ #ifdef TARGET_NR_getgroups32                                                                                                                              // 0.0
/*4830 */     case TARGET_NR_getgroups32:                                                                                                                           // 0.0
/*4832 */         {                                                                                                                                                 // 0.0
/*4834 */             int gidsetsize = arg1;                                                                                                                        // 0.0
/*4836 */             uint32_t *target_grouplist;                                                                                                                   // 0.0
/*4838 */             gid_t *grouplist;                                                                                                                             // 0.0
/*4840 */             int i;                                                                                                                                        // 0.0
/*4844 */             grouplist = alloca(gidsetsize * sizeof(gid_t));                                                                                               // 0.0
/*4846 */             ret = get_errno(getgroups(gidsetsize, grouplist));                                                                                            // 0.0
/*4848 */             if (gidsetsize == 0)                                                                                                                          // 0.0
/*4850 */                 break;                                                                                                                                    // 0.0
/*4852 */             if (!is_error(ret)) {                                                                                                                         // 0.0
/*4854 */                 target_grouplist = lock_user(VERIFY_WRITE, arg2, gidsetsize * 4, 0);                                                                      // 0.0
/*4856 */                 if (!target_grouplist) {                                                                                                                  // 0.0
/*4858 */                     ret = -TARGET_EFAULT;                                                                                                                 // 0.0
/*4860 */                     goto fail;                                                                                                                            // 0.0
/*4862 */                 }                                                                                                                                         // 0.0
/*4864 */                 for(i = 0;i < ret; i++)                                                                                                                   // 0.0
/*4866 */                     target_grouplist[i] = tswap32(grouplist[i]);                                                                                          // 0.0
/*4868 */                 unlock_user(target_grouplist, arg2, gidsetsize * 4);                                                                                      // 0.0
/*4870 */             }                                                                                                                                             // 0.0
/*4872 */         }                                                                                                                                                 // 0.0
/*4874 */         break;                                                                                                                                            // 0.0
/*4876 */ #endif                                                                                                                                                    // 0.0
/*4878 */ #ifdef TARGET_NR_setgroups32                                                                                                                              // 0.0
/*4880 */     case TARGET_NR_setgroups32:                                                                                                                           // 0.0
/*4882 */         {                                                                                                                                                 // 0.0
/*4884 */             int gidsetsize = arg1;                                                                                                                        // 0.0
/*4886 */             uint32_t *target_grouplist;                                                                                                                   // 0.0
/*4888 */             gid_t *grouplist;                                                                                                                             // 0.0
/*4890 */             int i;                                                                                                                                        // 0.0
/*4894 */             grouplist = alloca(gidsetsize * sizeof(gid_t));                                                                                               // 0.0
/*4896 */             target_grouplist = lock_user(VERIFY_READ, arg2, gidsetsize * 4, 1);                                                                           // 0.0
/*4898 */             if (!target_grouplist) {                                                                                                                      // 0.0
/*4900 */                 ret = -TARGET_EFAULT;                                                                                                                     // 0.0
/*4902 */                 goto fail;                                                                                                                                // 0.0
/*4904 */             }                                                                                                                                             // 0.0
/*4906 */             for(i = 0;i < gidsetsize; i++)                                                                                                                // 0.0
/*4908 */                 grouplist[i] = tswap32(target_grouplist[i]);                                                                                              // 0.0
/*4910 */             unlock_user(target_grouplist, arg2, 0);                                                                                                       // 0.0
/*4912 */             ret = get_errno(setgroups(gidsetsize, grouplist));                                                                                            // 0.0
/*4914 */         }                                                                                                                                                 // 0.0
/*4916 */         break;                                                                                                                                            // 0.0
/*4918 */ #endif                                                                                                                                                    // 0.0
/*4920 */ #ifdef TARGET_NR_fchown32                                                                                                                                 // 0.0
/*4922 */     case TARGET_NR_fchown32:                                                                                                                              // 0.0
/*4924 */         ret = get_errno(fchown(arg1, arg2, arg3));                                                                                                        // 0.0
/*4926 */         break;                                                                                                                                            // 0.0
/*4928 */ #endif                                                                                                                                                    // 0.0
/*4930 */ #ifdef TARGET_NR_setresuid32                                                                                                                              // 0.0
/*4932 */     case TARGET_NR_setresuid32:                                                                                                                           // 0.0
/*4934 */         ret = get_errno(setresuid(arg1, arg2, arg3));                                                                                                     // 0.0
/*4936 */         break;                                                                                                                                            // 0.0
/*4938 */ #endif                                                                                                                                                    // 0.0
/*4940 */ #ifdef TARGET_NR_getresuid32                                                                                                                              // 0.0
/*4942 */     case TARGET_NR_getresuid32:                                                                                                                           // 0.0
/*4944 */         {                                                                                                                                                 // 0.0
/*4946 */             uid_t ruid, euid, suid;                                                                                                                       // 0.0
/*4948 */             ret = get_errno(getresuid(&ruid, &euid, &suid));                                                                                              // 0.0
/*4950 */             if (!is_error(ret)) {                                                                                                                         // 0.0
/*4952 */                 if (put_user_u32(ruid, arg1)                                                                                                              // 0.0
/*4954 */                     || put_user_u32(euid, arg2)                                                                                                           // 0.0
/*4956 */                     || put_user_u32(suid, arg3))                                                                                                          // 0.0
/*4958 */                     goto efault;                                                                                                                          // 0.0
/*4960 */             }                                                                                                                                             // 0.0
/*4962 */         }                                                                                                                                                 // 0.0
/*4964 */         break;                                                                                                                                            // 0.0
/*4966 */ #endif                                                                                                                                                    // 0.0
/*4968 */ #ifdef TARGET_NR_setresgid32                                                                                                                              // 0.0
/*4970 */     case TARGET_NR_setresgid32:                                                                                                                           // 0.0
/*4972 */         ret = get_errno(setresgid(arg1, arg2, arg3));                                                                                                     // 0.0
/*4974 */         break;                                                                                                                                            // 0.0
/*4976 */ #endif                                                                                                                                                    // 0.0
/*4978 */ #ifdef TARGET_NR_getresgid32                                                                                                                              // 0.0
/*4980 */     case TARGET_NR_getresgid32:                                                                                                                           // 0.0
/*4982 */         {                                                                                                                                                 // 0.0
/*4984 */             gid_t rgid, egid, sgid;                                                                                                                       // 0.0
/*4986 */             ret = get_errno(getresgid(&rgid, &egid, &sgid));                                                                                              // 0.0
/*4988 */             if (!is_error(ret)) {                                                                                                                         // 0.0
/*4990 */                 if (put_user_u32(rgid, arg1)                                                                                                              // 0.0
/*4992 */                     || put_user_u32(egid, arg2)                                                                                                           // 0.0
/*4994 */                     || put_user_u32(sgid, arg3))                                                                                                          // 0.0
/*4996 */                     goto efault;                                                                                                                          // 0.0
/*4998 */             }                                                                                                                                             // 0.0
/*5000 */         }                                                                                                                                                 // 0.0
/*5002 */         break;                                                                                                                                            // 0.0
/*5004 */ #endif                                                                                                                                                    // 0.0
/*5006 */ #ifdef TARGET_NR_chown32                                                                                                                                  // 0.0
/*5008 */     case TARGET_NR_chown32:                                                                                                                               // 0.0
/*5010 */         if (!(p = lock_user_string(arg1)))                                                                                                                // 0.0
/*5012 */             goto efault;                                                                                                                                  // 0.0
/*5014 */         ret = get_errno(chown(p, arg2, arg3));                                                                                                            // 0.0
/*5016 */         unlock_user(p, arg1, 0);                                                                                                                          // 0.0
/*5018 */         break;                                                                                                                                            // 0.0
/*5020 */ #endif                                                                                                                                                    // 0.0
/*5022 */ #ifdef TARGET_NR_setuid32                                                                                                                                 // 0.0
/*5024 */     case TARGET_NR_setuid32:                                                                                                                              // 0.0
/*5026 */         ret = get_errno(setuid(arg1));                                                                                                                    // 0.0
/*5028 */         break;                                                                                                                                            // 0.0
/*5030 */ #endif                                                                                                                                                    // 0.0
/*5032 */ #ifdef TARGET_NR_setgid32                                                                                                                                 // 0.0
/*5034 */     case TARGET_NR_setgid32:                                                                                                                              // 0.0
/*5036 */         ret = get_errno(setgid(arg1));                                                                                                                    // 0.0
/*5038 */         break;                                                                                                                                            // 0.0
/*5040 */ #endif                                                                                                                                                    // 0.0
/*5042 */ #ifdef TARGET_NR_setfsuid32                                                                                                                               // 0.0
/*5044 */     case TARGET_NR_setfsuid32:                                                                                                                            // 0.0
/*5046 */         ret = get_errno(setfsuid(arg1));                                                                                                                  // 0.0
/*5048 */         break;                                                                                                                                            // 0.0
/*5050 */ #endif                                                                                                                                                    // 0.0
/*5052 */ #ifdef TARGET_NR_setfsgid32                                                                                                                               // 0.0
/*5054 */     case TARGET_NR_setfsgid32:                                                                                                                            // 0.0
/*5056 */         ret = get_errno(setfsgid(arg1));                                                                                                                  // 0.0
/*5058 */         break;                                                                                                                                            // 0.0
/*5060 */ #endif                                                                                                                                                    // 0.0
/*5064 */     case TARGET_NR_pivot_root:                                                                                                                            // 0.0
/*5066 */         goto unimplemented;                                                                                                                               // 0.0
/*5068 */ #ifdef TARGET_NR_mincore                                                                                                                                  // 0.0
/*5070 */     case TARGET_NR_mincore:                                                                                                                               // 0.0
/*5072 */         {                                                                                                                                                 // 0.0
/*5074 */             void *a;                                                                                                                                      // 0.0
/*5076 */             ret = -TARGET_EFAULT;                                                                                                                         // 0.0
/*5078 */             if (!(a = lock_user(VERIFY_READ, arg1,arg2, 0)))                                                                                              // 0.0
/*5080 */                 goto efault;                                                                                                                              // 0.0
/*5082 */             if (!(p = lock_user_string(arg3)))                                                                                                            // 0.0
/*5084 */                 goto mincore_fail;                                                                                                                        // 0.0
/*5086 */             ret = get_errno(mincore(a, arg2, p));                                                                                                         // 0.0
/*5088 */             unlock_user(p, arg3, ret);                                                                                                                    // 0.0
/*5090 */             mincore_fail:                                                                                                                                 // 0.0
/*5092 */             unlock_user(a, arg1, 0);                                                                                                                      // 0.0
/*5094 */         }                                                                                                                                                 // 0.0
/*5096 */         break;                                                                                                                                            // 0.0
/*5098 */ #endif                                                                                                                                                    // 0.0
/*5100 */ #ifdef TARGET_NR_arm_fadvise64_64                                                                                                                         // 0.0
/*5102 */     case TARGET_NR_arm_fadvise64_64:                                                                                                                      // 0.0
/*5104 */ 	{                                                                                                                                                        // 0.0
/*5106 */ 		/*                                                                                                                                                      // 0.0
/*5108 */ 		 * arm_fadvise64_64 looks like fadvise64_64 but                                                                                                         // 0.0
/*5110 */ 		 * with different argument order                                                                                                                        // 0.0
/*5112 */ 		 */                                                                                                                                                     // 0.0
/*5114 */ 		abi_long temp;                                                                                                                                          // 0.0
/*5116 */ 		temp = arg3;                                                                                                                                            // 0.0
/*5118 */ 		arg3 = arg4;                                                                                                                                            // 0.0
/*5120 */ 		arg4 = temp;                                                                                                                                            // 0.0
/*5122 */ 	}                                                                                                                                                        // 0.0
/*5124 */ #endif                                                                                                                                                    // 0.0
/*5126 */ #if defined(TARGET_NR_fadvise64_64) || defined(TARGET_NR_arm_fadvise64_64) || defined(TARGET_NR_fadvise64)                                                // 0.0
/*5128 */ #ifdef TARGET_NR_fadvise64_64                                                                                                                             // 0.0
/*5130 */     case TARGET_NR_fadvise64_64:                                                                                                                          // 0.0
/*5132 */ #endif                                                                                                                                                    // 0.0
/*5134 */ #ifdef TARGET_NR_fadvise64                                                                                                                                // 0.0
/*5136 */     case TARGET_NR_fadvise64:                                                                                                                             // 0.0
/*5138 */ #endif                                                                                                                                                    // 0.0
/*5140 */ #ifdef TARGET_S390X                                                                                                                                       // 0.0
/*5142 */         switch (arg4) {                                                                                                                                   // 0.0
/*5144 */         case 4: arg4 = POSIX_FADV_NOREUSE + 1; break; /* make sure it's an invalid value */                                                               // 0.0
/*5146 */         case 5: arg4 = POSIX_FADV_NOREUSE + 2; break; /* ditto */                                                                                         // 0.0
/*5148 */         case 6: arg4 = POSIX_FADV_DONTNEED; break;                                                                                                        // 0.0
/*5150 */         case 7: arg4 = POSIX_FADV_NOREUSE; break;                                                                                                         // 0.0
/*5152 */         default: break;                                                                                                                                   // 0.0
/*5154 */         }                                                                                                                                                 // 0.0
/*5156 */ #endif                                                                                                                                                    // 0.0
/*5158 */         ret = -posix_fadvise(arg1, arg2, arg3, arg4);                                                                                                     // 0.0
/*5160 */ 	break;                                                                                                                                                   // 0.0
/*5162 */ #endif                                                                                                                                                    // 0.0
/*5164 */ #ifdef TARGET_NR_madvise                                                                                                                                  // 0.0
/*5166 */     case TARGET_NR_madvise:                                                                                                                               // 0.0
/*5168 */         /* A straight passthrough may not be safe because qemu sometimes                                                                                  // 0.0
/*5170 */            turns private flie-backed mappings into anonymous mappings.                                                                                    // 0.0
/*5172 */            This will break MADV_DONTNEED.                                                                                                                 // 0.0
/*5174 */            This is a hint, so ignoring and returning success is ok.  */                                                                                   // 0.0
/*5176 */         ret = get_errno(0);                                                                                                                               // 0.0
/*5178 */         break;                                                                                                                                            // 0.0
/*5180 */ #endif                                                                                                                                                    // 0.0
/*5182 */ #if TARGET_ABI_BITS == 32                                                                                                                                 // 0.0
/*5184 */     case TARGET_NR_fcntl64:                                                                                                                               // 0.0
/*5186 */     {                                                                                                                                                     // 0.0
/*5188 */ 	int cmd;                                                                                                                                                 // 0.0
/*5190 */ 	struct flock64 fl;                                                                                                                                       // 0.0
/*5192 */ 	struct target_flock64 *target_fl;                                                                                                                        // 0.0
/*5194 */ #ifdef TARGET_ARM                                                                                                                                         // 0.0
/*5196 */ 	struct target_eabi_flock64 *target_efl;                                                                                                                  // 0.0
/*5198 */ #endif                                                                                                                                                    // 0.0
/*5202 */ 	cmd = target_to_host_fcntl_cmd(arg2);                                                                                                                    // 0.0
/*5204 */ 	if (cmd == -TARGET_EINVAL)                                                                                                                               // 0.0
/*5206 */ 		return cmd;                                                                                                                                             // 0.0
/*5210 */         switch(arg2) {                                                                                                                                    // 0.0
/*5212 */         case TARGET_F_GETLK64:                                                                                                                            // 0.0
/*5214 */ #ifdef TARGET_ARM                                                                                                                                         // 0.0
/*5216 */             if (((CPUARMState *)cpu_env)->eabi) {                                                                                                         // 0.0
/*5218 */                 if (!lock_user_struct(VERIFY_READ, target_efl, arg3, 1))                                                                                  // 0.0
/*5220 */                     goto efault;                                                                                                                          // 0.0
/*5222 */                 fl.l_type = tswap16(target_efl->l_type);                                                                                                  // 0.0
/*5224 */                 fl.l_whence = tswap16(target_efl->l_whence);                                                                                              // 0.0
/*5226 */                 fl.l_start = tswap64(target_efl->l_start);                                                                                                // 0.0
/*5228 */                 fl.l_len = tswap64(target_efl->l_len);                                                                                                    // 0.0
/*5230 */                 fl.l_pid = tswap32(target_efl->l_pid);                                                                                                    // 0.0
/*5232 */                 unlock_user_struct(target_efl, arg3, 0);                                                                                                  // 0.0
/*5234 */             } else                                                                                                                                        // 0.0
/*5236 */ #endif                                                                                                                                                    // 0.0
/*5238 */             {                                                                                                                                             // 0.0
/*5240 */                 if (!lock_user_struct(VERIFY_READ, target_fl, arg3, 1))                                                                                   // 0.0
/*5242 */                     goto efault;                                                                                                                          // 0.0
/*5244 */                 fl.l_type = tswap16(target_fl->l_type);                                                                                                   // 0.0
/*5246 */                 fl.l_whence = tswap16(target_fl->l_whence);                                                                                               // 0.0
/*5248 */                 fl.l_start = tswap64(target_fl->l_start);                                                                                                 // 0.0
/*5250 */                 fl.l_len = tswap64(target_fl->l_len);                                                                                                     // 0.0
/*5252 */                 fl.l_pid = tswap32(target_fl->l_pid);                                                                                                     // 0.0
/*5254 */                 unlock_user_struct(target_fl, arg3, 0);                                                                                                   // 0.0
/*5256 */             }                                                                                                                                             // 0.0
/*5258 */             ret = get_errno(fcntl(arg1, cmd, &fl));                                                                                                       // 0.0
/*5260 */ 	    if (ret == 0) {                                                                                                                                      // 0.0
/*5262 */ #ifdef TARGET_ARM                                                                                                                                         // 0.0
/*5264 */                 if (((CPUARMState *)cpu_env)->eabi) {                                                                                                     // 0.0
/*5266 */                     if (!lock_user_struct(VERIFY_WRITE, target_efl, arg3, 0))                                                                             // 0.0
/*5268 */                         goto efault;                                                                                                                      // 0.0
/*5270 */                     target_efl->l_type = tswap16(fl.l_type);                                                                                              // 0.0
/*5272 */                     target_efl->l_whence = tswap16(fl.l_whence);                                                                                          // 0.0
/*5274 */                     target_efl->l_start = tswap64(fl.l_start);                                                                                            // 0.0
/*5276 */                     target_efl->l_len = tswap64(fl.l_len);                                                                                                // 0.0
/*5278 */                     target_efl->l_pid = tswap32(fl.l_pid);                                                                                                // 0.0
/*5280 */                     unlock_user_struct(target_efl, arg3, 1);                                                                                              // 0.0
/*5282 */                 } else                                                                                                                                    // 0.0
/*5284 */ #endif                                                                                                                                                    // 0.0
/*5286 */                 {                                                                                                                                         // 0.0
/*5288 */                     if (!lock_user_struct(VERIFY_WRITE, target_fl, arg3, 0))                                                                              // 0.0
/*5290 */                         goto efault;                                                                                                                      // 0.0
/*5292 */                     target_fl->l_type = tswap16(fl.l_type);                                                                                               // 0.0
/*5294 */                     target_fl->l_whence = tswap16(fl.l_whence);                                                                                           // 0.0
/*5296 */                     target_fl->l_start = tswap64(fl.l_start);                                                                                             // 0.0
/*5298 */                     target_fl->l_len = tswap64(fl.l_len);                                                                                                 // 0.0
/*5300 */                     target_fl->l_pid = tswap32(fl.l_pid);                                                                                                 // 0.0
/*5302 */                     unlock_user_struct(target_fl, arg3, 1);                                                                                               // 0.0
/*5304 */                 }                                                                                                                                         // 0.0
/*5306 */ 	    }                                                                                                                                                    // 0.0
/*5308 */ 	    break;                                                                                                                                               // 0.0
/*5312 */         case TARGET_F_SETLK64:                                                                                                                            // 0.0
/*5314 */         case TARGET_F_SETLKW64:                                                                                                                           // 0.0
/*5316 */ #ifdef TARGET_ARM                                                                                                                                         // 0.0
/*5318 */             if (((CPUARMState *)cpu_env)->eabi) {                                                                                                         // 0.0
/*5320 */                 if (!lock_user_struct(VERIFY_READ, target_efl, arg3, 1))                                                                                  // 0.0
/*5322 */                     goto efault;                                                                                                                          // 0.0
/*5324 */                 fl.l_type = tswap16(target_efl->l_type);                                                                                                  // 0.0
/*5326 */                 fl.l_whence = tswap16(target_efl->l_whence);                                                                                              // 0.0
/*5328 */                 fl.l_start = tswap64(target_efl->l_start);                                                                                                // 0.0
/*5330 */                 fl.l_len = tswap64(target_efl->l_len);                                                                                                    // 0.0
/*5332 */                 fl.l_pid = tswap32(target_efl->l_pid);                                                                                                    // 0.0
/*5334 */                 unlock_user_struct(target_efl, arg3, 0);                                                                                                  // 0.0
/*5336 */             } else                                                                                                                                        // 0.0
/*5338 */ #endif                                                                                                                                                    // 0.0
/*5340 */             {                                                                                                                                             // 0.0
/*5342 */                 if (!lock_user_struct(VERIFY_READ, target_fl, arg3, 1))                                                                                   // 0.0
/*5344 */                     goto efault;                                                                                                                          // 0.0
/*5346 */                 fl.l_type = tswap16(target_fl->l_type);                                                                                                   // 0.0
/*5348 */                 fl.l_whence = tswap16(target_fl->l_whence);                                                                                               // 0.0
/*5350 */                 fl.l_start = tswap64(target_fl->l_start);                                                                                                 // 0.0
/*5352 */                 fl.l_len = tswap64(target_fl->l_len);                                                                                                     // 0.0
/*5354 */                 fl.l_pid = tswap32(target_fl->l_pid);                                                                                                     // 0.0
/*5356 */                 unlock_user_struct(target_fl, arg3, 0);                                                                                                   // 0.0
/*5358 */             }                                                                                                                                             // 0.0
/*5360 */             ret = get_errno(fcntl(arg1, cmd, &fl));                                                                                                       // 0.0
/*5362 */ 	    break;                                                                                                                                               // 0.0
/*5364 */         default:                                                                                                                                          // 0.0
/*5366 */             ret = do_fcntl(arg1, arg2, arg3);                                                                                                             // 0.0
/*5368 */             break;                                                                                                                                        // 0.0
/*5370 */         }                                                                                                                                                 // 0.0
/*5372 */ 	break;                                                                                                                                                   // 0.0
/*5374 */     }                                                                                                                                                     // 0.0
/*5376 */ #endif                                                                                                                                                    // 0.0
/*5378 */ #ifdef TARGET_NR_cacheflush                                                                                                                               // 0.0
/*5380 */     case TARGET_NR_cacheflush:                                                                                                                            // 0.0
/*5382 */         /* self-modifying code is handled automatically, so nothing needed */                                                                             // 0.0
/*5384 */         ret = 0;                                                                                                                                          // 0.0
/*5386 */         break;                                                                                                                                            // 0.0
/*5388 */ #endif                                                                                                                                                    // 0.0
/*5390 */ #ifdef TARGET_NR_security                                                                                                                                 // 0.0
/*5392 */     case TARGET_NR_security:                                                                                                                              // 0.0
/*5394 */         goto unimplemented;                                                                                                                               // 0.0
/*5396 */ #endif                                                                                                                                                    // 0.0
/*5398 */ #ifdef TARGET_NR_getpagesize                                                                                                                              // 0.0
/*5400 */     case TARGET_NR_getpagesize:                                                                                                                           // 0.0
/*5402 */         ret = TARGET_PAGE_SIZE;                                                                                                                           // 0.0
/*5404 */         break;                                                                                                                                            // 0.0
/*5406 */ #endif                                                                                                                                                    // 0.0
/*5408 */     case TARGET_NR_gettid:                                                                                                                                // 0.0
/*5410 */         ret = get_errno(gettid());                                                                                                                        // 0.0
/*5412 */         break;                                                                                                                                            // 0.0
/*5414 */ #ifdef TARGET_NR_readahead                                                                                                                                // 0.0
/*5416 */     case TARGET_NR_readahead:                                                                                                                             // 0.0
/*5418 */ #if TARGET_ABI_BITS == 32                                                                                                                                 // 0.0
/*5420 */ #ifdef TARGET_ARM                                                                                                                                         // 0.0
/*5422 */         if (((CPUARMState *)cpu_env)->eabi)                                                                                                               // 0.0
/*5424 */         {                                                                                                                                                 // 0.0
/*5426 */             arg2 = arg3;                                                                                                                                  // 0.0
/*5428 */             arg3 = arg4;                                                                                                                                  // 0.0
/*5430 */             arg4 = arg5;                                                                                                                                  // 0.0
/*5432 */         }                                                                                                                                                 // 0.0
/*5434 */ #endif                                                                                                                                                    // 0.0
/*5436 */         ret = get_errno(readahead(arg1, ((off64_t)arg3 << 32) | arg2, arg4));                                                                             // 0.0
/*5438 */ #else                                                                                                                                                     // 0.0
/*5440 */         ret = get_errno(readahead(arg1, arg2, arg3));                                                                                                     // 0.0
/*5442 */ #endif                                                                                                                                                    // 0.0
/*5444 */         break;                                                                                                                                            // 0.0
/*5446 */ #endif                                                                                                                                                    // 0.0
/*5448 */ #ifdef TARGET_NR_setxattr                                                                                                                                 // 0.0
/*5450 */     case TARGET_NR_setxattr:                                                                                                                              // 0.0
/*5452 */     case TARGET_NR_lsetxattr:                                                                                                                             // 0.0
/*5454 */     case TARGET_NR_fsetxattr:                                                                                                                             // 0.0
/*5456 */     case TARGET_NR_getxattr:                                                                                                                              // 0.0
/*5458 */     case TARGET_NR_lgetxattr:                                                                                                                             // 0.0
/*5460 */     case TARGET_NR_fgetxattr:                                                                                                                             // 0.0
/*5462 */     case TARGET_NR_listxattr:                                                                                                                             // 0.0
/*5464 */     case TARGET_NR_llistxattr:                                                                                                                            // 0.0
/*5466 */     case TARGET_NR_flistxattr:                                                                                                                            // 0.0
/*5468 */     case TARGET_NR_removexattr:                                                                                                                           // 0.0
/*5470 */     case TARGET_NR_lremovexattr:                                                                                                                          // 0.0
/*5472 */     case TARGET_NR_fremovexattr:                                                                                                                          // 0.0
/*5474 */         ret = -TARGET_EOPNOTSUPP;                                                                                                                         // 0.0
/*5476 */         break;                                                                                                                                            // 0.0
/*5478 */ #endif                                                                                                                                                    // 0.0
/*5480 */ #ifdef TARGET_NR_set_thread_area                                                                                                                          // 0.0
/*5482 */     case TARGET_NR_set_thread_area:                                                                                                                       // 0.0
/*5484 */ #if defined(TARGET_MIPS)                                                                                                                                  // 0.0
/*5486 */       ((CPUMIPSState *) cpu_env)->tls_value = arg1;                                                                                                       // 0.0
/*5488 */       ret = 0;                                                                                                                                            // 0.0
/*5490 */       break;                                                                                                                                              // 0.0
/*5492 */ #elif defined(TARGET_CRIS)                                                                                                                                // 0.0
/*5494 */       if (arg1 & 0xff)                                                                                                                                    // 0.0
/*5496 */           ret = -TARGET_EINVAL;                                                                                                                           // 0.0
/*5498 */       else {                                                                                                                                              // 0.0
/*5500 */           ((CPUCRISState *) cpu_env)->pregs[PR_PID] = arg1;                                                                                               // 0.0
/*5502 */           ret = 0;                                                                                                                                        // 0.0
/*5504 */       }                                                                                                                                                   // 0.0
/*5506 */       break;                                                                                                                                              // 0.0
/*5508 */ #elif defined(TARGET_I386) && defined(TARGET_ABI32)                                                                                                       // 0.0
/*5510 */       ret = do_set_thread_area(cpu_env, arg1);                                                                                                            // 0.0
/*5512 */       break;                                                                                                                                              // 0.0
/*5514 */ #else                                                                                                                                                     // 0.0
/*5516 */       goto unimplemented_nowarn;                                                                                                                          // 0.0
/*5518 */ #endif                                                                                                                                                    // 0.0
/*5520 */ #endif                                                                                                                                                    // 0.0
/*5522 */ #ifdef TARGET_NR_get_thread_area                                                                                                                          // 0.0
/*5524 */     case TARGET_NR_get_thread_area:                                                                                                                       // 0.0
/*5526 */ #if defined(TARGET_I386) && defined(TARGET_ABI32)                                                                                                         // 0.0
/*5528 */         ret = do_get_thread_area(cpu_env, arg1);                                                                                                          // 0.0
/*5530 */ #else                                                                                                                                                     // 0.0
/*5532 */         goto unimplemented_nowarn;                                                                                                                        // 0.0
/*5534 */ #endif                                                                                                                                                    // 0.0
/*5536 */ #endif                                                                                                                                                    // 0.0
/*5538 */ #ifdef TARGET_NR_getdomainname                                                                                                                            // 0.0
/*5540 */     case TARGET_NR_getdomainname:                                                                                                                         // 0.0
/*5542 */         goto unimplemented_nowarn;                                                                                                                        // 0.0
/*5544 */ #endif                                                                                                                                                    // 0.0
/*5548 */ #ifdef TARGET_NR_clock_gettime                                                                                                                            // 0.0
/*5550 */     case TARGET_NR_clock_gettime:                                                                                                                         // 0.0
/*5552 */     {                                                                                                                                                     // 0.0
/*5554 */         struct timespec ts;                                                                                                                               // 0.0
/*5556 */         ret = get_errno(clock_gettime(arg1, &ts));                                                                                                        // 0.0
/*5558 */         if (!is_error(ret)) {                                                                                                                             // 0.0
/*5560 */             host_to_target_timespec(arg2, &ts);                                                                                                           // 0.0
/*5562 */         }                                                                                                                                                 // 0.0
/*5564 */         break;                                                                                                                                            // 0.0
/*5566 */     }                                                                                                                                                     // 0.0
/*5568 */ #endif                                                                                                                                                    // 0.0
/*5570 */ #ifdef TARGET_NR_clock_getres                                                                                                                             // 0.0
/*5572 */     case TARGET_NR_clock_getres:                                                                                                                          // 0.0
/*5574 */     {                                                                                                                                                     // 0.0
/*5576 */         struct timespec ts;                                                                                                                               // 0.0
/*5578 */         ret = get_errno(clock_getres(arg1, &ts));                                                                                                         // 0.0
/*5580 */         if (!is_error(ret)) {                                                                                                                             // 0.0
/*5582 */             host_to_target_timespec(arg2, &ts);                                                                                                           // 0.0
/*5584 */         }                                                                                                                                                 // 0.0
/*5586 */         break;                                                                                                                                            // 0.0
/*5588 */     }                                                                                                                                                     // 0.0
/*5590 */ #endif                                                                                                                                                    // 0.0
/*5592 */ #ifdef TARGET_NR_clock_nanosleep                                                                                                                          // 0.0
/*5594 */     case TARGET_NR_clock_nanosleep:                                                                                                                       // 0.0
/*5596 */     {                                                                                                                                                     // 0.0
/*5598 */         struct timespec ts;                                                                                                                               // 0.0
/*5600 */         target_to_host_timespec(&ts, arg3);                                                                                                               // 0.0
/*5602 */         ret = get_errno(clock_nanosleep(arg1, arg2, &ts, arg4 ? &ts : NULL));                                                                             // 0.0
/*5604 */         if (arg4)                                                                                                                                         // 0.0
/*5606 */             host_to_target_timespec(arg4, &ts);                                                                                                           // 0.0
/*5608 */         break;                                                                                                                                            // 0.0
/*5610 */     }                                                                                                                                                     // 0.0
/*5612 */ #endif                                                                                                                                                    // 0.0
/*5616 */ #if defined(TARGET_NR_set_tid_address) && defined(__NR_set_tid_address)                                                                                   // 0.0
/*5618 */     case TARGET_NR_set_tid_address:                                                                                                                       // 0.0
/*5620 */         ret = get_errno(set_tid_address((int *)g2h(arg1)));                                                                                               // 0.0
/*5622 */         break;                                                                                                                                            // 0.0
/*5624 */ #endif                                                                                                                                                    // 0.0
/*5628 */ #if defined(TARGET_NR_tkill) && defined(__NR_tkill)                                                                                                       // 0.0
/*5630 */     case TARGET_NR_tkill:                                                                                                                                 // 0.0
/*5632 */         ret = get_errno(sys_tkill((int)arg1, target_to_host_signal(arg2)));                                                                               // 0.0
/*5634 */         break;                                                                                                                                            // 0.0
/*5636 */ #endif                                                                                                                                                    // 0.0
/*5640 */ #if defined(TARGET_NR_tgkill) && defined(__NR_tgkill)                                                                                                     // 0.0
/*5642 */     case TARGET_NR_tgkill:                                                                                                                                // 0.0
/*5644 */ 	ret = get_errno(sys_tgkill((int)arg1, (int)arg2,                                                                                                         // 0.0
/*5646 */                         target_to_host_signal(arg3)));                                                                                                    // 0.0
/*5648 */ 	break;                                                                                                                                                   // 0.0
/*5650 */ #endif                                                                                                                                                    // 0.0
/*5654 */ #ifdef TARGET_NR_set_robust_list                                                                                                                          // 0.0
/*5656 */     case TARGET_NR_set_robust_list:                                                                                                                       // 0.0
/*5658 */ 	goto unimplemented_nowarn;                                                                                                                               // 0.0
/*5660 */ #endif                                                                                                                                                    // 0.0
/*5664 */ #if defined(TARGET_NR_utimensat) && defined(__NR_utimensat)                                                                                               // 0.0
/*5666 */     case TARGET_NR_utimensat:                                                                                                                             // 0.0
/*5668 */         {                                                                                                                                                 // 0.0
/*5670 */             struct timespec *tsp, ts[2];                                                                                                                  // 0.0
/*5672 */             if (!arg3) {                                                                                                                                  // 0.0
/*5674 */                 tsp = NULL;                                                                                                                               // 0.0
/*5676 */             } else {                                                                                                                                      // 0.0
/*5678 */                 target_to_host_timespec(ts, arg3);                                                                                                        // 0.0
/*5680 */                 target_to_host_timespec(ts+1, arg3+sizeof(struct target_timespec));                                                                       // 0.0
/*5682 */                 tsp = ts;                                                                                                                                 // 0.0
/*5684 */             }                                                                                                                                             // 0.0
/*5686 */             if (!arg2)                                                                                                                                    // 0.0
/*5688 */                 ret = get_errno(sys_utimensat(arg1, NULL, tsp, arg4));                                                                                    // 0.0
/*5690 */             else {                                                                                                                                        // 0.0
/*5692 */                 if (!(p = lock_user_string(arg2))) {                                                                                                      // 0.0
/*5694 */                     ret = -TARGET_EFAULT;                                                                                                                 // 0.0
/*5696 */                     goto fail;                                                                                                                            // 0.0
/*5698 */                 }                                                                                                                                         // 0.0
/*5700 */                 ret = get_errno(sys_utimensat(arg1, path(p), tsp, arg4));                                                                                 // 0.0
/*5702 */                 unlock_user(p, arg2, 0);                                                                                                                  // 0.0
/*5704 */             }                                                                                                                                             // 0.0
/*5706 */         }                                                                                                                                                 // 0.0
/*5708 */ 	break;                                                                                                                                                   // 0.0
/*5710 */ #endif                                                                                                                                                    // 0.0
/*5712 */ #if defined(CONFIG_USE_NPTL)                                                                                                                              // 0.0
/*5714 */     case TARGET_NR_futex:                                                                                                                                 // 0.0
/*5716 */         ret = do_futex(arg1, arg2, arg3, arg4, arg5, arg6);                                                                                               // 0.0
/*5718 */         break;                                                                                                                                            // 0.0
/*5720 */ #endif                                                                                                                                                    // 0.0
/*5722 */ #if defined(TARGET_NR_inotify_init) && defined(__NR_inotify_init)                                                                                         // 0.0
/*5724 */     case TARGET_NR_inotify_init:                                                                                                                          // 0.0
/*5726 */         ret = get_errno(sys_inotify_init());                                                                                                              // 0.0
/*5728 */         break;                                                                                                                                            // 0.0
/*5730 */ #endif                                                                                                                                                    // 0.0
/*5732 */ #if defined(TARGET_NR_inotify_add_watch) && defined(__NR_inotify_add_watch)                                                                               // 0.0
/*5734 */     case TARGET_NR_inotify_add_watch:                                                                                                                     // 0.0
/*5736 */         p = lock_user_string(arg2);                                                                                                                       // 0.0
/*5738 */         ret = get_errno(sys_inotify_add_watch(arg1, path(p), arg3));                                                                                      // 0.0
/*5740 */         unlock_user(p, arg2, 0);                                                                                                                          // 0.0
/*5742 */         break;                                                                                                                                            // 0.0
/*5744 */ #endif                                                                                                                                                    // 0.0
/*5746 */ #if defined(TARGET_NR_inotify_rm_watch) && defined(__NR_inotify_rm_watch)                                                                                 // 0.0
/*5748 */     case TARGET_NR_inotify_rm_watch:                                                                                                                      // 0.0
/*5750 */         ret = get_errno(sys_inotify_rm_watch(arg1, arg2));                                                                                                // 0.0
/*5752 */         break;                                                                                                                                            // 0.0
/*5754 */ #endif                                                                                                                                                    // 0.0
/*5758 */ #if defined(TARGET_NR_mq_open) && defined(__NR_mq_open)                                                                                                   // 0.0
/*5760 */     case TARGET_NR_mq_open:                                                                                                                               // 0.0
/*5762 */         {                                                                                                                                                 // 0.0
/*5764 */             struct mq_attr posix_mq_attr;                                                                                                                 // 0.0
/*5768 */             p = lock_user_string(arg1 - 1);                                                                                                               // 0.0
/*5770 */             if (arg4 != 0)                                                                                                                                // 0.0
/*5772 */                 copy_from_user_mq_attr (&posix_mq_attr, arg4);                                                                                            // 0.0
/*5774 */             ret = get_errno(mq_open(p, arg2, arg3, &posix_mq_attr));                                                                                      // 0.0
/*5776 */             unlock_user (p, arg1, 0);                                                                                                                     // 0.0
/*5778 */         }                                                                                                                                                 // 0.0
/*5780 */         break;                                                                                                                                            // 0.0
/*5784 */     case TARGET_NR_mq_unlink:                                                                                                                             // 0.0
/*5786 */         p = lock_user_string(arg1 - 1);                                                                                                                   // 0.0
/*5788 */         ret = get_errno(mq_unlink(p));                                                                                                                    // 0.0
/*5790 */         unlock_user (p, arg1, 0);                                                                                                                         // 0.0
/*5792 */         break;                                                                                                                                            // 0.0
/*5796 */     case TARGET_NR_mq_timedsend:                                                                                                                          // 0.0
/*5798 */         {                                                                                                                                                 // 0.0
/*5800 */             struct timespec ts;                                                                                                                           // 0.0
/*5804 */             p = lock_user (VERIFY_READ, arg2, arg3, 1);                                                                                                   // 0.0
/*5806 */             if (arg5 != 0) {                                                                                                                              // 0.0
/*5808 */                 target_to_host_timespec(&ts, arg5);                                                                                                       // 0.0
/*5810 */                 ret = get_errno(mq_timedsend(arg1, p, arg3, arg4, &ts));                                                                                  // 0.0
/*5812 */                 host_to_target_timespec(arg5, &ts);                                                                                                       // 0.0
/*5814 */             }                                                                                                                                             // 0.0
/*5816 */             else                                                                                                                                          // 0.0
/*5818 */                 ret = get_errno(mq_send(arg1, p, arg3, arg4));                                                                                            // 0.0
/*5820 */             unlock_user (p, arg2, arg3);                                                                                                                  // 0.0
/*5822 */         }                                                                                                                                                 // 0.0
/*5824 */         break;                                                                                                                                            // 0.0
/*5828 */     case TARGET_NR_mq_timedreceive:                                                                                                                       // 0.0
/*5830 */         {                                                                                                                                                 // 0.0
/*5832 */             struct timespec ts;                                                                                                                           // 0.0
/*5834 */             unsigned int prio;                                                                                                                            // 0.0
/*5838 */             p = lock_user (VERIFY_READ, arg2, arg3, 1);                                                                                                   // 0.0
/*5840 */             if (arg5 != 0) {                                                                                                                              // 0.0
/*5842 */                 target_to_host_timespec(&ts, arg5);                                                                                                       // 0.0
/*5844 */                 ret = get_errno(mq_timedreceive(arg1, p, arg3, &prio, &ts));                                                                              // 0.0
/*5846 */                 host_to_target_timespec(arg5, &ts);                                                                                                       // 0.0
/*5848 */             }                                                                                                                                             // 0.0
/*5850 */             else                                                                                                                                          // 0.0
/*5852 */                 ret = get_errno(mq_receive(arg1, p, arg3, &prio));                                                                                        // 0.0
/*5854 */             unlock_user (p, arg2, arg3);                                                                                                                  // 0.0
/*5856 */             if (arg4 != 0)                                                                                                                                // 0.0
/*5858 */                 put_user_u32(prio, arg4);                                                                                                                 // 0.0
/*5860 */         }                                                                                                                                                 // 0.0
/*5862 */         break;                                                                                                                                            // 0.0
/*5866 */     /* Not implemented for now... */                                                                                                                      // 0.0
/*5868 */ /*     case TARGET_NR_mq_notify: */                                                                                                                       // 0.0
/*5870 */ /*         break; */                                                                                                                                      // 0.0
/*5874 */     case TARGET_NR_mq_getsetattr:                                                                                                                         // 0.0
/*5876 */         {                                                                                                                                                 // 0.0
/*5878 */             struct mq_attr posix_mq_attr_in, posix_mq_attr_out;                                                                                           // 0.0
/*5880 */             ret = 0;                                                                                                                                      // 0.0
/*5882 */             if (arg3 != 0) {                                                                                                                              // 0.0
/*5884 */                 ret = mq_getattr(arg1, &posix_mq_attr_out);                                                                                               // 0.0
/*5886 */                 copy_to_user_mq_attr(arg3, &posix_mq_attr_out);                                                                                           // 0.0
/*5888 */             }                                                                                                                                             // 0.0
/*5890 */             if (arg2 != 0) {                                                                                                                              // 0.0
/*5892 */                 copy_from_user_mq_attr(&posix_mq_attr_in, arg2);                                                                                          // 0.0
/*5894 */                 ret |= mq_setattr(arg1, &posix_mq_attr_in, &posix_mq_attr_out);                                                                           // 0.0
/*5896 */             }                                                                                                                                             // 0.0
/*5900 */         }                                                                                                                                                 // 0.0
/*5902 */         break;                                                                                                                                            // 0.0
/*5904 */ #endif                                                                                                                                                    // 0.0
/*5908 */ #ifdef CONFIG_SPLICE                                                                                                                                      // 0.0
/*5910 */ #ifdef TARGET_NR_tee                                                                                                                                      // 0.0
/*5912 */     case TARGET_NR_tee:                                                                                                                                   // 0.0
/*5914 */         {                                                                                                                                                 // 0.0
/*5916 */             ret = get_errno(tee(arg1,arg2,arg3,arg4));                                                                                                    // 0.0
/*5918 */         }                                                                                                                                                 // 0.0
/*5920 */         break;                                                                                                                                            // 0.0
/*5922 */ #endif                                                                                                                                                    // 0.0
/*5924 */ #ifdef TARGET_NR_splice                                                                                                                                   // 0.0
/*5926 */     case TARGET_NR_splice:                                                                                                                                // 0.0
/*5928 */         {                                                                                                                                                 // 0.0
/*5930 */             loff_t loff_in, loff_out;                                                                                                                     // 0.0
/*5932 */             loff_t *ploff_in = NULL, *ploff_out = NULL;                                                                                                   // 0.0
/*5934 */             if(arg2) {                                                                                                                                    // 0.0
/*5936 */                 get_user_u64(loff_in, arg2);                                                                                                              // 0.0
/*5938 */                 ploff_in = &loff_in;                                                                                                                      // 0.0
/*5940 */             }                                                                                                                                             // 0.0
/*5942 */             if(arg4) {                                                                                                                                    // 0.0
/*5944 */                 get_user_u64(loff_out, arg2);                                                                                                             // 0.0
/*5946 */                 ploff_out = &loff_out;                                                                                                                    // 0.0
/*5948 */             }                                                                                                                                             // 0.0
/*5950 */             ret = get_errno(splice(arg1, ploff_in, arg3, ploff_out, arg5, arg6));                                                                         // 0.0
/*5952 */         }                                                                                                                                                 // 0.0
/*5954 */         break;                                                                                                                                            // 0.0
/*5956 */ #endif                                                                                                                                                    // 0.0
/*5958 */ #ifdef TARGET_NR_vmsplice                                                                                                                                 // 0.0
/*5960 */ 	case TARGET_NR_vmsplice:                                                                                                                                 // 0.0
/*5962 */         {                                                                                                                                                 // 0.0
/*5964 */             int count = arg3;                                                                                                                             // 0.0
/*5966 */             struct iovec *vec;                                                                                                                            // 0.0
/*5970 */             vec = alloca(count * sizeof(struct iovec));                                                                                                   // 0.0
/*5972 */             if (lock_iovec(VERIFY_READ, vec, arg2, count, 1) < 0)                                                                                         // 0.0
/*5974 */                 goto efault;                                                                                                                              // 0.0
/*5976 */             ret = get_errno(vmsplice(arg1, vec, count, arg4));                                                                                            // 0.0
/*5978 */             unlock_iovec(vec, arg2, count, 0);                                                                                                            // 0.0
/*5980 */         }                                                                                                                                                 // 0.0
/*5982 */         break;                                                                                                                                            // 0.0
/*5984 */ #endif                                                                                                                                                    // 0.0
/*5986 */ #endif /* CONFIG_SPLICE */                                                                                                                                // 0.0
/*5988 */ #ifdef CONFIG_EVENTFD                                                                                                                                     // 0.0
/*5990 */ #if defined(TARGET_NR_eventfd)                                                                                                                            // 0.0
/*5992 */     case TARGET_NR_eventfd:                                                                                                                               // 0.0
/*5994 */         ret = get_errno(eventfd(arg1, 0));                                                                                                                // 0.0
/*5996 */         break;                                                                                                                                            // 0.0
/*5998 */ #endif                                                                                                                                                    // 0.0
/*6000 */ #if defined(TARGET_NR_eventfd2)                                                                                                                           // 0.0
/*6002 */     case TARGET_NR_eventfd2:                                                                                                                              // 0.0
/*6004 */         ret = get_errno(eventfd(arg1, arg2));                                                                                                             // 0.0
/*6006 */         break;                                                                                                                                            // 0.0
/*6008 */ #endif                                                                                                                                                    // 0.0
/*6010 */ #endif /* CONFIG_EVENTFD  */                                                                                                                              // 0.0
/*6012 */ #if defined(CONFIG_FALLOCATE) && defined(TARGET_NR_fallocate)                                                                                             // 0.0
/*6014 */     case TARGET_NR_fallocate:                                                                                                                             // 0.0
/*6016 */         ret = get_errno(fallocate(arg1, arg2, arg3, arg4));                                                                                               // 0.0
/*6018 */         break;                                                                                                                                            // 0.0
/*6020 */ #endif                                                                                                                                                    // 0.0
/*6022 */     default:                                                                                                                                              // 0.0
/*6024 */     unimplemented:                                                                                                                                        // 0.0
/*6026 */         gemu_log("qemu: Unsupported syscall: %d\n", num);                                                                                                 // 0.0
/*6028 */ #if defined(TARGET_NR_setxattr) || defined(TARGET_NR_get_thread_area) || defined(TARGET_NR_getdomainname) || defined(TARGET_NR_set_robust_list)           // 0.0
/*6030 */     unimplemented_nowarn:                                                                                                                                 // 0.0
/*6032 */ #endif                                                                                                                                                    // 0.0
/*6034 */         ret = -TARGET_ENOSYS;                                                                                                                             // 0.0
/*6036 */         break;                                                                                                                                            // 0.0
/*6038 */     }                                                                                                                                                     // 0.0
/*6040 */ fail:                                                                                                                                                     // 0.0
/*6042 */ #ifdef DEBUG                                                                                                                                              // 0.0
/*6044 */     gemu_log(" = " TARGET_ABI_FMT_ld "\n", ret);                                                                                                          // 0.0
/*6046 */ #endif                                                                                                                                                    // 0.0
/*6048 */     if(do_strace)                                                                                                                                         // 0.0
/*6050 */         print_syscall_ret(num, ret);                                                                                                                      // 0.0
/*6052 */     return ret;                                                                                                                                           // 0.0
/*6054 */ efault:                                                                                                                                                   // 0.0
/*6056 */     ret = -TARGET_EFAULT;                                                                                                                                 // 0.0
/*6058 */     goto fail;                                                                                                                                            // 0.0
/*6060 */ }                                                                                                                                                         // 0.0
