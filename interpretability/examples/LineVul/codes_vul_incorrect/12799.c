// commit message qemu@de82815db1 (target=1, prob=0.38204673, correct=False): qcow2: Handle failure for potentially large allocations
/*0   */ int qcow2_expand_zero_clusters(BlockDriverState *bs)                             // (11) 0.03711
/*2   */ {                                                                                // (25) 0.001953
/*4   */     BDRVQcowState *s = bs->opaque;                                               // (13) 0.03516
/*6   */     uint64_t *l1_table = NULL;                                                   // (15) 0.0293
/*8   */     uint64_t nb_clusters;                                                        // (17) 0.02539
/*10  */     uint8_t *expanded_clusters;                                                  // (16) 0.02734
/*12  */     int ret;                                                                     // (23) 0.01172
/*14  */     int i, j;                                                                    // (22) 0.01563
/*18  */     nb_clusters = size_to_clusters(s, bs->file->total_sectors *                  // (3) 0.05469
/*20  */                                    BDRV_SECTOR_SIZE);                            // (1) 0.08594
/*22  */     expanded_clusters = g_malloc0((nb_clusters + 7) / 8);                        // (4) 0.04688
/*26  */     ret = expand_zero_clusters_in_l1(bs, s->l1_table, s->l1_size,                // (2) 0.06445
/*28  */                                      &expanded_clusters, &nb_clusters);          // (0) 0.0957
/*30  */     if (ret < 0) {                                                               // (20) 0.01953
/*32  */         goto fail;                                                               // (19) 0.01953
/*34  */     }                                                                            // (24) 0.007813
/*38  */     /* Inactive L1 tables may point to active L2 tables - therefore it is        // (9) 0.03906
/*40  */      * necessary to flush the L2 table cache before trying to access the L2      // (6) 0.03906
/*42  */      * tables pointed to by inactive L1 entries (else we might try to expand     // (7) 0.03906
/*44  */      * zero clusters that have already been expanded); furthermore, it is also   // (14) 0.03516
/*46  */      * necessary to empty the L2 table cache, since it may contain tables which  // (10) 0.03906
/*48  */      * are now going to be modified directly on disk, bypassing the cache.       // (8) 0.03906
/*50  */      * qcow2_cache_empty() does both for us. */                                  // (12) 0.03711
/*52  */     ret = qcow2_cache_empty(bs, s->l2_table_cache);                              // (5) 0.04688
/*54  */     if (ret < 0) {                                                               // (21) 0.01953
/*56  */         goto fail;                                                               // (18) 0.01953
/*58  */     }                                                                            // 0.0
/*62  */     for (i = 0; i < s->nb_snapshots; i++) {                                      // 0.0
/*64  */         int l1_sectors = (s->snapshots[i].l1_size * sizeof(uint64_t) +           // 0.0
/*66  */                 BDRV_SECTOR_SIZE - 1) / BDRV_SECTOR_SIZE;                        // 0.0
/*70  */         l1_table = g_realloc(l1_table, l1_sectors * BDRV_SECTOR_SIZE);           // 0.0
/*74  */         ret = bdrv_read(bs->file, s->snapshots[i].l1_table_offset /              // 0.0
/*76  */                 BDRV_SECTOR_SIZE, (void *)l1_table, l1_sectors);                 // 0.0
/*78  */         if (ret < 0) {                                                           // 0.0
/*80  */             goto fail;                                                           // 0.0
/*82  */         }                                                                        // 0.0
/*86  */         for (j = 0; j < s->snapshots[i].l1_size; j++) {                          // 0.0
/*88  */             be64_to_cpus(&l1_table[j]);                                          // 0.0
/*90  */         }                                                                        // 0.0
/*94  */         ret = expand_zero_clusters_in_l1(bs, l1_table, s->snapshots[i].l1_size,  // 0.0
/*96  */                                          &expanded_clusters, &nb_clusters);      // 0.0
/*98  */         if (ret < 0) {                                                           // 0.0
/*100 */             goto fail;                                                           // 0.0
/*102 */         }                                                                        // 0.0
/*104 */     }                                                                            // 0.0
/*108 */     ret = 0;                                                                     // 0.0
/*112 */ fail:                                                                            // 0.0
/*114 */     g_free(expanded_clusters);                                                   // 0.0
/*116 */     g_free(l1_table);                                                            // 0.0
/*118 */     return ret;                                                                  // 0.0
/*120 */ }                                                                                // 0.0
