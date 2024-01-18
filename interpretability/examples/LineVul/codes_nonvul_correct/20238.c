// commit message qemu@d4c430a80f (target=0, prob=0.0121675115, correct=True): Large page TLB flush
/*0  */ int cpu_s390x_handle_mmu_fault (CPUState *env, target_ulong address, int rw,  // (3) 0.1266
/*2  */                                 int mmu_idx, int is_softmmu)                  // (0) 0.1899
/*4  */ {                                                                             // (10) 0.004219
/*6  */     target_ulong phys;                                                        // (7) 0.03797
/*8  */     int prot;                                                                 // (9) 0.02532
/*12 */     /* XXX: implement mmu */                                                  // (6) 0.04219
/*16 */     phys = address;                                                           // (8) 0.02954
/*18 */     prot = PAGE_READ | PAGE_WRITE;                                            // (5) 0.05907
/*22 */     return tlb_set_page(env, address & TARGET_PAGE_MASK,                      // (4) 0.1013
/*24 */                         phys & TARGET_PAGE_MASK, prot,                        // (1) 0.1519
/*26 */                         mmu_idx, is_softmmu);                                 // (2) 0.1477
/*28 */ }                                                                             // (11) 0.004219
