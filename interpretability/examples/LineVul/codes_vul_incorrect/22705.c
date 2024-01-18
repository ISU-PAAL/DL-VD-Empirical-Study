// commit message qemu@7faa8075d8 (target=1, prob=0.15354663, correct=False): acpi_piix4: Fix PCI hotplug race
/*0  */ static void piix4_update_hotplug(PIIX4PMState *s)               // (6) 0.07519
/*2  */ {                                                               // (13) 0.003759
/*4  */     PCIDevice *dev = &s->dev;                                   // (9) 0.05639
/*6  */     BusState *bus = qdev_get_parent_bus(&dev->qdev);            // (4) 0.08271
/*8  */     DeviceState *qdev, *next;                                   // (10) 0.04511
/*12 */     s->pci0_hotplug_enable = ~0;                                // (7) 0.06391
/*16 */     QTAILQ_FOREACH_SAFE(qdev, &bus->children, sibling, next) {  // (2) 0.1015
/*18 */         PCIDevice *pdev = PCI_DEVICE(qdev);                     // (3) 0.08647
/*20 */         PCIDeviceClass *pc = PCI_DEVICE_GET_CLASS(pdev);        // (1) 0.1015
/*22 */         int slot = PCI_SLOT(pdev->devfn);                       // (5) 0.07895
/*26 */         if (pc->no_hotplug) {                                   // (8) 0.06391
/*28 */             s->pci0_hotplug_enable &= ~(1 << slot);             // (0) 0.109
/*30 */         }                                                       // (11) 0.03008
/*32 */     }                                                           // (12) 0.01504
/*34 */ }                                                               // (14) 0.003759
