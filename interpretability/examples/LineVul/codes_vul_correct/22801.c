// commit message qemu@bb44619b06 (target=1, prob=0.5505701, correct=True): blockdev: Keep a copy of DriveInfo.serial
/*0   */ DriveInfo *drive_init(QemuOpts *opts, BlockInterfaceType block_default_type)              // (1) 0.05312
/*2   */ {                                                                                         // (32) 0.001846
/*4   */     const char *buf;                                                                      // (26) 0.01455
/*6   */     const char *file = NULL;                                                              // (20) 0.01804
/*8   */     const char *serial;                                                                   // (28) 0.01424
/*10  */     const char *mediastr = "";                                                            // (15) 0.02132
/*12  */     BlockInterfaceType type;                                                              // (24) 0.01465
/*14  */     enum { MEDIA_DISK, MEDIA_CDROM } media;                                               // (9) 0.03561
/*16  */     int bus_id, unit_id;                                                                  // (16) 0.02131
/*18  */     int cyls, heads, secs, translation;                                                   // (12) 0.0261
/*20  */     BlockDriver *drv = NULL;                                                              // (17) 0.02092
/*22  */     int max_devs;                                                                         // (23) 0.01605
/*24  */     int index;                                                                            // (31) 0.01065
/*26  */     int ro = 0;                                                                           // (27) 0.01434
/*28  */     int bdrv_flags = 0;                                                                   // (14) 0.02149
/*30  */     int on_read_error, on_write_error;                                                    // (10) 0.03311
/*32  */     const char *devaddr;                                                                  // (22) 0.01658
/*34  */     DriveInfo *dinfo;                                                                     // (21) 0.01728
/*36  */     BlockIOLimit io_limits;                                                               // (13) 0.02195
/*38  */     int snapshot = 0;                                                                     // (25) 0.0146
/*40  */     bool copy_on_read;                                                                    // (18) 0.02014
/*42  */     int ret;                                                                              // (29) 0.01333
/*44  */     Error *error = NULL;                                                                  // (0) 0.07435
/*48  */     translation = BIOS_ATA_TRANSLATION_AUTO;                                              // (11) 0.03272
/*50  */     media = MEDIA_DISK;                                                                   // (19) 0.01963
/*54  */     /* extract parameters */                                                              // (30) 0.01288
/*56  */     bus_id  = qemu_opt_get_number(opts, "bus", 0);                                        // (2) 0.04624
/*58  */     unit_id = qemu_opt_get_number(opts, "unit", -1);                                      // (5) 0.04588
/*60  */     index   = qemu_opt_get_number(opts, "index", -1);                                     // (4) 0.04598
/*64  */     cyls  = qemu_opt_get_number(opts, "cyls", 0);                                         // (3) 0.04607
/*66  */     heads = qemu_opt_get_number(opts, "heads", 0);                                        // (8) 0.04067
/*68  */     secs  = qemu_opt_get_number(opts, "secs", 0);                                         // (6) 0.04586
/*72  */     snapshot = qemu_opt_get_bool(opts, "snapshot", 0);                                    // (7) 0.04264
/*74  */     ro = qemu_opt_get_bool(opts, "readonly", 0);                                          // 0.0
/*76  */     copy_on_read = qemu_opt_get_bool(opts, "copy-on-read", false);                        // 0.0
/*80  */     file = qemu_opt_get(opts, "file");                                                    // 0.0
/*82  */     serial = qemu_opt_get(opts, "serial");                                                // 0.0
/*86  */     if ((buf = qemu_opt_get(opts, "if")) != NULL) {                                       // 0.0
/*88  */         for (type = 0; type < IF_COUNT && strcmp(buf, if_name[type]); type++)             // 0.0
/*90  */             ;                                                                             // 0.0
/*92  */         if (type == IF_COUNT) {                                                           // 0.0
/*94  */             error_report("unsupported bus type '%s'", buf);                               // 0.0
/*96  */             return NULL;                                                                  // 0.0
/*98  */ 	}                                                                                        // 0.0
/*100 */     } else {                                                                              // 0.0
/*102 */         type = block_default_type;                                                        // 0.0
/*104 */     }                                                                                     // 0.0
/*108 */     max_devs = if_max_devs[type];                                                         // 0.0
/*112 */     if (cyls || heads || secs) {                                                          // 0.0
/*114 */         if (cyls < 1) {                                                                   // 0.0
/*116 */             error_report("invalid physical cyls number");                                 // 0.0
/*118 */ 	    return NULL;                                                                         // 0.0
/*120 */ 	}                                                                                        // 0.0
/*122 */         if (heads < 1) {                                                                  // 0.0
/*124 */             error_report("invalid physical heads number");                                // 0.0
/*126 */ 	    return NULL;                                                                         // 0.0
/*128 */ 	}                                                                                        // 0.0
/*130 */         if (secs < 1) {                                                                   // 0.0
/*132 */             error_report("invalid physical secs number");                                 // 0.0
/*134 */ 	    return NULL;                                                                         // 0.0
/*136 */ 	}                                                                                        // 0.0
/*138 */     }                                                                                     // 0.0
/*142 */     if ((buf = qemu_opt_get(opts, "trans")) != NULL) {                                    // 0.0
/*144 */         if (!cyls) {                                                                      // 0.0
/*146 */             error_report("'%s' trans must be used with cyls, heads and secs",             // 0.0
/*148 */                          buf);                                                            // 0.0
/*150 */             return NULL;                                                                  // 0.0
/*152 */         }                                                                                 // 0.0
/*154 */         if (!strcmp(buf, "none"))                                                         // 0.0
/*156 */             translation = BIOS_ATA_TRANSLATION_NONE;                                      // 0.0
/*158 */         else if (!strcmp(buf, "lba"))                                                     // 0.0
/*160 */             translation = BIOS_ATA_TRANSLATION_LBA;                                       // 0.0
/*162 */         else if (!strcmp(buf, "auto"))                                                    // 0.0
/*164 */             translation = BIOS_ATA_TRANSLATION_AUTO;                                      // 0.0
/*166 */ 	else {                                                                                   // 0.0
/*168 */             error_report("'%s' invalid translation type", buf);                           // 0.0
/*170 */ 	    return NULL;                                                                         // 0.0
/*172 */ 	}                                                                                        // 0.0
/*174 */     }                                                                                     // 0.0
/*178 */     if ((buf = qemu_opt_get(opts, "media")) != NULL) {                                    // 0.0
/*180 */         if (!strcmp(buf, "disk")) {                                                       // 0.0
/*182 */ 	    media = MEDIA_DISK;                                                                  // 0.0
/*184 */ 	} else if (!strcmp(buf, "cdrom")) {                                                      // 0.0
/*186 */             if (cyls || secs || heads) {                                                  // 0.0
/*188 */                 error_report("CHS can't be set with media=%s", buf);                      // 0.0
/*190 */ 	        return NULL;                                                                     // 0.0
/*192 */             }                                                                             // 0.0
/*194 */ 	    media = MEDIA_CDROM;                                                                 // 0.0
/*196 */ 	} else {                                                                                 // 0.0
/*198 */ 	    error_report("'%s' invalid media", buf);                                             // 0.0
/*200 */ 	    return NULL;                                                                         // 0.0
/*202 */ 	}                                                                                        // 0.0
/*204 */     }                                                                                     // 0.0
/*208 */     if ((buf = qemu_opt_get(opts, "discard")) != NULL) {                                  // 0.0
/*210 */         if (bdrv_parse_discard_flags(buf, &bdrv_flags) != 0) {                            // 0.0
/*212 */             error_report("invalid discard option");                                       // 0.0
/*214 */             return NULL;                                                                  // 0.0
/*216 */         }                                                                                 // 0.0
/*218 */     }                                                                                     // 0.0
/*222 */     bdrv_flags |= BDRV_O_CACHE_WB;                                                        // 0.0
/*224 */     if ((buf = qemu_opt_get(opts, "cache")) != NULL) {                                    // 0.0
/*226 */         if (bdrv_parse_cache_flags(buf, &bdrv_flags) != 0) {                              // 0.0
/*228 */             error_report("invalid cache option");                                         // 0.0
/*230 */             return NULL;                                                                  // 0.0
/*232 */         }                                                                                 // 0.0
/*234 */     }                                                                                     // 0.0
/*238 */ #ifdef CONFIG_LINUX_AIO                                                                   // 0.0
/*240 */     if ((buf = qemu_opt_get(opts, "aio")) != NULL) {                                      // 0.0
/*242 */         if (!strcmp(buf, "native")) {                                                     // 0.0
/*244 */             bdrv_flags |= BDRV_O_NATIVE_AIO;                                              // 0.0
/*246 */         } else if (!strcmp(buf, "threads")) {                                             // 0.0
/*248 */             /* this is the default */                                                     // 0.0
/*250 */         } else {                                                                          // 0.0
/*252 */            error_report("invalid aio option");                                            // 0.0
/*254 */            return NULL;                                                                   // 0.0
/*256 */         }                                                                                 // 0.0
/*258 */     }                                                                                     // 0.0
/*260 */ #endif                                                                                    // 0.0
/*264 */     if ((buf = qemu_opt_get(opts, "format")) != NULL) {                                   // 0.0
/*266 */         if (is_help_option(buf)) {                                                        // 0.0
/*268 */             error_printf("Supported formats:");                                           // 0.0
/*270 */             bdrv_iterate_format(bdrv_format_print, NULL);                                 // 0.0
/*272 */             error_printf("\n");                                                           // 0.0
/*274 */             return NULL;                                                                  // 0.0
/*276 */         }                                                                                 // 0.0
/*278 */         drv = bdrv_find_whitelisted_format(buf);                                          // 0.0
/*280 */         if (!drv) {                                                                       // 0.0
/*282 */             error_report("'%s' invalid format", buf);                                     // 0.0
/*284 */             return NULL;                                                                  // 0.0
/*286 */         }                                                                                 // 0.0
/*288 */     }                                                                                     // 0.0
/*292 */     /* disk I/O throttling */                                                             // 0.0
/*294 */     io_limits.bps[BLOCK_IO_LIMIT_TOTAL]  =                                                // 0.0
/*296 */                            qemu_opt_get_number(opts, "bps", 0);                           // 0.0
/*298 */     io_limits.bps[BLOCK_IO_LIMIT_READ]   =                                                // 0.0
/*300 */                            qemu_opt_get_number(opts, "bps_rd", 0);                        // 0.0
/*302 */     io_limits.bps[BLOCK_IO_LIMIT_WRITE]  =                                                // 0.0
/*304 */                            qemu_opt_get_number(opts, "bps_wr", 0);                        // 0.0
/*306 */     io_limits.iops[BLOCK_IO_LIMIT_TOTAL] =                                                // 0.0
/*308 */                            qemu_opt_get_number(opts, "iops", 0);                          // 0.0
/*310 */     io_limits.iops[BLOCK_IO_LIMIT_READ]  =                                                // 0.0
/*312 */                            qemu_opt_get_number(opts, "iops_rd", 0);                       // 0.0
/*314 */     io_limits.iops[BLOCK_IO_LIMIT_WRITE] =                                                // 0.0
/*316 */                            qemu_opt_get_number(opts, "iops_wr", 0);                       // 0.0
/*320 */     if (!do_check_io_limits(&io_limits, &error)) {                                        // 0.0
/*322 */         error_report("%s", error_get_pretty(error));                                      // 0.0
/*324 */         error_free(error);                                                                // 0.0
/*326 */         return NULL;                                                                      // 0.0
/*328 */     }                                                                                     // 0.0
/*332 */     if (qemu_opt_get(opts, "boot") != NULL) {                                             // 0.0
/*334 */         fprintf(stderr, "qemu-kvm: boot=on|off is deprecated and will be "                // 0.0
/*336 */                 "ignored. Future versions will reject this parameter. Please "            // 0.0
/*338 */                 "update your scripts.\n");                                                // 0.0
/*340 */     }                                                                                     // 0.0
/*344 */     on_write_error = BLOCKDEV_ON_ERROR_ENOSPC;                                            // 0.0
/*346 */     if ((buf = qemu_opt_get(opts, "werror")) != NULL) {                                   // 0.0
/*348 */         if (type != IF_IDE && type != IF_SCSI && type != IF_VIRTIO && type != IF_NONE) {  // 0.0
/*350 */             error_report("werror is not supported by this bus type");                     // 0.0
/*352 */             return NULL;                                                                  // 0.0
/*354 */         }                                                                                 // 0.0
/*358 */         on_write_error = parse_block_error_action(buf, 0);                                // 0.0
/*360 */         if (on_write_error < 0) {                                                         // 0.0
/*362 */             return NULL;                                                                  // 0.0
/*364 */         }                                                                                 // 0.0
/*366 */     }                                                                                     // 0.0
/*370 */     on_read_error = BLOCKDEV_ON_ERROR_REPORT;                                             // 0.0
/*372 */     if ((buf = qemu_opt_get(opts, "rerror")) != NULL) {                                   // 0.0
/*374 */         if (type != IF_IDE && type != IF_VIRTIO && type != IF_SCSI && type != IF_NONE) {  // 0.0
/*376 */             error_report("rerror is not supported by this bus type");                     // 0.0
/*378 */             return NULL;                                                                  // 0.0
/*380 */         }                                                                                 // 0.0
/*384 */         on_read_error = parse_block_error_action(buf, 1);                                 // 0.0
/*386 */         if (on_read_error < 0) {                                                          // 0.0
/*388 */             return NULL;                                                                  // 0.0
/*390 */         }                                                                                 // 0.0
/*392 */     }                                                                                     // 0.0
/*396 */     if ((devaddr = qemu_opt_get(opts, "addr")) != NULL) {                                 // 0.0
/*398 */         if (type != IF_VIRTIO) {                                                          // 0.0
/*400 */             error_report("addr is not supported by this bus type");                       // 0.0
/*402 */             return NULL;                                                                  // 0.0
/*404 */         }                                                                                 // 0.0
/*406 */     }                                                                                     // 0.0
/*410 */     /* compute bus and unit according index */                                            // 0.0
/*414 */     if (index != -1) {                                                                    // 0.0
/*416 */         if (bus_id != 0 || unit_id != -1) {                                               // 0.0
/*418 */             error_report("index cannot be used with bus and unit");                       // 0.0
/*420 */             return NULL;                                                                  // 0.0
/*422 */         }                                                                                 // 0.0
/*424 */         bus_id = drive_index_to_bus_id(type, index);                                      // 0.0
/*426 */         unit_id = drive_index_to_unit_id(type, index);                                    // 0.0
/*428 */     }                                                                                     // 0.0
/*432 */     /* if user doesn't specify a unit_id,                                                 // 0.0
/*434 */      * try to find the first free                                                         // 0.0
/*436 */      */                                                                                   // 0.0
/*440 */     if (unit_id == -1) {                                                                  // 0.0
/*442 */        unit_id = 0;                                                                       // 0.0
/*444 */        while (drive_get(type, bus_id, unit_id) != NULL) {                                 // 0.0
/*446 */            unit_id++;                                                                     // 0.0
/*448 */            if (max_devs && unit_id >= max_devs) {                                         // 0.0
/*450 */                unit_id -= max_devs;                                                       // 0.0
/*452 */                bus_id++;                                                                  // 0.0
/*454 */            }                                                                              // 0.0
/*456 */        }                                                                                  // 0.0
/*458 */     }                                                                                     // 0.0
/*462 */     /* check unit id */                                                                   // 0.0
/*466 */     if (max_devs && unit_id >= max_devs) {                                                // 0.0
/*468 */         error_report("unit %d too big (max is %d)",                                       // 0.0
/*470 */                      unit_id, max_devs - 1);                                              // 0.0
/*472 */         return NULL;                                                                      // 0.0
/*474 */     }                                                                                     // 0.0
/*478 */     /*                                                                                    // 0.0
/*480 */      * catch multiple definitions                                                         // 0.0
/*482 */      */                                                                                   // 0.0
/*486 */     if (drive_get(type, bus_id, unit_id) != NULL) {                                       // 0.0
/*488 */         error_report("drive with bus=%d, unit=%d (index=%d) exists",                      // 0.0
/*490 */                      bus_id, unit_id, index);                                             // 0.0
/*492 */         return NULL;                                                                      // 0.0
/*494 */     }                                                                                     // 0.0
/*498 */     /* init */                                                                            // 0.0
/*502 */     dinfo = g_malloc0(sizeof(*dinfo));                                                    // 0.0
/*504 */     if ((buf = qemu_opts_id(opts)) != NULL) {                                             // 0.0
/*506 */         dinfo->id = g_strdup(buf);                                                        // 0.0
/*508 */     } else {                                                                              // 0.0
/*510 */         /* no id supplied -> create one */                                                // 0.0
/*512 */         dinfo->id = g_malloc0(32);                                                        // 0.0
/*514 */         if (type == IF_IDE || type == IF_SCSI)                                            // 0.0
/*516 */             mediastr = (media == MEDIA_CDROM) ? "-cd" : "-hd";                            // 0.0
/*518 */         if (max_devs)                                                                     // 0.0
/*520 */             snprintf(dinfo->id, 32, "%s%i%s%i",                                           // 0.0
/*522 */                      if_name[type], bus_id, mediastr, unit_id);                           // 0.0
/*524 */         else                                                                              // 0.0
/*526 */             snprintf(dinfo->id, 32, "%s%s%i",                                             // 0.0
/*528 */                      if_name[type], mediastr, unit_id);                                   // 0.0
/*530 */     }                                                                                     // 0.0
/*532 */     dinfo->bdrv = bdrv_new(dinfo->id);                                                    // 0.0
/*534 */     dinfo->bdrv->open_flags = snapshot ? BDRV_O_SNAPSHOT : 0;                             // 0.0
/*536 */     dinfo->bdrv->read_only = ro;                                                          // 0.0
/*538 */     dinfo->devaddr = devaddr;                                                             // 0.0
/*540 */     dinfo->type = type;                                                                   // 0.0
/*542 */     dinfo->bus = bus_id;                                                                  // 0.0
/*544 */     dinfo->unit = unit_id;                                                                // 0.0
/*546 */     dinfo->cyls = cyls;                                                                   // 0.0
/*548 */     dinfo->heads = heads;                                                                 // 0.0
/*550 */     dinfo->secs = secs;                                                                   // 0.0
/*552 */     dinfo->trans = translation;                                                           // 0.0
/*554 */     dinfo->opts = opts;                                                                   // 0.0
/*556 */     dinfo->refcount = 1;                                                                  // 0.0
/*558 */     dinfo->serial = serial;                                                               // 0.0
/*560 */     QTAILQ_INSERT_TAIL(&drives, dinfo, next);                                             // 0.0
/*564 */     bdrv_set_on_error(dinfo->bdrv, on_read_error, on_write_error);                        // 0.0
/*568 */     /* disk I/O throttling */                                                             // 0.0
/*570 */     bdrv_set_io_limits(dinfo->bdrv, &io_limits);                                          // 0.0
/*574 */     switch(type) {                                                                        // 0.0
/*576 */     case IF_IDE:                                                                          // 0.0
/*578 */     case IF_SCSI:                                                                         // 0.0
/*580 */     case IF_XEN:                                                                          // 0.0
/*582 */     case IF_NONE:                                                                         // 0.0
/*584 */         dinfo->media_cd = media == MEDIA_CDROM;                                           // 0.0
/*586 */         break;                                                                            // 0.0
/*588 */     case IF_SD:                                                                           // 0.0
/*590 */     case IF_FLOPPY:                                                                       // 0.0
/*592 */     case IF_PFLASH:                                                                       // 0.0
/*594 */     case IF_MTD:                                                                          // 0.0
/*596 */         break;                                                                            // 0.0
/*598 */     case IF_VIRTIO:                                                                       // 0.0
/*600 */         /* add virtio block device */                                                     // 0.0
/*602 */         opts = qemu_opts_create_nofail(qemu_find_opts("device"));                         // 0.0
/*604 */         if (arch_type == QEMU_ARCH_S390X) {                                               // 0.0
/*606 */             qemu_opt_set(opts, "driver", "virtio-blk-s390");                              // 0.0
/*608 */         } else {                                                                          // 0.0
/*610 */             qemu_opt_set(opts, "driver", "virtio-blk-pci");                               // 0.0
/*612 */         }                                                                                 // 0.0
/*614 */         qemu_opt_set(opts, "drive", dinfo->id);                                           // 0.0
/*616 */         if (devaddr)                                                                      // 0.0
/*618 */             qemu_opt_set(opts, "addr", devaddr);                                          // 0.0
/*620 */         break;                                                                            // 0.0
/*622 */     default:                                                                              // 0.0
/*624 */         abort();                                                                          // 0.0
/*626 */     }                                                                                     // 0.0
/*628 */     if (!file || !*file) {                                                                // 0.0
/*630 */         return dinfo;                                                                     // 0.0
/*632 */     }                                                                                     // 0.0
/*634 */     if (snapshot) {                                                                       // 0.0
/*636 */         /* always use cache=unsafe with snapshot */                                       // 0.0
/*638 */         bdrv_flags &= ~BDRV_O_CACHE_MASK;                                                 // 0.0
/*640 */         bdrv_flags |= (BDRV_O_SNAPSHOT|BDRV_O_CACHE_WB|BDRV_O_NO_FLUSH);                  // 0.0
/*642 */     }                                                                                     // 0.0
/*646 */     if (copy_on_read) {                                                                   // 0.0
/*648 */         bdrv_flags |= BDRV_O_COPY_ON_READ;                                                // 0.0
/*650 */     }                                                                                     // 0.0
/*654 */     if (runstate_check(RUN_STATE_INMIGRATE)) {                                            // 0.0
/*656 */         bdrv_flags |= BDRV_O_INCOMING;                                                    // 0.0
/*658 */     }                                                                                     // 0.0
/*662 */     if (media == MEDIA_CDROM) {                                                           // 0.0
/*664 */         /* CDROM is fine for any interface, don't check.  */                              // 0.0
/*666 */         ro = 1;                                                                           // 0.0
/*668 */     } else if (ro == 1) {                                                                 // 0.0
/*670 */         if (type != IF_SCSI && type != IF_VIRTIO && type != IF_FLOPPY &&                  // 0.0
/*672 */             type != IF_NONE && type != IF_PFLASH) {                                       // 0.0
/*674 */             error_report("readonly not supported by this bus type");                      // 0.0
/*676 */             goto err;                                                                     // 0.0
/*678 */         }                                                                                 // 0.0
/*680 */     }                                                                                     // 0.0
/*684 */     bdrv_flags |= ro ? 0 : BDRV_O_RDWR;                                                   // 0.0
/*688 */     if (ro && copy_on_read) {                                                             // 0.0
/*690 */         error_report("warning: disabling copy_on_read on readonly drive");                // 0.0
/*692 */     }                                                                                     // 0.0
/*696 */     ret = bdrv_open(dinfo->bdrv, file, NULL, bdrv_flags, drv);                            // 0.0
/*698 */     if (ret < 0) {                                                                        // 0.0
/*700 */         if (ret == -EMEDIUMTYPE) {                                                        // 0.0
/*702 */             error_report("could not open disk image %s: not in %s format",                // 0.0
/*704 */                          file, drv->format_name);                                         // 0.0
/*706 */         } else {                                                                          // 0.0
/*708 */             error_report("could not open disk image %s: %s",                              // 0.0
/*710 */                          file, strerror(-ret));                                           // 0.0
/*712 */         }                                                                                 // 0.0
/*714 */         goto err;                                                                         // 0.0
/*716 */     }                                                                                     // 0.0
/*720 */     if (bdrv_key_required(dinfo->bdrv))                                                   // 0.0
/*722 */         autostart = 0;                                                                    // 0.0
/*724 */     return dinfo;                                                                         // 0.0
/*728 */ err:                                                                                      // 0.0
/*730 */     bdrv_delete(dinfo->bdrv);                                                             // 0.0
/*732 */     g_free(dinfo->id);                                                                    // 0.0
/*734 */     QTAILQ_REMOVE(&drives, dinfo, next);                                                  // 0.0
/*736 */     g_free(dinfo);                                                                        // 0.0
/*738 */     return NULL;                                                                          // 0.0
/*740 */ }                                                                                         // 0.0
