// commit message qemu@4656e1f012 (target=1, prob=0.43973804, correct=False): ppc64: Rudimentary Support for extra page sizes on server CPUs
/*0  */ void ppc_tlb_invalidate_all(CPUPPCState *env)                     // (5) 0.03906
/*2  */ {                                                                 // (31) 0.001953
/*4  */     switch (env->mmu_model) {                                     // (17) 0.02539
/*6  */     case POWERPC_MMU_SOFT_6xx:                                    // (7) 0.03125
/*8  */     case POWERPC_MMU_SOFT_74xx:                                   // (8) 0.03125
/*10 */         ppc6xx_tlb_invalidate_all(env);                           // (2) 0.04492
/*12 */         break;                                                    // (25) 0.01758
/*14 */     case POWERPC_MMU_SOFT_4xx:                                    // (9) 0.03125
/*16 */     case POWERPC_MMU_SOFT_4xx_Z:                                  // (6) 0.03516
/*18 */         ppc4xx_tlb_invalidate_all(env);                           // (3) 0.04492
/*20 */         break;                                                    // (26) 0.01758
/*22 */     case POWERPC_MMU_REAL:                                        // (18) 0.02539
/*24 */         cpu_abort(env, "No TLB for PowerPC 4xx in real mode\n");  // (0) 0.05664
/*26 */         break;                                                    // (27) 0.01758
/*28 */     case POWERPC_MMU_MPC8xx:                                      // (12) 0.0293
/*30 */         /* XXX: TODO */                                           // (19) 0.02539
/*32 */         cpu_abort(env, "MPC8xx MMU model is not implemented\n");  // (1) 0.05469
/*34 */         break;                                                    // (28) 0.01758
/*36 */     case POWERPC_MMU_BOOKE:                                       // (14) 0.02734
/*38 */         tlb_flush(env, 1);                                        // (10) 0.03125
/*40 */         break;                                                    // (29) 0.01758
/*42 */     case POWERPC_MMU_BOOKE206:                                    // (13) 0.0293
/*44 */         booke206_flush_tlb(env, -1, 0);                           // (4) 0.04492
/*46 */         break;                                                    // (30) 0.01758
/*48 */     case POWERPC_MMU_32B:                                         // (20) 0.02539
/*50 */     case POWERPC_MMU_601:                                         // (22) 0.02344
/*52 */ #if defined(TARGET_PPC64)                                         // (24) 0.02148
/*54 */     case POWERPC_MMU_620:                                         // (23) 0.02344
/*56 */     case POWERPC_MMU_64B:                                         // (21) 0.02539
/*58 */     case POWERPC_MMU_2_06:                                        // (15) 0.02734
/*61 */ #endif /* defined(TARGET_PPC64) */                                // (16) 0.02539
/*63 */         tlb_flush(env, 1);                                        // (11) 0.03125
/*65 */         break;                                                    // 0.0
/*67 */     default:                                                      // 0.0
/*69 */         /* XXX: TODO */                                           // 0.0
/*71 */         cpu_abort(env, "Unknown MMU model\n");                    // 0.0
/*73 */         break;                                                    // 0.0
/*75 */     }                                                             // 0.0
/*77 */ }                                                                 // 0.0
