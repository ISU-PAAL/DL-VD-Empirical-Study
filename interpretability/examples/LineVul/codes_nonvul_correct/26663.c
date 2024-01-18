// commit message qemu@eb700029c7 (target=0, prob=0.03963154, correct=True): net_pkt: Extend packet abstraction as required by e1000e functionality
/*0  */ eth_setup_ip4_fragmentation(const void *l2hdr, size_t l2hdr_len,               // (8) 0.0587
/*2  */                             void *l3hdr, size_t l3hdr_len,                     // (0) 0.08907
/*4  */                             size_t l3payload_len,                              // (3) 0.0749
/*6  */                             size_t frag_offset, bool more_frags)               // (1) 0.08097
/*8  */ {                                                                              // (16) 0.002024
/*10 */     if (eth_get_l3_proto(l2hdr, l2hdr_len) == ETH_P_IP) {                      // (6) 0.07085
/*12 */         uint16_t orig_flags;                                                   // (14) 0.03036
/*14 */         struct ip_header *iphdr = (struct ip_header *) l3hdr;                  // (10) 0.05263
/*16 */         uint16_t frag_off_units = frag_offset / IP_FRAG_UNIT_SIZE;             // (7) 0.06275
/*18 */         uint16_t new_ip_off;                                                   // (13) 0.03441
/*22 */         assert(frag_offset % IP_FRAG_UNIT_SIZE == 0);                          // (11) 0.05263
/*24 */         assert((frag_off_units & ~IP_OFFMASK) == 0);                           // (12) 0.05263
/*28 */         orig_flags = be16_to_cpu(iphdr->ip_off) & ~(IP_OFFMASK|IP_MF);         // (2) 0.07692
/*30 */         new_ip_off = frag_off_units | orig_flags  | (more_frags ? IP_MF : 0);  // (5) 0.07287
/*32 */         iphdr->ip_off = cpu_to_be16(new_ip_off);                               // (9) 0.05668
/*34 */         iphdr->ip_len = cpu_to_be16(l3payload_len + l3hdr_len);                // (4) 0.07287
/*36 */     }                                                                          // (15) 0.008097
/*38 */ }                                                                              // (17) 0.002024
