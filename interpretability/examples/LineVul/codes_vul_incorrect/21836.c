// commit message qemu@147dfab747 (target=1, prob=0.023105824, correct=False): aio-posix: Change CONFIG_EPOLL to CONFIG_EPOLL_CREATE1
/*0  */ void aio_context_setup(AioContext *ctx, Error **errp)  // (1) 0.131
/*2  */ {                                                      // (11) 0.006897
/*4  */ #ifdef CONFIG_EPOLL                                    // (6) 0.05517
/*6  */     assert(!ctx->epollfd);                             // (5) 0.08276
/*8  */     ctx->epollfd = epoll_create1(EPOLL_CLOEXEC);       // (0) 0.1724
/*10 */     if (ctx->epollfd == -1) {                          // (4) 0.1034
/*12 */         ctx->epoll_available = false;                  // (2) 0.1172
/*14 */     } else {                                           // (7) 0.04138
/*16 */         ctx->epoll_available = true;                   // (3) 0.1172
/*18 */     }                                                  // (8) 0.02759
/*20 */ #endif                                                 // (9) 0.01379
/*22 */ }                                                      // (10) 0.006897
