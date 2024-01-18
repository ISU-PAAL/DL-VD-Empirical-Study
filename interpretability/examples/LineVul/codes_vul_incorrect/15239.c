// commit message qemu@b7c8c35f0a (target=1, prob=0.22151285, correct=False): scsi: fix memory leak
/*0  */ static char *scsibus_get_dev_path(DeviceState *dev)                            // (5) 0.07087
/*2  */ {                                                                              // (12) 0.003937
/*4  */     SCSIDevice *d = DO_UPCAST(SCSIDevice, qdev, dev);                          // (3) 0.1102
/*6  */     DeviceState *hba = dev->parent_bus->parent;                                // (6) 0.06693
/*8  */     char *id = NULL;                                                           // (7) 0.03543
/*12 */     if (hba && hba->parent_bus && hba->parent_bus->info->get_dev_path) {       // (2) 0.122
/*14 */         id = hba->parent_bus->info->get_dev_path(hba);                         // (4) 0.1063
/*16 */     }                                                                          // (10) 0.01575
/*18 */     if (id) {                                                                  // (8) 0.0315
/*20 */         return g_strdup_printf("%s/%d:%d:%d", id, d->channel, d->id, d->lun);  // (0) 0.1693
/*22 */     } else {                                                                   // (9) 0.02362
/*24 */         return g_strdup_printf("%d:%d:%d", d->channel, d->id, d->lun);         // (1) 0.1496
/*26 */     }                                                                          // (11) 0.01575
/*28 */ }                                                                              // (13) 0.003937
