// commit message qemu@0b8b8753e4 (target=1, prob=0.37320843, correct=False): coroutine: move entry argument to qemu_coroutine_create
/*0  */ static BlockAIOCB *bdrv_co_aio_rw_vector(BdrvChild *child,              // (8) 0.05078
/*2  */                                          int64_t sector_num,            // (2) 0.09375
/*4  */                                          QEMUIOVector *qiov,            // (0) 0.0957
/*6  */                                          int nb_sectors,                // (3) 0.0918
/*8  */                                          BdrvRequestFlags flags,        // (4) 0.0918
/*10 */                                          BlockCompletionFunc *cb,       // (1) 0.09375
/*12 */                                          void *opaque,                  // (6) 0.08789
/*14 */                                          bool is_write)                 // (5) 0.08789
/*16 */ {                                                                       // (16) 0.001953
/*18 */     Coroutine *co;                                                      // (15) 0.01563
/*20 */     BlockAIOCBCoroutine *acb;                                           // (12) 0.02539
/*24 */     acb = qemu_aio_get(&bdrv_em_co_aiocb_info, child->bs, cb, opaque);  // (7) 0.07422
/*26 */     acb->child = child;                                                 // (14) 0.01953
/*28 */     acb->need_bh = true;                                                // (13) 0.02344
/*30 */     acb->req.error = -EINPROGRESS;                                      // (10) 0.0332
/*32 */     acb->req.sector = sector_num;                                       // (11) 0.02734
/*34 */     acb->req.nb_sectors = nb_sectors;                                   // (9) 0.03711
/*36 */     acb->req.qiov = qiov;                                               // 0.0
/*38 */     acb->req.flags = flags;                                             // 0.0
/*40 */     acb->is_write = is_write;                                           // 0.0
/*44 */     co = qemu_coroutine_create(bdrv_co_do_rw);                          // 0.0
/*46 */     qemu_coroutine_enter(co, acb);                                      // 0.0
/*50 */     bdrv_co_maybe_schedule_bh(acb);                                     // 0.0
/*52 */     return &acb->common;                                                // 0.0
/*54 */ }                                                                       // 0.0
