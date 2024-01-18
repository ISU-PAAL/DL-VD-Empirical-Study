// commit message qemu@5a2223ca26 (target=0, prob=0.17386626, correct=True): pcihp: reduce number of device check events
/*0 */ static void enable_device(AcpiPciHpState *s, unsigned bsel, int slot)  // (1) 0.3594
/*2 */ {                                                                      // (2) 0.01563
/*4 */     s->acpi_pcihp_pci_status[bsel].device_present |= (1U << slot);     // (0) 0.4844
/*6 */ }                                                                      // (3) 0.01562
