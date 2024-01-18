// commit message qemu@f45cb2f43f (target=1, prob=0.45688334, correct=False): target-mips: Avoid shifting left into sign bit
/*0  */ static void mvp_init (CPUMIPSState *env, const mips_def_t *def)                 // (6) 0.04687
/*2  */ {                                                                               // (15) 0.001953
/*4  */     env->mvp = g_malloc0(sizeof(CPUMIPSMVPContext));                            // (7) 0.04687
/*8  */     /* MVPConf1 implemented, TLB sharable, no gating storage support,           // (9) 0.03906
/*10 */        programmable cache partitioning implemented, number of allocatable       // (10) 0.0332
/*12 */        and sharable TLB entries, MVP has allocatable TCs, 2 VPEs                // (8) 0.04687
/*14 */        implemented, 5 TCs implemented. */                                       // (11) 0.02734
/*16 */     env->mvp->CP0_MVPConf0 = (1 << CP0MVPC0_M) | (1 << CP0MVPC0_TLBS) |         // (4) 0.08398
/*18 */                              (0 << CP0MVPC0_GS) | (1 << CP0MVPC0_PCP) |         // (2) 0.1074
/*20 */ // TODO: actually do 2 VPEs.                                                    // (14) 0.02149
/*22 */ //                             (1 << CP0MVPC0_TCA) | (0x1 << CP0MVPC0_PVPE) |   // (0) 0.1172
/*24 */ //                             (0x04 << CP0MVPC0_PTC);                          // (3) 0.08594
/*26 */                              (1 << CP0MVPC0_TCA) | (0x0 << CP0MVPC0_PVPE) |     // (1) 0.1152
/*28 */                              (0x00 << CP0MVPC0_PTC);                            // (5) 0.08398
/*30 */ #if !defined(CONFIG_USER_ONLY)                                                  // (12) 0.02539
/*32 */     /* Usermode has no TLB support */                                           // (13) 0.02344
/*34 */     env->mvp->CP0_MVPConf0 |= (env->tlb->nb_tlb << CP0MVPC0_PTLBE);             // 0.0
/*36 */ #endif                                                                          // 0.0
/*40 */     /* Allocatable CP1 have media extensions, allocatable CP1 have FP support,  // 0.0
/*42 */        no UDI implemented, no CP2 implemented, 1 CP1 implemented. */            // 0.0
/*44 */     env->mvp->CP0_MVPConf1 = (1 << CP0MVPC1_CIM) | (1 << CP0MVPC1_CIF) |        // 0.0
/*46 */                              (0x0 << CP0MVPC1_PCX) | (0x0 << CP0MVPC1_PCP2) |   // 0.0
/*48 */                              (0x1 << CP0MVPC1_PCP1);                            // 0.0
/*50 */ }                                                                               // 0.0
