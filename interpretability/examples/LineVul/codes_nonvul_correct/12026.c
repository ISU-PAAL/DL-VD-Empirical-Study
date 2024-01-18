// commit message qemu@77af8a2b95 (target=0, prob=0.026893029, correct=True): hw/i386: Use Rev3 FADT (ACPI 2.0) instead of Rev1 to improve guest OS support.
/*0  */ static void fadt_setup(AcpiFadtDescriptorRev1 *fadt, AcpiPmInfo *pm)            // (2) 0.06055
/*2  */ {                                                                               // (19) 0.001953
/*4  */     fadt->model = 1;                                                            // (18) 0.02148
/*6  */     fadt->reserved1 = 0;                                                        // (17) 0.02539
/*8  */     fadt->sci_int = cpu_to_le16(pm->sci_int);                                   // (10) 0.04687
/*10 */     fadt->smi_cmd = cpu_to_le32(ACPI_PORT_SMI_CMD);                             // (5) 0.05859
/*12 */     fadt->acpi_enable = pm->acpi_enable_cmd;                                    // (13) 0.04102
/*14 */     fadt->acpi_disable = pm->acpi_disable_cmd;                                  // (12) 0.04102
/*16 */     /* EVT, CNT, TMR offset matches hw/acpi/core.c */                           // (9) 0.04688
/*18 */     fadt->pm1a_evt_blk = cpu_to_le32(pm->io_base);                              // (6) 0.05859
/*20 */     fadt->pm1a_cnt_blk = cpu_to_le32(pm->io_base + 0x04);                       // (0) 0.06641
/*22 */     fadt->pm_tmr_blk = cpu_to_le32(pm->io_base + 0x08);                         // (1) 0.0625
/*24 */     fadt->gpe0_blk = cpu_to_le32(pm->gpe0_blk);                                 // (7) 0.05859
/*26 */     /* EVT, CNT, TMR length matches hw/acpi/core.c */                           // (11) 0.04687
/*28 */     fadt->pm1_evt_len = 4;                                                      // (14) 0.0332
/*30 */     fadt->pm1_cnt_len = 2;                                                      // (15) 0.0332
/*32 */     fadt->pm_tmr_len = 4;                                                       // (16) 0.03125
/*34 */     fadt->gpe0_blk_len = pm->gpe0_blk_len;                                      // (8) 0.05273
/*36 */     fadt->plvl2_lat = cpu_to_le16(0xfff); /* C2 state not supported */          // (3) 0.06055
/*38 */     fadt->plvl3_lat = cpu_to_le16(0xfff); /* C3 state not supported */          // (4) 0.06055
/*40 */     fadt->flags = cpu_to_le32((1 << ACPI_FADT_F_WBINVD) |                       // 0.0
/*42 */                               (1 << ACPI_FADT_F_PROC_C1) |                      // 0.0
/*44 */                               (1 << ACPI_FADT_F_SLP_BUTTON) |                   // 0.0
/*46 */                               (1 << ACPI_FADT_F_RTC_S4));                       // 0.0
/*48 */     fadt->flags |= cpu_to_le32(1 << ACPI_FADT_F_USE_PLATFORM_CLOCK);            // 0.0
/*50 */     /* APIC destination mode ("Flat Logical") has an upper limit of 8 CPUs      // 0.0
/*52 */      * For more than 8 CPUs, "Clustered Logical" mode has to be used            // 0.0
/*54 */      */                                                                         // 0.0
/*56 */     if (max_cpus > 8) {                                                         // 0.0
/*58 */         fadt->flags |= cpu_to_le32(1 << ACPI_FADT_F_FORCE_APIC_CLUSTER_MODEL);  // 0.0
/*60 */     }                                                                           // 0.0
/*62 */     fadt->century = RTC_CENTURY;                                                // 0.0
/*64 */ }                                                                               // 0.0
