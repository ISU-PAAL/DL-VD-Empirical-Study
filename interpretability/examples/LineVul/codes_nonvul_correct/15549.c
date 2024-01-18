// commit message qemu@10ee2aaa41 (target=0, prob=0.032828692, correct=True): Remove unneded ac97 indirection accessing its state
/*0  */ static void ac97_initfn (PCIDevice *dev)                                       // (14) 0.0293
/*2  */ {                                                                              // (21) 0.001953
/*4  */     PCIAC97LinkState *d = DO_UPCAST (PCIAC97LinkState, dev, dev);              // (7) 0.05469
/*6  */     AC97LinkState *s = &d->ac97;                                               // (13) 0.03125
/*8  */     uint8_t *c = d->dev.config;                                                // (12) 0.03125
/*12 */     s->pci_dev = &d->dev;                                                      // (15) 0.0293
/*14 */     pci_config_set_vendor_id (c, PCI_VENDOR_ID_INTEL); /* ro */                // (3) 0.05859
/*16 */     pci_config_set_device_id (c, PCI_DEVICE_ID_INTEL_82801AA_5); /* ro */      // (0) 0.06836
/*20 */     c[0x04] = 0x00;      /* pcicmd pci command rw, ro */                       // (5) 0.05859
/*22 */     c[0x05] = 0x00;                                                            // (17) 0.02734
/*26 */     c[0x06] = 0x80;      /* pcists pci status rwc, ro */                       // (4) 0.05859
/*28 */     c[0x07] = 0x02;                                                            // (18) 0.02734
/*32 */     c[0x08] = 0x01;      /* rid revision ro */                                 // (11) 0.04687
/*34 */     c[0x09] = 0x00;      /* pi programming interface ro */                     // (10) 0.04883
/*36 */     pci_config_set_class (c, PCI_CLASS_MULTIMEDIA_AUDIO); /* ro */             // (6) 0.05664
/*38 */     c[PCI_HEADER_TYPE] = PCI_HEADER_TYPE_NORMAL; /* headtyp header type ro */  // (2) 0.06055
/*42 */     c[0x10] = 0x01;      /* nabmar native audio mixer base                     // (9) 0.05078
/*44 */                             address rw */                                      // (1) 0.06055
/*46 */     c[0x11] = 0x00;                                                            // (16) 0.02734
/*48 */     c[0x12] = 0x00;                                                            // (19) 0.02734
/*50 */     c[0x13] = 0x00;                                                            // (20) 0.02734
/*54 */     c[0x14] = 0x01;      /* nabmbar native audio bus mastering                 // (8) 0.05273
/*56 */                             base address rw */                                 // 0.0
/*58 */     c[0x15] = 0x00;                                                            // 0.0
/*60 */     c[0x16] = 0x00;                                                            // 0.0
/*62 */     c[0x17] = 0x00;                                                            // 0.0
/*66 */     c[0x2c] = 0x86;      /* svid subsystem vendor id rwo */                    // 0.0
/*68 */     c[0x2d] = 0x80;                                                            // 0.0
/*72 */     c[0x2e] = 0x00;      /* sid subsystem id rwo */                            // 0.0
/*74 */     c[0x2f] = 0x00;                                                            // 0.0
/*78 */     c[0x3c] = 0x00;      /* intr_ln interrupt line rw */                       // 0.0
/*80 */     c[0x3d] = 0x01;      /* intr_pn interrupt pin ro */                        // 0.0
/*84 */     pci_register_bar (&d->dev, 0, 256 * 4, PCI_ADDRESS_SPACE_IO, ac97_map);    // 0.0
/*86 */     pci_register_bar (&d->dev, 1, 64 * 4, PCI_ADDRESS_SPACE_IO, ac97_map);     // 0.0
/*88 */     register_savevm ("ac97", 0, 2, ac97_save, ac97_load, s);                   // 0.0
/*90 */     qemu_register_reset (ac97_on_reset, s);                                    // 0.0
/*92 */     AUD_register_card ("ac97", &s->card);                                      // 0.0
/*94 */     ac97_on_reset (s);                                                         // 0.0
/*96 */ }                                                                              // 0.0
