// commit message qemu@97f3ad3551 (target=1, prob=0.9385979, correct=True): migration: Use g_new() & friends where that makes obvious sense
/*0   */ static int rdma_add_block(RDMAContext *rdma, const char *block_name,            // (9) 0.05078
/*2   */                          void *host_addr,                                       // (5) 0.05859
/*4   */                          ram_addr_t block_offset, uint64_t length)              // (3) 0.07617
/*6   */ {                                                                               // (18) 0.001953
/*8   */     RDMALocalBlocks *local = &rdma->local_ram_blocks;                           // (10) 0.04102
/*10  */     RDMALocalBlock *block;                                                      // (15) 0.02148
/*12  */     RDMALocalBlock *old = local->block;                                         // (12) 0.0293
/*16  */     local->block = g_malloc0(sizeof(RDMALocalBlock) * (local->nb_blocks + 1));  // (4) 0.0625
/*20  */     if (local->nb_blocks) {                                                     // (13) 0.02344
/*22  */         int x;                                                                  // (16) 0.01953
/*26  */         if (rdma->blockmap) {                                                   // (11) 0.03125
/*28  */             for (x = 0; x < local->nb_blocks; x++) {                            // (8) 0.05469
/*30  */                 g_hash_table_remove(rdma->blockmap,                             // (6) 0.05664
/*32  */                                     (void *)(uintptr_t)old[x].offset);          // (1) 0.09766
/*34  */                 g_hash_table_insert(rdma->blockmap,                             // (7) 0.05664
/*36  */                                     (void *)(uintptr_t)old[x].offset,           // (0) 0.09766
/*38  */                                     &local->block[x]);                          // (2) 0.08203
/*40  */             }                                                                   // (14) 0.02344
/*42  */         }                                                                       // (17) 0.01562
/*44  */         memcpy(local->block, old, sizeof(RDMALocalBlock) * local->nb_blocks);   // 0.0
/*46  */         g_free(old);                                                            // 0.0
/*48  */     }                                                                           // 0.0
/*52  */     block = &local->block[local->nb_blocks];                                    // 0.0
/*56  */     block->block_name = g_strdup(block_name);                                   // 0.0
/*58  */     block->local_host_addr = host_addr;                                         // 0.0
/*60  */     block->offset = block_offset;                                               // 0.0
/*62  */     block->length = length;                                                     // 0.0
/*64  */     block->index = local->nb_blocks;                                            // 0.0
/*66  */     block->src_index = ~0U; /* Filled in by the receipt of the block list */    // 0.0
/*68  */     block->nb_chunks = ram_chunk_index(host_addr, host_addr + length) + 1UL;    // 0.0
/*70  */     block->transit_bitmap = bitmap_new(block->nb_chunks);                       // 0.0
/*72  */     bitmap_clear(block->transit_bitmap, 0, block->nb_chunks);                   // 0.0
/*74  */     block->unregister_bitmap = bitmap_new(block->nb_chunks);                    // 0.0
/*76  */     bitmap_clear(block->unregister_bitmap, 0, block->nb_chunks);                // 0.0
/*78  */     block->remote_keys = g_malloc0(block->nb_chunks * sizeof(uint32_t));        // 0.0
/*82  */     block->is_ram_block = local->init ? false : true;                           // 0.0
/*86  */     if (rdma->blockmap) {                                                       // 0.0
/*88  */         g_hash_table_insert(rdma->blockmap, (void *) block_offset, block);      // 0.0
/*90  */     }                                                                           // 0.0
/*94  */     trace_rdma_add_block(block_name, local->nb_blocks,                          // 0.0
/*96  */                          (uintptr_t) block->local_host_addr,                    // 0.0
/*98  */                          block->offset, block->length,                          // 0.0
/*100 */                          (uintptr_t) (block->local_host_addr + block->length),  // 0.0
/*102 */                          BITS_TO_LONGS(block->nb_chunks) *                      // 0.0
/*104 */                              sizeof(unsigned long) * 8,                         // 0.0
/*106 */                          block->nb_chunks);                                     // 0.0
/*110 */     local->nb_blocks++;                                                         // 0.0
/*114 */     return 0;                                                                   // 0.0
/*116 */ }                                                                               // 0.0
