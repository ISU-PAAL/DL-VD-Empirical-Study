// commit message qemu@4545d4f4af (target=1, prob=0.5098967, correct=True): block/vmdk: Fix the endian problem of buf_len and lba
/*0   */ static int vmdk_write_extent(VmdkExtent *extent, int64_t cluster_offset,        // (4) 0.05469
/*2   */                             int64_t offset_in_cluster, QEMUIOVector *qiov,      // (0) 0.0918
/*4   */                             uint64_t qiov_offset, uint64_t n_bytes,             // (1) 0.08594
/*6   */                             uint64_t offset)                                    // (3) 0.06445
/*8   */ {                                                                               // (23) 0.001953
/*10  */     int ret;                                                                    // (22) 0.01172
/*12  */     VmdkGrainMarker *data = NULL;                                               // (12) 0.0293
/*14  */     uLongf buf_len;                                                             // (20) 0.01953
/*16  */     QEMUIOVector local_qiov;                                                    // (16) 0.02539
/*18  */     struct iovec iov;                                                           // (19) 0.01953
/*20  */     int64_t write_offset;                                                       // (18) 0.02148
/*22  */     int64_t write_end_sector;                                                   // (15) 0.02539
/*26  */     if (extent->compressed) {                                                   // (17) 0.02344
/*28  */         void *compressed_data;                                                  // (14) 0.02734
/*32  */         if (!extent->has_marker) {                                              // (9) 0.03516
/*34  */             ret = -EINVAL;                                                      // (10) 0.03516
/*36  */             goto out;                                                           // (13) 0.02734
/*38  */         }                                                                       // (21) 0.01562
/*40  */         buf_len = (extent->cluster_sectors << 9) * 2;                           // (7) 0.05078
/*42  */         data = g_malloc(buf_len + sizeof(VmdkGrainMarker));                     // (5) 0.05469
/*46  */         compressed_data = g_malloc(n_bytes);                                    // (8) 0.03906
/*48  */         qemu_iovec_to_buf(qiov, qiov_offset, compressed_data, n_bytes);         // (2) 0.06836
/*50  */         ret = compress(data->data, &buf_len, compressed_data, n_bytes);         // (6) 0.05469
/*52  */         g_free(compressed_data);                                                // (11) 0.03125
/*56  */         if (ret != Z_OK || buf_len == 0) {                                      // 0.0
/*58  */             ret = -EINVAL;                                                      // 0.0
/*60  */             goto out;                                                           // 0.0
/*62  */         }                                                                       // 0.0
/*66  */         data->lba = offset >> BDRV_SECTOR_BITS;                                 // 0.0
/*68  */         data->size = buf_len;                                                   // 0.0
/*72  */         n_bytes = buf_len + sizeof(VmdkGrainMarker);                            // 0.0
/*74  */         iov = (struct iovec) {                                                  // 0.0
/*76  */             .iov_base   = data,                                                 // 0.0
/*78  */             .iov_len    = n_bytes,                                              // 0.0
/*80  */         };                                                                      // 0.0
/*82  */         qemu_iovec_init_external(&local_qiov, &iov, 1);                         // 0.0
/*84  */     } else {                                                                    // 0.0
/*86  */         qemu_iovec_init(&local_qiov, qiov->niov);                               // 0.0
/*88  */         qemu_iovec_concat(&local_qiov, qiov, qiov_offset, n_bytes);             // 0.0
/*90  */     }                                                                           // 0.0
/*94  */     write_offset = cluster_offset + offset_in_cluster,                          // 0.0
/*96  */     ret = bdrv_co_pwritev(extent->file, write_offset, n_bytes,                  // 0.0
/*98  */                           &local_qiov, 0);                                      // 0.0
/*102 */     write_end_sector = DIV_ROUND_UP(write_offset + n_bytes, BDRV_SECTOR_SIZE);  // 0.0
/*106 */     if (extent->compressed) {                                                   // 0.0
/*108 */         extent->next_cluster_sector = write_end_sector;                         // 0.0
/*110 */     } else {                                                                    // 0.0
/*112 */         extent->next_cluster_sector = MAX(extent->next_cluster_sector,          // 0.0
/*114 */                                           write_end_sector);                    // 0.0
/*116 */     }                                                                           // 0.0
/*120 */     if (ret < 0) {                                                              // 0.0
/*122 */         goto out;                                                               // 0.0
/*124 */     }                                                                           // 0.0
/*126 */     ret = 0;                                                                    // 0.0
/*128 */  out:                                                                           // 0.0
/*130 */     g_free(data);                                                               // 0.0
/*132 */     if (!extent->compressed) {                                                  // 0.0
/*134 */         qemu_iovec_destroy(&local_qiov);                                        // 0.0
/*136 */     }                                                                           // 0.0
/*138 */     return ret;                                                                 // 0.0
/*140 */ }                                                                               // 0.0
