// commit message qemu@340849a9ff (target=1, prob=0.31429014, correct=False): util: retry getaddrinfo if getting EAI_BADFLAGS with AI_V4MAPPED
/*0  */ static struct addrinfo *inet_parse_connect_saddr(InetSocketAddress *saddr,  // (7) 0.04846
/*2  */                                                  Error **errp)              // (0) 0.1167
/*4  */ {                                                                           // (25) 0.002203
/*6  */     struct addrinfo ai, *res;                                               // (12) 0.02643
/*8  */     int rc;                                                                 // (19) 0.01322
/*10 */     Error *err = NULL;                                                      // (17) 0.01982
/*14 */     memset(&ai, 0, sizeof(ai));                                             // (11) 0.03084
/*18 */     ai.ai_flags = AI_CANONNAME | AI_V4MAPPED | AI_ADDRCONFIG;               // (2) 0.06828
/*20 */     ai.ai_family = inet_ai_family_from_address(saddr, &err);                // (4) 0.05947
/*22 */     ai.ai_socktype = SOCK_STREAM;                                           // (9) 0.03965
/*26 */     if (err) {                                                              // (18) 0.01762
/*28 */         error_propagate(errp, err);                                         // (10) 0.03744
/*30 */         return NULL;                                                        // (13) 0.02203
/*32 */     }                                                                       // (22) 0.008811
/*36 */     if (saddr->host == NULL || saddr->port == NULL) {                       // (8) 0.04405
/*38 */         error_setg(errp, "host and/or port not specified");                 // (6) 0.05286
/*40 */         return NULL;                                                        // (15) 0.02203
/*42 */     }                                                                       // (23) 0.008811
/*46 */     /* lookup */                                                            // (20) 0.01322
/*48 */     rc = getaddrinfo(saddr->host, saddr->port, &ai, &res);                  // (5) 0.05507
/*50 */     if (rc != 0) {                                                          // (14) 0.02203
/*52 */         error_setg(errp, "address resolution failed for %s:%s: %s",         // (3) 0.06388
/*54 */                    saddr->host, saddr->port, gai_strerror(rc));             // (1) 0.0815
/*56 */         return NULL;                                                        // (16) 0.02203
/*58 */     }                                                                       // (24) 0.008811
/*60 */     return res;                                                             // (21) 0.01322
/*62 */ }                                                                           // (26) 0.002203
