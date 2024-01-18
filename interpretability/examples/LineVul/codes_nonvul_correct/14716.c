// commit message qemu@fd56e0612b (target=0, prob=0.44525516, correct=True): pci: Eliminate redundant PCIDevice::bus pointer
/*0  */ static PCIBridgeWindows *pci_bridge_region_init(PCIBridge *br)  // (12) 0.03906
/*2  */ {                                                               // (16) 0.001953
/*4  */     PCIDevice *pd = PCI_DEVICE(br);                             // (14) 0.0332
/*6  */     PCIBus *parent = pd->bus;                                   // (15) 0.02734
/*8  */     PCIBridgeWindows *w = g_new(PCIBridgeWindows, 1);           // (11) 0.03906
/*10 */     uint16_t cmd = pci_get_word(pd->config + PCI_COMMAND);      // (9) 0.04883
/*14 */     pci_bridge_init_alias(br, &w->alias_pref_mem,               // (10) 0.04492
/*16 */                           PCI_BASE_ADDRESS_MEM_PREFETCH,        // (0) 0.08203
/*18 */                           "pci_bridge_pref_mem",                // (3) 0.07031
/*20 */                           &br->address_space_mem,               // (4) 0.06641
/*22 */                           parent->address_space_mem,            // (6) 0.06445
/*24 */                           cmd & PCI_COMMAND_MEMORY);            // (2) 0.07227
/*26 */     pci_bridge_init_alias(br, &w->alias_mem,                    // (13) 0.03906
/*28 */                           PCI_BASE_ADDRESS_SPACE_MEMORY,        // (1) 0.08008
/*30 */                           "pci_bridge_mem",                     // (8) 0.06445
/*32 */                           &br->address_space_mem,               // (5) 0.06641
/*34 */                           parent->address_space_mem,            // (7) 0.06445
/*36 */                           cmd & PCI_COMMAND_MEMORY);            // 0.0
/*38 */     pci_bridge_init_alias(br, &w->alias_io,                     // 0.0
/*40 */                           PCI_BASE_ADDRESS_SPACE_IO,            // 0.0
/*42 */                           "pci_bridge_io",                      // 0.0
/*44 */                           &br->address_space_io,                // 0.0
/*46 */                           parent->address_space_io,             // 0.0
/*48 */                           cmd & PCI_COMMAND_IO);                // 0.0
/*52 */     pci_bridge_init_vga_aliases(br, parent, w->alias_vga);      // 0.0
/*56 */     return w;                                                   // 0.0
/*58 */ }                                                               // 0.0
