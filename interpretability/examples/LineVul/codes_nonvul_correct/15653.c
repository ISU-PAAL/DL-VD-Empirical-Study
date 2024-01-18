// commit message qemu@ecf5e8eae8 (target=0, prob=0.25891474, correct=True): target/arm: Make MPU_CTRL register banked for v8M
/*0  */ static inline bool regime_translation_disabled(CPUARMState *env,                // (12) 0.0293
/*2  */                                                ARMMMUIdx mmu_idx)               // (0) 0.1113
/*4  */ {                                                                               // (20) 0.001953
/*6  */     if (arm_feature(env, ARM_FEATURE_M)) {                                      // (10) 0.03711
/*8  */         switch (env->v7m.mpu_ctrl &                                             // (9) 0.03906
/*10 */                 (R_V7M_MPU_CTRL_ENABLE_MASK | R_V7M_MPU_CTRL_HFNMIENA_MASK)) {  // (1) 0.1074
/*12 */         case R_V7M_MPU_CTRL_ENABLE_MASK:                                        // (7) 0.05078
/*14 */             /* Enabled, but not for HardFault and NMI */                        // (8) 0.04688
/*16 */             return mmu_idx == ARMMMUIdx_MNegPri ||                              // (6) 0.05469
/*18 */                 mmu_idx == ARMMMUIdx_MSNegPri;                                  // (4) 0.06055
/*20 */         case R_V7M_MPU_CTRL_ENABLE_MASK | R_V7M_MPU_CTRL_HFNMIENA_MASK:         // (2) 0.08984
/*22 */             /* Enabled for all cases */                                         // (11) 0.0332
/*24 */             return false;                                                       // (14) 0.02734
/*26 */         case 0:                                                                 // (16) 0.01953
/*28 */         default:                                                                // (17) 0.01758
/*30 */             /* HFNMIENA set and ENABLE clear is UNPREDICTABLE, but              // (5) 0.05859
/*32 */              * we warned about that in armv7m_nvic.c when the guest set it.     // (3) 0.06445
/*34 */              */                                                                 // (15) 0.02539
/*36 */             return true;                                                        // (13) 0.02734
/*38 */         }                                                                       // (18) 0.01563
/*40 */     }                                                                           // (19) 0.007813
/*44 */     if (mmu_idx == ARMMMUIdx_S2NS) {                                            // 0.0
/*46 */         return (env->cp15.hcr_el2 & HCR_VM) == 0;                               // 0.0
/*48 */     }                                                                           // 0.0
/*50 */     return (regime_sctlr(env, mmu_idx) & SCTLR_M) == 0;                         // 0.0
/*52 */ }                                                                               // 0.0
