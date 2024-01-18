// commit message qemu@0c0eb30260 (target=1, prob=0.96437544, correct=True): tests: fix vhost-user-test leaks
/*0  */ static void init_virtio_dev(TestServer *s)              // (10) 0.05072
/*2  */ {                                                       // (16) 0.003623
/*4  */     QPCIBus *bus;                                       // (14) 0.03623
/*6  */     QVirtioPCIDevice *dev;                              // (9) 0.05072
/*8  */     uint32_t features;                                  // (15) 0.03261
/*12 */     bus = qpci_init_pc(NULL);                           // (8) 0.05435
/*14 */     g_assert_nonnull(bus);                              // (12) 0.04348
/*18 */     dev = qvirtio_pci_device_find(bus, VIRTIO_ID_NET);  // (0) 0.0942
/*20 */     g_assert_nonnull(dev);                              // (13) 0.04348
/*24 */     qvirtio_pci_device_enable(dev);                     // (6) 0.05797
/*26 */     qvirtio_reset(&dev->vdev);                          // (11) 0.05072
/*28 */     qvirtio_set_acknowledge(&dev->vdev);                // (1) 0.06522
/*30 */     qvirtio_set_driver(&dev->vdev);                     // (7) 0.05797
/*34 */     features = qvirtio_get_features(&dev->vdev);        // (2) 0.06522
/*36 */     features = features & VIRTIO_NET_F_MAC;             // (5) 0.06159
/*38 */     qvirtio_set_features(&dev->vdev, features);         // (3) 0.06522
/*42 */     qvirtio_set_driver_ok(&dev->vdev);                  // (4) 0.06522
/*44 */ }                                                       // (17) 0.003623
