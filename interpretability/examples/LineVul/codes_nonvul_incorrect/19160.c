// commit message qemu@a193b0f0a8 (target=0, prob=0.5159943, correct=False): backup: move from done_bitmap to copy_bitmap
/*0   */ static int coroutine_fn backup_do_cow(BackupBlockJob *job,                        // (11) 0.03711
/*2   */                                       int64_t offset, uint64_t bytes,             // (0) 0.0957
/*4   */                                       bool *error_is_read,                        // (1) 0.08789
/*6   */                                       bool is_write_notifier)                     // (2) 0.08789
/*8   */ {                                                                                 // (22) 0.001953
/*10  */     BlockBackend *blk = job->common.blk;                                          // (14) 0.0332
/*12  */     CowRequest cow_request;                                                       // (20) 0.01758
/*14  */     struct iovec iov;                                                             // (18) 0.01953
/*16  */     QEMUIOVector bounce_qiov;                                                     // (16) 0.02539
/*18  */     void *bounce_buffer = NULL;                                                   // (17) 0.02344
/*20  */     int ret = 0;                                                                  // (21) 0.01562
/*22  */     int64_t start, end; /* bytes */                                               // (15) 0.02734
/*24  */     int n; /* bytes */                                                            // (19) 0.01758
/*28  */     qemu_co_rwlock_rdlock(&job->flush_rwlock);                                    // (8) 0.04297
/*32  */     start = QEMU_ALIGN_DOWN(offset, job->cluster_size);                           // (6) 0.04492
/*34  */     end = QEMU_ALIGN_UP(bytes + offset, job->cluster_size);                       // (5) 0.04883
/*38  */     trace_backup_do_cow_enter(job, start, offset, bytes);                         // (7) 0.04297
/*42  */     wait_for_overlapping_requests(job, start, end);                               // (9) 0.03906
/*44  */     cow_request_begin(&cow_request, job, start, end);                             // (12) 0.03711
/*48  */     for (; start < end; start += job->cluster_size) {                             // (10) 0.03906
/*50  */         if (test_bit(start / job->cluster_size, job->done_bitmap)) {              // (3) 0.05859
/*52  */             trace_backup_do_cow_skip(job, start);                                 // (4) 0.05078
/*54  */             continue; /* already copied */                                        // (13) 0.0332
/*56  */         }                                                                         // 0.0
/*60  */         trace_backup_do_cow_process(job, start);                                  // 0.0
/*64  */         n = MIN(job->cluster_size, job->common.len - start);                      // 0.0
/*68  */         if (!bounce_buffer) {                                                     // 0.0
/*70  */             bounce_buffer = blk_blockalign(blk, job->cluster_size);               // 0.0
/*72  */         }                                                                         // 0.0
/*74  */         iov.iov_base = bounce_buffer;                                             // 0.0
/*76  */         iov.iov_len = n;                                                          // 0.0
/*78  */         qemu_iovec_init_external(&bounce_qiov, &iov, 1);                          // 0.0
/*82  */         ret = blk_co_preadv(blk, start, bounce_qiov.size, &bounce_qiov,           // 0.0
/*84  */                             is_write_notifier ? BDRV_REQ_NO_SERIALISING : 0);     // 0.0
/*86  */         if (ret < 0) {                                                            // 0.0
/*88  */             trace_backup_do_cow_read_fail(job, start, ret);                       // 0.0
/*90  */             if (error_is_read) {                                                  // 0.0
/*92  */                 *error_is_read = true;                                            // 0.0
/*94  */             }                                                                     // 0.0
/*96  */             goto out;                                                             // 0.0
/*98  */         }                                                                         // 0.0
/*102 */         if (buffer_is_zero(iov.iov_base, iov.iov_len)) {                          // 0.0
/*104 */             ret = blk_co_pwrite_zeroes(job->target, start,                        // 0.0
/*106 */                                        bounce_qiov.size, BDRV_REQ_MAY_UNMAP);     // 0.0
/*108 */         } else {                                                                  // 0.0
/*110 */             ret = blk_co_pwritev(job->target, start,                              // 0.0
/*112 */                                  bounce_qiov.size, &bounce_qiov,                  // 0.0
/*114 */                                  job->compress ? BDRV_REQ_WRITE_COMPRESSED : 0);  // 0.0
/*116 */         }                                                                         // 0.0
/*118 */         if (ret < 0) {                                                            // 0.0
/*120 */             trace_backup_do_cow_write_fail(job, start, ret);                      // 0.0
/*122 */             if (error_is_read) {                                                  // 0.0
/*124 */                 *error_is_read = false;                                           // 0.0
/*126 */             }                                                                     // 0.0
/*128 */             goto out;                                                             // 0.0
/*130 */         }                                                                         // 0.0
/*134 */         set_bit(start / job->cluster_size, job->done_bitmap);                     // 0.0
/*138 */         /* Publish progress, guest I/O counts as progress too.  Note that the     // 0.0
/*140 */          * offset field is an opaque progress value, it is not a disk offset.     // 0.0
/*142 */          */                                                                       // 0.0
/*144 */         job->bytes_read += n;                                                     // 0.0
/*146 */         job->common.offset += n;                                                  // 0.0
/*148 */     }                                                                             // 0.0
/*152 */ out:                                                                              // 0.0
/*154 */     if (bounce_buffer) {                                                          // 0.0
/*156 */         qemu_vfree(bounce_buffer);                                                // 0.0
/*158 */     }                                                                             // 0.0
/*162 */     cow_request_end(&cow_request);                                                // 0.0
/*166 */     trace_backup_do_cow_return(job, offset, bytes, ret);                          // 0.0
/*170 */     qemu_co_rwlock_unlock(&job->flush_rwlock);                                    // 0.0
/*174 */     return ret;                                                                   // 0.0
/*176 */ }                                                                                 // 0.0
