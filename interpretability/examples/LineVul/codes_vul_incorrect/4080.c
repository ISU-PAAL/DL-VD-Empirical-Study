// commit message qemu@14fe292d86 (target=1, prob=0.2649723, correct=False): qed: do not evict in-use L2 table cache entries
/*0  */ void qed_commit_l2_cache_entry(L2TableCache *l2_cache, CachedL2Table *l2_table)  // (0) 0.1015
/*2  */ {                                                                                // (16) 0.002985
/*4  */     CachedL2Table *entry;                                                        // (11) 0.03284
/*8  */     entry = qed_find_l2_cache_entry(l2_cache, l2_table->offset);                 // (2) 0.08657
/*10 */     if (entry) {                                                                 // (13) 0.02388
/*12 */         qed_unref_l2_cache_entry(entry);                                         // (7) 0.06567
/*14 */         qed_unref_l2_cache_entry(l2_table);                                      // (5) 0.07463
/*16 */         return;                                                                  // (12) 0.02687
/*18 */     }                                                                            // (14) 0.01194
/*22 */     if (l2_cache->n_entries >= MAX_L2_CACHE_SIZE) {                              // (4) 0.0806
/*24 */         entry = QTAILQ_FIRST(&l2_cache->entries);                                // (6) 0.07463
/*26 */         QTAILQ_REMOVE(&l2_cache->entries, entry, node);                          // (3) 0.08358
/*28 */         l2_cache->n_entries--;                                                   // (9) 0.05373
/*30 */         qed_unref_l2_cache_entry(entry);                                         // (8) 0.06567
/*32 */     }                                                                            // (15) 0.01194
/*36 */     l2_cache->n_entries++;                                                       // (10) 0.03881
/*38 */     QTAILQ_INSERT_TAIL(&l2_cache->entries, l2_table, node);                      // (1) 0.08657
/*40 */ }                                                                                // (17) 0.002985
