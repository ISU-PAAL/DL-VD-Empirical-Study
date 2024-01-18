// commit message qemu@d15fda639b (target=0, prob=0.17860256, correct=True): hw/intel-hda.c: convert to PCIDeviceInfo to initialize ids
/*0  */ static int intel_hda_init(PCIDevice *pci)                                        // (13) 0.0332
/*2  */ {                                                                                // (19) 0.001953
/*4  */     IntelHDAState *d = DO_UPCAST(IntelHDAState, pci, pci);                       // (9) 0.04883
/*6  */     uint8_t *conf = d->pci.config;                                               // (14) 0.0332
/*10 */     d->name = d->pci.qdev.info->name;                                            // (11) 0.03711
/*14 */     pci_config_set_vendor_id(conf, PCI_VENDOR_ID_INTEL);                         // (7) 0.05273
/*16 */     pci_config_set_device_id(conf, 0x2668);                                      // (10) 0.03906
/*18 */     pci_config_set_revision(conf, 1);                                            // (15) 0.03125
/*20 */     pci_config_set_class(conf, PCI_CLASS_MULTIMEDIA_HD_AUDIO);                   // (4) 0.05469
/*22 */     pci_config_set_interrupt_pin(conf, 1);                                       // (12) 0.03516
/*26 */     /* HDCTL off 0x40 bit 0 selects signaling mode (1-HDA, 0 - Ac97) 18.1.19 */  // (2) 0.06445
/*28 */     conf[0x40] = 0x01;                                                           // (16) 0.02734
/*32 */     d->mmio_addr = cpu_register_io_memory(intel_hda_mmio_read,                   // (5) 0.05469
/*34 */                                           intel_hda_mmio_write, d,               // (0) 0.1035
/*36 */                                           DEVICE_NATIVE_ENDIAN);                 // (1) 0.09766
/*38 */     pci_register_bar_simple(&d->pci, 0, 0x4000, 0, d->mmio_addr);                // (3) 0.06055
/*40 */     if (d->msi) {                                                                // (17) 0.02148
/*42 */         msi_init(&d->pci, 0x50, 1, true, false);                                 // (8) 0.05273
/*44 */     }                                                                            // (18) 0.007812
/*48 */     hda_codec_bus_init(&d->pci.qdev, &d->codecs,                                 // (6) 0.05469
/*50 */                        intel_hda_response, intel_hda_xfer);                      // 0.0
/*54 */     return 0;                                                                    // 0.0
/*56 */ }                                                                                // 0.0
