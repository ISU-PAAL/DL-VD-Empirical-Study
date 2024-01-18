// commit message qemu@8a5bb1f114 (target=0, prob=0.581603, correct=False): qcow2-refcount: rename inc_refcounts() and make it public
/*0   */ static int calculate_refcounts(BlockDriverState *bs, BdrvCheckResult *res,       // (7) 0.04297
/*2   */                                BdrvCheckMode fix, bool *rebuild,                 // (2) 0.08203
/*4   */                                void **refcount_table, int64_t *nb_clusters)      // (0) 0.0918
/*6   */ {                                                                                // (24) 0.001953
/*8   */     BDRVQcow2State *s = bs->opaque;                                              // (8) 0.03711
/*10  */     int64_t i;                                                                   // (17) 0.01758
/*12  */     QCowSnapshot *sn;                                                            // (14) 0.01953
/*14  */     int ret;                                                                     // (20) 0.01172
/*18  */     if (!*refcount_table) {                                                      // (13) 0.02344
/*20  */         int64_t old_size = 0;                                                    // (9) 0.0332
/*22  */         ret = realloc_refcount_array(s, refcount_table,                          // (6) 0.04688
/*24  */                                      &old_size, *nb_clusters);                   // (1) 0.0918
/*26  */         if (ret < 0) {                                                           // (11) 0.02734
/*28  */             res->check_errors++;                                                 // (10) 0.0332
/*30  */             return ret;                                                          // (12) 0.02734
/*32  */         }                                                                        // (19) 0.01562
/*34  */     }                                                                            // (22) 0.007812
/*38  */     /* header */                                                                 // (21) 0.01172
/*40  */     ret = inc_refcounts(bs, res, refcount_table, nb_clusters,                    // (5) 0.05078
/*42  */                         0, s->cluster_size);                                     // (3) 0.0625
/*44  */     if (ret < 0) {                                                               // (15) 0.01953
/*46  */         return ret;                                                              // (16) 0.01953
/*48  */     }                                                                            // (23) 0.007812
/*52  */     /* current L1 table */                                                       // (18) 0.01758
/*54  */     ret = check_refcounts_l1(bs, res, refcount_table, nb_clusters,               // (4) 0.05664
/*56  */                              s->l1_table_offset, s->l1_size, CHECK_FRAG_INFO);   // 0.0
/*58  */     if (ret < 0) {                                                               // 0.0
/*60  */         return ret;                                                              // 0.0
/*62  */     }                                                                            // 0.0
/*66  */     /* snapshots */                                                              // 0.0
/*68  */     for (i = 0; i < s->nb_snapshots; i++) {                                      // 0.0
/*70  */         sn = s->snapshots + i;                                                   // 0.0
/*72  */         ret = check_refcounts_l1(bs, res, refcount_table, nb_clusters,           // 0.0
/*74  */                                  sn->l1_table_offset, sn->l1_size, 0);           // 0.0
/*76  */         if (ret < 0) {                                                           // 0.0
/*78  */             return ret;                                                          // 0.0
/*80  */         }                                                                        // 0.0
/*82  */     }                                                                            // 0.0
/*84  */     ret = inc_refcounts(bs, res, refcount_table, nb_clusters,                    // 0.0
/*86  */                         s->snapshots_offset, s->snapshots_size);                 // 0.0
/*88  */     if (ret < 0) {                                                               // 0.0
/*90  */         return ret;                                                              // 0.0
/*92  */     }                                                                            // 0.0
/*96  */     /* refcount data */                                                          // 0.0
/*98  */     ret = inc_refcounts(bs, res, refcount_table, nb_clusters,                    // 0.0
/*100 */                         s->refcount_table_offset,                                // 0.0
/*102 */                         s->refcount_table_size * sizeof(uint64_t));              // 0.0
/*104 */     if (ret < 0) {                                                               // 0.0
/*106 */         return ret;                                                              // 0.0
/*108 */     }                                                                            // 0.0
/*112 */     /* encryption */                                                             // 0.0
/*114 */     if (s->crypto_header.length) {                                               // 0.0
/*116 */         ret = inc_refcounts(bs, res, refcount_table, nb_clusters,                // 0.0
/*118 */                             s->crypto_header.offset,                             // 0.0
/*120 */                             s->crypto_header.length);                            // 0.0
/*122 */         if (ret < 0) {                                                           // 0.0
/*124 */             return ret;                                                          // 0.0
/*126 */         }                                                                        // 0.0
/*128 */     }                                                                            // 0.0
/*132 */     return check_refblocks(bs, res, fix, rebuild, refcount_table, nb_clusters);  // 0.0
/*134 */ }                                                                                // 0.0
