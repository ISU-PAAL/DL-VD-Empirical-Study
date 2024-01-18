// commit message qemu@9cd1e97a7a (target=0, prob=0.055878587, correct=True): pci: allow 32-bit PCI IO accesses to pass through the PCI bridge
/*0  */ void pci_bridge_initfn(PCIDevice *dev, const char *typename)                               // (8) 0.04297
/*2  */ {                                                                                          // (23) 0.001953
/*4  */     PCIBus *parent = dev->bus;                                                             // (17) 0.02539
/*6  */     PCIBridge *br = PCI_BRIDGE(dev);                                                       // (15) 0.03125
/*8  */     PCIBus *sec_bus = &br->sec_bus;                                                        // (11) 0.03516
/*12 */     pci_word_test_and_set_mask(dev->config + PCI_STATUS,                                   // (7) 0.04687
/*14 */                                PCI_STATUS_66MHZ | PCI_STATUS_FAST_BACK);                   // (0) 0.0957
/*18 */     /*                                                                                     // (21) 0.007813
/*20 */      * TODO: We implement VGA Enable in the Bridge Control Register                        // (12) 0.03516
/*22 */      * therefore per the PCI to PCI bridge spec we must also implement                     // (14) 0.0332
/*24 */      * VGA Palette Snooping.  When done, set this bit writable:                            // (9) 0.04297
/*26 */      *                                                                                     // (19) 0.009766
/*28 */      * pci_word_test_and_set_mask(dev->wmask + PCI_COMMAND,                                // (4) 0.05469
/*30 */      *                            PCI_COMMAND_VGA_PALETTE);                                // (1) 0.08984
/*32 */      */                                                                                    // (20) 0.009766
/*36 */     pci_config_set_class(dev->config, PCI_CLASS_BRIDGE_PCI);                               // (5) 0.05078
/*38 */     dev->config[PCI_HEADER_TYPE] =                                                         // (16) 0.03125
/*40 */         (dev->config[PCI_HEADER_TYPE] & PCI_HEADER_TYPE_MULTI_FUNCTION) |                  // (2) 0.07227
/*42 */         PCI_HEADER_TYPE_BRIDGE;                                                            // (13) 0.03516
/*44 */     pci_set_word(dev->config + PCI_SEC_STATUS,                                             // (10) 0.03906
/*46 */                  PCI_STATUS_66MHZ | PCI_STATUS_FAST_BACK);                                 // (3) 0.06836
/*50 */     /*                                                                                     // (22) 0.007812
/*52 */      * If we don't specify the name, the bus will be addressed as <id>.0, where            // (6) 0.04883
/*54 */      * id is the device id.                                                                // (18) 0.02148
/*56 */      * Since PCI Bridge devices have a single bus each, we don't need the index:           // 0.0
/*58 */      * let users address the bus using the device name.                                    // 0.0
/*60 */      */                                                                                    // 0.0
/*62 */     if (!br->bus_name && dev->qdev.id && *dev->qdev.id) {                                  // 0.0
/*64 */ 	    br->bus_name = dev->qdev.id;                                                          // 0.0
/*66 */     }                                                                                      // 0.0
/*70 */     qbus_create_inplace(sec_bus, sizeof(br->sec_bus), typename, DEVICE(dev),               // 0.0
/*72 */                         br->bus_name);                                                     // 0.0
/*74 */     sec_bus->parent_dev = dev;                                                             // 0.0
/*76 */     sec_bus->map_irq = br->map_irq ? br->map_irq : pci_swizzle_map_irq_fn;                 // 0.0
/*78 */     sec_bus->address_space_mem = &br->address_space_mem;                                   // 0.0
/*80 */     memory_region_init(&br->address_space_mem, OBJECT(br), "pci_bridge_pci", UINT64_MAX);  // 0.0
/*82 */     sec_bus->address_space_io = &br->address_space_io;                                     // 0.0
/*84 */     memory_region_init(&br->address_space_io, OBJECT(br), "pci_bridge_io", 65536);         // 0.0
/*86 */     br->windows = pci_bridge_region_init(br);                                              // 0.0
/*88 */     QLIST_INIT(&sec_bus->child);                                                           // 0.0
/*90 */     QLIST_INSERT_HEAD(&parent->child, sec_bus, sibling);                                   // 0.0
/*92 */ }                                                                                          // 0.0
