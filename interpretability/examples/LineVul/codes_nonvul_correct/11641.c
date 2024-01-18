// commit message qemu@da3e8a2349 (target=0, prob=0.1693767, correct=True): virtio-net: Move DEFINE_VIRTIO_NET_FEATURES to virtio-net
/*0  */ static void virtio_net_pci_realize(VirtIOPCIProxy *vpci_dev, Error **errp)  // (1) 0.1158
/*2  */ {                                                                           // (9) 0.003861
/*4  */     DeviceState *qdev = DEVICE(vpci_dev);                                   // (7) 0.06564
/*6  */     VirtIONetPCI *dev = VIRTIO_NET_PCI(vpci_dev);                           // (4) 0.09653
/*8  */     DeviceState *vdev = DEVICE(&dev->vdev);                                 // (8) 0.06564
/*12 */     virtio_net_set_config_size(&dev->vdev, vpci_dev->host_features);        // (2) 0.112
/*14 */     virtio_net_set_netclient_name(&dev->vdev, qdev->id,                     // (5) 0.09653
/*16 */                                   object_get_typename(OBJECT(qdev)));       // (0) 0.1853
/*18 */     qdev_set_parent_bus(vdev, BUS(&vpci_dev->bus));                         // (6) 0.09266
/*20 */     object_property_set_bool(OBJECT(vdev), true, "realized", errp);         // (3) 0.1004
/*22 */ }                                                                           // (10) 0.003861
