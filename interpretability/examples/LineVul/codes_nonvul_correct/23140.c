// commit message qemu@cb2e28780c (target=0, prob=0.33608952, correct=True): block: Perform copy-on-read in loop
/*0   */ static int coroutine_fn bdrv_co_do_copy_on_readv(BdrvChild *child,               // (2) 0.05469
/*2   */         int64_t offset, unsigned int bytes, QEMUIOVector *qiov)                  // (3) 0.05078
/*4   */ {                                                                                // (28) 0.001953
/*6   */     BlockDriverState *bs = child->bs;                                            // (16) 0.02539
/*10  */     /* Perform I/O through a temporary buffer so that users who scribble over    // (8) 0.03711
/*12  */      * their read buffer while the operation is in progress do not end up        // (12) 0.03516
/*14  */      * modifying the image file.  This is critical for zero-copy guest I/O       // (5) 0.04297
/*16  */      * where anything might happen inside guest memory.                          // (18) 0.02539
/*18  */      */                                                                          // (26) 0.009766
/*20  */     void *bounce_buffer;                                                         // (23) 0.01953
/*24  */     BlockDriver *drv = bs->drv;                                                  // (14) 0.0293
/*26  */     struct iovec iov;                                                            // (21) 0.01953
/*28  */     QEMUIOVector bounce_qiov;                                                    // (15) 0.02539
/*30  */     int64_t cluster_offset;                                                      // (19) 0.02148
/*32  */     unsigned int cluster_bytes;                                                  // (24) 0.01758
/*34  */     size_t skip_bytes;                                                           // (22) 0.01953
/*36  */     int ret;                                                                     // (25) 0.01172
/*40  */     /* FIXME We cannot require callers to have write permissions when all they   // (10) 0.03516
/*42  */      * are doing is a read request. If we did things right, write permissions    // (7) 0.03906
/*44  */      * would be obtained anyway, but internally by the copy-on-read code. As     // (6) 0.04297
/*46  */      * long as it is implemented here rather than in a separate filter driver,   // (9) 0.03711
/*48  */      * the copy-on-read code doesn't have its own BdrvChild, however, for which  // (4) 0.05078
/*50  */      * it could request permissions. Therefore we have to bypass the permission  // (13) 0.0332
/*52  */      * system for the moment. */                                                 // (20) 0.02148
/*54  */     // assert(child->perm & (BLK_PERM_WRITE_UNCHANGED | BLK_PERM_WRITE));        // (0) 0.06445
/*58  */     /* Cover entire cluster so no additional backing file I/O is required when   // (11) 0.03516
/*60  */      * allocating cluster in the image file.                                     // (17) 0.02539
/*62  */      */                                                                          // (27) 0.009766
/*64  */     bdrv_round_to_clusters(bs, offset, bytes, &cluster_offset, &cluster_bytes);  // (1) 0.0625
/*68  */     trace_bdrv_co_do_copy_on_readv(bs, offset, bytes,                            // 0.0
/*70  */                                    cluster_offset, cluster_bytes);               // 0.0
/*74  */     iov.iov_len = cluster_bytes;                                                 // 0.0
/*76  */     iov.iov_base = bounce_buffer = qemu_try_blockalign(bs, iov.iov_len);         // 0.0
/*78  */     if (bounce_buffer == NULL) {                                                 // 0.0
/*80  */         ret = -ENOMEM;                                                           // 0.0
/*82  */         goto err;                                                                // 0.0
/*84  */     }                                                                            // 0.0
/*88  */     qemu_iovec_init_external(&bounce_qiov, &iov, 1);                             // 0.0
/*92  */     ret = bdrv_driver_preadv(bs, cluster_offset, cluster_bytes,                  // 0.0
/*94  */                              &bounce_qiov, 0);                                   // 0.0
/*96  */     if (ret < 0) {                                                               // 0.0
/*98  */         goto err;                                                                // 0.0
/*100 */     }                                                                            // 0.0
/*104 */     bdrv_debug_event(bs, BLKDBG_COR_WRITE);                                      // 0.0
/*106 */     if (drv->bdrv_co_pwrite_zeroes &&                                            // 0.0
/*108 */         buffer_is_zero(bounce_buffer, iov.iov_len)) {                            // 0.0
/*110 */         /* FIXME: Should we (perhaps conditionally) be setting                   // 0.0
/*112 */          * BDRV_REQ_MAY_UNMAP, if it will allow for a sparser copy               // 0.0
/*114 */          * that still correctly reads as zero? */                                // 0.0
/*116 */         ret = bdrv_co_do_pwrite_zeroes(bs, cluster_offset, cluster_bytes, 0);    // 0.0
/*118 */     } else {                                                                     // 0.0
/*120 */         /* This does not change the data on the disk, it is not necessary        // 0.0
/*122 */          * to flush even in cache=writethrough mode.                             // 0.0
/*124 */          */                                                                      // 0.0
/*126 */         ret = bdrv_driver_pwritev(bs, cluster_offset, cluster_bytes,             // 0.0
/*128 */                                   &bounce_qiov, 0);                              // 0.0
/*130 */     }                                                                            // 0.0
/*134 */     if (ret < 0) {                                                               // 0.0
/*136 */         /* It might be okay to ignore write errors for guest requests.  If this  // 0.0
/*138 */          * is a deliberate copy-on-read then we don't want to ignore the error.  // 0.0
/*140 */          * Simply report it in all cases.                                        // 0.0
/*142 */          */                                                                      // 0.0
/*144 */         goto err;                                                                // 0.0
/*146 */     }                                                                            // 0.0
/*150 */     skip_bytes = offset - cluster_offset;                                        // 0.0
/*152 */     qemu_iovec_from_buf(qiov, 0, bounce_buffer + skip_bytes, bytes);             // 0.0
/*156 */ err:                                                                             // 0.0
/*158 */     qemu_vfree(bounce_buffer);                                                   // 0.0
/*160 */     return ret;                                                                  // 0.0
/*162 */ }                                                                                // 0.0
