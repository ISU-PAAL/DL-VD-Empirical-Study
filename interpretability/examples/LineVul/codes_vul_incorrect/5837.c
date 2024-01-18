// commit message qemu@ad5b88b1f1 (target=1, prob=0.029750966, correct=False): acpi-build: mark RAM dirty on table update
/*0  */ static void acpi_build_update(void *build_opaque, uint32_t offset)        // (2) 0.08462
/*2  */ {                                                                         // (14) 0.003846
/*4  */     AcpiBuildState *build_state = build_opaque;                           // (6) 0.06538
/*6  */     AcpiBuildTables tables;                                               // (11) 0.03846
/*10 */     /* No state to update or already patched? Nothing to do. */           // (7) 0.06538
/*12 */     if (!build_state || build_state->patched) {                           // (8) 0.06538
/*14 */         return;                                                           // (12) 0.03462
/*16 */     }                                                                     // (13) 0.01538
/*18 */     build_state->patched = 1;                                             // (10) 0.04615
/*22 */     acpi_build_tables_init(&tables);                                      // (9) 0.06154
/*26 */     acpi_build(build_state->guest_info, &tables);                         // (3) 0.08077
/*30 */     assert(acpi_data_len(tables.table_data) == build_state->table_size);  // (0) 0.1077
/*32 */     memcpy(build_state->table_ram, tables.table_data->data,               // (1) 0.08846
/*34 */            build_state->table_size);                                      // (5) 0.06923
/*38 */     acpi_build_tables_cleanup(&tables, true);                             // (4) 0.07308
/*40 */ }                                                                         // (15) 0.003846
