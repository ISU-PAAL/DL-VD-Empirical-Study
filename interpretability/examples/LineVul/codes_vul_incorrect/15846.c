// commit message qemu@e3c9d76acc (target=1, prob=0.4399158, correct=False): virtio-scsi: switch exit callback to VirtioDeviceClass
/*0  */ static int virtio_scsi_device_exit(DeviceState *qdev)  // (3) 0.1552
/*2  */ {                                                      // (5) 0.008621
/*4  */     VirtIOSCSI *s = VIRTIO_SCSI(qdev);                 // (1) 0.181
/*6  */     VirtIOSCSICommon *vs = VIRTIO_SCSI_COMMON(qdev);   // (0) 0.2241
/*10 */     unregister_savevm(qdev, "virtio-scsi", s);         // (2) 0.181
/*12 */     return virtio_scsi_common_exit(vs);                // (4) 0.1379
/*14 */ }                                                      // (6) 0.008621
