// commit message qemu@21a0b6ed1d (target=0, prob=0.014062491, correct=True): PPC: booke206: move avail check to tlbwe
/*0  */ target_phys_addr_t booke206_tlb_to_page_size(CPUState *env, ppcmas_tlb_t *tlb)  // (2) 0.135
/*2  */ {                                                                               // (12) 0.00365
/*4  */     uint32_t tlbncfg;                                                           // (8) 0.0438
/*6  */     int tlbn = booke206_tlbm_to_tlbn(env, tlb);                                 // (4) 0.09124
/*8  */     int tlbm_size;                                                              // (9) 0.0365
/*12 */     tlbncfg = env->spr[SPR_BOOKE_TLB0CFG + tlbn];                               // (3) 0.1058
/*16 */     if (tlbncfg & TLBnCFG_AVAIL) {                                              // (5) 0.07299
/*18 */         tlbm_size = (tlb->mas1 & MAS1_TSIZE_MASK) >> MAS1_TSIZE_SHIFT;          // (1) 0.1423
/*20 */     } else {                                                                    // (10) 0.0219
/*22 */         tlbm_size = (tlbncfg & TLBnCFG_MINSIZE) >> TLBnCFG_MINSIZE_SHIFT;       // (0) 0.146
/*24 */         tlbm_size <<= 1;                                                        // (6) 0.05839
/*26 */     }                                                                           // (11) 0.0146
/*30 */     return 1024ULL << tlbm_size;                                                // (7) 0.04745
/*32 */ }                                                                               // (13) 0.00365
