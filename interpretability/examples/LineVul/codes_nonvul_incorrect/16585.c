// commit message qemu@9a4c0e220d (target=0, prob=0.69556224, correct=False): hw/virtio-pci: fix virtio behaviour
/*0   */ static void virtio_pci_realize(PCIDevice *pci_dev, Error **errp)                     // (2) 0.05078
/*2   */ {                                                                                    // (28) 0.001953
/*4   */     VirtIOPCIProxy *proxy = VIRTIO_PCI(pci_dev);                                     // (6) 0.04492
/*6   */     VirtioPCIClass *k = VIRTIO_PCI_GET_CLASS(pci_dev);                               // (1) 0.05273
/*10  */     /*                                                                               // (27) 0.007812
/*12  */      * virtio pci bar layout used by default.                                        // (13) 0.02734
/*14  */      * subclasses can re-arrange things if needed.                                   // (11) 0.03125
/*16  */      *                                                                               // (26) 0.009766
/*18  */      *   region 0   --  virtio legacy io bar                                         // (9) 0.03516
/*20  */      *   region 1   --  msi-x bar                                                    // (8) 0.03516
/*22  */      *   region 4+5 --  virtio modern memory (64bit) bar                             // (7) 0.04297
/*24  */      *                                                                               // (24) 0.009766
/*26  */      */                                                                              // (25) 0.009766
/*28  */     proxy->legacy_io_bar  = 0;                                                       // (12) 0.0293
/*30  */     proxy->msix_bar       = 1;                                                       // (10) 0.03516
/*32  */     proxy->modern_io_bar  = 2;                                                       // (16) 0.02734
/*34  */     proxy->modern_mem_bar = 4;                                                       // (19) 0.02539
/*38  */     proxy->common.offset = 0x0;                                                      // (18) 0.02539
/*40  */     proxy->common.size = 0x1000;                                                     // (21) 0.02539
/*42  */     proxy->common.type = VIRTIO_PCI_CAP_COMMON_CFG;                                  // (4) 0.04687
/*46  */     proxy->isr.offset = 0x1000;                                                      // (15) 0.02734
/*48  */     proxy->isr.size = 0x1000;                                                        // (17) 0.02734
/*50  */     proxy->isr.type = VIRTIO_PCI_CAP_ISR_CFG;                                        // (3) 0.04883
/*54  */     proxy->device.offset = 0x2000;                                                   // (20) 0.02539
/*56  */     proxy->device.size = 0x1000;                                                     // (22) 0.02539
/*58  */     proxy->device.type = VIRTIO_PCI_CAP_DEVICE_CFG;                                  // (5) 0.04687
/*62  */     proxy->notify.offset = 0x3000;                                                   // (14) 0.02734
/*64  */     proxy->notify.size =                                                             // (23) 0.01953
/*66  */         QEMU_VIRTIO_PCI_QUEUE_MEM_MULT * VIRTIO_QUEUE_MAX;                           // (0) 0.07422
/*68  */     proxy->notify.type = VIRTIO_PCI_CAP_NOTIFY_CFG;                                  // 0.0
/*72  */     proxy->notify_pio.offset = 0x0;                                                  // 0.0
/*74  */     proxy->notify_pio.size = 0x4;                                                    // 0.0
/*76  */     proxy->notify_pio.type = VIRTIO_PCI_CAP_NOTIFY_CFG;                              // 0.0
/*80  */     /* subclasses can enforce modern, so do this unconditionally */                  // 0.0
/*82  */     memory_region_init(&proxy->modern_bar, OBJECT(proxy), "virtio-pci",              // 0.0
/*84  */                        2 * QEMU_VIRTIO_PCI_QUEUE_MEM_MULT *                          // 0.0
/*86  */                        VIRTIO_QUEUE_MAX);                                            // 0.0
/*90  */     memory_region_init_alias(&proxy->modern_cfg,                                     // 0.0
/*92  */                              OBJECT(proxy),                                          // 0.0
/*94  */                              "virtio-pci-cfg",                                       // 0.0
/*96  */                              &proxy->modern_bar,                                     // 0.0
/*98  */                              0,                                                      // 0.0
/*100 */                              memory_region_size(&proxy->modern_bar));                // 0.0
/*104 */     address_space_init(&proxy->modern_as, &proxy->modern_cfg, "virtio-pci-cfg-as");  // 0.0
/*108 */     if (pci_is_express(pci_dev) && pci_bus_is_express(pci_dev->bus) &&               // 0.0
/*110 */         !pci_bus_is_root(pci_dev->bus)) {                                            // 0.0
/*112 */         int pos;                                                                     // 0.0
/*116 */         pos = pcie_endpoint_cap_init(pci_dev, 0);                                    // 0.0
/*118 */         assert(pos > 0);                                                             // 0.0
/*122 */         pos = pci_add_capability(pci_dev, PCI_CAP_ID_PM, 0, PCI_PM_SIZEOF);          // 0.0
/*124 */         assert(pos > 0);                                                             // 0.0
/*128 */         /*                                                                           // 0.0
/*130 */          * Indicates that this function complies with revision 1.2 of the            // 0.0
/*132 */          * PCI Power Management Interface Specification.                             // 0.0
/*134 */          */                                                                          // 0.0
/*136 */         pci_set_word(pci_dev->config + pos + PCI_PM_PMC, 0x3);                       // 0.0
/*138 */     } else {                                                                         // 0.0
/*140 */         /*                                                                           // 0.0
/*142 */          * make future invocations of pci_is_express() return false                  // 0.0
/*144 */          * and pci_config_size() return PCI_CONFIG_SPACE_SIZE.                       // 0.0
/*146 */          */                                                                          // 0.0
/*148 */         pci_dev->cap_present &= ~QEMU_PCI_CAP_EXPRESS;                               // 0.0
/*150 */     }                                                                                // 0.0
/*154 */     virtio_pci_bus_new(&proxy->bus, sizeof(proxy->bus), proxy);                      // 0.0
/*156 */     if (k->realize) {                                                                // 0.0
/*158 */         k->realize(proxy, errp);                                                     // 0.0
/*160 */     }                                                                                // 0.0
/*162 */ }                                                                                    // 0.0
