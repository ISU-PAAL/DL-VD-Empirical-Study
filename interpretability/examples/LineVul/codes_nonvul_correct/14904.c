// commit message qemu@4d68e86bb1 (target=0, prob=0.27282068, correct=True): coroutine: rewrite pool to avoid mutex
/*0  */ void qemu_coroutine_adjust_pool_size(int n)                    // (4) 0.07489
/*2  */ {                                                              // (13) 0.004405
/*4  */     qemu_mutex_lock(&pool_lock);                               // (6) 0.07048
/*8  */     pool_max_size += n;                                        // (11) 0.04846
/*12 */     /* Callers should never take away more than they added */  // (8) 0.06608
/*14 */     assert(pool_max_size >= POOL_DEFAULT_SIZE);                // (2) 0.0837
/*18 */     /* Trim oversized pool down to new max */                  // (9) 0.05727
/*20 */     while (pool_size > pool_max_size) {                        // (7) 0.07048
/*22 */         Coroutine *co = QSLIST_FIRST(&pool);                   // (1) 0.09251
/*24 */         QSLIST_REMOVE_HEAD(&pool, pool_next);                  // (0) 0.1013
/*26 */         pool_size--;                                           // (10) 0.05286
/*28 */         qemu_coroutine_delete(co);                             // (3) 0.0793
/*30 */     }                                                          // (12) 0.01762
/*34 */     qemu_mutex_unlock(&pool_lock);                             // (5) 0.07489
/*36 */ }                                                              // (14) 0.004405
