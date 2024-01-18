// commit message qemu@6a8f9661dc (target=0, prob=0.40078434, correct=True): block: Convert to new qapi union layout
/*0   */ void qmp_transaction(TransactionActionList *dev_list, Error **errp)            // (6) 0.03906
/*2   */ {                                                                              // (27) 0.001953
/*4   */     TransactionActionList *dev_entry = dev_list;                               // (16) 0.0293
/*6   */     BlkTransactionState *state, *next;                                         // (20) 0.02539
/*8   */     Error *local_err = NULL;                                                   // (24) 0.02148
/*12  */     QSIMPLEQ_HEAD(snap_bdrv_states, BlkTransactionState) snap_bdrv_states;     // (0) 0.06055
/*14  */     QSIMPLEQ_INIT(&snap_bdrv_states);                                          // (7) 0.03711
/*18  */     /* drain all i/o before any operations */                                  // (19) 0.02539
/*20  */     bdrv_drain_all();                                                          // (22) 0.02344
/*24  */     /* We don't do anything in this loop that commits us to the operations */  // (8) 0.03711
/*26  */     while (NULL != dev_entry) {                                                // (23) 0.02344
/*28  */         TransactionAction *dev_info = NULL;                                    // (14) 0.03125
/*30  */         const BdrvActionOps *ops;                                              // (15) 0.03125
/*34  */         dev_info = dev_entry->value;                                           // (12) 0.0332
/*36  */         dev_entry = dev_entry->next;                                           // (11) 0.0332
/*40  */         assert(dev_info->kind < ARRAY_SIZE(actions));                          // (3) 0.04297
/*44  */         ops = &actions[dev_info->kind];                                        // (10) 0.03516
/*46  */         assert(ops->instance_size > 0);                                        // (13) 0.0332
/*50  */         state = g_malloc0(ops->instance_size);                                 // (5) 0.04102
/*52  */         state->ops = ops;                                                      // (21) 0.02539
/*54  */         state->action = dev_info;                                              // (17) 0.0293
/*56  */         QSIMPLEQ_INSERT_TAIL(&snap_bdrv_states, state, entry);                 // (1) 0.05859
/*60  */         state->ops->prepare(state, &local_err);                                // (4) 0.04102
/*62  */         if (local_err) {                                                       // (18) 0.02734
/*64  */             error_propagate(errp, local_err);                                  // (2) 0.04492
/*66  */             goto delete_and_fail;                                              // (9) 0.03516
/*68  */         }                                                                      // (25) 0.01563
/*70  */     }                                                                          // (26) 0.007813
/*74  */     QSIMPLEQ_FOREACH(state, &snap_bdrv_states, entry) {                        // 0.0
/*76  */         if (state->ops->commit) {                                              // 0.0
/*78  */             state->ops->commit(state);                                         // 0.0
/*80  */         }                                                                      // 0.0
/*82  */     }                                                                          // 0.0
/*86  */     /* success */                                                              // 0.0
/*88  */     goto exit;                                                                 // 0.0
/*92  */ delete_and_fail:                                                               // 0.0
/*94  */     /* failure, and it is all-or-none; roll back all operations */             // 0.0
/*96  */     QSIMPLEQ_FOREACH(state, &snap_bdrv_states, entry) {                        // 0.0
/*98  */         if (state->ops->abort) {                                               // 0.0
/*100 */             state->ops->abort(state);                                          // 0.0
/*102 */         }                                                                      // 0.0
/*104 */     }                                                                          // 0.0
/*106 */ exit:                                                                          // 0.0
/*108 */     QSIMPLEQ_FOREACH_SAFE(state, &snap_bdrv_states, entry, next) {             // 0.0
/*110 */         if (state->ops->clean) {                                               // 0.0
/*112 */             state->ops->clean(state);                                          // 0.0
/*114 */         }                                                                      // 0.0
/*116 */         g_free(state);                                                         // 0.0
/*118 */     }                                                                          // 0.0
/*120 */ }                                                                              // 0.0
