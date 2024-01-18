// commit message qemu@3e305e4a47 (target=1, prob=0.06904311, correct=False): ui: convert VNC server to use QCryptoTLSSession
/*0  */ static ssize_t vnc_tls_push(gnutls_transport_ptr_t transport,  // (2) 0.1163
/*2  */                             const void *data,                  // (1) 0.1488
/*4  */                             size_t len) {                      // (0) 0.1535
/*6  */     VncState *vs = (VncState *)transport;                      // (4) 0.07907
/*8  */     int ret;                                                   // (9) 0.02791
/*12 */  retry:                                                        // (12) 0.01395
/*14 */     ret = send(vs->csock, data, len, 0);                       // (3) 0.08372
/*16 */     if (ret < 0) {                                             // (8) 0.04651
/*18 */         if (errno == EINTR)                                    // (5) 0.07442
/*20 */             goto retry;                                        // (6) 0.06977
/*22 */         return -1;                                             // (7) 0.05116
/*24 */     }                                                          // (11) 0.0186
/*26 */     return ret;                                                // (10) 0.02791
/*28 */ }                                                              // (13) 0.004651
