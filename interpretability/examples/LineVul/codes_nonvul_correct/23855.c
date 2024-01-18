// commit message qemu@5819e3e072 (target=0, prob=0.30676958, correct=True): gdbstub: avoid busy loop while waiting for gdb
/*0  */ static void gdb_accept(void)                                            // (18) 0.02284
/*2  */ {                                                                       // (27) 0.002538
/*4  */     GDBState *s;                                                        // (17) 0.02284
/*6  */     struct sockaddr_in sockaddr;                                        // (15) 0.02792
/*8  */     socklen_t len;                                                      // (19) 0.02284
/*10 */     int fd;                                                             // (24) 0.01777
/*14 */     for(;;) {                                                           // (21) 0.0203
/*16 */         len = sizeof(sockaddr);                                         // (7) 0.03807
/*18 */         fd = accept(gdbserver_fd, (struct sockaddr *)&sockaddr, &len);  // (0) 0.07868
/*20 */         if (fd < 0 && errno != EINTR) {                                 // (3) 0.0533
/*22 */             perror("accept");                                           // (5) 0.04061
/*24 */             return;                                                     // (11) 0.03299
/*26 */         } else if (fd >= 0) {                                           // (6) 0.04061
/*28 */ #ifndef _WIN32                                                          // (23) 0.01777
/*30 */             fcntl(fd, F_SETFD, FD_CLOEXEC);                             // (1) 0.07868
/*32 */ #endif                                                                  // (26) 0.005076
/*34 */             break;                                                      // (12) 0.03299
/*36 */         }                                                               // (22) 0.0203
/*38 */     }                                                                   // (25) 0.01015
/*42 */     /* set short latency */                                             // (20) 0.0203
/*44 */     socket_set_nodelay(fd);                                             // (8) 0.03553
/*48 */     s = g_malloc0(sizeof(GDBState));                                    // (4) 0.04569
/*50 */     s->c_cpu = first_cpu;                                               // (10) 0.03299
/*52 */     s->g_cpu = first_cpu;                                               // (9) 0.03299
/*54 */     s->fd = fd;                                                         // (16) 0.02538
/*56 */     gdb_has_xml = false;                                                // (13) 0.03046
/*60 */     gdbserver_state = s;                                                // (14) 0.03046
/*64 */     fcntl(fd, F_SETFL, O_NONBLOCK);                                     // (2) 0.05584
/*66 */ }                                                                       // (28) 0.002538
