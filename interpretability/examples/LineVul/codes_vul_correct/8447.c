// commit message qemu@33848ceed7 (target=1, prob=0.6967319, correct=True): pcie_aer: Convert pcie_aer_init to Error
/*0   */ int pcie_aer_init(PCIDevice *dev, uint16_t offset, uint16_t size)           // (9) 0.05273
/*2   */ {                                                                           // (20) 0.001953
/*4   */     PCIExpressDevice *exp;                                                  // (17) 0.01758
/*8   */     pcie_add_capability(dev, PCI_EXT_CAP_ID_ERR, PCI_ERR_VER,               // (4) 0.06055
/*10  */                         offset, size);                                      // (10) 0.05273
/*12  */     exp = &dev->exp;                                                        // (15) 0.01953
/*14  */     exp->aer_cap = offset;                                                  // (14) 0.02148
/*18  */     /* log_max is property */                                               // (16) 0.01953
/*20  */     if (dev->exp.aer_log.log_max == PCIE_AER_LOG_MAX_UNSET) {               // (6) 0.06055
/*22  */         dev->exp.aer_log.log_max = PCIE_AER_LOG_MAX_DEFAULT;                // (3) 0.0625
/*24  */     }                                                                       // (18) 0.007812
/*26  */     /* clip down the value to avoid unreasobale memory usage */             // (12) 0.0332
/*28  */     if (dev->exp.aer_log.log_max > PCIE_AER_LOG_MAX_LIMIT) {                // (2) 0.0625
/*30  */         return -EINVAL;                                                     // (13) 0.02539
/*32  */     }                                                                       // (19) 0.007812
/*34  */     dev->exp.aer_log.log = g_malloc0(sizeof dev->exp.aer_log.log[0] *       // (1) 0.06641
/*36  */                                         dev->exp.aer_log.log_max);          // (0) 0.09961
/*40  */     pci_set_long(dev->w1cmask + offset + PCI_ERR_UNCOR_STATUS,              // (7) 0.05664
/*42  */                  PCI_ERR_UNC_SUPPORTED);                                    // (8) 0.05469
/*46  */     pci_set_long(dev->config + offset + PCI_ERR_UNCOR_SEVER,                // (11) 0.05078
/*48  */                  PCI_ERR_UNC_SEVERITY_DEFAULT);                             // (5) 0.06055
/*50  */     pci_set_long(dev->wmask + offset + PCI_ERR_UNCOR_SEVER,                 // 0.0
/*52  */                  PCI_ERR_UNC_SUPPORTED);                                    // 0.0
/*56  */     pci_long_test_and_set_mask(dev->w1cmask + offset + PCI_ERR_COR_STATUS,  // 0.0
/*58  */                                PCI_ERR_COR_SUPPORTED);                      // 0.0
/*62  */     pci_set_long(dev->config + offset + PCI_ERR_COR_MASK,                   // 0.0
/*64  */                  PCI_ERR_COR_MASK_DEFAULT);                                 // 0.0
/*66  */     pci_set_long(dev->wmask + offset + PCI_ERR_COR_MASK,                    // 0.0
/*68  */                  PCI_ERR_COR_SUPPORTED);                                    // 0.0
/*72  */     /* capabilities and control. multiple header logging is supported */    // 0.0
/*74  */     if (dev->exp.aer_log.log_max > 0) {                                     // 0.0
/*76  */         pci_set_long(dev->config + offset + PCI_ERR_CAP,                    // 0.0
/*78  */                      PCI_ERR_CAP_ECRC_GENC | PCI_ERR_CAP_ECRC_CHKC |        // 0.0
/*80  */                      PCI_ERR_CAP_MHRC);                                     // 0.0
/*82  */         pci_set_long(dev->wmask + offset + PCI_ERR_CAP,                     // 0.0
/*84  */                      PCI_ERR_CAP_ECRC_GENE | PCI_ERR_CAP_ECRC_CHKE |        // 0.0
/*86  */                      PCI_ERR_CAP_MHRE);                                     // 0.0
/*88  */     } else {                                                                // 0.0
/*90  */         pci_set_long(dev->config + offset + PCI_ERR_CAP,                    // 0.0
/*92  */                      PCI_ERR_CAP_ECRC_GENC | PCI_ERR_CAP_ECRC_CHKC);        // 0.0
/*94  */         pci_set_long(dev->wmask + offset + PCI_ERR_CAP,                     // 0.0
/*96  */                      PCI_ERR_CAP_ECRC_GENE | PCI_ERR_CAP_ECRC_CHKE);        // 0.0
/*98  */     }                                                                       // 0.0
/*102 */     switch (pcie_cap_get_type(dev)) {                                       // 0.0
/*104 */     case PCI_EXP_TYPE_ROOT_PORT:                                            // 0.0
/*106 */         /* this case will be set by pcie_aer_root_init() */                 // 0.0
/*108 */         /* fallthrough */                                                   // 0.0
/*110 */     case PCI_EXP_TYPE_DOWNSTREAM:                                           // 0.0
/*112 */     case PCI_EXP_TYPE_UPSTREAM:                                             // 0.0
/*114 */         pci_word_test_and_set_mask(dev->wmask + PCI_BRIDGE_CONTROL,         // 0.0
/*116 */                                    PCI_BRIDGE_CTL_SERR);                    // 0.0
/*118 */         pci_long_test_and_set_mask(dev->w1cmask + PCI_STATUS,               // 0.0
/*120 */                                    PCI_SEC_STATUS_RCV_SYSTEM_ERROR);        // 0.0
/*122 */         break;                                                              // 0.0
/*124 */     default:                                                                // 0.0
/*126 */         /* nothing */                                                       // 0.0
/*128 */         break;                                                              // 0.0
/*130 */     }                                                                       // 0.0
/*132 */     return 0;                                                               // 0.0
/*134 */ }                                                                           // 0.0
