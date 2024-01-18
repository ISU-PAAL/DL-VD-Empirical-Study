// commit message qemu@684e508c23 (target=1, prob=0.029736767, correct=False): aio: add .io_poll_begin/end() callbacks
/*0  */ static bool try_poll_mode(AioContext *ctx, bool blocking)              // (6) 0.06667
/*2  */ {                                                                      // (12) 0.003922
/*4  */     if (blocking && ctx->poll_max_ns && ctx->poll_disable_cnt == 0) {  // (2) 0.1137
/*6  */         /* See qemu_soonest_timeout() uint64_t hack */                 // (4) 0.09412
/*8  */         int64_t max_ns = MIN((uint64_t)aio_compute_timeout(ctx),       // (1) 0.1255
/*10 */                              (uint64_t)ctx->poll_max_ns);              // (0) 0.1647
/*14 */         if (max_ns) {                                                  // (7) 0.0549
/*16 */             if (run_poll_handlers(ctx, max_ns)) {                      // (3) 0.1059
/*18 */                 return true;                                           // (5) 0.07059
/*20 */             }                                                          // (8) 0.04706
/*22 */         }                                                              // (9) 0.03137
/*24 */     }                                                                  // (11) 0.01569
/*28 */     return false;                                                      // (10) 0.02353
/*30 */ }                                                                      // (13) 0.003922
