// commit message qemu@b16595275b (target=0, prob=0.49797013, correct=True): hw/arm/virt: allow pmu instantiation with userspace irqchip
/*0  */ MemTxAttrs kvm_arch_post_run(CPUState *cs, struct kvm_run *run)                  // (8) 0.05078
/*2  */ {                                                                                // (22) 0.001953
/*4  */     ARMCPU *cpu;                                                                 // (17) 0.01758
/*6  */     uint32_t switched_level;                                                     // (16) 0.02148
/*10 */     if (kvm_irqchip_in_kernel()) {                                               // (14) 0.0332
/*12 */         /*                                                                       // (19) 0.01562
/*14 */          * We only need to sync timer states with user-space interrupt           // (11) 0.04102
/*16 */          * controllers, so return early and save cycles if we don't.             // (10) 0.04297
/*18 */          */                                                                      // (18) 0.01758
/*20 */         return MEMTXATTRS_UNSPECIFIED;                                           // (13) 0.03516
/*22 */     }                                                                            // (21) 0.007813
/*26 */     cpu = ARM_CPU(cs);                                                           // (15) 0.02148
/*30 */     /* Synchronize our shadowed in-kernel device irq lines with the kvm ones */  // (9) 0.04492
/*32 */     if (run->s.regs.device_irq_level != cpu->device_irq_level) {                 // (5) 0.05664
/*34 */         switched_level = cpu->device_irq_level ^ run->s.regs.device_irq_level;   // (3) 0.06641
/*38 */         qemu_mutex_lock_iothread();                                              // (12) 0.03906
/*42 */         if (switched_level & KVM_ARM_DEV_EL1_VTIMER) {                           // (6) 0.05664
/*44 */             qemu_set_irq(cpu->gt_timer_outputs[GTIMER_VIRT],                     // (2) 0.07031
/*46 */                          !!(run->s.regs.device_irq_level &                       // (1) 0.07812
/*48 */                             KVM_ARM_DEV_EL1_VTIMER));                            // (0) 0.08008
/*50 */             switched_level &= ~KVM_ARM_DEV_EL1_VTIMER;                           // (4) 0.06055
/*52 */         }                                                                        // (20) 0.01562
/*56 */         if (switched_level & KVM_ARM_DEV_EL1_PTIMER) {                           // (7) 0.05664
/*58 */             qemu_set_irq(cpu->gt_timer_outputs[GTIMER_PHYS],                     // 0.0
/*60 */                          !!(run->s.regs.device_irq_level &                       // 0.0
/*62 */                             KVM_ARM_DEV_EL1_PTIMER));                            // 0.0
/*64 */             switched_level &= ~KVM_ARM_DEV_EL1_PTIMER;                           // 0.0
/*66 */         }                                                                        // 0.0
/*70 */         /* XXX PMU IRQ is missing */                                             // 0.0
/*74 */         if (switched_level) {                                                    // 0.0
/*76 */             qemu_log_mask(LOG_UNIMP, "%s: unhandled in-kernel device IRQ %x\n",  // 0.0
/*78 */                           __func__, switched_level);                             // 0.0
/*80 */         }                                                                        // 0.0
/*84 */         /* We also mark unknown levels as processed to not waste cycles */       // 0.0
/*86 */         cpu->device_irq_level = run->s.regs.device_irq_level;                    // 0.0
/*88 */         qemu_mutex_unlock_iothread();                                            // 0.0
/*90 */     }                                                                            // 0.0
/*94 */     return MEMTXATTRS_UNSPECIFIED;                                               // 0.0
/*96 */ }                                                                                // 0.0
