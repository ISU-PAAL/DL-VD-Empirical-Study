// commit message qemu@db12451dec (target=1, prob=0.9870629, correct=True): Fix for crash after migration in virtio-rng on bi-endian targets
/*0  */ static void virtio_rng_class_init(ObjectClass *klass, void *data)  // (2) 0.1146
/*2  */ {                                                                  // (9) 0.005208
/*4  */     DeviceClass *dc = DEVICE_CLASS(klass);                         // (6) 0.08333
/*6  */     VirtioDeviceClass *vdc = VIRTIO_DEVICE_CLASS(klass);           // (0) 0.1198
/*10 */     dc->props = virtio_rng_properties;                             // (7) 0.08333
/*12 */     set_bit(DEVICE_CATEGORY_MISC, dc->categories);                 // (1) 0.1198
/*14 */     vdc->realize = virtio_rng_device_realize;                      // (4) 0.1042
/*16 */     vdc->unrealize = virtio_rng_device_unrealize;                  // (3) 0.1146
/*18 */     vdc->get_features = get_features;                              // (8) 0.07292
/*20 */     vdc->load = virtio_rng_load_device;                            // (5) 0.09375
/*22 */ }                                                                  // (10) 0.005208
