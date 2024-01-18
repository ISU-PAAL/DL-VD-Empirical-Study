// commit message qemu@1da41cc1c6 (target=0, prob=0.57164156, correct=False): arm: vgic device control api support
/*0  */ static void kvm_arm_gic_realize(DeviceState *dev, Error **errp)                  // (4) 0.04492
/*2  */ {                                                                                // (28) 0.001953
/*4  */     int i;                                                                       // (23) 0.01172
/*6  */     GICState *s = KVM_ARM_GIC(dev);                                              // (10) 0.03711
/*8  */     SysBusDevice *sbd = SYS_BUS_DEVICE(dev);                                     // (6) 0.04102
/*10 */     KVMARMGICClass *kgc = KVM_ARM_GIC_GET_CLASS(s);                              // (3) 0.05273
/*14 */     kgc->parent_realize(dev, errp);                                              // (16) 0.03125
/*16 */     if (error_is_set(errp)) {                                                    // (17) 0.0293
/*18 */         return;                                                                  // (20) 0.01758
/*20 */     }                                                                            // (26) 0.007812
/*24 */     i = s->num_irq - GIC_INTERNAL;                                               // (11) 0.03711
/*26 */     /* For the GIC, also expose incoming GPIO lines for PPIs for each CPU.       // (7) 0.04102
/*28 */      * GPIO array layout is thus:                                                // (19) 0.02148
/*30 */      *  [0..N-1] SPIs                                                            // (18) 0.0293
/*32 */      *  [N..N+31] PPIs for CPU 0                                                 // (14) 0.03516
/*34 */      *  [N+32..N+63] PPIs for CPU 1                                              // (8) 0.03906
/*36 */      *   ...                                                                     // (21) 0.01562
/*38 */      */                                                                          // (24) 0.009766
/*40 */     i += (GIC_INTERNAL * s->num_cpu);                                            // (12) 0.03711
/*42 */     qdev_init_gpio_in(dev, kvm_arm_gic_set_irq, i);                              // (1) 0.05859
/*44 */     /* We never use our outbound IRQ lines but provide them so that              // (15) 0.03516
/*46 */      * we maintain the same interface as the non-KVM GIC.                        // (13) 0.03711
/*48 */      */                                                                          // (25) 0.009766
/*50 */     for (i = 0; i < s->num_cpu; i++) {                                           // (9) 0.03906
/*52 */         sysbus_init_irq(sbd, &s->parent_irq[i]);                                 // (2) 0.05469
/*54 */     }                                                                            // (27) 0.007812
/*56 */     /* Distributor */                                                            // (22) 0.01367
/*58 */     memory_region_init_reservation(&s->iomem, OBJECT(s),                         // (5) 0.04297
/*60 */                                    "kvm-gic_dist", 0x1000);                      // (0) 0.0918
/*62 */     sysbus_init_mmio(sbd, &s->iomem);                                            // 0.0
/*64 */     kvm_arm_register_device(&s->iomem,                                           // 0.0
/*66 */                             (KVM_ARM_DEVICE_VGIC_V2 << KVM_ARM_DEVICE_ID_SHIFT)  // 0.0
/*68 */                             | KVM_VGIC_V2_ADDR_TYPE_DIST);                       // 0.0
/*70 */     /* CPU interface for current core. Unlike arm_gic, we don't                  // 0.0
/*72 */      * provide the "interface for core #N" memory regions, because               // 0.0
/*74 */      * cores with a VGIC don't have those.                                       // 0.0
/*76 */      */                                                                          // 0.0
/*78 */     memory_region_init_reservation(&s->cpuiomem[0], OBJECT(s),                   // 0.0
/*80 */                                    "kvm-gic_cpu", 0x1000);                       // 0.0
/*82 */     sysbus_init_mmio(sbd, &s->cpuiomem[0]);                                      // 0.0
/*84 */     kvm_arm_register_device(&s->cpuiomem[0],                                     // 0.0
/*86 */                             (KVM_ARM_DEVICE_VGIC_V2 << KVM_ARM_DEVICE_ID_SHIFT)  // 0.0
/*88 */                             | KVM_VGIC_V2_ADDR_TYPE_CPU);                        // 0.0
/*90 */ }                                                                                // 0.0
