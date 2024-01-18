// commit message qemu@7453c96b78 (target=1, prob=0.56092256, correct=True): qcow2: Helper function for refcount modification
/*0   */ static int alloc_refcount_block(BlockDriverState *bs,                              // (14) 0.0293
/*2   */     int64_t cluster_index, uint16_t **refcount_block)                              // (9) 0.04102
/*4   */ {                                                                                  // (18) 0.001953
/*6   */     BDRVQcowState *s = bs->opaque;                                                 // (10) 0.03516
/*8   */     unsigned int refcount_table_index;                                             // (16) 0.02344
/*10  */     int ret;                                                                       // (17) 0.01172
/*14  */     BLKDBG_EVENT(bs->file, BLKDBG_REFBLOCK_ALLOC);                                 // (6) 0.05273
/*18  */     /* Find the refcount block for the given cluster */                            // (15) 0.02734
/*20  */     refcount_table_index = cluster_index >> s->refcount_block_bits;                // (7) 0.04492
/*24  */     if (refcount_table_index < s->refcount_table_size) {                           // (8) 0.04297
/*28  */         uint64_t refcount_block_offset =                                           // (11) 0.03516
/*30  */             s->refcount_table[refcount_table_index] & REFT_OFFSET_MASK;            // (4) 0.06836
/*34  */         /* If it's already there, we're done */                                    // (12) 0.03516
/*36  */         if (refcount_block_offset) {                                               // (13) 0.0332
/*38  */             if (offset_into_cluster(s, refcount_block_offset)) {                   // (5) 0.05859
/*40  */                 qcow2_signal_corruption(bs, true, -1, -1, "Refblock offset %#"     // (3) 0.08008
/*42  */                                         PRIx64 " unaligned (reftable index: "      // (0) 0.1035
/*44  */                                         "%#x)", refcount_block_offset,             // (1) 0.09766
/*46  */                                         refcount_table_index);                     // (2) 0.08984
/*48  */                 return -EIO;                                                       // 0.0
/*50  */             }                                                                      // 0.0
/*54  */              return load_refcount_block(bs, refcount_block_offset,                 // 0.0
/*56  */                  (void**) refcount_block);                                         // 0.0
/*58  */         }                                                                          // 0.0
/*60  */     }                                                                              // 0.0
/*64  */     /*                                                                             // 0.0
/*66  */      * If we came here, we need to allocate something. Something is at least       // 0.0
/*68  */      * a cluster for the new refcount block. It may also include a new refcount    // 0.0
/*70  */      * table if the old refcount table is too small.                               // 0.0
/*72  */      *                                                                             // 0.0
/*74  */      * Note that allocating clusters here needs some special care:                 // 0.0
/*76  */      *                                                                             // 0.0
/*78  */      * - We can't use the normal qcow2_alloc_clusters(), it would try to           // 0.0
/*80  */      *   increase the refcount and very likely we would end up with an endless     // 0.0
/*82  */      *   recursion. Instead we must place the refcount blocks in a way that        // 0.0
/*84  */      *   they can describe them themselves.                                        // 0.0
/*86  */      *                                                                             // 0.0
/*88  */      * - We need to consider that at this point we are inside update_refcounts     // 0.0
/*90  */      *   and potentially doing an initial refcount increase. This means that       // 0.0
/*92  */      *   some clusters have already been allocated by the caller, but their        // 0.0
/*94  */      *   refcount isn't accurate yet. If we allocate clusters for metadata, we     // 0.0
/*96  */      *   need to return -EAGAIN to signal the caller that it needs to restart      // 0.0
/*98  */      *   the search for free clusters.                                             // 0.0
/*100 */      *                                                                             // 0.0
/*102 */      * - alloc_clusters_noref and qcow2_free_clusters may load a different         // 0.0
/*104 */      *   refcount block into the cache                                             // 0.0
/*106 */      */                                                                            // 0.0
/*110 */     *refcount_block = NULL;                                                        // 0.0
/*114 */     /* We write to the refcount table, so we might depend on L2 tables */          // 0.0
/*116 */     ret = qcow2_cache_flush(bs, s->l2_table_cache);                                // 0.0
/*118 */     if (ret < 0) {                                                                 // 0.0
/*120 */         return ret;                                                                // 0.0
/*122 */     }                                                                              // 0.0
/*126 */     /* Allocate the refcount block itself and mark it as used */                   // 0.0
/*128 */     int64_t new_block = alloc_clusters_noref(bs, s->cluster_size);                 // 0.0
/*130 */     if (new_block < 0) {                                                           // 0.0
/*132 */         return new_block;                                                          // 0.0
/*134 */     }                                                                              // 0.0
/*138 */ #ifdef DEBUG_ALLOC2                                                                // 0.0
/*140 */     fprintf(stderr, "qcow2: Allocate refcount block %d for %" PRIx64               // 0.0
/*142 */         " at %" PRIx64 "\n",                                                       // 0.0
/*144 */         refcount_table_index, cluster_index << s->cluster_bits, new_block);        // 0.0
/*146 */ #endif                                                                             // 0.0
/*150 */     if (in_same_refcount_block(s, new_block, cluster_index << s->cluster_bits)) {  // 0.0
/*152 */         /* Zero the new refcount block before updating it */                       // 0.0
/*154 */         ret = qcow2_cache_get_empty(bs, s->refcount_block_cache, new_block,        // 0.0
/*156 */             (void**) refcount_block);                                              // 0.0
/*158 */         if (ret < 0) {                                                             // 0.0
/*160 */             goto fail_block;                                                       // 0.0
/*162 */         }                                                                          // 0.0
/*166 */         memset(*refcount_block, 0, s->cluster_size);                               // 0.0
/*170 */         /* The block describes itself, need to update the cache */                 // 0.0
/*172 */         int block_index = (new_block >> s->cluster_bits) &                         // 0.0
/*174 */             (s->refcount_block_size - 1);                                          // 0.0
/*176 */         (*refcount_block)[block_index] = cpu_to_be16(1);                           // 0.0
/*178 */     } else {                                                                       // 0.0
/*180 */         /* Described somewhere else. This can recurse at most twice before we      // 0.0
/*182 */          * arrive at a block that describes itself. */                             // 0.0
/*184 */         ret = update_refcount(bs, new_block, s->cluster_size, 1, false,            // 0.0
/*186 */                               QCOW2_DISCARD_NEVER);                                // 0.0
/*188 */         if (ret < 0) {                                                             // 0.0
/*190 */             goto fail_block;                                                       // 0.0
/*192 */         }                                                                          // 0.0
/*196 */         ret = qcow2_cache_flush(bs, s->refcount_block_cache);                      // 0.0
/*198 */         if (ret < 0) {                                                             // 0.0
/*200 */             goto fail_block;                                                       // 0.0
/*202 */         }                                                                          // 0.0
/*206 */         /* Initialize the new refcount block only after updating its refcount,     // 0.0
/*208 */          * update_refcount uses the refcount cache itself */                       // 0.0
/*210 */         ret = qcow2_cache_get_empty(bs, s->refcount_block_cache, new_block,        // 0.0
/*212 */             (void**) refcount_block);                                              // 0.0
/*214 */         if (ret < 0) {                                                             // 0.0
/*216 */             goto fail_block;                                                       // 0.0
/*218 */         }                                                                          // 0.0
/*222 */         memset(*refcount_block, 0, s->cluster_size);                               // 0.0
/*224 */     }                                                                              // 0.0
/*228 */     /* Now the new refcount block needs to be written to disk */                   // 0.0
/*230 */     BLKDBG_EVENT(bs->file, BLKDBG_REFBLOCK_ALLOC_WRITE);                           // 0.0
/*232 */     qcow2_cache_entry_mark_dirty(s->refcount_block_cache, *refcount_block);        // 0.0
/*234 */     ret = qcow2_cache_flush(bs, s->refcount_block_cache);                          // 0.0
/*236 */     if (ret < 0) {                                                                 // 0.0
/*238 */         goto fail_block;                                                           // 0.0
/*240 */     }                                                                              // 0.0
/*244 */     /* If the refcount table is big enough, just hook the block up there */        // 0.0
/*246 */     if (refcount_table_index < s->refcount_table_size) {                           // 0.0
/*248 */         uint64_t data64 = cpu_to_be64(new_block);                                  // 0.0
/*250 */         BLKDBG_EVENT(bs->file, BLKDBG_REFBLOCK_ALLOC_HOOKUP);                      // 0.0
/*252 */         ret = bdrv_pwrite_sync(bs->file,                                           // 0.0
/*254 */             s->refcount_table_offset + refcount_table_index * sizeof(uint64_t),    // 0.0
/*256 */             &data64, sizeof(data64));                                              // 0.0
/*258 */         if (ret < 0) {                                                             // 0.0
/*260 */             goto fail_block;                                                       // 0.0
/*262 */         }                                                                          // 0.0
/*266 */         s->refcount_table[refcount_table_index] = new_block;                       // 0.0
/*270 */         /* The new refcount block may be where the caller intended to put its      // 0.0
/*272 */          * data, so let it restart the search. */                                  // 0.0
/*274 */         return -EAGAIN;                                                            // 0.0
/*276 */     }                                                                              // 0.0
/*280 */     ret = qcow2_cache_put(bs, s->refcount_block_cache, (void**) refcount_block);   // 0.0
/*282 */     if (ret < 0) {                                                                 // 0.0
/*284 */         goto fail_block;                                                           // 0.0
/*286 */     }                                                                              // 0.0
/*290 */     /*                                                                             // 0.0
/*292 */      * If we come here, we need to grow the refcount table. Again, a new           // 0.0
/*294 */      * refcount table needs some space and we can't simply allocate to avoid       // 0.0
/*296 */      * endless recursion.                                                          // 0.0
/*298 */      *                                                                             // 0.0
/*300 */      * Therefore let's grab new refcount blocks at the end of the image, which     // 0.0
/*302 */      * will describe themselves and the new refcount table. This way we can        // 0.0
/*304 */      * reference them only in the new table and do the switch to the new           // 0.0
/*306 */      * refcount table at once without producing an inconsistent state in           // 0.0
/*308 */      * between.                                                                    // 0.0
/*310 */      */                                                                            // 0.0
/*312 */     BLKDBG_EVENT(bs->file, BLKDBG_REFTABLE_GROW);                                  // 0.0
/*316 */     /* Calculate the number of refcount blocks needed so far */                    // 0.0
/*318 */     uint64_t blocks_used = DIV_ROUND_UP(cluster_index, s->refcount_block_size);    // 0.0
/*322 */     if (blocks_used > QCOW_MAX_REFTABLE_SIZE / sizeof(uint64_t)) {                 // 0.0
/*324 */         return -EFBIG;                                                             // 0.0
/*326 */     }                                                                              // 0.0
/*330 */     /* And now we need at least one block more for the new metadata */             // 0.0
/*332 */     uint64_t table_size = next_refcount_table_size(s, blocks_used + 1);            // 0.0
/*334 */     uint64_t last_table_size;                                                      // 0.0
/*336 */     uint64_t blocks_clusters;                                                      // 0.0
/*338 */     do {                                                                           // 0.0
/*340 */         uint64_t table_clusters =                                                  // 0.0
/*342 */             size_to_clusters(s, table_size * sizeof(uint64_t));                    // 0.0
/*344 */         blocks_clusters = 1 +                                                      // 0.0
/*346 */             ((table_clusters + s->refcount_block_size - 1)                         // 0.0
/*348 */             / s->refcount_block_size);                                             // 0.0
/*350 */         uint64_t meta_clusters = table_clusters + blocks_clusters;                 // 0.0
/*354 */         last_table_size = table_size;                                              // 0.0
/*356 */         table_size = next_refcount_table_size(s, blocks_used +                     // 0.0
/*358 */             ((meta_clusters + s->refcount_block_size - 1)                          // 0.0
/*360 */             / s->refcount_block_size));                                            // 0.0
/*364 */     } while (last_table_size != table_size);                                       // 0.0
/*368 */ #ifdef DEBUG_ALLOC2                                                                // 0.0
/*370 */     fprintf(stderr, "qcow2: Grow refcount table %" PRId32 " => %" PRId64 "\n",     // 0.0
/*372 */         s->refcount_table_size, table_size);                                       // 0.0
/*374 */ #endif                                                                             // 0.0
/*378 */     /* Create the new refcount table and blocks */                                 // 0.0
/*380 */     uint64_t meta_offset = (blocks_used * s->refcount_block_size) *                // 0.0
/*382 */         s->cluster_size;                                                           // 0.0
/*384 */     uint64_t table_offset = meta_offset + blocks_clusters * s->cluster_size;       // 0.0
/*386 */     uint64_t *new_table = g_try_new0(uint64_t, table_size);                        // 0.0
/*388 */     uint16_t *new_blocks = g_try_malloc0(blocks_clusters * s->cluster_size);       // 0.0
/*392 */     assert(table_size > 0 && blocks_clusters > 0);                                 // 0.0
/*394 */     if (new_table == NULL || new_blocks == NULL) {                                 // 0.0
/*396 */         ret = -ENOMEM;                                                             // 0.0
/*398 */         goto fail_table;                                                           // 0.0
/*400 */     }                                                                              // 0.0
/*404 */     /* Fill the new refcount table */                                              // 0.0
/*406 */     memcpy(new_table, s->refcount_table,                                           // 0.0
/*408 */         s->refcount_table_size * sizeof(uint64_t));                                // 0.0
/*410 */     new_table[refcount_table_index] = new_block;                                   // 0.0
/*414 */     int i;                                                                         // 0.0
/*416 */     for (i = 0; i < blocks_clusters; i++) {                                        // 0.0
/*418 */         new_table[blocks_used + i] = meta_offset + (i * s->cluster_size);          // 0.0
/*420 */     }                                                                              // 0.0
/*424 */     /* Fill the refcount blocks */                                                 // 0.0
/*426 */     uint64_t table_clusters = size_to_clusters(s, table_size * sizeof(uint64_t));  // 0.0
/*428 */     int block = 0;                                                                 // 0.0
/*430 */     for (i = 0; i < table_clusters + blocks_clusters; i++) {                       // 0.0
/*432 */         new_blocks[block++] = cpu_to_be16(1);                                      // 0.0
/*434 */     }                                                                              // 0.0
/*438 */     /* Write refcount blocks to disk */                                            // 0.0
/*440 */     BLKDBG_EVENT(bs->file, BLKDBG_REFBLOCK_ALLOC_WRITE_BLOCKS);                    // 0.0
/*442 */     ret = bdrv_pwrite_sync(bs->file, meta_offset, new_blocks,                      // 0.0
/*444 */         blocks_clusters * s->cluster_size);                                        // 0.0
/*446 */     g_free(new_blocks);                                                            // 0.0
/*448 */     new_blocks = NULL;                                                             // 0.0
/*450 */     if (ret < 0) {                                                                 // 0.0
/*452 */         goto fail_table;                                                           // 0.0
/*454 */     }                                                                              // 0.0
/*458 */     /* Write refcount table to disk */                                             // 0.0
/*460 */     for(i = 0; i < table_size; i++) {                                              // 0.0
/*462 */         cpu_to_be64s(&new_table[i]);                                               // 0.0
/*464 */     }                                                                              // 0.0
/*468 */     BLKDBG_EVENT(bs->file, BLKDBG_REFBLOCK_ALLOC_WRITE_TABLE);                     // 0.0
/*470 */     ret = bdrv_pwrite_sync(bs->file, table_offset, new_table,                      // 0.0
/*472 */         table_size * sizeof(uint64_t));                                            // 0.0
/*474 */     if (ret < 0) {                                                                 // 0.0
/*476 */         goto fail_table;                                                           // 0.0
/*478 */     }                                                                              // 0.0
/*482 */     for(i = 0; i < table_size; i++) {                                              // 0.0
/*484 */         be64_to_cpus(&new_table[i]);                                               // 0.0
/*486 */     }                                                                              // 0.0
/*490 */     /* Hook up the new refcount table in the qcow2 header */                       // 0.0
/*492 */     uint8_t data[12];                                                              // 0.0
/*494 */     cpu_to_be64w((uint64_t*)data, table_offset);                                   // 0.0
/*496 */     cpu_to_be32w((uint32_t*)(data + 8), table_clusters);                           // 0.0
/*498 */     BLKDBG_EVENT(bs->file, BLKDBG_REFBLOCK_ALLOC_SWITCH_TABLE);                    // 0.0
/*500 */     ret = bdrv_pwrite_sync(bs->file, offsetof(QCowHeader, refcount_table_offset),  // 0.0
/*502 */         data, sizeof(data));                                                       // 0.0
/*504 */     if (ret < 0) {                                                                 // 0.0
/*506 */         goto fail_table;                                                           // 0.0
/*508 */     }                                                                              // 0.0
/*512 */     /* And switch it in memory */                                                  // 0.0
/*514 */     uint64_t old_table_offset = s->refcount_table_offset;                          // 0.0
/*516 */     uint64_t old_table_size = s->refcount_table_size;                              // 0.0
/*520 */     g_free(s->refcount_table);                                                     // 0.0
/*522 */     s->refcount_table = new_table;                                                 // 0.0
/*524 */     s->refcount_table_size = table_size;                                           // 0.0
/*526 */     s->refcount_table_offset = table_offset;                                       // 0.0
/*530 */     /* Free old table. */                                                          // 0.0
/*532 */     qcow2_free_clusters(bs, old_table_offset, old_table_size * sizeof(uint64_t),   // 0.0
/*534 */                         QCOW2_DISCARD_OTHER);                                      // 0.0
/*538 */     ret = load_refcount_block(bs, new_block, (void**) refcount_block);             // 0.0
/*540 */     if (ret < 0) {                                                                 // 0.0
/*542 */         return ret;                                                                // 0.0
/*544 */     }                                                                              // 0.0
/*548 */     /* If we were trying to do the initial refcount update for some cluster        // 0.0
/*550 */      * allocation, we might have used the same clusters to store newly             // 0.0
/*552 */      * allocated metadata. Make the caller search some new space. */               // 0.0
/*554 */     return -EAGAIN;                                                                // 0.0
/*558 */ fail_table:                                                                        // 0.0
/*560 */     g_free(new_blocks);                                                            // 0.0
/*562 */     g_free(new_table);                                                             // 0.0
/*564 */ fail_block:                                                                        // 0.0
/*566 */     if (*refcount_block != NULL) {                                                 // 0.0
/*568 */         qcow2_cache_put(bs, s->refcount_block_cache, (void**) refcount_block);     // 0.0
/*570 */     }                                                                              // 0.0
/*572 */     return ret;                                                                    // 0.0
/*574 */ }                                                                                  // 0.0
