// commit message qemu@bb16172c52 (target=1, prob=0.9992545, correct=True): gdbstub: Fix fd leak in gdbserver_open() error path
/*0  */ static int gdbserver_open(int port)                                       // (8) 0.03183
/*2  */ {                                                                         // (28) 0.002653
/*4  */     struct sockaddr_in sockaddr;                                          // (11) 0.02918
/*6  */     int fd, val, ret;                                                     // (13) 0.02918
/*10 */     fd = socket(PF_INET, SOCK_STREAM, 0);                                 // (3) 0.0557
/*12 */     if (fd < 0) {                                                         // (19) 0.02653
/*14 */         perror("socket");                                                 // (9) 0.03183
/*16 */         return -1;                                                        // (14) 0.02918
/*18 */     }                                                                     // (24) 0.01061
/*20 */ #ifndef _WIN32                                                            // (21) 0.01857
/*22 */     fcntl(fd, F_SETFD, FD_CLOEXEC);                                       // (2) 0.06101
/*24 */ #endif                                                                    // (27) 0.005305
/*28 */     /* allow fast reuse */                                                // (20) 0.02122
/*30 */     val = 1;                                                              // (22) 0.01857
/*32 */     setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&val, sizeof(val));  // (0) 0.08488
/*36 */     sockaddr.sin_family = AF_INET;                                        // (6) 0.03979
/*38 */     sockaddr.sin_port = htons(port);                                      // (5) 0.03979
/*40 */     sockaddr.sin_addr.s_addr = 0;                                         // (4) 0.04244
/*42 */     ret = bind(fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));       // (1) 0.06631
/*44 */     if (ret < 0) {                                                        // (17) 0.02653
/*46 */         perror("bind");                                                   // (10) 0.03183
/*49 */         return -1;                                                        // (15) 0.02918
/*51 */     }                                                                     // (25) 0.01061
/*53 */     ret = listen(fd, 0);                                                  // (12) 0.02918
/*55 */     if (ret < 0) {                                                        // (18) 0.02653
/*57 */         perror("listen");                                                 // (7) 0.03448
/*60 */         return -1;                                                        // (16) 0.02918
/*62 */     }                                                                     // (26) 0.01061
/*64 */     return fd;                                                            // (23) 0.01857
/*66 */ }                                                                         // (29) 0.002653
