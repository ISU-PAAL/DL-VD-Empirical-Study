// commit message qemu@de00982e9e (target=0, prob=0.048950974, correct=True): xen-platform: convert to memory API
/*0  */ static int xen_platform_initfn(PCIDevice *dev)                                  // (8) 0.04863
/*2  */ {                                                                               // (15) 0.00304
/*4  */     PCIXenPlatformState *d = DO_UPCAST(PCIXenPlatformState, pci_dev, dev);      // (3) 0.08815
/*6  */     uint8_t *pci_conf;                                                          // (12) 0.03951
/*10 */     pci_conf = d->pci_dev.config;                                               // (9) 0.04863
/*14 */     pci_set_word(pci_conf + PCI_COMMAND, PCI_COMMAND_IO | PCI_COMMAND_MEMORY);  // (0) 0.1155
/*18 */     pci_config_set_prog_interface(pci_conf, 0);                                 // (6) 0.06383
/*22 */     pci_conf[PCI_INTERRUPT_PIN] = 1;                                            // (7) 0.06079
/*26 */     pci_register_bar(&d->pci_dev, 0, 0x100,                                     // (5) 0.06687
/*28 */             PCI_BASE_ADDRESS_SPACE_IO, platform_ioport_map);                    // (2) 0.09726
/*32 */     /* reserve 16MB mmio address for share memory*/                             // (11) 0.04255
/*34 */     pci_register_bar(&d->pci_dev, 1, 0x1000000,                                 // (4) 0.06991
/*36 */             PCI_BASE_ADDRESS_MEM_PREFETCH, platform_mmio_map);                  // (1) 0.1064
/*40 */     platform_fixed_ioport_init(d);                                              // (10) 0.04255
/*44 */     return 0;                                                                   // (13) 0.01824
/*46 */ }                                                                               // (14) 0.00304
