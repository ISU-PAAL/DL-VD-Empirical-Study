// commit message qemu@a87f39543a (target=0, prob=0.4725948, correct=True): memory: fix limiting of translation at a page boundary
/*0  */ static inline bool memory_access_is_direct(MemoryRegion *mr, bool is_write)  // (0) 0.178
/*2  */ {                                                                            // (8) 0.008475
/*4  */     if (memory_region_is_ram(mr)) {                                          // (3) 0.1356
/*6  */         return !(is_write && mr->readonly);                                  // (1) 0.1695
/*8  */     }                                                                        // (6) 0.0339
/*10 */     if (memory_region_is_romd(mr)) {                                         // (2) 0.1441
/*12 */         return !is_write;                                                    // (4) 0.1102
/*14 */     }                                                                        // (7) 0.0339
/*18 */     return false;                                                            // (5) 0.05085
/*20 */ }                                                                            // (9) 0.008475
