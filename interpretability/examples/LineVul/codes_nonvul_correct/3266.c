// commit message qemu@99fd437dee (target=0, prob=0.2112228, correct=True): acpi-build: enable hotplug for PCI bridges
/*0  */ static void patch_pcihp(int slot, uint8_t *ssdt_ptr, uint32_t eject)  // (4) 0.08738
/*2  */ {                                                                     // (14) 0.003236
/*4  */     ssdt_ptr[ACPI_PCIHP_OFFSET_HEX] = acpi_get_hex(slot >> 4);        // (1) 0.11
/*6  */     ssdt_ptr[ACPI_PCIHP_OFFSET_HEX + 1] = acpi_get_hex(slot);         // (2) 0.11
/*8  */     ssdt_ptr[ACPI_PCIHP_OFFSET_ID] = slot;                            // (6) 0.07767
/*10 */     ssdt_ptr[ACPI_PCIHP_OFFSET_ADR + 2] = slot;                       // (5) 0.08738
/*14 */     /* Runtime patching of ACPI_EJ0: to disable hotplug for a slot,   // (7) 0.0712
/*16 */      * replace the method name: _EJ0 by ACPI_EJ0_.                    // (8) 0.06796
/*18 */      */                                                               // (11) 0.01618
/*20 */     /* Sanity check */                                                // (10) 0.02589
/*22 */     assert(!memcmp(ssdt_ptr + ACPI_PCIHP_OFFSET_EJ0, "_EJ0", 4));     // (3) 0.11
/*26 */     if (!eject) {                                                     // (9) 0.02913
/*28 */         memcpy(ssdt_ptr + ACPI_PCIHP_OFFSET_EJ0, "EJ0_", 4);          // (0) 0.1197
/*30 */     }                                                                 // (12) 0.01294
/*32 */ }                                                                     // (13) 0.003236
