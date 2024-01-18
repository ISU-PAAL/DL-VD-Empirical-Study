// commit message qemu@67251a3113 (target=0, prob=0.25456873, correct=True): block: Fix reopen flag inheritance
/*0  */ BlockReopenQueue *bdrv_reopen_queue(BlockReopenQueue *bs_queue,              // (4) 0.06609
/*2  */                                     BlockDriverState *bs, int flags)         // (0) 0.1264
/*4  */ {                                                                            // (18) 0.002874
/*6  */     assert(bs != NULL);                                                      // (14) 0.02586
/*10 */     BlockReopenQueueEntry *bs_entry;                                         // (11) 0.03736
/*12 */     if (bs_queue == NULL) {                                                  // (12) 0.03448
/*14 */         bs_queue = g_new0(BlockReopenQueue, 1);                              // (3) 0.06897
/*16 */         QSIMPLEQ_INIT(bs_queue);                                             // (6) 0.0546
/*18 */     }                                                                        // (16) 0.01149
/*22 */     /* bdrv_open() masks this flag out */                                    // (8) 0.0431
/*24 */     flags &= ~BDRV_O_PROTOCOL;                                               // (7) 0.05172
/*28 */     if (bs->file) {                                                          // (13) 0.02874
/*30 */         bdrv_reopen_queue(bs_queue, bs->file, bdrv_inherited_flags(flags));  // (1) 0.1063
/*32 */     }                                                                        // (17) 0.01149
/*36 */     bs_entry = g_new0(BlockReopenQueueEntry, 1);                             // (5) 0.06034
/*38 */     QSIMPLEQ_INSERT_TAIL(bs_queue, bs_entry, entry);                         // (2) 0.07184
/*42 */     bs_entry->state.bs = bs;                                                 // (9) 0.0431
/*44 */     bs_entry->state.flags = flags;                                           // (10) 0.04023
/*48 */     return bs_queue;                                                         // (15) 0.02586
/*50 */ }                                                                            // (19) 0.002874
