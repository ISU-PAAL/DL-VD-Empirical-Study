// commit message qemu@61007b316c (target=0, prob=0.032997616, correct=True): block: move I/O request processing to block/io.c
/*0  */ BlockAIOCB *bdrv_aio_write_zeroes(BlockDriverState *bs,                      // (5) 0.09664
/*2  */         int64_t sector_num, int nb_sectors, BdrvRequestFlags flags,          // (4) 0.1218
/*4  */         BlockCompletionFunc *cb, void *opaque)                               // (6) 0.08403
/*6  */ {                                                                            // (7) 0.004202
/*8  */     trace_bdrv_aio_write_zeroes(bs, sector_num, nb_sectors, flags, opaque);  // (2) 0.1387
/*12 */     return bdrv_co_aio_rw_vector(bs, sector_num, NULL, nb_sectors,           // (3) 0.1303
/*14 */                                  BDRV_REQ_ZERO_WRITE | flags,                // (0) 0.1975
/*16 */                                  cb, opaque, true);                          // (1) 0.1639
/*18 */ }                                                                            // (8) 0.004202
