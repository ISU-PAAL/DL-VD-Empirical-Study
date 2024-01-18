// commit message qemu@0208def1ca (target=1, prob=0.044879973, correct=False): pci/bridge: fix pci_bridge_reset()
/*0  */ void pci_bridge_reset_reg(PCIDevice *dev)            // (12) 0.04805
/*2  */ {                                                    // (16) 0.003003
/*4  */     uint8_t *conf = dev->config;                     // (14) 0.04204
/*8  */     conf[PCI_PRIMARY_BUS] = 0;                       // (9) 0.05105
/*10 */     conf[PCI_SECONDARY_BUS] = 0;                     // (10) 0.05105
/*12 */     conf[PCI_SUBORDINATE_BUS] = 0;                   // (8) 0.05706
/*14 */     conf[PCI_SEC_LATENCY_TIMER] = 0;                 // (7) 0.06306
/*18 */     conf[PCI_IO_BASE] = 0;                           // (13) 0.04805
/*20 */     conf[PCI_IO_LIMIT] = 0;                          // (11) 0.05105
/*22 */     pci_set_word(conf + PCI_MEMORY_BASE, 0);         // (6) 0.06607
/*24 */     pci_set_word(conf + PCI_MEMORY_LIMIT, 0);        // (5) 0.06907
/*26 */     pci_set_word(conf + PCI_PREF_MEMORY_BASE, 0);    // (2) 0.07508
/*28 */     pci_set_word(conf + PCI_PREF_MEMORY_LIMIT, 0);   // (1) 0.07808
/*30 */     pci_set_word(conf + PCI_PREF_BASE_UPPER32, 0);   // (3) 0.07508
/*32 */     pci_set_word(conf + PCI_PREF_LIMIT_UPPER32, 0);  // (0) 0.07808
/*36 */     pci_set_word(conf + PCI_BRIDGE_CONTROL, 0);      // (4) 0.06907
/*38 */ }                                                    // (15) 0.003003
