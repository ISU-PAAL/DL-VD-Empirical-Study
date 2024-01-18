// commit message qemu@0bed71edbc (target=0, prob=0.7593661, correct=False): slirp: allow host port 0 for hostfwd
/*0   */ static int slirp_hostfwd(SlirpState *s, const char *redir_str,                 // (5) 0.04883
/*2   */                          int legacy_format)                                    // (4) 0.05664
/*4   */ {                                                                              // (31) 0.001953
/*6   */     struct in_addr host_addr = { .s_addr = INADDR_ANY };                       // (7) 0.04492
/*8   */     struct in_addr guest_addr = { .s_addr = 0 };                               // (8) 0.03711
/*10  */     int host_port, guest_port;                                                 // (17) 0.02344
/*12  */     const char *p;                                                             // (21) 0.01563
/*14  */     char buf[256];                                                             // (22) 0.01562
/*16  */     int is_udp;                                                                // (20) 0.01758
/*18  */     char *end;                                                                 // (25) 0.01367
/*22  */     p = redir_str;                                                             // (19) 0.01953
/*24  */     if (!p || get_str_sep(buf, sizeof(buf), &p, ':') < 0) {                    // (3) 0.05859
/*26  */         goto fail_syntax;                                                      // (14) 0.02539
/*28  */     }                                                                          // (28) 0.007812
/*30  */     if (!strcmp(buf, "tcp") || buf[0] == '\0') {                               // (6) 0.04883
/*32  */         is_udp = 0;                                                            // (12) 0.02734
/*34  */     } else if (!strcmp(buf, "udp")) {                                          // (10) 0.0332
/*36  */         is_udp = 1;                                                            // (13) 0.02734
/*38  */     } else {                                                                   // (26) 0.01172
/*40  */         goto fail_syntax;                                                      // (16) 0.02539
/*42  */     }                                                                          // (29) 0.007812
/*46  */     if (!legacy_format) {                                                      // (18) 0.02148
/*48  */         if (get_str_sep(buf, sizeof(buf), &p, ':') < 0) {                      // (2) 0.0625
/*50  */             goto fail_syntax;                                                  // (11) 0.0332
/*52  */         }                                                                      // (24) 0.01562
/*54  */         if (buf[0] != '\0' && !inet_aton(buf, &host_addr)) {                   // (1) 0.0625
/*56  */             goto fail_syntax;                                                  // (9) 0.0332
/*58  */         }                                                                      // (23) 0.01562
/*60  */     }                                                                          // (27) 0.007812
/*64  */     if (get_str_sep(buf, sizeof(buf), &p, legacy_format ? ':' : '-') < 0) {    // (0) 0.06836
/*66  */         goto fail_syntax;                                                      // (15) 0.02539
/*68  */     }                                                                          // (30) 0.007812
/*70  */     host_port = strtol(buf, &end, 0);                                          // 0.0
/*72  */     if (*end != '\0' || host_port < 1 || host_port > 65535) {                  // 0.0
/*74  */         goto fail_syntax;                                                      // 0.0
/*76  */     }                                                                          // 0.0
/*80  */     if (get_str_sep(buf, sizeof(buf), &p, ':') < 0) {                          // 0.0
/*82  */         goto fail_syntax;                                                      // 0.0
/*84  */     }                                                                          // 0.0
/*86  */     if (buf[0] != '\0' && !inet_aton(buf, &guest_addr)) {                      // 0.0
/*88  */         goto fail_syntax;                                                      // 0.0
/*90  */     }                                                                          // 0.0
/*94  */     guest_port = strtol(p, &end, 0);                                           // 0.0
/*96  */     if (*end != '\0' || guest_port < 1 || guest_port > 65535) {                // 0.0
/*98  */         goto fail_syntax;                                                      // 0.0
/*100 */     }                                                                          // 0.0
/*104 */     if (slirp_add_hostfwd(s->slirp, is_udp, host_addr, host_port, guest_addr,  // 0.0
/*106 */                           guest_port) < 0) {                                   // 0.0
/*108 */         error_report("could not set up host forwarding rule '%s'",             // 0.0
/*110 */                      redir_str);                                               // 0.0
/*112 */         return -1;                                                             // 0.0
/*114 */     }                                                                          // 0.0
/*116 */     return 0;                                                                  // 0.0
/*120 */  fail_syntax:                                                                  // 0.0
/*122 */     error_report("invalid host forwarding rule '%s'", redir_str);              // 0.0
/*124 */     return -1;                                                                 // 0.0
/*126 */ }                                                                              // 0.0
