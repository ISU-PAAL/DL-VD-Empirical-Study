// commit message qemu@5a2223ca26 (target=0, prob=0.15959662, correct=True): pcihp: reduce number of device check events
/*0  */ int acpi_pcihp_device_hotplug(AcpiPciHpState *s, PCIDevice *dev,              // (2) 0.08451
/*2  */                               PCIHotplugState state)                          // (0) 0.09859
/*4  */ {                                                                             // (20) 0.002817
/*6  */     int slot = PCI_SLOT(dev->devfn);                                          // (10) 0.04507
/*8  */     int bsel = acpi_pcihp_get_bsel(dev->bus);                                 // (3) 0.06479
/*10 */     if (bsel < 0) {                                                           // (12) 0.03099
/*12 */         return -1;                                                            // (13) 0.03099
/*14 */     }                                                                         // (17) 0.01127
/*18 */     /* Don't send event when device is enabled during qemu machine creation:  // (5) 0.05352
/*20 */      * it is present on boot, no hotplug event is necessary. We do send an    // (4) 0.06197
/*22 */      * event when the device is disabled later. */                            // (11) 0.03944
/*24 */     if (state == PCI_COLDPLUG_ENABLED) {                                      // (6) 0.05352
/*26 */         s->acpi_pcihp_pci_status[bsel].device_present |= (1U << slot);        // (1) 0.09859
/*28 */         return 0;                                                             // (14) 0.02817
/*30 */     }                                                                         // (18) 0.01127
/*34 */     if (state == PCI_HOTPLUG_ENABLED) {                                       // (7) 0.05352
/*36 */         enable_device(s, bsel, slot);                                         // (8) 0.0507
/*38 */     } else {                                                                  // (15) 0.0169
/*40 */         disable_device(s, bsel, slot);                                        // (9) 0.0507
/*42 */     }                                                                         // (19) 0.01127
/*46 */     return 0;                                                                 // (16) 0.0169
/*48 */ }                                                                             // (21) 0.002817
