// commit message qemu@b6d36def6d (target=0, prob=0.32795036, correct=True): qcow2: Make size_to_clusters() return uint64_t
/*0   */ static int discard_single_l2(BlockDriverState *bs, uint64_t offset,              // (9) 0.04102
/*2   */     unsigned int nb_clusters, enum qcow2_discard_type type, bool full_discard)   // (2) 0.05469
/*4   */ {                                                                                // (26) 0.001953
/*6   */     BDRVQcow2State *s = bs->opaque;                                              // (12) 0.03711
/*8   */     uint64_t *l2_table;                                                          // (16) 0.02539
/*10  */     int l2_index;                                                                // (19) 0.01758
/*12  */     int ret;                                                                     // (23) 0.01172
/*14  */     int i;                                                                       // (24) 0.01172
/*18  */     ret = get_cluster_table(bs, offset, &l2_table, &l2_index);                   // (3) 0.05469
/*20  */     if (ret < 0) {                                                               // (17) 0.01953
/*22  */         return ret;                                                              // (18) 0.01953
/*24  */     }                                                                            // (25) 0.007812
/*28  */     /* Limit nb_clusters to one L2 table */                                      // (14) 0.03125
/*30  */     nb_clusters = MIN(nb_clusters, s->l2_size - l2_index);                       // (4) 0.05469
/*34  */     for (i = 0; i < nb_clusters; i++) {                                          // (11) 0.03906
/*36  */         uint64_t old_l2_entry;                                                   // (13) 0.03516
/*40  */         old_l2_entry = be64_to_cpu(l2_table[l2_index + i]);                      // (0) 0.06445
/*44  */         /*                                                                       // (22) 0.01563
/*46  */          * If full_discard is false, make sure that a discarded area reads back  // (6) 0.04883
/*48  */          * as zeroes for v3 images (we cannot do it for v2 without actually      // (5) 0.05273
/*50  */          * writing a zero-filled buffer). We can skip the operation if the       // (8) 0.04492
/*52  */          * cluster is already marked as zero, or if it's unallocated and we      // (7) 0.04883
/*54  */          * don't have a backing file.                                            // (15) 0.03125
/*56  */          *                                                                       // (20) 0.01758
/*58  */          * TODO We might want to use bdrv_get_block_status(bs) here, but we're   // (1) 0.06445
/*60  */          * holding s->lock, so that doesn't work today.                          // (10) 0.04102
/*62  */          *                                                                       // (21) 0.01758
/*64  */          * If full_discard is true, the sector should not read back as zeroes,   // 0.0
/*66  */          * but rather fall through to the backing file.                          // 0.0
/*68  */          */                                                                      // 0.0
/*70  */         switch (qcow2_get_cluster_type(old_l2_entry)) {                          // 0.0
/*72  */             case QCOW2_CLUSTER_UNALLOCATED:                                      // 0.0
/*74  */                 if (full_discard || !bs->backing_hd) {                           // 0.0
/*76  */                     continue;                                                    // 0.0
/*78  */                 }                                                                // 0.0
/*80  */                 break;                                                           // 0.0
/*84  */             case QCOW2_CLUSTER_ZERO:                                             // 0.0
/*86  */                 if (!full_discard) {                                             // 0.0
/*88  */                     continue;                                                    // 0.0
/*90  */                 }                                                                // 0.0
/*92  */                 break;                                                           // 0.0
/*96  */             case QCOW2_CLUSTER_NORMAL:                                           // 0.0
/*98  */             case QCOW2_CLUSTER_COMPRESSED:                                       // 0.0
/*100 */                 break;                                                           // 0.0
/*104 */             default:                                                             // 0.0
/*106 */                 abort();                                                         // 0.0
/*108 */         }                                                                        // 0.0
/*112 */         /* First remove L2 entries */                                            // 0.0
/*114 */         qcow2_cache_entry_mark_dirty(bs, s->l2_table_cache, l2_table);           // 0.0
/*116 */         if (!full_discard && s->qcow_version >= 3) {                             // 0.0
/*118 */             l2_table[l2_index + i] = cpu_to_be64(QCOW_OFLAG_ZERO);               // 0.0
/*120 */         } else {                                                                 // 0.0
/*122 */             l2_table[l2_index + i] = cpu_to_be64(0);                             // 0.0
/*124 */         }                                                                        // 0.0
/*128 */         /* Then decrease the refcount */                                         // 0.0
/*130 */         qcow2_free_any_clusters(bs, old_l2_entry, 1, type);                      // 0.0
/*132 */     }                                                                            // 0.0
/*136 */     qcow2_cache_put(bs, s->l2_table_cache, (void **) &l2_table);                 // 0.0
/*140 */     return nb_clusters;                                                          // 0.0
/*142 */ }                                                                                // 0.0
