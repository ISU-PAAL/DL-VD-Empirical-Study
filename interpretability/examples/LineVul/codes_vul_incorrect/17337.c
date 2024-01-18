// commit message qemu@71d0770c4c (target=1, prob=0.4390091, correct=False): Fix CVE-2008-0928 - insufficient block device address range checking (Anthony Liguori)
/*0  */ int bdrv_read(BlockDriverState *bs, int64_t sector_num,          // (3) 0.0614
/*2  */               uint8_t *buf, int nb_sectors)                      // (2) 0.07895
/*4  */ {                                                                // (21) 0.002924
/*6  */     BlockDriver *drv = bs->drv;                                  // (7) 0.04386
/*10 */     if (!drv)                                                    // (17) 0.02339
/*12 */         return -ENOMEDIUM;                                       // (9) 0.04094
/*18 */     if (drv->bdrv_pread) {                                       // (8) 0.04386
/*20 */         int ret, len;                                            // (14) 0.03509
/*22 */         len = nb_sectors * 512;                                  // (4) 0.04971
/*24 */         ret = drv->bdrv_pread(bs, sector_num * 512, buf, len);   // (1) 0.08772
/*26 */         if (ret < 0)                                             // (13) 0.03801
/*28 */             return ret;                                          // (10) 0.04094
/*30 */         else if (ret != len)                                     // (11) 0.04094
/*32 */             return -EINVAL;                                      // (5) 0.04971
/*34 */         else {                                                   // (16) 0.02632
/*36 */ 	    bs->rd_bytes += (unsigned) len;                             // (6) 0.04678
/*38 */ 	    bs->rd_ops ++;                                              // (15) 0.03509
/*40 */             return 0;                                            // (12) 0.04094
/*42 */ 	}                                                               // (20) 0.005848
/*44 */     } else {                                                     // (18) 0.01754
/*46 */         return drv->bdrv_read(bs, sector_num, buf, nb_sectors);  // (0) 0.09064
/*48 */     }                                                            // (19) 0.0117
/*50 */ }                                                                // (22) 0.002924
