// commit message qemu@280d373579 (target=0, prob=0.35214052, correct=True): qcow2: Enable dirty flag in qcow2_alloc_cluster_link_l2
/*0   */ static coroutine_fn int qcow2_co_writev(BlockDriverState *bs,                     // (8) 0.04102
/*2   */                            int64_t sector_num,                                    // (2) 0.06641
/*4   */                            int remaining_sectors,                                 // (3) 0.0625
/*6   */                            QEMUIOVector *qiov)                                    // (1) 0.06836
/*8   */ {                                                                                 // (23) 0.001953
/*10  */     BDRVQcowState *s = bs->opaque;                                                // (11) 0.03516
/*12  */     int index_in_cluster;                                                         // (20) 0.02148
/*14  */     int n_end;                                                                    // (21) 0.01562
/*16  */     int ret;                                                                      // (22) 0.01172
/*18  */     int cur_nr_sectors; /* number of sectors in current iteration */              // (10) 0.03711
/*20  */     uint64_t cluster_offset;                                                      // (19) 0.02148
/*22  */     QEMUIOVector hd_qiov;                                                         // (15) 0.02734
/*24  */     uint64_t bytes_done = 0;                                                      // (18) 0.02539
/*26  */     uint8_t *cluster_data = NULL;                                                 // (13) 0.0293
/*28  */     QCowL2Meta *l2meta;                                                           // (16) 0.02539
/*32  */     trace_qcow2_writev_start_req(qemu_coroutine_self(), sector_num,               // (4) 0.05664
/*34  */                                  remaining_sectors);                              // (0) 0.07227
/*38  */     qemu_iovec_init(&hd_qiov, qiov->niov);                                        // (7) 0.04687
/*42  */     s->cluster_cache_offset = -1; /* disable compressed cache */                  // (9) 0.03906
/*46  */     qemu_co_mutex_lock(&s->lock);                                                 // (12) 0.03516
/*50  */     while (remaining_sectors != 0) {                                              // (14) 0.02734
/*54  */         l2meta = NULL;                                                            // (17) 0.02539
/*58  */         trace_qcow2_writev_start_part(qemu_coroutine_self());                     // (5) 0.05664
/*60  */         index_in_cluster = sector_num & (s->cluster_sectors - 1);                 // (6) 0.05664
/*62  */         n_end = index_in_cluster + remaining_sectors;                             // 0.0
/*64  */         if (s->crypt_method &&                                                    // 0.0
/*66  */             n_end > QCOW_MAX_CRYPT_CLUSTERS * s->cluster_sectors) {               // 0.0
/*68  */             n_end = QCOW_MAX_CRYPT_CLUSTERS * s->cluster_sectors;                 // 0.0
/*70  */         }                                                                         // 0.0
/*74  */         ret = qcow2_alloc_cluster_offset(bs, sector_num << 9,                     // 0.0
/*76  */             index_in_cluster, n_end, &cur_nr_sectors, &cluster_offset, &l2meta);  // 0.0
/*78  */         if (ret < 0) {                                                            // 0.0
/*80  */             goto fail;                                                            // 0.0
/*82  */         }                                                                         // 0.0
/*86  */         if (l2meta->nb_clusters > 0 &&                                            // 0.0
/*88  */             (s->compatible_features & QCOW2_COMPAT_LAZY_REFCOUNTS)) {             // 0.0
/*90  */             qcow2_mark_dirty(bs);                                                 // 0.0
/*92  */         }                                                                         // 0.0
/*96  */         assert((cluster_offset & 511) == 0);                                      // 0.0
/*100 */         qemu_iovec_reset(&hd_qiov);                                               // 0.0
/*102 */         qemu_iovec_concat(&hd_qiov, qiov, bytes_done,                             // 0.0
/*104 */             cur_nr_sectors * 512);                                                // 0.0
/*108 */         if (s->crypt_method) {                                                    // 0.0
/*110 */             if (!cluster_data) {                                                  // 0.0
/*112 */                 cluster_data = qemu_blockalign(bs, QCOW_MAX_CRYPT_CLUSTERS *      // 0.0
/*114 */                                                  s->cluster_size);                // 0.0
/*116 */             }                                                                     // 0.0
/*120 */             assert(hd_qiov.size <=                                                // 0.0
/*122 */                    QCOW_MAX_CRYPT_CLUSTERS * s->cluster_size);                    // 0.0
/*124 */             qemu_iovec_to_buf(&hd_qiov, 0, cluster_data, hd_qiov.size);           // 0.0
/*128 */             qcow2_encrypt_sectors(s, sector_num, cluster_data,                    // 0.0
/*130 */                 cluster_data, cur_nr_sectors, 1, &s->aes_encrypt_key);            // 0.0
/*134 */             qemu_iovec_reset(&hd_qiov);                                           // 0.0
/*136 */             qemu_iovec_add(&hd_qiov, cluster_data,                                // 0.0
/*138 */                 cur_nr_sectors * 512);                                            // 0.0
/*140 */         }                                                                         // 0.0
/*144 */         qemu_co_mutex_unlock(&s->lock);                                           // 0.0
/*146 */         BLKDBG_EVENT(bs->file, BLKDBG_WRITE_AIO);                                 // 0.0
/*148 */         trace_qcow2_writev_data(qemu_coroutine_self(),                            // 0.0
/*150 */                                 (cluster_offset >> 9) + index_in_cluster);        // 0.0
/*152 */         ret = bdrv_co_writev(bs->file,                                            // 0.0
/*154 */                              (cluster_offset >> 9) + index_in_cluster,            // 0.0
/*156 */                              cur_nr_sectors, &hd_qiov);                           // 0.0
/*158 */         qemu_co_mutex_lock(&s->lock);                                             // 0.0
/*160 */         if (ret < 0) {                                                            // 0.0
/*162 */             goto fail;                                                            // 0.0
/*164 */         }                                                                         // 0.0
/*168 */         if (l2meta != NULL) {                                                     // 0.0
/*170 */             ret = qcow2_alloc_cluster_link_l2(bs, l2meta);                        // 0.0
/*172 */             if (ret < 0) {                                                        // 0.0
/*174 */                 goto fail;                                                        // 0.0
/*176 */             }                                                                     // 0.0
/*180 */             run_dependent_requests(s, l2meta);                                    // 0.0
/*182 */             g_free(l2meta);                                                       // 0.0
/*184 */             l2meta = NULL;                                                        // 0.0
/*186 */         }                                                                         // 0.0
/*190 */         remaining_sectors -= cur_nr_sectors;                                      // 0.0
/*192 */         sector_num += cur_nr_sectors;                                             // 0.0
/*194 */         bytes_done += cur_nr_sectors * 512;                                       // 0.0
/*196 */         trace_qcow2_writev_done_part(qemu_coroutine_self(), cur_nr_sectors);      // 0.0
/*198 */     }                                                                             // 0.0
/*200 */     ret = 0;                                                                      // 0.0
/*204 */ fail:                                                                             // 0.0
/*206 */     if (l2meta != NULL) {                                                         // 0.0
/*208 */         run_dependent_requests(s, l2meta);                                        // 0.0
/*210 */         g_free(l2meta);                                                           // 0.0
/*212 */     }                                                                             // 0.0
/*216 */     qemu_co_mutex_unlock(&s->lock);                                               // 0.0
/*220 */     qemu_iovec_destroy(&hd_qiov);                                                 // 0.0
/*222 */     qemu_vfree(cluster_data);                                                     // 0.0
/*224 */     trace_qcow2_writev_done_req(qemu_coroutine_self(), ret);                      // 0.0
/*228 */     return ret;                                                                   // 0.0
/*230 */ }                                                                                 // 0.0
