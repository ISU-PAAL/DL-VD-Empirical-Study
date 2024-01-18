// commit message qemu@de13d21614 (target=0, prob=0.006174406, correct=True): s390x: cleanup interrupt injection
/*0 */ void kvm_s390_service_interrupt(S390CPU *cpu, uint32_t parm)              // (1) 0.3623
/*2 */ {                                                                         // (2) 0.01449
/*4 */     kvm_s390_interrupt_internal(cpu, KVM_S390_INT_SERVICE, parm, 0 , 1);  // (0) 0.4928
/*6 */ }                                                                         // (3) 0.01449
