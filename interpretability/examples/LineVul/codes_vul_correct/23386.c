// commit message qemu@d470ad42ac (target=1, prob=0.9990928, correct=True): block: Guard against NULL bs->drv
/*0  */ static int coroutine_fn bdrv_aligned_pwritev(BdrvChild *child,                   // (4) 0.04492
/*1  */     BdrvTrackedRequest *req, int64_t offset, unsigned int bytes,                 // (6) 0.04297
/*2  */     int64_t align, QEMUIOVector *qiov, int flags)                                // (7) 0.04102
/*3  */ {                                                                                // (25) 0.001953
/*4  */     BlockDriverState *bs = child->bs;                                            // (20) 0.02539
/*5  */     BlockDriver *drv = bs->drv;                                                  // (12) 0.0293
/*6  */     bool waited;                                                                 // (23) 0.01172
/*7  */     int ret;                                                                     // (24) 0.01172
/*8  */     int64_t end_sector = DIV_ROUND_UP(offset + bytes, BDRV_SECTOR_SIZE);         // (2) 0.06445
/*9  */     uint64_t bytes_remaining = bytes;                                            // (18) 0.02734
/*10 */     int max_transfer;                                                            // (22) 0.01562
/*11 */     if (bdrv_has_readonly_bitmaps(bs)) {                                         // (8) 0.03906
/*12 */         return -EPERM;                                                           // (21) 0.02539
/*13 */     assert(is_power_of_2(align));                                                // (14) 0.0293
/*14 */     assert((offset & (align - 1)) == 0);                                         // (15) 0.0293
/*15 */     assert((bytes & (align - 1)) == 0);                                          // (17) 0.0293
/*16 */     assert(!qiov || bytes == qiov->size);                                        // (11) 0.03125
/*17 */     assert((bs->open_flags & BDRV_O_NO_IO) == 0);                                // (3) 0.04687
/*18 */     assert(!(flags & ~BDRV_REQ_MASK));                                           // (9) 0.03906
/*19 */     max_transfer = QEMU_ALIGN_DOWN(MIN_NON_ZERO(bs->bl.max_transfer, INT_MAX),   // (0) 0.07031
/*20 */                                    align);                                       // (1) 0.07031
/*21 */     waited = wait_serialising_requests(req);                                     // (13) 0.0293
/*22 */     assert(!waited || !req->serialising);                                        // (16) 0.0293
/*23 */     assert(req->overlap_offset <= offset);                                       // (19) 0.02734
/*24 */     assert(offset + bytes <= req->overlap_offset + req->overlap_bytes);          // (5) 0.04492
/*25 */     assert(child->perm & BLK_PERM_WRITE);                                        // (10) 0.03516
/*26 */     assert(end_sector <= bs->total_sectors || child->perm & BLK_PERM_RESIZE);    // 0.0
/*27 */     ret = notifier_with_return_list_notify(&bs->before_write_notifiers, req);    // 0.0
/*28 */     if (!ret && bs->detect_zeroes != BLOCKDEV_DETECT_ZEROES_OPTIONS_OFF &&       // 0.0
/*29 */         !(flags & BDRV_REQ_ZERO_WRITE) && drv->bdrv_co_pwrite_zeroes &&          // 0.0
/*30 */         qemu_iovec_is_zero(qiov)) {                                              // 0.0
/*31 */         flags |= BDRV_REQ_ZERO_WRITE;                                            // 0.0
/*32 */         if (bs->detect_zeroes == BLOCKDEV_DETECT_ZEROES_OPTIONS_UNMAP) {         // 0.0
/*33 */             flags |= BDRV_REQ_MAY_UNMAP;                                         // 0.0
/*34 */     if (ret < 0) {                                                               // 0.0
/*35 */         /* Do nothing, write notifier decided to fail this request */            // 0.0
/*36 */     } else if (flags & BDRV_REQ_ZERO_WRITE) {                                    // 0.0
/*37 */         bdrv_debug_event(bs, BLKDBG_PWRITEV_ZERO);                               // 0.0
/*38 */         ret = bdrv_co_do_pwrite_zeroes(bs, offset, bytes, flags);                // 0.0
/*39 */     } else if (flags & BDRV_REQ_WRITE_COMPRESSED) {                              // 0.0
/*40 */         ret = bdrv_driver_pwritev_compressed(bs, offset, bytes, qiov);           // 0.0
/*41 */     } else if (bytes <= max_transfer) {                                          // 0.0
/*42 */         bdrv_debug_event(bs, BLKDBG_PWRITEV);                                    // 0.0
/*43 */         ret = bdrv_driver_pwritev(bs, offset, bytes, qiov, flags);               // 0.0
/*44 */     } else {                                                                     // 0.0
/*45 */         bdrv_debug_event(bs, BLKDBG_PWRITEV);                                    // 0.0
/*46 */         while (bytes_remaining) {                                                // 0.0
/*47 */             int num = MIN(bytes_remaining, max_transfer);                        // 0.0
/*48 */             QEMUIOVector local_qiov;                                             // 0.0
/*49 */             int local_flags = flags;                                             // 0.0
/*50 */             assert(num);                                                         // 0.0
/*51 */             if (num < bytes_remaining && (flags & BDRV_REQ_FUA) &&               // 0.0
/*52 */                 !(bs->supported_write_flags & BDRV_REQ_FUA)) {                   // 0.0
/*53 */                 /* If FUA is going to be emulated by flush, we only              // 0.0
/*54 */                  * need to flush on the last iteration */                        // 0.0
/*55 */                 local_flags &= ~BDRV_REQ_FUA;                                    // 0.0
/*56 */             qemu_iovec_init(&local_qiov, qiov->niov);                            // 0.0
/*57 */             qemu_iovec_concat(&local_qiov, qiov, bytes - bytes_remaining, num);  // 0.0
/*58 */             ret = bdrv_driver_pwritev(bs, offset + bytes - bytes_remaining,      // 0.0
/*59 */                                       num, &local_qiov, local_flags);            // 0.0
/*60 */             qemu_iovec_destroy(&local_qiov);                                     // 0.0
/*61 */             if (ret < 0) {                                                       // 0.0
/*62 */                 break;                                                           // 0.0
/*63 */             bytes_remaining -= num;                                              // 0.0
/*64 */     bdrv_debug_event(bs, BLKDBG_PWRITEV_DONE);                                   // 0.0
/*65 */     atomic_inc(&bs->write_gen);                                                  // 0.0
/*66 */     bdrv_set_dirty(bs, offset, bytes);                                           // 0.0
/*67 */     stat64_max(&bs->wr_highest_offset, offset + bytes);                          // 0.0
/*68 */     if (ret >= 0) {                                                              // 0.0
/*69 */         bs->total_sectors = MAX(bs->total_sectors, end_sector);                  // 0.0
/*70 */         ret = 0;                                                                 // 0.0
/*71 */     return ret;                                                                  // 0.0
