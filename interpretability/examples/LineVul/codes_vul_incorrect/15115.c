// commit message qemu@4a1cba3802 (target=1, prob=0.33470267, correct=False): aio: add polling mode to AioContext
/*0   */ bool aio_poll(AioContext *ctx, bool blocking)                                 // (13) 0.0293
/*2   */ {                                                                             // (33) 0.001953
/*4   */     AioHandler *node;                                                         // (19) 0.01758
/*6   */     int i, ret;                                                               // (23) 0.01562
/*8   */     bool progress;                                                            // (28) 0.01172
/*10  */     int64_t timeout;                                                          // (22) 0.01758
/*14  */     aio_context_acquire(ctx);                                                 // (14) 0.02539
/*16  */     progress = false;                                                         // (27) 0.01367
/*20  */     /* aio_notify can avoid the expensive event_notifier_set if               // (4) 0.03906
/*22  */      * everything (file descriptors, bottom halves, timers) will              // (10) 0.0332
/*24  */      * be re-evaluated before the next blocking poll().  This is              // (8) 0.03711
/*26  */      * already true when aio_poll is called with blocking == false;           // (7) 0.03711
/*28  */      * if blocking == true, it is only true after poll() returns,             // (9) 0.03711
/*30  */      * so disable the optimization now.                                       // (16) 0.02148
/*32  */      */                                                                       // (29) 0.009766
/*34  */     if (blocking) {                                                           // (25) 0.01562
/*36  */         atomic_add(&ctx->notify_me, 2);                                       // (5) 0.03906
/*38  */     }                                                                         // (30) 0.007812
/*42  */     ctx->walking_handlers++;                                                  // (17) 0.02148
/*46  */     assert(npfd == 0);                                                        // (18) 0.01953
/*50  */     /* fill pollfds */                                                        // (21) 0.01758
/*54  */     if (!aio_epoll_enabled(ctx)) {                                            // (12) 0.03125
/*56  */         QLIST_FOREACH(node, &ctx->aio_handlers, node) {                       // (1) 0.05273
/*58  */             if (!node->deleted && node->pfd.events                            // (2) 0.04687
/*60  */                 && aio_node_check(ctx, node->is_external)) {                  // (0) 0.0625
/*62  */                 add_pollfd(node);                                             // (3) 0.04297
/*64  */             }                                                                 // (15) 0.02344
/*66  */         }                                                                     // (26) 0.01562
/*68  */     }                                                                         // (31) 0.007812
/*72  */     timeout = blocking ? aio_compute_timeout(ctx) : 0;                        // (6) 0.03906
/*76  */     /* wait until next event */                                               // (20) 0.01758
/*78  */     if (timeout) {                                                            // (24) 0.01562
/*80  */         aio_context_release(ctx);                                             // (11) 0.03125
/*82  */     }                                                                         // (32) 0.007812
/*84  */     if (aio_epoll_check_poll(ctx, pollfds, npfd, timeout)) {                  // 0.0
/*86  */         AioHandler epoll_handler;                                             // 0.0
/*90  */         epoll_handler.pfd.fd = ctx->epollfd;                                  // 0.0
/*92  */         epoll_handler.pfd.events = G_IO_IN | G_IO_OUT | G_IO_HUP | G_IO_ERR;  // 0.0
/*94  */         npfd = 0;                                                             // 0.0
/*96  */         add_pollfd(&epoll_handler);                                           // 0.0
/*98  */         ret = aio_epoll(ctx, pollfds, npfd, timeout);                         // 0.0
/*100 */     } else  {                                                                 // 0.0
/*102 */         ret = qemu_poll_ns(pollfds, npfd, timeout);                           // 0.0
/*104 */     }                                                                         // 0.0
/*106 */     if (blocking) {                                                           // 0.0
/*108 */         atomic_sub(&ctx->notify_me, 2);                                       // 0.0
/*110 */     }                                                                         // 0.0
/*112 */     if (timeout) {                                                            // 0.0
/*114 */         aio_context_acquire(ctx);                                             // 0.0
/*116 */     }                                                                         // 0.0
/*120 */     aio_notify_accept(ctx);                                                   // 0.0
/*124 */     /* if we have any readable fds, dispatch event */                         // 0.0
/*126 */     if (ret > 0) {                                                            // 0.0
/*128 */         for (i = 0; i < npfd; i++) {                                          // 0.0
/*130 */             nodes[i]->pfd.revents = pollfds[i].revents;                       // 0.0
/*132 */         }                                                                     // 0.0
/*134 */     }                                                                         // 0.0
/*138 */     npfd = 0;                                                                 // 0.0
/*140 */     ctx->walking_handlers--;                                                  // 0.0
/*144 */     /* Run dispatch even if there were no readable fds to run timers */       // 0.0
/*146 */     if (aio_dispatch(ctx, ret > 0)) {                                         // 0.0
/*148 */         progress = true;                                                      // 0.0
/*150 */     }                                                                         // 0.0
/*154 */     aio_context_release(ctx);                                                 // 0.0
/*158 */     return progress;                                                          // 0.0
/*160 */ }                                                                             // 0.0
