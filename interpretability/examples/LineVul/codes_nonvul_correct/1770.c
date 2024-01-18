// commit message qemu@eb700029c7 (target=0, prob=0.02377947, correct=True): net_pkt: Extend packet abstraction as required by e1000e functionality
/*0  */ static uint8_t net_tx_pkt_get_gso_type(struct NetTxPkt *pkt,                   // (5) 0.08589
/*2  */                                           bool tso_enable)                     // (0) 0.1442
/*4  */ {                                                                              // (13) 0.003067
/*6  */     uint8_t rc = VIRTIO_NET_HDR_GSO_NONE;                                      // (6) 0.07362
/*8  */     uint16_t l3_proto;                                                         // (7) 0.03988
/*12 */     l3_proto = eth_get_l3_proto(pkt->vec[NET_TX_PKT_L2HDR_FRAG].iov_base,      // (2) 0.1319
/*14 */         pkt->vec[NET_TX_PKT_L2HDR_FRAG].iov_len);                              // (4) 0.09509
/*18 */     if (!tso_enable) {                                                         // (9) 0.03374
/*20 */         goto func_exit;                                                        // (8) 0.03681
/*22 */     }                                                                          // (11) 0.01227
/*26 */     rc = eth_get_gso_type(l3_proto, pkt->vec[NET_TX_PKT_L3HDR_FRAG].iov_base,  // (1) 0.135
/*28 */                           pkt->l4proto);                                       // (3) 0.1012
/*32 */ func_exit:                                                                     // (12) 0.01227
/*34 */     return rc;                                                                 // (10) 0.0184
/*36 */ }                                                                              // (14) 0.003067
