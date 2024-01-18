// commit message qemu@3e305e4a47 (target=1, prob=0.46983796, correct=False): ui: convert VNC server to use QCryptoTLSSession
/*0  */ ssize_t vnc_client_write_buf(VncState *vs, const uint8_t *data, size_t datalen)  // (0) 0.1393
/*2  */ {                                                                                // (13) 0.004098
/*4  */     ssize_t ret;                                                                 // (10) 0.03689
/*6  */ #ifdef CONFIG_VNC_TLS                                                            // (8) 0.04098
/*8  */     if (vs->tls.session) {                                                       // (5) 0.05328
/*10 */         ret = vnc_client_write_tls(&vs->tls.session, data, datalen);             // (1) 0.1311
/*12 */     } else {                                                                     // (11) 0.02459
/*14 */ #endif /* CONFIG_VNC_TLS */                                                      // (6) 0.04508
/*16 */         ret = send(vs->csock, (const void *)data, datalen, 0);                   // (3) 0.1148
/*18 */ #ifdef CONFIG_VNC_TLS                                                            // (9) 0.04098
/*20 */     }                                                                            // (12) 0.01639
/*22 */ #endif /* CONFIG_VNC_TLS */                                                      // (7) 0.04508
/*24 */     VNC_DEBUG("Wrote wire %p %zd -> %ld\n", data, datalen, ret);                 // (2) 0.123
/*26 */     return vnc_client_io_error(vs, ret, socket_error());                         // (4) 0.08607
/*28 */ }                                                                                // (14) 0.004098
