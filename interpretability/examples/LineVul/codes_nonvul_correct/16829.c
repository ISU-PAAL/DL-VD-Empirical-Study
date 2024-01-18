// commit message qemu@c2b38b277a (target=0, prob=0.090389766, correct=True): block: move AioContext, QEMUTimer, main-loop to libqemuutil
/*0  */ static bool aio_epoll_check_poll(AioContext *ctx, GPollFD *pfds,  // (1) 0.102
/*2  */                                  unsigned npfd, int64_t timeout)  // (0) 0.1647
/*4  */ {                                                                 // (16) 0.003922
/*6  */     if (!ctx->epoll_available) {                                  // (7) 0.05098
/*8  */         return false;                                             // (8) 0.03922
/*10 */     }                                                             // (13) 0.01569
/*12 */     if (aio_epoll_enabled(ctx)) {                                 // (5) 0.06275
/*14 */         return true;                                              // (9) 0.03922
/*16 */     }                                                             // (14) 0.01569
/*18 */     if (npfd >= EPOLL_ENABLE_THRESHOLD) {                         // (3) 0.08235
/*20 */         if (aio_epoll_try_enable(ctx)) {                          // (2) 0.08627
/*22 */             return true;                                          // (6) 0.0549
/*24 */         } else {                                                  // (10) 0.03922
/*26 */             aio_epoll_disable(ctx);                               // (4) 0.08235
/*28 */         }                                                         // (11) 0.03137
/*30 */     }                                                             // (15) 0.01569
/*32 */     return false;                                                 // (12) 0.02353
/*34 */ }                                                                 // (17) 0.003922
