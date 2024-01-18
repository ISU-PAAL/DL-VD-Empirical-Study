// commit message qemu@c2b38b277a (target=0, prob=0.019149207, correct=True): block: move AioContext, QEMUTimer, main-loop to libqemuutil
/*0  */ static AioHandler *find_aio_handler(AioContext *ctx, int fd)  // (1) 0.1606
/*2  */ {                                                             // (8) 0.007299
/*4  */     AioHandler *node;                                         // (5) 0.06569
/*8  */     QLIST_FOREACH(node, &ctx->aio_handlers, node) {           // (0) 0.1679
/*10 */         if (node->pfd.fd == fd)                               // (2) 0.1387
/*12 */             if (!node->deleted)                               // (3) 0.1314
/*14 */                 return node;                                  // (4) 0.1314
/*16 */     }                                                         // (7) 0.0292
/*20 */     return NULL;                                              // (6) 0.0438
/*22 */ }                                                             // (9) 0.007299
