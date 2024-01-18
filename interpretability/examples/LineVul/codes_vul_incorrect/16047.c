// commit message qemu@b5eff35546 (target=1, prob=0.3623397, correct=False): Revert fix for CVE-2008-0928. Will be fixed in a different way later.
/*0  */ int bdrv_pwrite(BlockDriverState *bs, int64_t offset,     // (4) 0.09901
/*2  */                 const void *buf1, int count1)             // (1) 0.1238
/*4  */ {                                                         // (10) 0.00495
/*6  */     BlockDriver *drv = bs->drv;                           // (5) 0.07426
/*10 */     if (!drv)                                             // (9) 0.0396
/*12 */         return -ENOMEDIUM;                                // (7) 0.06931
/*14 */     if (!drv->bdrv_pwrite)                                // (6) 0.07426
/*16 */         return bdrv_pwrite_em(bs, offset, buf1, count1);  // (0) 0.1337
/*18 */     if (bdrv_wr_badreq_bytes(bs, offset, count1))         // (3) 0.1139
/*20 */         return -EDOM;                                     // (8) 0.05941
/*22 */     return drv->bdrv_pwrite(bs, offset, buf1, count1);    // (2) 0.1188
/*24 */ }                                                         // (11) 0.00495
