// commit message qemu@2231f69b4e (target=0, prob=0.114675924, correct=True): hw/arm/virt: no ITS on older machine types
/*0   */ build_madt(GArray *table_data, BIOSLinker *linker, VirtGuestInfo *guest_info)  // (2) 0.05469
/*2   */ {                                                                              // (21) 0.001953
/*4   */     int madt_start = table_data->len;                                          // (17) 0.0293
/*6   */     const MemMapEntry *memmap = guest_info->memmap;                            // (12) 0.03516
/*8   */     const int *irqmap = guest_info->irqmap;                                    // (13) 0.03516
/*10  */     AcpiMultipleApicTable *madt;                                               // (19) 0.02539
/*12  */     AcpiMadtGenericDistributor *gicd;                                          // (16) 0.03125
/*14  */     AcpiMadtGenericMsiFrame *gic_msi;                                          // (11) 0.03516
/*16  */     int i;                                                                     // (20) 0.01172
/*20  */     madt = acpi_data_push(table_data, sizeof *madt);                           // (9) 0.04297
/*24  */     gicd = acpi_data_push(table_data, sizeof *gicd);                           // (8) 0.04687
/*26  */     gicd->type = ACPI_APIC_GENERIC_DISTRIBUTOR;                                // (7) 0.04687
/*28  */     gicd->length = sizeof(*gicd);                                              // (18) 0.0293
/*30  */     gicd->base_address = memmap[VIRT_GIC_DIST].base;                           // (5) 0.04883
/*32  */     gicd->version = guest_info->gic_version;                                   // (14) 0.03516
/*36  */     for (i = 0; i < guest_info->smp_cpus; i++) {                               // (6) 0.04687
/*38  */         AcpiMadtGenericInterrupt *gicc = acpi_data_push(table_data,            // (1) 0.05664
/*40  */                                                      sizeof *gicc);            // (0) 0.1113
/*42  */         ARMCPU *armcpu = ARM_CPU(qemu_get_cpu(i));                             // (3) 0.05469
/*46  */         gicc->type = ACPI_APIC_GENERIC_INTERRUPT;                              // (4) 0.05078
/*48  */         gicc->length = sizeof(*gicc);                                          // (15) 0.0332
/*50  */         if (guest_info->gic_version == 2) {                                    // (10) 0.04297
/*52  */             gicc->base_address = memmap[VIRT_GIC_CPU].base;                    // 0.0
/*54  */         }                                                                      // 0.0
/*56  */         gicc->cpu_interface_number = i;                                        // 0.0
/*58  */         gicc->arm_mpidr = armcpu->mp_affinity;                                 // 0.0
/*60  */         gicc->uid = i;                                                         // 0.0
/*62  */         gicc->flags = cpu_to_le32(ACPI_GICC_ENABLED);                          // 0.0
/*66  */         if (armcpu->has_pmu) {                                                 // 0.0
/*68  */             gicc->performance_interrupt = cpu_to_le32(PPI(VIRTUAL_PMU_IRQ));   // 0.0
/*70  */         }                                                                      // 0.0
/*72  */     }                                                                          // 0.0
/*76  */     if (guest_info->gic_version == 3) {                                        // 0.0
/*78  */         AcpiMadtGenericTranslator *gic_its;                                    // 0.0
/*80  */         AcpiMadtGenericRedistributor *gicr = acpi_data_push(table_data,        // 0.0
/*82  */                                                          sizeof *gicr);        // 0.0
/*86  */         gicr->type = ACPI_APIC_GENERIC_REDISTRIBUTOR;                          // 0.0
/*88  */         gicr->length = sizeof(*gicr);                                          // 0.0
/*90  */         gicr->base_address = cpu_to_le64(memmap[VIRT_GIC_REDIST].base);        // 0.0
/*92  */         gicr->range_length = cpu_to_le32(memmap[VIRT_GIC_REDIST].size);        // 0.0
/*96  */         if (its_class_name()) {                                                // 0.0
/*98  */             gic_its = acpi_data_push(table_data, sizeof *gic_its);             // 0.0
/*100 */             gic_its->type = ACPI_APIC_GENERIC_TRANSLATOR;                      // 0.0
/*102 */             gic_its->length = sizeof(*gic_its);                                // 0.0
/*104 */             gic_its->translation_id = 0;                                       // 0.0
/*106 */             gic_its->base_address = cpu_to_le64(memmap[VIRT_GIC_ITS].base);    // 0.0
/*108 */         }                                                                      // 0.0
/*110 */     } else {                                                                   // 0.0
/*112 */         gic_msi = acpi_data_push(table_data, sizeof *gic_msi);                 // 0.0
/*114 */         gic_msi->type = ACPI_APIC_GENERIC_MSI_FRAME;                           // 0.0
/*116 */         gic_msi->length = sizeof(*gic_msi);                                    // 0.0
/*118 */         gic_msi->gic_msi_frame_id = 0;                                         // 0.0
/*120 */         gic_msi->base_address = cpu_to_le64(memmap[VIRT_GIC_V2M].base);        // 0.0
/*122 */         gic_msi->flags = cpu_to_le32(1);                                       // 0.0
/*124 */         gic_msi->spi_count = cpu_to_le16(NUM_GICV2M_SPIS);                     // 0.0
/*126 */         gic_msi->spi_base = cpu_to_le16(irqmap[VIRT_GIC_V2M] + ARM_SPI_BASE);  // 0.0
/*128 */     }                                                                          // 0.0
/*132 */     build_header(linker, table_data,                                           // 0.0
/*134 */                  (void *)(table_data->data + madt_start), "APIC",              // 0.0
/*136 */                  table_data->len - madt_start, 3, NULL, NULL);                 // 0.0
/*138 */ }                                                                              // 0.0
