// commit message qemu@d659d94013 (target=1, prob=0.5795546, correct=True): hw/pci-bridge/pcie_pci_bridge: properly handle MSI unavailability case
/*0  */ static void pcie_pci_bridge_write_config(PCIDevice *d,  // (1) 0.1858
/*2  */         uint32_t address, uint32_t val, int len)        // (0) 0.1947
/*4  */ {                                                       // (5) 0.00885
/*6  */     pci_bridge_write_config(d, address, val, len);      // (3) 0.1681
/*8  */     msi_write_config(d, address, val, len);             // (4) 0.1593
/*10 */     shpc_cap_write_config(d, address, val, len);        // (2) 0.177
/*12 */ }                                                       // (6) 0.00885
