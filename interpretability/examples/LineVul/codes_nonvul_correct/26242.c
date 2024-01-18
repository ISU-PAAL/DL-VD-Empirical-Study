// commit message qemu@b8eb5512fd (target=0, prob=0.08627572, correct=True): target-i386: disable LINT0 after reset
/*0  */ static void apic_reset_common(DeviceState *dev)                              // (10) 0.04255
/*2  */ {                                                                            // (19) 0.00304
/*4  */     APICCommonState *s = APIC_COMMON(dev);                                   // (6) 0.05471
/*6  */     APICCommonClass *info = APIC_COMMON_GET_CLASS(s);                        // (4) 0.06687
/*8  */     bool bsp;                                                                // (16) 0.02128
/*12 */     bsp = cpu_is_bsp(s->cpu);                                                // (8) 0.04863
/*14 */     s->apicbase = APIC_DEFAULT_ADDRESS |                                     // (5) 0.05775
/*16 */         (bsp ? MSR_IA32_APICBASE_BSP : 0) | MSR_IA32_APICBASE_ENABLE;        // (0) 0.1246
/*20 */     s->vapic_paddr = 0;                                                      // (11) 0.04255
/*22 */     info->vapic_base_update(s);                                              // (9) 0.04559
/*26 */     apic_init_reset(dev);                                                    // (12) 0.03647
/*30 */     if (bsp) {                                                               // (14) 0.02432
/*32 */         /*                                                                   // (15) 0.02432
/*34 */          * LINT0 delivery mode on CPU #0 is set to ExtInt at initialization  // (2) 0.07599
/*36 */          * time typically by BIOS, so PIC interrupt can be delivered to the  // (3) 0.06991
/*38 */          * processor when local APIC is enabled.                             // (7) 0.05167
/*40 */          */                                                                  // (13) 0.02736
/*42 */         s->lvt[APIC_LVT_LINT0] = 0x700;                                      // (1) 0.08207
/*44 */     }                                                                        // (17) 0.01216
/*46 */ }                                                                            // (18) 0.00304
