// commit message qemu@c6d2283068 (target=1, prob=0.27444968, correct=False): block migration: Cleanup dirty tracking code
/*0  */ BlockDriverAIOCB *bdrv_aio_writev(BlockDriverState *bs, int64_t sector_num,     // (4) 0.06849
/*2  */                                   QEMUIOVector *qiov, int nb_sectors,           // (0) 0.1119
/*4  */                                   BlockDriverCompletionFunc *cb, void *opaque)  // (1) 0.1073
/*6  */ {                                                                               // (22) 0.002283
/*8  */     BlockDriver *drv = bs->drv;                                                 // (8) 0.03425
/*10 */     BlockDriverAIOCB *ret;                                                      // (11) 0.02511
/*14 */     if (!drv)                                                                   // (16) 0.01826
/*16 */         return NULL;                                                            // (13) 0.02283
/*18 */     if (bs->read_only)                                                          // (12) 0.02511
/*20 */         return NULL;                                                            // (14) 0.02283
/*22 */     if (bdrv_check_request(bs, sector_num, nb_sectors))                         // (7) 0.05708
/*24 */         return NULL;                                                            // (15) 0.02283
/*28 */     if (bs->dirty_tracking) {                                                   // (10) 0.0274
/*30 */         set_dirty_bitmap(bs, sector_num, nb_sectors, 1);                        // (5) 0.06393
/*32 */     }                                                                           // (20) 0.009132
/*36 */     ret = drv->bdrv_aio_writev(bs, sector_num, qiov, nb_sectors,                // (3) 0.07534
/*38 */                                cb, opaque);                                     // (2) 0.07991
/*42 */     if (ret) {                                                                  // (17) 0.01826
/*44 */ 	/* Update stats even though technically transfer has not happened. */          // (9) 0.02968
/*46 */ 	bs->wr_bytes += (unsigned) nb_sectors * BDRV_SECTOR_SIZE;                      // (6) 0.05936
/*48 */ 	bs->wr_ops ++;                                                                 // (18) 0.01826
/*50 */     }                                                                           // (21) 0.009132
/*54 */     return ret;                                                                 // (19) 0.0137
/*56 */ }                                                                               // (23) 0.002283
