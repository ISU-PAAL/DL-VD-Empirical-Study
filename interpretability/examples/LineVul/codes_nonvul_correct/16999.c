// commit message qemu@6877cff044 (target=0, prob=0.21878706, correct=True): pci-assign: propagate errors from assign_device()
/*0   */ static int assigned_initfn(struct PCIDevice *pci_dev)                            // (13) 0.03516
/*2   */ {                                                                                // (27) 0.001953
/*4   */     AssignedDevice *dev = DO_UPCAST(AssignedDevice, dev, pci_dev);               // (6) 0.04883
/*6   */     uint8_t e_intx;                                                              // (16) 0.02344
/*8   */     int r;                                                                       // (22) 0.01172
/*10  */     Error *local_err = NULL;                                                     // (17) 0.02149
/*14  */     if (!kvm_enabled()) {                                                        // (18) 0.02148
/*16  */         error_report("pci-assign: error: requires KVM support");                 // (8) 0.04688
/*18  */         return -1;                                                               // (19) 0.02148
/*20  */     }                                                                            // (25) 0.007812
/*24  */     if (!dev->host.domain && !dev->host.bus && !dev->host.slot &&                // (5) 0.04883
/*26  */         !dev->host.function) {                                                   // (15) 0.0293
/*28  */         error_report("pci-assign: error: no host device specified");             // (9) 0.04687
/*30  */         return -1;                                                               // (20) 0.02148
/*32  */     }                                                                            // (24) 0.007812
/*36  */     /*                                                                           // (26) 0.007812
/*38  */      * Set up basic config space access control. Will be further refined during  // (14) 0.03516
/*40  */      * device initialization.                                                    // (21) 0.01562
/*42  */      */                                                                          // (23) 0.009766
/*44  */     assigned_dev_emulate_config_read(dev, 0, PCI_CONFIG_SPACE_SIZE);             // (1) 0.05469
/*46  */     assigned_dev_direct_config_read(dev, PCI_STATUS, 2);                         // (11) 0.04297
/*48  */     assigned_dev_direct_config_read(dev, PCI_REVISION_ID, 1);                    // (7) 0.04883
/*50  */     assigned_dev_direct_config_read(dev, PCI_CLASS_PROG, 3);                     // (10) 0.04687
/*52  */     assigned_dev_direct_config_read(dev, PCI_CACHE_LINE_SIZE, 1);                // (3) 0.05273
/*54  */     assigned_dev_direct_config_read(dev, PCI_LATENCY_TIMER, 1);                  // (2) 0.05273
/*56  */     assigned_dev_direct_config_read(dev, PCI_BIST, 1);                           // (12) 0.04297
/*58  */     assigned_dev_direct_config_read(dev, PCI_CARDBUS_CIS, 4);                    // (4) 0.05078
/*60  */     assigned_dev_direct_config_read(dev, PCI_SUBSYSTEM_VENDOR_ID, 2);            // (0) 0.05859
/*62  */     assigned_dev_direct_config_read(dev, PCI_SUBSYSTEM_ID, 2);                   // 0.0
/*64  */     assigned_dev_direct_config_read(dev, PCI_CAPABILITY_LIST + 1, 7);            // 0.0
/*66  */     assigned_dev_direct_config_read(dev, PCI_MIN_GNT, 1);                        // 0.0
/*68  */     assigned_dev_direct_config_read(dev, PCI_MAX_LAT, 1);                        // 0.0
/*70  */     memcpy(dev->emulate_config_write, dev->emulate_config_read,                  // 0.0
/*72  */            sizeof(dev->emulate_config_read));                                    // 0.0
/*76  */     get_real_device(dev, &local_err);                                            // 0.0
/*78  */     if (local_err) {                                                             // 0.0
/*80  */         qerror_report_err(local_err);                                            // 0.0
/*82  */         error_free(local_err);                                                   // 0.0
/*84  */         goto out;                                                                // 0.0
/*86  */     }                                                                            // 0.0
/*90  */     if (assigned_device_pci_cap_init(pci_dev, &local_err) < 0) {                 // 0.0
/*92  */         qerror_report_err(local_err);                                            // 0.0
/*94  */         error_free(local_err);                                                   // 0.0
/*96  */         goto out;                                                                // 0.0
/*98  */     }                                                                            // 0.0
/*102 */     /* intercept MSI-X entry page in the MMIO */                                 // 0.0
/*104 */     if (dev->cap.available & ASSIGNED_DEVICE_CAP_MSIX) {                         // 0.0
/*106 */         assigned_dev_register_msix_mmio(dev, &local_err);                        // 0.0
/*108 */         if (local_err) {                                                         // 0.0
/*110 */             qerror_report_err(local_err);                                        // 0.0
/*112 */             error_free(local_err);                                               // 0.0
/*114 */             goto out;                                                            // 0.0
/*116 */         }                                                                        // 0.0
/*118 */     }                                                                            // 0.0
/*122 */     /* handle real device's MMIO/PIO BARs */                                     // 0.0
/*124 */     assigned_dev_register_regions(dev->real_device.regions,                      // 0.0
/*126 */                                   dev->real_device.region_number, dev,           // 0.0
/*128 */                                   &local_err);                                   // 0.0
/*130 */     if (local_err) {                                                             // 0.0
/*132 */         qerror_report_err(local_err);                                            // 0.0
/*134 */         error_free(local_err);                                                   // 0.0
/*136 */         goto out;                                                                // 0.0
/*138 */     }                                                                            // 0.0
/*142 */     /* handle interrupt routing */                                               // 0.0
/*144 */     e_intx = dev->dev.config[PCI_INTERRUPT_PIN] - 1;                             // 0.0
/*146 */     dev->intpin = e_intx;                                                        // 0.0
/*148 */     dev->intx_route.mode = PCI_INTX_DISABLED;                                    // 0.0
/*150 */     dev->intx_route.irq = -1;                                                    // 0.0
/*154 */     /* assign device to guest */                                                 // 0.0
/*156 */     r = assign_device(dev);                                                      // 0.0
/*158 */     if (r < 0) {                                                                 // 0.0
/*160 */         goto out;                                                                // 0.0
/*162 */     }                                                                            // 0.0
/*166 */     /* assign legacy INTx to the device */                                       // 0.0
/*168 */     r = assign_intx(dev);                                                        // 0.0
/*170 */     if (r < 0) {                                                                 // 0.0
/*172 */         goto assigned_out;                                                       // 0.0
/*174 */     }                                                                            // 0.0
/*178 */     assigned_dev_load_option_rom(dev);                                           // 0.0
/*182 */     add_boot_device_path(dev->bootindex, &pci_dev->qdev, NULL);                  // 0.0
/*186 */     return 0;                                                                    // 0.0
/*190 */ assigned_out:                                                                    // 0.0
/*192 */     deassign_device(dev);                                                        // 0.0
/*194 */ out:                                                                             // 0.0
/*196 */     free_assigned_device(dev);                                                   // 0.0
/*198 */     return -1;                                                                   // 0.0
/*200 */ }                                                                                // 0.0
