// commit message qemu@c2b38b277a (target=0, prob=0.11970697, correct=True): block: move AioContext, QEMUTimer, main-loop to libqemuutil
/*0  */ bool aio_pending(AioContext *ctx)                                    // (10) 0.03457
/*2  */ {                                                                    // (24) 0.00266
/*4  */     AioHandler *node;                                                // (15) 0.02394
/*6  */     bool result = false;                                             // (16) 0.02128
/*10 */     /*                                                               // (22) 0.01064
/*12 */      * We have to walk very carefully in case aio_set_fd_handler is  // (4) 0.05851
/*14 */      * called while we're walking.                                   // (14) 0.02926
/*16 */      */                                                              // (21) 0.0133
/*18 */     qemu_lockcnt_inc(&ctx->list_lock);                               // (5) 0.05053
/*20 */     QLIST_FOREACH_RCU(node, &ctx->aio_handlers, node) {              // (2) 0.06915
/*22 */         if (node->pfd.revents && node->io_notify) {                  // (3) 0.06649
/*24 */             result = true;                                           // (7) 0.03989
/*26 */             break;                                                   // (11) 0.03457
/*28 */         }                                                            // (17) 0.02128
/*32 */         if ((node->pfd.revents & G_IO_IN) && node->io_read) {        // (0) 0.08245
/*34 */             result = true;                                           // (8) 0.03989
/*36 */             break;                                                   // (12) 0.03457
/*38 */         }                                                            // (18) 0.02128
/*40 */         if ((node->pfd.revents & G_IO_OUT) && node->io_write) {      // (1) 0.08245
/*42 */             result = true;                                           // (9) 0.03989
/*44 */             break;                                                   // (13) 0.03457
/*46 */         }                                                            // (19) 0.02128
/*48 */     }                                                                // (23) 0.01064
/*52 */     qemu_lockcnt_dec(&ctx->list_lock);                               // (6) 0.05053
/*54 */     return result;                                                   // (20) 0.01596
/*56 */ }                                                                    // (25) 0.00266
