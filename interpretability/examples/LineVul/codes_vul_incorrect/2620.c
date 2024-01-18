// commit message qemu@b0706b7167 (target=1, prob=0.13729948, correct=False): cputlb: atomically update tlb fields used by tlb_reset_dirty
/*0  */ void tlb_reset_dirty(CPUState *cpu, ram_addr_t start1, ram_addr_t length)  // (5) 0.07692
/*2  */ {                                                                          // (16) 0.002747
/*4  */     CPUArchState *env;                                                     // (12) 0.02473
/*8  */     int mmu_idx;                                                           // (11) 0.02747
/*12 */     assert_cpu_is_self(cpu);                                               // (8) 0.03571
/*16 */     env = cpu->env_ptr;                                                    // (9) 0.03022
/*18 */     for (mmu_idx = 0; mmu_idx < NB_MMU_MODES; mmu_idx++) {                 // (4) 0.09341
/*20 */         unsigned int i;                                                    // (10) 0.03022
/*24 */         for (i = 0; i < CPU_TLB_SIZE; i++) {                               // (7) 0.06868
/*26 */             tlb_reset_dirty_range(&env->tlb_table[mmu_idx][i],             // (3) 0.09615
/*28 */                                   start1, length);                         // (0) 0.1044
/*30 */         }                                                                  // (13) 0.02198
/*34 */         for (i = 0; i < CPU_VTLB_SIZE; i++) {                              // (6) 0.07143
/*36 */             tlb_reset_dirty_range(&env->tlb_v_table[mmu_idx][i],           // (2) 0.1016
/*38 */                                   start1, length);                         // (1) 0.1044
/*40 */         }                                                                  // (14) 0.02198
/*42 */     }                                                                      // (15) 0.01099
/*44 */ }                                                                          // (17) 0.002747
