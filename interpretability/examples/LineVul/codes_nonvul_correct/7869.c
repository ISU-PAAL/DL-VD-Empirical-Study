// commit message qemu@37ad223c51 (target=0, prob=0.0109360395, correct=True): acpi: take oem_id in build_header(), optionally
/*0  */ build_dmar_q35(GArray *table_data, GArray *linker)                             // (10) 0.05316
/*2  */ {                                                                              // (16) 0.002532
/*4  */     int dmar_start = table_data->len;                                          // (12) 0.03797
/*8  */     AcpiTableDmar *dmar;                                                       // (15) 0.03038
/*10 */     AcpiDmarHardwareUnit *drhd;                                                // (13) 0.03291
/*14 */     dmar = acpi_data_push(table_data, sizeof(*dmar));                          // (7) 0.0557
/*16 */     dmar->host_address_width = VTD_HOST_ADDRESS_WIDTH - 1;                     // (5) 0.07089
/*18 */     dmar->flags = 0;    /* No intr_remap for now */                            // (8) 0.0557
/*22 */     /* DMAR Remapping Hardware Unit Definition structure */                    // (14) 0.03291
/*24 */     drhd = acpi_data_push(table_data, sizeof(*drhd));                          // (9) 0.0557
/*26 */     drhd->type = cpu_to_le16(ACPI_DMAR_TYPE_HARDWARE_UNIT);                    // (2) 0.07595
/*28 */     drhd->length = cpu_to_le16(sizeof(*drhd));   /* No device scope now */     // (3) 0.07342
/*30 */     drhd->flags = ACPI_DMAR_INCLUDE_PCI_ALL;                                   // (6) 0.05823
/*32 */     drhd->pci_segment = cpu_to_le16(0);                                        // (11) 0.05316
/*34 */     drhd->address = cpu_to_le64(Q35_HOST_BRIDGE_IOMMU_ADDR);                   // (1) 0.08101
/*38 */     build_header(linker, table_data, (void *)(table_data->data + dmar_start),  // (4) 0.07342
/*40 */                  "DMAR", table_data->len - dmar_start, 1, NULL);               // (0) 0.08861
/*42 */ }                                                                              // (17) 0.002532
