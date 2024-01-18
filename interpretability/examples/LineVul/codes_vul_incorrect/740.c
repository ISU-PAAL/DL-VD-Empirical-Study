// commit message qemu@d049bde69d (target=1, prob=0.052392926, correct=False): spapr_pci: drop useless check in spapr_populate_pci_child_dt()
/*0   */ static int spapr_populate_pci_child_dt(PCIDevice *dev, void *fdt, int offset,   // (4) 0.06055
/*2   */                                        sPAPRPHBState *sphb)                     // (0) 0.09766
/*4   */ {                                                                               // (19) 0.001953
/*6   */     ResourceProps rp;                                                           // (16) 0.01758
/*8   */     bool is_bridge = false;                                                     // (15) 0.01953
/*10  */     int pci_status, err;                                                        // (14) 0.01953
/*12  */     char *buf = NULL;                                                           // (17) 0.01758
/*14  */     uint32_t drc_index = spapr_phb_get_pci_drc_index(sphb, dev);                // (3) 0.06836
/*16  */     uint32_t ccode = pci_default_read_config(dev, PCI_CLASS_PROG, 3);           // (5) 0.05664
/*18  */     uint32_t max_msi, max_msix;                                                 // (12) 0.0332
/*22  */     if (pci_default_read_config(dev, PCI_HEADER_TYPE, 1) ==                     // (6) 0.05078
/*24  */         PCI_HEADER_TYPE_BRIDGE) {                                               // (11) 0.03711
/*26  */         is_bridge = true;                                                       // (13) 0.02539
/*28  */     }                                                                           // (18) 0.007812
/*32  */     /* in accordance with PAPR+ v2.7 13.6.3, Table 181 */                       // (10) 0.04687
/*34  */     _FDT(fdt_setprop_cell(fdt, offset, "vendor-id",                             // (7) 0.05078
/*36  */                           pci_default_read_config(dev, PCI_VENDOR_ID, 2)));     // (1) 0.08984
/*38  */     _FDT(fdt_setprop_cell(fdt, offset, "device-id",                             // (9) 0.04883
/*40  */                           pci_default_read_config(dev, PCI_DEVICE_ID, 2)));     // (2) 0.08789
/*42  */     _FDT(fdt_setprop_cell(fdt, offset, "revision-id",                           // (8) 0.05078
/*44  */                           pci_default_read_config(dev, PCI_REVISION_ID, 1)));   // 0.0
/*46  */     _FDT(fdt_setprop_cell(fdt, offset, "class-code", ccode));                   // 0.0
/*48  */     if (pci_default_read_config(dev, PCI_INTERRUPT_PIN, 1)) {                   // 0.0
/*50  */         _FDT(fdt_setprop_cell(fdt, offset, "interrupts",                        // 0.0
/*52  */                  pci_default_read_config(dev, PCI_INTERRUPT_PIN, 1)));          // 0.0
/*54  */     }                                                                           // 0.0
/*58  */     if (!is_bridge) {                                                           // 0.0
/*60  */         _FDT(fdt_setprop_cell(fdt, offset, "min-grant",                         // 0.0
/*62  */             pci_default_read_config(dev, PCI_MIN_GNT, 1)));                     // 0.0
/*64  */         _FDT(fdt_setprop_cell(fdt, offset, "max-latency",                       // 0.0
/*66  */             pci_default_read_config(dev, PCI_MAX_LAT, 1)));                     // 0.0
/*68  */     }                                                                           // 0.0
/*72  */     if (pci_default_read_config(dev, PCI_SUBSYSTEM_ID, 2)) {                    // 0.0
/*74  */         _FDT(fdt_setprop_cell(fdt, offset, "subsystem-id",                      // 0.0
/*76  */                  pci_default_read_config(dev, PCI_SUBSYSTEM_ID, 2)));           // 0.0
/*78  */     }                                                                           // 0.0
/*82  */     if (pci_default_read_config(dev, PCI_SUBSYSTEM_VENDOR_ID, 2)) {             // 0.0
/*84  */         _FDT(fdt_setprop_cell(fdt, offset, "subsystem-vendor-id",               // 0.0
/*86  */                  pci_default_read_config(dev, PCI_SUBSYSTEM_VENDOR_ID, 2)));    // 0.0
/*88  */     }                                                                           // 0.0
/*92  */     _FDT(fdt_setprop_cell(fdt, offset, "cache-line-size",                       // 0.0
/*94  */         pci_default_read_config(dev, PCI_CACHE_LINE_SIZE, 1)));                 // 0.0
/*98  */     /* the following fdt cells are masked off the pci status register */        // 0.0
/*100 */     pci_status = pci_default_read_config(dev, PCI_STATUS, 2);                   // 0.0
/*102 */     _FDT(fdt_setprop_cell(fdt, offset, "devsel-speed",                          // 0.0
/*104 */                           PCI_STATUS_DEVSEL_MASK & pci_status));                // 0.0
/*108 */     if (pci_status & PCI_STATUS_FAST_BACK) {                                    // 0.0
/*110 */         _FDT(fdt_setprop(fdt, offset, "fast-back-to-back", NULL, 0));           // 0.0
/*112 */     }                                                                           // 0.0
/*114 */     if (pci_status & PCI_STATUS_66MHZ) {                                        // 0.0
/*116 */         _FDT(fdt_setprop(fdt, offset, "66mhz-capable", NULL, 0));               // 0.0
/*118 */     }                                                                           // 0.0
/*120 */     if (pci_status & PCI_STATUS_UDF) {                                          // 0.0
/*122 */         _FDT(fdt_setprop(fdt, offset, "udf-supported", NULL, 0));               // 0.0
/*124 */     }                                                                           // 0.0
/*128 */     _FDT(fdt_setprop_string(fdt, offset, "name",                                // 0.0
/*130 */                             pci_find_device_name((ccode >> 16) & 0xff,          // 0.0
/*132 */                                                  (ccode >> 8) & 0xff,           // 0.0
/*134 */                                                  ccode & 0xff)));               // 0.0
/*136 */     buf = spapr_phb_get_loc_code(sphb, dev);                                    // 0.0
/*138 */     if (!buf) {                                                                 // 0.0
/*140 */         error_report("Failed setting the ibm,loc-code");                        // 0.0
/*142 */         return -1;                                                              // 0.0
/*144 */     }                                                                           // 0.0
/*148 */     err = fdt_setprop_string(fdt, offset, "ibm,loc-code", buf);                 // 0.0
/*150 */     g_free(buf);                                                                // 0.0
/*152 */     if (err < 0) {                                                              // 0.0
/*154 */         return err;                                                             // 0.0
/*156 */     }                                                                           // 0.0
/*160 */     if (drc_index) {                                                            // 0.0
/*162 */         _FDT(fdt_setprop_cell(fdt, offset, "ibm,my-drc-index", drc_index));     // 0.0
/*164 */     }                                                                           // 0.0
/*168 */     _FDT(fdt_setprop_cell(fdt, offset, "#address-cells",                        // 0.0
/*170 */                           RESOURCE_CELLS_ADDRESS));                             // 0.0
/*172 */     _FDT(fdt_setprop_cell(fdt, offset, "#size-cells",                           // 0.0
/*174 */                           RESOURCE_CELLS_SIZE));                                // 0.0
/*178 */     max_msi = msi_nr_vectors_allocated(dev);                                    // 0.0
/*180 */     if (max_msi) {                                                              // 0.0
/*182 */         _FDT(fdt_setprop_cell(fdt, offset, "ibm,req#msi", max_msi));            // 0.0
/*184 */     }                                                                           // 0.0
/*186 */     max_msix = dev->msix_entries_nr;                                            // 0.0
/*188 */     if (max_msix) {                                                             // 0.0
/*190 */         _FDT(fdt_setprop_cell(fdt, offset, "ibm,req#msi-x", max_msix));         // 0.0
/*192 */     }                                                                           // 0.0
/*196 */     populate_resource_props(dev, &rp);                                          // 0.0
/*198 */     _FDT(fdt_setprop(fdt, offset, "reg", (uint8_t *)rp.reg, rp.reg_len));       // 0.0
/*200 */     _FDT(fdt_setprop(fdt, offset, "assigned-addresses",                         // 0.0
/*202 */                      (uint8_t *)rp.assigned, rp.assigned_len));                 // 0.0
/*206 */     if (sphb->pcie_ecs && pci_is_express(dev)) {                                // 0.0
/*208 */         _FDT(fdt_setprop_cell(fdt, offset, "ibm,pci-config-space-type", 0x1));  // 0.0
/*210 */     }                                                                           // 0.0
/*214 */     return 0;                                                                   // 0.0
/*216 */ }                                                                               // 0.0
