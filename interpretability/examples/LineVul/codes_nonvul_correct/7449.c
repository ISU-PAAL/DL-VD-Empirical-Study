// commit message qemu@d62b5dea30 (target=0, prob=0.21600334, correct=True): fix code format
/*0  */ BlockDriverAIOCB *bdrv_aio_readv(BlockDriverState *bs, int64_t sector_num,     // (4) 0.07595
/*2  */                                  QEMUIOVector *qiov, int nb_sectors,           // (0) 0.1215
/*4  */                                  BlockDriverCompletionFunc *cb, void *opaque)  // (1) 0.1165
/*6  */ {                                                                              // (18) 0.002532
/*8  */     BlockDriver *drv = bs->drv;                                                // (8) 0.03797
/*10 */     BlockDriverAIOCB *ret;                                                     // (10) 0.02785
/*14 */     trace_bdrv_aio_readv(bs, sector_num, nb_sectors, opaque);                  // (5) 0.07342
/*18 */     if (!drv)                                                                  // (13) 0.02025
/*20 */         return NULL;                                                           // (11) 0.02532
/*22 */     if (bdrv_check_request(bs, sector_num, nb_sectors))                        // (7) 0.06329
/*24 */         return NULL;                                                           // (12) 0.02532
/*28 */     ret = drv->bdrv_aio_readv(bs, sector_num, qiov, nb_sectors,                // (3) 0.08354
/*30 */                               cb, opaque);                                     // (2) 0.08608
/*34 */     if (ret) {                                                                 // (14) 0.02025
/*36 */ 	/* Update stats even though technically transfer has not happened. */         // (9) 0.03291
/*38 */ 	bs->rd_bytes += (unsigned) nb_sectors * BDRV_SECTOR_SIZE;                     // (6) 0.06582
/*40 */ 	bs->rd_ops ++;                                                                // (15) 0.02025
/*42 */     }                                                                          // (17) 0.01013
/*46 */     return ret;                                                                // (16) 0.01519
/*48 */ }                                                                              // (19) 0.002532
