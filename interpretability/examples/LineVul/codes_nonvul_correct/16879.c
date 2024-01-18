// commit message qemu@cbcfa0418f (target=0, prob=0.39293915, correct=True): link the main loop and its dependencies into the tools
/*0  */ int qemu_eventfd(int fds[2])              // (6) 0.05447
/*2  */ {                                         // (19) 0.003891
/*4  */ #ifdef CONFIG_EVENTFD                     // (13) 0.03113
/*6  */     int ret;                              // (15) 0.02335
/*10 */     ret = eventfd(0, 0);                  // (9) 0.04669
/*12 */     if (ret >= 0) {                       // (11) 0.03891
/*14 */         fds[0] = ret;                     // (3) 0.05837
/*16 */         qemu_set_cloexec(ret);            // (2) 0.07393
/*18 */         if ((fds[1] = dup(ret)) == -1) {  // (0) 0.09339
/*20 */             close(ret);                   // (4) 0.05837
/*22 */             return -1;                    // (5) 0.05837
/*24 */         }                                 // (14) 0.03113
/*26 */         qemu_set_cloexec(fds[1]);         // (1) 0.0856
/*28 */         return 0;                         // (12) 0.03891
/*30 */     }                                     // (16) 0.01556
/*34 */     if (errno != ENOSYS) {                // (8) 0.05058
/*36 */         return -1;                        // (10) 0.0428
/*38 */     }                                     // (17) 0.01556
/*40 */ #endif                                    // (18) 0.007782
/*44 */     return qemu_pipe(fds);                // (7) 0.05058
/*46 */ }                                         // (20) 0.003891
