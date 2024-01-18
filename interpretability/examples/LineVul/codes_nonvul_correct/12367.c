// commit message qemu@1dde716ed6 (target=0, prob=0.48942253, correct=True): iscsi: retry read, write, flush and unmap on unit attention check conditions
/*0  */ iscsi_unmap_cb(struct iscsi_context *iscsi, int status,        // (3) 0.09091
/*2  */                      void *command_data, void *opaque)         // (0) 0.1342
/*4  */ {                                                              // (13) 0.004329
/*6  */     IscsiAIOCB *acb = opaque;                                  // (5) 0.06494
/*10 */     if (acb->canceled != 0) {                                  // (6) 0.06494
/*12 */         return;                                                // (10) 0.03896
/*14 */     }                                                          // (11) 0.01732
/*18 */     acb->status = 0;                                           // (8) 0.04329
/*20 */     if (status < 0) {                                          // (9) 0.04329
/*22 */         error_report("Failed to unmap data on iSCSI lun. %s",  // (2) 0.1126
/*24 */                      iscsi_get_error(iscsi));                  // (1) 0.1342
/*26 */         acb->status = -EIO;                                    // (4) 0.06926
/*28 */     }                                                          // (12) 0.01732
/*32 */     iscsi_schedule_bh(acb);                                    // (7) 0.06494
/*34 */ }                                                              // (14) 0.004329
