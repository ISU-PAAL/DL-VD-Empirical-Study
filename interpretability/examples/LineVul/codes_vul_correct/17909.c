// commit message qemu@b4ba67d9a7 (target=1, prob=0.9963659, correct=True): libqos: Change PCI accessors to take opaque BAR handle
/*0  */ void qvirtio_pci_device_enable(QVirtioPCIDevice *d)  // (0) 0.2644
/*2  */ {                                                    // (4) 0.01149
/*4  */     qpci_device_enable(d->pdev);                     // (2) 0.1839
/*6  */     d->addr = qpci_iomap(d->pdev, 0, NULL);          // (1) 0.2644
/*8  */     g_assert(d->addr != NULL);                       // (3) 0.1494
/*10 */ }                                                    // (5) 0.01149
