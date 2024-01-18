// commit message qemu@a818a4b69d (target=0, prob=0.12381548, correct=True): scsi-bus: Convert DeviceClass init to realize
/*0  */ static int scsi_qdev_exit(DeviceState *qdev)              // (2) 0.1416
/*2  */ {                                                         // (7) 0.00885
/*4  */     SCSIDevice *dev = SCSI_DEVICE(qdev);                  // (1) 0.177
/*8  */     if (dev->vmsentry) {                                  // (4) 0.1062
/*10 */         qemu_del_vm_change_state_handler(dev->vmsentry);  // (0) 0.2389
/*12 */     }                                                     // (6) 0.0354
/*14 */     scsi_device_destroy(dev);                             // (3) 0.1062
/*16 */     return 0;                                             // (5) 0.0531
/*18 */ }                                                         // (8) 0.00885
