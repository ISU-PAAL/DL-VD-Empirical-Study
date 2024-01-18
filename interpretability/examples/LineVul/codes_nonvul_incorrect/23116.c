// commit message qemu@d85f4222b4 (target=0, prob=0.5612407, correct=False): qcow: convert QCow to use QCryptoBlock for encryption
/*0   */ static coroutine_fn int qcow_co_readv(BlockDriverState *bs, int64_t sector_num,  // (4) 0.05468
/*2   */                          int nb_sectors, QEMUIOVector *qiov)                     // (1) 0.07811
/*4   */ {                                                                                // (26) 0.001953
/*6   */     BDRVQcowState *s = bs->opaque;                                               // (7) 0.03515
/*8   */     int index_in_cluster;                                                        // (17) 0.02148
/*10  */     int ret = 0, n;                                                              // (20) 0.01953
/*12  */     uint64_t cluster_offset;                                                     // (18) 0.02148
/*14  */     struct iovec hd_iov;                                                         // (16) 0.02343
/*16  */     QEMUIOVector hd_qiov;                                                        // (12) 0.02734
/*18  */     uint8_t *buf;                                                                // (19) 0.01953
/*20  */     void *orig_buf;                                                              // (22) 0.01758
/*22  */     Error *err = NULL;                                                           // (21) 0.01779
/*26  */     if (qiov->niov > 1) {                                                        // (10) 0.02734
/*28  */         buf = orig_buf = qemu_try_blockalign(bs, qiov->size);                    // (2) 0.05663
/*30  */         if (buf == NULL) {                                                       // (11) 0.02734
/*32  */             return -ENOMEM;                                                      // (9) 0.03319
/*34  */         }                                                                        // (23) 0.01562
/*36  */     } else {                                                                     // (24) 0.01172
/*38  */         orig_buf = NULL;                                                         // (13) 0.02538
/*40  */         buf = (uint8_t *)qiov->iov->iov_base;                                    // (6) 0.04686
/*42  */     }                                                                            // (25) 0.007811
/*46  */     qemu_co_mutex_lock(&s->lock);                                                // (8) 0.03515
/*50  */     while (nb_sectors != 0) {                                                    // (14) 0.02538
/*52  */         /* prepare next request */                                               // (15) 0.02343
/*54  */         cluster_offset = get_cluster_offset(bs, sector_num << 9,                 // (5) 0.05077
/*56  */                                                  0, 0, 0, 0);                    // (0) 0.1093
/*58  */         index_in_cluster = sector_num & (s->cluster_sectors - 1);                // (3) 0.05663
/*60  */         n = s->cluster_sectors - index_in_cluster;                               // 0.0
/*62  */         if (n > nb_sectors) {                                                    // 0.0
/*64  */             n = nb_sectors;                                                      // 0.0
/*66  */         }                                                                        // 0.0
/*70  */         if (!cluster_offset) {                                                   // 0.0
/*72  */             if (bs->backing) {                                                   // 0.0
/*74  */                 /* read from the base image */                                   // 0.0
/*76  */                 hd_iov.iov_base = (void *)buf;                                   // 0.0
/*78  */                 hd_iov.iov_len = n * 512;                                        // 0.0
/*80  */                 qemu_iovec_init_external(&hd_qiov, &hd_iov, 1);                  // 0.0
/*82  */                 qemu_co_mutex_unlock(&s->lock);                                  // 0.0
/*84  */                 ret = bdrv_co_readv(bs->backing, sector_num, n, &hd_qiov);       // 0.0
/*86  */                 qemu_co_mutex_lock(&s->lock);                                    // 0.0
/*88  */                 if (ret < 0) {                                                   // 0.0
/*90  */                     goto fail;                                                   // 0.0
/*92  */                 }                                                                // 0.0
/*94  */             } else {                                                             // 0.0
/*96  */                 /* Note: in this case, no need to wait */                        // 0.0
/*98  */                 memset(buf, 0, 512 * n);                                         // 0.0
/*100 */             }                                                                    // 0.0
/*102 */         } else if (cluster_offset & QCOW_OFLAG_COMPRESSED) {                     // 0.0
/*104 */             /* add AIO support for compressed blocks ? */                        // 0.0
/*106 */             if (decompress_cluster(bs, cluster_offset) < 0) {                    // 0.0
/*108 */                 goto fail;                                                       // 0.0
/*110 */             }                                                                    // 0.0
/*112 */             memcpy(buf,                                                          // 0.0
/*114 */                    s->cluster_cache + index_in_cluster * 512, 512 * n);          // 0.0
/*116 */         } else {                                                                 // 0.0
/*118 */             if ((cluster_offset & 511) != 0) {                                   // 0.0
/*120 */                 goto fail;                                                       // 0.0
/*122 */             }                                                                    // 0.0
/*124 */             hd_iov.iov_base = (void *)buf;                                       // 0.0
/*126 */             hd_iov.iov_len = n * 512;                                            // 0.0
/*128 */             qemu_iovec_init_external(&hd_qiov, &hd_iov, 1);                      // 0.0
/*130 */             qemu_co_mutex_unlock(&s->lock);                                      // 0.0
/*132 */             ret = bdrv_co_readv(bs->file,                                        // 0.0
/*134 */                                 (cluster_offset >> 9) + index_in_cluster,        // 0.0
/*136 */                                 n, &hd_qiov);                                    // 0.0
/*138 */             qemu_co_mutex_lock(&s->lock);                                        // 0.0
/*140 */             if (ret < 0) {                                                       // 0.0
/*142 */                 break;                                                           // 0.0
/*144 */             }                                                                    // 0.0
/*146 */             if (bs->encrypted) {                                                 // 0.0
/*148 */                 assert(s->cipher);                                               // 0.0
/*150 */                 if (encrypt_sectors(s, sector_num, buf,                          // 0.0
/*152 */                                     n, false, &err) < 0) {                       // 0.0
/*154 */                     goto fail;                                                   // 0.0
/*156 */                 }                                                                // 0.0
/*158 */             }                                                                    // 0.0
/*160 */         }                                                                        // 0.0
/*162 */         ret = 0;                                                                 // 0.0
/*166 */         nb_sectors -= n;                                                         // 0.0
/*168 */         sector_num += n;                                                         // 0.0
/*170 */         buf += n * 512;                                                          // 0.0
/*172 */     }                                                                            // 0.0
/*176 */ done:                                                                            // 0.0
/*178 */     qemu_co_mutex_unlock(&s->lock);                                              // 0.0
/*182 */     if (qiov->niov > 1) {                                                        // 0.0
/*184 */         qemu_iovec_from_buf(qiov, 0, orig_buf, qiov->size);                      // 0.0
/*186 */         qemu_vfree(orig_buf);                                                    // 0.0
/*188 */     }                                                                            // 0.0
/*192 */     return ret;                                                                  // 0.0
/*196 */ fail:                                                                            // 0.0
/*198 */     error_free(err);                                                             // 0.0
/*200 */     ret = -EIO;                                                                  // 0.0
/*202 */     goto done;                                                                   // 0.0
/*204 */ }                                                                                // 0.0
