// commit message qemu@713d9675e0 (target=0, prob=0.4343078, correct=True): qcow2: Use int64_t for in-memory reftable size
/*0  */ static void inc_refcounts(BlockDriverState *bs,                                  // (17) 0.02734
/*2  */                           BdrvCheckResult *res,                                  // (4) 0.06445
/*4  */                           uint16_t *refcount_table,                              // (2) 0.06836
/*6  */                           int refcount_table_size,                               // (5) 0.06445
/*8  */                           int64_t offset, int64_t size)                          // (0) 0.07227
/*10 */ {                                                                                // (21) 0.001953
/*12 */     BDRVQcowState *s = bs->opaque;                                               // (12) 0.03516
/*14 */     uint64_t start, last, cluster_offset, k;                                     // (14) 0.0332
/*18 */     if (size <= 0)                                                               // (19) 0.01758
/*20 */         return;                                                                  // (20) 0.01758
/*24 */     start = start_of_cluster(s, offset);                                         // (16) 0.03125
/*26 */     last = start_of_cluster(s, offset + size - 1);                               // (8) 0.03906
/*28 */     for(cluster_offset = start; cluster_offset <= last;                          // (13) 0.03516
/*30 */         cluster_offset += s->cluster_size) {                                     // (11) 0.03711
/*32 */         k = cluster_offset >> s->cluster_bits;                                   // (7) 0.03906
/*34 */         if (k >= refcount_table_size) {                                          // (9) 0.03711
/*36 */             fprintf(stderr, "Warning: cluster offset=0x%" PRIx64 " is after "    // (1) 0.06836
/*38 */                 "the end of the image file, can't properly check refcounts.\n",  // (3) 0.06641
/*40 */                 cluster_offset);                                                 // (10) 0.03711
/*42 */             res->check_errors++;                                                 // (15) 0.0332
/*44 */         } else {                                                                 // (18) 0.01953
/*46 */             if (++refcount_table[k] == 0) {                                      // (6) 0.04883
/*48 */                 fprintf(stderr, "ERROR: overflow cluster offset=0x%" PRIx64      // 0.0
/*50 */                     "\n", cluster_offset);                                       // 0.0
/*52 */                 res->corruptions++;                                              // 0.0
/*54 */             }                                                                    // 0.0
/*56 */         }                                                                        // 0.0
/*58 */     }                                                                            // 0.0
/*60 */ }                                                                                // 0.0
