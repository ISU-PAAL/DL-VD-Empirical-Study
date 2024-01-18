// commit message qemu@43771539d4 (target=0, prob=0.19813713, correct=True): exec: protect mru_block with RCU
/*0  */ static RAMBlock *qemu_get_ram_block(ram_addr_t addr)                  // (3) 0.083
/*2  */ {                                                                     // (17) 0.003953
/*4  */     RAMBlock *block;                                                  // (10) 0.03162
/*8  */     /* The list is protected by the iothread lock here.  */           // (5) 0.07115
/*10 */     block = ram_list.mru_block;                                       // (6) 0.05534
/*12 */     if (block && addr - block->offset < block->max_length) {          // (4) 0.07905
/*14 */         goto found;                                                   // (9) 0.03953
/*16 */     }                                                                 // (14) 0.01581
/*18 */     QTAILQ_FOREACH(block, &ram_list.blocks, next) {                   // (1) 0.09091
/*20 */         if (addr - block->offset < block->max_length) {               // (2) 0.08696
/*22 */             goto found;                                               // (7) 0.05534
/*24 */         }                                                             // (11) 0.03162
/*26 */     }                                                                 // (15) 0.01581
/*30 */     fprintf(stderr, "Bad ram offset %" PRIx64 "\n", (uint64_t)addr);  // (0) 0.1225
/*32 */     abort();                                                          // (13) 0.01976
/*36 */ found:                                                                // (16) 0.007905
/*38 */     ram_list.mru_block = block;                                       // (8) 0.05534
/*40 */     return block;                                                     // (12) 0.02372
/*42 */ }                                                                     // (18) 0.003953
