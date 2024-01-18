// commit message qemu@10c4c98ab7 (target=0, prob=0.00803351, correct=True): qdev: replace bus_type enum with bus_info struct.
/*0  */ void pci_qdev_register(PCIDeviceInfo *info)  // (2) 0.2078
/*2  */ {                                            // (5) 0.01299
/*4  */     info->qdev.init = pci_qdev_init;         // (1) 0.2208
/*6  */     info->qdev.bus_type = BUS_TYPE_PCI;      // (0) 0.2467
/*8  */     qdev_register(&info->qdev);              // (3) 0.1688
/*10 */ }                                            // (4) 0.01299
