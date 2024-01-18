// commit message qemu@c2b38b277a (target=0, prob=0.11460996, correct=True): block: move AioContext, QEMUTimer, main-loop to libqemuutil
/*0  */ aio_compute_timeout(AioContext *ctx)                           // (12) 0.03562
/*2  */ {                                                              // (24) 0.002545
/*4  */     int64_t deadline;                                          // (18) 0.0229
/*6  */     int timeout = -1;                                          // (19) 0.0229
/*8  */     QEMUBH *bh;                                                // (16) 0.02545
/*12 */     for (bh = atomic_rcu_read(&ctx->first_bh); bh;             // (2) 0.05852
/*14 */          bh = atomic_rcu_read(&bh->next)) {                    // (3) 0.05852
/*16 */         if (bh->scheduled) {                                   // (11) 0.04071
/*18 */             if (bh->idle) {                                    // (7) 0.04835
/*20 */                 /* idle bottom halves will be polled at least  // (1) 0.06107
/*22 */                  * every 10ms */                               // (4) 0.05344
/*24 */                 timeout = 10000000;                            // (6) 0.05089
/*26 */             } else {                                           // (13) 0.03562
/*28 */                 /* non-idle bottom halves will be executed     // (0) 0.06361
/*30 */                  * immediately */                              // (8) 0.04835
/*32 */                 return 0;                                      // (10) 0.0458
/*34 */             }                                                  // (14) 0.03053
/*36 */         }                                                      // (20) 0.02036
/*38 */     }                                                          // (22) 0.01018
/*42 */     deadline = timerlistgroup_deadline_ns(&ctx->tlg);          // (9) 0.04835
/*44 */     if (deadline == 0) {                                       // (15) 0.02799
/*46 */         return 0;                                              // (17) 0.02545
/*48 */     } else {                                                   // (21) 0.01527
/*50 */         return qemu_soonest_timeout(timeout, deadline);        // (5) 0.05344
/*52 */     }                                                          // (23) 0.01018
/*54 */ }                                                              // (25) 0.002545
