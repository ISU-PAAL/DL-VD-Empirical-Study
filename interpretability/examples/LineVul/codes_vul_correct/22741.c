// commit message qemu@40ff6d7e8d (target=1, prob=0.7093605, correct=True): Don't leak file descriptors
/*0  */ int unix_start_incoming_migration(const char *path)                              // (7) 0.03664
/*2  */ {                                                                                // (27) 0.002155
/*4  */     struct sockaddr_un un;                                                       // (16) 0.02155
/*6  */     int sock;                                                                    // (21) 0.01293
/*10 */     dprintf("Attempting to start an incoming migration\n");                      // (9) 0.03448
/*14 */     sock = socket(PF_UNIX, SOCK_STREAM, 0);                                      // (6) 0.0431
/*16 */     if (sock < 0) {                                                              // (15) 0.02371
/*18 */         fprintf(stderr, "Could not open unix socket: %s\n", strerror(errno));    // (2) 0.07328
/*20 */         return -EINVAL;                                                          // (12) 0.02802
/*22 */     }                                                                            // (23) 0.008621
/*26 */     memset(&un, 0, sizeof(un));                                                  // (10) 0.03017
/*28 */     un.sun_family = AF_UNIX;                                                     // (11) 0.03017
/*30 */     snprintf(un.sun_path, sizeof(un.sun_path), "%s", path);                      // (5) 0.05388
/*34 */     unlink(un.sun_path);                                                         // (14) 0.02586
/*36 */     if (bind(sock, (struct sockaddr*) &un, sizeof(un)) < 0) {                    // (4) 0.05603
/*38 */         fprintf(stderr, "bind(unix:%s): %s\n", un.sun_path, strerror(errno));    // (1) 0.08836
/*40 */         goto err;                                                                // (17) 0.02155
/*42 */     }                                                                            // (24) 0.008621
/*44 */     if (listen(sock, 1) < 0) {                                                   // (8) 0.03664
/*46 */         fprintf(stderr, "listen(unix:%s): %s\n", un.sun_path, strerror(errno));  // (0) 0.09052
/*48 */         goto err;                                                                // (18) 0.02155
/*50 */     }                                                                            // (25) 0.008621
/*54 */     qemu_set_fd_handler2(sock, NULL, unix_accept_incoming_migration, NULL,       // (3) 0.06897
/*56 */ 			 (void *)(unsigned long)sock);                                                // (13) 0.02802
/*60 */     return 0;                                                                    // (22) 0.01293
/*64 */ err:                                                                             // (26) 0.00431
/*66 */     close(sock);                                                                 // (20) 0.01724
/*70 */     return -EINVAL;                                                              // (19) 0.0194
/*72 */ }                                                                                // (28) 0.002155
