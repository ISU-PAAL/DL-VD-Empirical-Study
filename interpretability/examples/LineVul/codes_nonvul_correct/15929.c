// commit message qemu@f8b6cc0070 (target=0, prob=0.33918765, correct=True): qdev: Decouple qdev_prop_drive from DriveInfo
/*0  */ static int ide_qdev_init(DeviceState *qdev, DeviceInfo *base)           // (6) 0.04237
/*2  */ {                                                                       // (32) 0.002119
/*4  */     IDEDevice *dev = DO_UPCAST(IDEDevice, qdev, qdev);                  // (4) 0.0572
/*6  */     IDEDeviceInfo *info = DO_UPCAST(IDEDeviceInfo, qdev, base);         // (3) 0.05932
/*8  */     IDEBus *bus = DO_UPCAST(IDEBus, qbus, qdev->parent_bus);            // (5) 0.0572
/*12 */     if (!dev->conf.dinfo) {                                             // (12) 0.02754
/*14 */         fprintf(stderr, "%s: no drive specified\n", qdev->info->name);  // (0) 0.06356
/*16 */         goto err;                                                       // (16) 0.02119
/*18 */     }                                                                   // (28) 0.008475
/*20 */     if (dev->unit == -1) {                                              // (13) 0.02754
/*22 */         dev->unit = bus->master ? 1 : 0;                                // (7) 0.04025
/*24 */     }                                                                   // (29) 0.008475
/*26 */     switch (dev->unit) {                                                // (17) 0.02119
/*28 */     case 0:                                                             // (25) 0.01271
/*30 */         if (bus->master) {                                              // (8) 0.02966
/*32 */             fprintf(stderr, "ide: tried to assign master twice\n");     // (1) 0.06144
/*34 */             goto err;                                                   // (9) 0.02966
/*36 */         }                                                               // (22) 0.01695
/*38 */         bus->master = dev;                                              // (14) 0.02754
/*40 */         break;                                                          // (20) 0.01907
/*42 */     case 1:                                                             // (26) 0.01271
/*44 */         if (bus->slave) {                                               // (10) 0.02966
/*46 */             fprintf(stderr, "ide: tried to assign slave twice\n");      // (2) 0.06144
/*48 */             goto err;                                                   // (11) 0.02966
/*50 */         }                                                               // (23) 0.01695
/*52 */         bus->slave = dev;                                               // (15) 0.02754
/*54 */         break;                                                          // (21) 0.01907
/*56 */     default:                                                            // (27) 0.01059
/*58 */         goto err;                                                       // (18) 0.02119
/*60 */     }                                                                   // (30) 0.008475
/*62 */     return info->init(dev);                                             // (19) 0.02119
/*66 */ err:                                                                    // (31) 0.004237
/*68 */     return -1;                                                          // (24) 0.01483
/*70 */ }                                                                       // (33) 0.002119
