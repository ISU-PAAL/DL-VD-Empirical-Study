// commit message qemu@b9bec74bcb (target=0, prob=0.014982054, correct=True): kvm: x86: Fix a few coding style violations
/*0  */ static int kvm_put_xcrs(CPUState *env)                // (3) 0.07979
/*2  */ {                                                     // (13) 0.005319
/*4  */ #ifdef KVM_CAP_XCRS                                   // (7) 0.05851
/*6  */     struct kvm_xcrs xcrs;                             // (5) 0.06915
/*10 */     if (!kvm_has_xcrs())                              // (6) 0.06915
/*12 */         return 0;                                     // (9) 0.05319
/*16 */     xcrs.nr_xcrs = 1;                                 // (4) 0.07447
/*18 */     xcrs.flags = 0;                                   // (8) 0.05851
/*20 */     xcrs.xcrs[0].xcr = 0;                             // (2) 0.09043
/*22 */     xcrs.xcrs[0].value = env->xcr0;                   // (1) 0.1064
/*24 */     return kvm_vcpu_ioctl(env, KVM_SET_XCRS, &xcrs);  // (0) 0.1489
/*26 */ #else                                                 // (11) 0.01064
/*28 */     return 0;                                         // (10) 0.03191
/*30 */ #endif                                                // (12) 0.01064
/*32 */ }                                                     // (14) 0.005319
