// commit message qemu@9ef91a6771 (target=0, prob=0.022684116, correct=True): raw-posix: refactor AIO support
/*0  */ static BlockDriverAIOCB *raw_aio_writev(BlockDriverState *bs,           // (3) 0.09502
/*2  */         int64_t sector_num, QEMUIOVector *qiov, int nb_sectors,         // (1) 0.1403
/*4  */         BlockDriverCompletionFunc *cb, void *opaque)                    // (4) 0.09502
/*6  */ {                                                                       // (12) 0.004525
/*8  */     RawAIOCB *acb;                                                      // (6) 0.04977
/*12 */     acb = raw_aio_setup(bs, sector_num, qiov, nb_sectors, cb, opaque);  // (0) 0.1493
/*14 */     if (!acb)                                                           // (10) 0.0362
/*16 */         return NULL;                                                    // (7) 0.04525
/*18 */     if (qemu_paio_write(&acb->aiocb) < 0) {                             // (2) 0.1086
/*20 */         raw_aio_remove(acb);                                            // (5) 0.07692
/*22 */         return NULL;                                                    // (8) 0.04525
/*24 */     }                                                                   // (11) 0.0181
/*26 */     return &acb->common;                                                // (9) 0.04525
/*28 */ }                                                                       // (13) 0.004525
