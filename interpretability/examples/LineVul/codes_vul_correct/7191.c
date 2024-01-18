// commit message qemu@a890643958 (target=1, prob=0.76735413, correct=True): util/qht: atomically set b->hashes
/*0  */ static bool qht_insert__locked(struct qht *ht, struct qht_map *map,              // (6) 0.04492
/*2  */                                struct qht_bucket *head, void *p, uint32_t hash,  // (0) 0.0957
/*4  */                                bool *needs_resize)                               // (1) 0.07227
/*6  */ {                                                                                // (27) 0.001953
/*8  */     struct qht_bucket *b = head;                                                 // (13) 0.02734
/*10 */     struct qht_bucket *prev = NULL;                                              // (14) 0.02734
/*12 */     struct qht_bucket *new = NULL;                                               // (15) 0.02734
/*14 */     int i;                                                                       // (25) 0.01172
/*18 */     do {                                                                         // (26) 0.009766
/*20 */         for (i = 0; i < QHT_BUCKET_ENTRIES; i++) {                               // (3) 0.05664
/*22 */             if (b->pointers[i]) {                                                // (8) 0.03906
/*24 */                 if (unlikely(b->pointers[i] == p)) {                             // (2) 0.05859
/*26 */                     return false;                                                // (7) 0.04297
/*28 */                 }                                                                // (11) 0.03125
/*30 */             } else {                                                             // (16) 0.02734
/*32 */                 goto found;                                                      // (9) 0.03516
/*34 */             }                                                                    // (19) 0.02344
/*36 */         }                                                                        // (21) 0.01562
/*38 */         prev = b;                                                                // (20) 0.02148
/*40 */         b = b->next;                                                             // (18) 0.02539
/*42 */     } while (b);                                                                 // (22) 0.01562
/*46 */     b = qemu_memalign(QHT_BUCKET_ALIGN, sizeof(*b));                             // (5) 0.05078
/*48 */     memset(b, 0, sizeof(*b));                                                    // (17) 0.02734
/*50 */     new = b;                                                                     // (23) 0.01367
/*52 */     i = 0;                                                                       // (24) 0.01367
/*54 */     atomic_inc(&map->n_added_buckets);                                           // (10) 0.03125
/*56 */     if (unlikely(qht_map_needs_resize(map)) && needs_resize) {                   // (4) 0.05273
/*58 */         *needs_resize = true;                                                    // (12) 0.0293
/*60 */     }                                                                            // 0.0
/*64 */  found:                                                                          // 0.0
/*66 */     /* found an empty key: acquire the seqlock and write */                      // 0.0
/*68 */     seqlock_write_begin(&head->sequence);                                        // 0.0
/*70 */     if (new) {                                                                   // 0.0
/*72 */         atomic_rcu_set(&prev->next, b);                                          // 0.0
/*74 */     }                                                                            // 0.0
/*76 */     b->hashes[i] = hash;                                                         // 0.0
/*78 */     /* smp_wmb() implicit in seqlock_write_begin.  */                            // 0.0
/*80 */     atomic_set(&b->pointers[i], p);                                              // 0.0
/*82 */     seqlock_write_end(&head->sequence);                                          // 0.0
/*84 */     return true;                                                                 // 0.0
/*86 */ }                                                                                // 0.0
