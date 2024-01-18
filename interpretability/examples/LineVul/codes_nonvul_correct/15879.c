// commit message qemu@7d6e771f49 (target=0, prob=0.40113312, correct=True): hw/versatile_pci: Expose multiple sysbus mmio regions
/*0  */ static int pci_vpb_init(SysBusDevice *dev)                            // (13) 0.0293
/*2  */ {                                                                     // (20) 0.001953
/*4  */     PCIVPBState *s = FROM_SYSBUS(PCIVPBState, dev);                   // (10) 0.04492
/*6  */     PCIBus *bus;                                                      // (16) 0.01758
/*8  */     int i;                                                            // (17) 0.01172
/*12 */     for (i = 0; i < 4; i++) {                                         // (12) 0.03125
/*14 */         sysbus_init_irq(dev, &s->irq[i]);                             // (8) 0.04883
/*16 */     }                                                                 // (18) 0.007812
/*18 */     bus = pci_register_bus(&dev->qdev, "pci",                         // (11) 0.03906
/*20 */                            pci_vpb_set_irq, pci_vpb_map_irq, s->irq,  // (0) 0.09961
/*22 */                            get_system_memory(), get_system_io(),      // (3) 0.07422
/*24 */                            PCI_DEVFN(11, 0), 4);                      // (4) 0.07227
/*28 */     /* ??? Register memory space.  */                                 // (14) 0.02148
/*32 */     memory_region_init_io(&s->mem_config, &pci_vpb_config_ops, bus,   // (7) 0.05859
/*34 */                           "pci-vpb-selfconfig", 0x1000000);           // (1) 0.07812
/*36 */     memory_region_init_io(&s->mem_config2, &pci_vpb_config_ops, bus,  // (5) 0.06055
/*38 */                           "pci-vpb-config", 0x1000000);               // (2) 0.07617
/*40 */     if (s->realview) {                                                // (15) 0.02148
/*42 */         isa_mmio_setup(&s->isa, 0x0100000);                           // (9) 0.04688
/*44 */     }                                                                 // (19) 0.007812
/*48 */     sysbus_init_mmio_cb2(dev, pci_vpb_map, pci_vpb_unmap);            // (6) 0.06055
/*52 */     pci_create_simple(bus, -1, "versatile_pci_host");                 // 0.0
/*54 */     return 0;                                                         // 0.0
/*56 */ }                                                                     // 0.0
