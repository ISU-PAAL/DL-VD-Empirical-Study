// commit message qemu@5d1abf2344 (target=0, prob=0.07694895, correct=True): s390x/pci: enforce zPCI state checking
/*0  */ static void s390_pcihost_hot_plug(HotplugHandler *hotplug_dev,           // (9) 0.04297
/*2  */                                   DeviceState *dev, Error **errp)        // (2) 0.08398
/*4  */ {                                                                        // (16) 0.001953
/*6  */     PCIDevice *pci_dev = PCI_DEVICE(dev);                                // (10) 0.03906
/*8  */     S390PCIBusDevice *pbdev;                                             // (13) 0.02539
/*10 */     S390pciState *s = S390_PCI_HOST_BRIDGE(pci_device_root_bus(pci_dev)  // (3) 0.07422
/*12 */                                            ->qbus.parent);               // (1) 0.09375
/*16 */     pbdev = &s->pbdev[PCI_SLOT(pci_dev->devfn)];                         // (6) 0.05469
/*20 */     pbdev->fid = s390_pci_get_pfid(pci_dev);                             // (8) 0.05273
/*22 */     pbdev->pdev = pci_dev;                                               // (12) 0.02734
/*24 */     pbdev->configured = true;                                            // (15) 0.02344
/*26 */     pbdev->fh = s390_pci_get_pfh(pci_dev);                               // (7) 0.05273
/*30 */     s390_pcihost_setup_msix(pbdev);                                      // (11) 0.03516
/*34 */     if (dev->hotplugged) {                                               // (14) 0.02344
/*36 */         s390_pci_generate_plug_event(HP_EVENT_RESERVED_TO_STANDBY,       // (4) 0.07031
/*38 */                                      pbdev->fh, pbdev->fid);             // (0) 0.09766
/*40 */         s390_pci_generate_plug_event(HP_EVENT_TO_CONFIGURED,             // (5) 0.0625
/*42 */                                      pbdev->fh, pbdev->fid);             // 0.0
/*44 */     }                                                                    // 0.0
/*46 */ }                                                                        // 0.0
