// commit message qemu@de13d21614 (target=0, prob=0.10174496, correct=True): s390x: cleanup interrupt injection
/*0  */ static int s390_virtio_device_init(VirtIOS390Device *dev, VirtIODevice *vdev)  // (3) 0.06424
/*2  */ {                                                                              // (21) 0.002141
/*4  */     VirtIOS390Bus *bus;                                                        // (16) 0.02355
/*6  */     int dev_len;                                                               // (18) 0.01713
/*10 */     bus = DO_UPCAST(VirtIOS390Bus, bus, dev->qdev.parent_bus);                 // (4) 0.0621
/*12 */     dev->vdev = vdev;                                                          // (17) 0.02355
/*14 */     dev->dev_offs = bus->dev_offs;                                             // (11) 0.03212
/*16 */     dev->feat_len = sizeof(uint32_t); /* always keep 32 bits features */       // (8) 0.04925
/*20 */     dev_len = VIRTIO_DEV_OFFS_CONFIG;                                          // (9) 0.04069
/*22 */     dev_len += s390_virtio_device_num_vq(dev) * VIRTIO_VQCONFIG_LEN;           // (2) 0.07495
/*24 */     dev_len += dev->feat_len * 2;                                              // (12) 0.03212
/*26 */     dev_len += virtio_bus_get_vdev_config_len(&dev->bus);                      // (5) 0.05353
/*30 */     bus->dev_offs += dev_len;                                                  // (15) 0.02784
/*34 */     dev->host_features = virtio_bus_get_vdev_features(&dev->bus,               // (6) 0.05353
/*36 */                                                       dev->host_features);     // (0) 0.1263
/*38 */     s390_virtio_device_sync(dev);                                              // (13) 0.03212
/*40 */     s390_virtio_reset_idx(dev);                                                // (10) 0.03426
/*42 */     if (dev->qdev.hotplugged) {                                                // (14) 0.03212
/*44 */         S390CPU *cpu = s390_cpu_addr2state(0);                                 // (7) 0.05139
/*46 */         s390_virtio_irq(cpu, VIRTIO_PARAM_DEV_ADD, dev->dev_offs);             // (1) 0.07495
/*48 */     }                                                                          // (20) 0.008565
/*52 */     return 0;                                                                  // (19) 0.01285
/*54 */ }                                                                              // (22) 0.002141
