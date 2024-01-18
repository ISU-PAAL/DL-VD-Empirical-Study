// commit message qemu@4c055ab54f (target=0, prob=0.5158206, correct=False): cpu: Reclaim vCPU objects
/*0  */ int kvm_init_vcpu(CPUState *cpu)                                              // (12) 0.02734
/*2  */ {                                                                             // (28) 0.001953
/*4  */     KVMState *s = kvm_state;                                                  // (13) 0.02734
/*6  */     long mmap_size;                                                           // (23) 0.01758
/*8  */     int ret;                                                                  // (24) 0.01172
/*12 */     DPRINTF("kvm_init_vcpu\n");                                               // (10) 0.0332
/*16 */     ret = kvm_vm_ioctl(s, KVM_CREATE_VCPU, (void *)kvm_arch_vcpu_id(cpu));    // (0) 0.07617
/*18 */     if (ret < 0) {                                                            // (20) 0.01953
/*20 */         DPRINTF("kvm_create_vcpu failed\n");                                  // (6) 0.04297
/*22 */         goto err;                                                             // (21) 0.01953
/*24 */     }                                                                         // (27) 0.007812
/*28 */     cpu->kvm_fd = ret;                                                        // (17) 0.02344
/*30 */     cpu->kvm_state = s;                                                       // (18) 0.02344
/*32 */     cpu->kvm_vcpu_dirty = true;                                               // (11) 0.0293
/*36 */     mmap_size = kvm_ioctl(s, KVM_GET_VCPU_MMAP_SIZE, 0);                      // (3) 0.06055
/*38 */     if (mmap_size < 0) {                                                      // (15) 0.02539
/*40 */         ret = mmap_size;                                                      // (14) 0.02734
/*42 */         DPRINTF("KVM_GET_VCPU_MMAP_SIZE failed\n");                           // (5) 0.05273
/*44 */         goto err;                                                             // (19) 0.01953
/*46 */     }                                                                         // (25) 0.007813
/*50 */     cpu->kvm_run = mmap(NULL, mmap_size, PROT_READ | PROT_WRITE, MAP_SHARED,  // (1) 0.06836
/*52 */                         cpu->kvm_fd, 0);                                      // (2) 0.0625
/*54 */     if (cpu->kvm_run == MAP_FAILED) {                                         // (8) 0.03711
/*56 */         ret = -errno;                                                         // (16) 0.02539
/*58 */         DPRINTF("mmap'ing vcpu state failed\n");                              // (7) 0.04297
/*60 */         goto err;                                                             // (22) 0.01953
/*62 */     }                                                                         // (26) 0.007813
/*66 */     if (s->coalesced_mmio && !s->coalesced_mmio_ring) {                       // (4) 0.05273
/*68 */         s->coalesced_mmio_ring =                                              // (9) 0.03516
/*70 */             (void *)cpu->kvm_run + s->coalesced_mmio * PAGE_SIZE;             // 0.0
/*72 */     }                                                                         // 0.0
/*76 */     ret = kvm_arch_init_vcpu(cpu);                                            // 0.0
/*78 */ err:                                                                          // 0.0
/*80 */     return ret;                                                               // 0.0
/*82 */ }                                                                             // 0.0
