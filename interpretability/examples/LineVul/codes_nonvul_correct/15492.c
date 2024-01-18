// commit message qemu@c34d440a72 (target=0, prob=0.013435958, correct=True): kvm: x86: Consolidate TCG and KVM MCE injection code
/*0 */ static int kvm_set_mce(CPUState *env, struct kvm_x86_mce *m)  // (1) 0.4154
/*2 */ {                                                             // (2) 0.01538
/*4 */     return kvm_vcpu_ioctl(env, KVM_X86_SET_MCE, m);           // (0) 0.4308
/*6 */ }                                                             // (3) 0.01538
