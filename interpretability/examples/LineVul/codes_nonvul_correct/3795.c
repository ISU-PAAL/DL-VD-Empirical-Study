// commit message qemu@ec05ec26f9 (target=0, prob=0.060342968, correct=True): memory: use mr->ram_addr in "is this RAM?" assertions
/*0  */ int memory_region_get_fd(MemoryRegion *mr)                    // (2) 0.1359
/*2  */ {                                                             // (6) 0.009709
/*4  */     if (mr->alias) {                                          // (3) 0.09709
/*6  */         return memory_region_get_fd(mr->alias);               // (1) 0.1942
/*8  */     }                                                         // (5) 0.03883
/*12 */     assert(mr->terminates);                                   // (4) 0.09709
/*16 */     return qemu_get_ram_fd(mr->ram_addr & TARGET_PAGE_MASK);  // (0) 0.2816
/*18 */ }                                                             // (7) 0.009709
