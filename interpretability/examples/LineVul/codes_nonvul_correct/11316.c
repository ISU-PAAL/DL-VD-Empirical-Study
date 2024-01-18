// commit message qemu@62c58ee0b2 (target=0, prob=0.3515005, correct=True): target/arm: Make MPU_RBAR, MPU_RLAR banked for v8M
/*0   */ static bool get_phys_addr_pmsav8(CPUARMState *env, uint32_t address,             // (5) 0.04883
/*2   */                                  MMUAccessType access_type, ARMMMUIdx mmu_idx,   // (1) 0.09961
/*4   */                                  hwaddr *phys_ptr, int *prot, uint32_t *fsr)     // (0) 0.1016
/*6   */ {                                                                                // (25) 0.001953
/*8   */     ARMCPU *cpu = arm_env_get_cpu(env);                                          // (11) 0.03711
/*10  */     bool is_user = regime_is_user(env, mmu_idx);                                 // (7) 0.04297
/*12  */     int n;                                                                       // (22) 0.01172
/*14  */     int matchregion = -1;                                                        // (18) 0.01953
/*16  */     bool hit = false;                                                            // (21) 0.01562
/*20  */     *phys_ptr = address;                                                         // (19) 0.01953
/*22  */     *prot = 0;                                                                   // (20) 0.01563
/*26  */     /* Unlike the ARM ARM pseudocode, we don't need to check whether this        // (10) 0.03906
/*28  */      * was an exception vector read from the vector table (which is always       // (12) 0.03516
/*30  */      * done using the default system address map), because those accesses        // (13) 0.0332
/*32  */      * are done in arm_v7m_load_vector(), which always does a direct             // (6) 0.04492
/*34  */      * read using address_space_ldl(), rather than going via this function.      // (9) 0.04102
/*36  */      */                                                                          // (24) 0.009766
/*38  */     if (regime_translation_disabled(env, mmu_idx)) { /* MPU disabled */          // (4) 0.05078
/*40  */         hit = true;                                                              // (15) 0.02148
/*42  */     } else if (m_is_ppb_region(env, address)) {                                  // (8) 0.04102
/*44  */         hit = true;                                                              // (16) 0.02148
/*46  */     } else if (pmsav7_use_background_region(cpu, mmu_idx, is_user)) {            // (3) 0.06055
/*48  */         hit = true;                                                              // (17) 0.02148
/*50  */     } else {                                                                     // (23) 0.01172
/*52  */         for (n = (int)cpu->pmsav7_dregion - 1; n >= 0; n--) {                    // (2) 0.06641
/*54  */             /* region search */                                                  // (14) 0.0293
/*56  */             /* Note that the base address is bits [31:5] from the register       // 0.0
/*58  */              * with bits [4:0] all zeroes, but the limit address is bits         // 0.0
/*60  */              * [31:5] from the register with bits [4:0] all ones.                // 0.0
/*62  */              */                                                                  // 0.0
/*64  */             uint32_t base = env->pmsav8.rbar[n] & ~0x1f;                         // 0.0
/*66  */             uint32_t limit = env->pmsav8.rlar[n] | 0x1f;                         // 0.0
/*70  */             if (!(env->pmsav8.rlar[n] & 0x1)) {                                  // 0.0
/*72  */                 /* Region disabled */                                            // 0.0
/*74  */                 continue;                                                        // 0.0
/*76  */             }                                                                    // 0.0
/*80  */             if (address < base || address > limit) {                             // 0.0
/*82  */                 continue;                                                        // 0.0
/*84  */             }                                                                    // 0.0
/*88  */             if (hit) {                                                           // 0.0
/*90  */                 /* Multiple regions match -- always a failure (unlike            // 0.0
/*92  */                  * PMSAv7 where highest-numbered-region wins)                    // 0.0
/*94  */                  */                                                              // 0.0
/*96  */                 *fsr = 0x00d; /* permission fault */                             // 0.0
/*98  */                 return true;                                                     // 0.0
/*100 */             }                                                                    // 0.0
/*104 */             matchregion = n;                                                     // 0.0
/*106 */             hit = true;                                                          // 0.0
/*110 */             if (base & ~TARGET_PAGE_MASK) {                                      // 0.0
/*112 */                 qemu_log_mask(LOG_UNIMP,                                         // 0.0
/*114 */                               "MPU_RBAR[%d]: No support for MPU region base"     // 0.0
/*116 */                               "address of 0x%" PRIx32 ". Minimum alignment is "  // 0.0
/*118 */                               "%d\n",                                            // 0.0
/*120 */                               n, base, TARGET_PAGE_BITS);                        // 0.0
/*122 */                 continue;                                                        // 0.0
/*124 */             }                                                                    // 0.0
/*126 */             if ((limit + 1) & ~TARGET_PAGE_MASK) {                               // 0.0
/*128 */                 qemu_log_mask(LOG_UNIMP,                                         // 0.0
/*130 */                               "MPU_RBAR[%d]: No support for MPU region limit"    // 0.0
/*132 */                               "address of 0x%" PRIx32 ". Minimum alignment is "  // 0.0
/*134 */                               "%d\n",                                            // 0.0
/*136 */                               n, limit, TARGET_PAGE_BITS);                       // 0.0
/*138 */                 continue;                                                        // 0.0
/*140 */             }                                                                    // 0.0
/*142 */         }                                                                        // 0.0
/*144 */     }                                                                            // 0.0
/*148 */     if (!hit) {                                                                  // 0.0
/*150 */         /* background fault */                                                   // 0.0
/*152 */         *fsr = 0;                                                                // 0.0
/*154 */         return true;                                                             // 0.0
/*156 */     }                                                                            // 0.0
/*160 */     if (matchregion == -1) {                                                     // 0.0
/*162 */         /* hit using the background region */                                    // 0.0
/*164 */         get_phys_addr_pmsav7_default(env, mmu_idx, address, prot);               // 0.0
/*166 */     } else {                                                                     // 0.0
/*168 */         uint32_t ap = extract32(env->pmsav8.rbar[matchregion], 1, 2);            // 0.0
/*170 */         uint32_t xn = extract32(env->pmsav8.rbar[matchregion], 0, 1);            // 0.0
/*174 */         if (m_is_system_region(env, address)) {                                  // 0.0
/*176 */             /* System space is always execute never */                           // 0.0
/*178 */             xn = 1;                                                              // 0.0
/*180 */         }                                                                        // 0.0
/*184 */         *prot = simple_ap_to_rw_prot(env, mmu_idx, ap);                          // 0.0
/*186 */         if (*prot && !xn) {                                                      // 0.0
/*188 */             *prot |= PAGE_EXEC;                                                  // 0.0
/*190 */         }                                                                        // 0.0
/*192 */         /* We don't need to look the attribute up in the MAIR0/MAIR1             // 0.0
/*194 */          * registers because that only tells us about cacheability.              // 0.0
/*196 */          */                                                                      // 0.0
/*198 */     }                                                                            // 0.0
/*202 */     *fsr = 0x00d; /* Permission fault */                                         // 0.0
/*204 */     return !(*prot & (1 << access_type));                                        // 0.0
/*206 */ }                                                                                // 0.0
