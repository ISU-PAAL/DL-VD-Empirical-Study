// commit message qemu@a3f1afb43a (target=0, prob=0.35008255, correct=True): qcow2: make qcow2_cache_put() a void function
/*0  */ static int zero_single_l2(BlockDriverState *bs, uint64_t offset,                // (8) 0.04102
/*2  */     unsigned int nb_clusters)                                                   // (15) 0.02148
/*4  */ {                                                                               // (25) 0.001953
/*6  */     BDRVQcowState *s = bs->opaque;                                              // (10) 0.03516
/*8  */     uint64_t *l2_table;                                                         // (13) 0.02539
/*10 */     int l2_index;                                                               // (19) 0.01758
/*12 */     int ret;                                                                    // (21) 0.01172
/*14 */     int i;                                                                      // (22) 0.01172
/*18 */     ret = get_cluster_table(bs, offset, &l2_table, &l2_index);                  // (5) 0.05469
/*20 */     if (ret < 0) {                                                              // (16) 0.01953
/*22 */         return ret;                                                             // (17) 0.01953
/*24 */     }                                                                           // (23) 0.007812
/*28 */     /* Limit nb_clusters to one L2 table */                                     // (11) 0.03125
/*30 */     nb_clusters = MIN(nb_clusters, s->l2_size - l2_index);                      // (6) 0.05469
/*34 */     for (i = 0; i < nb_clusters; i++) {                                         // (9) 0.03906
/*36 */         uint64_t old_offset;                                                    // (12) 0.0293
/*40 */         old_offset = be64_to_cpu(l2_table[l2_index + i]);                       // (4) 0.05859
/*44 */         /* Update L2 entries */                                                 // (14) 0.02539
/*46 */         qcow2_cache_entry_mark_dirty(bs, s->l2_table_cache, l2_table);          // (3) 0.06836
/*48 */         if (old_offset & QCOW_OFLAG_COMPRESSED) {                               // (7) 0.04688
/*50 */             l2_table[l2_index + i] = cpu_to_be64(QCOW_OFLAG_ZERO);              // (2) 0.08008
/*52 */             qcow2_free_any_clusters(bs, old_offset, 1, QCOW2_DISCARD_REQUEST);  // (1) 0.08008
/*54 */         } else {                                                                // (18) 0.01953
/*56 */             l2_table[l2_index + i] |= cpu_to_be64(QCOW_OFLAG_ZERO);             // (0) 0.08203
/*58 */         }                                                                       // (20) 0.01562
/*60 */     }                                                                           // (24) 0.007812
/*64 */     ret = qcow2_cache_put(bs, s->l2_table_cache, (void**) &l2_table);           // 0.0
/*66 */     if (ret < 0) {                                                              // 0.0
/*68 */         return ret;                                                             // 0.0
/*70 */     }                                                                           // 0.0
/*74 */     return nb_clusters;                                                         // 0.0
/*76 */ }                                                                               // 0.0
