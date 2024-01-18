// commit message qemu@40ff6d7e8d (target=1, prob=0.4200716, correct=False): Don't leak file descriptors
/*0   */ int inet_dgram_opts(QemuOpts *opts)                                             // (8) 0.03711
/*2   */ {                                                                               // (28) 0.001953
/*4   */     struct addrinfo ai, *peer = NULL, *local = NULL;                            // (9) 0.03711
/*6   */     const char *addr;                                                           // (24) 0.01562
/*8   */     const char *port;                                                           // (25) 0.01562
/*10  */     char uaddr[INET6_ADDRSTRLEN+1];                                             // (11) 0.03711
/*12  */     char uport[33];                                                             // (22) 0.01758
/*14  */     int sock = -1, rc;                                                          // (20) 0.02148
/*18  */     /* lookup peer addr */                                                      // (23) 0.01563
/*20  */     memset(&ai,0, sizeof(ai));                                                  // (18) 0.02734
/*22  */     ai.ai_flags = AI_CANONNAME | AI_ADDRCONFIG;                                 // (6) 0.04492
/*24  */     ai.ai_family = PF_UNSPEC;                                                   // (17) 0.0293
/*26  */     ai.ai_socktype = SOCK_DGRAM;                                                // (10) 0.03711
/*30  */     addr = qemu_opt_get(opts, "host");                                          // (12) 0.03711
/*32  */     port = qemu_opt_get(opts, "port");                                          // (13) 0.03711
/*34  */     if (addr == NULL || strlen(addr) == 0) {                                    // (15) 0.03516
/*36  */         addr = "localhost";                                                     // (19) 0.02344
/*38  */     }                                                                           // (27) 0.007812
/*40  */     if (port == NULL || strlen(port) == 0) {                                    // (16) 0.03516
/*42  */         fprintf(stderr, "inet_dgram: port not specified\n");                    // (1) 0.05078
/*44  */         return -1;                                                              // (21) 0.02148
/*46  */     }                                                                           // (26) 0.007813
/*50  */     if (qemu_opt_get_bool(opts, "ipv4", 0))                                     // (3) 0.04883
/*52  */         ai.ai_family = PF_INET;                                                 // (14) 0.03711
/*54  */     if (qemu_opt_get_bool(opts, "ipv6", 0))                                     // (4) 0.04883
/*56  */         ai.ai_family = PF_INET6;                                                // (7) 0.03906
/*60  */     if (0 != (rc = getaddrinfo(addr, port, &ai, &peer))) {                      // (2) 0.04883
/*62  */         fprintf(stderr,"getaddrinfo(%s,%s): %s\n", addr, port,                  // (0) 0.06445
/*64  */                 gai_strerror(rc));                                              // (5) 0.04687
/*66  */ 	return -1;                                                                     // 0.0
/*68  */     }                                                                           // 0.0
/*70  */     if (sockets_debug) {                                                        // 0.0
/*72  */         fprintf(stderr, "%s: peer (%s:%s)\n", __FUNCTION__, addr, port);        // 0.0
/*74  */         inet_print_addrinfo(__FUNCTION__, peer);                                // 0.0
/*76  */     }                                                                           // 0.0
/*80  */     /* lookup local addr */                                                     // 0.0
/*82  */     memset(&ai,0, sizeof(ai));                                                  // 0.0
/*84  */     ai.ai_flags = AI_PASSIVE;                                                   // 0.0
/*86  */     ai.ai_family = peer->ai_family;                                             // 0.0
/*88  */     ai.ai_socktype = SOCK_DGRAM;                                                // 0.0
/*92  */     addr = qemu_opt_get(opts, "localaddr");                                     // 0.0
/*94  */     port = qemu_opt_get(opts, "localport");                                     // 0.0
/*96  */     if (addr == NULL || strlen(addr) == 0) {                                    // 0.0
/*98  */         addr = NULL;                                                            // 0.0
/*100 */     }                                                                           // 0.0
/*102 */     if (!port || strlen(port) == 0)                                             // 0.0
/*104 */         port = "0";                                                             // 0.0
/*108 */     if (0 != (rc = getaddrinfo(addr, port, &ai, &local))) {                     // 0.0
/*110 */         fprintf(stderr,"getaddrinfo(%s,%s): %s\n", addr, port,                  // 0.0
/*112 */                 gai_strerror(rc));                                              // 0.0
/*114 */         return -1;                                                              // 0.0
/*116 */     }                                                                           // 0.0
/*118 */     if (sockets_debug) {                                                        // 0.0
/*120 */         fprintf(stderr, "%s: local (%s:%s)\n", __FUNCTION__, addr, port);       // 0.0
/*122 */         inet_print_addrinfo(__FUNCTION__, local);                               // 0.0
/*124 */     }                                                                           // 0.0
/*128 */     /* create socket */                                                         // 0.0
/*130 */     sock = socket(peer->ai_family, peer->ai_socktype, peer->ai_protocol);       // 0.0
/*132 */     if (sock < 0) {                                                             // 0.0
/*134 */         fprintf(stderr,"%s: socket(%s): %s\n", __FUNCTION__,                    // 0.0
/*136 */                 inet_strfamily(peer->ai_family), strerror(errno));              // 0.0
/*138 */         goto err;                                                               // 0.0
/*140 */     }                                                                           // 0.0
/*142 */     setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(void*)&on,sizeof(on));             // 0.0
/*146 */     /* bind socket */                                                           // 0.0
/*148 */     if (getnameinfo((struct sockaddr*)local->ai_addr,local->ai_addrlen,         // 0.0
/*150 */                     uaddr,INET6_ADDRSTRLEN,uport,32,                            // 0.0
/*152 */                     NI_NUMERICHOST | NI_NUMERICSERV) != 0) {                    // 0.0
/*154 */         fprintf(stderr, "%s: getnameinfo: oops\n", __FUNCTION__);               // 0.0
/*156 */         goto err;                                                               // 0.0
/*158 */     }                                                                           // 0.0
/*160 */     if (bind(sock, local->ai_addr, local->ai_addrlen) < 0) {                    // 0.0
/*162 */         fprintf(stderr,"%s: bind(%s,%s,%d): OK\n", __FUNCTION__,                // 0.0
/*164 */                 inet_strfamily(local->ai_family), uaddr, inet_getport(local));  // 0.0
/*166 */         goto err;                                                               // 0.0
/*168 */     }                                                                           // 0.0
/*172 */     /* connect to peer */                                                       // 0.0
/*174 */     if (getnameinfo((struct sockaddr*)peer->ai_addr, peer->ai_addrlen,          // 0.0
/*176 */                     uaddr, INET6_ADDRSTRLEN, uport, 32,                         // 0.0
/*178 */                     NI_NUMERICHOST | NI_NUMERICSERV) != 0) {                    // 0.0
/*180 */         fprintf(stderr, "%s: getnameinfo: oops\n", __FUNCTION__);               // 0.0
/*182 */         goto err;                                                               // 0.0
/*184 */     }                                                                           // 0.0
/*186 */     if (connect(sock,peer->ai_addr,peer->ai_addrlen) < 0) {                     // 0.0
/*188 */         fprintf(stderr, "%s: connect(%s,%s,%s,%s): %s\n", __FUNCTION__,         // 0.0
/*190 */                 inet_strfamily(peer->ai_family),                                // 0.0
/*192 */                 peer->ai_canonname, uaddr, uport, strerror(errno));             // 0.0
/*194 */         goto err;                                                               // 0.0
/*196 */     }                                                                           // 0.0
/*200 */     freeaddrinfo(local);                                                        // 0.0
/*202 */     freeaddrinfo(peer);                                                         // 0.0
/*204 */     return sock;                                                                // 0.0
/*208 */ err:                                                                            // 0.0
/*210 */     if (-1 != sock)                                                             // 0.0
/*212 */         closesocket(sock);                                                      // 0.0
/*214 */     if (local)                                                                  // 0.0
/*216 */         freeaddrinfo(local);                                                    // 0.0
/*218 */     if (peer)                                                                   // 0.0
/*220 */         freeaddrinfo(peer);                                                     // 0.0
/*222 */     return -1;                                                                  // 0.0
/*224 */ }                                                                               // 0.0
