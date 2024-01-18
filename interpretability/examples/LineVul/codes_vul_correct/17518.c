// commit message qemu@dbb7405d8c (target=1, prob=0.9990688, correct=True): xen-platform: Ensure xen is enabled when initializing
/*0  */ static int xen_platform_initfn(PCIDevice *dev)                                  // (7) 0.05178
/*1  */ {                                                                               // (15) 0.003236
/*2  */     PCIXenPlatformState *d = XEN_PLATFORM(dev);                                 // (5) 0.06472
/*3  */     uint8_t *pci_conf;                                                          // (11) 0.04207
/*4  */     pci_conf = dev->config;                                                     // (13) 0.0356
/*5  */     pci_set_word(pci_conf + PCI_COMMAND, PCI_COMMAND_IO | PCI_COMMAND_MEMORY);  // (0) 0.123
/*6  */     pci_config_set_prog_interface(pci_conf, 0);                                 // (4) 0.06796
/*7  */     pci_conf[PCI_INTERRUPT_PIN] = 1;                                            // (6) 0.06472
/*8  */     platform_ioport_bar_setup(d);                                               // (8) 0.04531
/*9  */     pci_register_bar(dev, 0, PCI_BASE_ADDRESS_SPACE_IO, &d->bar);               // (1) 0.1036
/*10 */     /* reserve 16MB mmio address for share memory*/                             // (9) 0.04531
/*11 */     platform_mmio_setup(d);                                                     // (12) 0.03883
/*12 */     pci_register_bar(dev, 1, PCI_BASE_ADDRESS_MEM_PREFETCH,                     // (2) 0.09709
/*13 */                      &d->mmio_bar);                                             // (3) 0.09061
/*14 */     platform_fixed_ioport_init(d);                                              // (10) 0.04531
/*15 */     return 0;                                                                   // (14) 0.01942
/*16 */ }                                                                               // (16) 0.003236
