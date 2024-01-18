// commit message qemu@2dfb4c033f (target=0, prob=0.3860057, correct=True): block: Accept node-name for blockdev-snapshot-delete-internal-sync
/*0   */ SnapshotInfo *qmp_blockdev_snapshot_delete_internal_sync(const char *device,     // (7) 0.04688
/*2   */                                                          bool has_id,            // (3) 0.1191
/*4   */                                                          const char *id,         // (2) 0.1191
/*6   */                                                          bool has_name,          // (4) 0.1191
/*8   */                                                          const char *name,       // (1) 0.1191
/*10  */                                                          Error **errp)           // (0) 0.1191
/*12  */ {                                                                                // (18) 0.001954
/*14  */     BlockDriverState *bs;                                                        // (15) 0.01758
/*16  */     BlockBackend *blk;                                                           // (13) 0.01953
/*18  */     AioContext *aio_context;                                                     // (10) 0.02344
/*20  */     QEMUSnapshotInfo sn;                                                         // (9) 0.02344
/*22  */     Error *local_err = NULL;                                                     // (11) 0.02148
/*24  */     SnapshotInfo *info = NULL;                                                   // (12) 0.02148
/*26  */     int ret;                                                                     // (17) 0.01172
/*30  */     blk = blk_by_name(device);                                                   // (8) 0.0293
/*32  */     if (!blk) {                                                                  // (16) 0.01758
/*34  */         error_set(errp, ERROR_CLASS_DEVICE_NOT_FOUND,                            // (6) 0.05078
/*36  */                   "Device '%s' not found", device);                              // (5) 0.05469
/*38  */         return NULL;                                                             // (14) 0.01953
/*40  */     }                                                                            // 0.0
/*44  */     aio_context = blk_get_aio_context(blk);                                      // 0.0
/*46  */     aio_context_acquire(aio_context);                                            // 0.0
/*50  */     if (!has_id) {                                                               // 0.0
/*52  */         id = NULL;                                                               // 0.0
/*54  */     }                                                                            // 0.0
/*58  */     if (!has_name) {                                                             // 0.0
/*60  */         name = NULL;                                                             // 0.0
/*62  */     }                                                                            // 0.0
/*66  */     if (!id && !name) {                                                          // 0.0
/*68  */         error_setg(errp, "Name or id must be provided");                         // 0.0
/*70  */         goto out_aio_context;                                                    // 0.0
/*72  */     }                                                                            // 0.0
/*76  */     if (!blk_is_available(blk)) {                                                // 0.0
/*78  */         error_setg(errp, "Device '%s' has no medium", device);                   // 0.0
/*80  */         goto out_aio_context;                                                    // 0.0
/*82  */     }                                                                            // 0.0
/*84  */     bs = blk_bs(blk);                                                            // 0.0
/*88  */     if (bdrv_op_is_blocked(bs, BLOCK_OP_TYPE_INTERNAL_SNAPSHOT_DELETE, errp)) {  // 0.0
/*90  */         goto out_aio_context;                                                    // 0.0
/*92  */     }                                                                            // 0.0
/*96  */     ret = bdrv_snapshot_find_by_id_and_name(bs, id, name, &sn, &local_err);      // 0.0
/*98  */     if (local_err) {                                                             // 0.0
/*100 */         error_propagate(errp, local_err);                                        // 0.0
/*102 */         goto out_aio_context;                                                    // 0.0
/*104 */     }                                                                            // 0.0
/*106 */     if (!ret) {                                                                  // 0.0
/*108 */         error_setg(errp,                                                         // 0.0
/*110 */                    "Snapshot with id '%s' and name '%s' does not exist on "      // 0.0
/*112 */                    "device '%s'",                                                // 0.0
/*114 */                    STR_OR_NULL(id), STR_OR_NULL(name), device);                  // 0.0
/*116 */         goto out_aio_context;                                                    // 0.0
/*118 */     }                                                                            // 0.0
/*122 */     bdrv_snapshot_delete(bs, id, name, &local_err);                              // 0.0
/*124 */     if (local_err) {                                                             // 0.0
/*126 */         error_propagate(errp, local_err);                                        // 0.0
/*128 */         goto out_aio_context;                                                    // 0.0
/*130 */     }                                                                            // 0.0
/*134 */     aio_context_release(aio_context);                                            // 0.0
/*138 */     info = g_new0(SnapshotInfo, 1);                                              // 0.0
/*140 */     info->id = g_strdup(sn.id_str);                                              // 0.0
/*142 */     info->name = g_strdup(sn.name);                                              // 0.0
/*144 */     info->date_nsec = sn.date_nsec;                                              // 0.0
/*146 */     info->date_sec = sn.date_sec;                                                // 0.0
/*148 */     info->vm_state_size = sn.vm_state_size;                                      // 0.0
/*150 */     info->vm_clock_nsec = sn.vm_clock_nsec % 1000000000;                         // 0.0
/*152 */     info->vm_clock_sec = sn.vm_clock_nsec / 1000000000;                          // 0.0
/*156 */     return info;                                                                 // 0.0
/*160 */ out_aio_context:                                                                 // 0.0
/*162 */     aio_context_release(aio_context);                                            // 0.0
/*164 */     return NULL;                                                                 // 0.0
/*166 */ }                                                                                // 0.0
