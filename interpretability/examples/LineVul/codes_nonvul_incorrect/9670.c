// commit message qemu@62be4e3a50 (target=0, prob=0.5478992, correct=False): exec: qemu_ram_alloc_resizeable, qemu_ram_resize
/*0  */ static ram_addr_t find_ram_offset(ram_addr_t size)                              // (9) 0.04077
/*2  */ {                                                                               // (25) 0.002146
/*4  */     RAMBlock *block, *next_block;                                               // (16) 0.0279
/*6  */     ram_addr_t offset = RAM_ADDR_MAX, mingap = RAM_ADDR_MAX;                    // (2) 0.05794
/*10 */     assert(size != 0); /* it would hand out same offset multiple times */       // (10) 0.04077
/*14 */     if (QTAILQ_EMPTY(&ram_list.blocks))                                         // (11) 0.04077
/*16 */         return 0;                                                               // (18) 0.02146
/*20 */     QTAILQ_FOREACH(block, &ram_list.blocks, next) {                             // (4) 0.04936
/*22 */         ram_addr_t end, next = RAM_ADDR_MAX;                                    // (5) 0.04936
/*26 */         end = block->offset + block->length;                                    // (13) 0.03648
/*30 */         QTAILQ_FOREACH(next_block, &ram_list.blocks, next) {                    // (1) 0.06223
/*32 */             if (next_block->offset >= end) {                                    // (8) 0.04721
/*34 */                 next = MIN(next, next_block->offset);                           // (3) 0.05794
/*36 */             }                                                                   // (17) 0.02575
/*38 */         }                                                                       // (20) 0.01717
/*40 */         if (next - end >= size && next - end < mingap) {                        // (6) 0.04936
/*42 */             offset = end;                                                       // (14) 0.03219
/*44 */             mingap = next - end;                                                // (12) 0.03863
/*46 */         }                                                                       // (21) 0.01717
/*48 */     }                                                                           // (23) 0.008584
/*52 */     if (offset == RAM_ADDR_MAX) {                                               // (15) 0.03219
/*54 */         fprintf(stderr, "Failed to find gap of requested size: %" PRIu64 "\n",  // (0) 0.07082
/*56 */                 (uint64_t)size);                                                // (7) 0.04936
/*58 */         abort();                                                                // (19) 0.01931
/*60 */     }                                                                           // (24) 0.008584
/*64 */     return offset;                                                              // (22) 0.01288
/*66 */ }                                                                               // (26) 0.002146
