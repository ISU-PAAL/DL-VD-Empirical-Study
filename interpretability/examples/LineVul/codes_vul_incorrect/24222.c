// commit message qemu@ab0997e0af (target=1, prob=0.42729053, correct=False): qcow2: remove memory leak
/*0   */ static int qcow2_co_readv(BlockDriverState *bs, int64_t sector_num,            // (5) 0.04883
/*2   */                           int remaining_sectors, QEMUIOVector *qiov)           // (0) 0.07812
/*4   */ {                                                                              // (25) 0.001953
/*6   */     BDRVQcowState *s = bs->opaque;                                             // (10) 0.03516
/*8   */     int index_in_cluster, n1;                                                  // (14) 0.02734
/*10  */     int ret;                                                                   // (24) 0.01172
/*12  */     int cur_nr_sectors; /* number of sectors in current iteration */           // (8) 0.03711
/*14  */     uint64_t cluster_offset = 0;                                               // (19) 0.02539
/*16  */     uint64_t bytes_done = 0;                                                   // (20) 0.02539
/*18  */     QEMUIOVector hd_qiov;                                                      // (16) 0.02734
/*20  */     uint8_t *cluster_data = NULL;                                              // (13) 0.0293
/*24  */     qemu_iovec_init(&hd_qiov, qiov->niov);                                     // (7) 0.04687
/*28  */     qemu_co_mutex_lock(&s->lock);                                              // (11) 0.03516
/*32  */     while (remaining_sectors != 0) {                                           // (15) 0.02734
/*36  */         /* prepare next request */                                             // (21) 0.02344
/*38  */         cur_nr_sectors = remaining_sectors;                                    // (9) 0.03711
/*40  */         if (s->crypt_method) {                                                 // (12) 0.03125
/*42  */             cur_nr_sectors = MIN(cur_nr_sectors,                               // (4) 0.05273
/*44  */                 QCOW_MAX_CRYPT_CLUSTERS * s->cluster_sectors);                 // (1) 0.07031
/*46  */         }                                                                      // (22) 0.01562
/*50  */         ret = qcow2_get_cluster_offset(bs, sector_num << 9,                    // (3) 0.05469
/*52  */             &cur_nr_sectors, &cluster_offset);                                 // (6) 0.04883
/*54  */         if (ret < 0) {                                                         // (17) 0.02734
/*56  */             goto fail;                                                         // (18) 0.02734
/*58  */         }                                                                      // (23) 0.01562
/*62  */         index_in_cluster = sector_num & (s->cluster_sectors - 1);              // (2) 0.05664
/*66  */         qemu_iovec_reset(&hd_qiov);                                            // 0.0
/*68  */         qemu_iovec_copy(&hd_qiov, qiov, bytes_done,                            // 0.0
/*70  */             cur_nr_sectors * 512);                                             // 0.0
/*74  */         if (!cluster_offset) {                                                 // 0.0
/*78  */             if (bs->backing_hd) {                                              // 0.0
/*80  */                 /* read from the base image */                                 // 0.0
/*82  */                 n1 = qcow2_backing_read1(bs->backing_hd, &hd_qiov,             // 0.0
/*84  */                     sector_num, cur_nr_sectors);                               // 0.0
/*86  */                 if (n1 > 0) {                                                  // 0.0
/*88  */                     BLKDBG_EVENT(bs->file, BLKDBG_READ_BACKING_AIO);           // 0.0
/*90  */                     qemu_co_mutex_unlock(&s->lock);                            // 0.0
/*92  */                     ret = bdrv_co_readv(bs->backing_hd, sector_num,            // 0.0
/*94  */                                         n1, &hd_qiov);                         // 0.0
/*96  */                     qemu_co_mutex_lock(&s->lock);                              // 0.0
/*98  */                     if (ret < 0) {                                             // 0.0
/*100 */                         goto fail;                                             // 0.0
/*102 */                     }                                                          // 0.0
/*104 */                 }                                                              // 0.0
/*106 */             } else {                                                           // 0.0
/*108 */                 /* Note: in this case, no need to wait */                      // 0.0
/*110 */                 qemu_iovec_memset(&hd_qiov, 0, 512 * cur_nr_sectors);          // 0.0
/*112 */             }                                                                  // 0.0
/*114 */         } else if (cluster_offset & QCOW_OFLAG_COMPRESSED) {                   // 0.0
/*116 */             /* add AIO support for compressed blocks ? */                      // 0.0
/*118 */             ret = qcow2_decompress_cluster(bs, cluster_offset);                // 0.0
/*120 */             if (ret < 0) {                                                     // 0.0
/*122 */                 goto fail;                                                     // 0.0
/*124 */             }                                                                  // 0.0
/*128 */             qemu_iovec_from_buffer(&hd_qiov,                                   // 0.0
/*130 */                 s->cluster_cache + index_in_cluster * 512,                     // 0.0
/*132 */                 512 * cur_nr_sectors);                                         // 0.0
/*134 */         } else {                                                               // 0.0
/*136 */             if ((cluster_offset & 511) != 0) {                                 // 0.0
/*138 */                 ret = -EIO;                                                    // 0.0
/*140 */                 goto fail;                                                     // 0.0
/*142 */             }                                                                  // 0.0
/*146 */             if (s->crypt_method) {                                             // 0.0
/*148 */                 /*                                                             // 0.0
/*150 */                  * For encrypted images, read everything into a temporary      // 0.0
/*152 */                  * contiguous buffer on which the AES functions can work.      // 0.0
/*154 */                  */                                                            // 0.0
/*156 */                 if (!cluster_data) {                                           // 0.0
/*158 */                     cluster_data =                                             // 0.0
/*160 */                         g_malloc0(QCOW_MAX_CRYPT_CLUSTERS * s->cluster_size);  // 0.0
/*162 */                 }                                                              // 0.0
/*166 */                 assert(cur_nr_sectors <=                                       // 0.0
/*168 */                     QCOW_MAX_CRYPT_CLUSTERS * s->cluster_sectors);             // 0.0
/*170 */                 qemu_iovec_reset(&hd_qiov);                                    // 0.0
/*172 */                 qemu_iovec_add(&hd_qiov, cluster_data,                         // 0.0
/*174 */                     512 * cur_nr_sectors);                                     // 0.0
/*176 */             }                                                                  // 0.0
/*180 */             BLKDBG_EVENT(bs->file, BLKDBG_READ_AIO);                           // 0.0
/*182 */             qemu_co_mutex_unlock(&s->lock);                                    // 0.0
/*184 */             ret = bdrv_co_readv(bs->file,                                      // 0.0
/*186 */                                 (cluster_offset >> 9) + index_in_cluster,      // 0.0
/*188 */                                 cur_nr_sectors, &hd_qiov);                     // 0.0
/*190 */             qemu_co_mutex_lock(&s->lock);                                      // 0.0
/*192 */             if (ret < 0) {                                                     // 0.0
/*194 */                 goto fail;                                                     // 0.0
/*196 */             }                                                                  // 0.0
/*198 */             if (s->crypt_method) {                                             // 0.0
/*200 */                 qcow2_encrypt_sectors(s, sector_num,  cluster_data,            // 0.0
/*202 */                     cluster_data, cur_nr_sectors, 0, &s->aes_decrypt_key);     // 0.0
/*204 */                 qemu_iovec_reset(&hd_qiov);                                    // 0.0
/*206 */                 qemu_iovec_copy(&hd_qiov, qiov, bytes_done,                    // 0.0
/*208 */                     cur_nr_sectors * 512);                                     // 0.0
/*210 */                 qemu_iovec_from_buffer(&hd_qiov, cluster_data,                 // 0.0
/*212 */                     512 * cur_nr_sectors);                                     // 0.0
/*214 */             }                                                                  // 0.0
/*216 */         }                                                                      // 0.0
/*220 */         remaining_sectors -= cur_nr_sectors;                                   // 0.0
/*222 */         sector_num += cur_nr_sectors;                                          // 0.0
/*224 */         bytes_done += cur_nr_sectors * 512;                                    // 0.0
/*226 */     }                                                                          // 0.0
/*228 */     ret = 0;                                                                   // 0.0
/*232 */ fail:                                                                          // 0.0
/*234 */     qemu_co_mutex_unlock(&s->lock);                                            // 0.0
/*238 */     qemu_iovec_destroy(&hd_qiov);                                              // 0.0
/*243 */     return ret;                                                                // 0.0
/*245 */ }                                                                              // 0.0
