// commit message qemu@0d1c5c9160 (target=0, prob=0.292794, correct=True): block: Invalidate all children
/*0  */ void bdrv_invalidate_cache(BlockDriverState *bs, Error **errp)                 // (6) 0.05226
/*2  */ {                                                                              // (26) 0.002375
/*4  */     Error *local_err = NULL;                                                   // (13) 0.02613
/*6  */     int ret;                                                                   // (20) 0.01425
/*10 */     if (!bs->drv)  {                                                           // (11) 0.0285
/*12 */         return;                                                                // (16) 0.02138
/*14 */     }                                                                          // (21) 0.009501
/*18 */     if (!(bs->open_flags & BDRV_O_INACTIVE)) {                                 // (5) 0.05463
/*20 */         return;                                                                // (17) 0.02138
/*22 */     }                                                                          // (22) 0.009501
/*24 */     bs->open_flags &= ~BDRV_O_INACTIVE;                                        // (7) 0.05226
/*28 */     if (bs->drv->bdrv_invalidate_cache) {                                      // (9) 0.04988
/*30 */         bs->drv->bdrv_invalidate_cache(bs, &local_err);                        // (0) 0.07126
/*32 */     } else if (bs->file) {                                                     // (12) 0.0285
/*34 */         bdrv_invalidate_cache(bs->file->bs, &local_err);                       // (2) 0.06651
/*36 */     }                                                                          // (23) 0.009501
/*38 */     if (local_err) {                                                           // (14) 0.02375
/*40 */         bs->open_flags |= BDRV_O_INACTIVE;                                     // (3) 0.05938
/*42 */         error_propagate(errp, local_err);                                      // (10) 0.04513
/*44 */         return;                                                                // (18) 0.02138
/*46 */     }                                                                          // (24) 0.009501
/*50 */     ret = refresh_total_sectors(bs, bs->total_sectors);                        // (8) 0.05226
/*52 */     if (ret < 0) {                                                             // (15) 0.02375
/*54 */         bs->open_flags |= BDRV_O_INACTIVE;                                     // (4) 0.05938
/*56 */         error_setg_errno(errp, -ret, "Could not refresh total sector count");  // (1) 0.06888
/*58 */         return;                                                                // (19) 0.02138
/*60 */     }                                                                          // (25) 0.009501
/*62 */ }                                                                              // (27) 0.002375
