// commit message qemu@ab0997e0af (target=1, prob=0.39787036, correct=False): qcow2: remove memory leak
/*0   */ static int qcow2_co_writev(BlockDriverState *bs,                        // (12) 0.0332
/*2   */                            int64_t sector_num,                          // (2) 0.06641
/*4   */                            int remaining_sectors,                       // (3) 0.0625
/*6   */                            QEMUIOVector *qiov)                          // (1) 0.06836
/*8   */ {                                                                       // (24) 0.001953
/*10  */     BDRVQcowState *s = bs->opaque;                                      // (11) 0.03516
/*12  */     int index_in_cluster;                                               // (21) 0.02148
/*14  */     int n_end;                                                          // (22) 0.01562
/*16  */     int ret;                                                            // (23) 0.01172
/*18  */     int cur_nr_sectors; /* number of sectors in current iteration */    // (9) 0.03711
/*20  */     QCowL2Meta l2meta;                                                  // (19) 0.02344
/*22  */     uint64_t cluster_offset;                                            // (20) 0.02148
/*24  */     QEMUIOVector hd_qiov;                                               // (16) 0.02734
/*26  */     uint64_t bytes_done = 0;                                            // (18) 0.02539
/*28  */     uint8_t *cluster_data = NULL;                                       // (14) 0.0293
/*32  */     l2meta.nb_clusters = 0;                                             // (17) 0.02734
/*34  */     qemu_co_queue_init(&l2meta.dependent_requests);                     // (7) 0.04297
/*38  */     qemu_iovec_init(&hd_qiov, qiov->niov);                              // (5) 0.04687
/*42  */     s->cluster_cache_offset = -1; /* disable compressed cache */        // (8) 0.03906
/*46  */     qemu_co_mutex_lock(&s->lock);                                       // (10) 0.03516
/*50  */     while (remaining_sectors != 0) {                                    // (15) 0.02734
/*54  */         index_in_cluster = sector_num & (s->cluster_sectors - 1);       // (4) 0.05664
/*56  */         n_end = index_in_cluster + remaining_sectors;                   // (6) 0.04492
/*58  */         if (s->crypt_method &&                                          // (13) 0.0293
/*60  */             n_end > QCOW_MAX_CRYPT_CLUSTERS * s->cluster_sectors) {     // (0) 0.07227
/*62  */             n_end = QCOW_MAX_CRYPT_CLUSTERS * s->cluster_sectors;       // 0.0
/*64  */         }                                                               // 0.0
/*68  */         ret = qcow2_alloc_cluster_offset(bs, sector_num << 9,           // 0.0
/*70  */             index_in_cluster, n_end, &cur_nr_sectors, &l2meta);         // 0.0
/*72  */         if (ret < 0) {                                                  // 0.0
/*74  */             goto fail;                                                  // 0.0
/*76  */         }                                                               // 0.0
/*80  */         cluster_offset = l2meta.cluster_offset;                         // 0.0
/*82  */         assert((cluster_offset & 511) == 0);                            // 0.0
/*86  */         qemu_iovec_reset(&hd_qiov);                                     // 0.0
/*88  */         qemu_iovec_copy(&hd_qiov, qiov, bytes_done,                     // 0.0
/*90  */             cur_nr_sectors * 512);                                      // 0.0
/*94  */         if (s->crypt_method) {                                          // 0.0
/*96  */             if (!cluster_data) {                                        // 0.0
/*98  */                 cluster_data = g_malloc0(QCOW_MAX_CRYPT_CLUSTERS *      // 0.0
/*100 */                                                  s->cluster_size);      // 0.0
/*102 */             }                                                           // 0.0
/*106 */             assert(hd_qiov.size <=                                      // 0.0
/*108 */                    QCOW_MAX_CRYPT_CLUSTERS * s->cluster_size);          // 0.0
/*110 */             qemu_iovec_to_buffer(&hd_qiov, cluster_data);               // 0.0
/*114 */             qcow2_encrypt_sectors(s, sector_num, cluster_data,          // 0.0
/*116 */                 cluster_data, cur_nr_sectors, 1, &s->aes_encrypt_key);  // 0.0
/*120 */             qemu_iovec_reset(&hd_qiov);                                 // 0.0
/*122 */             qemu_iovec_add(&hd_qiov, cluster_data,                      // 0.0
/*124 */                 cur_nr_sectors * 512);                                  // 0.0
/*126 */         }                                                               // 0.0
/*130 */         BLKDBG_EVENT(bs->file, BLKDBG_WRITE_AIO);                       // 0.0
/*132 */         qemu_co_mutex_unlock(&s->lock);                                 // 0.0
/*134 */         ret = bdrv_co_writev(bs->file,                                  // 0.0
/*136 */                              (cluster_offset >> 9) + index_in_cluster,  // 0.0
/*138 */                              cur_nr_sectors, &hd_qiov);                 // 0.0
/*140 */         qemu_co_mutex_lock(&s->lock);                                   // 0.0
/*142 */         if (ret < 0) {                                                  // 0.0
/*144 */             goto fail;                                                  // 0.0
/*146 */         }                                                               // 0.0
/*150 */         ret = qcow2_alloc_cluster_link_l2(bs, &l2meta);                 // 0.0
/*154 */         run_dependent_requests(s, &l2meta);                             // 0.0
/*158 */         if (ret < 0) {                                                  // 0.0
/*160 */             goto fail;                                                  // 0.0
/*162 */         }                                                               // 0.0
/*166 */         remaining_sectors -= cur_nr_sectors;                            // 0.0
/*168 */         sector_num += cur_nr_sectors;                                   // 0.0
/*170 */         bytes_done += cur_nr_sectors * 512;                             // 0.0
/*172 */     }                                                                   // 0.0
/*174 */     ret = 0;                                                            // 0.0
/*178 */ fail:                                                                   // 0.0
/*180 */     qemu_co_mutex_unlock(&s->lock);                                     // 0.0
/*184 */     qemu_iovec_destroy(&hd_qiov);                                       // 0.0
/*189 */     return ret;                                                         // 0.0
/*191 */ }                                                                       // 0.0
