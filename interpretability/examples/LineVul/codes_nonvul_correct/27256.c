// commit message qemu@fd56e0612b (target=0, prob=0.15461668, correct=True): pci: Eliminate redundant PCIDevice::bus pointer
/*0  */ AddressSpace *pci_device_iommu_address_space(PCIDevice *dev)                   // (4) 0.1041
/*2  */ {                                                                              // (10) 0.004525
/*4  */     PCIBus *bus = PCI_BUS(dev->bus);                                           // (5) 0.07692
/*6  */     PCIBus *iommu_bus = bus;                                                   // (6) 0.06787
/*10 */     while(iommu_bus && !iommu_bus->iommu_fn && iommu_bus->parent_dev) {        // (1) 0.1584
/*12 */         iommu_bus = PCI_BUS(iommu_bus->parent_dev->bus);                       // (2) 0.1312
/*14 */     }                                                                          // (8) 0.0181
/*16 */     if (iommu_bus && iommu_bus->iommu_fn) {                                    // (3) 0.1086
/*18 */         return iommu_bus->iommu_fn(bus, iommu_bus->iommu_opaque, dev->devfn);  // (0) 0.181
/*20 */     }                                                                          // (9) 0.0181
/*22 */     return &address_space_memory;                                              // (7) 0.04977
/*24 */ }                                                                              // (11) 0.004525
