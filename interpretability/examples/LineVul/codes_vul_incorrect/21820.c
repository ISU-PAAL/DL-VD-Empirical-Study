// commit message qemu@43e86c8f5b (target=1, prob=0.028449519, correct=False): pcie_host: verify mmcfg address range
/*0  */ static void pcie_mmcfg_data_write(PCIBus *s,                                   // (4) 0.07965
/*2  */                                   uint32_t mmcfg_addr, uint32_t val, int len)  // (0) 0.2257
/*4  */ {                                                                              // (8) 0.004425
/*6  */     PCIDevice *pci_dev = pcie_dev_find_by_mmcfg_addr(s, mmcfg_addr);           // (3) 0.1504
/*10 */     if (!pci_dev) {                                                            // (5) 0.04867
/*12 */         return;                                                                // (6) 0.03982
/*14 */     }                                                                          // (7) 0.0177
/*16 */     pci_host_config_write_common(pci_dev, PCIE_MMCFG_CONFOFFSET(mmcfg_addr),   // (2) 0.1549
/*18 */                                  pci_config_size(pci_dev), val, len);          // (1) 0.208
/*20 */ }                                                                              // (9) 0.004425
