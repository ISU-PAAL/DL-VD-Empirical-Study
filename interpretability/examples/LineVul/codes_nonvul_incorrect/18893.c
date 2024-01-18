// commit message qemu@e75ccf2c03 (target=0, prob=0.5809898, correct=False): virtio-pci.c: convert to PCIDEviceInfo to initialize ids
/*0   */ static void virtio_init_pci(VirtIOPCIProxy *proxy, VirtIODevice *vdev,          // (5) 0.05469
/*2   */                             uint16_t vendor, uint16_t device,                   // (2) 0.07617
/*4   */                             uint16_t class_code, uint8_t pif)                   // (0) 0.08203
/*6   */ {                                                                               // (21) 0.001953
/*8   */     uint8_t *config;                                                            // (19) 0.01953
/*10  */     uint32_t size;                                                              // (20) 0.01758
/*14  */     proxy->vdev = vdev;                                                         // (18) 0.02148
/*18  */     config = proxy->pci_dev.config;                                             // (15) 0.02734
/*20  */     pci_config_set_vendor_id(config, vendor);                                   // (11) 0.03516
/*22  */     pci_config_set_device_id(config, device);                                   // (12) 0.0332
/*26  */     config[0x08] = VIRTIO_PCI_ABI_VERSION;                                      // (7) 0.04297
/*30  */     config[0x09] = pif;                                                         // (16) 0.02539
/*32  */     pci_config_set_class(config, class_code);                                   // (14) 0.0332
/*36  */     config[0x2c] = vendor & 0xFF;                                               // (13) 0.0332
/*38  */     config[0x2d] = (vendor >> 8) & 0xFF;                                        // (9) 0.04297
/*40  */     config[0x2e] = vdev->device_id & 0xFF;                                      // (10) 0.04297
/*42  */     config[0x2f] = (vdev->device_id >> 8) & 0xFF;                               // (6) 0.05078
/*46  */     config[0x3d] = 1;                                                           // (17) 0.02539
/*50  */     if (vdev->nvectors && !msix_init(&proxy->pci_dev, vdev->nvectors, 1, 0)) {  // (4) 0.07227
/*52  */         pci_register_bar(&proxy->pci_dev, 1,                                    // (8) 0.04297
/*54  */                          msix_bar_size(&proxy->pci_dev),                        // (3) 0.07422
/*56  */                          PCI_BASE_ADDRESS_SPACE_MEMORY,                         // (1) 0.07812
/*58  */                          msix_mmio_map);                                        // 0.0
/*60  */     } else                                                                      // 0.0
/*62  */         vdev->nvectors = 0;                                                     // 0.0
/*66  */     proxy->pci_dev.config_write = virtio_write_config;                          // 0.0
/*70  */     size = VIRTIO_PCI_REGION_SIZE(&proxy->pci_dev) + vdev->config_len;          // 0.0
/*72  */     if (size & (size-1))                                                        // 0.0
/*74  */         size = 1 << qemu_fls(size);                                             // 0.0
/*78  */     pci_register_bar(&proxy->pci_dev, 0, size, PCI_BASE_ADDRESS_SPACE_IO,       // 0.0
/*80  */                            virtio_map);                                         // 0.0
/*84  */     if (!kvm_has_many_ioeventfds()) {                                           // 0.0
/*86  */         proxy->flags &= ~VIRTIO_PCI_FLAG_USE_IOEVENTFD;                         // 0.0
/*88  */     }                                                                           // 0.0
/*92  */     virtio_bind_device(vdev, &virtio_pci_bindings, proxy);                      // 0.0
/*94  */     proxy->host_features |= 0x1 << VIRTIO_F_NOTIFY_ON_EMPTY;                    // 0.0
/*96  */     proxy->host_features |= 0x1 << VIRTIO_F_BAD_FEATURE;                        // 0.0
/*98  */     proxy->host_features = vdev->get_features(vdev, proxy->host_features);      // 0.0
/*100 */ }                                                                               // 0.0
