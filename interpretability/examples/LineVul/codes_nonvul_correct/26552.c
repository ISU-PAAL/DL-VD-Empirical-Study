// commit message qemu@e4f308bbf9 (target=0, prob=0.13122575, correct=True): acpi: piix4: remove not needed GPE0 mask
/*0  */ static void pm_update_sci(PIIX4PMState *s)                                        // (11) 0.03981
/*2  */ {                                                                                 // (14) 0.002342
/*4  */     int sci_level, pmsts;                                                         // (12) 0.02576
/*8  */     pmsts = acpi_pm1_evt_get_sts(&s->ar);                                         // (9) 0.05386
/*10 */     sci_level = (((pmsts & s->ar.pm1.evt.en) &                                    // (8) 0.05855
/*12 */                   (ACPI_BITMASK_RT_CLOCK_ENABLE |                                 // (4) 0.07728
/*14 */                    ACPI_BITMASK_POWER_BUTTON_ENABLE |                             // (5) 0.07728
/*16 */                    ACPI_BITMASK_GLOBAL_LOCK_ENABLE |                              // (6) 0.07728
/*18 */                    ACPI_BITMASK_TIMER_ENABLE)) != 0) ||                           // (3) 0.08197
/*20 */         (((s->ar.gpe.sts[0] & s->ar.gpe.en[0]) &                                  // (7) 0.07728
/*22 */           (PIIX4_PCI_HOTPLUG_STATUS | PIIX4_CPU_HOTPLUG_STATUS)) != 0);           // (0) 0.103
/*26 */     qemu_set_irq(s->irq, sci_level);                                              // (10) 0.04918
/*28 */     /* schedule a timer interruption if needed */                                 // (13) 0.02576
/*30 */     acpi_pm_tmr_update(&s->ar, (s->ar.pm1.evt.en & ACPI_BITMASK_TIMER_ENABLE) &&  // (1) 0.103
/*32 */                        !(pmsts & ACPI_BITMASK_TIMER_STATUS));                     // (2) 0.09368
/*34 */ }                                                                                 // (15) 0.002342
