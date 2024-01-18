// commit message qemu@45eb768c70 (target=0, prob=0.17672515, correct=True): pci_bridge: factor out common code
/*0   */ static void pci_init_mask_bridge(PCIDevice *d)                               // (15) 0.0332
/*2   */ {                                                                            // (19) 0.001953
/*4   */     /* PCI_PRIMARY_BUS, PCI_SECONDARY_BUS, PCI_SUBORDINATE_BUS and           // (5) 0.05859
/*6   */        PCI_SEC_LETENCY_TIMER */                                              // (16) 0.0332
/*8   */     memset(d->wmask + PCI_PRIMARY_BUS, 0xff, 4);                             // (12) 0.04688
/*12  */     /* base and limit */                                                     // (18) 0.01562
/*14  */     d->wmask[PCI_IO_BASE] = PCI_IO_RANGE_MASK & 0xff;                        // (6) 0.05859
/*16  */     d->wmask[PCI_IO_LIMIT] = PCI_IO_RANGE_MASK & 0xff;                       // (2) 0.06055
/*18  */     pci_set_word(d->wmask + PCI_MEMORY_BASE,                                 // (14) 0.04492
/*20  */                  PCI_MEMORY_RANGE_MASK & 0xffff);                            // (0) 0.0625
/*22  */     pci_set_word(d->wmask + PCI_MEMORY_LIMIT,                                // (13) 0.04688
/*24  */                  PCI_MEMORY_RANGE_MASK & 0xffff);                            // (1) 0.0625
/*26  */     pci_set_word(d->wmask + PCI_PREF_MEMORY_BASE,                            // (11) 0.05078
/*28  */                  PCI_PREF_RANGE_MASK & 0xffff);                              // (3) 0.06055
/*30  */     pci_set_word(d->wmask + PCI_PREF_MEMORY_LIMIT,                           // (10) 0.05273
/*32  */                  PCI_PREF_RANGE_MASK & 0xffff);                              // (4) 0.06055
/*36  */     /* PCI_PREF_BASE_UPPER32 and PCI_PREF_LIMIT_UPPER32 */                   // (7) 0.05664
/*38  */     memset(d->wmask + PCI_PREF_BASE_UPPER32, 0xff, 8);                       // (9) 0.05469
/*42  */     /* Supported memory and i/o types */                                     // (17) 0.02344
/*44  */     d->config[PCI_IO_BASE] |= PCI_IO_RANGE_TYPE_16;                          // (8) 0.05469
/*46  */     d->config[PCI_IO_LIMIT] |= PCI_IO_RANGE_TYPE_16;                         // 0.0
/*48  */     pci_word_test_and_set_mask(d->config + PCI_PREF_MEMORY_BASE,             // 0.0
/*50  */                                PCI_PREF_RANGE_TYPE_64);                      // 0.0
/*52  */     pci_word_test_and_set_mask(d->config + PCI_PREF_MEMORY_LIMIT,            // 0.0
/*54  */                                PCI_PREF_RANGE_TYPE_64);                      // 0.0
/*58  */ /* TODO: add this define to pci_regs.h in linux and then in qemu. */         // 0.0
/*60  */ #define  PCI_BRIDGE_CTL_VGA_16BIT	0x10	/* VGA 16-bit decode */               // 0.0
/*62  */ #define  PCI_BRIDGE_CTL_DISCARD		0x100	/* Primary discard timer */           // 0.0
/*64  */ #define  PCI_BRIDGE_CTL_SEC_DISCARD	0x200	/* Secondary discard timer */      // 0.0
/*66  */ #define  PCI_BRIDGE_CTL_DISCARD_STATUS	0x400	/* Discard timer status */      // 0.0
/*68  */ #define  PCI_BRIDGE_CTL_DISCARD_SERR	0x800	/* Discard timer SERR# enable */  // 0.0
/*70  */ /*                                                                           // 0.0
/*72  */  * TODO: Bridges default to 10-bit VGA decoding but we currently only        // 0.0
/*74  */  * implement 16-bit decoding (no alias support).                             // 0.0
/*76  */  */                                                                          // 0.0
/*78  */     pci_set_word(d->wmask + PCI_BRIDGE_CONTROL,                              // 0.0
/*80  */                  PCI_BRIDGE_CTL_PARITY |                                     // 0.0
/*82  */                  PCI_BRIDGE_CTL_SERR |                                       // 0.0
/*84  */                  PCI_BRIDGE_CTL_ISA |                                        // 0.0
/*86  */                  PCI_BRIDGE_CTL_VGA |                                        // 0.0
/*88  */                  PCI_BRIDGE_CTL_VGA_16BIT |                                  // 0.0
/*90  */                  PCI_BRIDGE_CTL_MASTER_ABORT |                               // 0.0
/*92  */                  PCI_BRIDGE_CTL_BUS_RESET |                                  // 0.0
/*94  */                  PCI_BRIDGE_CTL_FAST_BACK |                                  // 0.0
/*96  */                  PCI_BRIDGE_CTL_DISCARD |                                    // 0.0
/*98  */                  PCI_BRIDGE_CTL_SEC_DISCARD |                                // 0.0
/*100 */                  PCI_BRIDGE_CTL_DISCARD_SERR);                               // 0.0
/*102 */     /* Below does not do anything as we never set this bit, put here for     // 0.0
/*104 */      * completeness. */                                                      // 0.0
/*106 */     pci_set_word(d->w1cmask + PCI_BRIDGE_CONTROL,                            // 0.0
/*108 */                  PCI_BRIDGE_CTL_DISCARD_STATUS);                             // 0.0
/*110 */     d->cmask[PCI_IO_BASE] |= PCI_IO_RANGE_TYPE_MASK;                         // 0.0
/*112 */     d->cmask[PCI_IO_LIMIT] |= PCI_IO_RANGE_TYPE_MASK;                        // 0.0
/*114 */     pci_word_test_and_set_mask(d->cmask + PCI_PREF_MEMORY_BASE,              // 0.0
/*116 */                                PCI_PREF_RANGE_TYPE_MASK);                    // 0.0
/*118 */     pci_word_test_and_set_mask(d->cmask + PCI_PREF_MEMORY_LIMIT,             // 0.0
/*120 */                                PCI_PREF_RANGE_TYPE_MASK);                    // 0.0
/*122 */ }                                                                            // 0.0
