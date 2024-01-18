// commit message qemu@d6085e3ace (target=0, prob=0.6505058, correct=False): net: remove implicit peer from offload API
/*0  */ static void vmxnet3_update_features(VMXNET3State *s)                           // (13) 0.03711
/*2  */ {                                                                              // (17) 0.001953
/*4  */     uint32_t guest_features;                                                   // (15) 0.02148
/*6  */     int rxcso_supported;                                                       // (16) 0.01953
/*10 */     guest_features = VMXNET3_READ_DRV_SHARED32(s->drv_shmem,                   // (6) 0.05859
/*12 */                                                devRead.misc.uptFeatures);      // (0) 0.1055
/*16 */     rxcso_supported = VMXNET_FLAG_IS_SET(guest_features, UPT1_F_RXCSUM);       // (2) 0.06836
/*18 */     s->rx_vlan_stripping = VMXNET_FLAG_IS_SET(guest_features, UPT1_F_RXVLAN);  // (1) 0.07617
/*20 */     s->lro_supported = VMXNET_FLAG_IS_SET(guest_features, UPT1_F_LRO);         // (4) 0.06641
/*24 */     VMW_CFPRN("Features configuration: LRO: %d, RXCSUM: %d, VLANSTRIP: %d",    // (3) 0.06641
/*26 */               s->lro_supported, rxcso_supported,                               // (10) 0.05078
/*28 */               s->rx_vlan_stripping);                                           // (12) 0.04492
/*30 */     if (s->peer_has_vhdr) {                                                    // (14) 0.03125
/*32 */         qemu_peer_set_offload(qemu_get_queue(s->nic),                          // (5) 0.05859
/*34 */                         rxcso_supported,                                       // (9) 0.05664
/*36 */                         s->lro_supported,                                      // (7) 0.05859
/*38 */                         s->lro_supported,                                      // (8) 0.05859
/*40 */                         0,                                                     // (11) 0.04883
/*42 */                         0);                                                    // 0.0
/*44 */     }                                                                          // 0.0
/*46 */ }                                                                              // 0.0
