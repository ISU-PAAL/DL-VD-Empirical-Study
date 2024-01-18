// commit message qemu@74b6ce43e3 (target=1, prob=0.99914134, correct=True): socket: unlink unix socket on remove
/*0 */ static void qio_channel_socket_finalize(Object *obj)  // (2) 0.1302
/*1 */ {                                                     // (8) 0.008128
/*2 */     QIOChannelSocket *ioc = QIO_CHANNEL_SOCKET(obj);  // (0) 0.1951
/*3 */     if (ioc->fd != -1) {                              // (5) 0.1138
/*4 */ #ifdef WIN32                                          // (6) 0.04068
/*5 */         WSAEventSelect(ioc->fd, NULL, 0);             // (1) 0.1707
/*6 */ #endif                                                // (7) 0.01632
/*7 */         closesocket(ioc->fd);                         // (3) 0.1219
/*8 */         ioc->fd = -1;                                 // (4) 0.1219
