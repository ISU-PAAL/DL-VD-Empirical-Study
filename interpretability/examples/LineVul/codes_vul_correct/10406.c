// commit message qemu@a01d8cadad (target=1, prob=0.61265105, correct=True): Fix memory corruption reported by Julian Seward   (still more bugs to fix in PreP emulation).
/*0  */ PCIBus *pci_prep_init(qemu_irq *pic)                                      // (13) 0.03906
/*2  */ {                                                                         // (18) 0.001953
/*4  */     PREPPCIState *s;                                                      // (14) 0.02148
/*6  */     PCIDevice *d;                                                         // (16) 0.01953
/*8  */     int PPC_io_memory;                                                    // (15) 0.02148
/*12 */     s = qemu_mallocz(sizeof(PREPPCIState));                               // (12) 0.04297
/*14 */     s->bus = pci_register_bus(prep_set_irq, prep_map_irq, pic, 0, 2);     // (1) 0.06445
/*18 */     register_ioport_write(0xcf8, 4, 4, pci_prep_addr_writel, s);          // (4) 0.05859
/*20 */     register_ioport_read(0xcf8, 4, 4, pci_prep_addr_readl, s);            // (5) 0.05859
/*24 */     register_ioport_write(0xcfc, 4, 1, pci_host_data_writeb, s);          // (7) 0.05859
/*26 */     register_ioport_write(0xcfc, 4, 2, pci_host_data_writew, s);          // (9) 0.05859
/*28 */     register_ioport_write(0xcfc, 4, 4, pci_host_data_writel, s);          // (2) 0.05859
/*30 */     register_ioport_read(0xcfc, 4, 1, pci_host_data_readb, s);            // (8) 0.05859
/*32 */     register_ioport_read(0xcfc, 4, 2, pci_host_data_readw, s);            // (10) 0.05859
/*34 */     register_ioport_read(0xcfc, 4, 4, pci_host_data_readl, s);            // (6) 0.05859
/*38 */     PPC_io_memory = cpu_register_io_memory(0, PPC_PCIIO_read,             // (11) 0.05664
/*40 */                                            PPC_PCIIO_write, s);           // (0) 0.1035
/*42 */     cpu_register_physical_memory(0x80800000, 0x00400000, PPC_io_memory);  // (3) 0.05859
/*46 */     /* PCI host bridge */                                                 // (17) 0.01563
/*48 */     d = pci_register_device(s->bus, "PREP Host Bridge - Motorola Raven",  // 0.0
/*50 */                             sizeof(PCIDevice), 0, NULL, NULL);            // 0.0
/*52 */     d->config[0x00] = 0x57; // vendor_id : Motorola                       // 0.0
/*54 */     d->config[0x01] = 0x10;                                               // 0.0
/*56 */     d->config[0x02] = 0x01; // device_id : Raven                          // 0.0
/*58 */     d->config[0x03] = 0x48;                                               // 0.0
/*60 */     d->config[0x08] = 0x00; // revision                                   // 0.0
/*62 */     d->config[0x0A] = 0x00; // class_sub = pci host                       // 0.0
/*64 */     d->config[0x0B] = 0x06; // class_base = PCI_bridge                    // 0.0
/*66 */     d->config[0x0C] = 0x08; // cache_line_size                            // 0.0
/*68 */     d->config[0x0D] = 0x10; // latency_timer                              // 0.0
/*70 */     d->config[0x0E] = 0x00; // header_type                                // 0.0
/*72 */     d->config[0x34] = 0x00; // capabilities_pointer                       // 0.0
/*76 */     return s->bus;                                                        // 0.0
/*78 */ }                                                                         // 0.0
