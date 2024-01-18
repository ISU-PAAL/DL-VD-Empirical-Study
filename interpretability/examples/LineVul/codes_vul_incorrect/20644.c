// commit message qemu@5666ca4ae0 (target=1, prob=0.026071139, correct=False): kvm: ppc: fixes for KVM_SET_SREGS on init
/*0  */ int kvm_arch_init_vcpu(CPUState *cenv)                             // (3) 0.1164
/*2  */ {                                                                  // (7) 0.006849
/*4  */     int ret = 0;                                                   // (5) 0.05479
/*6  */     struct kvm_sregs sregs;                                        // (4) 0.09589
/*10 */     sregs.pvr = cenv->spr[SPR_PVR];                                // (2) 0.1438
/*12 */     ret = kvm_vcpu_ioctl(cenv, KVM_SET_SREGS, &sregs);             // (0) 0.2123
/*16 */     idle_timer = qemu_new_timer_ns(vm_clock, kvm_kick_env, cenv);  // (1) 0.2123
/*20 */     return ret;                                                    // (6) 0.0411
/*22 */ }                                                                  // (8) 0.006849
