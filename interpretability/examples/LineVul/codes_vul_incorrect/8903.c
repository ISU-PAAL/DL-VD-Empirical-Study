// commit message qemu@5b456438f5 (target=1, prob=0.4317768, correct=False): virtio-rng: Fix crash with non-default backend
/*0  */ static int s390_virtio_rng_init(VirtIOS390Device *s390_dev)                  // (4) 0.09328
/*2  */ {                                                                            // (11) 0.003731
/*4  */     VirtIORNGS390 *dev = VIRTIO_RNG_S390(s390_dev);                          // (3) 0.09701
/*6  */     DeviceState *vdev = DEVICE(&dev->vdev);                                  // (6) 0.06343
/*10 */     qdev_set_parent_bus(vdev, BUS(&s390_dev->bus));                          // (5) 0.08955
/*12 */     if (qdev_init(vdev) < 0) {                                               // (7) 0.06343
/*14 */         return -1;                                                           // (9) 0.04104
/*16 */     }                                                                        // (10) 0.01493
/*20 */     object_property_set_link(OBJECT(dev),                                    // (8) 0.0597
/*22 */                              OBJECT(dev->vdev.conf.default_backend), "rng",  // (0) 0.1754
/*24 */                              NULL);                                          // (1) 0.1119
/*28 */     return s390_virtio_device_init(s390_dev, VIRTIO_DEVICE(vdev));           // (2) 0.1082
/*30 */ }                                                                            // (12) 0.003731
