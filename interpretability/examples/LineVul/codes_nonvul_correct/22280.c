// commit message qemu@c2b38b277a (target=0, prob=0.42437673, correct=True): block: move AioContext, QEMUTimer, main-loop to libqemuutil
/*0  */ static void thread_pool_cancel(BlockAIOCB *acb)                              // (12) 0.04474
/*2  */ {                                                                            // (18) 0.002632
/*4  */     ThreadPoolElement *elem = (ThreadPoolElement *)acb;                      // (8) 0.04737
/*6  */     ThreadPool *pool = elem->pool;                                           // (15) 0.03421
/*10 */     trace_thread_pool_cancel(elem, elem->common.opaque);                     // (5) 0.06053
/*14 */     qemu_mutex_lock(&pool->lock);                                            // (14) 0.04211
/*16 */     if (elem->state == THREAD_QUEUED &&                                      // (9) 0.04737
/*18 */         /* No thread has yet started working on elem. we can try to "steal"  // (3) 0.06842
/*20 */          * the item from the worker if we can get a signal from the          // (7) 0.05789
/*22 */          * semaphore.  Because this is non-blocking, we can do it with       // (4) 0.06842
/*24 */          * the lock taken and ensure that elem will remain THREAD_QUEUED.    // (1) 0.07105
/*26 */          */                                                                  // (16) 0.02368
/*28 */         qemu_sem_timedwait(&pool->sem, 0) == 0) {                            // (2) 0.07105
/*30 */         QTAILQ_REMOVE(&pool->request_list, elem, reqs);                      // (0) 0.07368
/*32 */         qemu_bh_schedule(pool->completion_bh);                               // (6) 0.06053
/*36 */         elem->state = THREAD_DONE;                                           // (10) 0.04737
/*38 */         elem->ret = -ECANCELED;                                              // (11) 0.04737
/*40 */     }                                                                        // (17) 0.01053
/*44 */     qemu_mutex_unlock(&pool->lock);                                          // (13) 0.04474
/*46 */ }                                                                            // (19) 0.002632
