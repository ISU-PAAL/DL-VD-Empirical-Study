// commit message qemu@8d0bcba837 (target=0, prob=0.42750034, correct=True): net: Convert to new qapi union layout
/*0   */ int net_init_socket(const NetClientOptions *opts, const char *name,               // (9) 0.03906
/*2   */                     NetClientState *peer, Error **errp)                           // (4) 0.05859
/*4   */ {                                                                                 // (26) 0.001953
/*6   */     /* FIXME error_setg(errp, ...) on failure */                                  // (10) 0.03711
/*8   */     Error *err = NULL;                                                            // (22) 0.01758
/*10  */     const NetdevSocketOptions *sock;                                              // (17) 0.02344
/*14  */     assert(opts->kind == NET_CLIENT_OPTIONS_KIND_SOCKET);                         // (6) 0.05078
/*16  */     sock = opts->socket;                                                          // (21) 0.01953
/*20  */     if (sock->has_fd + sock->has_listen + sock->has_connect + sock->has_mcast +   // (1) 0.0625
/*22  */         sock->has_udp != 1) {                                                     // (13) 0.0332
/*24  */         error_report("exactly one of fd=, listen=, connect=, mcast= or udp="      // (0) 0.0625
/*26  */                      " is required");                                             // (8) 0.04687
/*28  */         return -1;                                                                // (20) 0.02148
/*30  */     }                                                                             // (24) 0.007813
/*34  */     if (sock->has_localaddr && !sock->has_mcast && !sock->has_udp) {              // (2) 0.0625
/*36  */         error_report("localaddr= is only valid with mcast= or udp=");             // (7) 0.05078
/*38  */         return -1;                                                                // (18) 0.02148
/*40  */     }                                                                             // (25) 0.007812
/*44  */     if (sock->has_fd) {                                                           // (16) 0.02539
/*46  */         int fd;                                                                   // (19) 0.02148
/*50  */         fd = monitor_fd_param(cur_mon, sock->fd, &err);                           // (5) 0.05273
/*52  */         if (fd == -1) {                                                           // (14) 0.0293
/*54  */             error_report_err(err);                                                // (11) 0.03711
/*56  */             return -1;                                                            // (15) 0.0293
/*58  */         }                                                                         // (23) 0.01562
/*60  */         qemu_set_nonblock(fd);                                                    // (12) 0.03516
/*62  */         if (!net_socket_fd_init(peer, "socket", name, fd, 1)) {                   // (3) 0.05859
/*64  */             return -1;                                                            // 0.0
/*66  */         }                                                                         // 0.0
/*68  */         return 0;                                                                 // 0.0
/*70  */     }                                                                             // 0.0
/*74  */     if (sock->has_listen) {                                                       // 0.0
/*76  */         if (net_socket_listen_init(peer, "socket", name, sock->listen) == -1) {   // 0.0
/*78  */             return -1;                                                            // 0.0
/*80  */         }                                                                         // 0.0
/*82  */         return 0;                                                                 // 0.0
/*84  */     }                                                                             // 0.0
/*88  */     if (sock->has_connect) {                                                      // 0.0
/*90  */         if (net_socket_connect_init(peer, "socket", name, sock->connect) ==       // 0.0
/*92  */             -1) {                                                                 // 0.0
/*94  */             return -1;                                                            // 0.0
/*96  */         }                                                                         // 0.0
/*98  */         return 0;                                                                 // 0.0
/*100 */     }                                                                             // 0.0
/*104 */     if (sock->has_mcast) {                                                        // 0.0
/*106 */         /* if sock->localaddr is missing, it has been initialized to "all bits    // 0.0
/*108 */          * zero" */                                                               // 0.0
/*110 */         if (net_socket_mcast_init(peer, "socket", name, sock->mcast,              // 0.0
/*112 */             sock->localaddr) == -1) {                                             // 0.0
/*114 */             return -1;                                                            // 0.0
/*116 */         }                                                                         // 0.0
/*118 */         return 0;                                                                 // 0.0
/*120 */     }                                                                             // 0.0
/*124 */     assert(sock->has_udp);                                                        // 0.0
/*126 */     if (!sock->has_localaddr) {                                                   // 0.0
/*128 */         error_report("localaddr= is mandatory with udp=");                        // 0.0
/*130 */         return -1;                                                                // 0.0
/*132 */     }                                                                             // 0.0
/*134 */     if (net_socket_udp_init(peer, "socket", name, sock->udp, sock->localaddr) ==  // 0.0
/*136 */         -1) {                                                                     // 0.0
/*138 */         return -1;                                                                // 0.0
/*140 */     }                                                                             // 0.0
/*142 */     return 0;                                                                     // 0.0
/*144 */ }                                                                                 // 0.0
