// commit message qemu@8a5bb1f114 (target=0, prob=0.4377181, correct=True): qcow2-refcount: rename inc_refcounts() and make it public
/*0   */ static int check_refblocks(BlockDriverState *bs, BdrvCheckResult *res,           // (7) 0.04102
/*2   */                            BdrvCheckMode fix, bool *rebuild,                     // (2) 0.07422
/*4   */                            void **refcount_table, int64_t *nb_clusters)          // (0) 0.08398
/*6   */ {                                                                                // (21) 0.001953
/*8   */     BDRVQcow2State *s = bs->opaque;                                              // (9) 0.03711
/*10  */     int64_t i, size;                                                             // (18) 0.02148
/*12  */     int ret;                                                                     // (20) 0.01172
/*16  */     for(i = 0; i < s->refcount_table_size; i++) {                                // (6) 0.04492
/*18  */         uint64_t offset, cluster;                                                // (16) 0.0293
/*20  */         offset = s->refcount_table[i];                                           // (12) 0.03516
/*22  */         cluster = offset >> s->cluster_bits;                                     // (11) 0.03516
/*26  */         /* Refcount blocks are cluster aligned */                                // (15) 0.0293
/*28  */         if (offset_into_cluster(s, offset)) {                                    // (8) 0.04102
/*30  */             fprintf(stderr, "ERROR refcount block %" PRId64 " is not "           // (4) 0.0625
/*32  */                 "cluster aligned; refcount table entry corrupted\n", i);         // (5) 0.05859
/*34  */             res->corruptions++;                                                  // (13) 0.0332
/*36  */             *rebuild = true;                                                     // (14) 0.0332
/*38  */             continue;                                                            // (17) 0.02539
/*40  */         }                                                                        // (19) 0.01562
/*44  */         if (cluster >= *nb_clusters) {                                           // (10) 0.03711
/*46  */             fprintf(stderr, "%s refcount block %" PRId64 " is outside image\n",  // (3) 0.06836
/*48  */                     fix & BDRV_FIX_ERRORS ? "Repairing" : "ERROR", i);           // (1) 0.08008
/*52  */             if (fix & BDRV_FIX_ERRORS) {                                         // 0.0
/*54  */                 int64_t new_nb_clusters;                                         // 0.0
/*56  */                 Error *local_err = NULL;                                         // 0.0
/*60  */                 if (offset > INT64_MAX - s->cluster_size) {                      // 0.0
/*62  */                     ret = -EINVAL;                                               // 0.0
/*64  */                     goto resize_fail;                                            // 0.0
/*66  */                 }                                                                // 0.0
/*70  */                 ret = bdrv_truncate(bs->file, offset + s->cluster_size,          // 0.0
/*72  */                                     &local_err);                                 // 0.0
/*74  */                 if (ret < 0) {                                                   // 0.0
/*76  */                     error_report_err(local_err);                                 // 0.0
/*78  */                     goto resize_fail;                                            // 0.0
/*80  */                 }                                                                // 0.0
/*82  */                 size = bdrv_getlength(bs->file->bs);                             // 0.0
/*84  */                 if (size < 0) {                                                  // 0.0
/*86  */                     ret = size;                                                  // 0.0
/*88  */                     goto resize_fail;                                            // 0.0
/*90  */                 }                                                                // 0.0
/*94  */                 new_nb_clusters = size_to_clusters(s, size);                     // 0.0
/*96  */                 assert(new_nb_clusters >= *nb_clusters);                         // 0.0
/*100 */                 ret = realloc_refcount_array(s, refcount_table,                  // 0.0
/*102 */                                              nb_clusters, new_nb_clusters);      // 0.0
/*104 */                 if (ret < 0) {                                                   // 0.0
/*106 */                     res->check_errors++;                                         // 0.0
/*108 */                     return ret;                                                  // 0.0
/*110 */                 }                                                                // 0.0
/*114 */                 if (cluster >= *nb_clusters) {                                   // 0.0
/*116 */                     ret = -EINVAL;                                               // 0.0
/*118 */                     goto resize_fail;                                            // 0.0
/*120 */                 }                                                                // 0.0
/*124 */                 res->corruptions_fixed++;                                        // 0.0
/*126 */                 ret = inc_refcounts(bs, res, refcount_table, nb_clusters,        // 0.0
/*128 */                                     offset, s->cluster_size);                    // 0.0
/*130 */                 if (ret < 0) {                                                   // 0.0
/*132 */                     return ret;                                                  // 0.0
/*134 */                 }                                                                // 0.0
/*136 */                 /* No need to check whether the refcount is now greater than 1:  // 0.0
/*138 */                  * This area was just allocated and zeroed, so it can only be    // 0.0
/*140 */                  * exactly 1 after inc_refcounts() */                            // 0.0
/*142 */                 continue;                                                        // 0.0
/*146 */ resize_fail:                                                                     // 0.0
/*148 */                 res->corruptions++;                                              // 0.0
/*150 */                 *rebuild = true;                                                 // 0.0
/*152 */                 fprintf(stderr, "ERROR could not resize image: %s\n",            // 0.0
/*154 */                         strerror(-ret));                                         // 0.0
/*156 */             } else {                                                             // 0.0
/*158 */                 res->corruptions++;                                              // 0.0
/*160 */             }                                                                    // 0.0
/*162 */             continue;                                                            // 0.0
/*164 */         }                                                                        // 0.0
/*168 */         if (offset != 0) {                                                       // 0.0
/*170 */             ret = inc_refcounts(bs, res, refcount_table, nb_clusters,            // 0.0
/*172 */                                 offset, s->cluster_size);                        // 0.0
/*174 */             if (ret < 0) {                                                       // 0.0
/*176 */                 return ret;                                                      // 0.0
/*178 */             }                                                                    // 0.0
/*180 */             if (s->get_refcount(*refcount_table, cluster) != 1) {                // 0.0
/*182 */                 fprintf(stderr, "ERROR refcount block %" PRId64                  // 0.0
/*184 */                         " refcount=%" PRIu64 "\n", i,                            // 0.0
/*186 */                         s->get_refcount(*refcount_table, cluster));              // 0.0
/*188 */                 res->corruptions++;                                              // 0.0
/*190 */                 *rebuild = true;                                                 // 0.0
/*192 */             }                                                                    // 0.0
/*194 */         }                                                                        // 0.0
/*196 */     }                                                                            // 0.0
/*200 */     return 0;                                                                    // 0.0
/*202 */ }                                                                                // 0.0
