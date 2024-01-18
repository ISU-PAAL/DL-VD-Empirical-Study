// commit message qemu@eaf136f9a2 (target=0, prob=0.17100094, correct=True): slirp: Fix migration from older versions of QEMU to the current one
/*0  */ static int slirp_socket_load(QEMUFile *f, struct socket *so)                       // (6) 0.04297
/*2  */ {                                                                                  // (28) 0.001953
/*4  */     if (tcp_attach(so) < 0)                                                        // (14) 0.0293
/*6  */         return -ENOMEM;                                                            // (15) 0.02539
/*10 */     so->so_urgc = qemu_get_be32(f);                                                // (8) 0.04102
/*12 */     so->so_ffamily = qemu_get_be16(f);                                             // (9) 0.04102
/*14 */     switch (so->so_ffamily) {                                                      // (16) 0.02539
/*16 */     case AF_INET:                                                                  // (20) 0.01758
/*18 */         so->so_faddr.s_addr = qemu_get_be32(f);                                    // (3) 0.05664
/*20 */         so->so_fport = qemu_get_be16(f);                                           // (4) 0.04883
/*22 */         break;                                                                     // (21) 0.01758
/*24 */     default:                                                                       // (24) 0.009766
/*26 */         error_report(                                                              // (18) 0.02148
/*28 */                 "so_ffamily unknown, unable to restore so_faddr and so_lport\n");  // (0) 0.07227
/*30 */     }                                                                              // (26) 0.007812
/*32 */     so->so_lfamily = qemu_get_be16(f);                                             // (7) 0.04102
/*34 */     switch (so->so_lfamily) {                                                      // (17) 0.02539
/*36 */     case AF_INET:                                                                  // (22) 0.01758
/*38 */         so->so_laddr.s_addr = qemu_get_be32(f);                                    // (2) 0.05664
/*40 */         so->so_lport = qemu_get_be16(f);                                           // (5) 0.04883
/*42 */         break;                                                                     // (23) 0.01758
/*44 */     default:                                                                       // (25) 0.009766
/*46 */         error_report(                                                              // (19) 0.02148
/*48 */                 "so_ffamily unknown, unable to restore so_laddr and so_lport\n");  // (1) 0.07227
/*50 */     }                                                                              // (27) 0.007812
/*52 */     so->so_iptos = qemu_get_byte(f);                                               // (10) 0.03906
/*54 */     so->so_emu = qemu_get_byte(f);                                                 // (11) 0.03906
/*56 */     so->so_type = qemu_get_byte(f);                                                // (13) 0.03711
/*58 */     so->so_state = qemu_get_be32(f);                                               // (12) 0.03906
/*60 */     if (slirp_sbuf_load(f, &so->so_rcv) < 0)                                       // 0.0
/*62 */         return -ENOMEM;                                                            // 0.0
/*64 */     if (slirp_sbuf_load(f, &so->so_snd) < 0)                                       // 0.0
/*66 */         return -ENOMEM;                                                            // 0.0
/*68 */     slirp_tcp_load(f, so->so_tcpcb);                                               // 0.0
/*72 */     return 0;                                                                      // 0.0
/*74 */ }                                                                                  // 0.0
