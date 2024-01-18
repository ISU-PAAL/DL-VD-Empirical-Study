// commit message qemu@67d5cd9722 (target=0, prob=0.28270522, correct=True): s390x/pci: introduce S390PCIIOMMU
/*0  */ void s390_pci_iommu_disable(S390PCIBusDevice *pbdev)            // (1) 0.2371
/*2  */ {                                                               // (4) 0.01031
/*4  */     memory_region_del_subregion(&pbdev->mr, &pbdev->iommu_mr);  // (0) 0.2784
/*6  */     object_unparent(OBJECT(&pbdev->iommu_mr));                  // (2) 0.2062
/*8  */     pbdev->iommu_enabled = false;                               // (3) 0.1546
/*10 */ }                                                               // (5) 0.01031
