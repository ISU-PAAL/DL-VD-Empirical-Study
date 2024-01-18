// commit message qemu@7df9381b7a (target=0, prob=0.3785887, correct=True): vfio: Add sysfsdev property for pci & platform
/*0   */ static int vfio_add_std_cap(VFIOPCIDevice *vdev, uint8_t pos)                  // (1) 0.05664
/*2   */ {                                                                              // (29) 0.001953
/*4   */     PCIDevice *pdev = &vdev->pdev;                                             // (12) 0.03516
/*6   */     uint8_t cap_id, next, size;                                                // (14) 0.0293
/*8   */     int ret;                                                                   // (23) 0.01172
/*12  */     cap_id = pdev->config[pos];                                                // (17) 0.02734
/*14  */     next = pdev->config[pos + PCI_CAP_LIST_NEXT];                              // (5) 0.04102
/*18  */     /*                                                                         // (27) 0.007812
/*20  */      * If it becomes important to configure capabilities to their actual       // (15) 0.0293
/*22  */      * size, use this as the default when it's something we don't recognize.   // (6) 0.04102
/*24  */      * Since QEMU doesn't actually handle many of the config accesses,         // (9) 0.03906
/*26  */      * exact size doesn't seem worthwhile.                                     // (19) 0.02344
/*28  */      */                                                                        // (25) 0.009766
/*30  */     size = vfio_std_cap_max_size(pdev, pos);                                   // (4) 0.04297
/*34  */     /*                                                                         // (28) 0.007812
/*36  */      * pci_add_capability always inserts the new capability at the head        // (11) 0.03711
/*38  */      * of the chain.  Therefore to end up with a chain that matches the        // (10) 0.03906
/*40  */      * physical device, we insert from the end by making this recursive.       // (13) 0.03516
/*42  */      * This is also why we pre-calculate size above as cached config space     // (7) 0.04102
/*44  */      * will be changed as we unwind the stack.                                 // (16) 0.0293
/*46  */      */                                                                        // (26) 0.009766
/*48  */     if (next) {                                                                // (21) 0.01562
/*50  */         ret = vfio_add_std_cap(vdev, next);                                    // (2) 0.04688
/*52  */         if (ret) {                                                             // (20) 0.02344
/*54  */             return ret;                                                        // (18) 0.02734
/*56  */         }                                                                      // (22) 0.01562
/*58  */     } else {                                                                   // (24) 0.01172
/*60  */         /* Begin the rebuild, use QEMU emulated list bits */                   // (8) 0.04102
/*62  */         pdev->config[PCI_CAPABILITY_LIST] = 0;                                 // (3) 0.04688
/*64  */         vdev->emulated_config_bits[PCI_CAPABILITY_LIST] = 0xff;                // (0) 0.05859
/*66  */         vdev->emulated_config_bits[PCI_STATUS] |= PCI_STATUS_CAP_LIST;         // 0.0
/*68  */     }                                                                          // 0.0
/*72  */     /* Use emulated next pointer to allow dropping caps */                     // 0.0
/*74  */     pci_set_byte(vdev->emulated_config_bits + pos + PCI_CAP_LIST_NEXT, 0xff);  // 0.0
/*78  */     switch (cap_id) {                                                          // 0.0
/*80  */     case PCI_CAP_ID_MSI:                                                       // 0.0
/*82  */         ret = vfio_msi_setup(vdev, pos);                                       // 0.0
/*84  */         break;                                                                 // 0.0
/*86  */     case PCI_CAP_ID_EXP:                                                       // 0.0
/*88  */         vfio_check_pcie_flr(vdev, pos);                                        // 0.0
/*90  */         ret = vfio_setup_pcie_cap(vdev, pos, size);                            // 0.0
/*92  */         break;                                                                 // 0.0
/*94  */     case PCI_CAP_ID_MSIX:                                                      // 0.0
/*96  */         ret = vfio_msix_setup(vdev, pos);                                      // 0.0
/*98  */         break;                                                                 // 0.0
/*100 */     case PCI_CAP_ID_PM:                                                        // 0.0
/*102 */         vfio_check_pm_reset(vdev, pos);                                        // 0.0
/*104 */         vdev->pm_cap = pos;                                                    // 0.0
/*106 */         ret = pci_add_capability(pdev, cap_id, pos, size);                     // 0.0
/*108 */         break;                                                                 // 0.0
/*110 */     case PCI_CAP_ID_AF:                                                        // 0.0
/*112 */         vfio_check_af_flr(vdev, pos);                                          // 0.0
/*114 */         ret = pci_add_capability(pdev, cap_id, pos, size);                     // 0.0
/*116 */         break;                                                                 // 0.0
/*118 */     default:                                                                   // 0.0
/*120 */         ret = pci_add_capability(pdev, cap_id, pos, size);                     // 0.0
/*122 */         break;                                                                 // 0.0
/*124 */     }                                                                          // 0.0
/*128 */     if (ret < 0) {                                                             // 0.0
/*130 */         error_report("vfio: %04x:%02x:%02x.%x Error adding PCI capability "    // 0.0
/*132 */                      "0x%x[0x%x]@0x%x: %d", vdev->host.domain,                 // 0.0
/*134 */                      vdev->host.bus, vdev->host.slot, vdev->host.function,     // 0.0
/*136 */                      cap_id, size, pos, ret);                                  // 0.0
/*138 */         return ret;                                                            // 0.0
/*140 */     }                                                                          // 0.0
/*144 */     return 0;                                                                  // 0.0
/*146 */ }                                                                              // 0.0
