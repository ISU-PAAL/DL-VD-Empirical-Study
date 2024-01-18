// commit message qemu@c18ad9a54b (target=0, prob=0.51489097, correct=False): target-ppc: Eliminate kvmppc_kern_htab global
/*0  */ static hwaddr ppc_hash64_pteg_search(PowerPCCPU *cpu, hwaddr hash,       // (6) 0.05273
/*2  */                                      bool secondary, target_ulong ptem,  // (1) 0.08984
/*4  */                                      ppc_hash_pte64_t *pte)              // (0) 0.09766
/*6  */ {                                                                        // (22) 0.001953
/*8  */     CPUPPCState *env = &cpu->env;                                        // (14) 0.0293
/*10 */     int i;                                                               // (20) 0.01172
/*12 */     uint64_t token;                                                      // (18) 0.01758
/*14 */     target_ulong pte0, pte1;                                             // (15) 0.0293
/*16 */     target_ulong pte_index;                                              // (16) 0.02344
/*20 */     pte_index = (hash & env->htab_mask) * HPTES_PER_GROUP;               // (7) 0.05273
/*22 */     token = ppc_hash64_start_access(cpu, pte_index);                     // (9) 0.04297
/*24 */     if (!token) {                                                        // (19) 0.01562
/*26 */         return -1;                                                       // (17) 0.02148
/*28 */     }                                                                    // (21) 0.007812
/*30 */     for (i = 0; i < HPTES_PER_GROUP; i++) {                              // (10) 0.04297
/*32 */         pte0 = ppc_hash64_load_hpte0(cpu, token, i);                     // (3) 0.05859
/*34 */         pte1 = ppc_hash64_load_hpte1(cpu, token, i);                     // (4) 0.05859
/*38 */         if ((pte0 & HPTE64_V_VALID)                                      // (11) 0.04297
/*40 */             && (secondary == !!(pte0 & HPTE64_V_SECONDARY))              // (2) 0.06055
/*42 */             && HPTE64_V_COMPARE(pte0, ptem)) {                           // (5) 0.05859
/*44 */             pte->pte0 = pte0;                                            // (12) 0.04297
/*46 */             pte->pte1 = pte1;                                            // (13) 0.04297
/*48 */             ppc_hash64_stop_access(token);                               // (8) 0.04492
/*50 */             return (pte_index + i) * HASH_PTE_SIZE_64;                   // 0.0
/*52 */         }                                                                // 0.0
/*54 */     }                                                                    // 0.0
/*56 */     ppc_hash64_stop_access(token);                                       // 0.0
/*58 */     /*                                                                   // 0.0
/*60 */      * We didn't find a valid entry.                                     // 0.0
/*62 */      */                                                                  // 0.0
/*64 */     return -1;                                                           // 0.0
/*66 */ }                                                                        // 0.0
