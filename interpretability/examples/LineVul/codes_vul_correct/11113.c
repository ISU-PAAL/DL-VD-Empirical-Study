// commit message qemu@ecbddbb106 (target=1, prob=0.999067, correct=True): main-loop: Acquire main_context lock around os_host_main_loop_wait.
/*0  */ static int os_host_main_loop_wait(int64_t timeout)                              // (8) 0.03516
/*1  */ {                                                                               // (31) 0.001953
/*2  */     GMainContext *context = g_main_context_default();                           // (10) 0.0332
/*3  */     GPollFD poll_fds[1024 * 2]; /* this is probably overkill */                 // (4) 0.04297
/*4  */     int select_ret = 0;                                                         // (22) 0.01953
/*5  */     int g_poll_ret, ret, i, n_poll_fds;                                         // (5) 0.04102
/*6  */     PollingEntry *pe;                                                           // (24) 0.01758
/*7  */     WaitObjects *w = &wait_objects;                                             // (14) 0.02734
/*8  */     gint poll_timeout;                                                          // (25) 0.01758
/*9  */     int64_t poll_timeout_ns;                                                    // (15) 0.02539
/*10 */     static struct timeval tv0;                                                  // (21) 0.01953
/*11 */     fd_set rfds, wfds, xfds;                                                    // (7) 0.03711
/*12 */     int nfds;                                                                   // (27) 0.01562
/*13 */     /* XXX: need to suppress polling by better using win32 events */            // (9) 0.0332
/*14 */     ret = 0;                                                                    // (28) 0.01367
/*15 */     for (pe = first_polling_entry; pe != NULL; pe = pe->next) {                 // (3) 0.04883
/*16 */         ret |= pe->func(pe->opaque);                                            // (6) 0.03711
/*17 */     }                                                                           // (29) 0.007813
/*18 */     if (ret != 0) {                                                             // (20) 0.01953
/*19 */         return ret;                                                             // (23) 0.01953
/*20 */     }                                                                           // (30) 0.007812
/*21 */     FD_ZERO(&rfds);                                                             // (18) 0.02148
/*22 */     FD_ZERO(&wfds);                                                             // (16) 0.02344
/*23 */     FD_ZERO(&xfds);                                                             // (19) 0.02148
/*24 */     nfds = pollfds_fill(gpollfds, &rfds, &wfds, &xfds);                         // (2) 0.06055
/*25 */     if (nfds >= 0) {                                                            // (17) 0.02344
/*26 */         select_ret = select(nfds + 1, &rfds, &wfds, &xfds, &tv0);               // (1) 0.07031
/*27 */         if (select_ret != 0) {                                                  // (12) 0.03125
/*28 */             timeout = 0;                                                        // (13) 0.0293
/*29 */         }                                                                       // (26) 0.01562
/*30 */         if (select_ret > 0) {                                                   // (11) 0.03125
/*31 */             pollfds_poll(gpollfds, nfds, &rfds, &wfds, &xfds);                  // (0) 0.07617
/*32 */         }                                                                       // 0.0
/*33 */     }                                                                           // 0.0
/*34 */     g_main_context_prepare(context, &max_priority);                             // 0.0
/*35 */     n_poll_fds = g_main_context_query(context, max_priority, &poll_timeout,     // 0.0
/*36 */                                       poll_fds, ARRAY_SIZE(poll_fds));          // 0.0
/*37 */     g_assert(n_poll_fds <= ARRAY_SIZE(poll_fds));                               // 0.0
/*38 */     for (i = 0; i < w->num; i++) {                                              // 0.0
/*39 */         poll_fds[n_poll_fds + i].fd = (DWORD_PTR)w->events[i];                  // 0.0
/*40 */         poll_fds[n_poll_fds + i].events = G_IO_IN;                              // 0.0
/*41 */     }                                                                           // 0.0
/*42 */     if (poll_timeout < 0) {                                                     // 0.0
/*43 */         poll_timeout_ns = -1;                                                   // 0.0
/*44 */     } else {                                                                    // 0.0
/*45 */         poll_timeout_ns = (int64_t)poll_timeout * (int64_t)SCALE_MS;            // 0.0
/*46 */     }                                                                           // 0.0
/*47 */     poll_timeout_ns = qemu_soonest_timeout(poll_timeout_ns, timeout);           // 0.0
/*48 */     qemu_mutex_unlock_iothread();                                               // 0.0
/*49 */     g_poll_ret = qemu_poll_ns(poll_fds, n_poll_fds + w->num, poll_timeout_ns);  // 0.0
/*50 */     qemu_mutex_lock_iothread();                                                 // 0.0
/*51 */     if (g_poll_ret > 0) {                                                       // 0.0
/*52 */         for (i = 0; i < w->num; i++) {                                          // 0.0
/*53 */             w->revents[i] = poll_fds[n_poll_fds + i].revents;                   // 0.0
/*54 */         }                                                                       // 0.0
/*55 */         for (i = 0; i < w->num; i++) {                                          // 0.0
/*56 */             if (w->revents[i] && w->func[i]) {                                  // 0.0
/*57 */                 w->func[i](w->opaque[i]);                                       // 0.0
/*58 */             }                                                                   // 0.0
/*59 */         }                                                                       // 0.0
/*60 */     }                                                                           // 0.0
/*61 */     if (g_main_context_check(context, max_priority, poll_fds, n_poll_fds)) {    // 0.0
/*62 */         g_main_context_dispatch(context);                                       // 0.0
/*63 */     }                                                                           // 0.0
/*64 */     return select_ret || g_poll_ret;                                            // 0.0
/*65 */ }                                                                               // 0.0
