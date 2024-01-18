// commit message qemu@1606e4cf8a (target=1, prob=0.9990584, correct=True): throttle: Remove block from group on hot-unplug
/*0  */ static void blk_delete(BlockBackend *blk)                      // (6) 0.06635
/*2  */ {                                                              // (12) 0.004739
/*4  */     assert(!blk->refcnt);                                      // (7) 0.06161
/*6  */     assert(!blk->name);                                        // (8) 0.05213
/*8  */     assert(!blk->dev);                                         // (9) 0.05213
/*13 */     if (blk->root) {                                           // (10) 0.05213
/*15 */         blk_remove_bs(blk);                                    // (4) 0.08057
/*18 */     assert(QLIST_EMPTY(&blk->remove_bs_notifiers.notifiers));  // (0) 0.1137
/*20 */     assert(QLIST_EMPTY(&blk->insert_bs_notifiers.notifiers));  // (1) 0.1137
/*22 */     QTAILQ_REMOVE(&block_backends, blk, link);                 // (2) 0.1043
/*24 */     drive_info_del(blk->legacy_dinfo);                         // (3) 0.08531
/*26 */     block_acct_cleanup(&blk->stats);                           // (5) 0.07583
/*28 */     g_free(blk);                                               // (11) 0.04739
