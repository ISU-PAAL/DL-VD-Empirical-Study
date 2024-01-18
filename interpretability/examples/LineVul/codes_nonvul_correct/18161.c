// commit message qemu@e37e6ee6e1 (target=0, prob=0.08594802, correct=True): Allow 5 mmu indexes.
/*0  */ void tlb_flush_page(CPUState *env, target_ulong addr)              // (7) 0.0504
/*2  */ {                                                                  // (24) 0.002653
/*4  */     int i;                                                         // (18) 0.01592
/*8  */ #if defined(DEBUG_TLB)                                             // (16) 0.02387
/*10 */     printf("tlb_flush_page: " TARGET_FMT_lx "\n", addr);           // (1) 0.06897
/*12 */ #endif                                                             // (20) 0.005305
/*14 */     /* must reset current TB so that interrupts cannot modify the  // (11) 0.03714
/*16 */        links while we are modifying them */                        // (12) 0.03448
/*18 */     env->current_tb = NULL;                                        // (15) 0.03183
/*22 */     addr &= TARGET_PAGE_MASK;                                      // (9) 0.03979
/*24 */     i = (addr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);           // (0) 0.07427
/*26 */     tlb_flush_entry(&env->tlb_table[0][i], addr);                  // (2) 0.06101
/*28 */     tlb_flush_entry(&env->tlb_table[1][i], addr);                  // (3) 0.06101
/*30 */ #if (NB_MMU_MODES >= 3)                                            // (13) 0.03448
/*32 */     tlb_flush_entry(&env->tlb_table[2][i], addr);                  // (4) 0.06101
/*34 */ #if (NB_MMU_MODES == 4)                                            // (14) 0.03448
/*36 */     tlb_flush_entry(&env->tlb_table[3][i], addr);                  // (5) 0.06101
/*38 */ #endif                                                             // (21) 0.005305
/*40 */ #endif                                                             // (22) 0.005305
/*44 */     tlb_flush_jmp_cache(env, addr);                                // (8) 0.04509
/*48 */ #ifdef USE_KQEMU                                                   // (17) 0.02387
/*50 */     if (env->kqemu_enabled) {                                      // (10) 0.03979
/*52 */         kqemu_flush_page(env, addr);                               // (6) 0.05305
/*54 */     }                                                              // (19) 0.01061
/*56 */ #endif                                                             // (23) 0.005305
/*58 */ }                                                                  // (25) 0.002653
