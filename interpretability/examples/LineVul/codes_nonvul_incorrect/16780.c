// commit message qemu@2f859f80c2 (target=0, prob=0.5875551, correct=False): dump: eliminate DumpState.page_size ("guest's page size")
/*0  */ static bool get_next_page(GuestPhysBlock **blockptr, uint64_t *pfnptr,  // (3) 0.04687
/*2  */                           uint8_t **bufptr, DumpState *s)               // (0) 0.07617
/*4  */ {                                                                       // (29) 0.001953
/*6  */     GuestPhysBlock *block = *blockptr;                                  // (16) 0.02539
/*8  */     hwaddr addr;                                                        // (24) 0.01562
/*10 */     uint8_t *buf;                                                       // (22) 0.01953
/*14 */     /* block == NULL means the start of the iteration */                // (14) 0.02734
/*16 */     if (!block) {                                                       // (23) 0.01562
/*18 */         block = QTAILQ_FIRST(&s->guest_phys_blocks.head);               // (1) 0.05469
/*20 */         *blockptr = block;                                              // (18) 0.02539
/*22 */         assert(block->target_start % s->page_size == 0);                // (5) 0.04492
/*24 */         assert(block->target_end % s->page_size == 0);                  // (7) 0.04492
/*26 */         *pfnptr = paddr_to_pfn(block->target_start);                    // (2) 0.05078
/*28 */         if (bufptr) {                                                   // (17) 0.02539
/*30 */             *bufptr = block->host_addr;                                 // (9) 0.04102
/*32 */         }                                                               // (25) 0.01562
/*34 */         return true;                                                    // (21) 0.01953
/*36 */     }                                                                   // (28) 0.007812
/*40 */     *pfnptr = *pfnptr + 1;                                              // (12) 0.0293
/*42 */     addr = pfn_to_paddr(*pfnptr);                                       // (10) 0.0332
/*46 */     if ((addr >= block->target_start) &&                                // (13) 0.02734
/*48 */         (addr + s->page_size <= block->target_end)) {                   // (6) 0.04492
/*50 */         buf = block->host_addr + (addr - block->target_start);          // (4) 0.04687
/*52 */     } else {                                                            // (27) 0.01172
/*54 */         /* the next page is in the next block */                        // (11) 0.0332
/*56 */         block = QTAILQ_NEXT(block, next);                               // (8) 0.04102
/*58 */         *blockptr = block;                                              // (19) 0.02539
/*60 */         if (!block) {                                                   // (20) 0.02344
/*62 */             return false;                                               // (15) 0.02734
/*64 */         }                                                               // (26) 0.01562
/*66 */         assert(block->target_start % s->page_size == 0);                // 0.0
/*68 */         assert(block->target_end % s->page_size == 0);                  // 0.0
/*70 */         *pfnptr = paddr_to_pfn(block->target_start);                    // 0.0
/*72 */         buf = block->host_addr;                                         // 0.0
/*74 */     }                                                                   // 0.0
/*78 */     if (bufptr) {                                                       // 0.0
/*80 */         *bufptr = buf;                                                  // 0.0
/*82 */     }                                                                   // 0.0
/*86 */     return true;                                                        // 0.0
/*88 */ }                                                                       // 0.0
