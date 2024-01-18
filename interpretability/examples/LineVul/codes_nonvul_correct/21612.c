// commit message qemu@ec05ec26f9 (target=0, prob=0.005105677, correct=True): memory: use mr->ram_addr in "is this RAM?" assertions
/*0  */ bool memory_region_test_and_clear_dirty(MemoryRegion *mr, hwaddr addr,    // (3) 0.1322
/*2  */                                         hwaddr size, unsigned client)     // (1) 0.2701
/*4  */ {                                                                         // (5) 0.005747
/*6  */     assert(mr->terminates);                                               // (4) 0.05747
/*8  */     return cpu_physical_memory_test_and_clear_dirty(mr->ram_addr + addr,  // (2) 0.1494
/*10 */                                                     size, client);        // (0) 0.3161
/*12 */ }                                                                         // (6) 0.005747
