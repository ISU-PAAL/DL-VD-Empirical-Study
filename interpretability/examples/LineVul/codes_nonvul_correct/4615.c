// commit message qemu@b9bec74bcb (target=0, prob=0.40318167, correct=True): kvm: x86: Fix a few coding style violations
/*0  */ static int kvm_put_xsave(CPUState *env)                             // (18) 0.0293
/*2  */ {                                                                   // (24) 0.001953
/*4  */ #ifdef KVM_CAP_XSAVE                                                // (21) 0.02148
/*6  */     int i, r;                                                       // (23) 0.01562
/*8  */     struct kvm_xsave* xsave;                                        // (20) 0.02539
/*10 */     uint16_t cwd, swd, twd, fop;                                    // (11) 0.03711
/*14 */     if (!kvm_has_xsave())                                           // (19) 0.02539
/*16 */         return kvm_put_fpu(env);                                    // (13) 0.03516
/*20 */     xsave = qemu_memalign(4096, sizeof(struct kvm_xsave));          // (6) 0.04883
/*22 */     memset(xsave, 0, sizeof(struct kvm_xsave));                     // (9) 0.03906
/*24 */     cwd = swd = twd = fop = 0;                                      // (15) 0.0332
/*26 */     swd = env->fpus & ~(7 << 11);                                   // (16) 0.0332
/*28 */     swd |= (env->fpstt & 7) << 11;                                  // (12) 0.03711
/*30 */     cwd = env->fpuc;                                                // (22) 0.02148
/*32 */     for (i = 0; i < 8; ++i)                                         // (17) 0.03125
/*34 */         twd |= (!env->fptags[i]) << i;                              // (7) 0.04492
/*36 */     xsave->region[0] = (uint32_t)(swd << 16) + cwd;                 // (4) 0.05078
/*38 */     xsave->region[1] = (uint32_t)(fop << 16) + twd;                 // (5) 0.05078
/*40 */     memcpy(&xsave->region[XSAVE_ST_SPACE], env->fpregs,             // (3) 0.05273
/*42 */             sizeof env->fpregs);                                    // (14) 0.03516
/*44 */     memcpy(&xsave->region[XSAVE_XMM_SPACE], env->xmm_regs,          // (2) 0.05859
/*46 */             sizeof env->xmm_regs);                                  // (10) 0.03906
/*48 */     xsave->region[XSAVE_MXCSR] = env->mxcsr;                        // (8) 0.04492
/*50 */     *(uint64_t *)&xsave->region[XSAVE_XSTATE_BV] = env->xstate_bv;  // (0) 0.06836
/*52 */     memcpy(&xsave->region[XSAVE_YMMH_SPACE], env->ymmh_regs,        // (1) 0.06055
/*54 */             sizeof env->ymmh_regs);                                 // 0.0
/*56 */     r = kvm_vcpu_ioctl(env, KVM_SET_XSAVE, xsave);                  // 0.0
/*58 */     qemu_free(xsave);                                               // 0.0
/*60 */     return r;                                                       // 0.0
/*62 */ #else                                                               // 0.0
/*64 */     return kvm_put_fpu(env);                                        // 0.0
/*66 */ #endif                                                              // 0.0
/*68 */ }                                                                   // 0.0
