// commit message qemu@60fe637bf0 (target=1, prob=0.58911175, correct=True): Start migrating migration code into a migration directory
/*0  */ void tcp_start_incoming_migration(const char *host_port, Error **errp)  // (3) 0.1394
/*2  */ {                                                                       // (8) 0.006061
/*4  */     int s;                                                              // (6) 0.03636
/*8  */     s = inet_listen(host_port, NULL, 256, SOCK_STREAM, 0, errp);        // (2) 0.1818
/*10 */     if (s < 0) {                                                        // (4) 0.06061
/*12 */         return;                                                         // (5) 0.05455
/*14 */     }                                                                   // (7) 0.02424
/*18 */     qemu_set_fd_handler2(s, NULL, tcp_accept_incoming_migration, NULL,  // (1) 0.1818
/*20 */                          (void *)(intptr_t)s);                          // (0) 0.2121
/*22 */ }                                                                       // (9) 0.006061
