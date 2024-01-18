// commit message qemu@a03ef88f77 (target=0, prob=0.01131847, correct=True): block: Convert bdrv_co_preadv/pwritev to BdrvChild
/*0  */ static int coroutine_fn bdrv_co_do_readv(BdrvChild *child,               // (4) 0.1165
/*2  */     int64_t sector_num, int nb_sectors, QEMUIOVector *qiov,              // (3) 0.1311
/*4  */     BdrvRequestFlags flags)                                              // (6) 0.04854
/*6  */ {                                                                        // (8) 0.004854
/*8  */     if (nb_sectors < 0 || nb_sectors > BDRV_REQUEST_MAX_SECTORS) {       // (2) 0.1553
/*10 */         return -EINVAL;                                                  // (5) 0.06311
/*12 */     }                                                                    // (7) 0.01942
/*16 */     return bdrv_co_preadv(child->bs, sector_num << BDRV_SECTOR_BITS,     // (1) 0.1553
/*18 */                           nb_sectors << BDRV_SECTOR_BITS, qiov, flags);  // (0) 0.2282
/*20 */ }                                                                        // (9) 0.004854
