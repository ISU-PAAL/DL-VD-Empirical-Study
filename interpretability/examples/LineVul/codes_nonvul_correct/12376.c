// commit message qemu@abd696e4f7 (target=0, prob=0.0431059, correct=True): pc-bios/s390-ccw: make checkpatch happy
/*0 */ static void virtio_notify(struct subchannel_id schid)             // (1) 0.2544
/*2 */ {                                                                 // (3) 0.01586
/*4 */     kvm_hypercall(KVM_S390_VIRTIO_CCW_NOTIFY, *(u32*)&schid, 0);  // (0) 0.5866
/*6 */ }                                                                 // (2) 0.01587
