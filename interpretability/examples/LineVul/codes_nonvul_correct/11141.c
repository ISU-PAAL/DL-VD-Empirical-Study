// commit message qemu@cb2e28780c (target=0, prob=0.31301603, correct=True): block: Perform copy-on-read in loop
/*0   */ static int coroutine_fn bdrv_co_do_pwrite_zeroes(BlockDriverState *bs,           // (4) 0.05078
/*2   */     int64_t offset, int bytes, BdrvRequestFlags flags)                           // (11) 0.03711
/*4   */ {                                                                                // (26) 0.001954
/*6   */     BlockDriver *drv = bs->drv;                                                  // (12) 0.0293
/*8   */     QEMUIOVector qiov;                                                           // (18) 0.02148
/*10  */     struct iovec iov = {0};                                                      // (14) 0.02539
/*12  */     int ret = 0;                                                                 // (23) 0.01562
/*14  */     bool need_flush = false;                                                     // (20) 0.01953
/*16  */     int head = 0;                                                                // (24) 0.01562
/*18  */     int tail = 0;                                                                // (25) 0.01562
/*22  */     int max_write_zeroes = MIN_NON_ZERO(bs->bl.max_pwrite_zeroes, INT_MAX);      // (1) 0.06836
/*24  */     int alignment = MAX(bs->bl.pwrite_zeroes_alignment,                          // (9) 0.04102
/*26  */                         bs->bl.request_alignment);                               // (2) 0.06445
/*28  */     int max_transfer = MIN_NON_ZERO(bs->bl.max_transfer,                         // (6) 0.04687
/*30  */                                     MAX_WRITE_ZEROES_BOUNCE_BUFFER);             // (0) 0.09961
/*34  */     assert(alignment % bs->bl.request_alignment == 0);                           // (10) 0.03906
/*36  */     head = offset % alignment;                                                   // (21) 0.01758
/*38  */     tail = (offset + bytes) % alignment;                                         // (15) 0.02539
/*40  */     max_write_zeroes = QEMU_ALIGN_DOWN(max_write_zeroes, alignment);             // (3) 0.05469
/*42  */     assert(max_write_zeroes >= bs->bl.request_alignment);                        // (8) 0.04297
/*46  */     while (bytes > 0 && !ret) {                                                  // (13) 0.02539
/*48  */         int num = bytes;                                                         // (16) 0.02344
/*52  */         /* Align request.  Block drivers can expect the "bulk" of the request    // (5) 0.04883
/*54  */          * to be aligned, and that unaligned requests do not cross cluster       // (7) 0.04297
/*56  */          * boundaries.                                                           // (19) 0.02148
/*58  */          */                                                                      // (22) 0.01758
/*60  */         if (head) {                                                              // (17) 0.02344
/*62  */             /* Make a small request up to the first aligned sector. For          // 0.0
/*64  */              * convenience, limit this request to max_transfer even if           // 0.0
/*66  */              * we don't need to fall back to writes.  */                         // 0.0
/*68  */             num = MIN(MIN(bytes, max_transfer), alignment - head);               // 0.0
/*70  */             head = (head + num) % alignment;                                     // 0.0
/*72  */             assert(num < max_write_zeroes);                                      // 0.0
/*74  */         } else if (tail && num > alignment) {                                    // 0.0
/*76  */             /* Shorten the request to the last aligned sector.  */               // 0.0
/*78  */             num -= tail;                                                         // 0.0
/*80  */         }                                                                        // 0.0
/*84  */         /* limit request size */                                                 // 0.0
/*86  */         if (num > max_write_zeroes) {                                            // 0.0
/*88  */             num = max_write_zeroes;                                              // 0.0
/*90  */         }                                                                        // 0.0
/*94  */         ret = -ENOTSUP;                                                          // 0.0
/*96  */         /* First try the efficient write zeroes operation */                     // 0.0
/*98  */         if (drv->bdrv_co_pwrite_zeroes) {                                        // 0.0
/*100 */             ret = drv->bdrv_co_pwrite_zeroes(bs, offset, num,                    // 0.0
/*102 */                                              flags & bs->supported_zero_flags);  // 0.0
/*104 */             if (ret != -ENOTSUP && (flags & BDRV_REQ_FUA) &&                     // 0.0
/*106 */                 !(bs->supported_zero_flags & BDRV_REQ_FUA)) {                    // 0.0
/*108 */                 need_flush = true;                                               // 0.0
/*110 */             }                                                                    // 0.0
/*112 */         } else {                                                                 // 0.0
/*114 */             assert(!bs->supported_zero_flags);                                   // 0.0
/*116 */         }                                                                        // 0.0
/*120 */         if (ret == -ENOTSUP) {                                                   // 0.0
/*122 */             /* Fall back to bounce buffer if write zeroes is unsupported */      // 0.0
/*124 */             BdrvRequestFlags write_flags = flags & ~BDRV_REQ_ZERO_WRITE;         // 0.0
/*128 */             if ((flags & BDRV_REQ_FUA) &&                                        // 0.0
/*130 */                 !(bs->supported_write_flags & BDRV_REQ_FUA)) {                   // 0.0
/*132 */                 /* No need for bdrv_driver_pwrite() to do a fallback             // 0.0
/*134 */                  * flush on each chunk; use just one at the end */               // 0.0
/*136 */                 write_flags &= ~BDRV_REQ_FUA;                                    // 0.0
/*138 */                 need_flush = true;                                               // 0.0
/*140 */             }                                                                    // 0.0
/*142 */             num = MIN(num, max_transfer);                                        // 0.0
/*144 */             iov.iov_len = num;                                                   // 0.0
/*146 */             if (iov.iov_base == NULL) {                                          // 0.0
/*148 */                 iov.iov_base = qemu_try_blockalign(bs, num);                     // 0.0
/*150 */                 if (iov.iov_base == NULL) {                                      // 0.0
/*152 */                     ret = -ENOMEM;                                               // 0.0
/*154 */                     goto fail;                                                   // 0.0
/*156 */                 }                                                                // 0.0
/*158 */                 memset(iov.iov_base, 0, num);                                    // 0.0
/*160 */             }                                                                    // 0.0
/*162 */             qemu_iovec_init_external(&qiov, &iov, 1);                            // 0.0
/*166 */             ret = bdrv_driver_pwritev(bs, offset, num, &qiov, write_flags);      // 0.0
/*170 */             /* Keep bounce buffer around if it is big enough for all             // 0.0
/*172 */              * all future requests.                                              // 0.0
/*174 */              */                                                                  // 0.0
/*176 */             if (num < max_transfer) {                                            // 0.0
/*178 */                 qemu_vfree(iov.iov_base);                                        // 0.0
/*180 */                 iov.iov_base = NULL;                                             // 0.0
/*182 */             }                                                                    // 0.0
/*184 */         }                                                                        // 0.0
/*188 */         offset += num;                                                           // 0.0
/*190 */         bytes -= num;                                                            // 0.0
/*192 */     }                                                                            // 0.0
/*196 */ fail:                                                                            // 0.0
/*198 */     if (ret == 0 && need_flush) {                                                // 0.0
/*200 */         ret = bdrv_co_flush(bs);                                                 // 0.0
/*202 */     }                                                                            // 0.0
/*204 */     qemu_vfree(iov.iov_base);                                                    // 0.0
/*206 */     return ret;                                                                  // 0.0
/*208 */ }                                                                                // 0.0
