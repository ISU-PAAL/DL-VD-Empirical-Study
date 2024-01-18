// commit message qemu@61007b316c (target=0, prob=0.3186286, correct=True): block: move I/O request processing to block/io.c
/*0  */ int bdrv_write_compressed(BlockDriverState *bs, int64_t sector_num,      // (3) 0.08856
/*2  */                           const uint8_t *buf, int nb_sectors)            // (0) 0.1476
/*4  */ {                                                                        // (16) 0.00369
/*6  */     BlockDriver *drv = bs->drv;                                          // (6) 0.05535
/*8  */     int ret;                                                             // (12) 0.02214
/*12 */     if (!drv) {                                                          // (11) 0.03321
/*14 */         return -ENOMEDIUM;                                               // (7) 0.05166
/*16 */     }                                                                    // (13) 0.01476
/*18 */     if (!drv->bdrv_write_compressed) {                                   // (5) 0.06642
/*20 */         return -ENOTSUP;                                                 // (8) 0.04797
/*22 */     }                                                                    // (14) 0.01476
/*24 */     ret = bdrv_check_request(bs, sector_num, nb_sectors);                // (2) 0.09225
/*26 */     if (ret < 0) {                                                       // (9) 0.0369
/*28 */         return ret;                                                      // (10) 0.0369
/*30 */     }                                                                    // (15) 0.01476
/*34 */     assert(QLIST_EMPTY(&bs->dirty_bitmaps));                             // (4) 0.06642
/*38 */     return drv->bdrv_write_compressed(bs, sector_num, buf, nb_sectors);  // (1) 0.1107
/*40 */ }                                                                        // (17) 0.00369
