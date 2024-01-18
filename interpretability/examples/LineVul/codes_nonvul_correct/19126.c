// commit message qemu@67d5cd9722 (target=0, prob=0.010009441, correct=True): s390x/pci: introduce S390PCIIOMMU
/*0  */ static AddressSpace *s390_pci_dma_iommu(PCIBus *bus, void *opaque, int devfn)  // (0) 0.4103
/*2  */ {                                                                              // (3) 0.01282
/*4  */     S390pciState *s = opaque;                                                  // (2) 0.1667
/*8  */     return &s->pbdev[PCI_SLOT(devfn)].as;                                      // (1) 0.2692
/*10 */ }                                                                              // (4) 0.01282
