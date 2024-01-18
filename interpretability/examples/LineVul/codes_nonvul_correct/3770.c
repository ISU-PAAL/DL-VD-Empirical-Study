// commit message qemu@bd269ebc82 (target=0, prob=0.045586213, correct=True): sockets: Limit SocketAddressLegacy to external interfaces
/*0  */ int qio_channel_socket_dgram_sync(QIOChannelSocket *ioc,              // (8) 0.05817
/*2  */                                   SocketAddressLegacy *localAddr,     // (0) 0.1163
/*4  */                                   SocketAddressLegacy *remoteAddr,    // (1) 0.1163
/*6  */                                   Error **errp)                       // (2) 0.1053
/*8  */ {                                                                     // (17) 0.00277
/*10 */     int fd;                                                           // (13) 0.01939
/*14 */     trace_qio_channel_socket_dgram_sync(ioc, localAddr, remoteAddr);  // (4) 0.07756
/*16 */     fd = socket_dgram(remoteAddr, localAddr, errp);                   // (7) 0.06094
/*18 */     if (fd < 0) {                                                     // (12) 0.0277
/*20 */         trace_qio_channel_socket_dgram_fail(ioc);                     // (5) 0.06648
/*22 */         return -1;                                                    // (9) 0.03047
/*24 */     }                                                                 // (15) 0.01108
/*28 */     trace_qio_channel_socket_dgram_complete(ioc, fd);                 // (6) 0.06371
/*30 */     if (qio_channel_socket_set_fd(ioc, fd, errp) < 0) {               // (3) 0.08033
/*32 */         close(fd);                                                    // (10) 0.03047
/*34 */         return -1;                                                    // (11) 0.03047
/*36 */     }                                                                 // (16) 0.01108
/*40 */     return 0;                                                         // (14) 0.01662
/*42 */ }                                                                     // (18) 0.00277
