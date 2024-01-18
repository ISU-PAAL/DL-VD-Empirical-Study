// commit message qemu@4be746345f (target=0, prob=0.08963938, correct=True): hw: Convert from BlockDriverState to BlockBackend, mostly
/*0  */ static void scsi_disk_realize(SCSIDevice *dev, Error **errp)  // (0) 0.1004
/*2  */ {                                                             // (15) 0.004367
/*4  */     DriveInfo *dinfo;                                         // (10) 0.0393
/*6  */     Error *local_err = NULL;                                  // (9) 0.04803
/*10 */     if (!dev->conf.bs) {                                      // (8) 0.0524
/*12 */         scsi_realize(dev, &local_err);                        // (3) 0.08734
/*14 */         assert(local_err);                                    // (7) 0.05677
/*16 */         error_propagate(errp, local_err);                     // (5) 0.08297
/*18 */         return;                                               // (11) 0.0393
/*20 */     }                                                         // (13) 0.01747
/*24 */     dinfo = drive_get_by_blockdev(dev->conf.bs);              // (1) 0.0917
/*26 */     if (dinfo->media_cd) {                                    // (6) 0.05677
/*28 */         scsi_cd_realize(dev, errp);                           // (4) 0.08734
/*30 */     } else {                                                  // (12) 0.0262
/*32 */         scsi_hd_realize(dev, errp);                           // (2) 0.08734
/*34 */     }                                                         // (14) 0.01747
/*36 */ }                                                             // (16) 0.004367
