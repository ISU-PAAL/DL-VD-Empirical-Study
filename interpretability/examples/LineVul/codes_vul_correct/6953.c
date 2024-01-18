// commit message qemu@3e305e4a47 (target=1, prob=0.7158787, correct=True): ui: convert VNC server to use QCryptoTLSSession
/*0  */ static ssize_t vnc_client_read_tls(gnutls_session_t *session, uint8_t *data,  // (1) 0.1441
/*2  */                                    size_t datalen)                            // (0) 0.1847
/*4  */ {                                                                             // (12) 0.004505
/*6  */     ssize_t ret = gnutls_read(*session, data, datalen);                       // (2) 0.1036
/*8  */     if (ret < 0) {                                                            // (7) 0.04505
/*10 */         if (ret == GNUTLS_E_AGAIN) {                                          // (3) 0.09459
/*12 */             errno = EAGAIN;                                                   // (4) 0.08108
/*14 */         } else {                                                              // (8) 0.04505
/*16 */             errno = EIO;                                                      // (5) 0.07658
/*18 */         }                                                                     // (9) 0.03604
/*20 */         ret = -1;                                                             // (6) 0.05405
/*22 */     }                                                                         // (11) 0.01802
/*24 */     return ret;                                                               // (10) 0.02703
/*26 */ }                                                                             // (13) 0.004505
