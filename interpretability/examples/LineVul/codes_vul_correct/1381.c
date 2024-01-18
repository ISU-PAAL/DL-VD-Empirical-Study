// commit message qemu@0b8b8753e4 (target=1, prob=0.8148421, correct=True): coroutine: move entry argument to qemu_coroutine_create
/*0  */ bool qemu_co_enter_next(CoQueue *queue)                    // (2) 0.1231
/*2  */ {                                                          // (9) 0.007692
/*4  */     Coroutine *next;                                       // (5) 0.06154
/*8  */     next = QSIMPLEQ_FIRST(&queue->entries);                // (1) 0.1385
/*10 */     if (!next) {                                           // (6) 0.06154
/*12 */         return false;                                      // (4) 0.07692
/*14 */     }                                                      // (8) 0.03077
/*18 */     QSIMPLEQ_REMOVE_HEAD(&queue->entries, co_queue_next);  // (0) 0.1923
/*20 */     qemu_coroutine_enter(next, NULL);                      // (3) 0.1231
/*22 */     return true;                                           // (7) 0.04615
/*24 */ }                                                          // (10) 0.007692
