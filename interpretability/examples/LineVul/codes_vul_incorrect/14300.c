// commit message qemu@f80ac75d0e (target=1, prob=0.48211384, correct=False): qcow2: fix null pointer dereference
/*0   */ static int rebuild_refcount_structure(BlockDriverState *bs,                       // (15) 0.03125
/*2   */                                       BdrvCheckResult *res,                       // (1) 0.08789
/*4   */                                       void **refcount_table,                      // (2) 0.08594
/*6   */                                       int64_t *nb_clusters)                       // (0) 0.0918
/*8   */ {                                                                                 // (23) 0.001953
/*10  */     BDRVQcow2State *s = bs->opaque;                                               // (10) 0.03711
/*12  */     int64_t first_free_cluster = 0, reftable_offset = -1, cluster = 0;            // (3) 0.05664
/*14  */     int64_t refblock_offset, refblock_start, refblock_index;                      // (9) 0.04297
/*16  */     uint32_t reftable_size = 0;                                                   // (16) 0.0293
/*18  */     uint64_t *on_disk_reftable = NULL;                                            // (11) 0.03516
/*20  */     void *on_disk_refblock;                                                       // (18) 0.02344
/*22  */     int ret = 0;                                                                  // (19) 0.01563
/*24  */     struct {                                                                      // (22) 0.009766
/*26  */         uint64_t reftable_offset;                                                 // (14) 0.0332
/*28  */         uint32_t reftable_clusters;                                               // (12) 0.03516
/*30  */     } QEMU_PACKED reftable_offset_and_clusters;                                   // (7) 0.04297
/*34  */     qcow2_cache_empty(bs, s->refcount_block_cache);                               // (8) 0.04297
/*38  */ write_refblocks:                                                                  // (21) 0.009766
/*40  */     for (; cluster < *nb_clusters; cluster++) {                                   // (13) 0.0332
/*42  */         if (!s->get_refcount(*refcount_table, cluster)) {                         // (5) 0.04688
/*44  */             continue;                                                             // (17) 0.02539
/*46  */         }                                                                         // (20) 0.01562
/*50  */         refblock_index = cluster >> s->refcount_block_bits;                       // (6) 0.04492
/*52  */         refblock_start = refblock_index << s->refcount_block_bits;                // (4) 0.05078
/*56  */         /* Don't allocate a cluster in a refblock already written to disk */      // 0.0
/*58  */         if (first_free_cluster < refblock_start) {                                // 0.0
/*60  */             first_free_cluster = refblock_start;                                  // 0.0
/*62  */         }                                                                         // 0.0
/*64  */         refblock_offset = alloc_clusters_imrt(bs, 1, refcount_table,              // 0.0
/*66  */                                               nb_clusters, &first_free_cluster);  // 0.0
/*68  */         if (refblock_offset < 0) {                                                // 0.0
/*70  */             fprintf(stderr, "ERROR allocating refblock: %s\n",                    // 0.0
/*72  */                     strerror(-refblock_offset));                                  // 0.0
/*74  */             res->check_errors++;                                                  // 0.0
/*76  */             ret = refblock_offset;                                                // 0.0
/*78  */             goto fail;                                                            // 0.0
/*80  */         }                                                                         // 0.0
/*84  */         if (reftable_size <= refblock_index) {                                    // 0.0
/*86  */             uint32_t old_reftable_size = reftable_size;                           // 0.0
/*88  */             uint64_t *new_on_disk_reftable;                                       // 0.0
/*92  */             reftable_size = ROUND_UP((refblock_index + 1) * sizeof(uint64_t),     // 0.0
/*94  */                                      s->cluster_size) / sizeof(uint64_t);         // 0.0
/*96  */             new_on_disk_reftable = g_try_realloc(on_disk_reftable,                // 0.0
/*98  */                                                  reftable_size *                  // 0.0
/*100 */                                                  sizeof(uint64_t));               // 0.0
/*102 */             if (!new_on_disk_reftable) {                                          // 0.0
/*104 */                 res->check_errors++;                                              // 0.0
/*106 */                 ret = -ENOMEM;                                                    // 0.0
/*108 */                 goto fail;                                                        // 0.0
/*110 */             }                                                                     // 0.0
/*112 */             on_disk_reftable = new_on_disk_reftable;                              // 0.0
/*116 */             memset(on_disk_reftable + old_reftable_size, 0,                       // 0.0
/*118 */                    (reftable_size - old_reftable_size) * sizeof(uint64_t));       // 0.0
/*122 */             /* The offset we have for the reftable is now no longer valid;        // 0.0
/*124 */              * this will leak that range, but we can easily fix that by running   // 0.0
/*126 */              * a leak-fixing check after this rebuild operation */                // 0.0
/*128 */             reftable_offset = -1;                                                 // 0.0
/*130 */         }                                                                         // 0.0
/*132 */         on_disk_reftable[refblock_index] = refblock_offset;                       // 0.0
/*136 */         /* If this is apparently the last refblock (for now), try to squeeze the  // 0.0
/*138 */          * reftable in */                                                         // 0.0
/*140 */         if (refblock_index == (*nb_clusters - 1) >> s->refcount_block_bits &&     // 0.0
/*142 */             reftable_offset < 0)                                                  // 0.0
/*144 */         {                                                                         // 0.0
/*146 */             uint64_t reftable_clusters = size_to_clusters(s, reftable_size *      // 0.0
/*148 */                                                           sizeof(uint64_t));      // 0.0
/*150 */             reftable_offset = alloc_clusters_imrt(bs, reftable_clusters,          // 0.0
/*152 */                                                   refcount_table, nb_clusters,    // 0.0
/*154 */                                                   &first_free_cluster);           // 0.0
/*156 */             if (reftable_offset < 0) {                                            // 0.0
/*158 */                 fprintf(stderr, "ERROR allocating reftable: %s\n",                // 0.0
/*160 */                         strerror(-reftable_offset));                              // 0.0
/*162 */                 res->check_errors++;                                              // 0.0
/*164 */                 ret = reftable_offset;                                            // 0.0
/*166 */                 goto fail;                                                        // 0.0
/*168 */             }                                                                     // 0.0
/*170 */         }                                                                         // 0.0
/*174 */         ret = qcow2_pre_write_overlap_check(bs, 0, refblock_offset,               // 0.0
/*176 */                                             s->cluster_size);                     // 0.0
/*178 */         if (ret < 0) {                                                            // 0.0
/*180 */             fprintf(stderr, "ERROR writing refblock: %s\n", strerror(-ret));      // 0.0
/*182 */             goto fail;                                                            // 0.0
/*184 */         }                                                                         // 0.0
/*188 */         /* The size of *refcount_table is always cluster-aligned, therefore the   // 0.0
/*190 */          * write operation will not overflow */                                   // 0.0
/*192 */         on_disk_refblock = (void *)((char *) *refcount_table +                    // 0.0
/*194 */                                     refblock_index * s->cluster_size);            // 0.0
/*198 */         ret = bdrv_write(bs->file, refblock_offset / BDRV_SECTOR_SIZE,            // 0.0
/*200 */                          on_disk_refblock, s->cluster_sectors);                   // 0.0
/*202 */         if (ret < 0) {                                                            // 0.0
/*204 */             fprintf(stderr, "ERROR writing refblock: %s\n", strerror(-ret));      // 0.0
/*206 */             goto fail;                                                            // 0.0
/*208 */         }                                                                         // 0.0
/*212 */         /* Go to the end of this refblock */                                      // 0.0
/*214 */         cluster = refblock_start + s->refcount_block_size - 1;                    // 0.0
/*216 */     }                                                                             // 0.0
/*220 */     if (reftable_offset < 0) {                                                    // 0.0
/*222 */         uint64_t post_refblock_start, reftable_clusters;                          // 0.0
/*226 */         post_refblock_start = ROUND_UP(*nb_clusters, s->refcount_block_size);     // 0.0
/*228 */         reftable_clusters = size_to_clusters(s,                                   // 0.0
/*230 */                                              reftable_size * sizeof(uint64_t));   // 0.0
/*232 */         /* Not pretty but simple */                                               // 0.0
/*234 */         if (first_free_cluster < post_refblock_start) {                           // 0.0
/*236 */             first_free_cluster = post_refblock_start;                             // 0.0
/*238 */         }                                                                         // 0.0
/*240 */         reftable_offset = alloc_clusters_imrt(bs, reftable_clusters,              // 0.0
/*242 */                                               refcount_table, nb_clusters,        // 0.0
/*244 */                                               &first_free_cluster);               // 0.0
/*246 */         if (reftable_offset < 0) {                                                // 0.0
/*248 */             fprintf(stderr, "ERROR allocating reftable: %s\n",                    // 0.0
/*250 */                     strerror(-reftable_offset));                                  // 0.0
/*252 */             res->check_errors++;                                                  // 0.0
/*254 */             ret = reftable_offset;                                                // 0.0
/*256 */             goto fail;                                                            // 0.0
/*258 */         }                                                                         // 0.0
/*262 */         goto write_refblocks;                                                     // 0.0
/*264 */     }                                                                             // 0.0
/*268 */     assert(on_disk_reftable);                                                     // 0.0
/*272 */     for (refblock_index = 0; refblock_index < reftable_size; refblock_index++) {  // 0.0
/*274 */         cpu_to_be64s(&on_disk_reftable[refblock_index]);                          // 0.0
/*276 */     }                                                                             // 0.0
/*280 */     ret = qcow2_pre_write_overlap_check(bs, 0, reftable_offset,                   // 0.0
/*282 */                                         reftable_size * sizeof(uint64_t));        // 0.0
/*284 */     if (ret < 0) {                                                                // 0.0
/*286 */         fprintf(stderr, "ERROR writing reftable: %s\n", strerror(-ret));          // 0.0
/*288 */         goto fail;                                                                // 0.0
/*290 */     }                                                                             // 0.0
/*294 */     assert(reftable_size < INT_MAX / sizeof(uint64_t));                           // 0.0
/*296 */     ret = bdrv_pwrite(bs->file, reftable_offset, on_disk_reftable,                // 0.0
/*298 */                       reftable_size * sizeof(uint64_t));                          // 0.0
/*300 */     if (ret < 0) {                                                                // 0.0
/*302 */         fprintf(stderr, "ERROR writing reftable: %s\n", strerror(-ret));          // 0.0
/*304 */         goto fail;                                                                // 0.0
/*306 */     }                                                                             // 0.0
/*310 */     /* Enter new reftable into the image header */                                // 0.0
/*312 */     reftable_offset_and_clusters.reftable_offset = cpu_to_be64(reftable_offset);  // 0.0
/*314 */     reftable_offset_and_clusters.reftable_clusters =                              // 0.0
/*316 */         cpu_to_be32(size_to_clusters(s, reftable_size * sizeof(uint64_t)));       // 0.0
/*318 */     ret = bdrv_pwrite_sync(bs->file,                                              // 0.0
/*320 */                            offsetof(QCowHeader, refcount_table_offset),           // 0.0
/*322 */                            &reftable_offset_and_clusters,                         // 0.0
/*324 */                            sizeof(reftable_offset_and_clusters));                 // 0.0
/*326 */     if (ret < 0) {                                                                // 0.0
/*328 */         fprintf(stderr, "ERROR setting reftable: %s\n", strerror(-ret));          // 0.0
/*330 */         goto fail;                                                                // 0.0
/*332 */     }                                                                             // 0.0
/*336 */     for (refblock_index = 0; refblock_index < reftable_size; refblock_index++) {  // 0.0
/*338 */         be64_to_cpus(&on_disk_reftable[refblock_index]);                          // 0.0
/*340 */     }                                                                             // 0.0
/*342 */     s->refcount_table = on_disk_reftable;                                         // 0.0
/*344 */     s->refcount_table_offset = reftable_offset;                                   // 0.0
/*346 */     s->refcount_table_size = reftable_size;                                       // 0.0
/*348 */     update_max_refcount_table_index(s);                                           // 0.0
/*352 */     return 0;                                                                     // 0.0
/*356 */ fail:                                                                             // 0.0
/*358 */     g_free(on_disk_reftable);                                                     // 0.0
/*360 */     return ret;                                                                   // 0.0
/*362 */ }                                                                                 // 0.0
