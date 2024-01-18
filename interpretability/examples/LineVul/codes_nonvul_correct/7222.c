// commit message qemu@d4c430a80f (target=0, prob=0.034176253, correct=True): Large page TLB flush
/*0   */ int cpu_sh4_handle_mmu_fault(CPUState * env, target_ulong address, int rw,   // (0) 0.05664
/*2   */ 			     int mmu_idx, int is_softmmu)                                         // (1) 0.04102
/*4   */ {                                                                            // (37) 0.001953
/*6   */     target_ulong physical;                                                   // (26) 0.01758
/*8   */     int prot, ret, access_type;                                              // (20) 0.02344
/*12  */     access_type = ACCESS_INT;                                                // (21) 0.02344
/*14  */     ret =                                                                    // (36) 0.009766
/*16  */ 	get_physical_address(env, &physical, &prot, address, rw,                    // (2) 0.03906
/*18  */ 			     access_type);                                                        // (24) 0.02148
/*22  */     if (ret != MMU_OK) {                                                     // (17) 0.02539
/*24  */ 	env->tea = address;                                                         // (27) 0.01562
/*26  */ 	switch (ret) {                                                              // (28) 0.01172
/*28  */ 	case MMU_ITLB_MISS:                                                         // (23) 0.02148
/*30  */ 	case MMU_DTLB_MISS_READ:                                                    // (16) 0.02734
/*32  */ 	    env->exception_index = 0x040;                                           // (9) 0.0293
/*34  */ 	    break;                                                                  // (29) 0.01172
/*36  */ 	case MMU_DTLB_MULTIPLE:                                                     // (15) 0.02734
/*38  */ 	case MMU_ITLB_MULTIPLE:                                                     // (18) 0.02539
/*40  */ 	    env->exception_index = 0x140;                                           // (10) 0.0293
/*42  */ 	    break;                                                                  // (30) 0.01172
/*44  */ 	case MMU_ITLB_VIOLATION:                                                    // (22) 0.02344
/*46  */ 	    env->exception_index = 0x0a0;                                           // (3) 0.0332
/*48  */ 	    break;                                                                  // (31) 0.01172
/*50  */ 	case MMU_DTLB_MISS_WRITE:                                                   // (11) 0.0293
/*52  */ 	    env->exception_index = 0x060;                                           // (12) 0.0293
/*54  */ 	    break;                                                                  // (32) 0.01172
/*56  */ 	case MMU_DTLB_INITIAL_WRITE:                                                // (7) 0.03125
/*58  */ 	    env->exception_index = 0x080;                                           // (13) 0.0293
/*60  */ 	    break;                                                                  // (33) 0.01172
/*62  */ 	case MMU_DTLB_VIOLATION_READ:                                               // (14) 0.0293
/*64  */ 	    env->exception_index = 0x0a0;                                           // (4) 0.0332
/*66  */ 	    break;                                                                  // (34) 0.01172
/*68  */ 	case MMU_DTLB_VIOLATION_WRITE:                                              // (8) 0.03125
/*70  */ 	    env->exception_index = 0x0c0;                                           // (5) 0.0332
/*72  */ 	    break;                                                                  // (35) 0.01172
/*74  */ 	case MMU_IADDR_ERROR:                                                       // (25) 0.02148
/*76  */ 	case MMU_DADDR_ERROR_READ:                                                  // (19) 0.02539
/*78  */ 	    env->exception_index = 0x0c0;                                           // (6) 0.0332
/*80  */ 	    break;                                                                  // 0.0
/*82  */ 	case MMU_DADDR_ERROR_WRITE:                                                 // 0.0
/*84  */ 	    env->exception_index = 0x100;                                           // 0.0
/*86  */ 	    break;                                                                  // 0.0
/*88  */ 	default:                                                                    // 0.0
/*90  */ 	    assert(0);                                                              // 0.0
/*92  */ 	}                                                                           // 0.0
/*94  */ 	return 1;                                                                   // 0.0
/*96  */     }                                                                        // 0.0
/*100 */     address &= TARGET_PAGE_MASK;                                             // 0.0
/*102 */     physical &= TARGET_PAGE_MASK;                                            // 0.0
/*106 */     return tlb_set_page(env, address, physical, prot, mmu_idx, is_softmmu);  // 0.0
/*108 */ }                                                                            // 0.0
