// commit message qemu@d470ad42ac (target=1, prob=0.9992048, correct=True): block: Guard against NULL bs->drv
/*0   */ static int coroutine_fn bdrv_co_do_copy_on_readv(BdrvChild *child,               // (2) 0.05469
/*1   */         int64_t offset, unsigned int bytes, QEMUIOVector *qiov)                  // (3) 0.05078
/*2   */ {                                                                                // (27) 0.001953
/*3   */     BlockDriverState *bs = child->bs;                                            // (15) 0.02539
/*4   */     /* Perform I/O through a temporary buffer so that users who scribble over    // (9) 0.03711
/*5   */      * their read buffer while the operation is in progress do not end up        // (11) 0.03516
/*6   */      * modifying the image file.  This is critical for zero-copy guest I/O       // (6) 0.04297
/*7   */      * where anything might happen inside guest memory.                          // (17) 0.02539
/*8   */      */                                                                          // (26) 0.009766
/*9   */     void *bounce_buffer;                                                         // (22) 0.01953
/*10  */     BlockDriver *drv = bs->drv;                                                  // (14) 0.0293
/*11  */     struct iovec iov;                                                            // (23) 0.01953
/*12  */     QEMUIOVector local_qiov;                                                     // (16) 0.02539
/*13  */     int64_t cluster_offset;                                                      // (20) 0.02148
/*14  */     int64_t cluster_bytes;                                                       // (19) 0.02148
/*15  */     size_t skip_bytes;                                                           // (21) 0.01953
/*16  */     int ret;                                                                     // (25) 0.01172
/*17  */     int max_transfer = MIN_NON_ZERO(bs->bl.max_transfer,                         // (5) 0.04687
/*18  */                                     BDRV_REQUEST_MAX_BYTES);                     // (0) 0.09375
/*19  */     unsigned int progress = 0;                                                   // (24) 0.01758
/*20  */     /* FIXME We cannot require callers to have write permissions when all they   // (12) 0.03516
/*21  */      * are doing is a read request. If we did things right, write permissions    // (8) 0.03906
/*22  */      * would be obtained anyway, but internally by the copy-on-read code. As     // (7) 0.04297
/*23  */      * long as it is implemented here rather than in a separate filter driver,   // (10) 0.03711
/*24  */      * the copy-on-read code doesn't have its own BdrvChild, however, for which  // (4) 0.05078
/*25  */      * it could request permissions. Therefore we have to bypass the permission  // (13) 0.0332
/*26  */      * system for the moment. */                                                 // (18) 0.02148
/*27  */     // assert(child->perm & (BLK_PERM_WRITE_UNCHANGED | BLK_PERM_WRITE));        // (1) 0.06445
/*28  */     /* Cover entire cluster so no additional backing file I/O is required when   // 0.0
/*29  */      * allocating cluster in the image file.  Note that this value may exceed    // 0.0
/*30  */      * BDRV_REQUEST_MAX_BYTES (even when the original read did not), which       // 0.0
/*31  */      * is one reason we loop rather than doing it all at once.                   // 0.0
/*32  */      */                                                                          // 0.0
/*33  */     bdrv_round_to_clusters(bs, offset, bytes, &cluster_offset, &cluster_bytes);  // 0.0
/*34  */     skip_bytes = offset - cluster_offset;                                        // 0.0
/*35  */     trace_bdrv_co_do_copy_on_readv(bs, offset, bytes,                            // 0.0
/*36  */                                    cluster_offset, cluster_bytes);               // 0.0
/*37  */     bounce_buffer = qemu_try_blockalign(bs,                                      // 0.0
/*38  */                                         MIN(MIN(max_transfer, cluster_bytes),    // 0.0
/*39  */                                             MAX_BOUNCE_BUFFER));                 // 0.0
/*40  */     if (bounce_buffer == NULL) {                                                 // 0.0
/*41  */         ret = -ENOMEM;                                                           // 0.0
/*42  */         goto err;                                                                // 0.0
/*43  */     while (cluster_bytes) {                                                      // 0.0
/*44  */         int64_t pnum;                                                            // 0.0
/*45  */         ret = bdrv_is_allocated(bs, cluster_offset,                              // 0.0
/*46  */                                 MIN(cluster_bytes, max_transfer), &pnum);        // 0.0
/*47  */         if (ret < 0) {                                                           // 0.0
/*48  */             /* Safe to treat errors in querying allocation as if                 // 0.0
/*49  */              * unallocated; we'll probably fail again soon on the                // 0.0
/*50  */              * read, but at least that will set a decent errno.                  // 0.0
/*51  */              */                                                                  // 0.0
/*52  */             pnum = MIN(cluster_bytes, max_transfer);                             // 0.0
/*53  */         assert(skip_bytes < pnum);                                               // 0.0
/*54  */         if (ret <= 0) {                                                          // 0.0
/*55  */             /* Must copy-on-read; use the bounce buffer */                       // 0.0
/*56  */             iov.iov_base = bounce_buffer;                                        // 0.0
/*57  */             iov.iov_len = pnum = MIN(pnum, MAX_BOUNCE_BUFFER);                   // 0.0
/*58  */             qemu_iovec_init_external(&local_qiov, &iov, 1);                      // 0.0
/*59  */             ret = bdrv_driver_preadv(bs, cluster_offset, pnum,                   // 0.0
/*60  */                                      &local_qiov, 0);                            // 0.0
/*61  */             if (ret < 0) {                                                       // 0.0
/*62  */                 goto err;                                                        // 0.0
/*63  */             bdrv_debug_event(bs, BLKDBG_COR_WRITE);                              // 0.0
/*64  */             if (drv->bdrv_co_pwrite_zeroes &&                                    // 0.0
/*65  */                 buffer_is_zero(bounce_buffer, pnum)) {                           // 0.0
/*66  */                 /* FIXME: Should we (perhaps conditionally) be setting           // 0.0
/*67  */                  * BDRV_REQ_MAY_UNMAP, if it will allow for a sparser copy       // 0.0
/*68  */                  * that still correctly reads as zero? */                        // 0.0
/*69  */                 ret = bdrv_co_do_pwrite_zeroes(bs, cluster_offset, pnum, 0);     // 0.0
/*70  */             } else {                                                             // 0.0
/*71  */                 /* This does not change the data on the disk, it is not          // 0.0
/*72  */                  * necessary to flush even in cache=writethrough mode.           // 0.0
/*73  */                  */                                                              // 0.0
/*74  */                 ret = bdrv_driver_pwritev(bs, cluster_offset, pnum,              // 0.0
/*75  */                                           &local_qiov, 0);                       // 0.0
/*76  */             if (ret < 0) {                                                       // 0.0
/*77  */                 /* It might be okay to ignore write errors for guest             // 0.0
/*78  */                  * requests.  If this is a deliberate copy-on-read               // 0.0
/*79  */                  * then we don't want to ignore the error.  Simply               // 0.0
/*80  */                  * report it in all cases.                                       // 0.0
/*81  */                  */                                                              // 0.0
/*82  */                 goto err;                                                        // 0.0
/*83  */             qemu_iovec_from_buf(qiov, progress, bounce_buffer + skip_bytes,      // 0.0
/*84  */                                 pnum - skip_bytes);                              // 0.0
/*85  */         } else {                                                                 // 0.0
/*86  */             /* Read directly into the destination */                             // 0.0
/*87  */             qemu_iovec_init(&local_qiov, qiov->niov);                            // 0.0
/*88  */             qemu_iovec_concat(&local_qiov, qiov, progress, pnum - skip_bytes);   // 0.0
/*89  */             ret = bdrv_driver_preadv(bs, offset + progress, local_qiov.size,     // 0.0
/*90  */                                      &local_qiov, 0);                            // 0.0
/*91  */             qemu_iovec_destroy(&local_qiov);                                     // 0.0
/*92  */             if (ret < 0) {                                                       // 0.0
/*93  */                 goto err;                                                        // 0.0
/*94  */         cluster_offset += pnum;                                                  // 0.0
/*95  */         cluster_bytes -= pnum;                                                   // 0.0
/*96  */         progress += pnum - skip_bytes;                                           // 0.0
/*97  */         skip_bytes = 0;                                                          // 0.0
/*98  */     ret = 0;                                                                     // 0.0
/*99  */ err:                                                                             // 0.0
/*100 */     qemu_vfree(bounce_buffer);                                                   // 0.0
/*101 */     return ret;                                                                  // 0.0
