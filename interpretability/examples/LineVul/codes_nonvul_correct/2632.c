// commit message qemu@95b5edcd92 (target=0, prob=0.22602016, correct=True): blockdev: Store -drive option media in DriveInfo
/*0  */ int xen_config_dev_blk(DriveInfo *disk)                                        // (16) 0.03018
/*2  */ {                                                                              // (21) 0.002012
/*4  */     char fe[256], be[256];                                                     // (17) 0.02414
/*6  */     int vdev = 202 * 256 + 16 * disk->unit;                                    // (14) 0.03421
/*8  */     int cdrom = disk->bdrv->type == BDRV_TYPE_CDROM;                           // (8) 0.0503
/*10 */     const char *devtype = cdrom ? "cdrom" : "disk";                            // (12) 0.04024
/*12 */     const char *mode    = cdrom ? "r"     : "w";                               // (9) 0.0503
/*16 */     snprintf(disk->bdrv->device_name, sizeof(disk->bdrv->device_name),         // (5) 0.05634
/*18 */ 	     "xvd%c", 'a' + disk->unit);                                              // (13) 0.03823
/*20 */     xen_be_printf(NULL, 1, "config disk %d [%s]: %s\n",                        // (7) 0.05433
/*22 */                   disk->unit, disk->bdrv->device_name, disk->bdrv->filename);  // (0) 0.07847
/*24 */     xen_config_dev_dirs("vbd", "qdisk", vdev, fe, be, sizeof(fe));             // (3) 0.06036
/*28 */     /* frontend */                                                             // (19) 0.01408
/*30 */     xenstore_write_int(fe, "virtual-device",  vdev);                           // (11) 0.04225
/*32 */     xenstore_write_str(fe, "device-type",     devtype);                        // (10) 0.04829
/*36 */     /* backend */                                                              // (20) 0.01207
/*38 */     xenstore_write_str(be, "dev",             disk->bdrv->device_name);        // (1) 0.07445
/*40 */     xenstore_write_str(be, "type",            "file");                         // (4) 0.05835
/*42 */     xenstore_write_str(be, "params",          disk->bdrv->filename);           // (2) 0.06439
/*44 */     xenstore_write_str(be, "mode",            mode);                           // (6) 0.05634
/*48 */     /* common stuff */                                                         // (18) 0.01408
/*50 */     return xen_config_dev_all(fe, be);                                         // (15) 0.03219
/*52 */ }                                                                              // (22) 0.002012
