// commit message qemu@25f8e2f512 (target=0, prob=0.6193763, correct=False): ide/piix: convert to PCIDeviceInfo to initialize ids
/*0  */ static int pci_piix_ide_initfn(PCIIDEState *d)                                 // (4) 0.08716
/*2  */ {                                                                              // (9) 0.004587
/*4  */     uint8_t *pci_conf = d->dev.config;                                         // (5) 0.08716
/*8  */     pci_conf[PCI_CLASS_PROG] = 0x80; // legacy ATA mode                        // (3) 0.1147
/*10 */     pci_config_set_class(pci_conf, PCI_CLASS_STORAGE_IDE);                     // (2) 0.1193
/*14 */     qemu_register_reset(piix3_reset, d);                                       // (6) 0.08716
/*18 */     pci_register_bar(&d->dev, 4, 0x10, PCI_BASE_ADDRESS_SPACE_IO, bmdma_map);  // (0) 0.1789
/*22 */     vmstate_register(&d->dev.qdev, 0, &vmstate_ide_pci, d);                    // (1) 0.1284
/*26 */     pci_piix_init_ports(d);                                                    // (7) 0.06422
/*30 */     return 0;                                                                  // (8) 0.02752
/*32 */ }                                                                              // (10) 0.004587
