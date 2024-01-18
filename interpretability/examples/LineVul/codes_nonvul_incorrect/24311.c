// commit message qemu@0928a95ffe (target=0, prob=0.5653169, correct=False): slirp: Reassign same address to same DHCP client
/*0   */ static void bootp_reply(const struct bootp_t *bp)                             // (12) 0.03125
/*2   */ {                                                                             // (29) 0.001955
/*4   */     BOOTPClient *bc = NULL;                                                   // (19) 0.02344
/*6   */     struct mbuf *m;                                                           // (25) 0.01758
/*8   */     struct bootp_t *rbp;                                                      // (20) 0.02344
/*10  */     struct sockaddr_in saddr, daddr;                                          // (14) 0.02734
/*12  */     struct in_addr dns_addr;                                                  // (21) 0.02344
/*14  */     const struct in_addr *preq_addr;                                          // (13) 0.02734
/*16  */     int dhcp_msg_type, val;                                                   // (17) 0.02539
/*18  */     uint8_t *q;                                                               // (22) 0.01953
/*22  */     /* extract exact DHCP msg type */                                         // (23) 0.01953
/*24  */     dhcp_decode(bp, &dhcp_msg_type, &preq_addr);                              // (3) 0.04883
/*26  */     dprintf("bootp packet op=%d msgtype=%d", bp->bp_op, dhcp_msg_type);       // (0) 0.06445
/*28  */     if (preq_addr)                                                            // (24) 0.01953
/*30  */         dprintf(" req_addr=%08x\n", ntohl(preq_addr->s_addr));                // (1) 0.06445
/*32  */     else                                                                      // (28) 0.007812
/*34  */         dprintf("\n");                                                        // (18) 0.02539
/*38  */     if (dhcp_msg_type == 0)                                                   // (15) 0.02734
/*40  */         dhcp_msg_type = DHCPREQUEST; /* Force reply for old BOOTP clients */  // (2) 0.05469
/*44  */     if (dhcp_msg_type != DHCPDISCOVER &&                                      // (5) 0.03711
/*46  */         dhcp_msg_type != DHCPREQUEST)                                         // (8) 0.03516
/*48  */         return;                                                               // (26) 0.01758
/*50  */     /* XXX: this is a hack to get the client mac address */                   // (9) 0.0332
/*52  */     memcpy(client_ethaddr, bp->bp_hwaddr, 6);                                 // (4) 0.04297
/*56  */     if ((m = m_get()) == NULL)                                                // (16) 0.02734
/*58  */         return;                                                               // (27) 0.01758
/*60  */     m->m_data += IF_MAXLINKHDR;                                               // (11) 0.0332
/*62  */     rbp = (struct bootp_t *)m->m_data;                                        // (7) 0.03711
/*64  */     m->m_data += sizeof(struct udpiphdr);                                     // (10) 0.0332
/*66  */     memset(rbp, 0, sizeof(struct bootp_t));                                   // (6) 0.03711
/*70  */     if (dhcp_msg_type == DHCPDISCOVER) {                                      // 0.0
/*72  */         if (preq_addr) {                                                      // 0.0
/*74  */             bc = request_addr(preq_addr, client_ethaddr);                     // 0.0
/*76  */             if (bc) {                                                         // 0.0
/*78  */                 daddr.sin_addr = *preq_addr;                                  // 0.0
/*80  */             }                                                                 // 0.0
/*82  */         }                                                                     // 0.0
/*84  */         if (!bc) {                                                            // 0.0
/*86  */          new_addr:                                                            // 0.0
/*88  */             bc = get_new_addr(&daddr.sin_addr);                               // 0.0
/*90  */             if (!bc) {                                                        // 0.0
/*92  */                 dprintf("no address left\n");                                 // 0.0
/*94  */                 return;                                                       // 0.0
/*96  */             }                                                                 // 0.0
/*98  */         }                                                                     // 0.0
/*100 */         memcpy(bc->macaddr, client_ethaddr, 6);                               // 0.0
/*102 */     } else if (preq_addr) {                                                   // 0.0
/*104 */         bc = request_addr(preq_addr, client_ethaddr);                         // 0.0
/*106 */         if (bc) {                                                             // 0.0
/*108 */             daddr.sin_addr = *preq_addr;                                      // 0.0
/*110 */             memcpy(bc->macaddr, client_ethaddr, 6);                           // 0.0
/*112 */         } else {                                                              // 0.0
/*114 */             daddr.sin_addr.s_addr = 0;                                        // 0.0
/*116 */         }                                                                     // 0.0
/*118 */     } else {                                                                  // 0.0
/*120 */         bc = find_addr(&daddr.sin_addr, bp->bp_hwaddr);                       // 0.0
/*122 */         if (!bc) {                                                            // 0.0
/*124 */             /* if never assigned, behaves as if it was already                // 0.0
/*126 */                assigned (windows fix because it remembers its address) */     // 0.0
/*128 */             goto new_addr;                                                    // 0.0
/*130 */         }                                                                     // 0.0
/*132 */     }                                                                         // 0.0
/*136 */     saddr.sin_addr.s_addr = htonl(ntohl(special_addr.s_addr) | CTL_ALIAS);    // 0.0
/*138 */     saddr.sin_port = htons(BOOTP_SERVER);                                     // 0.0
/*142 */     daddr.sin_port = htons(BOOTP_CLIENT);                                     // 0.0
/*146 */     rbp->bp_op = BOOTP_REPLY;                                                 // 0.0
/*148 */     rbp->bp_xid = bp->bp_xid;                                                 // 0.0
/*150 */     rbp->bp_htype = 1;                                                        // 0.0
/*152 */     rbp->bp_hlen = 6;                                                         // 0.0
/*154 */     memcpy(rbp->bp_hwaddr, bp->bp_hwaddr, 6);                                 // 0.0
/*158 */     rbp->bp_yiaddr = daddr.sin_addr; /* Client IP address */                  // 0.0
/*160 */     rbp->bp_siaddr = saddr.sin_addr; /* Server IP address */                  // 0.0
/*164 */     q = rbp->bp_vend;                                                         // 0.0
/*166 */     memcpy(q, rfc1533_cookie, 4);                                             // 0.0
/*168 */     q += 4;                                                                   // 0.0
/*172 */     if (bc) {                                                                 // 0.0
/*174 */         dprintf("%s addr=%08x\n",                                             // 0.0
/*176 */                 (dhcp_msg_type == DHCPDISCOVER) ? "offered" : "ack'ed",       // 0.0
/*178 */                 ntohl(daddr.sin_addr.s_addr));                                // 0.0
/*182 */         if (dhcp_msg_type == DHCPDISCOVER) {                                  // 0.0
/*184 */             *q++ = RFC2132_MSG_TYPE;                                          // 0.0
/*186 */             *q++ = 1;                                                         // 0.0
/*188 */             *q++ = DHCPOFFER;                                                 // 0.0
/*190 */         } else /* DHCPREQUEST */ {                                            // 0.0
/*192 */             *q++ = RFC2132_MSG_TYPE;                                          // 0.0
/*194 */             *q++ = 1;                                                         // 0.0
/*196 */             *q++ = DHCPACK;                                                   // 0.0
/*198 */         }                                                                     // 0.0
/*202 */         if (bootp_filename)                                                   // 0.0
/*204 */             snprintf((char *)rbp->bp_file, sizeof(rbp->bp_file), "%s",        // 0.0
/*206 */                      bootp_filename);                                         // 0.0
/*210 */         *q++ = RFC2132_SRV_ID;                                                // 0.0
/*212 */         *q++ = 4;                                                             // 0.0
/*214 */         memcpy(q, &saddr.sin_addr, 4);                                        // 0.0
/*216 */         q += 4;                                                               // 0.0
/*220 */         *q++ = RFC1533_NETMASK;                                               // 0.0
/*222 */         *q++ = 4;                                                             // 0.0
/*224 */         *q++ = 0xff;                                                          // 0.0
/*226 */         *q++ = 0xff;                                                          // 0.0
/*228 */         *q++ = 0xff;                                                          // 0.0
/*230 */         *q++ = 0x00;                                                          // 0.0
/*234 */         if (!slirp_restrict) {                                                // 0.0
/*236 */             *q++ = RFC1533_GATEWAY;                                           // 0.0
/*238 */             *q++ = 4;                                                         // 0.0
/*240 */             memcpy(q, &saddr.sin_addr, 4);                                    // 0.0
/*242 */             q += 4;                                                           // 0.0
/*246 */             *q++ = RFC1533_DNS;                                               // 0.0
/*248 */             *q++ = 4;                                                         // 0.0
/*250 */             dns_addr.s_addr = htonl(ntohl(special_addr.s_addr) | CTL_DNS);    // 0.0
/*252 */             memcpy(q, &dns_addr, 4);                                          // 0.0
/*254 */             q += 4;                                                           // 0.0
/*256 */         }                                                                     // 0.0
/*260 */         *q++ = RFC2132_LEASE_TIME;                                            // 0.0
/*262 */         *q++ = 4;                                                             // 0.0
/*264 */         val = htonl(LEASE_TIME);                                              // 0.0
/*266 */         memcpy(q, &val, 4);                                                   // 0.0
/*268 */         q += 4;                                                               // 0.0
/*272 */         if (*slirp_hostname) {                                                // 0.0
/*274 */             val = strlen(slirp_hostname);                                     // 0.0
/*276 */             *q++ = RFC1533_HOSTNAME;                                          // 0.0
/*278 */             *q++ = val;                                                       // 0.0
/*280 */             memcpy(q, slirp_hostname, val);                                   // 0.0
/*282 */             q += val;                                                         // 0.0
/*284 */         }                                                                     // 0.0
/*286 */     } else {                                                                  // 0.0
/*288 */         static const char nak_msg[] = "requested address not available";      // 0.0
/*292 */         dprintf("nak'ed addr=%08x\n", ntohl(preq_addr->s_addr));              // 0.0
/*296 */         *q++ = RFC2132_MSG_TYPE;                                              // 0.0
/*298 */         *q++ = 1;                                                             // 0.0
/*300 */         *q++ = DHCPNAK;                                                       // 0.0
/*304 */         *q++ = RFC2132_MESSAGE;                                               // 0.0
/*306 */         *q++ = sizeof(nak_msg) - 1;                                           // 0.0
/*308 */         memcpy(q, nak_msg, sizeof(nak_msg) - 1);                              // 0.0
/*310 */         q += sizeof(nak_msg) - 1;                                             // 0.0
/*312 */     }                                                                         // 0.0
/*314 */     *q++ = RFC1533_END;                                                       // 0.0
/*318 */     daddr.sin_addr.s_addr = 0xffffffffu;                                      // 0.0
/*322 */     m->m_len = sizeof(struct bootp_t) -                                       // 0.0
/*324 */         sizeof(struct ip) - sizeof(struct udphdr);                            // 0.0
/*326 */     udp_output2(NULL, m, &saddr, &daddr, IPTOS_LOWDELAY);                     // 0.0
/*328 */ }                                                                             // 0.0
