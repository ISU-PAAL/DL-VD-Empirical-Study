// commit message qemu@ec05ec26f9 (target=0, prob=0.09130888, correct=True): memory: use mr->ram_addr in "is this RAM?" assertions
/*0  */ void *memory_region_get_ram_ptr(MemoryRegion *mr)                        // (2) 0.1466
/*2  */ {                                                                        // (6) 0.008621
/*4  */     if (mr->alias) {                                                     // (3) 0.08621
/*6  */         return memory_region_get_ram_ptr(mr->alias) + mr->alias_offset;  // (0) 0.2586
/*8  */     }                                                                    // (5) 0.03448
/*12 */     assert(mr->terminates);                                              // (4) 0.08621
/*16 */     return qemu_get_ram_ptr(mr->ram_addr & TARGET_PAGE_MASK);            // (1) 0.25
/*18 */ }                                                                        // (7) 0.008621
