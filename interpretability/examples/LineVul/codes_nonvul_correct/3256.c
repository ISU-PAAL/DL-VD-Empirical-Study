// commit message qemu@ef29a70d18 (target=0, prob=0.10041106, correct=True): CRIS MMU Updates * Add support for exec faults and for the k protection bit. * Abort if search_pc causes recursive mmu faults.
/*0  */ void helper_tlb_update(uint32_t T0)                       // (4) 0.07813
/*2  */ {                                                         // (11) 0.005208
/*4  */ #if !defined(CONFIG_USER_ONLY)                            // (6) 0.06771
/*6  */ 	uint32_t vaddr;                                          // (8) 0.04167
/*8  */ 	uint32_t srs = env->pregs[PR_SRS];                       // (3) 0.09896
/*12 */ 	if (srs != 1 && srs != 2)                                // (7) 0.06771
/*14 */ 		return;                                                 // (9) 0.02083
/*18 */ 	vaddr = cris_mmu_tlb_latest_update(env, T0);             // (2) 0.1094
/*20 */ 	D(printf("flush old_vaddr=%x vaddr=%x T0=%x\n", vaddr,   // (1) 0.1563
/*22 */ 		 env->sregs[SFR_R_MM_CAUSE] & TARGET_PAGE_MASK, T0));   // (0) 0.1615
/*24 */ 	tlb_flush_page(env, vaddr);                              // (5) 0.06771
/*26 */ #endif                                                    // (10) 0.01042
/*28 */ }                                                         // (12) 0.005208
