// commit message qemu@fb506e701e (target=1, prob=0.070318565, correct=False): intel_iommu: reject broken EIM
/*0  */ static bool vtd_decide_config(IntelIOMMUState *s, Error **errp)                  // (10) 0.05251
/*2  */ {                                                                                // (18) 0.002283
/*4  */     X86IOMMUState *x86_iommu = X86_IOMMU_DEVICE(s);                              // (4) 0.06621
/*8  */     /* Currently Intel IOMMU IR only support "kernel-irqchip={off|split}" */     // (8) 0.05479
/*10 */     if (x86_iommu->intr_supported && kvm_irqchip_in_kernel() &&                  // (5) 0.06621
/*12 */         !kvm_irqchip_is_split()) {                                               // (11) 0.04566
/*14 */         error_setg(errp, "Intel Interrupt Remapping cannot work with "           // (7) 0.05708
/*16 */                          "kernel-irqchip=on, please use 'split|off'.");          // (1) 0.09361
/*18 */         return false;                                                            // (12) 0.02283
/*20 */     }                                                                            // (15) 0.009132
/*22 */     if (s->intr_eim == ON_OFF_AUTO_ON && !x86_iommu->intr_supported) {           // (2) 0.08219
/*24 */         error_setg(errp, "eim=on cannot be selected without intremap=on");       // (3) 0.06849
/*26 */         return false;                                                            // (13) 0.02283
/*28 */     }                                                                            // (16) 0.009132
/*32 */     if (s->intr_eim == ON_OFF_AUTO_AUTO) {                                       // (9) 0.05479
/*34 */         s->intr_eim = x86_iommu->intr_supported ?                                // (6) 0.06164
/*36 */                                               ON_OFF_AUTO_ON : ON_OFF_AUTO_OFF;  // (0) 0.1438
/*38 */     }                                                                            // (17) 0.009132
/*42 */     return true;                                                                 // (14) 0.0137
/*44 */ }                                                                                // (19) 0.002283
