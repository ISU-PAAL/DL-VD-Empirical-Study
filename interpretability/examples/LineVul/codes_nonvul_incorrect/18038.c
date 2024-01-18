// commit message qemu@c2b38b277a (target=0, prob=0.6247554, correct=False): block: move AioContext, QEMUTimer, main-loop to libqemuutil
/*0  */ void qemu_bh_schedule(QEMUBH *bh)                                              // (5) 0.08252
/*2  */ {                                                                              // (13) 0.004854
/*4  */     AioContext *ctx;                                                           // (10) 0.04369
/*8  */     ctx = bh->ctx;                                                             // (7) 0.0534
/*10 */     bh->idle = 0;                                                              // (8) 0.0534
/*12 */     /* The memory barrier implicit in atomic_xchg makes sure that:             // (4) 0.08738
/*14 */      * 1. idle & any writes needed by the callback are done before the         // (3) 0.09223
/*16 */      *    locations are read in the aio_bh_poll.                               // (2) 0.09709
/*18 */      * 2. ctx is loaded before scheduled is set and the callback has a chance  // (1) 0.1019
/*20 */      *    to execute.                                                          // (9) 0.0534
/*22 */      */                                                                        // (11) 0.02427
/*24 */     if (atomic_xchg(&bh->scheduled, 1) == 0) {                                 // (0) 0.1117
/*26 */         aio_notify(ctx);                                                       // (6) 0.07282
/*28 */     }                                                                          // (12) 0.01942
/*30 */ }                                                                              // (14) 0.004854
