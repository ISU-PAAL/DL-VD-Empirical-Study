// commit message qemu@b60fae32ff (target=1, prob=0.017387751, correct=False): s390x/kvm: 2 byte software breakpoint support
/*0  */ int kvm_arch_insert_sw_breakpoint(CPUState *cs, struct kvm_sw_breakpoint *bp)  // (4) 0.1374
/*2  */ {                                                                              // (8) 0.004739
/*6  */     if (cpu_memory_rw_debug(cs, bp->pc, (uint8_t *)&bp->saved_insn,            // (2) 0.1659
/*8  */                             sizeof(diag_501), 0) ||                            // (0) 0.1754
/*10 */         cpu_memory_rw_debug(cs, bp->pc, (uint8_t *)diag_501,                   // (3) 0.1564
/*12 */                             sizeof(diag_501), 1)) {                            // (1) 0.1754
/*14 */         return -EINVAL;                                                        // (5) 0.06161
/*16 */     }                                                                          // (7) 0.01896
/*18 */     return 0;                                                                  // (6) 0.02844
/*20 */ }                                                                              // (9) 0.004739
