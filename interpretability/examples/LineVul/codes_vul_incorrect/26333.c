// commit message qemu@2886be1b01 (target=1, prob=0.07850461, correct=False): acpi: don't pass overflow_time to acpi_pm1_evt_get_sts
/*0  */ static void pm_update_sci(VT686PMState *s)                                        // (9) 0.04167
/*2  */ {                                                                                 // (12) 0.002778
/*4  */     int sci_level, pmsts;                                                         // (10) 0.03056
/*8  */     pmsts = acpi_pm1_evt_get_sts(&s->ar, s->ar.tmr.overflow_time);                // (2) 0.09722
/*10 */     sci_level = (((pmsts & s->ar.pm1.evt.en) &                                    // (8) 0.06944
/*12 */                   (ACPI_BITMASK_RT_CLOCK_ENABLE |                                 // (4) 0.09167
/*14 */                    ACPI_BITMASK_POWER_BUTTON_ENABLE |                             // (5) 0.09167
/*16 */                    ACPI_BITMASK_GLOBAL_LOCK_ENABLE |                              // (6) 0.09167
/*18 */                    ACPI_BITMASK_TIMER_ENABLE)) != 0);                             // (3) 0.09444
/*20 */     qemu_set_irq(s->dev.irq[0], sci_level);                                       // (7) 0.06944
/*22 */     /* schedule a timer interruption if needed */                                 // (11) 0.03056
/*24 */     acpi_pm_tmr_update(&s->ar, (s->ar.pm1.evt.en & ACPI_BITMASK_TIMER_ENABLE) &&  // (0) 0.1222
/*26 */                        !(pmsts & ACPI_BITMASK_TIMER_STATUS));                     // (1) 0.1111
/*28 */ }                                                                                 // (13) 0.002778
