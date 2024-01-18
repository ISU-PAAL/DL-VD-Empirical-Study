// commit message qemu@aef172ffdc (target=1, prob=0.35242683, correct=False): block/iscsi: dont leave allocmap in an invalid state on UNMAP failure
/*0   */ coroutine_fn iscsi_co_pdiscard(BlockDriverState *bs, int64_t offset, int bytes)  // (2) 0.05664
/*2   */ {                                                                                // (29) 0.001953
/*4   */     IscsiLun *iscsilun = bs->opaque;                                             // (7) 0.03711
/*6   */     struct IscsiTask iTask;                                                      // (20) 0.02148
/*8   */     struct unmap_list list;                                                      // (21) 0.01953
/*10  */     int r = 0;                                                                   // (23) 0.01562
/*14  */     if (!is_byte_request_lun_aligned(offset, bytes, iscsilun)) {                 // (3) 0.05078
/*16  */         return -ENOTSUP;                                                         // (17) 0.02539
/*18  */     }                                                                            // (25) 0.007812
/*22  */     if (!iscsilun->lbp.lbpu) {                                                   // (14) 0.03125
/*24  */         /* UNMAP is not supported by the target */                               // (13) 0.0332
/*26  */         return 0;                                                                // (22) 0.01953
/*28  */     }                                                                            // (24) 0.007812
/*32  */     list.lba = offset / iscsilun->block_size;                                    // (9) 0.03711
/*34  */     list.num = bytes / iscsilun->block_size;                                     // (11) 0.03516
/*38  */     iscsi_co_init_iscsitask(iscsilun, &iTask);                                   // (5) 0.04492
/*40  */     qemu_mutex_lock(&iscsilun->mutex);                                           // (8) 0.03711
/*42  */ retry:                                                                           // (28) 0.005859
/*44  */     if (iscsi_unmap_task(iscsilun->iscsi, iscsilun->lun, 0, 0, &list, 1,         // (1) 0.07227
/*46  */                          iscsi_co_generic_cb, &iTask) == NULL) {                 // (0) 0.08203
/*48  */         r = -ENOMEM;                                                             // (15) 0.02734
/*50  */         goto out_unlock;                                                         // (16) 0.02539
/*52  */     }                                                                            // (26) 0.007812
/*56  */     while (!iTask.complete) {                                                    // (19) 0.02148
/*58  */         iscsi_set_events(iscsilun);                                              // (10) 0.03711
/*60  */         qemu_mutex_unlock(&iscsilun->mutex);                                     // (4) 0.04687
/*62  */         qemu_coroutine_yield();                                                  // (12) 0.0332
/*64  */         qemu_mutex_lock(&iscsilun->mutex);                                       // (6) 0.04492
/*66  */     }                                                                            // (27) 0.007812
/*70  */     if (iTask.task != NULL) {                                                    // (18) 0.02539
/*72  */         scsi_free_scsi_task(iTask.task);                                         // 0.0
/*74  */         iTask.task = NULL;                                                       // 0.0
/*76  */     }                                                                            // 0.0
/*80  */     if (iTask.do_retry) {                                                        // 0.0
/*82  */         iTask.complete = 0;                                                      // 0.0
/*84  */         goto retry;                                                              // 0.0
/*86  */     }                                                                            // 0.0
/*90  */     if (iTask.status == SCSI_STATUS_CHECK_CONDITION) {                           // 0.0
/*92  */         /* the target might fail with a check condition if it                    // 0.0
/*94  */            is not happy with the alignment of the UNMAP request                  // 0.0
/*96  */            we silently fail in this case */                                      // 0.0
/*98  */         goto out_unlock;                                                         // 0.0
/*100 */     }                                                                            // 0.0
/*104 */     if (iTask.status != SCSI_STATUS_GOOD) {                                      // 0.0
/*106 */         r = iTask.err_code;                                                      // 0.0
/*108 */         goto out_unlock;                                                         // 0.0
/*110 */     }                                                                            // 0.0
/*114 */     iscsi_allocmap_set_invalid(iscsilun, offset >> BDRV_SECTOR_BITS,             // 0.0
/*116 */                                bytes >> BDRV_SECTOR_BITS);                       // 0.0
/*120 */ out_unlock:                                                                      // 0.0
/*122 */     qemu_mutex_unlock(&iscsilun->mutex);                                         // 0.0
/*124 */     return r;                                                                    // 0.0
/*126 */ }                                                                                // 0.0
