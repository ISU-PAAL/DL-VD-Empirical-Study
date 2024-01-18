// commit message qemu@0f8c289ad5 (target=1, prob=0.4827248, correct=False): net: fix -netdev socket,fd= for UDP sockets
/*0  */ static int net_socket_connect_init(NetClientState *peer,              // (12) 0.03125
/*2  */                                    const char *model,                 // (2) 0.07617
/*4  */                                    const char *name,                  // (1) 0.07617
/*6  */                                    const char *host_str)              // (0) 0.08008
/*8  */ {                                                                     // (25) 0.001953
/*10 */     NetSocketState *s;                                                // (21) 0.01758
/*12 */     int fd, connected, ret;                                           // (17) 0.02148
/*14 */     struct sockaddr_in saddr;                                         // (16) 0.02148
/*18 */     if (parse_host_port(&saddr, host_str) < 0)                        // (9) 0.04102
/*20 */         return -1;                                                    // (18) 0.02148
/*24 */     fd = qemu_socket(PF_INET, SOCK_STREAM, 0);                        // (7) 0.04883
/*26 */     if (fd < 0) {                                                     // (20) 0.01953
/*28 */         perror("socket");                                             // (15) 0.02344
/*30 */         return -1;                                                    // (19) 0.02148
/*32 */     }                                                                 // (24) 0.007812
/*34 */     qemu_set_nonblock(fd);                                            // (13) 0.02734
/*38 */     connected = 0;                                                    // (23) 0.01367
/*40 */     for(;;) {                                                         // (22) 0.01563
/*42 */         ret = connect(fd, (struct sockaddr *)&saddr, sizeof(saddr));  // (6) 0.05273
/*44 */         if (ret < 0) {                                                // (14) 0.02734
/*46 */             if (errno == EINTR || errno == EWOULDBLOCK) {             // (5) 0.05664
/*48 */                 /* continue */                                        // (10) 0.03516
/*50 */             } else if (errno == EINPROGRESS ||                        // (8) 0.04688
/*52 */                        errno == EALREADY ||                           // (3) 0.05859
/*54 */                        errno == EINVAL) {                             // (4) 0.05859
/*56 */                 break;                                                // (11) 0.0332
/*58 */             } else {                                                  // 0.0
/*60 */                 perror("connect");                                    // 0.0
/*62 */                 closesocket(fd);                                      // 0.0
/*64 */                 return -1;                                            // 0.0
/*66 */             }                                                         // 0.0
/*68 */         } else {                                                      // 0.0
/*70 */             connected = 1;                                            // 0.0
/*72 */             break;                                                    // 0.0
/*74 */         }                                                             // 0.0
/*76 */     }                                                                 // 0.0
/*78 */     s = net_socket_fd_init(peer, model, name, fd, connected);         // 0.0
/*80 */     if (!s)                                                           // 0.0
/*82 */         return -1;                                                    // 0.0
/*84 */     snprintf(s->nc.info_str, sizeof(s->nc.info_str),                  // 0.0
/*86 */              "socket: connect to %s:%d",                              // 0.0
/*88 */              inet_ntoa(saddr.sin_addr), ntohs(saddr.sin_port));       // 0.0
/*90 */     return 0;                                                         // 0.0
/*92 */ }                                                                     // 0.0
