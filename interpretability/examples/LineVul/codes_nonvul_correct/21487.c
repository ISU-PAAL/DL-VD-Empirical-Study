// commit message qemu@2bcf018340 (target=0, prob=0.014167743, correct=True): s390x/tcg: low-address protection support
/*0  */ int mmu_translate_real(CPUS390XState *env, target_ulong raddr, int rw,      // (1) 0.1905
/*2  */                        target_ulong *addr, int *flags)                      // (0) 0.2245
/*4  */ {                                                                           // (8) 0.006803
/*6  */     /* TODO: low address protection once we flush the tlb on cr changes */  // (2) 0.1361
/*8  */     *flags = PAGE_READ | PAGE_WRITE;                                        // (4) 0.102
/*10 */     *addr = mmu_real2abs(env, raddr);                                       // (3) 0.1224
/*14 */     /* TODO: storage key handling */                                        // (5) 0.07483
/*16 */     return 0;                                                               // (6) 0.04082
/*18 */ }                                                                           // (7) 0.006803
