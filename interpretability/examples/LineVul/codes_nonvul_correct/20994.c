// commit message qemu@ef546f1275 (target=0, prob=0.32865253, correct=True): virtio: add feature checking helpers
/*0  */ static void virtio_scsi_hotunplug(HotplugHandler *hotplug_dev, DeviceState *dev,  // (5) 0.07027
/*2  */                                   Error **errp)                                   // (2) 0.1027
/*4  */ {                                                                                 // (14) 0.002703
/*6  */     VirtIODevice *vdev = VIRTIO_DEVICE(hotplug_dev);                              // (7) 0.06486
/*8  */     VirtIOSCSI *s = VIRTIO_SCSI(vdev);                                            // (8) 0.05676
/*10 */     SCSIDevice *sd = SCSI_DEVICE(dev);                                            // (10) 0.05135
/*14 */     if ((vdev->guest_features >> VIRTIO_SCSI_F_HOTPLUG) & 1) {                    // (3) 0.08378
/*16 */         virtio_scsi_push_event(s, sd,                                             // (9) 0.05676
/*18 */                                VIRTIO_SCSI_T_TRANSPORT_RESET,                     // (0) 0.127
/*20 */                                VIRTIO_SCSI_EVT_RESET_REMOVED);                    // (1) 0.127
/*22 */     }                                                                             // (12) 0.01081
/*26 */     if (s->ctx) {                                                                 // (11) 0.02703
/*28 */         blk_op_unblock_all(sd->conf.blk, s->blocker);                             // (4) 0.07838
/*30 */     }                                                                             // (13) 0.01081
/*32 */     qdev_simple_device_unplug_cb(hotplug_dev, dev, errp);                         // (6) 0.06757
/*34 */ }                                                                                 // (15) 0.002703
