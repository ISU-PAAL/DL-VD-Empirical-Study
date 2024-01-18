// commit message qemu@37ad223c51 (target=0, prob=0.009560646, correct=True): acpi: take oem_id in build_header(), optionally
/*0  */ build_hpet(GArray *table_data, GArray *linker)                                  // (5) 0.08867
/*2  */ {                                                                               // (10) 0.004926
/*4  */     Acpi20Hpet *hpet;                                                           // (7) 0.05911
/*8  */     hpet = acpi_data_push(table_data, sizeof(*hpet));                           // (3) 0.1084
/*10 */     /* Note timer_block_id value must be kept in sync with value advertised by  // (4) 0.09852
/*12 */      * emulated hpet                                                            // (8) 0.04433
/*14 */      */                                                                         // (9) 0.02463
/*16 */     hpet->timer_block_id = cpu_to_le32(0x8086a201);                             // (1) 0.1281
/*18 */     hpet->addr.address = cpu_to_le64(HPET_BASE);                                // (2) 0.1133
/*20 */     build_header(linker, table_data,                                            // (6) 0.06897
/*22 */                  (void *)hpet, "HPET", sizeof(*hpet), 1, NULL);                 // (0) 0.1724
/*24 */ }                                                                               // (11) 0.004926
