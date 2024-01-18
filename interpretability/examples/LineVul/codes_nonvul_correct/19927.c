// commit message qemu@8103b4d161 (target=0, prob=0.025691137, correct=True): s390x: Dispatch interrupts to KVM or the real CPU
/*0  */ static void virtio_s390_notify(void *opaque, uint16_t vector)   // (2) 0.1774
/*2  */ {                                                               // (5) 0.008065
/*4  */     VirtIOS390Device *dev = (VirtIOS390Device*)opaque;          // (3) 0.1774
/*6  */     uint64_t token = s390_virtio_device_vq_token(dev, vector);  // (1) 0.2097
/*10 */     /* XXX kvm dependency! */                                   // (4) 0.08065
/*12 */     kvm_s390_virtio_irq(s390_cpu_addr2state(0), 0, token);      // (0) 0.2419
/*14 */ }                                                               // (6) 0.008065
