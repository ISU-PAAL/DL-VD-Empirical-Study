// commit message qemu@da98c8eb4c (target=0, prob=0.3042557, correct=True): suspend: switch acpi s3 to new infrastructure.
/*0  */ void acpi_pm1_cnt_write(ACPIREGS *ar, uint16_t val)                             // (4) 0.05882
/*2  */ {                                                                               // (20) 0.002353
/*4  */     ar->pm1.cnt.cnt = val & ~(ACPI_BITMASK_SLEEP_ENABLE);                       // (2) 0.07529
/*8  */     if (val & ACPI_BITMASK_SLEEP_ENABLE) {                                      // (9) 0.04941
/*10 */         /* change suspend type */                                               // (15) 0.02824
/*12 */         uint16_t sus_typ = (val >> 10) & 7;                                     // (6) 0.05412
/*14 */         switch(sus_typ) {                                                       // (11) 0.03529
/*16 */         case 0: /* soft power off */                                            // (12) 0.03529
/*18 */             qemu_system_shutdown_request();                                     // (7) 0.05176
/*20 */             break;                                                              // (13) 0.03059
/*22 */         case 1:                                                                 // (16) 0.02353
/*24 */             /* ACPI_BITMASK_WAKE_STATUS should be set on resume.                // (3) 0.06824
/*26 */                Pretend that resume was caused by power button */                // (5) 0.05647
/*28 */             ar->pm1.evt.sts |=                                                  // (8) 0.05176
/*30 */                 (ACPI_BITMASK_WAKE_STATUS | ACPI_BITMASK_POWER_BUTTON_STATUS);  // (0) 0.1035
/*32 */             qemu_system_reset_request();                                        // (10) 0.04941
/*34 */             qemu_irq_raise(ar->pm1.cnt.cmos_s3);                                // (1) 0.08
/*36 */         default:                                                                // (17) 0.02118
/*38 */             break;                                                              // (14) 0.03059
/*40 */         }                                                                       // (18) 0.01882
/*42 */     }                                                                           // (19) 0.009412
/*44 */ }                                                                               // (21) 0.002353
