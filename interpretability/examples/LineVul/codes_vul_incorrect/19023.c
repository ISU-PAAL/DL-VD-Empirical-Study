// commit message qemu@7364dbdabb (target=1, prob=0.38351053, correct=False): ui: add tracing of VNC authentication process
/*0   */ static int protocol_version(VncState *vs, uint8_t *version, size_t len)            // (3) 0.04688
/*2   */ {                                                                                  // (29) 0.001953
/*4   */     char local[13];                                                                // (25) 0.01562
/*8   */     memcpy(local, version, 12);                                                    // (19) 0.02539
/*10  */     local[12] = 0;                                                                 // (22) 0.01953
/*14  */     if (sscanf(local, "RFB %03d.%03d\n", &vs->major, &vs->minor) != 2) {           // (0) 0.07617
/*16  */         VNC_DEBUG("Malformed protocol version %s\n", local);                       // (5) 0.04492
/*18  */         vnc_client_error(vs);                                                      // (9) 0.03125
/*20  */         return 0;                                                                  // (23) 0.01953
/*22  */     }                                                                              // (27) 0.007812
/*24  */     VNC_DEBUG("Client request protocol version %d.%d\n", vs->major, vs->minor);    // (1) 0.05664
/*26  */     if (vs->major != 3 ||                                                          // (21) 0.02148
/*28  */         (vs->minor != 3 &&                                                         // (12) 0.0293
/*30  */          vs->minor != 4 &&                                                         // (13) 0.0293
/*32  */          vs->minor != 5 &&                                                         // (14) 0.0293
/*34  */          vs->minor != 7 &&                                                         // (15) 0.0293
/*36  */          vs->minor != 8)) {                                                        // (10) 0.03125
/*38  */         VNC_DEBUG("Unsupported client version\n");                                 // (7) 0.03711
/*40  */         vnc_write_u32(vs, VNC_AUTH_INVALID);                                       // (2) 0.05273
/*42  */         vnc_flush(vs);                                                             // (17) 0.02734
/*44  */         vnc_client_error(vs);                                                      // (11) 0.03125
/*46  */         return 0;                                                                  // (24) 0.01953
/*48  */     }                                                                              // (28) 0.007812
/*50  */     /* Some broken clients report v3.4 or v3.5, which spec requires to be treated  // (4) 0.04688
/*52  */      * as equivalent to v3.3 by servers                                            // (16) 0.02734
/*54  */      */                                                                            // (26) 0.009766
/*56  */     if (vs->minor == 4 || vs->minor == 5)                                          // (8) 0.03711
/*58  */         vs->minor = 3;                                                             // (18) 0.02734
/*62  */     if (vs->minor == 3) {                                                          // (20) 0.02539
/*64  */         if (vs->auth == VNC_AUTH_NONE) {                                           // (6) 0.04492
/*66  */             VNC_DEBUG("Tell client auth none\n");                                  // 0.0
/*68  */             vnc_write_u32(vs, vs->auth);                                           // 0.0
/*70  */             vnc_flush(vs);                                                         // 0.0
/*72  */             start_client_init(vs);                                                 // 0.0
/*74  */        } else if (vs->auth == VNC_AUTH_VNC) {                                      // 0.0
/*76  */             VNC_DEBUG("Tell client VNC auth\n");                                   // 0.0
/*78  */             vnc_write_u32(vs, vs->auth);                                           // 0.0
/*80  */             vnc_flush(vs);                                                         // 0.0
/*82  */             start_auth_vnc(vs);                                                    // 0.0
/*84  */        } else {                                                                    // 0.0
/*86  */             VNC_DEBUG("Unsupported auth %d for protocol 3.3\n", vs->auth);         // 0.0
/*88  */             vnc_write_u32(vs, VNC_AUTH_INVALID);                                   // 0.0
/*90  */             vnc_flush(vs);                                                         // 0.0
/*92  */             vnc_client_error(vs);                                                  // 0.0
/*94  */        }                                                                           // 0.0
/*96  */     } else {                                                                       // 0.0
/*98  */         VNC_DEBUG("Telling client we support auth %d\n", vs->auth);                // 0.0
/*100 */         vnc_write_u8(vs, 1); /* num auth */                                        // 0.0
/*102 */         vnc_write_u8(vs, vs->auth);                                                // 0.0
/*104 */         vnc_read_when(vs, protocol_client_auth, 1);                                // 0.0
/*106 */         vnc_flush(vs);                                                             // 0.0
/*108 */     }                                                                              // 0.0
/*112 */     return 0;                                                                      // 0.0
/*114 */ }                                                                                  // 0.0
