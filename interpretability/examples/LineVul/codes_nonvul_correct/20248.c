// commit message qemu@8a5bb1f114 (target=0, prob=0.458622, correct=True): qcow2-refcount: rename inc_refcounts() and make it public
/*0  */ static int inc_refcounts(BlockDriverState *bs,                                    // (17) 0.02734
/*2  */                          BdrvCheckResult *res,                                    // (3) 0.0625
/*4  */                          void **refcount_table,                                   // (4) 0.06055
/*6  */                          int64_t *refcount_table_size,                            // (2) 0.07031
/*8  */                          int64_t offset, int64_t size)                            // (1) 0.07031
/*10 */ {                                                                                 // (23) 0.001953
/*12 */     BDRVQcow2State *s = bs->opaque;                                               // (11) 0.03711
/*14 */     uint64_t start, last, cluster_offset, k, refcount;                            // (7) 0.03906
/*16 */     int ret;                                                                      // (21) 0.01172
/*20 */     if (size <= 0) {                                                              // (19) 0.01953
/*22 */         return 0;                                                                 // (20) 0.01953
/*24 */     }                                                                             // (22) 0.007812
/*28 */     start = start_of_cluster(s, offset);                                          // (16) 0.03125
/*30 */     last = start_of_cluster(s, offset + size - 1);                                // (8) 0.03906
/*32 */     for(cluster_offset = start; cluster_offset <= last;                           // (13) 0.03516
/*34 */         cluster_offset += s->cluster_size) {                                      // (12) 0.03711
/*36 */         k = cluster_offset >> s->cluster_bits;                                    // (9) 0.03906
/*38 */         if (k >= *refcount_table_size) {                                          // (10) 0.03906
/*40 */             ret = realloc_refcount_array(s, refcount_table,                       // (5) 0.05469
/*42 */                                          refcount_table_size, k + 1);             // (0) 0.09961
/*44 */             if (ret < 0) {                                                        // (14) 0.03516
/*46 */                 res->check_errors++;                                              // (6) 0.04102
/*48 */                 return ret;                                                       // (15) 0.03516
/*50 */             }                                                                     // (18) 0.02344
/*52 */         }                                                                         // 0.0
/*56 */         refcount = s->get_refcount(*refcount_table, k);                           // 0.0
/*58 */         if (refcount == s->refcount_max) {                                        // 0.0
/*60 */             fprintf(stderr, "ERROR: overflow cluster offset=0x%" PRIx64           // 0.0
/*62 */                     "\n", cluster_offset);                                        // 0.0
/*64 */             fprintf(stderr, "Use qemu-img amend to increase the refcount entry "  // 0.0
/*66 */                     "width or qemu-img convert to create a clean copy if the "    // 0.0
/*68 */                     "image cannot be opened for writing\n");                      // 0.0
/*70 */             res->corruptions++;                                                   // 0.0
/*72 */             continue;                                                             // 0.0
/*74 */         }                                                                         // 0.0
/*76 */         s->set_refcount(*refcount_table, k, refcount + 1);                        // 0.0
/*78 */     }                                                                             // 0.0
/*82 */     return 0;                                                                     // 0.0
/*84 */ }                                                                                 // 0.0
