// commit message qemu@df8bf7a7fe (target=1, prob=0.019337311, correct=False): NetRxPkt: Fix memory corruption on VLAN header stripping
/*0  */ bool net_rx_pkt_is_vlan_stripped(struct NetRxPkt *pkt)  // (0) 0.4407
/*2  */ {                                                       // (3) 0.01695
/*4  */     assert(pkt);                                        // (2) 0.1356
/*8  */     return pkt->vlan_stripped;                          // (1) 0.2203
/*10 */ }                                                       // (4) 0.01695
