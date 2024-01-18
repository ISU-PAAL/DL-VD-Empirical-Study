// commit message qemu@ff5ce21e1b (target=1, prob=0.0063359253, correct=False): acpi: change TPM TIS data conditions
/*0  */ build_tpm2(GArray *table_data, BIOSLinker *linker)                             // (5) 0.08696
/*2  */ {                                                                              // (8) 0.004348
/*4  */     Acpi20TPM2 *tpm2_ptr;                                                      // (6) 0.06957
/*8  */     tpm2_ptr = acpi_data_push(table_data, sizeof *tpm2_ptr);                   // (3) 0.1217
/*12 */     tpm2_ptr->platform_class = cpu_to_le16(TPM2_ACPI_CLASS_CLIENT);            // (2) 0.1391
/*14 */     tpm2_ptr->control_area_address = cpu_to_le64(0);                           // (4) 0.1043
/*16 */     tpm2_ptr->start_method = cpu_to_le32(TPM2_START_METHOD_MMIO);              // (1) 0.1435
/*20 */     build_header(linker, table_data,                                           // (7) 0.06087
/*22 */                  (void *)tpm2_ptr, "TPM2", sizeof(*tpm2_ptr), 4, NULL, NULL);  // (0) 0.1913
/*24 */ }                                                                              // (9) 0.004348
