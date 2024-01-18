// commit message qemu@88be7b4be4 (target=1, prob=0.3918104, correct=False): block: Fix bdrv_next() memory leak
/*0  */ void bdrv_invalidate_cache_all(Error **errp)                 // (6) 0.07171
/*2  */ {                                                            // (14) 0.003984
/*4  */     BlockDriverState *bs;                                    // (11) 0.03586
/*6  */     Error *local_err = NULL;                                 // (10) 0.04382
/*8  */     BdrvNextIterator *it = NULL;                             // (8) 0.05179
/*12 */     while ((it = bdrv_next(it, &bs)) != NULL) {              // (3) 0.08765
/*14 */         AioContext *aio_context = bdrv_get_aio_context(bs);  // (0) 0.1155
/*18 */         aio_context_acquire(aio_context);                    // (4) 0.07968
/*20 */         bdrv_invalidate_cache(bs, &local_err);               // (1) 0.09562
/*22 */         aio_context_release(aio_context);                    // (5) 0.0757
/*24 */         if (local_err) {                                     // (7) 0.05578
/*26 */             error_propagate(errp, local_err);                // (2) 0.09163
/*28 */             return;                                          // (9) 0.05179
/*30 */         }                                                    // (12) 0.03187
/*32 */     }                                                        // (13) 0.01594
/*34 */ }                                                            // (15) 0.003984
