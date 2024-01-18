// commit message qemu@111049a4ec (target=1, prob=0.052797373, correct=False): blockjob: refactor backup_start as backup_job_create
/*0  */ static void drive_backup_prepare(BlkActionState *common, Error **errp)      // (5) 0.06111
/*2  */ {                                                                           // (22) 0.002778
/*4  */     DriveBackupState *state = DO_UPCAST(DriveBackupState, common, common);  // (1) 0.06944
/*6  */     BlockDriverState *bs;                                                   // (16) 0.025
/*8  */     DriveBackup *backup;                                                    // (13) 0.02778
/*10 */     Error *local_err = NULL;                                                // (12) 0.03056
/*14 */     assert(common->action->type == TRANSACTION_ACTION_KIND_DRIVE_BACKUP);   // (2) 0.06944
/*16 */     backup = common->action->u.drive_backup.data;                           // (7) 0.05
/*20 */     bs = qmp_get_root_bs(backup->device, errp);                             // (3) 0.06389
/*22 */     if (!bs) {                                                              // (19) 0.02222
/*24 */         return;                                                             // (17) 0.025
/*26 */     }                                                                       // (20) 0.01111
/*30 */     /* AioContext is released in .clean() */                                // (9) 0.03889
/*32 */     state->aio_context = bdrv_get_aio_context(bs);                          // (4) 0.06389
/*34 */     aio_context_acquire(state->aio_context);                                // (8) 0.05
/*36 */     bdrv_drained_begin(bs);                                                 // (10) 0.03889
/*38 */     state->bs = bs;                                                         // (14) 0.02778
/*42 */     do_drive_backup(backup, common->block_job_txn, &local_err);             // (0) 0.075
/*44 */     if (local_err) {                                                        // (15) 0.02778
/*46 */         error_propagate(errp, local_err);                                   // (6) 0.05278
/*48 */         return;                                                             // (18) 0.025
/*50 */     }                                                                       // (21) 0.01111
/*54 */     state->job = state->bs->job;                                            // (11) 0.03611
/*56 */ }                                                                           // (23) 0.002778
