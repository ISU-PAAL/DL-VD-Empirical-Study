// commit message qemu@e75ccf2c03 (target=0, prob=0.08621337, correct=True): virtio-pci.c: convert to PCIDEviceInfo to initialize ids
/*0  */ static int virtio_serial_init_pci(PCIDevice *pci_dev)                             // (12) 0.04297
/*2  */ {                                                                                 // (18) 0.001953
/*4  */     VirtIOPCIProxy *proxy = DO_UPCAST(VirtIOPCIProxy, pci_dev, pci_dev);          // (5) 0.0625
/*6  */     VirtIODevice *vdev;                                                           // (14) 0.02344
/*10 */     if (proxy->class_code != PCI_CLASS_COMMUNICATION_OTHER &&                     // (11) 0.04492
/*12 */         proxy->class_code != PCI_CLASS_DISPLAY_OTHER && /* qemu 0.10 */           // (6) 0.05859
/*14 */         proxy->class_code != PCI_CLASS_OTHERS)          /* qemu-kvm  */           // (2) 0.07422
/*16 */         proxy->class_code = PCI_CLASS_COMMUNICATION_OTHER;                        // (10) 0.04883
/*20 */     vdev = virtio_serial_init(&pci_dev->qdev, &proxy->serial);                    // (8) 0.05078
/*22 */     if (!vdev) {                                                                  // (16) 0.01758
/*24 */         return -1;                                                                // (15) 0.02148
/*26 */     }                                                                             // (17) 0.007812
/*28 */     vdev->nvectors = proxy->nvectors == DEV_NVECTORS_UNSPECIFIED                  // (9) 0.05078
/*30 */                                         ? proxy->serial.max_virtserial_ports + 1  // (0) 0.1035
/*32 */                                         : proxy->nvectors;                        // (1) 0.08984
/*34 */     virtio_init_pci(proxy, vdev,                                                  // (13) 0.03125
/*36 */                     PCI_VENDOR_ID_REDHAT_QUMRANET,                                // (3) 0.07227
/*38 */                     PCI_DEVICE_ID_VIRTIO_CONSOLE,                                 // (4) 0.06641
/*40 */                     proxy->class_code, 0x00);                                     // (7) 0.05664
/*42 */     proxy->nvectors = vdev->nvectors;                                             // 0.0
/*44 */     return 0;                                                                     // 0.0
/*46 */ }                                                                                 // 0.0
