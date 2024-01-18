// commit message qemu@e97fc193e1 (target=0, prob=0.62859136, correct=False): Introduce bdrv_check (Kevin Wolf)
/*0   */ static void check_refcounts(BlockDriverState *bs)                           // (16) 0.02734
/*2   */ {                                                                           // (24) 0.001953
/*4   */     BDRVQcowState *s = bs->opaque;                                          // (13) 0.03516
/*6   */     int64_t size;                                                           // (19) 0.01758
/*8   */     int nb_clusters, refcount1, refcount2, i;                               // (11) 0.03906
/*10  */     QCowSnapshot *sn;                                                       // (18) 0.01953
/*12  */     uint16_t *refcount_table;                                               // (17) 0.02539
/*16  */     size = bdrv_getlength(s->hd);                                           // (14) 0.03125
/*18  */     nb_clusters = size_to_clusters(s, size);                                // (12) 0.03906
/*20  */     refcount_table = qemu_mallocz(nb_clusters * sizeof(uint16_t));          // (4) 0.05469
/*24  */     /* header */                                                            // (22) 0.01172
/*26  */     inc_refcounts(bs, refcount_table, nb_clusters,                          // (9) 0.04297
/*28  */                   0, s->cluster_size);                                      // (5) 0.05078
/*32  */     check_refcounts_l1(bs, refcount_table, nb_clusters,                     // (6) 0.04883
/*34  */                        s->l1_table_offset, s->l1_size, 1);                  // (1) 0.07813
/*38  */     /* snapshots */                                                         // (21) 0.01172
/*40  */     for(i = 0; i < s->nb_snapshots; i++) {                                  // (10) 0.04102
/*42  */         sn = s->snapshots + i;                                              // (15) 0.03125
/*44  */         check_refcounts_l1(bs, refcount_table, nb_clusters,                 // (3) 0.05664
/*46  */                            sn->l1_table_offset, sn->l1_size, 0);            // (0) 0.08594
/*48  */     }                                                                       // (23) 0.007812
/*50  */     inc_refcounts(bs, refcount_table, nb_clusters,                          // (8) 0.04297
/*52  */                   s->snapshots_offset, s->snapshots_size);                  // (2) 0.06055
/*56  */     /* refcount data */                                                     // (20) 0.01563
/*58  */     inc_refcounts(bs, refcount_table, nb_clusters,                          // (7) 0.04297
/*60  */                   s->refcount_table_offset,                                 // 0.0
/*62  */                   s->refcount_table_size * sizeof(uint64_t));               // 0.0
/*64  */     for(i = 0; i < s->refcount_table_size; i++) {                           // 0.0
/*66  */         int64_t offset;                                                     // 0.0
/*68  */         offset = s->refcount_table[i];                                      // 0.0
/*70  */         if (offset != 0) {                                                  // 0.0
/*72  */             inc_refcounts(bs, refcount_table, nb_clusters,                  // 0.0
/*74  */                           offset, s->cluster_size);                         // 0.0
/*76  */         }                                                                   // 0.0
/*78  */     }                                                                       // 0.0
/*82  */     /* compare ref counts */                                                // 0.0
/*84  */     for(i = 0; i < nb_clusters; i++) {                                      // 0.0
/*86  */         refcount1 = get_refcount(bs, i);                                    // 0.0
/*88  */         refcount2 = refcount_table[i];                                      // 0.0
/*90  */         if (refcount1 != refcount2)                                         // 0.0
/*92  */             fprintf(stderr, "ERROR cluster %d refcount=%d reference=%d\n",  // 0.0
/*94  */                    i, refcount1, refcount2);                                // 0.0
/*96  */     }                                                                       // 0.0
/*100 */     qemu_free(refcount_table);                                              // 0.0
/*102 */ }                                                                           // 0.0
