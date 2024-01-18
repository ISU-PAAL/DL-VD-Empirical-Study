// commit message qemu@955cc8c954 (target=0, prob=0.33241394, correct=True): virtio-ccw: using VIRTIO_NO_VECTOR instead of 0 for invalid virtqueue
/*0  */ static int virtio_ccw_set_vqs(SubchDev *sch, uint64_t addr, uint32_t align,  // (1) 0.06652
/*2  */                               uint16_t index, uint16_t num)                  // (0) 0.08798
/*4  */ {                                                                            // (27) 0.002146
/*6  */     VirtIODevice *vdev = virtio_ccw_get_vdev(sch);                           // (3) 0.05365
/*10 */     if (index >= VIRTIO_PCI_QUEUE_MAX) {                                     // (7) 0.04506
/*12 */         return -EINVAL;                                                      // (14) 0.0279
/*14 */     }                                                                        // (23) 0.008584
/*18 */     /* Current code in virtio.c relies on 4K alignment. */                   // (11) 0.03863
/*20 */     if (addr && (align != 4096)) {                                           // (15) 0.0279
/*22 */         return -EINVAL;                                                      // (16) 0.0279
/*24 */     }                                                                        // (24) 0.008584
/*28 */     if (!vdev) {                                                             // (18) 0.01931
/*30 */         return -EINVAL;                                                      // (17) 0.0279
/*32 */     }                                                                        // (25) 0.008584
/*36 */     virtio_queue_set_addr(vdev, index, addr);                                // (10) 0.04077
/*38 */     if (!addr) {                                                             // (19) 0.01717
/*40 */         virtio_queue_set_vector(vdev, index, 0);                             // (4) 0.04936
/*42 */     } else {                                                                 // (21) 0.01288
/*44 */         /* Fail if we don't have a big enough queue. */                      // (9) 0.04292
/*46 */         /* TODO: Add interface to handle vring.num changing */               // (8) 0.04506
/*48 */         if (virtio_queue_get_num(vdev, index) > num) {                       // (2) 0.05794
/*50 */             return -EINVAL;                                                  // (12) 0.03648
/*52 */         }                                                                    // (20) 0.01717
/*54 */         virtio_queue_set_vector(vdev, index, index);                         // (5) 0.04936
/*56 */     }                                                                        // (26) 0.008584
/*58 */     /* tell notify handler in case of config change */                       // (13) 0.0279
/*60 */     vdev->config_vector = VIRTIO_PCI_QUEUE_MAX;                              // (6) 0.04936
/*62 */     return 0;                                                                // (22) 0.01288
/*64 */ }                                                                            // (28) 0.002146
