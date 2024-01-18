// commit message qemu@1108b2f8a9 (target=1, prob=0.8033989, correct=True): pci: Convert msi_init() to Error and fix callers to check it
/*0  */ static void mptsas_scsi_init(PCIDevice *dev, Error **errp)                       // (9) 0.04688
/*2  */ {                                                                                // (18) 0.001953
/*4  */     DeviceState *d = DEVICE(dev);                                                // (16) 0.02539
/*6  */     MPTSASState *s = MPT_SAS(dev);                                               // (13) 0.03516
/*10 */     dev->config[PCI_LATENCY_TIMER] = 0;                                          // (11) 0.04102
/*12 */     dev->config[PCI_INTERRUPT_PIN] = 0x01;                                       // (10) 0.04297
/*16 */     memory_region_init_io(&s->mmio_io, OBJECT(s), &mptsas_mmio_ops, s,           // (2) 0.07031
/*18 */                           "mptsas-mmio", 0x4000);                                // (0) 0.07422
/*20 */     memory_region_init_io(&s->port_io, OBJECT(s), &mptsas_port_ops, s,           // (5) 0.06641
/*22 */                           "mptsas-io", 256);                                     // (4) 0.06836
/*24 */     memory_region_init_io(&s->diag_io, OBJECT(s), &mptsas_diag_ops, s,           // (3) 0.07031
/*26 */                           "mptsas-diag", 0x10000);                               // (1) 0.07422
/*30 */     if (s->msi != ON_OFF_AUTO_OFF &&                                             // (12) 0.03711
/*32 */         msi_init(dev, 0, 1, true, false) >= 0) {                                 // (8) 0.05078
/*34 */         /* TODO check for errors */                                              // (15) 0.02734
/*36 */         s->msi_in_use = true;                                                    // (14) 0.03516
/*38 */     }                                                                            // (17) 0.007812
/*42 */     pci_register_bar(dev, 0, PCI_BASE_ADDRESS_SPACE_IO, &s->port_io);            // (6) 0.06641
/*44 */     pci_register_bar(dev, 1, PCI_BASE_ADDRESS_SPACE_MEMORY |                     // (7) 0.05664
/*46 */                                  PCI_BASE_ADDRESS_MEM_TYPE_32, &s->mmio_io);     // 0.0
/*48 */     pci_register_bar(dev, 2, PCI_BASE_ADDRESS_SPACE_MEMORY |                     // 0.0
/*50 */                                  PCI_BASE_ADDRESS_MEM_TYPE_32, &s->diag_io);     // 0.0
/*54 */     if (!s->sas_addr) {                                                          // 0.0
/*56 */         s->sas_addr = ((NAA_LOCALLY_ASSIGNED_ID << 24) |                         // 0.0
/*58 */                        IEEE_COMPANY_LOCALLY_ASSIGNED) << 36;                     // 0.0
/*60 */         s->sas_addr |= (pci_bus_num(dev->bus) << 16);                            // 0.0
/*62 */         s->sas_addr |= (PCI_SLOT(dev->devfn) << 8);                              // 0.0
/*64 */         s->sas_addr |= PCI_FUNC(dev->devfn);                                     // 0.0
/*66 */     }                                                                            // 0.0
/*68 */     s->max_devices = MPTSAS_NUM_PORTS;                                           // 0.0
/*72 */     s->request_bh = qemu_bh_new(mptsas_fetch_requests, s);                       // 0.0
/*76 */     QTAILQ_INIT(&s->pending);                                                    // 0.0
/*80 */     scsi_bus_new(&s->bus, sizeof(s->bus), &dev->qdev, &mptsas_scsi_info, NULL);  // 0.0
/*82 */     if (!d->hotplugged) {                                                        // 0.0
/*84 */         scsi_bus_legacy_handle_cmdline(&s->bus, errp);                           // 0.0
/*86 */     }                                                                            // 0.0
/*88 */ }                                                                                // 0.0
