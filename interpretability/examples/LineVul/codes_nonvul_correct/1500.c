// commit message qemu@f73a2575a3 (target=0, prob=0.11121161, correct=True): pseries: More complete WIMG validation in H_ENTER code
/*0   */ static target_ulong h_enter(CPUState *env, sPAPREnvironment *spapr,   // (2) 0.04883
/*2   */                             target_ulong opcode, target_ulong *args)  // (0) 0.08008
/*4   */ {                                                                     // (30) 0.001953
/*6   */     target_ulong flags = args[0];                                     // (17) 0.02539
/*8   */     target_ulong pte_index = args[1];                                 // (10) 0.03125
/*10  */     target_ulong pteh = args[2];                                      // (13) 0.0293
/*12  */     target_ulong ptel = args[3];                                      // (16) 0.02734
/*14  */     target_ulong i;                                                   // (23) 0.01758
/*16  */     uint8_t *hpte;                                                    // (20) 0.02344
/*20  */     /* only handle 4k and 16M pages for now */                        // (14) 0.0293
/*22  */     if (pteh & HPTE_V_LARGE) {                                        // (9) 0.03516
/*24  */ #if 0 /* We don't support 64k pages yet */                            // (19) 0.02539
/*26  */         if ((ptel & 0xf000) == 0x1000) {                              // (5) 0.04297
/*28  */             /* 64k page */                                            // (11) 0.03125
/*30  */         } else                                                        // (25) 0.01758
/*32  */ #endif                                                                // (29) 0.003906
/*34  */         if ((ptel & 0xff000) == 0) {                                  // (7) 0.03906
/*36  */             /* 16M page */                                            // (12) 0.03125
/*38  */             /* lowest AVA bit must be 0 for 16M pages */              // (3) 0.04687
/*40  */             if (pteh & 0x80) {                                        // (6) 0.04102
/*42  */                 return H_PARAMETER;                                   // (4) 0.04492
/*44  */             }                                                         // (21) 0.02344
/*46  */         } else {                                                      // (22) 0.01953
/*48  */             return H_PARAMETER;                                       // (8) 0.03711
/*50  */         }                                                             // (26) 0.01562
/*52  */     }                                                                 // (27) 0.007812
/*56  */     /* FIXME: bounds check the pa? */                                 // (18) 0.02539
/*60  */     /* Check WIMG */                                                  // (24) 0.01758
/*62  */     if ((ptel & HPTE_R_WIMG) != HPTE_R_M) {                           // (1) 0.05078
/*64  */         return H_PARAMETER;                                           // (15) 0.0293
/*66  */     }                                                                 // (28) 0.007812
/*68  */     pteh &= ~0x60ULL;                                                 // 0.0
/*72  */     if ((pte_index * HASH_PTE_SIZE_64) & ~env->htab_mask) {           // 0.0
/*74  */         return H_PARAMETER;                                           // 0.0
/*76  */     }                                                                 // 0.0
/*78  */     if (likely((flags & H_EXACT) == 0)) {                             // 0.0
/*80  */         pte_index &= ~7ULL;                                           // 0.0
/*82  */         hpte = env->external_htab + (pte_index * HASH_PTE_SIZE_64);   // 0.0
/*84  */         for (i = 0; ; ++i) {                                          // 0.0
/*86  */             if (i == 8) {                                             // 0.0
/*88  */                 return H_PTEG_FULL;                                   // 0.0
/*90  */             }                                                         // 0.0
/*92  */             if (((ldq_p(hpte) & HPTE_V_VALID) == 0) &&                // 0.0
/*94  */                 lock_hpte(hpte, HPTE_V_HVLOCK | HPTE_V_VALID)) {      // 0.0
/*96  */                 break;                                                // 0.0
/*98  */             }                                                         // 0.0
/*100 */             hpte += HASH_PTE_SIZE_64;                                 // 0.0
/*102 */         }                                                             // 0.0
/*104 */     } else {                                                          // 0.0
/*106 */         i = 0;                                                        // 0.0
/*108 */         hpte = env->external_htab + (pte_index * HASH_PTE_SIZE_64);   // 0.0
/*110 */         if (!lock_hpte(hpte, HPTE_V_HVLOCK | HPTE_V_VALID)) {         // 0.0
/*112 */             return H_PTEG_FULL;                                       // 0.0
/*114 */         }                                                             // 0.0
/*116 */     }                                                                 // 0.0
/*118 */     stq_p(hpte + (HASH_PTE_SIZE_64/2), ptel);                         // 0.0
/*120 */     /* eieio();  FIXME: need some sort of barrier for smp? */         // 0.0
/*122 */     stq_p(hpte, pteh);                                                // 0.0
/*126 */     assert(!(ldq_p(hpte) & HPTE_V_HVLOCK));                           // 0.0
/*128 */     args[0] = pte_index + i;                                          // 0.0
/*130 */     return H_SUCCESS;                                                 // 0.0
/*132 */ }                                                                     // 0.0
