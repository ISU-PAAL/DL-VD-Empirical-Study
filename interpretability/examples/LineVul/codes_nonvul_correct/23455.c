// commit message qemu@79afc36d91 (target=0, prob=0.008718491, correct=True): s390x: consolidate floating interrupts
/*0  */ static void s390_virtio_irq(S390CPU *cpu, int config_change, uint64_t token)  // (1) 0.2314
/*2  */ {                                                                             // (6) 0.008264
/*4  */     if (kvm_enabled()) {                                                      // (3) 0.09091
/*6  */         kvm_s390_virtio_irq(cpu, config_change, token);                       // (2) 0.2231
/*8  */     } else {                                                                  // (4) 0.04959
/*10 */         cpu_inject_ext(cpu, VIRTIO_EXT_CODE, config_change, token);           // (0) 0.2562
/*12 */     }                                                                         // (5) 0.03306
/*14 */ }                                                                             // (7) 0.008264
