// commit message qemu@5fb6c7a8b2 (target=0, prob=0.32890818, correct=True): Move TLS auth into separate file ("Daniel P. Berrange")
/*0  */ static int start_auth_vencrypt_subauth(VncState *vs)                     // (11) 0.04206
/*2  */ {                                                                        // (23) 0.002336
/*4  */     switch (vs->vd->subauth) {                                           // (18) 0.03037
/*6  */     case VNC_AUTH_VENCRYPT_TLSNONE:                                      // (7) 0.04673
/*8  */     case VNC_AUTH_VENCRYPT_X509NONE:                                     // (8) 0.04673
/*10 */        VNC_DEBUG("Accept TLS auth none\n");                              // (12) 0.04206
/*12 */        vnc_write_u32(vs, 0); /* Accept auth completion */                // (3) 0.05374
/*14 */        vnc_read_when(vs, protocol_client_init, 1);                       // (2) 0.05374
/*16 */        break;                                                            // (19) 0.01869
/*20 */     case VNC_AUTH_VENCRYPT_TLSVNC:                                       // (6) 0.04673
/*22 */     case VNC_AUTH_VENCRYPT_X509VNC:                                      // (9) 0.04673
/*24 */        VNC_DEBUG("Start TLS auth VNC\n");                                // (10) 0.04439
/*26 */        return start_auth_vnc(vs);                                        // (14) 0.03738
/*30 */     default: /* Should not be possible, but just in case */              // (15) 0.03738
/*32 */        VNC_DEBUG("Reject auth %d\n", vs->vd->auth);                      // (0) 0.05841
/*34 */        vnc_write_u8(vs, 1);                                              // (13) 0.04206
/*36 */        if (vs->minor >= 8) {                                             // (16) 0.03738
/*38 */            static const char err[] = "Unsupported authentication type";  // (5) 0.0514
/*40 */            vnc_write_u32(vs, sizeof(err));                               // (1) 0.05607
/*42 */            vnc_write(vs, err, sizeof(err));                              // (4) 0.05374
/*44 */        }                                                                 // (20) 0.01636
/*46 */        vnc_client_error(vs);                                             // (17) 0.03505
/*48 */     }                                                                    // (22) 0.009346
/*52 */     return 0;                                                            // (21) 0.01402
/*54 */ }                                                                        // (24) 0.002336
