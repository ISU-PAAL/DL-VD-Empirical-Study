// commit message qemu@bbe2f399b2 (target=0, prob=0.8566822, correct=False): virtio-net: reorganize receive_filter()
/*0  */ static int receive_filter(VirtIONet *n, const uint8_t *buf, int size)     // (4) 0.0553
/*2  */ {                                                                         // (23) 0.002304
/*4  */     static const uint8_t bcast[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};  // (2) 0.07373
/*6  */     static const uint8_t vlan[] = {0x81, 0x00};                           // (6) 0.05069
/*8  */     uint8_t *ptr = (uint8_t *)buf;                                        // (9) 0.04147
/*10 */     int i;                                                                // (19) 0.01382
/*14 */     if (n->promisc)                                                       // (14) 0.02304
/*16 */         return 1;                                                         // (15) 0.02304
/*20 */     if (!memcmp(&ptr[12], vlan, sizeof(vlan))) {                          // (7) 0.04839
/*22 */         int vid = be16_to_cpup((uint16_t *)(ptr + 14)) & 0xfff;           // (1) 0.07834
/*24 */         if (!(n->vlans[vid >> 5] & (1U << (vid & 0x1f))))                 // (3) 0.07373
/*26 */             return 0;                                                     // (12) 0.03226
/*28 */     }                                                                     // (21) 0.009217
/*32 */     if ((ptr[0] & 1) && n->allmulti)                                      // (10) 0.04147
/*34 */         return 1;                                                         // (16) 0.02304
/*38 */     if (!memcmp(ptr, bcast, sizeof(bcast)))                               // (11) 0.04147
/*40 */         return 1;                                                         // (17) 0.02304
/*44 */     if (!memcmp(ptr, n->mac, ETH_ALEN))                                   // (8) 0.04378
/*46 */         return 1;                                                         // (18) 0.02304
/*50 */     for (i = 0; i < n->mac_table.in_use; i++) {                           // (5) 0.0553
/*52 */         if (!memcmp(ptr, &n->mac_table.macs[i * ETH_ALEN], ETH_ALEN))     // (0) 0.08295
/*54 */             return 1;                                                     // (13) 0.03226
/*56 */     }                                                                     // (22) 0.009217
/*60 */     return 0;                                                             // (20) 0.01382
/*62 */ }                                                                         // (24) 0.002304
