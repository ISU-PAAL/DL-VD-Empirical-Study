// commit message qemu@2e2aa31674 (target=0, prob=0.4734007, correct=True): mptsas: remove unnecessary internal msi state flag
/*0   */ static void mptsas_scsi_init(PCIDevice *dev, Error **errp)                       // (6) 0.04688
/*2   */ {                                                                                // (24) 0.001953
/*4   */     DeviceState *d = DEVICE(dev);                                                // (19) 0.02539
/*6   */     MPTSASState *s = MPT_SAS(dev);                                               // (15) 0.03516
/*8   */     Error *err = NULL;                                                           // (22) 0.01758
/*10  */     int ret;                                                                     // (23) 0.01172
/*14  */     dev->config[PCI_LATENCY_TIMER] = 0;                                          // (11) 0.04102
/*16  */     dev->config[PCI_INTERRUPT_PIN] = 0x01;                                       // (8) 0.04297
/*20  */     if (s->msi != ON_OFF_AUTO_OFF) {                                             // (13) 0.03906
/*22  */         ret = msi_init(dev, 0, 1, true, false, &err);                            // (2) 0.05273
/*24  */         /* Any error other than -ENOTSUP(board's MSI support is broken)          // (7) 0.04688
/*26  */          * is a programming error */                                             // (17) 0.02734
/*28  */         assert(!ret || ret == -ENOTSUP);                                         // (14) 0.03711
/*30  */         if (ret && s->msi == ON_OFF_AUTO_ON) {                                   // (3) 0.05078
/*32  */             /* Can't satisfy user's explicit msi=on request, fail */             // (4) 0.05078
/*34  */             error_append_hint(&err, "You have to use msi=auto (default) or "     // (0) 0.06641
/*36  */                     "msi=off with this machine type.\n");                        // (1) 0.0625
/*38  */             error_propagate(errp, err);                                          // (12) 0.04102
/*40  */             s->msi_in_use = false;                                               // (9) 0.04297
/*42  */             return;                                                              // (20) 0.02539
/*44  */         } else if (ret) {                                                        // (18) 0.02734
/*46  */             /* With msi=auto, we fall back to MSI off silently */                // (5) 0.05078
/*48  */             error_free(err);                                                     // (16) 0.0332
/*50  */             s->msi_in_use = false;                                               // (10) 0.04297
/*52  */         } else {                                                                 // (21) 0.01953
/*54  */             s->msi_in_use = true;                                                // 0.0
/*56  */         }                                                                        // 0.0
/*58  */     }                                                                            // 0.0
/*62  */     memory_region_init_io(&s->mmio_io, OBJECT(s), &mptsas_mmio_ops, s,           // 0.0
/*64  */                           "mptsas-mmio", 0x4000);                                // 0.0
/*66  */     memory_region_init_io(&s->port_io, OBJECT(s), &mptsas_port_ops, s,           // 0.0
/*68  */                           "mptsas-io", 256);                                     // 0.0
/*70  */     memory_region_init_io(&s->diag_io, OBJECT(s), &mptsas_diag_ops, s,           // 0.0
/*72  */                           "mptsas-diag", 0x10000);                               // 0.0
/*76  */     pci_register_bar(dev, 0, PCI_BASE_ADDRESS_SPACE_IO, &s->port_io);            // 0.0
/*78  */     pci_register_bar(dev, 1, PCI_BASE_ADDRESS_SPACE_MEMORY |                     // 0.0
/*80  */                                  PCI_BASE_ADDRESS_MEM_TYPE_32, &s->mmio_io);     // 0.0
/*82  */     pci_register_bar(dev, 2, PCI_BASE_ADDRESS_SPACE_MEMORY |                     // 0.0
/*84  */                                  PCI_BASE_ADDRESS_MEM_TYPE_32, &s->diag_io);     // 0.0
/*88  */     if (!s->sas_addr) {                                                          // 0.0
/*90  */         s->sas_addr = ((NAA_LOCALLY_ASSIGNED_ID << 24) |                         // 0.0
/*92  */                        IEEE_COMPANY_LOCALLY_ASSIGNED) << 36;                     // 0.0
/*94  */         s->sas_addr |= (pci_bus_num(dev->bus) << 16);                            // 0.0
/*96  */         s->sas_addr |= (PCI_SLOT(dev->devfn) << 8);                              // 0.0
/*98  */         s->sas_addr |= PCI_FUNC(dev->devfn);                                     // 0.0
/*100 */     }                                                                            // 0.0
/*102 */     s->max_devices = MPTSAS_NUM_PORTS;                                           // 0.0
/*106 */     s->request_bh = qemu_bh_new(mptsas_fetch_requests, s);                       // 0.0
/*110 */     QTAILQ_INIT(&s->pending);                                                    // 0.0
/*114 */     scsi_bus_new(&s->bus, sizeof(s->bus), &dev->qdev, &mptsas_scsi_info, NULL);  // 0.0
/*116 */     if (!d->hotplugged) {                                                        // 0.0
/*118 */         scsi_bus_legacy_handle_cmdline(&s->bus, errp);                           // 0.0
/*120 */     }                                                                            // 0.0
/*122 */ }                                                                                // 0.0
