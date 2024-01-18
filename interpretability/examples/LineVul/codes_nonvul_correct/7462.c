// commit message qemu@90e26f5aac (target=0, prob=0.48193496, correct=True): target-arm/arm-semi.c: In SYS_HEAPINFO use correct type for 'limit'
/*0   */ target_ulong do_arm_semihosting(CPUARMState *env)                                // (5) 0.03711
/*2   */ {                                                                                // (34) 0.001953
/*4   */     ARMCPU *cpu = arm_env_get_cpu(env);                                          // (6) 0.03711
/*6   */     CPUState *cs = CPU(cpu);                                                     // (19) 0.02344
/*8   */     target_ulong args;                                                           // (22) 0.01758
/*10  */     target_ulong arg0, arg1, arg2, arg3;                                         // (7) 0.03711
/*12  */     char * s;                                                                    // (28) 0.01367
/*14  */     int nr;                                                                      // (29) 0.01367
/*16  */     uint32_t ret;                                                                // (23) 0.01758
/*18  */     uint32_t len;                                                                // (24) 0.01758
/*20  */ #ifdef CONFIG_USER_ONLY                                                          // (25) 0.01758
/*22  */     TaskState *ts = cs->opaque;                                                  // (16) 0.02539
/*24  */ #else                                                                            // (33) 0.003906
/*26  */     CPUARMState *ts = env;                                                       // (21) 0.02148
/*28  */ #endif                                                                           // (32) 0.003906
/*32  */     if (is_a64(env)) {                                                           // (17) 0.02539
/*34  */         /* Note that the syscall number is in W0, not X0 */                      // (2) 0.04688
/*36  */         nr = env->xregs[0] & 0xffffffffU;                                        // (1) 0.04883
/*38  */         args = env->xregs[1];                                                    // (9) 0.0332
/*40  */     } else {                                                                     // (30) 0.01172
/*42  */         nr = env->regs[0];                                                       // (10) 0.0332
/*44  */         args = env->regs[1];                                                     // (11) 0.03125
/*46  */     }                                                                            // (31) 0.007812
/*50  */     switch (nr) {                                                                // (26) 0.01562
/*52  */     case TARGET_SYS_OPEN:                                                        // (18) 0.02539
/*54  */         GET_ARG(0);                                                              // (13) 0.02734
/*56  */         GET_ARG(1);                                                              // (14) 0.02734
/*58  */         GET_ARG(2);                                                              // (15) 0.02734
/*60  */         s = lock_user_string(arg0);                                              // (8) 0.03516
/*62  */         if (!s) {                                                                // (20) 0.02344
/*64  */             /* FIXME - should this error code be -TARGET_EFAULT ? */             // (0) 0.05469
/*66  */             return (uint32_t)-1;                                                 // (4) 0.03906
/*68  */         }                                                                        // (27) 0.01562
/*70  */         if (arg1 >= 12) {                                                        // (12) 0.0293
/*72  */             unlock_user(s, arg0, 0);                                             // (3) 0.04297
/*74  */             return (uint32_t)-1;                                                 // 0.0
/*76  */         }                                                                        // 0.0
/*78  */         if (strcmp(s, ":tt") == 0) {                                             // 0.0
/*80  */             int result_fileno = arg1 < 4 ? STDIN_FILENO : STDOUT_FILENO;         // 0.0
/*82  */             unlock_user(s, arg0, 0);                                             // 0.0
/*84  */             return result_fileno;                                                // 0.0
/*86  */         }                                                                        // 0.0
/*88  */         if (use_gdb_syscalls()) {                                                // 0.0
/*90  */             ret = arm_gdb_syscall(cpu, arm_semi_cb, "open,%s,%x,1a4", arg0,      // 0.0
/*92  */                                   (int)arg2+1, gdb_open_modeflags[arg1]);        // 0.0
/*94  */         } else {                                                                 // 0.0
/*96  */             ret = set_swi_errno(ts, open(s, open_modeflags[arg1], 0644));        // 0.0
/*98  */         }                                                                        // 0.0
/*100 */         unlock_user(s, arg0, 0);                                                 // 0.0
/*102 */         return ret;                                                              // 0.0
/*104 */     case TARGET_SYS_CLOSE:                                                       // 0.0
/*106 */         GET_ARG(0);                                                              // 0.0
/*108 */         if (use_gdb_syscalls()) {                                                // 0.0
/*110 */             return arm_gdb_syscall(cpu, arm_semi_cb, "close,%x", arg0);          // 0.0
/*112 */         } else {                                                                 // 0.0
/*114 */             return set_swi_errno(ts, close(arg0));                               // 0.0
/*116 */         }                                                                        // 0.0
/*118 */     case TARGET_SYS_WRITEC:                                                      // 0.0
/*120 */         {                                                                        // 0.0
/*122 */           char c;                                                                // 0.0
/*126 */           if (get_user_u8(c, args))                                              // 0.0
/*128 */               /* FIXME - should this error code be -TARGET_EFAULT ? */           // 0.0
/*130 */               return (uint32_t)-1;                                               // 0.0
/*132 */           /* Write to debug console.  stderr is near enough.  */                 // 0.0
/*134 */           if (use_gdb_syscalls()) {                                              // 0.0
/*136 */                 return arm_gdb_syscall(cpu, arm_semi_cb, "write,2,%x,1", args);  // 0.0
/*138 */           } else {                                                               // 0.0
/*140 */                 return write(STDERR_FILENO, &c, 1);                              // 0.0
/*142 */           }                                                                      // 0.0
/*144 */         }                                                                        // 0.0
/*146 */     case TARGET_SYS_WRITE0:                                                      // 0.0
/*148 */         if (!(s = lock_user_string(args)))                                       // 0.0
/*150 */             /* FIXME - should this error code be -TARGET_EFAULT ? */             // 0.0
/*152 */             return (uint32_t)-1;                                                 // 0.0
/*154 */         len = strlen(s);                                                         // 0.0
/*156 */         if (use_gdb_syscalls()) {                                                // 0.0
/*158 */             return arm_gdb_syscall(cpu, arm_semi_cb, "write,2,%x,%x",            // 0.0
/*160 */                                    args, len);                                   // 0.0
/*162 */         } else {                                                                 // 0.0
/*164 */             ret = write(STDERR_FILENO, s, len);                                  // 0.0
/*166 */         }                                                                        // 0.0
/*168 */         unlock_user(s, args, 0);                                                 // 0.0
/*170 */         return ret;                                                              // 0.0
/*172 */     case TARGET_SYS_WRITE:                                                       // 0.0
/*174 */         GET_ARG(0);                                                              // 0.0
/*176 */         GET_ARG(1);                                                              // 0.0
/*178 */         GET_ARG(2);                                                              // 0.0
/*180 */         len = arg2;                                                              // 0.0
/*182 */         if (use_gdb_syscalls()) {                                                // 0.0
/*184 */             arm_semi_syscall_len = len;                                          // 0.0
/*186 */             return arm_gdb_syscall(cpu, arm_semi_cb, "write,%x,%x,%x",           // 0.0
/*188 */                                    arg0, arg1, len);                             // 0.0
/*190 */         } else {                                                                 // 0.0
/*192 */             s = lock_user(VERIFY_READ, arg1, len, 1);                            // 0.0
/*194 */             if (!s) {                                                            // 0.0
/*196 */                 /* FIXME - should this error code be -TARGET_EFAULT ? */         // 0.0
/*198 */                 return (uint32_t)-1;                                             // 0.0
/*200 */             }                                                                    // 0.0
/*202 */             ret = set_swi_errno(ts, write(arg0, s, len));                        // 0.0
/*204 */             unlock_user(s, arg1, 0);                                             // 0.0
/*206 */             if (ret == (uint32_t)-1)                                             // 0.0
/*208 */                 return -1;                                                       // 0.0
/*210 */             return len - ret;                                                    // 0.0
/*212 */         }                                                                        // 0.0
/*214 */     case TARGET_SYS_READ:                                                        // 0.0
/*216 */         GET_ARG(0);                                                              // 0.0
/*218 */         GET_ARG(1);                                                              // 0.0
/*220 */         GET_ARG(2);                                                              // 0.0
/*222 */         len = arg2;                                                              // 0.0
/*224 */         if (use_gdb_syscalls()) {                                                // 0.0
/*226 */             arm_semi_syscall_len = len;                                          // 0.0
/*228 */             return arm_gdb_syscall(cpu, arm_semi_cb, "read,%x,%x,%x",            // 0.0
/*230 */                                    arg0, arg1, len);                             // 0.0
/*232 */         } else {                                                                 // 0.0
/*234 */             s = lock_user(VERIFY_WRITE, arg1, len, 0);                           // 0.0
/*236 */             if (!s) {                                                            // 0.0
/*238 */                 /* FIXME - should this error code be -TARGET_EFAULT ? */         // 0.0
/*240 */                 return (uint32_t)-1;                                             // 0.0
/*242 */             }                                                                    // 0.0
/*244 */             do {                                                                 // 0.0
/*246 */                 ret = set_swi_errno(ts, read(arg0, s, len));                     // 0.0
/*248 */             } while (ret == -1 && errno == EINTR);                               // 0.0
/*250 */             unlock_user(s, arg1, len);                                           // 0.0
/*252 */             if (ret == (uint32_t)-1)                                             // 0.0
/*254 */                 return -1;                                                       // 0.0
/*256 */             return len - ret;                                                    // 0.0
/*258 */         }                                                                        // 0.0
/*260 */     case TARGET_SYS_READC:                                                       // 0.0
/*262 */        /* XXX: Read from debug console. Not implemented.  */                     // 0.0
/*264 */         return 0;                                                                // 0.0
/*266 */     case TARGET_SYS_ISTTY:                                                       // 0.0
/*268 */         GET_ARG(0);                                                              // 0.0
/*270 */         if (use_gdb_syscalls()) {                                                // 0.0
/*272 */             return arm_gdb_syscall(cpu, arm_semi_cb, "isatty,%x", arg0);         // 0.0
/*274 */         } else {                                                                 // 0.0
/*276 */             return isatty(arg0);                                                 // 0.0
/*278 */         }                                                                        // 0.0
/*280 */     case TARGET_SYS_SEEK:                                                        // 0.0
/*282 */         GET_ARG(0);                                                              // 0.0
/*284 */         GET_ARG(1);                                                              // 0.0
/*286 */         if (use_gdb_syscalls()) {                                                // 0.0
/*288 */             return arm_gdb_syscall(cpu, arm_semi_cb, "lseek,%x,%x,0",            // 0.0
/*290 */                                    arg0, arg1);                                  // 0.0
/*292 */         } else {                                                                 // 0.0
/*294 */             ret = set_swi_errno(ts, lseek(arg0, arg1, SEEK_SET));                // 0.0
/*296 */             if (ret == (uint32_t)-1)                                             // 0.0
/*298 */               return -1;                                                         // 0.0
/*300 */             return 0;                                                            // 0.0
/*302 */         }                                                                        // 0.0
/*304 */     case TARGET_SYS_FLEN:                                                        // 0.0
/*306 */         GET_ARG(0);                                                              // 0.0
/*308 */         if (use_gdb_syscalls()) {                                                // 0.0
/*310 */             return arm_gdb_syscall(cpu, arm_semi_flen_cb, "fstat,%x,%x",         // 0.0
/*312 */                                    arg0, arm_flen_buf(cpu));                     // 0.0
/*314 */         } else {                                                                 // 0.0
/*316 */             struct stat buf;                                                     // 0.0
/*318 */             ret = set_swi_errno(ts, fstat(arg0, &buf));                          // 0.0
/*320 */             if (ret == (uint32_t)-1)                                             // 0.0
/*322 */                 return -1;                                                       // 0.0
/*324 */             return buf.st_size;                                                  // 0.0
/*326 */         }                                                                        // 0.0
/*328 */     case TARGET_SYS_TMPNAM:                                                      // 0.0
/*330 */         /* XXX: Not implemented.  */                                             // 0.0
/*332 */         return -1;                                                               // 0.0
/*334 */     case TARGET_SYS_REMOVE:                                                      // 0.0
/*336 */         GET_ARG(0);                                                              // 0.0
/*338 */         GET_ARG(1);                                                              // 0.0
/*340 */         if (use_gdb_syscalls()) {                                                // 0.0
/*342 */             ret = arm_gdb_syscall(cpu, arm_semi_cb, "unlink,%s",                 // 0.0
/*344 */                                   arg0, (int)arg1+1);                            // 0.0
/*346 */         } else {                                                                 // 0.0
/*348 */             s = lock_user_string(arg0);                                          // 0.0
/*350 */             if (!s) {                                                            // 0.0
/*352 */                 /* FIXME - should this error code be -TARGET_EFAULT ? */         // 0.0
/*354 */                 return (uint32_t)-1;                                             // 0.0
/*356 */             }                                                                    // 0.0
/*358 */             ret =  set_swi_errno(ts, remove(s));                                 // 0.0
/*360 */             unlock_user(s, arg0, 0);                                             // 0.0
/*362 */         }                                                                        // 0.0
/*364 */         return ret;                                                              // 0.0
/*366 */     case TARGET_SYS_RENAME:                                                      // 0.0
/*368 */         GET_ARG(0);                                                              // 0.0
/*370 */         GET_ARG(1);                                                              // 0.0
/*372 */         GET_ARG(2);                                                              // 0.0
/*374 */         GET_ARG(3);                                                              // 0.0
/*376 */         if (use_gdb_syscalls()) {                                                // 0.0
/*378 */             return arm_gdb_syscall(cpu, arm_semi_cb, "rename,%s,%s",             // 0.0
/*380 */                                    arg0, (int)arg1+1, arg2, (int)arg3+1);        // 0.0
/*382 */         } else {                                                                 // 0.0
/*384 */             char *s2;                                                            // 0.0
/*386 */             s = lock_user_string(arg0);                                          // 0.0
/*388 */             s2 = lock_user_string(arg2);                                         // 0.0
/*390 */             if (!s || !s2)                                                       // 0.0
/*392 */                 /* FIXME - should this error code be -TARGET_EFAULT ? */         // 0.0
/*394 */                 ret = (uint32_t)-1;                                              // 0.0
/*396 */             else                                                                 // 0.0
/*398 */                 ret = set_swi_errno(ts, rename(s, s2));                          // 0.0
/*400 */             if (s2)                                                              // 0.0
/*402 */                 unlock_user(s2, arg2, 0);                                        // 0.0
/*404 */             if (s)                                                               // 0.0
/*406 */                 unlock_user(s, arg0, 0);                                         // 0.0
/*408 */             return ret;                                                          // 0.0
/*410 */         }                                                                        // 0.0
/*412 */     case TARGET_SYS_CLOCK:                                                       // 0.0
/*414 */         return clock() / (CLOCKS_PER_SEC / 100);                                 // 0.0
/*416 */     case TARGET_SYS_TIME:                                                        // 0.0
/*418 */         return set_swi_errno(ts, time(NULL));                                    // 0.0
/*420 */     case TARGET_SYS_SYSTEM:                                                      // 0.0
/*422 */         GET_ARG(0);                                                              // 0.0
/*424 */         GET_ARG(1);                                                              // 0.0
/*426 */         if (use_gdb_syscalls()) {                                                // 0.0
/*428 */             return arm_gdb_syscall(cpu, arm_semi_cb, "system,%s",                // 0.0
/*430 */                                    arg0, (int)arg1+1);                           // 0.0
/*432 */         } else {                                                                 // 0.0
/*434 */             s = lock_user_string(arg0);                                          // 0.0
/*436 */             if (!s) {                                                            // 0.0
/*438 */                 /* FIXME - should this error code be -TARGET_EFAULT ? */         // 0.0
/*440 */                 return (uint32_t)-1;                                             // 0.0
/*442 */             }                                                                    // 0.0
/*444 */             ret = set_swi_errno(ts, system(s));                                  // 0.0
/*446 */             unlock_user(s, arg0, 0);                                             // 0.0
/*448 */             return ret;                                                          // 0.0
/*450 */         }                                                                        // 0.0
/*452 */     case TARGET_SYS_ERRNO:                                                       // 0.0
/*454 */ #ifdef CONFIG_USER_ONLY                                                          // 0.0
/*456 */         return ts->swi_errno;                                                    // 0.0
/*458 */ #else                                                                            // 0.0
/*460 */         return syscall_err;                                                      // 0.0
/*462 */ #endif                                                                           // 0.0
/*464 */     case TARGET_SYS_GET_CMDLINE:                                                 // 0.0
/*466 */         {                                                                        // 0.0
/*468 */             /* Build a command-line from the original argv.                      // 0.0
/*470 */              *                                                                   // 0.0
/*472 */              * The inputs are:                                                   // 0.0
/*474 */              *     * arg0, pointer to a buffer of at least the size              // 0.0
/*476 */              *               specified in arg1.                                  // 0.0
/*478 */              *     * arg1, size of the buffer pointed to by arg0 in              // 0.0
/*480 */              *               bytes.                                              // 0.0
/*482 */              *                                                                   // 0.0
/*484 */              * The outputs are:                                                  // 0.0
/*486 */              *     * arg0, pointer to null-terminated string of the              // 0.0
/*488 */              *               command line.                                       // 0.0
/*490 */              *     * arg1, length of the string pointed to by arg0.              // 0.0
/*492 */              */                                                                  // 0.0
/*496 */             char *output_buffer;                                                 // 0.0
/*498 */             size_t input_size;                                                   // 0.0
/*500 */             size_t output_size;                                                  // 0.0
/*502 */             int status = 0;                                                      // 0.0
/*504 */ #if !defined(CONFIG_USER_ONLY)                                                   // 0.0
/*506 */             const char *cmdline;                                                 // 0.0
/*508 */ #endif                                                                           // 0.0
/*510 */             GET_ARG(0);                                                          // 0.0
/*512 */             GET_ARG(1);                                                          // 0.0
/*514 */             input_size = arg1;                                                   // 0.0
/*516 */             /* Compute the size of the output string.  */                        // 0.0
/*518 */ #if !defined(CONFIG_USER_ONLY)                                                   // 0.0
/*520 */             cmdline = semihosting_get_cmdline();                                 // 0.0
/*522 */             if (cmdline == NULL) {                                               // 0.0
/*524 */                 cmdline = ""; /* Default to an empty line. */                    // 0.0
/*526 */             }                                                                    // 0.0
/*528 */             output_size = strlen(cmdline) + 1; /* Count terminating 0. */        // 0.0
/*530 */ #else                                                                            // 0.0
/*532 */             unsigned int i;                                                      // 0.0
/*536 */             output_size = ts->info->arg_end - ts->info->arg_start;               // 0.0
/*538 */             if (!output_size) {                                                  // 0.0
/*540 */                 /* We special-case the "empty command line" case (argc==0).      // 0.0
/*542 */                    Just provide the terminating 0. */                            // 0.0
/*544 */                 output_size = 1;                                                 // 0.0
/*546 */             }                                                                    // 0.0
/*548 */ #endif                                                                           // 0.0
/*552 */             if (output_size > input_size) {                                      // 0.0
/*554 */                  /* Not enough space to store command-line arguments.  */        // 0.0
/*556 */                 return -1;                                                       // 0.0
/*558 */             }                                                                    // 0.0
/*562 */             /* Adjust the command-line length.  */                               // 0.0
/*564 */             if (SET_ARG(1, output_size - 1)) {                                   // 0.0
/*566 */                 /* Couldn't write back to argument block */                      // 0.0
/*568 */                 return -1;                                                       // 0.0
/*570 */             }                                                                    // 0.0
/*574 */             /* Lock the buffer on the ARM side.  */                              // 0.0
/*576 */             output_buffer = lock_user(VERIFY_WRITE, arg0, output_size, 0);       // 0.0
/*578 */             if (!output_buffer) {                                                // 0.0
/*580 */                 return -1;                                                       // 0.0
/*582 */             }                                                                    // 0.0
/*586 */             /* Copy the command-line arguments.  */                              // 0.0
/*588 */ #if !defined(CONFIG_USER_ONLY)                                                   // 0.0
/*590 */             pstrcpy(output_buffer, output_size, cmdline);                        // 0.0
/*592 */ #else                                                                            // 0.0
/*594 */             if (output_size == 1) {                                              // 0.0
/*596 */                 /* Empty command-line.  */                                       // 0.0
/*598 */                 output_buffer[0] = '\0';                                         // 0.0
/*600 */                 goto out;                                                        // 0.0
/*602 */             }                                                                    // 0.0
/*606 */             if (copy_from_user(output_buffer, ts->info->arg_start,               // 0.0
/*608 */                                output_size)) {                                   // 0.0
/*610 */                 status = -1;                                                     // 0.0
/*612 */                 goto out;                                                        // 0.0
/*614 */             }                                                                    // 0.0
/*618 */             /* Separate arguments by white spaces.  */                           // 0.0
/*620 */             for (i = 0; i < output_size - 1; i++) {                              // 0.0
/*622 */                 if (output_buffer[i] == 0) {                                     // 0.0
/*624 */                     output_buffer[i] = ' ';                                      // 0.0
/*626 */                 }                                                                // 0.0
/*628 */             }                                                                    // 0.0
/*630 */         out:                                                                     // 0.0
/*632 */ #endif                                                                           // 0.0
/*634 */             /* Unlock the buffer on the ARM side.  */                            // 0.0
/*636 */             unlock_user(output_buffer, arg0, output_size);                       // 0.0
/*640 */             return status;                                                       // 0.0
/*642 */         }                                                                        // 0.0
/*644 */     case TARGET_SYS_HEAPINFO:                                                    // 0.0
/*646 */         {                                                                        // 0.0
/*648 */             target_ulong retvals[4];                                             // 0.0
/*650 */             uint32_t limit;                                                      // 0.0
/*652 */             int i;                                                               // 0.0
/*656 */             GET_ARG(0);                                                          // 0.0
/*660 */ #ifdef CONFIG_USER_ONLY                                                          // 0.0
/*662 */             /* Some C libraries assume the heap immediately follows .bss, so     // 0.0
/*664 */                allocate it using sbrk.  */                                       // 0.0
/*666 */             if (!ts->heap_limit) {                                               // 0.0
/*668 */                 abi_ulong ret;                                                   // 0.0
/*672 */                 ts->heap_base = do_brk(0);                                       // 0.0
/*674 */                 limit = ts->heap_base + ARM_ANGEL_HEAP_SIZE;                     // 0.0
/*676 */                 /* Try a big heap, and reduce the size if that fails.  */        // 0.0
/*678 */                 for (;;) {                                                       // 0.0
/*680 */                     ret = do_brk(limit);                                         // 0.0
/*682 */                     if (ret >= limit) {                                          // 0.0
/*684 */                         break;                                                   // 0.0
/*686 */                     }                                                            // 0.0
/*688 */                     limit = (ts->heap_base >> 1) + (limit >> 1);                 // 0.0
/*690 */                 }                                                                // 0.0
/*692 */                 ts->heap_limit = limit;                                          // 0.0
/*694 */             }                                                                    // 0.0
/*698 */             retvals[0] = ts->heap_base;                                          // 0.0
/*700 */             retvals[1] = ts->heap_limit;                                         // 0.0
/*702 */             retvals[2] = ts->stack_base;                                         // 0.0
/*704 */             retvals[3] = 0; /* Stack limit.  */                                  // 0.0
/*706 */ #else                                                                            // 0.0
/*708 */             limit = ram_size;                                                    // 0.0
/*710 */             /* TODO: Make this use the limit of the loaded application.  */      // 0.0
/*712 */             retvals[0] = limit / 2;                                              // 0.0
/*714 */             retvals[1] = limit;                                                  // 0.0
/*716 */             retvals[2] = limit; /* Stack base */                                 // 0.0
/*718 */             retvals[3] = 0; /* Stack limit.  */                                  // 0.0
/*720 */ #endif                                                                           // 0.0
/*724 */             for (i = 0; i < ARRAY_SIZE(retvals); i++) {                          // 0.0
/*726 */                 bool fail;                                                       // 0.0
/*730 */                 if (is_a64(env)) {                                               // 0.0
/*732 */                     fail = put_user_u64(retvals[i], arg0 + i * 8);               // 0.0
/*734 */                 } else {                                                         // 0.0
/*736 */                     fail = put_user_u32(retvals[i], arg0 + i * 4);               // 0.0
/*738 */                 }                                                                // 0.0
/*742 */                 if (fail) {                                                      // 0.0
/*744 */                     /* Couldn't write back to argument block */                  // 0.0
/*746 */                     return -1;                                                   // 0.0
/*748 */                 }                                                                // 0.0
/*750 */             }                                                                    // 0.0
/*752 */             return 0;                                                            // 0.0
/*754 */         }                                                                        // 0.0
/*756 */     case TARGET_SYS_EXIT:                                                        // 0.0
/*758 */         if (is_a64(env)) {                                                       // 0.0
/*760 */             /* The A64 version of this call takes a parameter block,             // 0.0
/*762 */              * so the application-exit type can return a subcode which           // 0.0
/*764 */              * is the exit status code from the application.                     // 0.0
/*766 */              */                                                                  // 0.0
/*768 */             GET_ARG(0);                                                          // 0.0
/*770 */             GET_ARG(1);                                                          // 0.0
/*774 */             if (arg0 == ADP_Stopped_ApplicationExit) {                           // 0.0
/*776 */                 ret = arg1;                                                      // 0.0
/*778 */             } else {                                                             // 0.0
/*780 */                 ret = 1;                                                         // 0.0
/*782 */             }                                                                    // 0.0
/*784 */         } else {                                                                 // 0.0
/*786 */             /* ARM specifies only Stopped_ApplicationExit as normal              // 0.0
/*788 */              * exit, everything else is considered an error */                   // 0.0
/*790 */             ret = (args == ADP_Stopped_ApplicationExit) ? 0 : 1;                 // 0.0
/*792 */         }                                                                        // 0.0
/*794 */         gdb_exit(env, ret);                                                      // 0.0
/*796 */         exit(ret);                                                               // 0.0
/*798 */     case TARGET_SYS_SYNCCACHE:                                                   // 0.0
/*800 */         /* Clean the D-cache and invalidate the I-cache for the specified        // 0.0
/*802 */          * virtual address range. This is a nop for us since we don't            // 0.0
/*804 */          * implement caches. This is only present on A64.                        // 0.0
/*806 */          */                                                                      // 0.0
/*808 */         if (is_a64(env)) {                                                       // 0.0
/*810 */             return 0;                                                            // 0.0
/*812 */         }                                                                        // 0.0
/*814 */         /* fall through -- invalid for A32/T32 */                                // 0.0
/*816 */     default:                                                                     // 0.0
/*818 */         fprintf(stderr, "qemu: Unsupported SemiHosting SWI 0x%02x\n", nr);       // 0.0
/*820 */         cpu_dump_state(cs, stderr, fprintf, 0);                                  // 0.0
/*822 */         abort();                                                                 // 0.0
/*824 */     }                                                                            // 0.0
/*826 */ }                                                                                // 0.0
