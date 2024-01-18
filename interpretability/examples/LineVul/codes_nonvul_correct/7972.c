// commit message qemu@3ad493fc5e (target=0, prob=0.030877374, correct=True): target-arm: disable PAGE_EXEC for XN pages
/*0  */ int cpu_arm_handle_mmu_fault (CPUState *env, target_ulong address,              // (7) 0.04688
/*2  */                               int access_type, int mmu_idx, int is_softmmu)     // (0) 0.09375
/*4  */ {                                                                               // (24) 0.001953
/*6  */     uint32_t phys_addr;                                                         // (17) 0.02148
/*8  */     target_ulong page_size;                                                     // (16) 0.02148
/*10 */     int prot;                                                                   // (21) 0.01172
/*12 */     int ret, is_user;                                                           // (18) 0.01953
/*16 */     is_user = mmu_idx == MMU_USER_IDX;                                          // (10) 0.04102
/*18 */     ret = get_phys_addr(env, address, access_type, is_user, &phys_addr, &prot,  // (2) 0.06055
/*20 */                         &page_size);                                            // (4) 0.05469
/*22 */     if (ret == 0) {                                                             // (19) 0.01953
/*24 */         /* Map a single [sub]page.  */                                          // (14) 0.03516
/*26 */         phys_addr &= ~(uint32_t)0x3ff;                                          // (8) 0.04687
/*28 */         address &= ~(uint32_t)0x3ff;                                            // (9) 0.04297
/*30 */         tlb_set_page (env, address, phys_addr, prot | PAGE_EXEC, mmu_idx,       // (1) 0.06836
/*32 */                       page_size);                                               // (6) 0.04883
/*34 */         return 0;                                                               // (20) 0.01953
/*36 */     }                                                                           // (23) 0.007813
/*40 */     if (access_type == 2) {                                                     // (15) 0.02344
/*42 */         env->cp15.c5_insn = ret;                                                // (12) 0.03906
/*44 */         env->cp15.c6_insn = address;                                            // (11) 0.03906
/*46 */         env->exception_index = EXCP_PREFETCH_ABORT;                             // (5) 0.04883
/*48 */     } else {                                                                    // (22) 0.01172
/*50 */         env->cp15.c5_data = ret;                                                // (13) 0.03711
/*52 */         if (access_type == 1 && arm_feature(env, ARM_FEATURE_V6))               // (3) 0.05664
/*54 */             env->cp15.c5_data |= (1 << 11);                                     // 0.0
/*56 */         env->cp15.c6_data = address;                                            // 0.0
/*58 */         env->exception_index = EXCP_DATA_ABORT;                                 // 0.0
/*60 */     }                                                                           // 0.0
/*62 */     return 1;                                                                   // 0.0
/*64 */ }                                                                               // 0.0
