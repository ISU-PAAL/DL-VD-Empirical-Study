// commit message qemu@80db0e7822 (target=0, prob=0.3930521, correct=True): memhp: don't generate memory hotplug AML if it's not enabled/supported
/*0  */ void ich9_pm_init(PCIDevice *lpc_pci, ICH9LPCPMRegs *pm,                          // (8) 0.06055
/*2  */                   bool smm_enabled,                                               // (12) 0.04492
/*4  */                   qemu_irq sci_irq)                                               // (9) 0.05469
/*6  */ {                                                                                 // (14) 0.001953
/*8  */     memory_region_init(&pm->io, OBJECT(lpc_pci), "ich9-pm", ICH9_PMIO_SIZE);      // (6) 0.07227
/*10 */     memory_region_set_enabled(&pm->io, false);                                    // (13) 0.0332
/*12 */     memory_region_add_subregion(pci_address_space_io(lpc_pci),                    // (11) 0.05273
/*14 */                                 0, &pm->io);                                      // (3) 0.07422
/*18 */     acpi_pm_tmr_init(&pm->acpi_regs, ich9_pm_update_sci_fn, &pm->io);             // (4) 0.07422
/*20 */     acpi_pm1_evt_init(&pm->acpi_regs, ich9_pm_update_sci_fn, &pm->io);            // (2) 0.07617
/*22 */     acpi_pm1_cnt_init(&pm->acpi_regs, &pm->io, pm->disable_s3, pm->disable_s4,    // (1) 0.08008
/*24 */                       pm->s4_val);                                                // (10) 0.05469
/*28 */     acpi_gpe_init(&pm->acpi_regs, ICH9_PMIO_GPE0_LEN);                            // (7) 0.06445
/*30 */     memory_region_init_io(&pm->io_gpe, OBJECT(lpc_pci), &ich9_gpe_ops, pm,        // (5) 0.07422
/*32 */                           "acpi-gpe0", ICH9_PMIO_GPE0_LEN);                       // (0) 0.0918
/*34 */     memory_region_add_subregion(&pm->io, ICH9_PMIO_GPE0_STS, &pm->io_gpe);        // 0.0
/*38 */     memory_region_init_io(&pm->io_smi, OBJECT(lpc_pci), &ich9_smi_ops, pm,        // 0.0
/*40 */                           "acpi-smi", 8);                                         // 0.0
/*42 */     memory_region_add_subregion(&pm->io, ICH9_PMIO_SMI_EN, &pm->io_smi);          // 0.0
/*46 */     pm->smm_enabled = smm_enabled;                                                // 0.0
/*50 */     pm->enable_tco = true;                                                        // 0.0
/*52 */     acpi_pm_tco_init(&pm->tco_regs, &pm->io);                                     // 0.0
/*56 */     pm->irq = sci_irq;                                                            // 0.0
/*58 */     qemu_register_reset(pm_reset, pm);                                            // 0.0
/*60 */     pm->powerdown_notifier.notify = pm_powerdown_req;                             // 0.0
/*62 */     qemu_register_powerdown_notifier(&pm->powerdown_notifier);                    // 0.0
/*66 */     legacy_acpi_cpu_hotplug_init(pci_address_space_io(lpc_pci),                   // 0.0
/*68 */         OBJECT(lpc_pci), &pm->gpe_cpu, ICH9_CPU_HOTPLUG_IO_BASE);                 // 0.0
/*72 */     if (pm->acpi_memory_hotplug.is_enabled) {                                     // 0.0
/*74 */         acpi_memory_hotplug_init(pci_address_space_io(lpc_pci), OBJECT(lpc_pci),  // 0.0
/*76 */                                  &pm->acpi_memory_hotplug);                       // 0.0
/*78 */     }                                                                             // 0.0
/*80 */ }                                                                                 // 0.0
