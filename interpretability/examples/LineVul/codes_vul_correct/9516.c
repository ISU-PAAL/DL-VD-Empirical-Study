// commit message qemu@7364dbdabb (target=1, prob=0.91473085, correct=True): ui: add tracing of VNC authentication process
/*0  */ static int protocol_client_auth_sasl_start_len(VncState *vs, uint8_t *data, size_t len)  // (0) 0.1423
/*2  */ {                                                                                        // (12) 0.004184
/*4  */     uint32_t startlen = read_u32(data, 0);                                               // (6) 0.0795
/*6  */     VNC_DEBUG("Got client start len %d\n", startlen);                                    // (4) 0.08368
/*8  */     if (startlen > SASL_DATA_MAX_LEN) {                                                  // (5) 0.0795
/*10 */         VNC_DEBUG("Too much SASL data %d\n", startlen);                                  // (3) 0.1046
/*12 */         vnc_client_error(vs);                                                            // (7) 0.06695
/*14 */         return -1;                                                                       // (8) 0.04603
/*16 */     }                                                                                    // (11) 0.01674
/*20 */     if (startlen == 0)                                                                   // (9) 0.04184
/*22 */         return protocol_client_auth_sasl_start(vs, NULL, 0);                             // (2) 0.1088
/*26 */     vnc_read_when(vs, protocol_client_auth_sasl_start, startlen);                        // (1) 0.113
/*28 */     return 0;                                                                            // (10) 0.0251
/*30 */ }                                                                                        // (13) 0.004184
