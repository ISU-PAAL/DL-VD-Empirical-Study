// commit message qemu@3c529d9359 (target=0, prob=0.31611714, correct=True): Replace posix-aio with custom thread pool
/*0  */ static BlockDriverAIOCB *raw_aio_read(BlockDriverState *bs,                 // (8) 0.04405
/*2  */         int64_t sector_num, uint8_t *buf, int nb_sectors,                   // (3) 0.06388
/*4  */         BlockDriverCompletionFunc *cb, void *opaque)                        // (6) 0.04626
/*6  */ {                                                                           // (25) 0.002203
/*8  */     RawAIOCB *acb;                                                          // (15) 0.02423
/*12 */     /*                                                                      // (22) 0.008811
/*14 */      * If O_DIRECT is used and the buffer is not aligned fall back          // (9) 0.04405
/*16 */      * to synchronous IO.                                                   // (16) 0.02203
/*18 */      */                                                                     // (21) 0.01101
/*20 */     BDRVRawState *s = bs->opaque;                                           // (12) 0.03744
/*24 */     if (unlikely(s->aligned_buf != NULL && ((uintptr_t) buf % 512))) {      // (4) 0.05947
/*26 */         QEMUBH *bh;                                                         // (13) 0.03084
/*28 */         acb = qemu_aio_get(bs, cb, opaque);                                 // (5) 0.05727
/*30 */         acb->ret = raw_pread(bs, 512 * sector_num, buf, 512 * nb_sectors);  // (0) 0.07489
/*32 */         bh = qemu_bh_new(raw_aio_em_cb, acb);                               // (2) 0.06608
/*34 */         qemu_bh_schedule(bh);                                               // (11) 0.03965
/*36 */         return &acb->common;                                                // (14) 0.03084
/*38 */     }                                                                       // (23) 0.008811
/*42 */     acb = raw_aio_setup(bs, sector_num, buf, nb_sectors, cb, opaque);       // (1) 0.07048
/*44 */     if (!acb)                                                               // (20) 0.01762
/*46 */         return NULL;                                                        // (17) 0.02203
/*48 */     if (aio_read(&acb->aiocb) < 0) {                                        // (7) 0.04626
/*50 */         qemu_aio_release(acb);                                              // (10) 0.04185
/*52 */         return NULL;                                                        // (18) 0.02203
/*54 */     }                                                                       // (24) 0.008811
/*56 */     return &acb->common;                                                    // (19) 0.02203
/*58 */ }                                                                           // (26) 0.002203
