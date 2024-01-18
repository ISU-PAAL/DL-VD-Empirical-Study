// commit message qemu@80ee15a6b2 (target=1, prob=0.5179284, correct=True): qcow2: Increase maximum cluster size to 2 MB
/*0   */ uint64_t qcow2_get_cluster_offset(BlockDriverState *bs, uint64_t offset,       // (1) 0.05273
/*2   */     int *num)                                                                  // (26) 0.01367
/*4   */ {                                                                              // (29) 0.001953
/*6   */     BDRVQcowState *s = bs->opaque;                                             // (8) 0.03516
/*8   */     int l1_index, l2_index;                                                    // (17) 0.02734
/*10  */     uint64_t l2_offset, *l2_table, cluster_offset;                             // (5) 0.04297
/*12  */     int l1_bits, c;                                                            // (20) 0.02148
/*14  */     int index_in_cluster, nb_available, nb_needed, nb_clusters;                // (2) 0.05273
/*18  */     index_in_cluster = (offset >> 9) & (s->cluster_sectors - 1);               // (3) 0.05273
/*20  */     nb_needed = *num + index_in_cluster;                                       // (9) 0.03516
/*24  */     l1_bits = s->l2_bits + s->cluster_bits;                                    // (6) 0.04297
/*28  */     /* compute how many bytes there are between the offset and                 // (16) 0.02734
/*30  */      * the end of the l1 entry                                                 // (18) 0.02344
/*32  */      */                                                                        // (27) 0.009766
/*36  */     nb_available = (1 << l1_bits) - (offset & ((1 << l1_bits) - 1));           // (0) 0.06055
/*40  */     /* compute the number of available sectors */                              // (21) 0.02148
/*44  */     nb_available = (nb_available >> 9) + index_in_cluster;                     // (4) 0.04492
/*48  */     if (nb_needed > nb_available) {                                            // (14) 0.0293
/*50  */         nb_needed = nb_available;                                              // (11) 0.0332
/*52  */     }                                                                          // (28) 0.007812
/*56  */     cluster_offset = 0;                                                        // (25) 0.01758
/*60  */     /* seek the the l2 offset in the l1 table */                               // (12) 0.03125
/*64  */     l1_index = offset >> l1_bits;                                              // (15) 0.0293
/*66  */     if (l1_index >= s->l1_size)                                                // (10) 0.0332
/*68  */         goto out;                                                              // (23) 0.01953
/*72  */     l2_offset = s->l1_table[l1_index];                                         // (7) 0.03906
/*76  */     /* seek the l2 table of the given l2 offset */                             // (13) 0.03125
/*80  */     if (!l2_offset)                                                            // (22) 0.01953
/*82  */         goto out;                                                              // (24) 0.01953
/*86  */     /* load the l2 table in memory */                                          // (19) 0.02344
/*90  */     l2_offset &= ~QCOW_OFLAG_COPIED;                                           // 0.0
/*92  */     l2_table = l2_load(bs, l2_offset);                                         // 0.0
/*94  */     if (l2_table == NULL)                                                      // 0.0
/*96  */         return 0;                                                              // 0.0
/*100 */     /* find the cluster offset for the given disk offset */                    // 0.0
/*104 */     l2_index = (offset >> s->cluster_bits) & (s->l2_size - 1);                 // 0.0
/*106 */     cluster_offset = be64_to_cpu(l2_table[l2_index]);                          // 0.0
/*108 */     nb_clusters = size_to_clusters(s, nb_needed << 9);                         // 0.0
/*112 */     if (!cluster_offset) {                                                     // 0.0
/*114 */         /* how many empty clusters ? */                                        // 0.0
/*116 */         c = count_contiguous_free_clusters(nb_clusters, &l2_table[l2_index]);  // 0.0
/*118 */     } else {                                                                   // 0.0
/*120 */         /* how many allocated clusters ? */                                    // 0.0
/*122 */         c = count_contiguous_clusters(nb_clusters, s->cluster_size,            // 0.0
/*124 */                 &l2_table[l2_index], 0, QCOW_OFLAG_COPIED);                    // 0.0
/*126 */     }                                                                          // 0.0
/*130 */    nb_available = (c * s->cluster_sectors);                                    // 0.0
/*132 */ out:                                                                           // 0.0
/*134 */     if (nb_available > nb_needed)                                              // 0.0
/*136 */         nb_available = nb_needed;                                              // 0.0
/*140 */     *num = nb_available - index_in_cluster;                                    // 0.0
/*144 */     return cluster_offset & ~QCOW_OFLAG_COPIED;                                // 0.0
/*146 */ }                                                                              // 0.0
