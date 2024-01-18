// commit message qemu@bd3be4dbbf (target=0, prob=0.024014456, correct=True): virtio-9p: move unrealize/realize after virtio_9p_transport definition
/*0  */ static void virtio_9p_device_unrealize(DeviceState *dev, Error **errp)  // (0) 0.186
/*2  */ {                                                                       // (6) 0.007752
/*4  */     VirtIODevice *vdev = VIRTIO_DEVICE(dev);                            // (2) 0.1628
/*6  */     V9fsVirtioState *v = VIRTIO_9P(dev);                                // (1) 0.1705
/*8  */     V9fsState *s = &v->state;                                           // (4) 0.1163
/*12 */     virtio_cleanup(vdev);                                               // (5) 0.09302
/*14 */     v9fs_device_unrealize_common(s, errp);                              // (3) 0.155
/*16 */ }                                                                       // (7) 0.007752
