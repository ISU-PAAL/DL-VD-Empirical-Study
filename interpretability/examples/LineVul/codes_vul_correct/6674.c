// commit message qemu@2e63eb2bec (target=1, prob=0.99906737, correct=True): xen/pt: Set is_express to avoid out-of-bounds write
/*0  */ static void xen_pci_passthrough_class_init(ObjectClass *klass, void *data)  // (0) 0.1185
/*2  */ {                                                                           // (11) 0.004739
/*4  */     DeviceClass *dc = DEVICE_CLASS(klass);                                  // (7) 0.07583
/*6  */     PCIDeviceClass *k = PCI_DEVICE_CLASS(klass);                            // (2) 0.09953
/*10 */     k->realize = xen_pt_realize;                                            // (9) 0.07109
/*12 */     k->exit = xen_pt_unregister_device;                                     // (8) 0.07583
/*14 */     k->config_read = xen_pt_pci_read_config;                                // (3) 0.09479
/*16 */     k->config_write = xen_pt_pci_write_config;                              // (4) 0.09479
/*19 */     set_bit(DEVICE_CATEGORY_MISC, dc->categories);                          // (1) 0.109
/*21 */     dc->desc = "Assign an host PCI device with Xen";                        // (6) 0.08057
/*23 */     dc->props = xen_pci_passthrough_properties;                             // (5) 0.09005
/*25 */ };                                                                          // (10) 0.004739
