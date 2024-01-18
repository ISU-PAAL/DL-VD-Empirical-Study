// commit message qemu@3ba235a022 (target=0, prob=0.36859667, correct=True): block: Use g_new0() for a bit of extra type checking
/*0  */ QEMUBH *aio_bh_new(AioContext *ctx, QEMUBHFunc *cb, void *opaque)           // (0) 0.1449
/*2  */ {                                                                           // (13) 0.004673
/*4  */     QEMUBH *bh;                                                             // (10) 0.04673
/*6  */     bh = g_malloc0(sizeof(QEMUBH));                                         // (1) 0.09346
/*8  */     bh->ctx = ctx;                                                          // (7) 0.0514
/*10 */     bh->cb = cb;                                                            // (8) 0.0514
/*12 */     bh->opaque = opaque;                                                    // (9) 0.0514
/*14 */     qemu_mutex_lock(&ctx->bh_lock);                                         // (4) 0.08411
/*16 */     bh->next = ctx->first_bh;                                               // (5) 0.07009
/*18 */     /* Make sure that the members are ready before putting bh into list */  // (3) 0.08411
/*20 */     smp_wmb();                                                              // (11) 0.04206
/*22 */     ctx->first_bh = bh;                                                     // (6) 0.06075
/*24 */     qemu_mutex_unlock(&ctx->bh_lock);                                       // (2) 0.08879
/*26 */     return bh;                                                              // (12) 0.03271
/*28 */ }                                                                           // (14) 0.004673
