// commit message qemu@def74c0cf0 (target=1, prob=0.057783537, correct=False): target-mips: fix compiler warnings (clang 5)
/*0  */ int mips_cpu_handle_mmu_fault(CPUState *cs, vaddr address, int rw,              // (5) 0.05273
/*2  */                               int mmu_idx)                                      // (4) 0.07031
/*4  */ {                                                                               // (26) 0.001953
/*6  */     MIPSCPU *cpu = MIPS_CPU(cs);                                                // (11) 0.03125
/*8  */     CPUMIPSState *env = &cpu->env;                                              // (12) 0.0293
/*10 */ #if !defined(CONFIG_USER_ONLY)                                                  // (15) 0.02539
/*12 */     hwaddr physical;                                                            // (19) 0.01563
/*14 */     int prot;                                                                   // (22) 0.01172
/*16 */     int access_type;                                                            // (20) 0.01562
/*18 */ #endif                                                                          // (24) 0.003906
/*20 */     int ret = 0;                                                                // (18) 0.01563
/*24 */ #if 0                                                                           // (23) 0.005859
/*26 */     log_cpu_state(cs, 0);                                                       // (13) 0.02539
/*28 */ #endif                                                                          // (25) 0.003906
/*30 */     qemu_log_mask(CPU_LOG_MMU,                                                  // (8) 0.03516
/*32 */               "%s pc " TARGET_FMT_lx " ad %" VADDR_PRIx " rw %d mmu_idx %d\n",  // (0) 0.09961
/*34 */               __func__, env->active_tc.PC, address, rw, mmu_idx);               // (3) 0.07031
/*38 */     /* data access */                                                           // (21) 0.01367
/*40 */ #if !defined(CONFIG_USER_ONLY)                                                  // (14) 0.02539
/*42 */     /* XXX: put correct access by using cpu_restore_state()                     // (9) 0.03516
/*44 */        correctly */                                                             // (17) 0.01563
/*46 */     access_type = ACCESS_INT;                                                   // (16) 0.02344
/*48 */     ret = get_physical_address(env, &physical, &prot,                           // (6) 0.03711
/*50 */                                address, rw, access_type);                       // (1) 0.07617
/*52 */     qemu_log_mask(CPU_LOG_MMU,                                                  // (10) 0.03516
/*54 */              "%s address=%" VADDR_PRIx " ret %d physical " TARGET_FMT_plx       // (2) 0.07422
/*56 */              " prot %d\n",                                                      // (7) 0.03711
/*58 */              __func__, address, ret, physical, prot);                           // 0.0
/*60 */     if (ret == TLBRET_MATCH) {                                                  // 0.0
/*62 */         tlb_set_page(cs, address & TARGET_PAGE_MASK,                            // 0.0
/*64 */                      physical & TARGET_PAGE_MASK, prot | PAGE_EXEC,             // 0.0
/*66 */                      mmu_idx, TARGET_PAGE_SIZE);                                // 0.0
/*68 */         ret = 0;                                                                // 0.0
/*70 */     } else if (ret < 0)                                                         // 0.0
/*72 */ #endif                                                                          // 0.0
/*74 */     {                                                                           // 0.0
/*76 */         raise_mmu_exception(env, address, rw, ret);                             // 0.0
/*78 */         ret = 1;                                                                // 0.0
/*80 */     }                                                                           // 0.0
/*84 */     return ret;                                                                 // 0.0
/*86 */ }                                                                               // 0.0
