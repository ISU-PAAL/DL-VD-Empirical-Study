// commit message qemu@52c91dac6b (target=1, prob=0.01279111, correct=False): memory: do not add a reference to the owner of aliased regions
/*0 */ static void memory_region_destructor_alias(MemoryRegion *mr)  // (0) 0.4
/*2 */ {                                                             // (2) 0.025
/*4 */     memory_region_unref(mr->alias);                           // (1) 0.35
/*6 */ }                                                             // (3) 0.025
