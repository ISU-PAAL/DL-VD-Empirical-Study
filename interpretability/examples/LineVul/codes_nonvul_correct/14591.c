// commit message qemu@67113c0342 (target=0, prob=0.2553718, correct=True): e500: fix pci host bridge class/type
/*0  */ static void e500_pcihost_bridge_realize(PCIDevice *d, Error **errp)                       // (7) 0.07163
/*2  */ {                                                                                         // (11) 0.002755
/*4  */     PPCE500PCIBridgeState *b = PPC_E500_PCI_BRIDGE(d);                                    // (5) 0.07713
/*6  */     PPCE500CCSRState *ccsr = CCSR(container_get(qdev_get_machine(),                       // (6) 0.07713
/*8  */                                   "/e500-ccsr"));                                         // (2) 0.1129
/*12 */     pci_config_set_class(d->config, PCI_CLASS_BRIDGE_PCI);                                // (8) 0.07163
/*14 */     d->config[PCI_HEADER_TYPE] =                                                          // (10) 0.04408
/*16 */         (d->config[PCI_HEADER_TYPE] & PCI_HEADER_TYPE_MULTI_FUNCTION) |                   // (3) 0.1019
/*18 */         PCI_HEADER_TYPE_BRIDGE;                                                           // (9) 0.04959
/*22 */     memory_region_init_alias(&b->bar0, OBJECT(ccsr), "e500-pci-bar0", &ccsr->ccsr_space,  // (1) 0.1129
/*24 */                              0, int128_get64(ccsr->ccsr_space.size));                     // (0) 0.1267
/*26 */     pci_register_bar(d, 0, PCI_BASE_ADDRESS_SPACE_MEMORY, &b->bar0);                      // (4) 0.09642
/*28 */ }                                                                                         // (12) 0.002755
