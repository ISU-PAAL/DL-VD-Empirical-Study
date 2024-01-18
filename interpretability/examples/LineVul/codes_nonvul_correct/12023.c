// commit message qemu@8dfd5f9651 (target=0, prob=0.13958612, correct=True): io: get rid of bounce buffering in websock write path
/*0  */ static void qio_channel_websock_write_close(QIOChannelWebsock *ioc,             // (6) 0.06053
/*2  */                                             uint16_t code, const char *reason)  // (0) 0.1308
/*4  */ {                                                                               // (17) 0.002421
/*6  */     struct iovec iov;                                                           // (14) 0.02421
/*8  */     buffer_reserve(&ioc->rawoutput, 2 + (reason ? strlen(reason) : 0));         // (5) 0.06538
/*10 */     *(uint16_t *)(ioc->rawoutput.buffer + ioc->rawoutput.offset) =              // (4) 0.0678
/*12 */         cpu_to_be16(code);                                                      // (11) 0.03874
/*14 */     ioc->rawoutput.offset += 2;                                                 // (12) 0.03148
/*16 */     if (reason) {                                                               // (15) 0.01937
/*18 */         buffer_append(&ioc->rawoutput, reason, strlen(reason));                 // (7) 0.05811
/*20 */     }                                                                           // (16) 0.009685
/*22 */     iov.iov_base = ioc->rawoutput.buffer;                                       // (9) 0.04358
/*24 */     iov.iov_len = ioc->rawoutput.offset;                                        // (10) 0.04358
/*26 */     qio_channel_websock_encode(ioc, QIO_CHANNEL_WEBSOCK_OPCODE_CLOSE,           // (2) 0.08475
/*28 */                                &iov, 1, iov.iov_len);                           // (1) 0.1017
/*30 */     buffer_reset(&ioc->rawoutput);                                              // (13) 0.03148
/*32 */     qio_channel_websock_write_wire(ioc, NULL);                                  // (8) 0.05085
/*34 */     qio_channel_shutdown(ioc->master, QIO_CHANNEL_SHUTDOWN_BOTH, NULL);         // (3) 0.07748
/*36 */ }                                                                               // (18) 0.002421
