// commit message qemu@39a7a362e1 (target=0, prob=0.091505714, correct=True): coroutine: switch per-thread free pool to a global pool
/*0  */ void qemu_coroutine_delete(Coroutine *co_)                            // (4) 0.08377
/*2  */ {                                                                     // (11) 0.005236
/*4  */     CoroutineThreadState *s = coroutine_get_thread_state();           // (2) 0.09948
/*6  */     CoroutineUContext *co = DO_UPCAST(CoroutineUContext, base, co_);  // (1) 0.1361
/*10 */     if (s->pool_size < POOL_MAX_SIZE) {                               // (3) 0.09948
/*12 */         QLIST_INSERT_HEAD(&s->pool, &co->base, pool_next);            // (0) 0.1466
/*14 */         co->base.caller = NULL;                                       // (5) 0.08377
/*16 */         s->pool_size++;                                               // (6) 0.06806
/*18 */         return;                                                       // (8) 0.04712
/*20 */     }                                                                 // (10) 0.02094
/*24 */     g_free(co->stack);                                                // (7) 0.05759
/*26 */     g_free(co);                                                       // (9) 0.04712
/*28 */ }                                                                     // (12) 0.005236
