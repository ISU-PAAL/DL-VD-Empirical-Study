// commit message qemu@eefff991d0 (target=1, prob=0.41025287, correct=False): qemu/migration: fix the double free problem on from_src_file
/*0   */ int load_snapshot(const char *name, Error **errp)                             // (10) 0.03125
/*2   */ {                                                                             // (28) 0.001953
/*4   */     BlockDriverState *bs, *bs_vm_state;                                       // (11) 0.03125
/*6   */     QEMUSnapshotInfo sn;                                                      // (18) 0.02344
/*8   */     QEMUFile *f;                                                              // (21) 0.01953
/*10  */     int ret;                                                                  // (24) 0.01172
/*12  */     AioContext *aio_context;                                                  // (19) 0.02344
/*14  */     MigrationIncomingState *mis = migration_incoming_get_current();           // (8) 0.03711
/*18  */     if (!bdrv_all_can_snapshot(&bs)) {                                        // (9) 0.03711
/*20  */         error_setg(errp,                                                      // (13) 0.0293
/*22  */                    "Device '%s' is writable but does not support snapshots",  // (1) 0.06445
/*24  */                    bdrv_get_device_name(bs));                                 // (3) 0.05859
/*26  */         return -ENOTSUP;                                                      // (16) 0.02539
/*28  */     }                                                                         // (26) 0.007812
/*30  */     ret = bdrv_all_find_snapshot(name, &bs);                                  // (7) 0.04102
/*32  */     if (ret < 0) {                                                            // (23) 0.01953
/*34  */         error_setg(errp,                                                      // (14) 0.0293
/*36  */                    "Device '%s' does not have the requested snapshot '%s'",   // (0) 0.06836
/*38  */                    bdrv_get_device_name(bs), name);                           // (2) 0.0625
/*40  */         return ret;                                                           // (22) 0.01953
/*42  */     }                                                                         // (25) 0.007812
/*46  */     bs_vm_state = bdrv_all_find_vmstate_bs();                                 // (5) 0.04492
/*48  */     if (!bs_vm_state) {                                                       // (20) 0.02344
/*50  */         error_setg(errp, "No block device supports snapshots");               // (6) 0.04297
/*52  */         return -ENOTSUP;                                                      // (17) 0.02539
/*54  */     }                                                                         // (27) 0.007812
/*56  */     aio_context = bdrv_get_aio_context(bs_vm_state);                          // (4) 0.04883
/*60  */     /* Don't even try to load empty VM states */                              // (15) 0.02734
/*62  */     aio_context_acquire(aio_context);                                         // (12) 0.03125
/*64  */     ret = bdrv_snapshot_find(bs_vm_state, &sn, name);                         // 0.0
/*66  */     aio_context_release(aio_context);                                         // 0.0
/*68  */     if (ret < 0) {                                                            // 0.0
/*70  */         return ret;                                                           // 0.0
/*72  */     } else if (sn.vm_state_size == 0) {                                       // 0.0
/*74  */         error_setg(errp, "This is a disk-only snapshot. Revert to it "        // 0.0
/*76  */                    " offline using qemu-img");                                // 0.0
/*78  */         return -EINVAL;                                                       // 0.0
/*80  */     }                                                                         // 0.0
/*84  */     /* Flush all IO requests so they don't interfere with the new state.  */  // 0.0
/*86  */     bdrv_drain_all();                                                         // 0.0
/*90  */     ret = bdrv_all_goto_snapshot(name, &bs);                                  // 0.0
/*92  */     if (ret < 0) {                                                            // 0.0
/*94  */         error_setg(errp, "Error %d while activating snapshot '%s' on '%s'",   // 0.0
/*96  */                      ret, name, bdrv_get_device_name(bs));                    // 0.0
/*98  */         return ret;                                                           // 0.0
/*100 */     }                                                                         // 0.0
/*104 */     /* restore the VM state */                                                // 0.0
/*106 */     f = qemu_fopen_bdrv(bs_vm_state, 0);                                      // 0.0
/*108 */     if (!f) {                                                                 // 0.0
/*110 */         error_setg(errp, "Could not open VM state file");                     // 0.0
/*112 */         return -EINVAL;                                                       // 0.0
/*114 */     }                                                                         // 0.0
/*118 */     qemu_system_reset(SHUTDOWN_CAUSE_NONE);                                   // 0.0
/*120 */     mis->from_src_file = f;                                                   // 0.0
/*124 */     aio_context_acquire(aio_context);                                         // 0.0
/*126 */     ret = qemu_loadvm_state(f);                                               // 0.0
/*128 */     qemu_fclose(f);                                                           // 0.0
/*130 */     aio_context_release(aio_context);                                         // 0.0
/*134 */     migration_incoming_state_destroy();                                       // 0.0
/*136 */     if (ret < 0) {                                                            // 0.0
/*138 */         error_setg(errp, "Error %d while loading VM state", ret);             // 0.0
/*140 */         return ret;                                                           // 0.0
/*142 */     }                                                                         // 0.0
/*146 */     return 0;                                                                 // 0.0
/*148 */ }                                                                             // 0.0
