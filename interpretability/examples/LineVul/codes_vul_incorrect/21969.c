// commit message qemu@ef0e8fc768 (target=1, prob=0.26831946, correct=False): iommu: Don't crash if machine is not PC_MACHINE
/*0  */ static void amdvi_realize(DeviceState *dev, Error **err)                             // (11) 0.0332
/*2  */ {                                                                                    // (19) 0.001953
/*4  */     int ret = 0;                                                                     // (18) 0.01562
/*6  */     AMDVIState *s = AMD_IOMMU_DEVICE(dev);                                           // (10) 0.03906
/*8  */     X86IOMMUState *x86_iommu = X86_IOMMU_DEVICE(dev);                                // (5) 0.05664
/*10 */     PCIBus *bus = PC_MACHINE(qdev_get_machine())->bus;                               // (9) 0.04883
/*12 */     s->iotlb = g_hash_table_new_full(amdvi_uint64_hash,                              // (8) 0.05078
/*14 */                                      amdvi_uint64_equal, g_free, g_free);            // (0) 0.1016
/*18 */     /* This device should take care of IOMMU PCI properties */                       // (12) 0.03125
/*20 */     x86_iommu->type = TYPE_AMD;                                                      // (13) 0.03125
/*22 */     qdev_set_parent_bus(DEVICE(&s->pci), &bus->qbus);                                // (7) 0.05078
/*24 */     object_property_set_bool(OBJECT(&s->pci), true, "realized", err);                // (6) 0.05273
/*26 */     s->capab_offset = pci_add_capability(&s->pci.dev, AMDVI_CAPAB_ID_SEC, 0,         // (4) 0.07031
/*28 */                                          AMDVI_CAPAB_SIZE);                          // (1) 0.09375
/*30 */     assert(s->capab_offset > 0);                                                     // (14) 0.02734
/*32 */     ret = pci_add_capability(&s->pci.dev, PCI_CAP_ID_MSI, 0, AMDVI_CAPAB_REG_SIZE);  // (2) 0.07812
/*34 */     assert(ret > 0);                                                                 // (16) 0.01758
/*36 */     ret = pci_add_capability(&s->pci.dev, PCI_CAP_ID_HT, 0, AMDVI_CAPAB_REG_SIZE);   // (3) 0.07617
/*38 */     assert(ret > 0);                                                                 // (17) 0.01758
/*42 */     /* set up MMIO */                                                                // (15) 0.01953
/*44 */     memory_region_init_io(&s->mmio, OBJECT(s), &mmio_mem_ops, s, "amdvi-mmio",       // 0.0
/*46 */                           AMDVI_MMIO_SIZE);                                          // 0.0
/*50 */     sysbus_init_mmio(SYS_BUS_DEVICE(s), &s->mmio);                                   // 0.0
/*52 */     sysbus_mmio_map(SYS_BUS_DEVICE(s), 0, AMDVI_BASE_ADDR);                          // 0.0
/*54 */     pci_setup_iommu(bus, amdvi_host_dma_iommu, s);                                   // 0.0
/*56 */     s->devid = object_property_get_int(OBJECT(&s->pci), "addr", err);                // 0.0
/*58 */     msi_init(&s->pci.dev, 0, 1, true, false, err);                                   // 0.0
/*60 */     amdvi_init(s);                                                                   // 0.0
/*62 */ }                                                                                    // 0.0
