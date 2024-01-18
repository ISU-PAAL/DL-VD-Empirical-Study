// commit message qemu@3d0be8a5c1 (target=0, prob=0.009069781, correct=True): target-xtensa: fix tb invalidation for IBREAK and LOOP
/*0  */ void HELPER(wsr_ibreakenable)(uint32_t v)                                      // (5) 0.07964
/*2  */ {                                                                              // (11) 0.004425
/*4  */     uint32_t change = v ^ env->sregs[IBREAKENABLE];                            // (4) 0.1018
/*6  */     unsigned i;                                                                // (8) 0.02655
/*10 */     for (i = 0; i < env->config->nibreak; ++i) {                               // (2) 0.1062
/*12 */         if (change & (1 << i)) {                                               // (6) 0.07522
/*14 */             tb_invalidate_phys_page_range(                                     // (3) 0.1062
/*16 */                     env->sregs[IBREAKA + i], env->sregs[IBREAKA + i] + 1, 0);  // (0) 0.2212
/*18 */         }                                                                      // (7) 0.0354
/*20 */     }                                                                          // (9) 0.0177
/*22 */     env->sregs[IBREAKENABLE] = v & ((1 << env->config->nibreak) - 1);          // (1) 0.146
/*24 */ }                                                                              // (10) 0.004425
