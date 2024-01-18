// commit message qemu@7453c96b78 (target=1, prob=0.5160828, correct=True): qcow2: Helper function for refcount modification
/*0   */ static int check_refcounts_l1(BlockDriverState *bs,                            // (12) 0.0332
/*2   */                               BdrvCheckResult *res,                            // (3) 0.07227
/*4   */                               uint16_t **refcount_table,                       // (2) 0.07617
/*6   */                               int64_t *refcount_table_size,                    // (1) 0.08008
/*8   */                               int64_t l1_table_offset, int l1_size,            // (0) 0.08984
/*10  */                               int flags)                                       // (5) 0.0625
/*12  */ {                                                                              // (21) 0.001953
/*14  */     BDRVQcowState *s = bs->opaque;                                             // (10) 0.03516
/*16  */     uint64_t *l1_table = NULL, l2_offset, l1_size2;                            // (7) 0.05078
/*18  */     int i, ret;                                                                // (19) 0.01562
/*22  */     l1_size2 = l1_size * sizeof(uint64_t);                                     // (9) 0.04102
/*26  */     /* Mark L1 table as used */                                                // (16) 0.02148
/*28  */     ret = inc_refcounts(bs, res, refcount_table, refcount_table_size,          // (6) 0.05273
/*30  */                         l1_table_offset, l1_size2);                            // (4) 0.07031
/*32  */     if (ret < 0) {                                                             // (18) 0.01953
/*34  */         goto fail;                                                             // (17) 0.01953
/*36  */     }                                                                          // (20) 0.007812
/*40  */     /* Read L1 table entries from disk */                                      // (15) 0.02344
/*42  */     if (l1_size2 > 0) {                                                        // (14) 0.02734
/*44  */         l1_table = g_try_malloc(l1_size2);                                     // (8) 0.04883
/*46  */         if (l1_table == NULL) {                                                // (13) 0.0332
/*48  */             ret = -ENOMEM;                                                     // (11) 0.03516
/*50  */             res->check_errors++;                                               // 0.0
/*52  */             goto fail;                                                         // 0.0
/*54  */         }                                                                      // 0.0
/*56  */         ret = bdrv_pread(bs->file, l1_table_offset, l1_table, l1_size2);       // 0.0
/*58  */         if (ret < 0) {                                                         // 0.0
/*60  */             fprintf(stderr, "ERROR: I/O error in check_refcounts_l1\n");       // 0.0
/*62  */             res->check_errors++;                                               // 0.0
/*64  */             goto fail;                                                         // 0.0
/*66  */         }                                                                      // 0.0
/*68  */         for(i = 0;i < l1_size; i++)                                            // 0.0
/*70  */             be64_to_cpus(&l1_table[i]);                                        // 0.0
/*72  */     }                                                                          // 0.0
/*76  */     /* Do the actual checks */                                                 // 0.0
/*78  */     for(i = 0; i < l1_size; i++) {                                             // 0.0
/*80  */         l2_offset = l1_table[i];                                               // 0.0
/*82  */         if (l2_offset) {                                                       // 0.0
/*84  */             /* Mark L2 table as used */                                        // 0.0
/*86  */             l2_offset &= L1E_OFFSET_MASK;                                      // 0.0
/*88  */             ret = inc_refcounts(bs, res, refcount_table, refcount_table_size,  // 0.0
/*90  */                                 l2_offset, s->cluster_size);                   // 0.0
/*92  */             if (ret < 0) {                                                     // 0.0
/*94  */                 goto fail;                                                     // 0.0
/*96  */             }                                                                  // 0.0
/*100 */             /* L2 tables are cluster aligned */                                // 0.0
/*102 */             if (offset_into_cluster(s, l2_offset)) {                           // 0.0
/*104 */                 fprintf(stderr, "ERROR l2_offset=%" PRIx64 ": Table is not "   // 0.0
/*106 */                     "cluster aligned; L1 entry corrupted\n", l2_offset);       // 0.0
/*108 */                 res->corruptions++;                                            // 0.0
/*110 */             }                                                                  // 0.0
/*114 */             /* Process and check L2 entries */                                 // 0.0
/*116 */             ret = check_refcounts_l2(bs, res, refcount_table,                  // 0.0
/*118 */                                      refcount_table_size, l2_offset, flags);   // 0.0
/*120 */             if (ret < 0) {                                                     // 0.0
/*122 */                 goto fail;                                                     // 0.0
/*124 */             }                                                                  // 0.0
/*126 */         }                                                                      // 0.0
/*128 */     }                                                                          // 0.0
/*130 */     g_free(l1_table);                                                          // 0.0
/*132 */     return 0;                                                                  // 0.0
/*136 */ fail:                                                                          // 0.0
/*138 */     g_free(l1_table);                                                          // 0.0
/*140 */     return ret;                                                                // 0.0
/*142 */ }                                                                              // 0.0
