// commit message qemu@35c2c8dc8c (target=0, prob=0.29511735, correct=True): osdep: Rename qemu_{get, set}_version() to qemu_{, set_}hw_version()
/*0   */ int ide_init_drive(IDEState *s, BlockBackend *blk, IDEDriveKind kind,           // (3) 0.04883
/*2   */                    const char *version, const char *serial, const char *model,  // (1) 0.06445
/*4   */                    uint64_t wwn,                                                // (4) 0.04883
/*6   */                    uint32_t cylinders, uint32_t heads, uint32_t secs,           // (0) 0.07227
/*8   */                    int chs_trans)                                               // (6) 0.04688
/*10  */ {                                                                               // (27) 0.001953
/*12  */     uint64_t nb_sectors;                                                        // (14) 0.02539
/*16  */     s->blk = blk;                                                               // (21) 0.02148
/*18  */     s->drive_kind = kind;                                                       // (18) 0.02148
/*22  */     blk_get_geometry(blk, &nb_sectors);                                         // (9) 0.03906
/*24  */     s->cylinders = cylinders;                                                   // (24) 0.01953
/*26  */     s->heads = heads;                                                           // (25) 0.01758
/*28  */     s->sectors = secs;                                                          // (22) 0.02148
/*30  */     s->chs_trans = chs_trans;                                                   // (11) 0.0293
/*32  */     s->nb_sectors = nb_sectors;                                                 // (10) 0.03125
/*34  */     s->wwn = wwn;                                                               // (19) 0.02148
/*36  */     /* The SMART values should be preserved across power cycles                 // (13) 0.02734
/*38  */        but they aren't.  */                                                     // (15) 0.02539
/*40  */     s->smart_enabled = 1;                                                       // (23) 0.02148
/*42  */     s->smart_autosave = 1;                                                      // (16) 0.02539
/*44  */     s->smart_errors = 0;                                                        // (20) 0.02148
/*46  */     s->smart_selftest_count = 0;                                                // (12) 0.0293
/*48  */     if (kind == IDE_CD) {                                                       // (17) 0.02344
/*50  */         blk_set_dev_ops(blk, &ide_cd_block_ops, s);                             // (2) 0.05859
/*52  */         blk_set_guest_block_size(blk, 2048);                                    // (7) 0.04688
/*54  */     } else {                                                                    // (26) 0.01172
/*56  */         if (!blk_is_inserted(s->blk)) {                                         // (8) 0.04492
/*58  */             error_report("Device needs media, but drive is empty");             // (5) 0.04688
/*60  */             return -1;                                                          // 0.0
/*62  */         }                                                                       // 0.0
/*64  */         if (blk_is_read_only(blk)) {                                            // 0.0
/*66  */             error_report("Can't use a read-only drive");                        // 0.0
/*68  */             return -1;                                                          // 0.0
/*70  */         }                                                                       // 0.0
/*72  */         blk_set_dev_ops(blk, &ide_hd_block_ops, s);                             // 0.0
/*74  */     }                                                                           // 0.0
/*76  */     if (serial) {                                                               // 0.0
/*78  */         pstrcpy(s->drive_serial_str, sizeof(s->drive_serial_str), serial);      // 0.0
/*80  */     } else {                                                                    // 0.0
/*82  */         snprintf(s->drive_serial_str, sizeof(s->drive_serial_str),              // 0.0
/*84  */                  "QM%05d", s->drive_serial);                                    // 0.0
/*86  */     }                                                                           // 0.0
/*88  */     if (model) {                                                                // 0.0
/*90  */         pstrcpy(s->drive_model_str, sizeof(s->drive_model_str), model);         // 0.0
/*92  */     } else {                                                                    // 0.0
/*94  */         switch (kind) {                                                         // 0.0
/*96  */         case IDE_CD:                                                            // 0.0
/*98  */             strcpy(s->drive_model_str, "QEMU DVD-ROM");                         // 0.0
/*100 */             break;                                                              // 0.0
/*102 */         case IDE_CFATA:                                                         // 0.0
/*104 */             strcpy(s->drive_model_str, "QEMU MICRODRIVE");                      // 0.0
/*106 */             break;                                                              // 0.0
/*108 */         default:                                                                // 0.0
/*110 */             strcpy(s->drive_model_str, "QEMU HARDDISK");                        // 0.0
/*112 */             break;                                                              // 0.0
/*114 */         }                                                                       // 0.0
/*116 */     }                                                                           // 0.0
/*120 */     if (version) {                                                              // 0.0
/*122 */         pstrcpy(s->version, sizeof(s->version), version);                       // 0.0
/*124 */     } else {                                                                    // 0.0
/*126 */         pstrcpy(s->version, sizeof(s->version), qemu_get_version());            // 0.0
/*128 */     }                                                                           // 0.0
/*132 */     ide_reset(s);                                                               // 0.0
/*134 */     blk_iostatus_enable(blk);                                                   // 0.0
/*136 */     return 0;                                                                   // 0.0
/*138 */ }                                                                               // 0.0
