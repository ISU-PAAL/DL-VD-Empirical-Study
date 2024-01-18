// commit message qemu@c5acdc9ab4 (target=0, prob=0.43095145, correct=True): block: Release named dirty bitmaps in bdrv_close()
/*0  */ static void bdrv_delete(BlockDriverState *bs)  // (2) 0.1014
/*2  */ {                                              // (9) 0.007246
/*4  */     assert(!bs->job);                          // (7) 0.07246
/*6  */     assert(bdrv_op_blocker_is_empty(bs));      // (0) 0.1449
/*8  */     assert(!bs->refcnt);                       // (4) 0.08696
/*10 */     assert(QLIST_EMPTY(&bs->dirty_bitmaps));   // (1) 0.1304
/*14 */     bdrv_close(bs);                            // (6) 0.07971
/*18 */     /* remove from list, if necessary */       // (5) 0.07971
/*20 */     bdrv_make_anon(bs);                        // (3) 0.0942
/*24 */     g_free(bs);                                // (8) 0.06522
/*26 */ }                                              // (10) 0.007246
