// commit message qemu@d3d250bddb (target=1, prob=0.19481736, correct=False): scsi: fix searching for an empty id
/*0  */ int scsi_bus_legacy_handle_cmdline(SCSIBus *bus)                              // (4) 0.07317
/*2  */ {                                                                             // (18) 0.003484
/*4  */     Location loc;                                                             // (15) 0.02091
/*6  */     DriveInfo *dinfo;                                                         // (11) 0.03136
/*8  */     int res = 0, unit;                                                        // (10) 0.03484
/*12 */     loc_push_none(&loc);                                                      // (9) 0.03833
/*14 */     for (unit = 0; unit < bus->info->max_target; unit++) {                    // (3) 0.07666
/*16 */         dinfo = drive_get(IF_SCSI, bus->busnr, unit);                         // (1) 0.09059
/*18 */         if (dinfo == NULL) {                                                  // (6) 0.05226
/*20 */             continue;                                                         // (7) 0.0453
/*22 */         }                                                                     // (13) 0.02787
/*24 */         qemu_opts_loc_restore(dinfo->opts);                                   // (2) 0.08711
/*26 */         if (!scsi_bus_legacy_add_drive(bus, dinfo->bdrv, unit, false, -1)) {  // (0) 0.1324
/*28 */             res = -1;                                                         // (5) 0.05575
/*30 */             break;                                                            // (8) 0.0453
/*32 */         }                                                                     // (14) 0.02787
/*34 */     }                                                                         // (17) 0.01394
/*36 */     loc_pop(&loc);                                                            // (12) 0.03136
/*38 */     return res;                                                               // (16) 0.02091
/*40 */ }                                                                             // (19) 0.003484
