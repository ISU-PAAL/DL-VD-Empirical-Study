// commit message qemu@37ad223c51 (target=0, prob=0.020439854, correct=True): acpi: take oem_id in build_header(), optionally
/*0  */ build_header(GArray *linker, GArray *table_data,                                  // (11) 0.0364
/*2  */              AcpiTableHeader *h, const char *sig, int len, uint8_t rev,           // (2) 0.07281
/*4  */              const char *oem_table_id)                                            // (9) 0.04711
/*6  */ {                                                                                 // (20) 0.002141
/*8  */     memcpy(&h->signature, sig, 4);                                                // (12) 0.03426
/*10 */     h->length = cpu_to_le32(len);                                                 // (13) 0.03426
/*12 */     h->revision = rev;                                                            // (16) 0.02141
/*14 */     memcpy(h->oem_id, ACPI_BUILD_APPNAME6, 6);                                    // (6) 0.05567
/*18 */     if (oem_table_id) {                                                           // (15) 0.02784
/*20 */         strncpy((char *)h->oem_table_id, oem_table_id, sizeof(h->oem_table_id));  // (1) 0.08565
/*22 */     } else {                                                                      // (18) 0.01285
/*24 */         memcpy(h->oem_table_id, ACPI_BUILD_APPNAME4, 4);                          // (3) 0.06852
/*26 */         memcpy(h->oem_table_id + 4, sig, 4);                                      // (7) 0.05567
/*28 */     }                                                                             // (19) 0.008565
/*32 */     h->oem_revision = cpu_to_le32(1);                                             // (10) 0.04283
/*34 */     memcpy(h->asl_compiler_id, ACPI_BUILD_APPNAME4, 4);                           // (4) 0.0621
/*36 */     h->asl_compiler_revision = cpu_to_le32(1);                                    // (8) 0.04925
/*38 */     h->checksum = 0;                                                              // (17) 0.02141
/*40 */     /* Checksum to be filled in by Guest linker */                                // (14) 0.03212
/*42 */     bios_linker_loader_add_checksum(linker, ACPI_BUILD_TABLE_FILE,                // (5) 0.05782
/*44 */                                     table_data->data, h, len, &h->checksum);      // (0) 0.1092
/*46 */ }                                                                                 // (21) 0.002141
