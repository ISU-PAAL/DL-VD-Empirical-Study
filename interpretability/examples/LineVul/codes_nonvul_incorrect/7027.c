// commit message qemu@eb700029c7 (target=0, prob=0.69534826, correct=False): net_pkt: Extend packet abstraction as required by e1000e functionality
/*0  */ static size_t net_tx_pkt_fetch_fragment(struct NetTxPkt *pkt,               // (4) 0.05273
/*2  */     int *src_idx, size_t *src_offset, struct iovec *dst, int *dst_idx)      // (3) 0.06641
/*4  */ {                                                                           // (21) 0.001953
/*6  */     size_t fetched = 0;                                                     // (18) 0.02148
/*8  */     struct iovec *src = pkt->vec;                                           // (15) 0.0293
/*12 */     *dst_idx = NET_TX_PKT_FRAGMENT_HEADER_NUM;                              // (7) 0.05078
/*16 */     while (fetched < pkt->virt_hdr.gso_size) {                              // (11) 0.04102
/*20 */         /* no more place in fragment iov */                                 // (13) 0.03125
/*22 */         if (*dst_idx == NET_MAX_FRAG_SG_LIST) {                             // (5) 0.05273
/*24 */             break;                                                          // (17) 0.02539
/*26 */         }                                                                   // (20) 0.01562
/*30 */         /* no more data in iovec */                                         // (14) 0.03125
/*32 */         if (*src_idx == (pkt->payload_frags + NET_TX_PKT_PL_START_FRAG)) {  // (0) 0.07812
/*34 */             break;                                                          // (16) 0.02539
/*36 */         }                                                                   // (19) 0.01562
/*42 */         dst[*dst_idx].iov_base = src[*src_idx].iov_base + *src_offset;      // (2) 0.07227
/*44 */         dst[*dst_idx].iov_len = MIN(src[*src_idx].iov_len - *src_offset,    // (1) 0.07617
/*46 */             pkt->virt_hdr.gso_size - fetched);                              // (6) 0.05273
/*50 */         *src_offset += dst[*dst_idx].iov_len;                               // (9) 0.04883
/*52 */         fetched += dst[*dst_idx].iov_len;                                   // (10) 0.04492
/*56 */         if (*src_offset == src[*src_idx].iov_len) {                         // (8) 0.05078
/*58 */             *src_offset = 0;                                                // (12) 0.03516
/*60 */             (*src_idx)++;                                                   // 0.0
/*62 */         }                                                                   // 0.0
/*66 */         (*dst_idx)++;                                                       // 0.0
/*68 */     }                                                                       // 0.0
/*72 */     return fetched;                                                         // 0.0
/*74 */ }                                                                           // 0.0
