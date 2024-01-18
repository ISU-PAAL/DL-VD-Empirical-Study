// commit message qemu@b4f72e31b9 (target=1, prob=0.20057556, correct=False): hw/net/xen_nic.c: Free 'netdev->txs' when map 'netdev->rxs' fails
/*0  */ static int net_connect(struct XenDevice *xendev)                                     // (10) 0.02734
/*2  */ {                                                                                    // (23) 0.001953
/*4  */     struct XenNetDev *netdev = container_of(xendev, struct XenNetDev, xendev);       // (8) 0.05469
/*6  */     int rx_copy;                                                                     // (17) 0.01758
/*10 */     if (xenstore_read_fe_int(&netdev->xendev, "tx-ring-ref",                         // (6) 0.05664
/*12 */                              &netdev->tx_ring_ref) == -1) {                          // (1) 0.08398
/*14 */         return -1;                                                                   // (13) 0.02148
/*16 */     }                                                                                // (18) 0.007812
/*18 */     if (xenstore_read_fe_int(&netdev->xendev, "rx-ring-ref",                         // (7) 0.05664
/*20 */                              &netdev->rx_ring_ref) == -1) {                          // (2) 0.08398
/*22 */         return 1;                                                                    // (16) 0.01953
/*24 */     }                                                                                // (19) 0.007812
/*26 */     if (xenstore_read_fe_int(&netdev->xendev, "event-channel",                       // (9) 0.05273
/*28 */                              &netdev->xendev.remote_port) == -1) {                   // (0) 0.08789
/*30 */         return -1;                                                                   // (14) 0.02148
/*32 */     }                                                                                // (20) 0.007812
/*36 */     if (xenstore_read_fe_int(&netdev->xendev, "request-rx-copy", &rx_copy) == -1) {  // (3) 0.07617
/*38 */         rx_copy = 0;                                                                 // (11) 0.02734
/*40 */     }                                                                                // (21) 0.007812
/*42 */     if (rx_copy == 0) {                                                              // (12) 0.02344
/*44 */         xen_be_printf(&netdev->xendev, 0, "frontend doesn't support rx-copy.\n");    // (4) 0.07031
/*46 */         return -1;                                                                   // (15) 0.02148
/*48 */     }                                                                                // (22) 0.007812
/*52 */     netdev->txs = xc_gnttab_map_grant_ref(netdev->xendev.gnttabdev,                  // (5) 0.06836
/*54 */                                           netdev->xendev.dom,                        // 0.0
/*56 */                                           netdev->tx_ring_ref,                       // 0.0
/*58 */                                           PROT_READ | PROT_WRITE);                   // 0.0
/*60 */     netdev->rxs = xc_gnttab_map_grant_ref(netdev->xendev.gnttabdev,                  // 0.0
/*62 */                                           netdev->xendev.dom,                        // 0.0
/*64 */                                           netdev->rx_ring_ref,                       // 0.0
/*66 */                                           PROT_READ | PROT_WRITE);                   // 0.0
/*68 */     if (!netdev->txs || !netdev->rxs) {                                              // 0.0
/*70 */         return -1;                                                                   // 0.0
/*72 */     }                                                                                // 0.0
/*74 */     BACK_RING_INIT(&netdev->tx_ring, netdev->txs, XC_PAGE_SIZE);                     // 0.0
/*76 */     BACK_RING_INIT(&netdev->rx_ring, netdev->rxs, XC_PAGE_SIZE);                     // 0.0
/*80 */     xen_be_bind_evtchn(&netdev->xendev);                                             // 0.0
/*84 */     xen_be_printf(&netdev->xendev, 1, "ok: tx-ring-ref %d, rx-ring-ref %d, "         // 0.0
/*86 */                   "remote port %d, local port %d\n",                                 // 0.0
/*88 */                   netdev->tx_ring_ref, netdev->rx_ring_ref,                          // 0.0
/*90 */                   netdev->xendev.remote_port, netdev->xendev.local_port);            // 0.0
/*94 */     net_tx_packets(netdev);                                                          // 0.0
/*96 */     return 0;                                                                        // 0.0
/*98 */ }                                                                                    // 0.0
