// commit message qemu@761731b180 (target=0, prob=0.4303863, correct=True): block: let backup blockjob run in BDS AioContext
/*0   */ void qmp_drive_backup(const char *device, const char *target,                     // (10) 0.03711
/*2   */                       bool has_format, const char *format,                        // (4) 0.06055
/*4   */                       enum MirrorSyncMode sync,                                   // (5) 0.05273
/*6   */                       bool has_mode, enum NewImageMode mode,                      // (3) 0.0625
/*8   */                       bool has_speed, int64_t speed,                              // (2) 0.0625
/*10  */                       bool has_on_source_error, BlockdevOnError on_source_error,  // (1) 0.07812
/*12  */                       bool has_on_target_error, BlockdevOnError on_target_error,  // (0) 0.07812
/*14  */                       Error **errp)                                               // (6) 0.05078
/*16  */ {                                                                                 // (28) 0.001953
/*18  */     BlockDriverState *bs;                                                         // (21) 0.01758
/*20  */     BlockDriverState *target_bs;                                                  // (15) 0.02148
/*22  */     BlockDriverState *source = NULL;                                              // (16) 0.02148
/*24  */     BlockDriver *drv = NULL;                                                      // (14) 0.02148
/*26  */     Error *local_err = NULL;                                                      // (13) 0.02148
/*28  */     int flags;                                                                    // (23) 0.01172
/*30  */     int64_t size;                                                                 // (20) 0.01758
/*32  */     int ret;                                                                      // (22) 0.01172
/*36  */     if (!has_speed) {                                                             // (18) 0.01953
/*38  */         speed = 0;                                                                // (17) 0.02148
/*40  */     }                                                                             // (25) 0.007812
/*42  */     if (!has_on_source_error) {                                                   // (12) 0.02734
/*44  */         on_source_error = BLOCKDEV_ON_ERROR_REPORT;                               // (9) 0.04687
/*46  */     }                                                                             // (26) 0.007812
/*48  */     if (!has_on_target_error) {                                                   // (11) 0.02734
/*50  */         on_target_error = BLOCKDEV_ON_ERROR_REPORT;                               // (8) 0.04687
/*52  */     }                                                                             // (27) 0.007812
/*54  */     if (!has_mode) {                                                              // (19) 0.01953
/*56  */         mode = NEW_IMAGE_MODE_ABSOLUTE_PATHS;                                     // (7) 0.04883
/*58  */     }                                                                             // (24) 0.007812
/*62  */     bs = bdrv_find(device);                                                       // 0.0
/*64  */     if (!bs) {                                                                    // 0.0
/*66  */         error_set(errp, QERR_DEVICE_NOT_FOUND, device);                           // 0.0
/*68  */         return;                                                                   // 0.0
/*70  */     }                                                                             // 0.0
/*74  */     if (!bdrv_is_inserted(bs)) {                                                  // 0.0
/*76  */         error_set(errp, QERR_DEVICE_HAS_NO_MEDIUM, device);                       // 0.0
/*78  */         return;                                                                   // 0.0
/*80  */     }                                                                             // 0.0
/*84  */     if (!has_format) {                                                            // 0.0
/*86  */         format = mode == NEW_IMAGE_MODE_EXISTING ? NULL : bs->drv->format_name;   // 0.0
/*88  */     }                                                                             // 0.0
/*90  */     if (format) {                                                                 // 0.0
/*92  */         drv = bdrv_find_format(format);                                           // 0.0
/*94  */         if (!drv) {                                                               // 0.0
/*96  */             error_set(errp, QERR_INVALID_BLOCK_FORMAT, format);                   // 0.0
/*98  */             return;                                                               // 0.0
/*100 */         }                                                                         // 0.0
/*102 */     }                                                                             // 0.0
/*106 */     if (bdrv_op_is_blocked(bs, BLOCK_OP_TYPE_BACKUP_SOURCE, errp)) {              // 0.0
/*108 */         return;                                                                   // 0.0
/*110 */     }                                                                             // 0.0
/*114 */     flags = bs->open_flags | BDRV_O_RDWR;                                         // 0.0
/*118 */     /* See if we have a backing HD we can use to create our new image             // 0.0
/*120 */      * on top of. */                                                              // 0.0
/*122 */     if (sync == MIRROR_SYNC_MODE_TOP) {                                           // 0.0
/*124 */         source = bs->backing_hd;                                                  // 0.0
/*126 */         if (!source) {                                                            // 0.0
/*128 */             sync = MIRROR_SYNC_MODE_FULL;                                         // 0.0
/*130 */         }                                                                         // 0.0
/*132 */     }                                                                             // 0.0
/*134 */     if (sync == MIRROR_SYNC_MODE_NONE) {                                          // 0.0
/*136 */         source = bs;                                                              // 0.0
/*138 */     }                                                                             // 0.0
/*142 */     size = bdrv_getlength(bs);                                                    // 0.0
/*144 */     if (size < 0) {                                                               // 0.0
/*146 */         error_setg_errno(errp, -size, "bdrv_getlength failed");                   // 0.0
/*148 */         return;                                                                   // 0.0
/*150 */     }                                                                             // 0.0
/*154 */     if (mode != NEW_IMAGE_MODE_EXISTING) {                                        // 0.0
/*156 */         assert(format && drv);                                                    // 0.0
/*158 */         if (source) {                                                             // 0.0
/*160 */             bdrv_img_create(target, format, source->filename,                     // 0.0
/*162 */                             source->drv->format_name, NULL,                       // 0.0
/*164 */                             size, flags, &local_err, false);                      // 0.0
/*166 */         } else {                                                                  // 0.0
/*168 */             bdrv_img_create(target, format, NULL, NULL, NULL,                     // 0.0
/*170 */                             size, flags, &local_err, false);                      // 0.0
/*172 */         }                                                                         // 0.0
/*174 */     }                                                                             // 0.0
/*178 */     if (local_err) {                                                              // 0.0
/*180 */         error_propagate(errp, local_err);                                         // 0.0
/*182 */         return;                                                                   // 0.0
/*184 */     }                                                                             // 0.0
/*188 */     target_bs = NULL;                                                             // 0.0
/*190 */     ret = bdrv_open(&target_bs, target, NULL, NULL, flags, drv, &local_err);      // 0.0
/*192 */     if (ret < 0) {                                                                // 0.0
/*194 */         error_propagate(errp, local_err);                                         // 0.0
/*196 */         return;                                                                   // 0.0
/*198 */     }                                                                             // 0.0
/*202 */     backup_start(bs, target_bs, speed, sync, on_source_error, on_target_error,    // 0.0
/*204 */                  block_job_cb, bs, &local_err);                                   // 0.0
/*206 */     if (local_err != NULL) {                                                      // 0.0
/*208 */         bdrv_unref(target_bs);                                                    // 0.0
/*210 */         error_propagate(errp, local_err);                                         // 0.0
/*212 */         return;                                                                   // 0.0
/*214 */     }                                                                             // 0.0
/*216 */ }                                                                                 // 0.0
