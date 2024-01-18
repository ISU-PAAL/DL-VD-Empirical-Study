// commit message qemu@acfb23ad3d (target=0, prob=0.44514325, correct=True): AioContext: do not rely on aio_poll(ctx, true) result to end a loop
/*0  */ static void *iothread_run(void *opaque)                                 // (8) 0.05405
/*2  */ {                                                                       // (15) 0.003861
/*4  */     IOThread *iothread = opaque;                                        // (10) 0.04633
/*8  */     qemu_mutex_lock(&iothread->init_done_lock);                         // (3) 0.08494
/*10 */     iothread->thread_id = qemu_get_thread_id();                         // (4) 0.08108
/*12 */     qemu_cond_signal(&iothread->init_done_cond);                        // (2) 0.08494
/*14 */     qemu_mutex_unlock(&iothread->init_done_lock);                       // (1) 0.0888
/*18 */     while (!iothread->stopping) {                                       // (9) 0.05019
/*20 */         aio_context_acquire(iothread->ctx);                             // (5) 0.08108
/*22 */         while (!iothread->stopping && aio_poll(iothread->ctx, true)) {  // (0) 0.1158
/*24 */             /* Progress was made, keep going */                         // (7) 0.07336
/*26 */         }                                                               // (11) 0.03089
/*28 */         aio_context_release(iothread->ctx);                             // (6) 0.07722
/*30 */     }                                                                   // (13) 0.01544
/*32 */     return NULL;                                                        // (12) 0.02317
/*34 */ }                                                                       // (14) 0.003861
