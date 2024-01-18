// commit message qemu@086abc1ccd (target=0, prob=0.24914913, correct=True): virtio-net: purge outstanding packets when starting vhost
/*0  */ static void virtio_net_vhost_status(VirtIONet *n, uint8_t status)   // (6) 0.05123
/*2  */ {                                                                   // (27) 0.002049
/*4  */     VirtIODevice *vdev = VIRTIO_DEVICE(n);                          // (7) 0.04303
/*6  */     NetClientState *nc = qemu_get_queue(n->nic);                    // (8) 0.04303
/*8  */     int queues = n->multiqueue ? n->max_queues : 1;                 // (9) 0.04303
/*12 */     if (!get_vhost_net(nc->peer)) {                                 // (11) 0.03484
/*14 */         return;                                                     // (19) 0.01844
/*16 */     }                                                               // (24) 0.008197
/*20 */     if (!!n->vhost_started ==                                       // (15) 0.02664
/*22 */         (virtio_net_started(n, status) && !nc->peer->link_down)) {  // (2) 0.06148
/*24 */         return;                                                     // (20) 0.01844
/*26 */     }                                                               // (25) 0.008197
/*28 */     if (!n->vhost_started) {                                        // (16) 0.02664
/*30 */         int r;                                                      // (18) 0.02049
/*32 */         if (!vhost_net_query(get_vhost_net(nc->peer), vdev)) {      // (1) 0.06352
/*34 */             return;                                                 // (17) 0.02664
/*36 */         }                                                           // (21) 0.01639
/*38 */         n->vhost_started = 1;                                       // (12) 0.03279
/*40 */         r = vhost_net_start(vdev, n->nic->ncs, queues);             // (3) 0.05738
/*42 */         if (r < 0) {                                                // (14) 0.02869
/*44 */             error_report("unable to start vhost net: %d: "          // (4) 0.05533
/*46 */                          "falling back on userspace virtio", -r);   // (0) 0.07582
/*48 */             n->vhost_started = 0;                                   // (10) 0.04098
/*50 */         }                                                           // (22) 0.01639
/*52 */     } else {                                                        // (23) 0.0123
/*54 */         vhost_net_stop(vdev, n->nic->ncs, queues);                  // (5) 0.05328
/*56 */         n->vhost_started = 0;                                       // (13) 0.03279
/*58 */     }                                                               // (26) 0.008197
/*60 */ }                                                                   // (28) 0.002049
