// commit message qemu@200668ba08 (target=0, prob=0.45858794, correct=True): Do not drop global mutex for polled main loop runs
/*0  */ void main_loop_wait(int nonblocking)                                         // (17) 0.02178
/*2  */ {                                                                            // (31) 0.00198
/*4  */     fd_set rfds, wfds, xfds;                                                 // (7) 0.03762
/*6  */     int ret, nfds;                                                           // (22) 0.0198
/*8  */     struct timeval tv;                                                       // (25) 0.01584
/*10 */     int timeout;                                                             // (28) 0.01188
/*14 */     if (nonblocking)                                                         // (26) 0.01584
/*16 */         timeout = 0;                                                         // (19) 0.02178
/*18 */     else {                                                                   // (29) 0.009901
/*20 */         timeout = qemu_calculate_timeout();                                  // (5) 0.03762
/*22 */         qemu_bh_update_timeout(&timeout);                                    // (6) 0.03762
/*24 */     }                                                                        // (30) 0.007921
/*28 */     os_host_main_loop_wait(&timeout);                                        // (12) 0.0297
/*32 */     tv.tv_sec = timeout / 1000;                                              // (15) 0.02574
/*34 */     tv.tv_usec = (timeout % 1000) * 1000;                                    // (8) 0.03564
/*38 */     /* poll any events */                                                    // (27) 0.01584
/*40 */     /* XXX: separate device handlers from system ones */                     // (14) 0.02574
/*42 */     nfds = -1;                                                               // (23) 0.0198
/*44 */     FD_ZERO(&rfds);                                                          // (18) 0.02178
/*46 */     FD_ZERO(&wfds);                                                          // (16) 0.02376
/*48 */     FD_ZERO(&xfds);                                                          // (20) 0.02178
/*50 */     qemu_iohandler_fill(&nfds, &rfds, &wfds, &xfds);                         // (0) 0.05743
/*52 */     slirp_select_fill(&nfds, &rfds, &wfds, &xfds);                           // (2) 0.05545
/*56 */     qemu_mutex_unlock_iothread();                                            // (10) 0.03366
/*58 */     ret = select(nfds + 1, &rfds, &wfds, &xfds, &tv);                        // (1) 0.05743
/*60 */     qemu_mutex_lock_iothread();                                              // (11) 0.03168
/*64 */     qemu_iohandler_poll(&rfds, &wfds, &xfds, ret);                           // (4) 0.05149
/*66 */     slirp_select_poll(&rfds, &wfds, &xfds, (ret < 0));                       // (3) 0.05545
/*70 */     qemu_run_all_timers();                                                   // (13) 0.02772
/*74 */     /* Check bottom-halves last in case any of the earlier events triggered  // (9) 0.03564
/*76 */        them.  */                                                             // (24) 0.0198
/*78 */     qemu_bh_poll();                                                          // (21) 0.02178
/*82 */ }                                                                            // (32) 0.00198
