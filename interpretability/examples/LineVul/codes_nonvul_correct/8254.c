// commit message qemu@185b43386a (target=0, prob=0.3498762, correct=True): nbd: consistently return negative errno values
/*0  */ static int nbd_establish_connection(BlockDriverState *bs)                   // (11) 0.0293
/*2  */ {                                                                           // (31) 0.001953
/*4  */     BDRVNBDState *s = bs->opaque;                                           // (9) 0.03516
/*6  */     int sock;                                                               // (25) 0.01172
/*8  */     int ret;                                                                // (26) 0.01172
/*10 */     off_t size;                                                             // (23) 0.01562
/*12 */     size_t blocksize;                                                       // (21) 0.01758
/*16 */     if (s->host_spec[0] == '/') {                                           // (10) 0.0332
/*18 */         sock = unix_socket_outgoing(s->host_spec);                          // (5) 0.04492
/*20 */     } else {                                                                // (27) 0.01172
/*22 */         sock = tcp_socket_outgoing_spec(s->host_spec);                      // (4) 0.04687
/*24 */     }                                                                       // (28) 0.007812
/*28 */     /* Failed to establish connection */                                    // (20) 0.01758
/*30 */     if (sock < 0) {                                                         // (17) 0.02148
/*32 */         logout("Failed to establish connection to NBD server\n");           // (6) 0.04297
/*34 */         return -errno;                                                      // (15) 0.02344
/*36 */     }                                                                       // (30) 0.007812
/*40 */     /* NBD handshake */                                                     // (24) 0.01562
/*42 */     ret = nbd_receive_negotiate(sock, s->export_name, &s->nbdflags, &size,  // (2) 0.06641
/*44 */                                 &blocksize);                                // (1) 0.06836
/*46 */     if (ret < 0) {                                                          // (19) 0.01953
/*48 */         logout("Failed to negotiate with the NBD server\n");                // (7) 0.04297
/*50 */         closesocket(sock);                                                  // (13) 0.02539
/*52 */         return -errno;                                                      // (16) 0.02344
/*54 */     }                                                                       // (29) 0.007812
/*58 */     /* Now that we're connected, set the socket to be non-blocking and      // (8) 0.03711
/*60 */      * kick the reply mechanism.  */                                        // (14) 0.02344
/*62 */     socket_set_nonblock(sock);                                              // (12) 0.02539
/*64 */     qemu_aio_set_fd_handler(s->sock, nbd_reply_ready, NULL,                 // (3) 0.05859
/*66 */                             nbd_have_request, NULL, s);                     // (0) 0.07422
/*70 */     s->sock = sock;                                                         // (18) 0.01953
/*72 */     s->size = size;                                                         // (22) 0.01758
/*74 */     s->blocksize = blocksize;                                               // 0.0
/*78 */     logout("Established connection with NBD server\n");                     // 0.0
/*80 */     return 0;                                                               // 0.0
/*82 */ }                                                                           // 0.0
