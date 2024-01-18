// commit message qemu@8172539d21 (target=0, prob=0.06494862, correct=True): virtio: add features as qdev properties
/*0   */ static void s390_virtio_device_sync(VirtIOS390Device *dev)                             // (11) 0.04102
/*2   */ {                                                                                      // (20) 0.001953
/*4   */     VirtIOS390Bus *bus = DO_UPCAST(VirtIOS390Bus, bus, dev->qdev.parent_bus);          // (3) 0.06836
/*6   */     ram_addr_t cur_offs;                                                               // (15) 0.02344
/*8   */     uint8_t num_vq;                                                                    // (16) 0.02344
/*10  */     int i;                                                                             // (19) 0.01172
/*14  */     virtio_reset(dev->vdev);                                                           // (14) 0.02539
/*18  */     /* Sync dev space */                                                               // (18) 0.01562
/*20  */     stb_phys(dev->dev_offs + VIRTIO_DEV_OFFS_TYPE, dev->vdev->device_id);              // (6) 0.06641
/*24  */     stb_phys(dev->dev_offs + VIRTIO_DEV_OFFS_NUM_VQ, s390_virtio_device_num_vq(dev));  // (0) 0.08398
/*26  */     stb_phys(dev->dev_offs + VIRTIO_DEV_OFFS_FEATURE_LEN, dev->feat_len);              // (4) 0.06836
/*30  */     stb_phys(dev->dev_offs + VIRTIO_DEV_OFFS_CONFIG_LEN, dev->vdev->config_len);       // (1) 0.07422
/*34  */     num_vq = s390_virtio_device_num_vq(dev);                                           // (9) 0.04492
/*36  */     stb_phys(dev->dev_offs + VIRTIO_DEV_OFFS_NUM_VQ, num_vq);                          // (7) 0.06445
/*40  */     /* Sync virtqueues */                                                              // (17) 0.01758
/*42  */     for (i = 0; i < num_vq; i++) {                                                     // (12) 0.03711
/*44  */         ram_addr_t vq = (dev->dev_offs + VIRTIO_DEV_OFFS_CONFIG) +                     // (5) 0.06836
/*46  */                         (i * VIRTIO_VQCONFIG_LEN);                                     // (2) 0.07422
/*48  */         ram_addr_t vring;                                                              // (13) 0.0293
/*52  */         vring = s390_virtio_next_ring(bus);                                            // (10) 0.04297
/*54  */         virtio_queue_set_addr(dev->vdev, i, vring);                                    // (8) 0.05078
/*56  */         virtio_queue_set_vector(dev->vdev, i, i);                                      // 0.0
/*58  */         stq_phys(vq + VIRTIO_VQCONFIG_OFFS_ADDRESS, vring);                            // 0.0
/*60  */         stw_phys(vq + VIRTIO_VQCONFIG_OFFS_NUM, virtio_queue_get_num(dev->vdev, i));   // 0.0
/*62  */     }                                                                                  // 0.0
/*66  */     cur_offs = dev->dev_offs;                                                          // 0.0
/*68  */     cur_offs += VIRTIO_DEV_OFFS_CONFIG;                                                // 0.0
/*70  */     cur_offs += num_vq * VIRTIO_VQCONFIG_LEN;                                          // 0.0
/*74  */     /* Sync feature bitmap */                                                          // 0.0
/*76  */     if (dev->vdev->get_features) {                                                     // 0.0
/*78  */         stl_phys(cur_offs, dev->vdev->get_features(dev->vdev));                        // 0.0
/*80  */     }                                                                                  // 0.0
/*84  */     dev->feat_offs = cur_offs + dev->feat_len;                                         // 0.0
/*86  */     cur_offs += dev->feat_len * 2;                                                     // 0.0
/*90  */     /* Sync config space */                                                            // 0.0
/*92  */     if (dev->vdev->get_config) {                                                       // 0.0
/*94  */         dev->vdev->get_config(dev->vdev, dev->vdev->config);                           // 0.0
/*96  */     }                                                                                  // 0.0
/*100 */     cpu_physical_memory_rw(cur_offs, dev->vdev->config, dev->vdev->config_len, 1);     // 0.0
/*102 */     cur_offs += dev->vdev->config_len;                                                 // 0.0
/*104 */ }                                                                                      // 0.0
