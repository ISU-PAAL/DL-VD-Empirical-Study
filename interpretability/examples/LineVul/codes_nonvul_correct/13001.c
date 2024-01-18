// commit message qemu@9a4c0e220d (target=0, prob=0.24842322, correct=True): hw/virtio-pci: fix virtio behaviour
/*0  */ static void virtio_input_pci_realize(VirtIOPCIProxy *vpci_dev, Error **errp)  // (0) 0.1429
/*2  */ {                                                                             // (8) 0.004762
/*4  */     VirtIOInputPCI *vinput = VIRTIO_INPUT_PCI(vpci_dev);                      // (3) 0.1286
/*6  */     DeviceState *vdev = DEVICE(&vinput->vdev);                                // (6) 0.08571
/*10 */     qdev_set_parent_bus(vdev, BUS(&vpci_dev->bus));                           // (5) 0.1143
/*12 */     /* force virtio-1.0 */                                                    // (7) 0.05714
/*14 */     vpci_dev->flags &= ~VIRTIO_PCI_FLAG_DISABLE_MODERN;                       // (1) 0.1333
/*16 */     vpci_dev->flags |= VIRTIO_PCI_FLAG_DISABLE_LEGACY;                        // (2) 0.1333
/*18 */     object_property_set_bool(OBJECT(vdev), true, "realized", errp);           // (4) 0.1238
/*20 */ }                                                                             // (9) 0.004762
