// commit message qemu@bee62662a3 (target=0, prob=0.42394218, correct=True): mips/kvm: Support MSA in MIPS KVM guests
/*0  */ static int kvm_mips_get_fpu_registers(CPUState *cs)                               // (8) 0.04102
/*2  */ {                                                                                 // (22) 0.001953
/*4  */     MIPSCPU *cpu = MIPS_CPU(cs);                                                  // (10) 0.03125
/*6  */     CPUMIPSState *env = &cpu->env;                                                // (11) 0.0293
/*8  */     int err, ret = 0;                                                             // (17) 0.01953
/*10 */     unsigned int i;                                                               // (21) 0.01367
/*14 */     /* Only get FPU state if we're emulating a CPU with an FPU */                 // (7) 0.04102
/*16 */     if (env->CP0_Config1 & (1 << CP0C1_FP)) {                                     // (6) 0.04688
/*18 */         /* FPU Control Registers */                                               // (14) 0.02734
/*20 */         err = kvm_mips_get_one_ureg(cs, KVM_REG_MIPS_FCR_IR,                      // (3) 0.07227
/*22 */                                     &env->active_fpu.fcr0);                       // (0) 0.0918
/*24 */         if (err < 0) {                                                            // (15) 0.02734
/*26 */             DPRINTF("%s: Failed to get FCR_IR (%d)\n", __func__, err);            // (5) 0.07031
/*28 */             ret = err;                                                            // (12) 0.0293
/*30 */         }                                                                         // (19) 0.01562
/*32 */         err = kvm_mips_get_one_ureg(cs, KVM_REG_MIPS_FCR_CSR,                     // (2) 0.07422
/*34 */                                     &env->active_fpu.fcr31);                      // (1) 0.0918
/*36 */         if (err < 0) {                                                            // (16) 0.02734
/*38 */             DPRINTF("%s: Failed to get FCR_CSR (%d)\n", __func__, err);           // (4) 0.07227
/*40 */             ret = err;                                                            // (13) 0.0293
/*42 */         } else {                                                                  // (18) 0.01953
/*44 */             restore_fp_status(env);                                               // (9) 0.03711
/*46 */         }                                                                         // (20) 0.01562
/*50 */         /* Floating point registers */                                            // 0.0
/*52 */         for (i = 0; i < 32; ++i) {                                                // 0.0
/*54 */             if (env->CP0_Status & (1 << CP0St_FR)) {                              // 0.0
/*56 */                 err = kvm_mips_get_one_ureg64(cs, KVM_REG_MIPS_FPR_64(i),         // 0.0
/*58 */                                               &env->active_fpu.fpr[i].d);         // 0.0
/*60 */             } else {                                                              // 0.0
/*62 */                 err = kvm_mips_get_one_ureg(cs, KVM_REG_MIPS_FPR_32(i),           // 0.0
/*64 */                                       &env->active_fpu.fpr[i].w[FP_ENDIAN_IDX]);  // 0.0
/*66 */             }                                                                     // 0.0
/*68 */             if (err < 0) {                                                        // 0.0
/*70 */                 DPRINTF("%s: Failed to get FPR%u (%d)\n", __func__, i, err);      // 0.0
/*72 */                 ret = err;                                                        // 0.0
/*74 */             }                                                                     // 0.0
/*76 */         }                                                                         // 0.0
/*78 */     }                                                                             // 0.0
/*82 */     return ret;                                                                   // 0.0
/*84 */ }                                                                                 // 0.0
