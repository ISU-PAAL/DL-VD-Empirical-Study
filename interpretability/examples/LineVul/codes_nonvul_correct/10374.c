// commit message qemu@b131c74a0e (target=0, prob=0.23910746, correct=True): kvm: Clean up irqfd API
/*0 */ int kvm_irqchip_add_irqfd(KVMState *s, int fd, int virq)  // (0) 0.4242
/*2 */ {                                                         // (2) 0.01515
/*4 */     return kvm_irqchip_assign_irqfd(s, fd, virq, true);   // (1) 0.4242
/*6 */ }                                                         // (3) 0.01515
