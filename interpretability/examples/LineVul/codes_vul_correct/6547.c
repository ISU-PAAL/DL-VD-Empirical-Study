// commit message qemu@aa4a3dce1c (target=1, prob=0.51671803, correct=True): net: vmxnet3: avoid memory leakage in activate_device
/*0  */ static void vmxnet3_net_uninit(VMXNET3State *s)  // (3) 0.1562
/*2  */ {                                                // (6) 0.007812
/*4  */     g_free(s->mcast_list);                       // (5) 0.1094
/*6  */     vmxnet_tx_pkt_reset(s->tx_pkt);              // (2) 0.1641
/*8  */     vmxnet_tx_pkt_uninit(s->tx_pkt);             // (0) 0.1719
/*10 */     vmxnet_rx_pkt_uninit(s->rx_pkt);             // (1) 0.1719
/*12 */     qemu_del_nic(s->nic);                        // (4) 0.1172
/*14 */ }                                                // (7) 0.007812
