// commit message qemu@a5cf8262e4 (target=0, prob=0.044481743, correct=True): scsi, pci, qdev, isa-bus, sysbus: don't let *_get_fw_dev_path return NULL
/*0  */ static char *pcibus_get_fw_dev_path(DeviceState *dev)                         // (4) 0.08796
/*2  */ {                                                                             // (10) 0.00463
/*4  */     PCIDevice *d = (PCIDevice *)dev;                                          // (5) 0.08333
/*6  */     char path[50], name[33];                                                  // (7) 0.05556
/*8  */     int off;                                                                  // (9) 0.02778
/*12 */     off = snprintf(path, sizeof(path), "%s@%x",                               // (3) 0.09259
/*14 */                    pci_dev_fw_name(dev, name, sizeof name),                   // (1) 0.1528
/*16 */                    PCI_SLOT(d->devfn));                                       // (2) 0.1296
/*18 */     if (PCI_FUNC(d->devfn))                                                   // (6) 0.07407
/*20 */         snprintf(path + off, sizeof(path) + off, ",%x", PCI_FUNC(d->devfn));  // (0) 0.162
/*22 */     return strdup(path);                                                      // (8) 0.0463
/*24 */ }                                                                             // (11) 0.00463
