// commit message qemu@fa61718183 (target=1, prob=0.9992453, correct=True): scsi: Clean up duplicated error in legacy if=scsi code
/*0  */ static int esp_pci_scsi_init(PCIDevice *dev)                             // (8) 0.0377
/*2  */ {                                                                        // (26) 0.001984
/*4  */     PCIESPState *pci = PCI_ESP(dev);                                     // (11) 0.03571
/*6  */     DeviceState *d = DEVICE(dev);                                        // (16) 0.02579
/*8  */     ESPState *s = &pci->esp;                                             // (14) 0.02778
/*10 */     uint8_t *pci_conf;                                                   // (17) 0.02579
/*12 */     Error *err = NULL;                                                   // (21) 0.01786
/*16 */     pci_conf = dev->config;                                              // (20) 0.02183
/*20 */     /* Interrupt pin A */                                                // (22) 0.01786
/*22 */     pci_conf[PCI_INTERRUPT_PIN] = 0x01;                                  // (7) 0.04365
/*26 */     s->dma_memory_read = esp_pci_dma_memory_read;                        // (5) 0.04762
/*28 */     s->dma_memory_write = esp_pci_dma_memory_write;                      // (6) 0.04762
/*30 */     s->dma_opaque = pci;                                                 // (18) 0.02579
/*32 */     s->chip_id = TCHI_AM53C974;                                          // (9) 0.0377
/*34 */     memory_region_init_io(&pci->io, OBJECT(pci), &esp_pci_io_ops, pci,   // (1) 0.06746
/*36 */                           "esp-io", 0x80);                               // (2) 0.06746
/*40 */     pci_register_bar(dev, 0, PCI_BASE_ADDRESS_SPACE_IO, &pci->io);       // (3) 0.06548
/*42 */     s->irq = pci_allocate_irq(dev);                                      // (10) 0.03571
/*46 */     scsi_bus_new(&s->bus, sizeof(s->bus), d, &esp_pci_scsi_info, NULL);  // (0) 0.06944
/*48 */     if (!d->hotplugged) {                                                // (19) 0.02381
/*50 */         scsi_bus_legacy_handle_cmdline(&s->bus, &err);                   // (4) 0.05357
/*52 */         if (err != NULL) {                                               // (15) 0.02778
/*55 */             error_free(err);                                             // (12) 0.03373
/*57 */             return -1;                                                   // (13) 0.02976
/*59 */         }                                                                // (23) 0.01587
/*61 */     }                                                                    // (25) 0.007937
/*63 */     return 0;                                                            // (24) 0.0119
/*65 */ }                                                                        // (27) 0.001984
