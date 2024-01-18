// commit message qemu@b63c7f6b77 (target=0, prob=0.4697187, correct=True): slirp: Handle DHCP requests for specific IP (Jan Kiszka)
/*0   */ static void bootp_reply(struct bootp_t *bp)                                   // (13) 0.0293
/*2   */ {                                                                             // (28) 0.001954
/*4   */     BOOTPClient *bc;                                                          // (21) 0.01953
/*6   */     struct mbuf *m;                                                           // (24) 0.01758
/*8   */     struct bootp_t *rbp;                                                      // (19) 0.02344
/*10  */     struct sockaddr_in saddr, daddr;                                          // (14) 0.02734
/*12  */     struct in_addr dns_addr;                                                  // (18) 0.02344
/*14  */     int dhcp_msg_type, val;                                                   // (17) 0.02539
/*16  */     uint8_t *q;                                                               // (23) 0.01953
/*20  */     /* extract exact DHCP msg type */                                         // (22) 0.01953
/*22  */     dhcp_decode(bp->bp_vend, DHCP_OPT_LEN, &dhcp_msg_type);                   // (1) 0.0625
/*24  */     dprintf("bootp packet op=%d msgtype=%d\n", bp->bp_op, dhcp_msg_type);     // (0) 0.06836
/*28  */     if (dhcp_msg_type == 0)                                                   // (15) 0.02734
/*30  */         dhcp_msg_type = DHCPREQUEST; /* Force reply for old BOOTP clients */  // (2) 0.05469
/*34  */     if (dhcp_msg_type != DHCPDISCOVER &&                                      // (7) 0.03711
/*36  */         dhcp_msg_type != DHCPREQUEST)                                         // (9) 0.03516
/*38  */         return;                                                               // (25) 0.01758
/*40  */     /* XXX: this is a hack to get the client mac address */                   // (10) 0.0332
/*42  */     memcpy(client_ethaddr, bp->bp_hwaddr, 6);                                 // (4) 0.04297
/*46  */     if ((m = m_get()) == NULL)                                                // (16) 0.02734
/*48  */         return;                                                               // (26) 0.01758
/*50  */     m->m_data += IF_MAXLINKHDR;                                               // (11) 0.0332
/*52  */     rbp = (struct bootp_t *)m->m_data;                                        // (8) 0.03711
/*54  */     m->m_data += sizeof(struct udpiphdr);                                     // (12) 0.0332
/*56  */     memset(rbp, 0, sizeof(struct bootp_t));                                   // (6) 0.03711
/*60  */     if (dhcp_msg_type == DHCPDISCOVER) {                                      // (5) 0.03906
/*62  */     new_addr:                                                                 // (27) 0.01367
/*64  */         bc = get_new_addr(&daddr.sin_addr);                                   // (3) 0.04297
/*66  */         if (!bc) {                                                            // (20) 0.02344
/*68  */             dprintf("no address left\n");                                     // 0.0
/*70  */             return;                                                           // 0.0
/*72  */         }                                                                     // 0.0
/*74  */         memcpy(bc->macaddr, client_ethaddr, 6);                               // 0.0
/*76  */     } else {                                                                  // 0.0
/*78  */         bc = find_addr(&daddr.sin_addr, bp->bp_hwaddr);                       // 0.0
/*80  */         if (!bc) {                                                            // 0.0
/*82  */             /* if never assigned, behaves as if it was already                // 0.0
/*84  */                assigned (windows fix because it remembers its address) */     // 0.0
/*86  */             goto new_addr;                                                    // 0.0
/*88  */         }                                                                     // 0.0
/*90  */     }                                                                         // 0.0
/*94  */     if (bootp_filename)                                                       // 0.0
/*96  */         snprintf((char *)rbp->bp_file, sizeof(rbp->bp_file), "%s",            // 0.0
/*98  */                  bootp_filename);                                             // 0.0
/*102 */     dprintf("offered addr=%08x\n", ntohl(daddr.sin_addr.s_addr));             // 0.0
/*106 */     saddr.sin_addr.s_addr = htonl(ntohl(special_addr.s_addr) | CTL_ALIAS);    // 0.0
/*108 */     saddr.sin_port = htons(BOOTP_SERVER);                                     // 0.0
/*112 */     daddr.sin_port = htons(BOOTP_CLIENT);                                     // 0.0
/*116 */     rbp->bp_op = BOOTP_REPLY;                                                 // 0.0
/*118 */     rbp->bp_xid = bp->bp_xid;                                                 // 0.0
/*120 */     rbp->bp_htype = 1;                                                        // 0.0
/*122 */     rbp->bp_hlen = 6;                                                         // 0.0
/*124 */     memcpy(rbp->bp_hwaddr, bp->bp_hwaddr, 6);                                 // 0.0
/*128 */     rbp->bp_yiaddr = daddr.sin_addr; /* Client IP address */                  // 0.0
/*130 */     rbp->bp_siaddr = saddr.sin_addr; /* Server IP address */                  // 0.0
/*134 */     daddr.sin_addr.s_addr = 0xffffffffu;                                      // 0.0
/*138 */     q = rbp->bp_vend;                                                         // 0.0
/*140 */     memcpy(q, rfc1533_cookie, 4);                                             // 0.0
/*142 */     q += 4;                                                                   // 0.0
/*146 */     if (dhcp_msg_type == DHCPDISCOVER) {                                      // 0.0
/*148 */         *q++ = RFC2132_MSG_TYPE;                                              // 0.0
/*150 */         *q++ = 1;                                                             // 0.0
/*152 */         *q++ = DHCPOFFER;                                                     // 0.0
/*154 */     } else if (dhcp_msg_type == DHCPREQUEST) {                                // 0.0
/*156 */         *q++ = RFC2132_MSG_TYPE;                                              // 0.0
/*158 */         *q++ = 1;                                                             // 0.0
/*160 */         *q++ = DHCPACK;                                                       // 0.0
/*162 */     }                                                                         // 0.0
/*166 */     if (dhcp_msg_type == DHCPDISCOVER ||                                      // 0.0
/*168 */         dhcp_msg_type == DHCPREQUEST) {                                       // 0.0
/*170 */         *q++ = RFC2132_SRV_ID;                                                // 0.0
/*172 */         *q++ = 4;                                                             // 0.0
/*174 */         memcpy(q, &saddr.sin_addr, 4);                                        // 0.0
/*176 */         q += 4;                                                               // 0.0
/*180 */         *q++ = RFC1533_NETMASK;                                               // 0.0
/*182 */         *q++ = 4;                                                             // 0.0
/*184 */         *q++ = 0xff;                                                          // 0.0
/*186 */         *q++ = 0xff;                                                          // 0.0
/*188 */         *q++ = 0xff;                                                          // 0.0
/*190 */         *q++ = 0x00;                                                          // 0.0
/*194 */         if (!slirp_restrict) {                                                // 0.0
/*196 */             *q++ = RFC1533_GATEWAY;                                           // 0.0
/*198 */             *q++ = 4;                                                         // 0.0
/*200 */             memcpy(q, &saddr.sin_addr, 4);                                    // 0.0
/*202 */             q += 4;                                                           // 0.0
/*206 */             *q++ = RFC1533_DNS;                                               // 0.0
/*208 */             *q++ = 4;                                                         // 0.0
/*210 */             dns_addr.s_addr = htonl(ntohl(special_addr.s_addr) | CTL_DNS);    // 0.0
/*212 */             memcpy(q, &dns_addr, 4);                                          // 0.0
/*214 */             q += 4;                                                           // 0.0
/*216 */         }                                                                     // 0.0
/*220 */         *q++ = RFC2132_LEASE_TIME;                                            // 0.0
/*222 */         *q++ = 4;                                                             // 0.0
/*224 */         val = htonl(LEASE_TIME);                                              // 0.0
/*226 */         memcpy(q, &val, 4);                                                   // 0.0
/*228 */         q += 4;                                                               // 0.0
/*232 */         if (*slirp_hostname) {                                                // 0.0
/*234 */             val = strlen(slirp_hostname);                                     // 0.0
/*236 */             *q++ = RFC1533_HOSTNAME;                                          // 0.0
/*238 */             *q++ = val;                                                       // 0.0
/*240 */             memcpy(q, slirp_hostname, val);                                   // 0.0
/*242 */             q += val;                                                         // 0.0
/*244 */         }                                                                     // 0.0
/*246 */     }                                                                         // 0.0
/*248 */     *q++ = RFC1533_END;                                                       // 0.0
/*252 */     m->m_len = sizeof(struct bootp_t) -                                       // 0.0
/*254 */         sizeof(struct ip) - sizeof(struct udphdr);                            // 0.0
/*256 */     udp_output2(NULL, m, &saddr, &daddr, IPTOS_LOWDELAY);                     // 0.0
/*258 */ }                                                                             // 0.0
