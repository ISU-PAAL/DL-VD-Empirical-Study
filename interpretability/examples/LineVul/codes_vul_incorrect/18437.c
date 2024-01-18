// commit message qemu@4c8449832c (target=1, prob=0.079067916, correct=False): block: Remove copy-on-read from bdrv_move_feature_fields()
/*0  */ static void external_snapshot_commit(BlkActionState *common)                    // (9) 0.05948
/*2  */ {                                                                               // (11) 0.003717
/*4  */     ExternalSnapshotState *state =                                              // (10) 0.03717
/*6  */                              DO_UPCAST(ExternalSnapshotState, common, common);  // (0) 0.1599
/*10 */     bdrv_set_aio_context(state->new_bs, state->aio_context);                    // (2) 0.1004
/*14 */     /* This removes our old bs and adds the new bs */                           // (8) 0.0632
/*16 */     bdrv_append(state->new_bs, state->old_bs);                                  // (5) 0.07807
/*18 */     /* We don't need (or want) to use the transactional                         // (6) 0.0632
/*20 */      * bdrv_reopen_multiple() across all the entries at once, because we        // (3) 0.0855
/*22 */      * don't want to abort all of them if one of them fails the reopen */       // (4) 0.07807
/*24 */     bdrv_reopen(state->old_bs, state->old_bs->open_flags & ~BDRV_O_RDWR,        // (1) 0.1338
/*26 */                 NULL);                                                          // (7) 0.0632
/*28 */ }                                                                               // (12) 0.003717
