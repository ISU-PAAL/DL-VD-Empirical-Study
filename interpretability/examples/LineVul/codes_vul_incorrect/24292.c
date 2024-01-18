// commit message qemu@a77fd4bb29 (target=1, prob=0.28867188, correct=False): block: Fix bdrv_drain in coroutine
/*0  */ void bdrv_drain(BlockDriverState *bs)                       // (4) 0.09524
/*2  */ {                                                           // (8) 0.006803
/*4  */     bool busy = true;                                       // (7) 0.05442
/*8  */     bdrv_drain_recurse(bs);                                 // (3) 0.102
/*14 */     while (busy) {                                          // (6) 0.06122
/*16 */         /* Keep iterating */                                // (5) 0.08163
/*18 */          bdrv_flush_io_queue(bs);                           // (2) 0.1361
/*20 */          busy = bdrv_requests_pending(bs);                  // (1) 0.1497
/*22 */          busy |= aio_poll(bdrv_get_aio_context(bs), busy);  // (0) 0.2109
