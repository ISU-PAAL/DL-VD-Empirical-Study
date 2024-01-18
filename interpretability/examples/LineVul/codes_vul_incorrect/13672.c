// commit message qemu@8cf07dcbe7 (target=1, prob=0.46312824, correct=False): Fix output of uninitialized strings
/*0   */ int drive_init(struct drive_opt *arg, int snapshot, void *opaque)                  // (5) 0.03906
/*2   */ {                                                                                  // (25) 0.001955
/*4   */     char buf[128];                                                                 // (21) 0.01562
/*6   */     char file[1024];                                                               // (22) 0.01562
/*8   */     char devname[128];                                                             // (17) 0.01758
/*10  */     char serial[21];                                                               // (20) 0.01562
/*12  */     const char *mediastr = "";                                                     // (12) 0.02344
/*14  */     BlockInterfaceType type;                                                       // (19) 0.01563
/*16  */     enum { MEDIA_DISK, MEDIA_CDROM } media;                                        // (6) 0.03906
/*18  */     int bus_id, unit_id;                                                           // (10) 0.02344
/*20  */     int cyls, heads, secs, translation;                                            // (8) 0.02734
/*22  */     BlockDriverState *bdrv;                                                        // (15) 0.02148
/*24  */     BlockDriver *drv = NULL;                                                       // (14) 0.02148
/*26  */     QEMUMachine *machine = opaque;                                                 // (11) 0.02344
/*28  */     int max_devs;                                                                  // (18) 0.01758
/*30  */     int index;                                                                     // (24) 0.01172
/*32  */     int cache;                                                                     // (23) 0.01172
/*34  */     int bdrv_flags, onerror;                                                       // (9) 0.02539
/*36  */     int drives_table_idx;                                                          // (13) 0.02148
/*38  */     char *str = arg->opt;                                                          // (16) 0.02148
/*40  */     static const char * const params[] = { "bus", "unit", "if", "index",           // (4) 0.04687
/*42  */                                            "cyls", "heads", "secs", "trans",       // (0) 0.1094
/*44  */                                            "media", "snapshot", "file",            // (2) 0.1016
/*46  */                                            "cache", "format", "serial", "werror",  // (1) 0.1074
/*48  */                                            NULL };                                 // (3) 0.08594
/*52  */     if (check_params(params, str) < 0) {                                           // (7) 0.0332
/*54  */          fprintf(stderr, "qemu: unknown parameter '%s' in '%s'\n",                 // 0.0
/*56  */                          buf, str);                                                // 0.0
/*58  */          return -1;                                                                // 0.0
/*60  */     }                                                                              // 0.0
/*64  */     file[0] = 0;                                                                   // 0.0
/*66  */     cyls = heads = secs = 0;                                                       // 0.0
/*68  */     bus_id = 0;                                                                    // 0.0
/*70  */     unit_id = -1;                                                                  // 0.0
/*72  */     translation = BIOS_ATA_TRANSLATION_AUTO;                                       // 0.0
/*74  */     index = -1;                                                                    // 0.0
/*76  */     cache = 3;                                                                     // 0.0
/*80  */     if (machine->use_scsi) {                                                       // 0.0
/*82  */         type = IF_SCSI;                                                            // 0.0
/*84  */         max_devs = MAX_SCSI_DEVS;                                                  // 0.0
/*86  */         pstrcpy(devname, sizeof(devname), "scsi");                                 // 0.0
/*88  */     } else {                                                                       // 0.0
/*90  */         type = IF_IDE;                                                             // 0.0
/*92  */         max_devs = MAX_IDE_DEVS;                                                   // 0.0
/*94  */         pstrcpy(devname, sizeof(devname), "ide");                                  // 0.0
/*96  */     }                                                                              // 0.0
/*98  */     media = MEDIA_DISK;                                                            // 0.0
/*102 */     /* extract parameters */                                                       // 0.0
/*106 */     if (get_param_value(buf, sizeof(buf), "bus", str)) {                           // 0.0
/*108 */         bus_id = strtol(buf, NULL, 0);                                             // 0.0
/*110 */ 	if (bus_id < 0) {                                                                 // 0.0
/*112 */ 	    fprintf(stderr, "qemu: '%s' invalid bus id\n", str);                          // 0.0
/*114 */ 	    return -1;                                                                    // 0.0
/*116 */ 	}                                                                                 // 0.0
/*118 */     }                                                                              // 0.0
/*122 */     if (get_param_value(buf, sizeof(buf), "unit", str)) {                          // 0.0
/*124 */         unit_id = strtol(buf, NULL, 0);                                            // 0.0
/*126 */ 	if (unit_id < 0) {                                                                // 0.0
/*128 */ 	    fprintf(stderr, "qemu: '%s' invalid unit id\n", str);                         // 0.0
/*130 */ 	    return -1;                                                                    // 0.0
/*132 */ 	}                                                                                 // 0.0
/*134 */     }                                                                              // 0.0
/*138 */     if (get_param_value(buf, sizeof(buf), "if", str)) {                            // 0.0
/*140 */         pstrcpy(devname, sizeof(devname), buf);                                    // 0.0
/*142 */         if (!strcmp(buf, "ide")) {                                                 // 0.0
/*144 */ 	    type = IF_IDE;                                                                // 0.0
/*146 */             max_devs = MAX_IDE_DEVS;                                               // 0.0
/*148 */         } else if (!strcmp(buf, "scsi")) {                                         // 0.0
/*150 */ 	    type = IF_SCSI;                                                               // 0.0
/*152 */             max_devs = MAX_SCSI_DEVS;                                              // 0.0
/*154 */         } else if (!strcmp(buf, "floppy")) {                                       // 0.0
/*156 */ 	    type = IF_FLOPPY;                                                             // 0.0
/*158 */             max_devs = 0;                                                          // 0.0
/*160 */         } else if (!strcmp(buf, "pflash")) {                                       // 0.0
/*162 */ 	    type = IF_PFLASH;                                                             // 0.0
/*164 */             max_devs = 0;                                                          // 0.0
/*166 */ 	} else if (!strcmp(buf, "mtd")) {                                                 // 0.0
/*168 */ 	    type = IF_MTD;                                                                // 0.0
/*170 */             max_devs = 0;                                                          // 0.0
/*172 */ 	} else if (!strcmp(buf, "sd")) {                                                  // 0.0
/*174 */ 	    type = IF_SD;                                                                 // 0.0
/*176 */             max_devs = 0;                                                          // 0.0
/*178 */         } else if (!strcmp(buf, "virtio")) {                                       // 0.0
/*180 */             type = IF_VIRTIO;                                                      // 0.0
/*182 */             max_devs = 0;                                                          // 0.0
/*184 */ 	} else if (!strcmp(buf, "xen")) {                                                 // 0.0
/*186 */ 	    type = IF_XEN;                                                                // 0.0
/*188 */             max_devs = 0;                                                          // 0.0
/*190 */ 	} else {                                                                          // 0.0
/*192 */             fprintf(stderr, "qemu: '%s' unsupported bus type '%s'\n", str, buf);   // 0.0
/*194 */             return -1;                                                             // 0.0
/*196 */ 	}                                                                                 // 0.0
/*198 */     }                                                                              // 0.0
/*202 */     if (get_param_value(buf, sizeof(buf), "index", str)) {                         // 0.0
/*204 */         index = strtol(buf, NULL, 0);                                              // 0.0
/*206 */ 	if (index < 0) {                                                                  // 0.0
/*208 */ 	    fprintf(stderr, "qemu: '%s' invalid index\n", str);                           // 0.0
/*210 */ 	    return -1;                                                                    // 0.0
/*212 */ 	}                                                                                 // 0.0
/*214 */     }                                                                              // 0.0
/*218 */     if (get_param_value(buf, sizeof(buf), "cyls", str)) {                          // 0.0
/*220 */         cyls = strtol(buf, NULL, 0);                                               // 0.0
/*222 */     }                                                                              // 0.0
/*226 */     if (get_param_value(buf, sizeof(buf), "heads", str)) {                         // 0.0
/*228 */         heads = strtol(buf, NULL, 0);                                              // 0.0
/*230 */     }                                                                              // 0.0
/*234 */     if (get_param_value(buf, sizeof(buf), "secs", str)) {                          // 0.0
/*236 */         secs = strtol(buf, NULL, 0);                                               // 0.0
/*238 */     }                                                                              // 0.0
/*242 */     if (cyls || heads || secs) {                                                   // 0.0
/*244 */         if (cyls < 1 || cyls > 16383) {                                            // 0.0
/*246 */             fprintf(stderr, "qemu: '%s' invalid physical cyls number\n", str);     // 0.0
/*248 */ 	    return -1;                                                                    // 0.0
/*250 */ 	}                                                                                 // 0.0
/*252 */         if (heads < 1 || heads > 16) {                                             // 0.0
/*254 */             fprintf(stderr, "qemu: '%s' invalid physical heads number\n", str);    // 0.0
/*256 */ 	    return -1;                                                                    // 0.0
/*258 */ 	}                                                                                 // 0.0
/*260 */         if (secs < 1 || secs > 63) {                                               // 0.0
/*262 */             fprintf(stderr, "qemu: '%s' invalid physical secs number\n", str);     // 0.0
/*264 */ 	    return -1;                                                                    // 0.0
/*266 */ 	}                                                                                 // 0.0
/*268 */     }                                                                              // 0.0
/*272 */     if (get_param_value(buf, sizeof(buf), "trans", str)) {                         // 0.0
/*274 */         if (!cyls) {                                                               // 0.0
/*276 */             fprintf(stderr,                                                        // 0.0
/*278 */                     "qemu: '%s' trans must be used with cyls,heads and secs\n",    // 0.0
/*280 */                     str);                                                          // 0.0
/*282 */             return -1;                                                             // 0.0
/*284 */         }                                                                          // 0.0
/*286 */         if (!strcmp(buf, "none"))                                                  // 0.0
/*288 */             translation = BIOS_ATA_TRANSLATION_NONE;                               // 0.0
/*290 */         else if (!strcmp(buf, "lba"))                                              // 0.0
/*292 */             translation = BIOS_ATA_TRANSLATION_LBA;                                // 0.0
/*294 */         else if (!strcmp(buf, "auto"))                                             // 0.0
/*296 */             translation = BIOS_ATA_TRANSLATION_AUTO;                               // 0.0
/*298 */ 	else {                                                                            // 0.0
/*300 */             fprintf(stderr, "qemu: '%s' invalid translation type\n", str);         // 0.0
/*302 */ 	    return -1;                                                                    // 0.0
/*304 */ 	}                                                                                 // 0.0
/*306 */     }                                                                              // 0.0
/*310 */     if (get_param_value(buf, sizeof(buf), "media", str)) {                         // 0.0
/*312 */         if (!strcmp(buf, "disk")) {                                                // 0.0
/*314 */ 	    media = MEDIA_DISK;                                                           // 0.0
/*316 */ 	} else if (!strcmp(buf, "cdrom")) {                                               // 0.0
/*318 */             if (cyls || secs || heads) {                                           // 0.0
/*320 */                 fprintf(stderr,                                                    // 0.0
/*322 */                         "qemu: '%s' invalid physical CHS format\n", str);          // 0.0
/*324 */ 	        return -1;                                                                // 0.0
/*326 */             }                                                                      // 0.0
/*328 */ 	    media = MEDIA_CDROM;                                                          // 0.0
/*330 */ 	} else {                                                                          // 0.0
/*332 */ 	    fprintf(stderr, "qemu: '%s' invalid media\n", str);                           // 0.0
/*334 */ 	    return -1;                                                                    // 0.0
/*336 */ 	}                                                                                 // 0.0
/*338 */     }                                                                              // 0.0
/*342 */     if (get_param_value(buf, sizeof(buf), "snapshot", str)) {                      // 0.0
/*344 */         if (!strcmp(buf, "on"))                                                    // 0.0
/*346 */ 	    snapshot = 1;                                                                 // 0.0
/*348 */         else if (!strcmp(buf, "off"))                                              // 0.0
/*350 */ 	    snapshot = 0;                                                                 // 0.0
/*352 */ 	else {                                                                            // 0.0
/*354 */ 	    fprintf(stderr, "qemu: '%s' invalid snapshot option\n", str);                 // 0.0
/*356 */ 	    return -1;                                                                    // 0.0
/*358 */ 	}                                                                                 // 0.0
/*360 */     }                                                                              // 0.0
/*364 */     if (get_param_value(buf, sizeof(buf), "cache", str)) {                         // 0.0
/*366 */         if (!strcmp(buf, "off") || !strcmp(buf, "none"))                           // 0.0
/*368 */             cache = 0;                                                             // 0.0
/*370 */         else if (!strcmp(buf, "writethrough"))                                     // 0.0
/*372 */             cache = 1;                                                             // 0.0
/*374 */         else if (!strcmp(buf, "writeback"))                                        // 0.0
/*376 */             cache = 2;                                                             // 0.0
/*378 */         else {                                                                     // 0.0
/*380 */            fprintf(stderr, "qemu: invalid cache option\n");                        // 0.0
/*382 */            return -1;                                                              // 0.0
/*384 */         }                                                                          // 0.0
/*386 */     }                                                                              // 0.0
/*390 */     if (get_param_value(buf, sizeof(buf), "format", str)) {                        // 0.0
/*392 */        if (strcmp(buf, "?") == 0) {                                                // 0.0
/*394 */             fprintf(stderr, "qemu: Supported formats:");                           // 0.0
/*396 */             bdrv_iterate_format(bdrv_format_print, NULL);                          // 0.0
/*398 */             fprintf(stderr, "\n");                                                 // 0.0
/*400 */ 	    return -1;                                                                    // 0.0
/*402 */         }                                                                          // 0.0
/*404 */         drv = bdrv_find_format(buf);                                               // 0.0
/*406 */         if (!drv) {                                                                // 0.0
/*408 */             fprintf(stderr, "qemu: '%s' invalid format\n", buf);                   // 0.0
/*410 */             return -1;                                                             // 0.0
/*412 */         }                                                                          // 0.0
/*414 */     }                                                                              // 0.0
/*418 */     if (arg->file == NULL)                                                         // 0.0
/*420 */         get_param_value(file, sizeof(file), "file", str);                          // 0.0
/*422 */     else                                                                           // 0.0
/*424 */         pstrcpy(file, sizeof(file), arg->file);                                    // 0.0
/*428 */     if (!get_param_value(serial, sizeof(serial), "serial", str))                   // 0.0
/*430 */ 	    memset(serial, 0,  sizeof(serial));                                           // 0.0
/*434 */     onerror = BLOCK_ERR_STOP_ENOSPC;                                               // 0.0
/*436 */     if (get_param_value(buf, sizeof(serial), "werror", str)) {                     // 0.0
/*438 */         if (type != IF_IDE && type != IF_SCSI && type != IF_VIRTIO) {              // 0.0
/*440 */             fprintf(stderr, "werror is no supported by this format\n");            // 0.0
/*442 */             return -1;                                                             // 0.0
/*444 */         }                                                                          // 0.0
/*446 */         if (!strcmp(buf, "ignore"))                                                // 0.0
/*448 */             onerror = BLOCK_ERR_IGNORE;                                            // 0.0
/*450 */         else if (!strcmp(buf, "enospc"))                                           // 0.0
/*452 */             onerror = BLOCK_ERR_STOP_ENOSPC;                                       // 0.0
/*454 */         else if (!strcmp(buf, "stop"))                                             // 0.0
/*456 */             onerror = BLOCK_ERR_STOP_ANY;                                          // 0.0
/*458 */         else if (!strcmp(buf, "report"))                                           // 0.0
/*460 */             onerror = BLOCK_ERR_REPORT;                                            // 0.0
/*462 */         else {                                                                     // 0.0
/*464 */             fprintf(stderr, "qemu: '%s' invalid write error action\n", buf);       // 0.0
/*466 */             return -1;                                                             // 0.0
/*468 */         }                                                                          // 0.0
/*470 */     }                                                                              // 0.0
/*474 */     /* compute bus and unit according index */                                     // 0.0
/*478 */     if (index != -1) {                                                             // 0.0
/*480 */         if (bus_id != 0 || unit_id != -1) {                                        // 0.0
/*482 */             fprintf(stderr,                                                        // 0.0
/*484 */                     "qemu: '%s' index cannot be used with bus and unit\n", str);   // 0.0
/*486 */             return -1;                                                             // 0.0
/*488 */         }                                                                          // 0.0
/*490 */         if (max_devs == 0)                                                         // 0.0
/*492 */         {                                                                          // 0.0
/*494 */             unit_id = index;                                                       // 0.0
/*496 */             bus_id = 0;                                                            // 0.0
/*498 */         } else {                                                                   // 0.0
/*500 */             unit_id = index % max_devs;                                            // 0.0
/*502 */             bus_id = index / max_devs;                                             // 0.0
/*504 */         }                                                                          // 0.0
/*506 */     }                                                                              // 0.0
/*510 */     /* if user doesn't specify a unit_id,                                          // 0.0
/*512 */      * try to find the first free                                                  // 0.0
/*514 */      */                                                                            // 0.0
/*518 */     if (unit_id == -1) {                                                           // 0.0
/*520 */        unit_id = 0;                                                                // 0.0
/*522 */        while (drive_get_index(type, bus_id, unit_id) != -1) {                      // 0.0
/*524 */            unit_id++;                                                              // 0.0
/*526 */            if (max_devs && unit_id >= max_devs) {                                  // 0.0
/*528 */                unit_id -= max_devs;                                                // 0.0
/*530 */                bus_id++;                                                           // 0.0
/*532 */            }                                                                       // 0.0
/*534 */        }                                                                           // 0.0
/*536 */     }                                                                              // 0.0
/*540 */     /* check unit id */                                                            // 0.0
/*544 */     if (max_devs && unit_id >= max_devs) {                                         // 0.0
/*546 */         fprintf(stderr, "qemu: '%s' unit %d too big (max is %d)\n",                // 0.0
/*548 */                         str, unit_id, max_devs - 1);                               // 0.0
/*550 */         return -1;                                                                 // 0.0
/*552 */     }                                                                              // 0.0
/*556 */     /*                                                                             // 0.0
/*558 */      * ignore multiple definitions                                                 // 0.0
/*560 */      */                                                                            // 0.0
/*564 */     if (drive_get_index(type, bus_id, unit_id) != -1)                              // 0.0
/*566 */         return -2;                                                                 // 0.0
/*570 */     /* init */                                                                     // 0.0
/*574 */     if (type == IF_IDE || type == IF_SCSI)                                         // 0.0
/*576 */         mediastr = (media == MEDIA_CDROM) ? "-cd" : "-hd";                         // 0.0
/*578 */     if (max_devs)                                                                  // 0.0
/*580 */         snprintf(buf, sizeof(buf), "%s%i%s%i",                                     // 0.0
/*582 */                  devname, bus_id, mediastr, unit_id);                              // 0.0
/*584 */     else                                                                           // 0.0
/*586 */         snprintf(buf, sizeof(buf), "%s%s%i",                                       // 0.0
/*588 */                  devname, mediastr, unit_id);                                      // 0.0
/*590 */     bdrv = bdrv_new(buf);                                                          // 0.0
/*592 */     drives_table_idx = drive_get_free_idx();                                       // 0.0
/*594 */     drives_table[drives_table_idx].bdrv = bdrv;                                    // 0.0
/*596 */     drives_table[drives_table_idx].type = type;                                    // 0.0
/*598 */     drives_table[drives_table_idx].bus = bus_id;                                   // 0.0
/*600 */     drives_table[drives_table_idx].unit = unit_id;                                 // 0.0
/*602 */     drives_table[drives_table_idx].onerror = onerror;                              // 0.0
/*604 */     drives_table[drives_table_idx].drive_opt_idx = arg - drives_opt;               // 0.0
/*606 */     strncpy(drives_table[drives_table_idx].serial, serial, sizeof(serial));        // 0.0
/*608 */     nb_drives++;                                                                   // 0.0
/*612 */     switch(type) {                                                                 // 0.0
/*614 */     case IF_IDE:                                                                   // 0.0
/*616 */     case IF_SCSI:                                                                  // 0.0
/*618 */     case IF_XEN:                                                                   // 0.0
/*620 */         switch(media) {                                                            // 0.0
/*622 */ 	case MEDIA_DISK:                                                                  // 0.0
/*624 */             if (cyls != 0) {                                                       // 0.0
/*626 */                 bdrv_set_geometry_hint(bdrv, cyls, heads, secs);                   // 0.0
/*628 */                 bdrv_set_translation_hint(bdrv, translation);                      // 0.0
/*630 */             }                                                                      // 0.0
/*632 */ 	    break;                                                                        // 0.0
/*634 */ 	case MEDIA_CDROM:                                                                 // 0.0
/*636 */             bdrv_set_type_hint(bdrv, BDRV_TYPE_CDROM);                             // 0.0
/*638 */ 	    break;                                                                        // 0.0
/*640 */ 	}                                                                                 // 0.0
/*642 */         break;                                                                     // 0.0
/*644 */     case IF_SD:                                                                    // 0.0
/*646 */         /* FIXME: This isn't really a floppy, but it's a reasonable                // 0.0
/*648 */            approximation.  */                                                      // 0.0
/*650 */     case IF_FLOPPY:                                                                // 0.0
/*652 */         bdrv_set_type_hint(bdrv, BDRV_TYPE_FLOPPY);                                // 0.0
/*654 */         break;                                                                     // 0.0
/*656 */     case IF_PFLASH:                                                                // 0.0
/*658 */     case IF_MTD:                                                                   // 0.0
/*660 */     case IF_VIRTIO:                                                                // 0.0
/*662 */         break;                                                                     // 0.0
/*664 */     case IF_COUNT:                                                                 // 0.0
/*666 */         abort();                                                                   // 0.0
/*668 */     }                                                                              // 0.0
/*670 */     if (!file[0])                                                                  // 0.0
/*672 */         return -2;                                                                 // 0.0
/*674 */     bdrv_flags = 0;                                                                // 0.0
/*676 */     if (snapshot) {                                                                // 0.0
/*678 */         bdrv_flags |= BDRV_O_SNAPSHOT;                                             // 0.0
/*680 */         cache = 2; /* always use write-back with snapshot */                       // 0.0
/*682 */     }                                                                              // 0.0
/*684 */     if (cache == 0) /* no caching */                                               // 0.0
/*686 */         bdrv_flags |= BDRV_O_NOCACHE;                                              // 0.0
/*688 */     else if (cache == 2) /* write-back */                                          // 0.0
/*690 */         bdrv_flags |= BDRV_O_CACHE_WB;                                             // 0.0
/*692 */     else if (cache == 3) /* not specified */                                       // 0.0
/*694 */         bdrv_flags |= BDRV_O_CACHE_DEF;                                            // 0.0
/*696 */     if (bdrv_open2(bdrv, file, bdrv_flags, drv) < 0) {                             // 0.0
/*698 */         fprintf(stderr, "qemu: could not open disk image %s\n",                    // 0.0
/*700 */                         file);                                                     // 0.0
/*702 */         return -1;                                                                 // 0.0
/*704 */     }                                                                              // 0.0
/*706 */     if (bdrv_key_required(bdrv))                                                   // 0.0
/*708 */         autostart = 0;                                                             // 0.0
/*710 */     return drives_table_idx;                                                       // 0.0
/*712 */ }                                                                                  // 0.0
