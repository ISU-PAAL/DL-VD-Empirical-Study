// commit message qemu@25db9ebe15 (target=0, prob=0.029653596, correct=True): virtio-pci: Use ioeventfd for virtqueue notify
/*0  */ static void virtio_pci_reset(DeviceState *d)                                // (1) 0.1579
/*2  */ {                                                                           // (5) 0.01053
/*4  */     VirtIOPCIProxy *proxy = container_of(d, VirtIOPCIProxy, pci_dev.qdev);  // (0) 0.3158
/*6  */     virtio_reset(proxy->vdev);                                              // (3) 0.1368
/*8  */     msix_reset(&proxy->pci_dev);                                            // (2) 0.1579
/*10 */     proxy->flags = 0;                                                       // (4) 0.09474
/*12 */ }                                                                           // (6) 0.01053
