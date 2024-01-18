// commit message qemu@340849a9ff (target=1, prob=0.35457397, correct=False): util: retry getaddrinfo if getting EAI_BADFLAGS with AI_V4MAPPED
/*0  */ static int check_bind(const char *hostname, bool *has_proto)               // (7) 0.03711
/*2  */ {                                                                          // (35) 0.001953
/*4  */     int fd = -1;                                                           // (19) 0.01953
/*6  */     struct addrinfo ai, *res = NULL;                                       // (12) 0.02734
/*8  */     int rc;                                                                // (29) 0.01172
/*10 */     int ret = -1;                                                          // (24) 0.01758
/*14 */     memset(&ai, 0, sizeof(ai));                                            // (13) 0.02734
/*16 */     ai.ai_flags = AI_CANONNAME | AI_V4MAPPED | AI_ADDRCONFIG;              // (1) 0.06055
/*18 */     ai.ai_family = AF_UNSPEC;                                              // (11) 0.0293
/*20 */     ai.ai_socktype = SOCK_STREAM;                                          // (10) 0.03516
/*24 */     /* lookup */                                                           // (28) 0.01172
/*26 */     rc = getaddrinfo(hostname, NULL, &ai, &res);                           // (5) 0.03906
/*28 */     if (rc != 0) {                                                         // (23) 0.01953
/*30 */         if (rc == EAI_ADDRFAMILY ||                                        // (6) 0.03906
/*32 */             rc == EAI_FAMILY) {                                            // (3) 0.04102
/*34 */             *has_proto = false;                                            // (9) 0.03711
/*36 */             goto done;                                                     // (15) 0.02734
/*38 */         }                                                                  // (26) 0.01562
/*40 */         goto cleanup;                                                      // (22) 0.01953
/*42 */     }                                                                      // (31) 0.007812
/*46 */     fd = qemu_socket(res->ai_family, res->ai_socktype, res->ai_protocol);  // (0) 0.06445
/*48 */     if (fd < 0) {                                                          // (20) 0.01953
/*50 */         goto cleanup;                                                      // (21) 0.01953
/*52 */     }                                                                      // (32) 0.007812
/*56 */     if (bind(fd, res->ai_addr, res->ai_addrlen) < 0) {                     // (2) 0.05078
/*58 */         if (errno == EADDRNOTAVAIL) {                                      // (4) 0.04102
/*60 */             *has_proto = false;                                            // (8) 0.03711
/*62 */             goto done;                                                     // (14) 0.02734
/*64 */         }                                                                  // (25) 0.01562
/*66 */         goto cleanup;                                                      // (18) 0.01953
/*68 */     }                                                                      // (30) 0.007813
/*72 */     *has_proto = true;                                                     // (16) 0.02148
/*74 */  done:                                                                     // (33) 0.003906
/*76 */     ret = 0;                                                               // (27) 0.01367
/*80 */  cleanup:                                                                  // (34) 0.003906
/*82 */     if (fd != -1) {                                                        // (17) 0.02148
/*84 */         close(fd);                                                         // 0.0
/*86 */     }                                                                      // 0.0
/*88 */     if (res) {                                                             // 0.0
/*90 */         freeaddrinfo(res);                                                 // 0.0
/*92 */     }                                                                      // 0.0
/*94 */     return ret;                                                            // 0.0
/*96 */ }                                                                          // 0.0
