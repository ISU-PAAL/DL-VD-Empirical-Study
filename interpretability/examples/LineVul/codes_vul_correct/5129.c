// commit message qemu@c95de7e2c4 (target=1, prob=0.9989774, correct=True): block: fix qcow2_co_flush deadlock
/*0  */ static int qcow2_co_flush(BlockDriverState *bs)            // (4) 0.08163
/*2  */ {                                                          // (14) 0.005102
/*4  */     BDRVQcowState *s = bs->opaque;                         // (2) 0.09184
/*6  */     int ret;                                               // (10) 0.03061
/*10 */     qemu_co_mutex_lock(&s->lock);                          // (3) 0.09184
/*12 */     ret = qcow2_cache_flush(bs, s->l2_table_cache);        // (1) 0.1224
/*14 */     if (ret < 0) {                                         // (6) 0.05102
/*17 */         return ret;                                        // (7) 0.05102
/*19 */     }                                                      // (11) 0.02041
/*23 */     ret = qcow2_cache_flush(bs, s->refcount_block_cache);  // (0) 0.1224
/*25 */     if (ret < 0) {                                         // (8) 0.05102
/*28 */         return ret;                                        // (9) 0.05102
/*30 */     }                                                      // (12) 0.02041
/*35 */     return bdrv_co_flush(bs->file);                        // (5) 0.08163
/*37 */ }                                                          // (13) 0.005102
