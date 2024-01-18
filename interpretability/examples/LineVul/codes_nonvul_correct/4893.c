// commit message qemu@dc638fadb5 (target=0, prob=0.011569938, correct=True): usb-uhci: convert to PCIDEviceInfo to initialize ids
/*0  */ static int usb_uhci_piix3_initfn(PCIDevice *dev)                        // (3) 0.1304
/*2  */ {                                                                       // (6) 0.006211
/*4  */     UHCIState *s = DO_UPCAST(UHCIState, dev, dev);                      // (2) 0.1553
/*6  */     uint8_t *pci_conf = s->dev.config;                                  // (4) 0.118
/*10 */     pci_config_set_vendor_id(pci_conf, PCI_VENDOR_ID_INTEL);            // (1) 0.1863
/*12 */     pci_config_set_device_id(pci_conf, PCI_DEVICE_ID_INTEL_82371SB_2);  // (0) 0.2174
/*14 */     return usb_uhci_common_initfn(s);                                   // (5) 0.09938
/*16 */ }                                                                       // (7) 0.006211
