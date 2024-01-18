// commit message qemu@164a101f28 (target=1, prob=0.2828399, correct=False): aio: stop using .io_flush()
/*0  */ void aio_set_event_notifier(AioContext *ctx,                                 // (13) 0.0332
/*2  */                             EventNotifier *e,                                // (2) 0.06445
/*4  */                             EventNotifierHandler *io_notify,                 // (1) 0.07227
/*6  */                             AioFlushEventNotifierHandler *io_flush)          // (0) 0.07813
/*8  */ {                                                                            // (23) 0.001953
/*10 */     AioHandler *node;                                                        // (20) 0.01758
/*14 */     QLIST_FOREACH(node, &ctx->aio_handlers, node) {                          // (9) 0.04492
/*16 */         if (node->e == e && !node->deleted) {                                // (10) 0.04297
/*18 */             break;                                                           // (16) 0.02539
/*20 */         }                                                                    // (21) 0.01562
/*22 */     }                                                                        // (22) 0.007812
/*26 */     /* Are we deleting the fd handler? */                                    // (17) 0.02539
/*28 */     if (!io_notify) {                                                        // (19) 0.02148
/*30 */         if (node) {                                                          // (18) 0.02344
/*32 */             g_source_remove_poll(&ctx->source, &node->pfd);                  // (4) 0.05664
/*36 */             /* If the lock is held, just mark the node as deleted */         // (6) 0.04883
/*38 */             if (ctx->walking_handlers) {                                     // (12) 0.04102
/*40 */                 node->deleted = 1;                                           // (11) 0.04297
/*42 */                 node->pfd.revents = 0;                                       // (7) 0.04883
/*44 */             } else {                                                         // (15) 0.02734
/*46 */                 /* Otherwise, delete it for real.  We can't just mark it as  // (3) 0.06055
/*48 */                  * deleted because deleted nodes are only cleaned up after   // (5) 0.05078
/*50 */                  * releasing the walking_handlers lock.                      // (8) 0.04883
/*52 */                  */                                                          // (14) 0.0332
/*54 */                 QLIST_REMOVE(node, node);                                    // 0.0
/*56 */                 g_free(node);                                                // 0.0
/*58 */             }                                                                // 0.0
/*60 */         }                                                                    // 0.0
/*62 */     } else {                                                                 // 0.0
/*64 */         if (node == NULL) {                                                  // 0.0
/*66 */             /* Alloc and insert if it's not already there */                 // 0.0
/*68 */             node = g_malloc0(sizeof(AioHandler));                            // 0.0
/*70 */             node->e = e;                                                     // 0.0
/*72 */             node->pfd.fd = (uintptr_t)event_notifier_get_handle(e);          // 0.0
/*74 */             node->pfd.events = G_IO_IN;                                      // 0.0
/*76 */             QLIST_INSERT_HEAD(&ctx->aio_handlers, node, node);               // 0.0
/*80 */             g_source_add_poll(&ctx->source, &node->pfd);                     // 0.0
/*82 */         }                                                                    // 0.0
/*84 */         /* Update handler with latest information */                         // 0.0
/*86 */         node->io_notify = io_notify;                                         // 0.0
/*88 */         node->io_flush = io_flush;                                           // 0.0
/*90 */     }                                                                        // 0.0
/*94 */     aio_notify(ctx);                                                         // 0.0
/*96 */ }                                                                            // 0.0
