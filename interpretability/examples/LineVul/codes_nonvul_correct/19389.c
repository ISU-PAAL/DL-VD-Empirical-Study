// commit message qemu@dc638fadb5 (target=0, prob=0.016122552, correct=True): usb-uhci: convert to PCIDEviceInfo to initialize ids
/*0  */ static int usb_uhci_vt82c686b_initfn(PCIDevice *dev)             // (4) 0.08679
/*2  */ {                                                                // (12) 0.003774
/*4  */     UHCIState *s = DO_UPCAST(UHCIState, dev, dev);               // (2) 0.09434
/*6  */     uint8_t *pci_conf = s->dev.config;                           // (7) 0.0717
/*10 */     pci_config_set_vendor_id(pci_conf, PCI_VENDOR_ID_VIA);       // (1) 0.1132
/*12 */     pci_config_set_device_id(pci_conf, PCI_DEVICE_ID_VIA_UHCI);  // (0) 0.1208
/*16 */     /* USB misc control 1/2 */                                   // (9) 0.04151
/*18 */     pci_set_long(pci_conf + 0x40,0x00001000);                    // (5) 0.08679
/*20 */     /* PM capability */                                          // (11) 0.02642
/*22 */     pci_set_long(pci_conf + 0x80,0x00020001);                    // (3) 0.09057
/*24 */     /* USB legacy support  */                                    // (10) 0.03396
/*26 */     pci_set_long(pci_conf + 0xc0,0x00002000);                    // (6) 0.08679
/*30 */     return usb_uhci_common_initfn(s);                            // (8) 0.06038
/*32 */ }                                                                // (13) 0.003774
