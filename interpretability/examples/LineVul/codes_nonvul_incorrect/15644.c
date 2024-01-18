// commit message qemu@36778660d7 (target=0, prob=0.62919974, correct=False): target/ppc: Eliminate htab_base and htab_mask variables
/*0  */ const ppc_hash_pte64_t *ppc_hash64_map_hptes(PowerPCCPU *cpu,                     // (5) 0.06055
/*2  */                                              hwaddr ptex, int n)                  // (0) 0.1035
/*4  */ {                                                                                 // (20) 0.001953
/*6  */     ppc_hash_pte64_t *hptes = NULL;                                               // (12) 0.03906
/*8  */     hwaddr pte_offset = ptex * HASH_PTE_SIZE_64;                                  // (9) 0.04688
/*12 */     if (cpu->env.external_htab == MMU_HASH64_KVM_MANAGED_HPT) {                   // (4) 0.0625
/*14 */         /*                                                                        // (18) 0.01562
/*16 */          * HTAB is controlled by KVM. Fetch into temporary buffer                 // (11) 0.04492
/*18 */          */                                                                       // (16) 0.01758
/*20 */         hptes = g_malloc(HASH_PTEG_SIZE_64);                                      // (7) 0.05078
/*22 */         kvmppc_read_hptes(hptes, ptex, n);                                        // (6) 0.05273
/*24 */     } else if (cpu->env.external_htab) {                                          // (13) 0.0332
/*26 */         /*                                                                        // (19) 0.01562
/*28 */          * HTAB is controlled by QEMU. Just point to the internally               // (10) 0.04688
/*30 */          * accessible PTEG.                                                       // (15) 0.02539
/*32 */          */                                                                       // (17) 0.01758
/*34 */         hptes = (ppc_hash_pte64_t *)(cpu->env.external_htab + pte_offset);        // (1) 0.07422
/*36 */     } else if (cpu->env.htab_base) {                                              // (14) 0.0332
/*38 */         hwaddr plen = n * HASH_PTE_SIZE_64;                                       // (8) 0.04883
/*40 */         hptes = address_space_map(CPU(cpu)->as, cpu->env.htab_base + pte_offset,  // (2) 0.07422
/*42 */                                  &plen, false);                                   // (3) 0.07422
/*44 */         if (plen < (n * HASH_PTE_SIZE_64)) {                                      // 0.0
/*46 */             hw_error("%s: Unable to map all requested HPTEs\n", __func__);        // 0.0
/*48 */         }                                                                         // 0.0
/*50 */     }                                                                             // 0.0
/*52 */     return hptes;                                                                 // 0.0
/*54 */ }                                                                                 // 0.0
