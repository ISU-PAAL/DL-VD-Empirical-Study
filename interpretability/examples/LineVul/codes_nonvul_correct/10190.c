// commit message qemu@6c5b5645ae (target=0, prob=0.12895405, correct=True): linux-user: add rtnetlink(7) support
/*0  */ static abi_long do_socket(int domain, int type, int protocol)  // (6) 0.04813
/*2  */ {                                                              // (24) 0.002674
/*4  */     int target_type = type;                                    // (14) 0.02674
/*6  */     int ret;                                                   // (19) 0.01604
/*10 */     ret = target_to_host_sock_type(&type);                     // (7) 0.04813
/*12 */     if (ret) {                                                 // (17) 0.02139
/*14 */         return ret;                                            // (15) 0.02674
/*16 */     }                                                          // (21) 0.0107
/*20 */     if (domain == PF_NETLINK)                                  // (11) 0.03476
/*22 */         return -TARGET_EAFNOSUPPORT;                           // (4) 0.0508
/*26 */     if (domain == AF_PACKET ||                                 // (12) 0.03476
/*28 */         (domain == AF_INET && type == SOCK_PACKET)) {          // (2) 0.06684
/*30 */         protocol = tswap16(protocol);                          // (10) 0.04545
/*32 */     }                                                          // (22) 0.0107
/*36 */     ret = get_errno(socket(domain, type, protocol));           // (8) 0.04813
/*38 */     if (ret >= 0) {                                            // (16) 0.02674
/*40 */         ret = sock_flags_fixup(ret, target_type);              // (3) 0.05882
/*42 */         if (type == SOCK_PACKET) {                             // (5) 0.0508
/*44 */             /* Manage an obsolete case :                       // (9) 0.04813
/*46 */              * if socket type is SOCK_PACKET, bind by name     // (1) 0.07219
/*48 */              */                                                // (13) 0.03476
/*50 */             fd_trans_register(ret, &target_packet_trans);      // (0) 0.07487
/*52 */         }                                                      // (18) 0.02139
/*54 */     }                                                          // (23) 0.0107
/*56 */     return ret;                                                // (20) 0.01604
/*58 */ }                                                              // (25) 0.002674
