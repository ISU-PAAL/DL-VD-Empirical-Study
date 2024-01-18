// commit message qemu@a89d89d3e6 (target=1, prob=0.08412261, correct=False): snapshot: distinguish id and name in snapshot delete
/*0  */ int bdrv_snapshot_delete(BlockDriverState *bs, const char *snapshot_id)  // (2) 0.1319
/*2  */ {                                                                        // (12) 0.005495
/*4  */     BlockDriver *drv = bs->drv;                                          // (4) 0.08242
/*6  */     if (!drv) {                                                          // (7) 0.04945
/*8  */         return -ENOMEDIUM;                                               // (5) 0.07692
/*10 */     }                                                                    // (9) 0.02198
/*12 */     if (drv->bdrv_snapshot_delete) {                                     // (3) 0.0989
/*14 */         return drv->bdrv_snapshot_delete(bs, snapshot_id);               // (0) 0.1429
/*16 */     }                                                                    // (10) 0.02198
/*18 */     if (bs->file) {                                                      // (6) 0.05495
/*20 */         return bdrv_snapshot_delete(bs->file, snapshot_id);              // (1) 0.1374
/*22 */     }                                                                    // (11) 0.02198
/*24 */     return -ENOTSUP;                                                     // (8) 0.04945
/*26 */ }                                                                        // (13) 0.005495
