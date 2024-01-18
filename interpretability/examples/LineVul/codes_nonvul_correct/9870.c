// commit message qemu@e70377dfa4 (target=0, prob=0.02027843, correct=True): s390x/pci: change the device array to a list
/*0  */ static S390PCIBusDevice *s390_pci_find_dev_by_target(const char *target)  // (0) 0.1111
/*2  */ {                                                                         // (17) 0.004115
/*4  */     int i;                                                                // (13) 0.02469
/*6  */     S390PCIBusDevice *pbdev;                                              // (6) 0.0535
/*8  */     S390pciState *s = s390_get_phb();                                     // (3) 0.07819
/*12 */     if (!target) {                                                        // (10) 0.03292
/*14 */         return NULL;                                                      // (9) 0.04115
/*16 */     }                                                                     // (15) 0.01646
/*20 */     for (i = 0; i < PCI_SLOT_MAX; i++) {                                  // (1) 0.08642
/*22 */         pbdev = s->pbdev[i];                                              // (4) 0.07407
/*24 */         if (!pbdev) {                                                     // (7) 0.0535
/*26 */             continue;                                                     // (8) 0.0535
/*28 */         }                                                                 // (11) 0.03292
/*32 */         if (!strcmp(pbdev->target, target)) {                             // (2) 0.0823
/*34 */             return pbdev;                                                 // (5) 0.06584
/*36 */         }                                                                 // (12) 0.03292
/*38 */     }                                                                     // (16) 0.01646
/*42 */     return NULL;                                                          // (14) 0.02469
/*44 */ }                                                                         // (18) 0.004115
