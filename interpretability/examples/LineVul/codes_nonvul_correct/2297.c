// commit message qemu@eb700029c7 (target=0, prob=0.09370104, correct=True): net_pkt: Extend packet abstraction as required by e1000e functionality
/*0  */ bool net_tx_pkt_add_raw_fragment(struct NetTxPkt *pkt, hwaddr pa,        // (0) 0.1075
/*2  */     size_t len)                                                          // (12) 0.02867
/*4  */ {                                                                        // (18) 0.003584
/*6  */     hwaddr mapped_len = 0;                                               // (7) 0.04301
/*8  */     struct iovec *ventry;                                                // (8) 0.03943
/*10 */     assert(pkt);                                                         // (13) 0.02867
/*12 */     assert(pkt->max_raw_frags > pkt->raw_frags);                         // (3) 0.08244
/*16 */     if (!len) {                                                          // (14) 0.02867
/*18 */         return true;                                                     // (9) 0.03584
/*20 */      }                                                                   // (16) 0.01792
/*24 */     ventry = &pkt->raw[pkt->raw_frags];                                  // (4) 0.07168
/*26 */     mapped_len = len;                                                    // (11) 0.03226
/*30 */     ventry->iov_base = cpu_physical_memory_map(pa, &mapped_len, false);  // (1) 0.1004
/*32 */     ventry->iov_len = mapped_len;                                        // (6) 0.05018
/*34 */     pkt->raw_frags += !!ventry->iov_base;                                // (5) 0.0681
/*38 */     if ((ventry->iov_base == NULL) || (len != mapped_len)) {             // (2) 0.08244
/*40 */         return false;                                                    // (10) 0.03584
/*42 */     }                                                                    // (17) 0.01434
/*46 */     return true;                                                         // (15) 0.02151
/*48 */ }                                                                        // (19) 0.003584
