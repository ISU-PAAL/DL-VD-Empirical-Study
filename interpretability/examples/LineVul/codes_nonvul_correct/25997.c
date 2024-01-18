// commit message qemu@ec05ec26f9 (target=0, prob=0.0061579305, correct=True): memory: use mr->ram_addr in "is this RAM?" assertions
/*0  */ void memory_region_set_dirty(MemoryRegion *mr, hwaddr addr,                     // (3) 0.1242
/*2  */                              hwaddr size)                                       // (1) 0.2157
/*4  */ {                                                                               // (5) 0.006536
/*6  */     assert(mr->terminates);                                                     // (4) 0.06536
/*8  */     cpu_physical_memory_set_dirty_range(mr->ram_addr + addr, size,              // (2) 0.1634
/*10 */                                         memory_region_get_dirty_log_mask(mr));  // (0) 0.3464
/*12 */ }                                                                               // (6) 0.006536
