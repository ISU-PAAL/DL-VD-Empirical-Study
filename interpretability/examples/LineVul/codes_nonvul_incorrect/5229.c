// commit message qemu@9a10bbb4e8 (target=0, prob=0.50393194, correct=False): hw/acpi: acpi_pm1_cnt_init(): take "disable_s3" and "disable_s4"
/*0  */ void ich9_pm_init(PCIDevice *lpc_pci, ICH9LPCPMRegs *pm,                          // (10) 0.06055
/*2  */                   qemu_irq sci_irq)                                               // (11) 0.05469
/*4  */ {                                                                                 // (14) 0.001953
/*6  */     memory_region_init(&pm->io, OBJECT(lpc_pci), "ich9-pm", ICH9_PMIO_SIZE);      // (7) 0.07227
/*8  */     memory_region_set_enabled(&pm->io, false);                                    // (13) 0.0332
/*10 */     memory_region_add_subregion(pci_address_space_io(lpc_pci),                    // (12) 0.05273
/*12 */                                 0, &pm->io);                                      // (2) 0.07422
/*16 */     acpi_pm_tmr_init(&pm->acpi_regs, ich9_pm_update_sci_fn, &pm->io);             // (3) 0.07422
/*18 */     acpi_pm1_evt_init(&pm->acpi_regs, ich9_pm_update_sci_fn, &pm->io);            // (1) 0.07617
/*20 */     acpi_pm1_cnt_init(&pm->acpi_regs, &pm->io, pm->s4_val);                       // (8) 0.06641
/*24 */     acpi_gpe_init(&pm->acpi_regs, ICH9_PMIO_GPE0_LEN);                            // (9) 0.06445
/*26 */     memory_region_init_io(&pm->io_gpe, OBJECT(lpc_pci), &ich9_gpe_ops, pm,        // (4) 0.07422
/*28 */                           "acpi-gpe0", ICH9_PMIO_GPE0_LEN);                       // (0) 0.0918
/*30 */     memory_region_add_subregion(&pm->io, ICH9_PMIO_GPE0_STS, &pm->io_gpe);        // (5) 0.07422
/*34 */     memory_region_init_io(&pm->io_smi, OBJECT(lpc_pci), &ich9_smi_ops, pm,        // (6) 0.07422
/*36 */                           "acpi-smi", 8);                                         // 0.0
/*38 */     memory_region_add_subregion(&pm->io, ICH9_PMIO_SMI_EN, &pm->io_smi);          // 0.0
/*42 */     pm->irq = sci_irq;                                                            // 0.0
/*44 */     qemu_register_reset(pm_reset, pm);                                            // 0.0
/*46 */     pm->powerdown_notifier.notify = pm_powerdown_req;                             // 0.0
/*48 */     qemu_register_powerdown_notifier(&pm->powerdown_notifier);                    // 0.0
/*52 */     acpi_cpu_hotplug_init(pci_address_space_io(lpc_pci), OBJECT(lpc_pci),         // 0.0
/*54 */                           &pm->gpe_cpu, ICH9_CPU_HOTPLUG_IO_BASE);                // 0.0
/*58 */     if (pm->acpi_memory_hotplug.is_enabled) {                                     // 0.0
/*60 */         acpi_memory_hotplug_init(pci_address_space_io(lpc_pci), OBJECT(lpc_pci),  // 0.0
/*62 */                                  &pm->acpi_memory_hotplug);                       // 0.0
/*64 */     }                                                                             // 0.0
/*66 */ }                                                                                 // 0.0
