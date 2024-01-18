// commit message qemu@641bb63cd6 (target=0, prob=0.42298076, correct=True): qcow2: Let inc_refcounts() resize the reftable
/*0  */ static int inc_refcounts(BlockDriverState *bs,                                   // (17) 0.02734
/*2  */                          BdrvCheckResult *res,                                   // (5) 0.0625
/*4  */                          uint16_t *refcount_table,                               // (4) 0.06641
/*6  */                          int64_t refcount_table_size,                            // (2) 0.06836
/*8  */                          int64_t offset, int64_t size)                           // (0) 0.07031
/*10 */ {                                                                                // (22) 0.001953
/*12 */     BDRVQcowState *s = bs->opaque;                                               // (12) 0.03516
/*14 */     uint64_t start, last, cluster_offset, k;                                     // (14) 0.0332
/*18 */     if (size <= 0) {                                                             // (18) 0.01953
/*20 */         return 0;                                                                // (19) 0.01953
/*22 */     }                                                                            // (21) 0.007812
/*26 */     start = start_of_cluster(s, offset);                                         // (16) 0.03125
/*28 */     last = start_of_cluster(s, offset + size - 1);                               // (7) 0.03906
/*30 */     for(cluster_offset = start; cluster_offset <= last;                          // (13) 0.03516
/*32 */         cluster_offset += s->cluster_size) {                                     // (9) 0.03711
/*34 */         k = cluster_offset >> s->cluster_bits;                                   // (8) 0.03906
/*36 */         if (k >= refcount_table_size) {                                          // (10) 0.03711
/*38 */             fprintf(stderr, "Warning: cluster offset=0x%" PRIx64 " is after "    // (1) 0.06836
/*40 */                 "the end of the image file, can't properly check refcounts.\n",  // (3) 0.06641
/*42 */                 cluster_offset);                                                 // (11) 0.03711
/*44 */             res->check_errors++;                                                 // (15) 0.0332
/*46 */         } else {                                                                 // (20) 0.01953
/*48 */             if (++refcount_table[k] == 0) {                                      // (6) 0.04883
/*50 */                 fprintf(stderr, "ERROR: overflow cluster offset=0x%" PRIx64      // 0.0
/*52 */                     "\n", cluster_offset);                                       // 0.0
/*54 */                 res->corruptions++;                                              // 0.0
/*56 */             }                                                                    // 0.0
/*58 */         }                                                                        // 0.0
/*60 */     }                                                                            // 0.0
/*64 */     return 0;                                                                    // 0.0
/*66 */ }                                                                                // 0.0
