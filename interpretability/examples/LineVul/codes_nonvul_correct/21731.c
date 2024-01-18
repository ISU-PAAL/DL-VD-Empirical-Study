// commit message qemu@0a75601853 (target=0, prob=0.36503443, correct=True): memory: Move assignment to ram_block to memory_region_init_*
/*0  */ RAMBlock *qemu_ram_alloc_internal(ram_addr_t size, ram_addr_t max_size,  // (5) 0.05664
/*2  */                                   void (*resized)(const char*,           // (3) 0.08008
/*4  */                                                   uint64_t length,       // (0) 0.1074
/*6  */                                                   void *host),           // (1) 0.1035
/*8  */                                   void *host, bool resizeable,           // (4) 0.08008
/*10 */                                   MemoryRegion *mr, Error **errp)        // (2) 0.08398
/*12 */ {                                                                        // (22) 0.001953
/*14 */     RAMBlock *new_block;                                                 // (18) 0.01953
/*16 */     Error *local_err = NULL;                                             // (15) 0.02148
/*20 */     size = HOST_PAGE_ALIGN(size);                                        // (9) 0.03125
/*22 */     max_size = HOST_PAGE_ALIGN(max_size);                                // (7) 0.03906
/*24 */     new_block = g_malloc0(sizeof(*new_block));                           // (6) 0.03906
/*26 */     new_block->mr = mr;                                                  // (14) 0.02344
/*28 */     new_block->resized = resized;                                        // (11) 0.02539
/*30 */     new_block->used_length = size;                                       // (12) 0.02539
/*32 */     new_block->max_length = max_size;                                    // (10) 0.0293
/*34 */     assert(max_size >= size);                                            // (17) 0.02148
/*36 */     new_block->fd = -1;                                                  // (13) 0.02344
/*38 */     new_block->host = host;                                              // (16) 0.02148
/*40 */     if (host) {                                                          // (20) 0.01562
/*42 */         new_block->flags |= RAM_PREALLOC;                                // (8) 0.03906
/*44 */     }                                                                    // (21) 0.007812
/*46 */     if (resizeable) {                                                    // (19) 0.01953
/*48 */         new_block->flags |= RAM_RESIZEABLE;                              // 0.0
/*50 */     }                                                                    // 0.0
/*52 */     ram_block_add(new_block, &local_err);                                // 0.0
/*54 */     if (local_err) {                                                     // 0.0
/*56 */         g_free(new_block);                                               // 0.0
/*58 */         error_propagate(errp, local_err);                                // 0.0
/*60 */         return NULL;                                                     // 0.0
/*62 */     }                                                                    // 0.0
/*64 */     mr->ram_block = new_block;                                           // 0.0
/*66 */     return new_block;                                                    // 0.0
/*68 */ }                                                                        // 0.0
