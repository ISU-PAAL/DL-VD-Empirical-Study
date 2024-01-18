// commit message qemu@d0d5d0e31a (target=1, prob=0.47838667, correct=False): qcow2: Check failure of bdrv_getlength()
/*0   */ qcow2_co_pwritev_compressed(BlockDriverState *bs, uint64_t offset,                // (3) 0.04883
/*2   */                             uint64_t bytes, QEMUIOVector *qiov)                   // (0) 0.08203
/*4   */ {                                                                                 // (27) 0.001953
/*6   */     BDRVQcow2State *s = bs->opaque;                                               // (11) 0.03711
/*8   */     QEMUIOVector hd_qiov;                                                         // (17) 0.02734
/*10  */     struct iovec iov;                                                             // (19) 0.01953
/*12  */     z_stream strm;                                                                // (22) 0.01758
/*14  */     int ret, out_len;                                                             // (20) 0.01953
/*16  */     uint8_t *buf, *out_buf;                                                       // (15) 0.0293
/*18  */     uint64_t cluster_offset;                                                      // (18) 0.02148
/*22  */     if (bytes == 0) {                                                             // (21) 0.01953
/*24  */         /* align end of file to a sector boundary to ease reading with            // (9) 0.03906
/*26  */            sector based I/Os */                                                   // (14) 0.03125
/*28  */         cluster_offset = bdrv_getlength(bs->file->bs);                            // (6) 0.04688
/*30  */         return bdrv_truncate(bs->file, cluster_offset, PREALLOC_MODE_OFF, NULL);  // (2) 0.06641
/*32  */     }                                                                             // (25) 0.007812
/*36  */     buf = qemu_blockalign(bs, s->cluster_size);                                   // (7) 0.04102
/*38  */     if (bytes != s->cluster_size) {                                               // (16) 0.0293
/*40  */         if (bytes > s->cluster_size ||                                            // (12) 0.03516
/*42  */             offset + bytes != bs->total_sectors << BDRV_SECTOR_BITS)              // (1) 0.06641
/*44  */         {                                                                         // (23) 0.01562
/*46  */             qemu_vfree(buf);                                                      // (10) 0.03906
/*48  */             return -EINVAL;                                                       // (13) 0.0332
/*50  */         }                                                                         // (24) 0.01562
/*52  */         /* Zero-pad last write if image size is not cluster aligned */            // (8) 0.04102
/*54  */         memset(buf + bytes, 0, s->cluster_size - bytes);                          // (4) 0.04883
/*56  */     }                                                                             // (26) 0.007812
/*58  */     qemu_iovec_to_buf(qiov, 0, buf, bytes);                                       // (5) 0.04688
/*62  */     out_buf = g_malloc(s->cluster_size);                                          // 0.0
/*66  */     /* best compression, small window, no zlib header */                          // 0.0
/*68  */     memset(&strm, 0, sizeof(strm));                                               // 0.0
/*70  */     ret = deflateInit2(&strm, Z_DEFAULT_COMPRESSION,                              // 0.0
/*72  */                        Z_DEFLATED, -12,                                           // 0.0
/*74  */                        9, Z_DEFAULT_STRATEGY);                                    // 0.0
/*76  */     if (ret != 0) {                                                               // 0.0
/*78  */         ret = -EINVAL;                                                            // 0.0
/*80  */         goto fail;                                                                // 0.0
/*82  */     }                                                                             // 0.0
/*86  */     strm.avail_in = s->cluster_size;                                              // 0.0
/*88  */     strm.next_in = (uint8_t *)buf;                                                // 0.0
/*90  */     strm.avail_out = s->cluster_size;                                             // 0.0
/*92  */     strm.next_out = out_buf;                                                      // 0.0
/*96  */     ret = deflate(&strm, Z_FINISH);                                               // 0.0
/*98  */     if (ret != Z_STREAM_END && ret != Z_OK) {                                     // 0.0
/*100 */         deflateEnd(&strm);                                                        // 0.0
/*102 */         ret = -EINVAL;                                                            // 0.0
/*104 */         goto fail;                                                                // 0.0
/*106 */     }                                                                             // 0.0
/*108 */     out_len = strm.next_out - out_buf;                                            // 0.0
/*112 */     deflateEnd(&strm);                                                            // 0.0
/*116 */     if (ret != Z_STREAM_END || out_len >= s->cluster_size) {                      // 0.0
/*118 */         /* could not compress: write normal cluster */                            // 0.0
/*120 */         ret = qcow2_co_pwritev(bs, offset, bytes, qiov, 0);                       // 0.0
/*122 */         if (ret < 0) {                                                            // 0.0
/*124 */             goto fail;                                                            // 0.0
/*126 */         }                                                                         // 0.0
/*128 */         goto success;                                                             // 0.0
/*130 */     }                                                                             // 0.0
/*134 */     qemu_co_mutex_lock(&s->lock);                                                 // 0.0
/*136 */     cluster_offset =                                                              // 0.0
/*138 */         qcow2_alloc_compressed_cluster_offset(bs, offset, out_len);               // 0.0
/*140 */     if (!cluster_offset) {                                                        // 0.0
/*142 */         qemu_co_mutex_unlock(&s->lock);                                           // 0.0
/*144 */         ret = -EIO;                                                               // 0.0
/*146 */         goto fail;                                                                // 0.0
/*148 */     }                                                                             // 0.0
/*150 */     cluster_offset &= s->cluster_offset_mask;                                     // 0.0
/*154 */     ret = qcow2_pre_write_overlap_check(bs, 0, cluster_offset, out_len);          // 0.0
/*156 */     qemu_co_mutex_unlock(&s->lock);                                               // 0.0
/*158 */     if (ret < 0) {                                                                // 0.0
/*160 */         goto fail;                                                                // 0.0
/*162 */     }                                                                             // 0.0
/*166 */     iov = (struct iovec) {                                                        // 0.0
/*168 */         .iov_base   = out_buf,                                                    // 0.0
/*170 */         .iov_len    = out_len,                                                    // 0.0
/*172 */     };                                                                            // 0.0
/*174 */     qemu_iovec_init_external(&hd_qiov, &iov, 1);                                  // 0.0
/*178 */     BLKDBG_EVENT(bs->file, BLKDBG_WRITE_COMPRESSED);                              // 0.0
/*180 */     ret = bdrv_co_pwritev(bs->file, cluster_offset, out_len, &hd_qiov, 0);        // 0.0
/*182 */     if (ret < 0) {                                                                // 0.0
/*184 */         goto fail;                                                                // 0.0
/*186 */     }                                                                             // 0.0
/*188 */ success:                                                                          // 0.0
/*190 */     ret = 0;                                                                      // 0.0
/*192 */ fail:                                                                             // 0.0
/*194 */     qemu_vfree(buf);                                                              // 0.0
/*196 */     g_free(out_buf);                                                              // 0.0
/*198 */     return ret;                                                                   // 0.0
/*200 */ }                                                                                 // 0.0
