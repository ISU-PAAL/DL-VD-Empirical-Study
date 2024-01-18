// commit message qemu@b4ba67d9a7 (target=1, prob=0.9569318, correct=True): libqos: Change PCI accessors to take opaque BAR handle
/*0  */ void qvirtio_pci_set_msix_configuration_vector(QVirtioPCIDevice *d,               // (7) 0.05664
/*2  */                                         QGuestAllocator *alloc, uint16_t entry)   // (2) 0.1035
/*4  */ {                                                                                 // (17) 0.001953
/*6  */     uint16_t vector;                                                              // (14) 0.01758
/*8  */     uint32_t control;                                                             // (15) 0.01758
/*10 */     void *addr;                                                                   // (16) 0.01367
/*14 */     g_assert(d->pdev->msix_enabled);                                              // (11) 0.0332
/*16 */     addr = d->pdev->msix_table + (entry * 16);                                    // (9) 0.03906
/*20 */     g_assert_cmpint(entry, >=, 0);                                                // (12) 0.03125
/*22 */     g_assert_cmpint(entry, <, qpci_msix_table_size(d->pdev));                     // (6) 0.05859
/*24 */     d->config_msix_entry = entry;                                                 // (13) 0.02734
/*28 */     d->config_msix_data = 0x12345678;                                             // (10) 0.03516
/*30 */     d->config_msix_addr = guest_alloc(alloc, 4);                                  // (8) 0.03906
/*34 */     qpci_io_writel(d->pdev, addr + PCI_MSIX_ENTRY_LOWER_ADDR,                     // (4) 0.06445
/*36 */                                                     d->config_msix_addr & ~0UL);  // (0) 0.125
/*38 */     qpci_io_writel(d->pdev, addr + PCI_MSIX_ENTRY_UPPER_ADDR,                     // (5) 0.06445
/*40 */                                             (d->config_msix_addr >> 32) & ~0UL);  // (1) 0.1172
/*42 */     qpci_io_writel(d->pdev, addr + PCI_MSIX_ENTRY_DATA, d->config_msix_data);     // (3) 0.07422
/*46 */     control = qpci_io_readl(d->pdev, addr + PCI_MSIX_ENTRY_VECTOR_CTRL);          // 0.0
/*48 */     qpci_io_writel(d->pdev, addr + PCI_MSIX_ENTRY_VECTOR_CTRL,                    // 0.0
/*50 */                                         control & ~PCI_MSIX_ENTRY_CTRL_MASKBIT);  // 0.0
/*54 */     qpci_io_writew(d->pdev, d->addr + VIRTIO_MSI_CONFIG_VECTOR, entry);           // 0.0
/*56 */     vector = qpci_io_readw(d->pdev, d->addr + VIRTIO_MSI_CONFIG_VECTOR);          // 0.0
/*58 */     g_assert_cmphex(vector, !=, VIRTIO_MSI_NO_VECTOR);                            // 0.0
/*60 */ }                                                                                 // 0.0
