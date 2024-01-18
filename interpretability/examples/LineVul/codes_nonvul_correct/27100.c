// commit message qemu@c2b38b277a (target=0, prob=0.073274545, correct=True): block: move AioContext, QEMUTimer, main-loop to libqemuutil
/*0  */ static bool try_poll_mode(AioContext *ctx, bool blocking)                       // (9) 0.04789
/*2  */ {                                                                               // (17) 0.002817
/*4  */     if (blocking && ctx->poll_max_ns && ctx->poll_disable_cnt == 0) {           // (2) 0.08169
/*6  */         /* See qemu_soonest_timeout() uint64_t hack */                          // (5) 0.06761
/*8  */         int64_t max_ns = MIN((uint64_t)aio_compute_timeout(ctx),                // (1) 0.09014
/*10 */                              (uint64_t)ctx->poll_ns);                           // (0) 0.1127
/*14 */         if (max_ns) {                                                           // (11) 0.03944
/*16 */             poll_set_started(ctx, true);                                        // (6) 0.05915
/*20 */             if (run_poll_handlers(ctx, max_ns)) {                               // (3) 0.07606
/*22 */                 return true;                                                    // (8) 0.0507
/*24 */             }                                                                   // (13) 0.0338
/*26 */         }                                                                       // (14) 0.02254
/*28 */     }                                                                           // (16) 0.01127
/*32 */     poll_set_started(ctx, false);                                               // (12) 0.03662
/*36 */     /* Even if we don't run busy polling, try polling once in case it can make  // (7) 0.05915
/*38 */      * progress and the caller will be able to avoid ppoll(2)/epoll_wait(2).    // (4) 0.07324
/*40 */      */                                                                         // (15) 0.01408
/*42 */     return run_poll_handlers_once(ctx);                                         // (10) 0.04225
/*44 */ }                                                                               // (18) 0.002817
