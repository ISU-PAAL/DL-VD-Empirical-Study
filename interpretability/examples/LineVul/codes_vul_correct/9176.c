// commit message qemu@71d0770c4c (target=1, prob=0.99901164, correct=True): Fix CVE-2008-0928 - insufficient block device address range checking (Anthony Liguori)
/*0 */ int bdrv_pread(BlockDriverState *bs, int64_t offset,     // (3) 0.1226
/*1 */                void *buf1, int count1)                   // (1) 0.1484
/*2 */ {                                                        // (8) 0.006452
/*3 */     BlockDriver *drv = bs->drv;                          // (4) 0.09677
/*4 */     if (!drv)                                            // (7) 0.05161
/*5 */         return -ENOMEDIUM;                               // (5) 0.09032
/*6 */     if (!drv->bdrv_pread)                                // (6) 0.09032
/*7 */         return bdrv_pread_em(bs, offset, buf1, count1);  // (0) 0.1677
/*8 */     return drv->bdrv_pread(bs, offset, buf1, count1);    // (2) 0.1484
/*9 */ }                                                        // (9) 0.006452
