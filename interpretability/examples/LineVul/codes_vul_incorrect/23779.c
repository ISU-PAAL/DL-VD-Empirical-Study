// commit message qemu@be18b2b53e (target=1, prob=0.041927632, correct=False): target-ppc: Use actual page size encodings from HPTE
/*0   */ int ppc_hash64_handle_mmu_fault(PowerPCCPU *cpu, target_ulong eaddr,             // (4) 0.05664
/*2   */                                 int rwx, int mmu_idx)                            // (0) 0.08203
/*4   */ {                                                                                // (23) 0.001953
/*6   */     CPUState *cs = CPU(cpu);                                                     // (16) 0.02344
/*8   */     CPUPPCState *env = &cpu->env;                                                // (13) 0.0293
/*10  */     ppc_slb_t *slb;                                                              // (14) 0.02734
/*12  */     hwaddr pte_offset;                                                           // (19) 0.02148
/*14  */     ppc_hash_pte64_t pte;                                                        // (11) 0.03125
/*16  */     int pp_prot, amr_prot, prot;                                                 // (12) 0.0293
/*18  */     uint64_t new_pte1;                                                           // (15) 0.02539
/*20  */     const int need_prot[] = {PAGE_READ, PAGE_WRITE, PAGE_EXEC};                  // (6) 0.05078
/*22  */     hwaddr raddr;                                                                // (21) 0.01758
/*26  */     assert((rwx == 0) || (rwx == 1) || (rwx == 2));                              // (7) 0.04687
/*30  */     /* 1. Handle real mode accesses */                                           // (17) 0.02344
/*32  */     if (((rwx == 2) && (msr_ir == 0)) || ((rwx != 2) && (msr_dr == 0))) {        // (3) 0.07227
/*34  */         /* Translation is off */                                                 // (18) 0.02344
/*36  */         /* In real mode the top 4 effective address bits are ignored */          // (9) 0.03906
/*38  */         raddr = eaddr & 0x0FFFFFFFFFFFFFFFULL;                                   // (8) 0.04492
/*40  */         tlb_set_page(cs, eaddr & TARGET_PAGE_MASK, raddr & TARGET_PAGE_MASK,     // (1) 0.07812
/*42  */                      PAGE_READ | PAGE_WRITE | PAGE_EXEC, mmu_idx,                // (2) 0.07812
/*44  */                      TARGET_PAGE_SIZE);                                          // (5) 0.05469
/*46  */         return 0;                                                                // (20) 0.01953
/*48  */     }                                                                            // (22) 0.007813
/*52  */     /* 2. Translation is on, so look up the SLB */                               // (10) 0.0332
/*54  */     slb = slb_lookup(cpu, eaddr);                                                // 0.0
/*58  */     if (!slb) {                                                                  // 0.0
/*60  */         if (rwx == 2) {                                                          // 0.0
/*62  */             cs->exception_index = POWERPC_EXCP_ISEG;                             // 0.0
/*64  */             env->error_code = 0;                                                 // 0.0
/*66  */         } else {                                                                 // 0.0
/*68  */             cs->exception_index = POWERPC_EXCP_DSEG;                             // 0.0
/*70  */             env->error_code = 0;                                                 // 0.0
/*72  */             env->spr[SPR_DAR] = eaddr;                                           // 0.0
/*74  */         }                                                                        // 0.0
/*76  */         return 1;                                                                // 0.0
/*78  */     }                                                                            // 0.0
/*82  */     /* 3. Check for segment level no-execute violation */                        // 0.0
/*84  */     if ((rwx == 2) && (slb->vsid & SLB_VSID_N)) {                                // 0.0
/*86  */         cs->exception_index = POWERPC_EXCP_ISI;                                  // 0.0
/*88  */         env->error_code = 0x10000000;                                            // 0.0
/*90  */         return 1;                                                                // 0.0
/*92  */     }                                                                            // 0.0
/*96  */     /* 4. Locate the PTE in the hash table */                                    // 0.0
/*98  */     pte_offset = ppc_hash64_htab_lookup(cpu, slb, eaddr, &pte);                  // 0.0
/*100 */     if (pte_offset == -1) {                                                      // 0.0
/*102 */         if (rwx == 2) {                                                          // 0.0
/*104 */             cs->exception_index = POWERPC_EXCP_ISI;                              // 0.0
/*106 */             env->error_code = 0x40000000;                                        // 0.0
/*108 */         } else {                                                                 // 0.0
/*110 */             cs->exception_index = POWERPC_EXCP_DSI;                              // 0.0
/*112 */             env->error_code = 0;                                                 // 0.0
/*114 */             env->spr[SPR_DAR] = eaddr;                                           // 0.0
/*116 */             if (rwx == 1) {                                                      // 0.0
/*118 */                 env->spr[SPR_DSISR] = 0x42000000;                                // 0.0
/*120 */             } else {                                                             // 0.0
/*122 */                 env->spr[SPR_DSISR] = 0x40000000;                                // 0.0
/*124 */             }                                                                    // 0.0
/*126 */         }                                                                        // 0.0
/*128 */         return 1;                                                                // 0.0
/*130 */     }                                                                            // 0.0
/*132 */     qemu_log_mask(CPU_LOG_MMU,                                                   // 0.0
/*134 */                 "found PTE at offset %08" HWADDR_PRIx "\n", pte_offset);         // 0.0
/*138 */     /* 5. Check access permissions */                                            // 0.0
/*142 */     pp_prot = ppc_hash64_pte_prot(cpu, slb, pte);                                // 0.0
/*144 */     amr_prot = ppc_hash64_amr_prot(cpu, pte);                                    // 0.0
/*146 */     prot = pp_prot & amr_prot;                                                   // 0.0
/*150 */     if ((need_prot[rwx] & ~prot) != 0) {                                         // 0.0
/*152 */         /* Access right violation */                                             // 0.0
/*154 */         qemu_log_mask(CPU_LOG_MMU, "PTE access rejected\n");                     // 0.0
/*156 */         if (rwx == 2) {                                                          // 0.0
/*158 */             cs->exception_index = POWERPC_EXCP_ISI;                              // 0.0
/*160 */             env->error_code = 0x08000000;                                        // 0.0
/*162 */         } else {                                                                 // 0.0
/*164 */             target_ulong dsisr = 0;                                              // 0.0
/*168 */             cs->exception_index = POWERPC_EXCP_DSI;                              // 0.0
/*170 */             env->error_code = 0;                                                 // 0.0
/*172 */             env->spr[SPR_DAR] = eaddr;                                           // 0.0
/*174 */             if (need_prot[rwx] & ~pp_prot) {                                     // 0.0
/*176 */                 dsisr |= 0x08000000;                                             // 0.0
/*178 */             }                                                                    // 0.0
/*180 */             if (rwx == 1) {                                                      // 0.0
/*182 */                 dsisr |= 0x02000000;                                             // 0.0
/*184 */             }                                                                    // 0.0
/*186 */             if (need_prot[rwx] & ~amr_prot) {                                    // 0.0
/*188 */                 dsisr |= 0x00200000;                                             // 0.0
/*190 */             }                                                                    // 0.0
/*192 */             env->spr[SPR_DSISR] = dsisr;                                         // 0.0
/*194 */         }                                                                        // 0.0
/*196 */         return 1;                                                                // 0.0
/*198 */     }                                                                            // 0.0
/*202 */     qemu_log_mask(CPU_LOG_MMU, "PTE access granted !\n");                        // 0.0
/*206 */     /* 6. Update PTE referenced and changed bits if necessary */                 // 0.0
/*210 */     new_pte1 = pte.pte1 | HPTE64_R_R; /* set referenced bit */                   // 0.0
/*212 */     if (rwx == 1) {                                                              // 0.0
/*214 */         new_pte1 |= HPTE64_R_C; /* set changed (dirty) bit */                    // 0.0
/*216 */     } else {                                                                     // 0.0
/*218 */         /* Treat the page as read-only for now, so that a later write            // 0.0
/*220 */          * will pass through this function again to set the C bit */             // 0.0
/*222 */         prot &= ~PAGE_WRITE;                                                     // 0.0
/*224 */     }                                                                            // 0.0
/*228 */     if (new_pte1 != pte.pte1) {                                                  // 0.0
/*230 */         ppc_hash64_store_hpte(cpu, pte_offset / HASH_PTE_SIZE_64,                // 0.0
/*232 */                               pte.pte0, new_pte1);                               // 0.0
/*234 */     }                                                                            // 0.0
/*238 */     /* 7. Determine the real address from the PTE */                             // 0.0
/*242 */     raddr = deposit64(pte.pte1 & HPTE64_R_RPN, 0, slb->sps->page_shift, eaddr);  // 0.0
/*246 */     tlb_set_page(cs, eaddr & TARGET_PAGE_MASK, raddr & TARGET_PAGE_MASK,         // 0.0
/*248 */                  prot, mmu_idx, TARGET_PAGE_SIZE);                               // 0.0
/*252 */     return 0;                                                                    // 0.0
/*254 */ }                                                                                // 0.0
