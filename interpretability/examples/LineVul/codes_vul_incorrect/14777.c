// commit message qemu@684e508c23 (target=1, prob=0.24250342, correct=False): aio: add .io_poll_begin/end() callbacks
/*0  */ static bool run_poll_handlers(AioContext *ctx, int64_t max_ns)                 // (6) 0.05867
/*2  */ {                                                                              // (20) 0.002551
/*4  */     bool progress = false;                                                     // (16) 0.02041
/*6  */     int64_t end_time;                                                          // (15) 0.02806
/*10 */     assert(ctx->notify_me);                                                    // (13) 0.03061
/*12 */     assert(ctx->walking_handlers > 0);                                         // (11) 0.03571
/*14 */     assert(ctx->poll_disable_cnt == 0);                                        // (10) 0.04082
/*18 */     trace_run_poll_handlers_begin(ctx, max_ns);                                // (7) 0.05102
/*22 */     end_time = qemu_clock_get_ns(QEMU_CLOCK_REALTIME) + max_ns;                // (1) 0.08418
/*26 */     do {                                                                       // (19) 0.01276
/*28 */         AioHandler *node;                                                      // (12) 0.03316
/*32 */         QLIST_FOREACH(node, &ctx->aio_handlers, node) {                        // (2) 0.06888
/*34 */             if (!node->deleted && node->io_poll &&                             // (5) 0.06122
/*36 */                 node->io_poll(node->opaque)) {                                 // (3) 0.06888
/*38 */                 progress = true;                                               // (8) 0.04847
/*40 */             }                                                                  // (14) 0.03061
/*44 */             /* Caller handles freeing deleted nodes.  Don't do it here. */     // (4) 0.06633
/*46 */         }                                                                      // (17) 0.02041
/*48 */     } while (!progress && qemu_clock_get_ns(QEMU_CLOCK_REALTIME) < end_time);  // (0) 0.08673
/*52 */     trace_run_poll_handlers_end(ctx, progress);                                // (9) 0.04592
/*56 */     return progress;                                                           // (18) 0.01531
/*58 */ }                                                                              // (21) 0.002551
