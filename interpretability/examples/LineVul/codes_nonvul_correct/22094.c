// commit message qemu@a426e12217 (target=0, prob=0.078599796, correct=True): kvm: Fix coding style violations
/*0  */ int kvm_set_signal_mask(CPUState *env, const sigset_t *sigset)  // (3) 0.1176
/*2  */ {                                                               // (11) 0.004525
/*4  */     struct kvm_signal_mask *sigmask;                            // (5) 0.0724
/*6  */     int r;                                                      // (9) 0.02715
/*10 */     if (!sigset)                                                // (7) 0.04072
/*12 */         return kvm_vcpu_ioctl(env, KVM_SET_SIGNAL_MASK, NULL);  // (0) 0.1448
/*16 */     sigmask = qemu_malloc(sizeof(*sigmask) + sizeof(*sigset));  // (2) 0.1267
/*20 */     sigmask->len = 8;                                           // (6) 0.04977
/*22 */     memcpy(sigmask->sigset, sigset, sizeof(*sigset));           // (4) 0.1086
/*24 */     r = kvm_vcpu_ioctl(env, KVM_SET_SIGNAL_MASK, sigmask);      // (1) 0.1403
/*26 */     free(sigmask);                                              // (8) 0.04072
/*30 */     return r;                                                   // (10) 0.02715
/*32 */ }                                                               // (12) 0.004525
