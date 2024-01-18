// commit message qemu@39f80521df (target=0, prob=0.37778467, correct=True): sockets: factor out create_fast_reuse_socket
/*0   */ static int inet_listen_saddr(InetSocketAddress *saddr,                        // (9) 0.03711
/*2   */                              int port_offset,                                 // (2) 0.06445
/*4   */                              bool update_addr,                                // (1) 0.06445
/*6   */                              Error **errp)                                    // (0) 0.06445
/*8   */ {                                                                             // (29) 0.001954
/*10  */     struct addrinfo ai,*res,*e;                                               // (14) 0.0293
/*12  */     char port[33];                                                            // (24) 0.01562
/*14  */     char uaddr[INET6_ADDRSTRLEN+1];                                           // (10) 0.03711
/*16  */     char uport[33];                                                           // (22) 0.01758
/*18  */     int slisten, rc, port_min, port_max, p;                                   // (6) 0.03906
/*20  */     Error *err = NULL;                                                        // (21) 0.01758
/*24  */     memset(&ai,0, sizeof(ai));                                                // (16) 0.02734
/*26  */     ai.ai_flags = AI_PASSIVE;                                                 // (15) 0.0293
/*28  */     if (saddr->has_numeric && saddr->numeric) {                               // (8) 0.03906
/*30  */         ai.ai_flags |= AI_NUMERICHOST | AI_NUMERICSERV;                       // (3) 0.05859
/*32  */     }                                                                         // (28) 0.007812
/*34  */     ai.ai_family = inet_ai_family_from_address(saddr, &err);                  // (4) 0.05273
/*36  */     ai.ai_socktype = SOCK_STREAM;                                             // (11) 0.03516
/*40  */     if (err) {                                                                // (23) 0.01562
/*42  */         error_propagate(errp, err);                                           // (12) 0.0332
/*44  */         return -1;                                                            // (20) 0.02148
/*46  */     }                                                                         // (26) 0.007812
/*50  */     if (saddr->host == NULL) {                                                // (18) 0.02539
/*52  */         error_setg(errp, "host not specified");                               // (7) 0.03906
/*54  */         return -1;                                                            // (19) 0.02148
/*56  */     }                                                                         // (27) 0.007812
/*58  */     if (saddr->port != NULL) {                                                // (17) 0.02539
/*60  */         pstrcpy(port, sizeof(port), saddr->port);                             // (5) 0.04492
/*62  */     } else {                                                                  // (25) 0.01172
/*64  */         port[0] = '\0';                                                       // (13) 0.03125
/*66  */     }                                                                         // 0.0
/*70  */     /* lookup */                                                              // 0.0
/*72  */     if (port_offset) {                                                        // 0.0
/*74  */         unsigned long long baseport;                                          // 0.0
/*76  */         if (strlen(port) == 0) {                                              // 0.0
/*78  */             error_setg(errp, "port not specified");                           // 0.0
/*80  */             return -1;                                                        // 0.0
/*82  */         }                                                                     // 0.0
/*84  */         if (parse_uint_full(port, &baseport, 10) < 0) {                       // 0.0
/*86  */             error_setg(errp, "can't convert to a number: %s", port);          // 0.0
/*88  */             return -1;                                                        // 0.0
/*90  */         }                                                                     // 0.0
/*92  */         if (baseport > 65535 ||                                               // 0.0
/*94  */             baseport + port_offset > 65535) {                                 // 0.0
/*96  */             error_setg(errp, "port %s out of range", port);                   // 0.0
/*98  */             return -1;                                                        // 0.0
/*100 */         }                                                                     // 0.0
/*102 */         snprintf(port, sizeof(port), "%d", (int)baseport + port_offset);      // 0.0
/*104 */     }                                                                         // 0.0
/*106 */     rc = getaddrinfo(strlen(saddr->host) ? saddr->host : NULL,                // 0.0
/*108 */                      strlen(port) ? port : NULL, &ai, &res);                  // 0.0
/*110 */     if (rc != 0) {                                                            // 0.0
/*112 */         error_setg(errp, "address resolution failed for %s:%s: %s",           // 0.0
/*114 */                    saddr->host, port, gai_strerror(rc));                      // 0.0
/*116 */         return -1;                                                            // 0.0
/*118 */     }                                                                         // 0.0
/*122 */     /* create socket + bind */                                                // 0.0
/*124 */     for (e = res; e != NULL; e = e->ai_next) {                                // 0.0
/*126 */         getnameinfo((struct sockaddr*)e->ai_addr,e->ai_addrlen,               // 0.0
/*128 */ 		        uaddr,INET6_ADDRSTRLEN,uport,32,                                    // 0.0
/*130 */ 		        NI_NUMERICHOST | NI_NUMERICSERV);                                   // 0.0
/*132 */         slisten = qemu_socket(e->ai_family, e->ai_socktype, e->ai_protocol);  // 0.0
/*134 */         if (slisten < 0) {                                                    // 0.0
/*136 */             if (!e->ai_next) {                                                // 0.0
/*138 */                 error_setg_errno(errp, errno, "Failed to create socket");     // 0.0
/*140 */             }                                                                 // 0.0
/*142 */             continue;                                                         // 0.0
/*144 */         }                                                                     // 0.0
/*148 */         socket_set_fast_reuse(slisten);                                       // 0.0
/*152 */         port_min = inet_getport(e);                                           // 0.0
/*154 */         port_max = saddr->has_to ? saddr->to + port_offset : port_min;        // 0.0
/*156 */         for (p = port_min; p <= port_max; p++) {                              // 0.0
/*158 */             inet_setport(e, p);                                               // 0.0
/*160 */             if (try_bind(slisten, saddr, e) >= 0) {                           // 0.0
/*162 */                 goto listen;                                                  // 0.0
/*164 */             }                                                                 // 0.0
/*166 */             if (p == port_max) {                                              // 0.0
/*168 */                 if (!e->ai_next) {                                            // 0.0
/*170 */                     error_setg_errno(errp, errno, "Failed to bind socket");   // 0.0
/*172 */                 }                                                             // 0.0
/*174 */             }                                                                 // 0.0
/*176 */         }                                                                     // 0.0
/*178 */         closesocket(slisten);                                                 // 0.0
/*180 */     }                                                                         // 0.0
/*182 */     freeaddrinfo(res);                                                        // 0.0
/*184 */     return -1;                                                                // 0.0
/*188 */ listen:                                                                       // 0.0
/*190 */     if (listen(slisten,1) != 0) {                                             // 0.0
/*192 */         error_setg_errno(errp, errno, "Failed to listen on socket");          // 0.0
/*194 */         closesocket(slisten);                                                 // 0.0
/*196 */         freeaddrinfo(res);                                                    // 0.0
/*198 */         return -1;                                                            // 0.0
/*200 */     }                                                                         // 0.0
/*202 */     if (update_addr) {                                                        // 0.0
/*204 */         g_free(saddr->host);                                                  // 0.0
/*206 */         saddr->host = g_strdup(uaddr);                                        // 0.0
/*208 */         g_free(saddr->port);                                                  // 0.0
/*210 */         saddr->port = g_strdup_printf("%d",                                   // 0.0
/*212 */                                       inet_getport(e) - port_offset);         // 0.0
/*214 */         saddr->has_ipv6 = saddr->ipv6 = e->ai_family == PF_INET6;             // 0.0
/*216 */         saddr->has_ipv4 = saddr->ipv4 = e->ai_family != PF_INET6;             // 0.0
/*218 */     }                                                                         // 0.0
/*220 */     freeaddrinfo(res);                                                        // 0.0
/*222 */     return slisten;                                                           // 0.0
/*224 */ }                                                                             // 0.0
