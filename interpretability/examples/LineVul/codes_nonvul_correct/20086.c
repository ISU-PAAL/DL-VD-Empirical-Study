// commit message qemu@a818a4b69d (target=0, prob=0.27189538, correct=True): scsi-bus: Convert DeviceClass init to realize
/*0   */ static int scsi_initfn(SCSIDevice *dev)                                         // (12) 0.03125
/*2   */ {                                                                               // (29) 0.001953
/*4   */     SCSIDiskState *s = DO_UPCAST(SCSIDiskState, qdev, dev);                     // (2) 0.05469
/*6   */     Error *err = NULL;                                                          // (22) 0.01758
/*10  */     if (!s->qdev.conf.bs) {                                                     // (14) 0.0293
/*12  */         error_report("drive property not set");                                 // (13) 0.03125
/*14  */         return -1;                                                              // (18) 0.02148
/*16  */     }                                                                           // (24) 0.007812
/*20  */     if (!(s->features & (1 << SCSI_DISK_F_REMOVABLE)) &&                        // (4) 0.05078
/*22  */         !bdrv_is_inserted(s->qdev.conf.bs)) {                                   // (3) 0.05273
/*24  */         error_report("Device needs media, but drive is empty");                 // (9) 0.03906
/*26  */         return -1;                                                              // (19) 0.02148
/*28  */     }                                                                           // (25) 0.007812
/*32  */     blkconf_serial(&s->qdev.conf, &s->serial);                                  // (8) 0.04102
/*34  */     if (dev->type == TYPE_DISK) {                                               // (15) 0.0293
/*36  */         blkconf_geometry(&dev->conf, NULL, 65535, 255, 255, &err);              // (1) 0.05859
/*38  */         if (err) {                                                              // (17) 0.02344
/*40  */             error_report("%s", error_get_pretty(err));                          // (5) 0.05078
/*42  */             error_free(err);                                                    // (11) 0.0332
/*44  */             return -1;                                                          // (16) 0.0293
/*46  */         }                                                                       // (23) 0.01562
/*48  */     }                                                                           // (26) 0.007812
/*52  */     if (s->qdev.conf.discard_granularity == -1) {                               // (7) 0.04297
/*54  */         s->qdev.conf.discard_granularity =                                      // (10) 0.03906
/*56  */             MAX(s->qdev.conf.logical_block_size, DEFAULT_DISCARD_GRANULARITY);  // (0) 0.07617
/*58  */     }                                                                           // (27) 0.007812
/*62  */     if (!s->version) {                                                          // (21) 0.01953
/*64  */         s->version = g_strdup(qemu_get_version());                              // (6) 0.04883
/*66  */     }                                                                           // (28) 0.007812
/*68  */     if (!s->vendor) {                                                           // (20) 0.02148
/*70  */         s->vendor = g_strdup("QEMU");                                           // 0.0
/*72  */     }                                                                           // 0.0
/*76  */     if (bdrv_is_sg(s->qdev.conf.bs)) {                                          // 0.0
/*78  */         error_report("unwanted /dev/sg*");                                      // 0.0
/*80  */         return -1;                                                              // 0.0
/*82  */     }                                                                           // 0.0
/*86  */     if ((s->features & (1 << SCSI_DISK_F_REMOVABLE)) &&                         // 0.0
/*88  */             !(s->features & (1 << SCSI_DISK_F_NO_REMOVABLE_DEVOPS))) {          // 0.0
/*90  */         bdrv_set_dev_ops(s->qdev.conf.bs, &scsi_disk_removable_block_ops, s);   // 0.0
/*92  */     } else {                                                                    // 0.0
/*94  */         bdrv_set_dev_ops(s->qdev.conf.bs, &scsi_disk_block_ops, s);             // 0.0
/*96  */     }                                                                           // 0.0
/*98  */     bdrv_set_guest_block_size(s->qdev.conf.bs, s->qdev.blocksize);              // 0.0
/*102 */     bdrv_iostatus_enable(s->qdev.conf.bs);                                      // 0.0
/*104 */     add_boot_device_path(s->qdev.conf.bootindex, &dev->qdev, NULL);             // 0.0
/*106 */     return 0;                                                                   // 0.0
/*108 */ }                                                                               // 0.0
