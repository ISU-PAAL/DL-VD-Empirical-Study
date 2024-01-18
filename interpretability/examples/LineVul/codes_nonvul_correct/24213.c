// commit message qemu@9c12a6f24d (target=0, prob=0.39352497, correct=True): slirp: Do not allow to remove non-hostfwd sockets
/*0  */ void net_slirp_hostfwd_remove(Monitor *mon, const char *src_str)         // (5) 0.04688
/*2  */ {                                                                        // (31) 0.001953
/*4  */     struct in_addr host_addr = { .s_addr = INADDR_ANY };                 // (7) 0.04492
/*6  */     int host_port;                                                       // (24) 0.01562
/*8  */     char buf[256] = "";                                                  // (21) 0.02148
/*10 */     const char *p = src_str;                                             // (20) 0.02344
/*12 */     int is_udp = 0;                                                      // (22) 0.02148
/*14 */     int n;                                                               // (25) 0.01172
/*18 */     if (!slirp_inited) {                                                 // (14) 0.02539
/*20 */         monitor_printf(mon, "user mode network stack not in use\n");     // (6) 0.04688
/*22 */         return;                                                          // (23) 0.01758
/*24 */     }                                                                    // (27) 0.007812
/*28 */     if (!src_str || !src_str[0])                                         // (11) 0.03125
/*30 */         goto fail_syntax;                                                // (15) 0.02539
/*34 */     get_str_sep(buf, sizeof(buf), &p, ':');                              // (8) 0.04297
/*38 */     if (!strcmp(buf, "tcp") || buf[0] == '\0') {                         // (4) 0.04883
/*40 */         is_udp = 0;                                                      // (12) 0.02734
/*42 */     } else if (!strcmp(buf, "udp")) {                                    // (10) 0.0332
/*44 */         is_udp = 1;                                                      // (13) 0.02734
/*46 */     } else {                                                             // (26) 0.01172
/*48 */         goto fail_syntax;                                                // (16) 0.02539
/*50 */     }                                                                    // (28) 0.007812
/*54 */     if (get_str_sep(buf, sizeof(buf), &p, ':') < 0) {                    // (1) 0.05469
/*56 */         goto fail_syntax;                                                // (17) 0.02539
/*58 */     }                                                                    // (29) 0.007812
/*60 */     if (buf[0] != '\0' && !inet_aton(buf, &host_addr)) {                 // (2) 0.05469
/*62 */         goto fail_syntax;                                                // (18) 0.02539
/*64 */     }                                                                    // (30) 0.007812
/*68 */     host_port = atoi(p);                                                 // (19) 0.02344
/*72 */     n = slirp_remove_hostfwd(is_udp, host_addr, host_port);              // (0) 0.05469
/*76 */     monitor_printf(mon, "removed %d host forwarding rules for %s\n", n,  // (3) 0.04883
/*78 */                    src_str);                                             // (9) 0.04297
/*80 */     return;                                                              // 0.0
/*84 */  fail_syntax:                                                            // 0.0
/*86 */     monitor_printf(mon, "invalid format\n");                             // 0.0
/*88 */ }                                                                        // 0.0
