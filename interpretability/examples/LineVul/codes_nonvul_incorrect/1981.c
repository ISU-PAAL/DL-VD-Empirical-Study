// commit message qemu@6b9b8758c1 (target=0, prob=0.53508306, correct=False): virtio-net: only delete bh that existed
/*0  */ static int virtio_net_device_exit(DeviceState *qdev)        // (12) 0.0332
/*2  */ {                                                           // (30) 0.001953
/*4  */     VirtIONet *n = VIRTIO_NET(qdev);                        // (9) 0.03516
/*6  */     VirtIODevice *vdev = VIRTIO_DEVICE(qdev);               // (2) 0.04297
/*8  */     int i;                                                  // (26) 0.01172
/*12 */     /* This will stop vhost backend if appropriate. */      // (19) 0.02734
/*14 */     virtio_net_set_status(vdev, 0);                         // (13) 0.0332
/*18 */     unregister_savevm(qdev, "virtio-net", n);               // (8) 0.03906
/*22 */     if (n->netclient_name) {                                // (20) 0.02539
/*24 */         g_free(n->netclient_name);                          // (10) 0.03516
/*26 */         n->netclient_name = NULL;                           // (14) 0.03125
/*28 */     }                                                       // (27) 0.007812
/*30 */     if (n->netclient_type) {                                // (21) 0.02539
/*32 */         g_free(n->netclient_type);                          // (11) 0.03516
/*34 */         n->netclient_type = NULL;                           // (15) 0.03125
/*36 */     }                                                       // (28) 0.007812
/*40 */     g_free(n->mac_table.macs);                              // (16) 0.03125
/*42 */     g_free(n->vlans);                                       // (23) 0.02344
/*46 */     for (i = 0; i < n->max_queues; i++) {                   // (5) 0.04102
/*48 */         VirtIONetQueue *q = &n->vqs[i];                     // (3) 0.04297
/*50 */         NetClientState *nc = qemu_get_subqueue(n->nic, i);  // (0) 0.05469
/*54 */         qemu_purge_queued_packets(nc);                      // (4) 0.04297
/*58 */         if (q->tx_timer) {                                  // (17) 0.03125
/*60 */             timer_del(q->tx_timer);                         // (6) 0.04102
/*62 */             timer_free(q->tx_timer);                        // (7) 0.04102
/*64 */         } else {                                            // (24) 0.01953
/*66 */             qemu_bh_delete(q->tx_bh);                       // (1) 0.04883
/*68 */         }                                                   // (25) 0.01562
/*70 */     }                                                       // (29) 0.007812
/*74 */     g_free(n->vqs);                                         // (22) 0.02344
/*76 */     qemu_del_nic(n->nic);                                   // (18) 0.0293
/*78 */     virtio_cleanup(vdev);                                   // 0.0
/*82 */     return 0;                                               // 0.0
/*84 */ }                                                           // 0.0
