// commit message qemu@fc6c9257c6 (target=0, prob=0.54243237, correct=False): slirp: Adding ICMPv6 error sending
/*0  */ void ip6_input(struct mbuf *m)                                                 // (16) 0.02449
/*2  */ {                                                                              // (37) 0.002041
/*4  */     struct ip6 *ip6;                                                           // (19) 0.02041
/*8  */     DEBUG_CALL("ip6_input");                                                   // (12) 0.02653
/*10 */     DEBUG_ARG("m = %lx", (long)m);                                             // (3) 0.03878
/*12 */     DEBUG_ARG("m_len = %d", m->m_len);                                         // (2) 0.04286
/*16 */     if (m->m_len < sizeof(struct ip6)) {                                       // (5) 0.03673
/*18 */         goto bad;                                                              // (20) 0.02041
/*20 */     }                                                                          // (30) 0.008163
/*24 */     ip6 = mtod(m, struct ip6 *);                                               // (7) 0.03265
/*28 */     if (ip6->ip_v != IP6VERSION) {                                             // (6) 0.03469
/*30 */         goto bad;                                                              // (21) 0.02041
/*32 */     }                                                                          // (31) 0.008163
/*36 */     /* check ip_ttl for a correct ICMP reply */                                // (8) 0.03265
/*38 */     if (ip6->ip_hl == 0) {                                                     // (9) 0.03061
/*40 */         /*icmp_send_error(m, ICMP_TIMXCEED,ICMP_TIMXCEED_INTRANS, 0,"ttl");*/  // (0) 0.09184
/*42 */         goto bad;                                                              // (22) 0.02041
/*44 */     }                                                                          // (32) 0.008163
/*48 */     /*                                                                         // (33) 0.008163
/*50 */      * Switch out to protocol's input routine.                                 // (13) 0.02653
/*52 */      */                                                                        // (27) 0.0102
/*54 */     switch (ip6->ip_nh) {                                                      // (11) 0.02857
/*56 */     case IPPROTO_TCP:                                                          // (18) 0.02245
/*58 */         /*tcp_input(m, hlen, (struct socket *)NULL);*/                         // (1) 0.05102
/*60 */         break;                                                                 // (23) 0.01837
/*62 */     case IPPROTO_UDP:                                                          // (17) 0.02245
/*64 */         /*udp_input(m, hlen);*/                                                // (4) 0.03878
/*66 */         break;                                                                 // (24) 0.01837
/*68 */     case IPPROTO_ICMPV6:                                                       // (14) 0.02653
/*70 */         icmp6_input(m);                                                        // (10) 0.03061
/*72 */         break;                                                                 // (25) 0.01837
/*74 */     default:                                                                   // (28) 0.0102
/*76 */         m_free(m);                                                             // (15) 0.02653
/*78 */     }                                                                          // (34) 0.008163
/*80 */     return;                                                                    // (29) 0.0102
/*82 */ bad:                                                                           // (35) 0.004082
/*84 */     m_free(m);                                                                 // (26) 0.01837
/*86 */ }                                                                              // (36) 0.002041
