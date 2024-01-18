// commit message qemu@041d95f42e (target=0, prob=0.28741995, correct=True): target-ppc: Remove unused mmu models from ppc_tlb_invalidate_one
/*0  */ static inline void ppc4xx_tlb_invalidate_virt(CPUPPCState *env,                  // (4) 0.05418
/*2  */                                               target_ulong eaddr, uint32_t pid)  // (0) 0.1309
/*4  */ {                                                                                // (22) 0.002257
/*6  */ #if !defined(FLUSH_ALL_TLBS)                                                     // (12) 0.02935
/*8  */     CPUState *cs = CPU(ppc_env_get_cpu(env));                                    // (7) 0.0474
/*10 */     ppcemb_tlb_t *tlb;                                                           // (11) 0.03386
/*12 */     hwaddr raddr;                                                                // (16) 0.02032
/*14 */     target_ulong page, end;                                                      // (15) 0.02483
/*16 */     int i;                                                                       // (18) 0.01354
/*20 */     for (i = 0; i < env->nb_tlb; i++) {                                          // (8) 0.0474
/*22 */         tlb = &env->tlb.tlbe[i];                                                 // (9) 0.0474
/*24 */         if (ppcemb_tlb_check(env, tlb, &raddr, eaddr, pid, 0, i) == 0) {         // (1) 0.09029
/*26 */             end = tlb->EPN + tlb->size;                                          // (5) 0.05418
/*28 */             for (page = tlb->EPN; page < end; page += TARGET_PAGE_SIZE) {        // (2) 0.08126
/*30 */                 tlb_flush_page(cs, page);                                        // (3) 0.05869
/*32 */             }                                                                    // (14) 0.02709
/*34 */             tlb->prot &= ~PAGE_VALID;                                            // (6) 0.05418
/*36 */             break;                                                               // (13) 0.02935
/*38 */         }                                                                        // (17) 0.01806
/*40 */     }                                                                            // (19) 0.009029
/*42 */ #else                                                                            // (20) 0.004515
/*44 */     ppc4xx_tlb_invalidate_all(env);                                              // (10) 0.04289
/*46 */ #endif                                                                           // (21) 0.004515
/*48 */ }                                                                                // (23) 0.002257
