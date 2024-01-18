// commit message qemu@2cbe2de545 (target=1, prob=0.99883443, correct=True): virtio-scsi: Unset hotplug handler when unrealize
/*0 */ static void virtio_scsi_device_unrealize(DeviceState *dev, Error **errp)  // (0) 0.4706
/*1 */ {                                                                         // (2) 0.01961
/*2 */     virtio_scsi_common_unrealize(dev, errp);                              // (1) 0.3922
/*3 */ }                                                                         // (3) 0.01961
