// commit message qemu@1a9353d258 (target=0, prob=0.3669511, correct=True): added loop/xadd/cmpxchg support
/*0    */ long do_syscall(void *cpu_env, int num, long arg1, long arg2, long arg3,                // (0) 0.05469
/*2    */                 long arg4, long arg5, long arg6)                                        // (4) 0.05273
/*4    */ {                                                                                       // (37) 0.001953
/*6    */     long ret;                                                                           // (32) 0.01172
/*8    */     struct stat st;                                                                     // (31) 0.01367
/*10   */     struct kernel_statfs *stfs;                                                         // (11) 0.02344
/*12   */                                                                                         // (33) 0.007813
/*14   */ #ifdef DEBUG                                                                            // (34) 0.007813
/*16   */     gemu_log("syscall %d\n", num);                                                      // (7) 0.0332
/*18   */ #endif                                                                                  // (35) 0.003906
/*20   */     switch(num) {                                                                       // (29) 0.01562
/*22   */     case TARGET_NR_exit:                                                                // (17) 0.02148
/*24   */ #ifdef HAVE_GPROF                                                                       // (28) 0.01562
/*26   */         _mcleanup();                                                                    // (13) 0.02344
/*28   */ #endif                                                                                  // (36) 0.003906
/*30   */         _exit(arg1);                                                                    // (10) 0.02539
/*32   */         ret = 0; /* avoid warning */                                                    // (9) 0.0293
/*34   */         break;                                                                          // (22) 0.01758
/*36   */     case TARGET_NR_read:                                                                // (16) 0.02148
/*38   */         ret = get_errno(read(arg1, (void *)arg2, arg3));                                // (2) 0.05469
/*40   */         break;                                                                          // (23) 0.01758
/*42   */     case TARGET_NR_write:                                                               // (18) 0.02148
/*44   */         ret = get_errno(write(arg1, (void *)arg2, arg3));                               // (1) 0.05469
/*46   */         break;                                                                          // (24) 0.01758
/*48   */     case TARGET_NR_open:                                                                // (19) 0.02148
/*50   */         ret = get_errno(open((const char *)arg1, arg2, arg3));                          // (3) 0.05469
/*52   */         break;                                                                          // (25) 0.01758
/*54   */     case TARGET_NR_close:                                                               // (20) 0.02148
/*56   */         ret = get_errno(close(arg1));                                                   // (6) 0.03711
/*58   */         break;                                                                          // (26) 0.01758
/*60   */     case TARGET_NR_brk:                                                                 // (14) 0.02344
/*62   */         ret = do_brk((char *)arg1);                                                     // (5) 0.03711
/*64   */         break;                                                                          // (27) 0.01758
/*66   */     case TARGET_NR_fork:                                                                // (15) 0.02148
/*68   */         ret = get_errno(fork());                                                        // (8) 0.03125
/*70   */         break;                                                                          // (21) 0.01758
/*72   */     case TARGET_NR_waitpid:                                                             // (12) 0.02344
/*74   */         {                                                                               // (30) 0.01562
/*76   */             int *status = (int *)arg2;                                                  // 0.0
/*78   */             ret = get_errno(waitpid(arg1, status, arg3));                               // 0.0
/*80   */             if (!is_error(ret) && status)                                               // 0.0
/*82   */                 tswapls((long *)&status);                                               // 0.0
/*84   */         }                                                                               // 0.0
/*86   */         break;                                                                          // 0.0
/*88   */     case TARGET_NR_creat:                                                               // 0.0
/*90   */         ret = get_errno(creat((const char *)arg1, arg2));                               // 0.0
/*92   */         break;                                                                          // 0.0
/*94   */     case TARGET_NR_link:                                                                // 0.0
/*96   */         ret = get_errno(link((const char *)arg1, (const char *)arg2));                  // 0.0
/*98   */         break;                                                                          // 0.0
/*100  */     case TARGET_NR_unlink:                                                              // 0.0
/*102  */         ret = get_errno(unlink((const char *)arg1));                                    // 0.0
/*104  */         break;                                                                          // 0.0
/*106  */     case TARGET_NR_execve:                                                              // 0.0
/*108  */         ret = get_errno(execve((const char *)arg1, (void *)arg2, (void *)arg3));        // 0.0
/*110  */         break;                                                                          // 0.0
/*112  */     case TARGET_NR_chdir:                                                               // 0.0
/*114  */         ret = get_errno(chdir((const char *)arg1));                                     // 0.0
/*116  */         break;                                                                          // 0.0
/*118  */     case TARGET_NR_time:                                                                // 0.0
/*120  */         {                                                                               // 0.0
/*122  */             int *time_ptr = (int *)arg1;                                                // 0.0
/*124  */             ret = get_errno(time((time_t *)time_ptr));                                  // 0.0
/*126  */             if (!is_error(ret) && time_ptr)                                             // 0.0
/*128  */                 tswap32s(time_ptr);                                                     // 0.0
/*130  */         }                                                                               // 0.0
/*132  */         break;                                                                          // 0.0
/*134  */     case TARGET_NR_mknod:                                                               // 0.0
/*136  */         ret = get_errno(mknod((const char *)arg1, arg2, arg3));                         // 0.0
/*138  */         break;                                                                          // 0.0
/*140  */     case TARGET_NR_chmod:                                                               // 0.0
/*142  */         ret = get_errno(chmod((const char *)arg1, arg2));                               // 0.0
/*144  */         break;                                                                          // 0.0
/*146  */     case TARGET_NR_lchown:                                                              // 0.0
/*148  */         ret = get_errno(chown((const char *)arg1, arg2, arg3));                         // 0.0
/*150  */         break;                                                                          // 0.0
/*152  */     case TARGET_NR_break:                                                               // 0.0
/*154  */         goto unimplemented;                                                             // 0.0
/*156  */     case TARGET_NR_oldstat:                                                             // 0.0
/*158  */         goto unimplemented;                                                             // 0.0
/*160  */     case TARGET_NR_lseek:                                                               // 0.0
/*162  */         ret = get_errno(lseek(arg1, arg2, arg3));                                       // 0.0
/*164  */         break;                                                                          // 0.0
/*166  */     case TARGET_NR_getpid:                                                              // 0.0
/*168  */         ret = get_errno(getpid());                                                      // 0.0
/*170  */         break;                                                                          // 0.0
/*172  */     case TARGET_NR_mount:                                                               // 0.0
/*174  */         /* need to look at the data field */                                            // 0.0
/*176  */         goto unimplemented;                                                             // 0.0
/*178  */     case TARGET_NR_umount:                                                              // 0.0
/*180  */         ret = get_errno(umount((const char *)arg1));                                    // 0.0
/*182  */         break;                                                                          // 0.0
/*184  */     case TARGET_NR_setuid:                                                              // 0.0
/*186  */         ret = get_errno(setuid(arg1));                                                  // 0.0
/*188  */         break;                                                                          // 0.0
/*190  */     case TARGET_NR_getuid:                                                              // 0.0
/*192  */         ret = get_errno(getuid());                                                      // 0.0
/*194  */         break;                                                                          // 0.0
/*196  */     case TARGET_NR_stime:                                                               // 0.0
/*198  */         {                                                                               // 0.0
/*200  */             int *time_ptr = (int *)arg1;                                                // 0.0
/*202  */             if (time_ptr)                                                               // 0.0
/*204  */                 tswap32s(time_ptr);                                                     // 0.0
/*206  */             ret = get_errno(stime((time_t *)time_ptr));                                 // 0.0
/*208  */         }                                                                               // 0.0
/*210  */         break;                                                                          // 0.0
/*212  */     case TARGET_NR_ptrace:                                                              // 0.0
/*214  */         goto unimplemented;                                                             // 0.0
/*216  */     case TARGET_NR_alarm:                                                               // 0.0
/*218  */         ret = alarm(arg1);                                                              // 0.0
/*220  */         break;                                                                          // 0.0
/*222  */     case TARGET_NR_oldfstat:                                                            // 0.0
/*224  */         goto unimplemented;                                                             // 0.0
/*226  */     case TARGET_NR_pause:                                                               // 0.0
/*228  */         ret = get_errno(pause());                                                       // 0.0
/*230  */         break;                                                                          // 0.0
/*232  */     case TARGET_NR_utime:                                                               // 0.0
/*234  */         goto unimplemented;                                                             // 0.0
/*236  */     case TARGET_NR_stty:                                                                // 0.0
/*238  */         goto unimplemented;                                                             // 0.0
/*240  */     case TARGET_NR_gtty:                                                                // 0.0
/*242  */         goto unimplemented;                                                             // 0.0
/*244  */     case TARGET_NR_access:                                                              // 0.0
/*246  */         ret = get_errno(access((const char *)arg1, arg2));                              // 0.0
/*248  */         break;                                                                          // 0.0
/*250  */     case TARGET_NR_nice:                                                                // 0.0
/*252  */         ret = get_errno(nice(arg1));                                                    // 0.0
/*254  */         break;                                                                          // 0.0
/*256  */     case TARGET_NR_ftime:                                                               // 0.0
/*258  */         goto unimplemented;                                                             // 0.0
/*260  */     case TARGET_NR_sync:                                                                // 0.0
/*262  */         ret = get_errno(sync());                                                        // 0.0
/*264  */         break;                                                                          // 0.0
/*266  */     case TARGET_NR_kill:                                                                // 0.0
/*268  */         ret = get_errno(kill(arg1, arg2));                                              // 0.0
/*270  */         break;                                                                          // 0.0
/*272  */     case TARGET_NR_rename:                                                              // 0.0
/*274  */         ret = get_errno(rename((const char *)arg1, (const char *)arg2));                // 0.0
/*276  */         break;                                                                          // 0.0
/*278  */     case TARGET_NR_mkdir:                                                               // 0.0
/*280  */         ret = get_errno(mkdir((const char *)arg1, arg2));                               // 0.0
/*282  */         break;                                                                          // 0.0
/*284  */     case TARGET_NR_rmdir:                                                               // 0.0
/*286  */         ret = get_errno(rmdir((const char *)arg1));                                     // 0.0
/*288  */         break;                                                                          // 0.0
/*290  */     case TARGET_NR_dup:                                                                 // 0.0
/*292  */         ret = get_errno(dup(arg1));                                                     // 0.0
/*294  */         break;                                                                          // 0.0
/*296  */     case TARGET_NR_pipe:                                                                // 0.0
/*298  */         {                                                                               // 0.0
/*300  */             int *pipe_ptr = (int *)arg1;                                                // 0.0
/*302  */             ret = get_errno(pipe(pipe_ptr));                                            // 0.0
/*304  */             if (!is_error(ret)) {                                                       // 0.0
/*306  */                 tswap32s(&pipe_ptr[0]);                                                 // 0.0
/*308  */                 tswap32s(&pipe_ptr[1]);                                                 // 0.0
/*310  */             }                                                                           // 0.0
/*312  */         }                                                                               // 0.0
/*314  */         break;                                                                          // 0.0
/*316  */     case TARGET_NR_times:                                                               // 0.0
/*318  */         goto unimplemented;                                                             // 0.0
/*320  */     case TARGET_NR_prof:                                                                // 0.0
/*322  */         goto unimplemented;                                                             // 0.0
/*324  */     case TARGET_NR_setgid:                                                              // 0.0
/*326  */         ret = get_errno(setgid(arg1));                                                  // 0.0
/*328  */         break;                                                                          // 0.0
/*330  */     case TARGET_NR_getgid:                                                              // 0.0
/*332  */         ret = get_errno(getgid());                                                      // 0.0
/*334  */         break;                                                                          // 0.0
/*336  */     case TARGET_NR_signal:                                                              // 0.0
/*338  */         goto unimplemented;                                                             // 0.0
/*340  */     case TARGET_NR_geteuid:                                                             // 0.0
/*342  */         ret = get_errno(geteuid());                                                     // 0.0
/*344  */         break;                                                                          // 0.0
/*346  */     case TARGET_NR_getegid:                                                             // 0.0
/*348  */         ret = get_errno(getegid());                                                     // 0.0
/*350  */         break;                                                                          // 0.0
/*352  */     case TARGET_NR_acct:                                                                // 0.0
/*354  */         goto unimplemented;                                                             // 0.0
/*356  */     case TARGET_NR_umount2:                                                             // 0.0
/*358  */         ret = get_errno(umount2((const char *)arg1, arg2));                             // 0.0
/*360  */         break;                                                                          // 0.0
/*362  */     case TARGET_NR_lock:                                                                // 0.0
/*364  */         goto unimplemented;                                                             // 0.0
/*366  */     case TARGET_NR_ioctl:                                                               // 0.0
/*368  */         ret = do_ioctl(arg1, arg2, arg3);                                               // 0.0
/*370  */         break;                                                                          // 0.0
/*372  */     case TARGET_NR_fcntl:                                                               // 0.0
/*374  */         switch(arg2) {                                                                  // 0.0
/*376  */         case F_GETLK:                                                                   // 0.0
/*378  */         case F_SETLK:                                                                   // 0.0
/*380  */         case F_SETLKW:                                                                  // 0.0
/*382  */             goto unimplemented;                                                         // 0.0
/*384  */         default:                                                                        // 0.0
/*386  */             ret = get_errno(fcntl(arg1, arg2, arg3));                                   // 0.0
/*388  */             break;                                                                      // 0.0
/*390  */         }                                                                               // 0.0
/*392  */         break;                                                                          // 0.0
/*394  */     case TARGET_NR_mpx:                                                                 // 0.0
/*396  */         goto unimplemented;                                                             // 0.0
/*398  */     case TARGET_NR_setpgid:                                                             // 0.0
/*400  */         ret = get_errno(setpgid(arg1, arg2));                                           // 0.0
/*402  */         break;                                                                          // 0.0
/*404  */     case TARGET_NR_ulimit:                                                              // 0.0
/*406  */         goto unimplemented;                                                             // 0.0
/*408  */     case TARGET_NR_oldolduname:                                                         // 0.0
/*410  */         goto unimplemented;                                                             // 0.0
/*412  */     case TARGET_NR_umask:                                                               // 0.0
/*414  */         ret = get_errno(umask(arg1));                                                   // 0.0
/*416  */         break;                                                                          // 0.0
/*418  */     case TARGET_NR_chroot:                                                              // 0.0
/*420  */         ret = get_errno(chroot((const char *)arg1));                                    // 0.0
/*422  */         break;                                                                          // 0.0
/*424  */     case TARGET_NR_ustat:                                                               // 0.0
/*426  */         goto unimplemented;                                                             // 0.0
/*428  */     case TARGET_NR_dup2:                                                                // 0.0
/*430  */         ret = get_errno(dup2(arg1, arg2));                                              // 0.0
/*432  */         break;                                                                          // 0.0
/*434  */     case TARGET_NR_getppid:                                                             // 0.0
/*436  */         ret = get_errno(getppid());                                                     // 0.0
/*438  */         break;                                                                          // 0.0
/*440  */     case TARGET_NR_getpgrp:                                                             // 0.0
/*442  */         ret = get_errno(getpgrp());                                                     // 0.0
/*444  */         break;                                                                          // 0.0
/*446  */     case TARGET_NR_setsid:                                                              // 0.0
/*448  */         ret = get_errno(setsid());                                                      // 0.0
/*450  */         break;                                                                          // 0.0
/*452  */     case TARGET_NR_sigaction:                                                           // 0.0
/*454  */ #if 0                                                                                   // 0.0
/*456  */         {                                                                               // 0.0
/*458  */             int signum = arg1;                                                          // 0.0
/*460  */             struct target_old_sigaction *tact = arg2, *toldact = arg3;                  // 0.0
/*462  */             ret = get_errno(setsid());                                                  // 0.0
/*464  */                                                                                         // 0.0
/*468  */         }                                                                               // 0.0
/*470  */         break;                                                                          // 0.0
/*472  */ #else                                                                                   // 0.0
/*474  */         goto unimplemented;                                                             // 0.0
/*476  */ #endif                                                                                  // 0.0
/*478  */     case TARGET_NR_sgetmask:                                                            // 0.0
/*480  */         goto unimplemented;                                                             // 0.0
/*482  */     case TARGET_NR_ssetmask:                                                            // 0.0
/*484  */         goto unimplemented;                                                             // 0.0
/*486  */     case TARGET_NR_setreuid:                                                            // 0.0
/*488  */         ret = get_errno(setreuid(arg1, arg2));                                          // 0.0
/*490  */         break;                                                                          // 0.0
/*492  */     case TARGET_NR_setregid:                                                            // 0.0
/*494  */         ret = get_errno(setregid(arg1, arg2));                                          // 0.0
/*496  */         break;                                                                          // 0.0
/*498  */     case TARGET_NR_sigsuspend:                                                          // 0.0
/*500  */         goto unimplemented;                                                             // 0.0
/*502  */     case TARGET_NR_sigpending:                                                          // 0.0
/*504  */         goto unimplemented;                                                             // 0.0
/*506  */     case TARGET_NR_sethostname:                                                         // 0.0
/*508  */         ret = get_errno(sethostname((const char *)arg1, arg2));                         // 0.0
/*510  */         break;                                                                          // 0.0
/*512  */     case TARGET_NR_setrlimit:                                                           // 0.0
/*514  */         goto unimplemented;                                                             // 0.0
/*516  */     case TARGET_NR_getrlimit:                                                           // 0.0
/*518  */         goto unimplemented;                                                             // 0.0
/*520  */     case TARGET_NR_getrusage:                                                           // 0.0
/*522  */         goto unimplemented;                                                             // 0.0
/*524  */     case TARGET_NR_gettimeofday:                                                        // 0.0
/*526  */         {                                                                               // 0.0
/*528  */             struct target_timeval *target_tv = (void *)arg1;                            // 0.0
/*530  */             struct timeval tv;                                                          // 0.0
/*532  */             ret = get_errno(gettimeofday(&tv, NULL));                                   // 0.0
/*534  */             if (!is_error(ret)) {                                                       // 0.0
/*536  */                 target_tv->tv_sec = tswapl(tv.tv_sec);                                  // 0.0
/*538  */                 target_tv->tv_usec = tswapl(tv.tv_usec);                                // 0.0
/*540  */             }                                                                           // 0.0
/*542  */         }                                                                               // 0.0
/*544  */         break;                                                                          // 0.0
/*546  */     case TARGET_NR_settimeofday:                                                        // 0.0
/*548  */         {                                                                               // 0.0
/*550  */             struct target_timeval *target_tv = (void *)arg1;                            // 0.0
/*552  */             struct timeval tv;                                                          // 0.0
/*554  */             tv.tv_sec = tswapl(target_tv->tv_sec);                                      // 0.0
/*556  */             tv.tv_usec = tswapl(target_tv->tv_usec);                                    // 0.0
/*558  */             ret = get_errno(settimeofday(&tv, NULL));                                   // 0.0
/*560  */         }                                                                               // 0.0
/*562  */         break;                                                                          // 0.0
/*564  */     case TARGET_NR_getgroups:                                                           // 0.0
/*566  */         goto unimplemented;                                                             // 0.0
/*568  */     case TARGET_NR_setgroups:                                                           // 0.0
/*570  */         goto unimplemented;                                                             // 0.0
/*572  */     case TARGET_NR_select:                                                              // 0.0
/*574  */         goto unimplemented;                                                             // 0.0
/*576  */     case TARGET_NR_symlink:                                                             // 0.0
/*578  */         ret = get_errno(symlink((const char *)arg1, (const char *)arg2));               // 0.0
/*580  */         break;                                                                          // 0.0
/*582  */     case TARGET_NR_oldlstat:                                                            // 0.0
/*584  */         goto unimplemented;                                                             // 0.0
/*586  */     case TARGET_NR_readlink:                                                            // 0.0
/*588  */         ret = get_errno(readlink((const char *)arg1, (char *)arg2, arg3));              // 0.0
/*590  */         break;                                                                          // 0.0
/*592  */     case TARGET_NR_uselib:                                                              // 0.0
/*594  */         goto unimplemented;                                                             // 0.0
/*596  */     case TARGET_NR_swapon:                                                              // 0.0
/*598  */         ret = get_errno(swapon((const char *)arg1, arg2));                              // 0.0
/*600  */         break;                                                                          // 0.0
/*602  */     case TARGET_NR_reboot:                                                              // 0.0
/*604  */         goto unimplemented;                                                             // 0.0
/*606  */     case TARGET_NR_readdir:                                                             // 0.0
/*608  */         goto unimplemented;                                                             // 0.0
/*610  */ #ifdef TARGET_I386                                                                      // 0.0
/*612  */     case TARGET_NR_mmap:                                                                // 0.0
/*614  */         {                                                                               // 0.0
/*616  */             uint32_t v1, v2, v3, v4, v5, v6, *vptr;                                     // 0.0
/*618  */             vptr = (uint32_t *)arg1;                                                    // 0.0
/*620  */             v1 = tswap32(vptr[0]);                                                      // 0.0
/*622  */             v2 = tswap32(vptr[1]);                                                      // 0.0
/*624  */             v3 = tswap32(vptr[2]);                                                      // 0.0
/*626  */             v4 = tswap32(vptr[3]);                                                      // 0.0
/*628  */             v5 = tswap32(vptr[4]);                                                      // 0.0
/*630  */             v6 = tswap32(vptr[5]);                                                      // 0.0
/*632  */             ret = get_errno((long)mmap((void *)v1, v2, v3, v4, v5, v6));                // 0.0
/*634  */         }                                                                               // 0.0
/*636  */         break;                                                                          // 0.0
/*638  */ #endif                                                                                  // 0.0
/*640  */ #ifdef TARGET_I386                                                                      // 0.0
/*642  */     case TARGET_NR_mmap2:                                                               // 0.0
/*644  */ #else                                                                                   // 0.0
/*646  */     case TARGET_NR_mmap:                                                                // 0.0
/*648  */ #endif                                                                                  // 0.0
/*650  */         ret = get_errno((long)mmap((void *)arg1, arg2, arg3, arg4, arg5, arg6));        // 0.0
/*652  */         break;                                                                          // 0.0
/*654  */     case TARGET_NR_munmap:                                                              // 0.0
/*656  */         ret = get_errno(munmap((void *)arg1, arg2));                                    // 0.0
/*658  */         break;                                                                          // 0.0
/*660  */     case TARGET_NR_truncate:                                                            // 0.0
/*662  */         ret = get_errno(truncate((const char *)arg1, arg2));                            // 0.0
/*664  */         break;                                                                          // 0.0
/*666  */     case TARGET_NR_ftruncate:                                                           // 0.0
/*668  */         ret = get_errno(ftruncate(arg1, arg2));                                         // 0.0
/*670  */         break;                                                                          // 0.0
/*672  */     case TARGET_NR_fchmod:                                                              // 0.0
/*674  */         ret = get_errno(fchmod(arg1, arg2));                                            // 0.0
/*676  */         break;                                                                          // 0.0
/*678  */     case TARGET_NR_fchown:                                                              // 0.0
/*680  */         ret = get_errno(fchown(arg1, arg2, arg3));                                      // 0.0
/*682  */         break;                                                                          // 0.0
/*684  */     case TARGET_NR_getpriority:                                                         // 0.0
/*686  */         ret = get_errno(getpriority(arg1, arg2));                                       // 0.0
/*688  */         break;                                                                          // 0.0
/*690  */     case TARGET_NR_setpriority:                                                         // 0.0
/*692  */         ret = get_errno(setpriority(arg1, arg2, arg3));                                 // 0.0
/*694  */         break;                                                                          // 0.0
/*696  */     case TARGET_NR_profil:                                                              // 0.0
/*698  */         goto unimplemented;                                                             // 0.0
/*700  */     case TARGET_NR_statfs:                                                              // 0.0
/*702  */         stfs = (void *)arg2;                                                            // 0.0
/*704  */         ret = get_errno(sys_statfs((const char *)arg1, stfs));                          // 0.0
/*706  */     convert_statfs:                                                                     // 0.0
/*708  */         if (!is_error(ret)) {                                                           // 0.0
/*710  */             tswap32s(&stfs->f_type);                                                    // 0.0
/*712  */             tswap32s(&stfs->f_bsize);                                                   // 0.0
/*714  */             tswap32s(&stfs->f_blocks);                                                  // 0.0
/*716  */             tswap32s(&stfs->f_bfree);                                                   // 0.0
/*718  */             tswap32s(&stfs->f_bavail);                                                  // 0.0
/*720  */             tswap32s(&stfs->f_files);                                                   // 0.0
/*722  */             tswap32s(&stfs->f_ffree);                                                   // 0.0
/*724  */             tswap32s(&stfs->f_fsid.val[0]);                                             // 0.0
/*726  */             tswap32s(&stfs->f_fsid.val[1]);                                             // 0.0
/*728  */             tswap32s(&stfs->f_namelen);                                                 // 0.0
/*730  */         }                                                                               // 0.0
/*732  */         break;                                                                          // 0.0
/*734  */     case TARGET_NR_fstatfs:                                                             // 0.0
/*736  */         stfs = (void *)arg2;                                                            // 0.0
/*738  */         ret = get_errno(sys_fstatfs(arg1, stfs));                                       // 0.0
/*740  */         goto convert_statfs;                                                            // 0.0
/*742  */     case TARGET_NR_ioperm:                                                              // 0.0
/*744  */         goto unimplemented;                                                             // 0.0
/*746  */     case TARGET_NR_socketcall:                                                          // 0.0
/*748  */         ret = do_socketcall(arg1, (long *)arg2);                                        // 0.0
/*750  */         break;                                                                          // 0.0
/*752  */     case TARGET_NR_syslog:                                                              // 0.0
/*754  */         goto unimplemented;                                                             // 0.0
/*756  */     case TARGET_NR_setitimer:                                                           // 0.0
/*758  */         goto unimplemented;                                                             // 0.0
/*760  */     case TARGET_NR_getitimer:                                                           // 0.0
/*762  */         goto unimplemented;                                                             // 0.0
/*764  */     case TARGET_NR_stat:                                                                // 0.0
/*766  */         ret = get_errno(stat((const char *)arg1, &st));                                 // 0.0
/*768  */         goto do_stat;                                                                   // 0.0
/*770  */     case TARGET_NR_lstat:                                                               // 0.0
/*772  */         ret = get_errno(lstat((const char *)arg1, &st));                                // 0.0
/*774  */         goto do_stat;                                                                   // 0.0
/*776  */     case TARGET_NR_fstat:                                                               // 0.0
/*778  */         {                                                                               // 0.0
/*780  */             ret = get_errno(fstat(arg1, &st));                                          // 0.0
/*782  */         do_stat:                                                                        // 0.0
/*784  */             if (!is_error(ret)) {                                                       // 0.0
/*786  */                 struct target_stat *target_st = (void *)arg2;                           // 0.0
/*788  */                 target_st->st_dev = tswap16(st.st_dev);                                 // 0.0
/*790  */                 target_st->st_ino = tswapl(st.st_ino);                                  // 0.0
/*792  */                 target_st->st_mode = tswap16(st.st_mode);                               // 0.0
/*794  */                 target_st->st_nlink = tswap16(st.st_nlink);                             // 0.0
/*796  */                 target_st->st_uid = tswap16(st.st_uid);                                 // 0.0
/*798  */                 target_st->st_gid = tswap16(st.st_gid);                                 // 0.0
/*800  */                 target_st->st_rdev = tswap16(st.st_rdev);                               // 0.0
/*802  */                 target_st->st_size = tswapl(st.st_size);                                // 0.0
/*804  */                 target_st->st_blksize = tswapl(st.st_blksize);                          // 0.0
/*806  */                 target_st->st_blocks = tswapl(st.st_blocks);                            // 0.0
/*808  */                 target_st->st_atime = tswapl(st.st_atime);                              // 0.0
/*810  */                 target_st->st_mtime = tswapl(st.st_mtime);                              // 0.0
/*812  */                 target_st->st_ctime = tswapl(st.st_ctime);                              // 0.0
/*814  */             }                                                                           // 0.0
/*816  */         }                                                                               // 0.0
/*818  */         break;                                                                          // 0.0
/*820  */     case TARGET_NR_olduname:                                                            // 0.0
/*822  */         goto unimplemented;                                                             // 0.0
/*824  */     case TARGET_NR_iopl:                                                                // 0.0
/*826  */         goto unimplemented;                                                             // 0.0
/*828  */     case TARGET_NR_vhangup:                                                             // 0.0
/*830  */         ret = get_errno(vhangup());                                                     // 0.0
/*832  */         break;                                                                          // 0.0
/*834  */     case TARGET_NR_idle:                                                                // 0.0
/*836  */         goto unimplemented;                                                             // 0.0
/*838  */     case TARGET_NR_vm86old:                                                             // 0.0
/*840  */         goto unimplemented;                                                             // 0.0
/*842  */     case TARGET_NR_wait4:                                                               // 0.0
/*844  */         {                                                                               // 0.0
/*846  */             int status;                                                                 // 0.0
/*848  */             target_long *status_ptr = (void *)arg2;                                     // 0.0
/*850  */             struct rusage rusage, *rusage_ptr;                                          // 0.0
/*852  */             struct target_rusage *target_rusage = (void *)arg4;                         // 0.0
/*854  */             if (target_rusage)                                                          // 0.0
/*856  */                 rusage_ptr = &rusage;                                                   // 0.0
/*858  */             else                                                                        // 0.0
/*860  */                 rusage_ptr = NULL;                                                      // 0.0
/*862  */             ret = get_errno(wait4(arg1, &status, arg3, rusage_ptr));                    // 0.0
/*864  */             if (!is_error(ret)) {                                                       // 0.0
/*866  */                 if (status_ptr)                                                         // 0.0
/*868  */                     *status_ptr = tswap32(status);                                      // 0.0
/*870  */                 if (target_rusage) {                                                    // 0.0
/*872  */                     target_rusage->ru_utime.tv_sec = tswapl(rusage.ru_utime.tv_sec);    // 0.0
/*874  */                     target_rusage->ru_utime.tv_usec = tswapl(rusage.ru_utime.tv_usec);  // 0.0
/*876  */                     target_rusage->ru_stime.tv_sec = tswapl(rusage.ru_stime.tv_sec);    // 0.0
/*878  */                     target_rusage->ru_stime.tv_usec = tswapl(rusage.ru_stime.tv_usec);  // 0.0
/*880  */                     target_rusage->ru_maxrss = tswapl(rusage.ru_maxrss);                // 0.0
/*882  */                     target_rusage->ru_ixrss = tswapl(rusage.ru_ixrss);                  // 0.0
/*884  */                     target_rusage->ru_idrss = tswapl(rusage.ru_idrss);                  // 0.0
/*886  */                     target_rusage->ru_isrss = tswapl(rusage.ru_isrss);                  // 0.0
/*888  */                     target_rusage->ru_minflt = tswapl(rusage.ru_minflt);                // 0.0
/*890  */                     target_rusage->ru_majflt = tswapl(rusage.ru_majflt);                // 0.0
/*892  */                     target_rusage->ru_nswap = tswapl(rusage.ru_nswap);                  // 0.0
/*894  */                     target_rusage->ru_inblock = tswapl(rusage.ru_inblock);              // 0.0
/*896  */                     target_rusage->ru_oublock = tswapl(rusage.ru_oublock);              // 0.0
/*898  */                     target_rusage->ru_msgsnd = tswapl(rusage.ru_msgsnd);                // 0.0
/*900  */                     target_rusage->ru_msgrcv = tswapl(rusage.ru_msgrcv);                // 0.0
/*902  */                     target_rusage->ru_nsignals = tswapl(rusage.ru_nsignals);            // 0.0
/*904  */                     target_rusage->ru_nvcsw = tswapl(rusage.ru_nvcsw);                  // 0.0
/*906  */                     target_rusage->ru_nivcsw = tswapl(rusage.ru_nivcsw);                // 0.0
/*908  */                 }                                                                       // 0.0
/*910  */             }                                                                           // 0.0
/*912  */         }                                                                               // 0.0
/*914  */         break;                                                                          // 0.0
/*916  */     case TARGET_NR_swapoff:                                                             // 0.0
/*918  */         ret = get_errno(swapoff((const char *)arg1));                                   // 0.0
/*920  */         break;                                                                          // 0.0
/*922  */     case TARGET_NR_sysinfo:                                                             // 0.0
/*924  */         goto unimplemented;                                                             // 0.0
/*926  */     case TARGET_NR_ipc:                                                                 // 0.0
/*928  */         goto unimplemented;                                                             // 0.0
/*930  */     case TARGET_NR_fsync:                                                               // 0.0
/*932  */         ret = get_errno(fsync(arg1));                                                   // 0.0
/*934  */         break;                                                                          // 0.0
/*936  */     case TARGET_NR_sigreturn:                                                           // 0.0
/*938  */         goto unimplemented;                                                             // 0.0
/*940  */     case TARGET_NR_clone:                                                               // 0.0
/*942  */         goto unimplemented;                                                             // 0.0
/*944  */     case TARGET_NR_setdomainname:                                                       // 0.0
/*946  */         ret = get_errno(setdomainname((const char *)arg1, arg2));                       // 0.0
/*948  */         break;                                                                          // 0.0
/*950  */     case TARGET_NR_uname:                                                               // 0.0
/*952  */         /* no need to transcode because we use the linux syscall */                     // 0.0
/*954  */         ret = get_errno(sys_uname((struct new_utsname *)arg1));                         // 0.0
/*956  */         break;                                                                          // 0.0
/*958  */ #ifdef TARGET_I386                                                                      // 0.0
/*960  */     case TARGET_NR_modify_ldt:                                                          // 0.0
/*962  */         ret = get_errno(gemu_modify_ldt(cpu_env, arg1, (void *)arg2, arg3));            // 0.0
/*964  */         break;                                                                          // 0.0
/*966  */ #endif                                                                                  // 0.0
/*968  */     case TARGET_NR_adjtimex:                                                            // 0.0
/*970  */         goto unimplemented;                                                             // 0.0
/*972  */     case TARGET_NR_mprotect:                                                            // 0.0
/*974  */         ret = get_errno(mprotect((void *)arg1, arg2, arg3));                            // 0.0
/*976  */         break;                                                                          // 0.0
/*978  */     case TARGET_NR_sigprocmask:                                                         // 0.0
/*980  */         {                                                                               // 0.0
/*982  */             int how = arg1;                                                             // 0.0
/*984  */             sigset_t set, oldset, *set_ptr;                                             // 0.0
/*986  */             target_ulong *pset = (void *)arg2, *poldset = (void *)arg3;                 // 0.0
/*988  */                                                                                         // 0.0
/*990  */             switch(how) {                                                               // 0.0
/*992  */             case TARGET_SIG_BLOCK:                                                      // 0.0
/*994  */                 how = SIG_BLOCK;                                                        // 0.0
/*996  */                 break;                                                                  // 0.0
/*998  */             case TARGET_SIG_UNBLOCK:                                                    // 0.0
/*1000 */                 how = SIG_UNBLOCK;                                                      // 0.0
/*1002 */                 break;                                                                  // 0.0
/*1004 */             case TARGET_SIG_SETMASK:                                                    // 0.0
/*1006 */                 how = SIG_SETMASK;                                                      // 0.0
/*1008 */                 break;                                                                  // 0.0
/*1010 */             default:                                                                    // 0.0
/*1012 */                 ret = -EINVAL;                                                          // 0.0
/*1014 */                 goto fail;                                                              // 0.0
/*1016 */             }                                                                           // 0.0
/*1018 */                                                                                         // 0.0
/*1020 */             if (pset) {                                                                 // 0.0
/*1022 */                 target_to_host_old_sigset(&set, pset);                                  // 0.0
/*1024 */                 set_ptr = &set;                                                         // 0.0
/*1026 */             } else {                                                                    // 0.0
/*1028 */                 set_ptr = NULL;                                                         // 0.0
/*1030 */             }                                                                           // 0.0
/*1032 */             ret = get_errno(sigprocmask(arg1, set_ptr, &oldset));                       // 0.0
/*1034 */             if (!is_error(ret) && poldset) {                                            // 0.0
/*1036 */                 host_to_target_old_sigset(poldset, &oldset);                            // 0.0
/*1038 */             }                                                                           // 0.0
/*1040 */         }                                                                               // 0.0
/*1042 */         break;                                                                          // 0.0
/*1044 */     case TARGET_NR_create_module:                                                       // 0.0
/*1046 */     case TARGET_NR_init_module:                                                         // 0.0
/*1048 */     case TARGET_NR_delete_module:                                                       // 0.0
/*1050 */     case TARGET_NR_get_kernel_syms:                                                     // 0.0
/*1052 */         goto unimplemented;                                                             // 0.0
/*1054 */     case TARGET_NR_quotactl:                                                            // 0.0
/*1056 */         goto unimplemented;                                                             // 0.0
/*1058 */     case TARGET_NR_getpgid:                                                             // 0.0
/*1060 */         ret = get_errno(getpgid(arg1));                                                 // 0.0
/*1062 */         break;                                                                          // 0.0
/*1064 */     case TARGET_NR_fchdir:                                                              // 0.0
/*1066 */         ret = get_errno(fchdir(arg1));                                                  // 0.0
/*1068 */         break;                                                                          // 0.0
/*1070 */     case TARGET_NR_bdflush:                                                             // 0.0
/*1072 */         goto unimplemented;                                                             // 0.0
/*1074 */     case TARGET_NR_sysfs:                                                               // 0.0
/*1076 */         goto unimplemented;                                                             // 0.0
/*1078 */     case TARGET_NR_personality:                                                         // 0.0
/*1080 */         ret = get_errno(mprotect((void *)arg1, arg2, arg3));                            // 0.0
/*1082 */         break;                                                                          // 0.0
/*1084 */     case TARGET_NR_afs_syscall:                                                         // 0.0
/*1086 */         goto unimplemented;                                                             // 0.0
/*1088 */     case TARGET_NR_setfsuid:                                                            // 0.0
/*1090 */         goto unimplemented;                                                             // 0.0
/*1092 */     case TARGET_NR_setfsgid:                                                            // 0.0
/*1094 */         goto unimplemented;                                                             // 0.0
/*1096 */     case TARGET_NR__llseek:                                                             // 0.0
/*1098 */         {                                                                               // 0.0
/*1100 */             int64_t res;                                                                // 0.0
/*1102 */             ret = get_errno(_llseek(arg1, arg2, arg3, &res, arg5));                     // 0.0
/*1104 */             *(int64_t *)arg4 = tswap64(res);                                            // 0.0
/*1106 */         }                                                                               // 0.0
/*1108 */         break;                                                                          // 0.0
/*1110 */     case TARGET_NR_getdents:                                                            // 0.0
/*1112 */ #if TARGET_LONG_SIZE != 4                                                               // 0.0
/*1114 */ #error not supported                                                                    // 0.0
/*1116 */ #endif                                                                                  // 0.0
/*1118 */         {                                                                               // 0.0
/*1120 */             struct dirent *dirp = (void *)arg2;                                         // 0.0
/*1122 */             long count = arg3;                                                          // 0.0
/*1124 */             ret = get_errno(sys_getdents(arg1, dirp, count));                           // 0.0
/*1126 */             if (!is_error(ret)) {                                                       // 0.0
/*1128 */                 struct dirent *de;                                                      // 0.0
/*1130 */                 int len = ret;                                                          // 0.0
/*1132 */                 int reclen;                                                             // 0.0
/*1134 */                 de = dirp;                                                              // 0.0
/*1136 */                 while (len > 0) {                                                       // 0.0
/*1138 */                     reclen = tswap16(de->d_reclen);                                     // 0.0
/*1140 */                     if (reclen > len)                                                   // 0.0
/*1142 */                         break;                                                          // 0.0
/*1144 */                     de->d_reclen = reclen;                                              // 0.0
/*1146 */                     tswapls(&de->d_ino);                                                // 0.0
/*1148 */                     tswapls(&de->d_off);                                                // 0.0
/*1150 */                     de = (struct dirent *)((char *)de + reclen);                        // 0.0
/*1152 */                     len -= reclen;                                                      // 0.0
/*1154 */                 }                                                                       // 0.0
/*1156 */             }                                                                           // 0.0
/*1158 */         }                                                                               // 0.0
/*1160 */         break;                                                                          // 0.0
/*1162 */     case TARGET_NR__newselect:                                                          // 0.0
/*1164 */         ret = do_select(arg1, (void *)arg2, (void *)arg3, (void *)arg4,                 // 0.0
/*1166 */                         (void *)arg5);                                                  // 0.0
/*1168 */         break;                                                                          // 0.0
/*1170 */     case TARGET_NR_flock:                                                               // 0.0
/*1172 */         goto unimplemented;                                                             // 0.0
/*1174 */     case TARGET_NR_msync:                                                               // 0.0
/*1176 */         ret = get_errno(msync((void *)arg1, arg2, arg3));                               // 0.0
/*1178 */         break;                                                                          // 0.0
/*1180 */     case TARGET_NR_readv:                                                               // 0.0
/*1182 */         {                                                                               // 0.0
/*1184 */             int count = arg3;                                                           // 0.0
/*1186 */             int i;                                                                      // 0.0
/*1188 */             struct iovec *vec;                                                          // 0.0
/*1190 */             struct target_iovec *target_vec = (void *)arg2;                             // 0.0
/*1194 */             vec = alloca(count * sizeof(struct iovec));                                 // 0.0
/*1196 */             for(i = 0;i < count; i++) {                                                 // 0.0
/*1198 */                 vec[i].iov_base = (void *)tswapl(target_vec[i].iov_base);               // 0.0
/*1200 */                 vec[i].iov_len = tswapl(target_vec[i].iov_len);                         // 0.0
/*1202 */             }                                                                           // 0.0
/*1204 */             ret = get_errno(readv(arg1, vec, count));                                   // 0.0
/*1206 */         }                                                                               // 0.0
/*1208 */         break;                                                                          // 0.0
/*1210 */     case TARGET_NR_writev:                                                              // 0.0
/*1212 */         {                                                                               // 0.0
/*1214 */             int count = arg3;                                                           // 0.0
/*1216 */             int i;                                                                      // 0.0
/*1218 */             struct iovec *vec;                                                          // 0.0
/*1220 */             struct target_iovec *target_vec = (void *)arg2;                             // 0.0
/*1224 */             vec = alloca(count * sizeof(struct iovec));                                 // 0.0
/*1226 */             for(i = 0;i < count; i++) {                                                 // 0.0
/*1228 */                 vec[i].iov_base = (void *)tswapl(target_vec[i].iov_base);               // 0.0
/*1230 */                 vec[i].iov_len = tswapl(target_vec[i].iov_len);                         // 0.0
/*1232 */             }                                                                           // 0.0
/*1234 */             ret = get_errno(writev(arg1, vec, count));                                  // 0.0
/*1236 */         }                                                                               // 0.0
/*1238 */         break;                                                                          // 0.0
/*1240 */     case TARGET_NR_getsid:                                                              // 0.0
/*1242 */         ret = get_errno(getsid(arg1));                                                  // 0.0
/*1244 */         break;                                                                          // 0.0
/*1246 */     case TARGET_NR_fdatasync:                                                           // 0.0
/*1248 */         goto unimplemented;                                                             // 0.0
/*1250 */     case TARGET_NR__sysctl:                                                             // 0.0
/*1252 */         goto unimplemented;                                                             // 0.0
/*1254 */     case TARGET_NR_mlock:                                                               // 0.0
/*1256 */         ret = get_errno(mlock((void *)arg1, arg2));                                     // 0.0
/*1258 */         break;                                                                          // 0.0
/*1260 */     case TARGET_NR_munlock:                                                             // 0.0
/*1262 */         ret = get_errno(munlock((void *)arg1, arg2));                                   // 0.0
/*1264 */         break;                                                                          // 0.0
/*1266 */     case TARGET_NR_mlockall:                                                            // 0.0
/*1268 */         ret = get_errno(mlockall(arg1));                                                // 0.0
/*1270 */         break;                                                                          // 0.0
/*1272 */     case TARGET_NR_munlockall:                                                          // 0.0
/*1274 */         ret = get_errno(munlockall());                                                  // 0.0
/*1276 */         break;                                                                          // 0.0
/*1278 */     case TARGET_NR_sched_setparam:                                                      // 0.0
/*1280 */         goto unimplemented;                                                             // 0.0
/*1282 */     case TARGET_NR_sched_getparam:                                                      // 0.0
/*1284 */         goto unimplemented;                                                             // 0.0
/*1286 */     case TARGET_NR_sched_setscheduler:                                                  // 0.0
/*1288 */         goto unimplemented;                                                             // 0.0
/*1290 */     case TARGET_NR_sched_getscheduler:                                                  // 0.0
/*1292 */         goto unimplemented;                                                             // 0.0
/*1294 */     case TARGET_NR_sched_yield:                                                         // 0.0
/*1296 */         ret = get_errno(sched_yield());                                                 // 0.0
/*1298 */         break;                                                                          // 0.0
/*1300 */     case TARGET_NR_sched_get_priority_max:                                              // 0.0
/*1302 */     case TARGET_NR_sched_get_priority_min:                                              // 0.0
/*1304 */     case TARGET_NR_sched_rr_get_interval:                                               // 0.0
/*1306 */     case TARGET_NR_nanosleep:                                                           // 0.0
/*1308 */     case TARGET_NR_mremap:                                                              // 0.0
/*1310 */     case TARGET_NR_setresuid:                                                           // 0.0
/*1312 */     case TARGET_NR_getresuid:                                                           // 0.0
/*1314 */     case TARGET_NR_vm86:                                                                // 0.0
/*1316 */     case TARGET_NR_query_module:                                                        // 0.0
/*1318 */     case TARGET_NR_poll:                                                                // 0.0
/*1320 */     case TARGET_NR_nfsservctl:                                                          // 0.0
/*1322 */     case TARGET_NR_setresgid:                                                           // 0.0
/*1324 */     case TARGET_NR_getresgid:                                                           // 0.0
/*1326 */     case TARGET_NR_prctl:                                                               // 0.0
/*1328 */     case TARGET_NR_rt_sigreturn:                                                        // 0.0
/*1330 */     case TARGET_NR_rt_sigaction:                                                        // 0.0
/*1332 */     case TARGET_NR_rt_sigprocmask:                                                      // 0.0
/*1334 */     case TARGET_NR_rt_sigpending:                                                       // 0.0
/*1336 */     case TARGET_NR_rt_sigtimedwait:                                                     // 0.0
/*1338 */     case TARGET_NR_rt_sigqueueinfo:                                                     // 0.0
/*1340 */     case TARGET_NR_rt_sigsuspend:                                                       // 0.0
/*1342 */     case TARGET_NR_pread:                                                               // 0.0
/*1344 */     case TARGET_NR_pwrite:                                                              // 0.0
/*1346 */         goto unimplemented;                                                             // 0.0
/*1348 */     case TARGET_NR_chown:                                                               // 0.0
/*1350 */         ret = get_errno(chown((const char *)arg1, arg2, arg3));                         // 0.0
/*1352 */         break;                                                                          // 0.0
/*1354 */     case TARGET_NR_getcwd:                                                              // 0.0
/*1356 */         ret = get_errno(sys_getcwd1((char *)arg1, arg2));                               // 0.0
/*1358 */         break;                                                                          // 0.0
/*1360 */     case TARGET_NR_capget:                                                              // 0.0
/*1362 */     case TARGET_NR_capset:                                                              // 0.0
/*1364 */     case TARGET_NR_sigaltstack:                                                         // 0.0
/*1366 */     case TARGET_NR_sendfile:                                                            // 0.0
/*1368 */     case TARGET_NR_getpmsg:                                                             // 0.0
/*1370 */     case TARGET_NR_putpmsg:                                                             // 0.0
/*1372 */     case TARGET_NR_vfork:                                                               // 0.0
/*1374 */         ret = get_errno(vfork());                                                       // 0.0
/*1376 */         break;                                                                          // 0.0
/*1378 */     case TARGET_NR_ugetrlimit:                                                          // 0.0
/*1380 */     case TARGET_NR_truncate64:                                                          // 0.0
/*1382 */     case TARGET_NR_ftruncate64:                                                         // 0.0
/*1384 */     case TARGET_NR_stat64:                                                              // 0.0
/*1386 */     case TARGET_NR_lstat64:                                                             // 0.0
/*1388 */     case TARGET_NR_fstat64:                                                             // 0.0
/*1390 */     case TARGET_NR_lchown32:                                                            // 0.0
/*1392 */     case TARGET_NR_getuid32:                                                            // 0.0
/*1394 */     case TARGET_NR_getgid32:                                                            // 0.0
/*1396 */     case TARGET_NR_geteuid32:                                                           // 0.0
/*1398 */     case TARGET_NR_getegid32:                                                           // 0.0
/*1400 */     case TARGET_NR_setreuid32:                                                          // 0.0
/*1402 */     case TARGET_NR_setregid32:                                                          // 0.0
/*1404 */     case TARGET_NR_getgroups32:                                                         // 0.0
/*1406 */     case TARGET_NR_setgroups32:                                                         // 0.0
/*1408 */     case TARGET_NR_fchown32:                                                            // 0.0
/*1410 */     case TARGET_NR_setresuid32:                                                         // 0.0
/*1412 */     case TARGET_NR_getresuid32:                                                         // 0.0
/*1414 */     case TARGET_NR_setresgid32:                                                         // 0.0
/*1416 */     case TARGET_NR_getresgid32:                                                         // 0.0
/*1418 */     case TARGET_NR_chown32:                                                             // 0.0
/*1420 */     case TARGET_NR_setuid32:                                                            // 0.0
/*1422 */     case TARGET_NR_setgid32:                                                            // 0.0
/*1424 */     case TARGET_NR_setfsuid32:                                                          // 0.0
/*1426 */     case TARGET_NR_setfsgid32:                                                          // 0.0
/*1428 */     case TARGET_NR_pivot_root:                                                          // 0.0
/*1430 */     case TARGET_NR_mincore:                                                             // 0.0
/*1432 */     case TARGET_NR_madvise:                                                             // 0.0
/*1434 */     case TARGET_NR_getdents64:                                                          // 0.0
/*1436 */     case TARGET_NR_fcntl64:                                                             // 0.0
/*1438 */     case TARGET_NR_security:                                                            // 0.0
/*1440 */         goto unimplemented;                                                             // 0.0
/*1442 */     case TARGET_NR_gettid:                                                              // 0.0
/*1444 */         ret = get_errno(gettid());                                                      // 0.0
/*1446 */         break;                                                                          // 0.0
/*1448 */     case TARGET_NR_readahead:                                                           // 0.0
/*1450 */     case TARGET_NR_setxattr:                                                            // 0.0
/*1452 */     case TARGET_NR_lsetxattr:                                                           // 0.0
/*1454 */     case TARGET_NR_fsetxattr:                                                           // 0.0
/*1456 */     case TARGET_NR_getxattr:                                                            // 0.0
/*1458 */     case TARGET_NR_lgetxattr:                                                           // 0.0
/*1460 */     case TARGET_NR_fgetxattr:                                                           // 0.0
/*1462 */     case TARGET_NR_listxattr:                                                           // 0.0
/*1464 */     case TARGET_NR_llistxattr:                                                          // 0.0
/*1466 */     case TARGET_NR_flistxattr:                                                          // 0.0
/*1468 */     case TARGET_NR_removexattr:                                                         // 0.0
/*1470 */     case TARGET_NR_lremovexattr:                                                        // 0.0
/*1472 */     case TARGET_NR_fremovexattr:                                                        // 0.0
/*1474 */         goto unimplemented;                                                             // 0.0
/*1476 */     default:                                                                            // 0.0
/*1478 */     unimplemented:                                                                      // 0.0
/*1480 */         gemu_log("Unsupported syscall: %d\n", num);                                     // 0.0
/*1482 */         ret = -ENOSYS;                                                                  // 0.0
/*1484 */         break;                                                                          // 0.0
/*1486 */     }                                                                                   // 0.0
/*1488 */  fail:                                                                                  // 0.0
/*1490 */     return ret;                                                                         // 0.0
/*1492 */ }                                                                                       // 0.0
