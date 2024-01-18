// commit message qemu@df3c286c53 (target=0, prob=0.030910965, correct=True): error: Strip trailing '\n' from error string arguments (again)
/*0  */ static void slirp_socket_save(QEMUFile *f, struct socket *so)                   // (6) 0.04297
/*2  */ {                                                                               // (27) 0.001953
/*4  */     qemu_put_be32(f, so->so_urgc);                                              // (8) 0.04102
/*6  */     qemu_put_be16(f, so->so_ffamily);                                           // (9) 0.04102
/*8  */     switch (so->so_ffamily) {                                                   // (15) 0.02539
/*10 */     case AF_INET:                                                               // (19) 0.01758
/*12 */         qemu_put_be32(f, so->so_faddr.s_addr);                                  // (2) 0.05664
/*14 */         qemu_put_be16(f, so->so_fport);                                         // (4) 0.04883
/*16 */         break;                                                                  // (21) 0.01758
/*18 */     default:                                                                    // (23) 0.009766
/*20 */         error_report(                                                           // (18) 0.02148
/*22 */                 "so_ffamily unknown, unable to save so_faddr and so_fport\n");  // (0) 0.07227
/*24 */     }                                                                           // (25) 0.007812
/*26 */     qemu_put_be16(f, so->so_lfamily);                                           // (10) 0.04102
/*28 */     switch (so->so_lfamily) {                                                   // (16) 0.02539
/*30 */     case AF_INET:                                                               // (20) 0.01758
/*32 */         qemu_put_be32(f, so->so_laddr.s_addr);                                  // (3) 0.05664
/*34 */         qemu_put_be16(f, so->so_lport);                                         // (5) 0.04883
/*36 */         break;                                                                  // (22) 0.01758
/*38 */     default:                                                                    // (24) 0.009766
/*40 */         error_report(                                                           // (17) 0.02148
/*42 */                 "so_ffamily unknown, unable to save so_laddr and so_lport\n");  // (1) 0.07227
/*44 */     }                                                                           // (26) 0.007812
/*46 */     qemu_put_byte(f, so->so_iptos);                                             // (11) 0.03906
/*48 */     qemu_put_byte(f, so->so_emu);                                               // (13) 0.03906
/*50 */     qemu_put_byte(f, so->so_type);                                              // (14) 0.03711
/*52 */     qemu_put_be32(f, so->so_state);                                             // (12) 0.03906
/*54 */     slirp_sbuf_save(f, &so->so_rcv);                                            // (7) 0.04297
/*56 */     slirp_sbuf_save(f, &so->so_snd);                                            // 0.0
/*58 */     slirp_tcp_save(f, so->so_tcpcb);                                            // 0.0
/*60 */ }                                                                               // 0.0
