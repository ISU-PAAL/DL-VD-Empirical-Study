// commit message qemu@dfd100f242 (target=0, prob=0.045156147, correct=True): sockets: Rename SocketAddress to SocketAddressLegacy
/*0  */ int qio_channel_socket_connect_sync(QIOChannelSocket *ioc,  // (6) 0.06557
/*2  */                                     SocketAddress *addr,    // (0) 0.1311
/*4  */                                     Error **errp)           // (1) 0.1311
/*6  */ {                                                           // (16) 0.003279
/*8  */     int fd;                                                 // (12) 0.02295
/*12 */     trace_qio_channel_socket_connect_sync(ioc, addr);       // (5) 0.06885
/*14 */     fd = socket_connect(addr, NULL, NULL, errp);            // (7) 0.0623
/*16 */     if (fd < 0) {                                           // (11) 0.03279
/*18 */         trace_qio_channel_socket_connect_fail(ioc);         // (3) 0.07541
/*20 */         return -1;                                          // (8) 0.03607
/*22 */     }                                                       // (14) 0.01311
/*26 */     trace_qio_channel_socket_connect_complete(ioc, fd);     // (4) 0.07213
/*28 */     if (qio_channel_socket_set_fd(ioc, fd, errp) < 0) {     // (2) 0.09508
/*30 */         close(fd);                                          // (9) 0.03607
/*32 */         return -1;                                          // (10) 0.03607
/*34 */     }                                                       // (15) 0.01311
/*38 */     return 0;                                               // (13) 0.01967
/*40 */ }                                                           // (17) 0.003279
