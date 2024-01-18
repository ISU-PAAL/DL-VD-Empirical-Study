// commit message qemu@838ef60249 (target=0, prob=0.38731644, correct=True): curl: Eliminate unnecessary use of curl_multi_socket_all
/*0  */ static int curl_sock_cb(CURL *curl, curl_socket_t fd, int action,          // (6) 0.06566
/*2  */                         void *s, void *sp)                                 // (5) 0.07828
/*4  */ {                                                                          // (18) 0.002525
/*6  */     DPRINTF("CURL (AIO): Sock action %d on fd %d\n", action, fd);          // (4) 0.07828
/*8  */     switch (action) {                                                      // (15) 0.0202
/*10 */         case CURL_POLL_IN:                                                 // (9) 0.0404
/*12 */             qemu_aio_set_fd_handler(fd, curl_multi_do, NULL, s);           // (1) 0.09091
/*14 */             break;                                                         // (11) 0.03283
/*16 */         case CURL_POLL_OUT:                                                // (10) 0.0404
/*18 */             qemu_aio_set_fd_handler(fd, NULL, curl_multi_do, s);           // (2) 0.09091
/*20 */             break;                                                         // (12) 0.03283
/*22 */         case CURL_POLL_INOUT:                                              // (8) 0.04293
/*24 */             qemu_aio_set_fd_handler(fd, curl_multi_do, curl_multi_do, s);  // (0) 0.101
/*26 */             break;                                                         // (13) 0.03283
/*28 */         case CURL_POLL_REMOVE:                                             // (7) 0.04545
/*30 */             qemu_aio_set_fd_handler(fd, NULL, NULL, NULL);                 // (3) 0.08081
/*32 */             break;                                                         // (14) 0.03283
/*34 */     }                                                                      // (17) 0.0101
/*38 */     return 0;                                                              // (16) 0.01515
/*40 */ }                                                                          // (19) 0.002525
