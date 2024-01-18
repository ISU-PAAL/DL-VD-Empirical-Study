// commit message qemu@146beee5d9 (target=0, prob=0.018294912, correct=True): hw/piix4.c: convert to PCIDeviceInfo to initialize ids
/*0  */ static int piix4_initfn(PCIDevice *dev)                                                                          // (6) 0.06226
/*2  */ {                                                                                                                // (11) 0.003891
/*4  */     PIIX4State *d = DO_UPCAST(PIIX4State, dev, dev);                                                             // (2) 0.1051
/*6  */     uint8_t *pci_conf;                                                                                           // (8) 0.05058
/*10 */     isa_bus_new(&d->dev.qdev);                                                                                   // (5) 0.06615
/*14 */     pci_conf = d->dev.config;                                                                                    // (9) 0.05058
/*16 */     pci_config_set_vendor_id(pci_conf, PCI_VENDOR_ID_INTEL);                                                     // (1) 0.1167
/*18 */     pci_config_set_device_id(pci_conf, PCI_DEVICE_ID_INTEL_82371AB_0); // 82371AB/EB/MB PIIX4 PCI-to-ISA bridge  // (0) 0.2101
/*20 */     pci_config_set_class(pci_conf, PCI_CLASS_BRIDGE_ISA);                                                        // (3) 0.1012
/*24 */     piix4_dev = &d->dev;                                                                                         // (7) 0.05447
/*26 */     qemu_register_reset(piix4_reset, d);                                                                         // (4) 0.07393
/*28 */     return 0;                                                                                                    // (10) 0.02335
/*30 */ }                                                                                                                // (12) 0.003891
