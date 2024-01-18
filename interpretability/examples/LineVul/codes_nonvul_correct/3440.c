// commit message qemu@a27365265c (target=0, prob=0.011321789, correct=True): raw-win32: implement native asynchronous I/O
/*0  */ static BlockDriverAIOCB *raw_aio_readv(BlockDriverState *bs,                      // (4) 0.1034
/*2  */                          int64_t sector_num, QEMUIOVector *qiov, int nb_sectors,  // (0) 0.2365
/*4  */                          BlockDriverCompletionFunc *cb, void *opaque)             // (1) 0.1872
/*6  */ {                                                                                 // (6) 0.004926
/*8  */     BDRVRawState *s = bs->opaque;                                                 // (5) 0.08374
/*10 */     return paio_submit(bs, s->hfile, sector_num, qiov, nb_sectors,                // (3) 0.1429
/*12 */                        cb, opaque, QEMU_AIO_READ);                                // (2) 0.1773
/*14 */ }                                                                                 // (7) 0.004926
