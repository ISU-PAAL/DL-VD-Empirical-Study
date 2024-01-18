// commit message qemu@4be746345f (target=0, prob=0.013867729, correct=True): hw: Convert from BlockDriverState to BlockBackend, mostly
/*0  */ static void scsi_disk_reset(DeviceState *dev)                     // (5) 0.05907
/*2  */ {                                                                 // (13) 0.004219
/*4  */     SCSIDiskState *s = DO_UPCAST(SCSIDiskState, qdev.qdev, dev);  // (0) 0.1308
/*6  */     uint64_t nb_sectors;                                          // (7) 0.05485
/*10 */     scsi_device_purge_requests(&s->qdev, SENSE_CODE(RESET));      // (1) 0.1181
/*14 */     bdrv_get_geometry(s->qdev.conf.bs, &nb_sectors);              // (2) 0.1139
/*16 */     nb_sectors /= s->qdev.blocksize / 512;                        // (3) 0.08439
/*18 */     if (nb_sectors) {                                             // (10) 0.04641
/*20 */         nb_sectors--;                                             // (6) 0.05907
/*22 */     }                                                             // (12) 0.01688
/*24 */     s->qdev.max_lba = nb_sectors;                                 // (4) 0.08017
/*26 */     /* reset tray statuses */                                     // (11) 0.03797
/*28 */     s->tray_locked = 0;                                           // (8) 0.05063
/*30 */     s->tray_open = 0;                                             // (9) 0.05063
/*32 */ }                                                                 // (14) 0.004219
