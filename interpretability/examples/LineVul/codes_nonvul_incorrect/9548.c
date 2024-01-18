// commit message qemu@72cf2d4f0e (target=0, prob=0.77929205, correct=False): Fix sys-queue.h conflict for good
/*0   */ uint64_t qcow2_alloc_cluster_offset(BlockDriverState *bs,                        // (10) 0.04102
/*2   */                                     uint64_t offset,                             // (2) 0.08008
/*4   */                                     int n_start, int n_end,                      // (1) 0.08789
/*6   */                                     int *num, QCowL2Meta *m)                     // (0) 0.0918
/*8   */ {                                                                                // (19) 0.001953
/*10  */     BDRVQcowState *s = bs->opaque;                                               // (12) 0.03516
/*12  */     int l2_index, ret;                                                           // (16) 0.02148
/*14  */     uint64_t l2_offset, *l2_table, cluster_offset;                               // (9) 0.04297
/*16  */     int nb_clusters, i = 0;                                                      // (14) 0.02734
/*18  */     QCowL2Meta *old_alloc;                                                       // (15) 0.02539
/*22  */     ret = get_cluster_table(bs, offset, &l2_table, &l2_offset, &l2_index);       // (3) 0.06641
/*24  */     if (ret == 0)                                                                // (18) 0.01758
/*26  */         return 0;                                                                // (17) 0.01953
/*30  */     nb_clusters = size_to_clusters(s, n_end << 9);                               // (7) 0.04688
/*34  */     nb_clusters = MIN(nb_clusters, s->l2_size - l2_index);                       // (6) 0.05469
/*38  */     cluster_offset = be64_to_cpu(l2_table[l2_index]);                            // (8) 0.04687
/*42  */     /* We keep all QCOW_OFLAG_COPIED clusters */                                 // (13) 0.03516
/*46  */     if (cluster_offset & QCOW_OFLAG_COPIED) {                                    // (11) 0.04102
/*48  */         nb_clusters = count_contiguous_clusters(nb_clusters, s->cluster_size,    // (4) 0.06445
/*50  */                 &l2_table[l2_index], 0, 0);                                      // (5) 0.05859
/*54  */         cluster_offset &= ~QCOW_OFLAG_COPIED;                                    // 0.0
/*56  */         m->nb_clusters = 0;                                                      // 0.0
/*60  */         goto out;                                                                // 0.0
/*62  */     }                                                                            // 0.0
/*66  */     /* for the moment, multiple compressed clusters are not managed */           // 0.0
/*70  */     if (cluster_offset & QCOW_OFLAG_COMPRESSED)                                  // 0.0
/*72  */         nb_clusters = 1;                                                         // 0.0
/*76  */     /* how many available clusters ? */                                          // 0.0
/*80  */     while (i < nb_clusters) {                                                    // 0.0
/*82  */         i += count_contiguous_clusters(nb_clusters - i, s->cluster_size,         // 0.0
/*84  */                 &l2_table[l2_index], i, 0);                                      // 0.0
/*88  */         if(be64_to_cpu(l2_table[l2_index + i]))                                  // 0.0
/*90  */             break;                                                               // 0.0
/*94  */         i += count_contiguous_free_clusters(nb_clusters - i,                     // 0.0
/*96  */                 &l2_table[l2_index + i]);                                        // 0.0
/*100 */         cluster_offset = be64_to_cpu(l2_table[l2_index + i]);                    // 0.0
/*104 */         if ((cluster_offset & QCOW_OFLAG_COPIED) ||                              // 0.0
/*106 */                 (cluster_offset & QCOW_OFLAG_COMPRESSED))                        // 0.0
/*108 */             break;                                                               // 0.0
/*110 */     }                                                                            // 0.0
/*112 */     nb_clusters = i;                                                             // 0.0
/*116 */     /*                                                                           // 0.0
/*118 */      * Check if there already is an AIO write request in flight which allocates  // 0.0
/*120 */      * the same cluster. In this case we need to wait until the previous         // 0.0
/*122 */      * request has completed and updated the L2 table accordingly.               // 0.0
/*124 */      */                                                                          // 0.0
/*126 */     LIST_FOREACH(old_alloc, &s->cluster_allocs, next_in_flight) {                // 0.0
/*130 */         uint64_t end_offset = offset + nb_clusters * s->cluster_size;            // 0.0
/*132 */         uint64_t old_offset = old_alloc->offset;                                 // 0.0
/*134 */         uint64_t old_end_offset = old_alloc->offset +                            // 0.0
/*136 */             old_alloc->nb_clusters * s->cluster_size;                            // 0.0
/*140 */         if (end_offset < old_offset || offset > old_end_offset) {                // 0.0
/*142 */             /* No intersection */                                                // 0.0
/*144 */         } else {                                                                 // 0.0
/*146 */             if (offset < old_offset) {                                           // 0.0
/*148 */                 /* Stop at the start of a running allocation */                  // 0.0
/*150 */                 nb_clusters = (old_offset - offset) >> s->cluster_bits;          // 0.0
/*152 */             } else {                                                             // 0.0
/*154 */                 nb_clusters = 0;                                                 // 0.0
/*156 */             }                                                                    // 0.0
/*160 */             if (nb_clusters == 0) {                                              // 0.0
/*162 */                 /* Set dependency and wait for a callback */                     // 0.0
/*164 */                 m->depends_on = old_alloc;                                       // 0.0
/*166 */                 m->nb_clusters = 0;                                              // 0.0
/*168 */                 *num = 0;                                                        // 0.0
/*170 */                 return 0;                                                        // 0.0
/*172 */             }                                                                    // 0.0
/*174 */         }                                                                        // 0.0
/*176 */     }                                                                            // 0.0
/*180 */     if (!nb_clusters) {                                                          // 0.0
/*182 */         abort();                                                                 // 0.0
/*184 */     }                                                                            // 0.0
/*188 */     LIST_INSERT_HEAD(&s->cluster_allocs, m, next_in_flight);                     // 0.0
/*192 */     /* allocate a new cluster */                                                 // 0.0
/*196 */     cluster_offset = qcow2_alloc_clusters(bs, nb_clusters * s->cluster_size);    // 0.0
/*200 */     /* save info needed for meta data update */                                  // 0.0
/*202 */     m->offset = offset;                                                          // 0.0
/*204 */     m->n_start = n_start;                                                        // 0.0
/*206 */     m->nb_clusters = nb_clusters;                                                // 0.0
/*210 */ out:                                                                             // 0.0
/*212 */     m->nb_available = MIN(nb_clusters << (s->cluster_bits - 9), n_end);          // 0.0
/*216 */     *num = m->nb_available - n_start;                                            // 0.0
/*220 */     return cluster_offset;                                                       // 0.0
/*222 */ }                                                                                // 0.0
