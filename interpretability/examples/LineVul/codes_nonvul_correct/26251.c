// commit message qemu@f8c35c1d59 (target=0, prob=0.3252229, correct=True): block: drop .bdrv_read()/.bdrv_write() emulation
/*0  */ static int bdrv_read_em(BlockDriverState *bs, int64_t sector_num,     // (4) 0.06234
/*2  */                         uint8_t *buf, int nb_sectors)                 // (2) 0.0961
/*4  */ {                                                                     // (21) 0.002597
/*6  */     int async_ret;                                                    // (16) 0.02078
/*8  */     BlockDriverAIOCB *acb;                                            // (10) 0.03117
/*10 */     struct iovec iov;                                                 // (14) 0.02597
/*12 */     QEMUIOVector qiov;                                                // (12) 0.02857
/*16 */     async_ret = NOT_DONE;                                             // (11) 0.03117
/*18 */     iov.iov_base = (void *)buf;                                       // (8) 0.03896
/*20 */     iov.iov_len = nb_sectors * BDRV_SECTOR_SIZE;                      // (3) 0.06753
/*22 */     qemu_iovec_init_external(&qiov, &iov, 1);                         // (5) 0.05974
/*26 */     acb = bs->drv->bdrv_aio_readv(bs, sector_num, &qiov, nb_sectors,  // (1) 0.0987
/*28 */                                   bdrv_rw_em_cb, &async_ret);         // (0) 0.1273
/*30 */     if (acb == NULL) {                                                // (13) 0.02857
/*32 */         async_ret = -1;                                               // (9) 0.03636
/*34 */         goto fail;                                                    // (15) 0.02597
/*36 */     }                                                                 // (18) 0.01039
/*40 */     while (async_ret == NOT_DONE) {                                   // (6) 0.04156
/*42 */         qemu_aio_wait();                                              // (7) 0.04156
/*44 */     }                                                                 // (19) 0.01039
/*50 */ fail:                                                                 // (20) 0.005195
/*52 */     return async_ret;                                                 // (17) 0.02078
/*54 */ }                                                                     // (22) 0.002597
