// commit message qemu@ba737541ed (target=1, prob=0.5280196, correct=True): acpi_piix4: Disallow write to up/down PCI hotplug registers
/*0  */ static uint32_t pcihotplug_read(void *opaque, uint32_t addr)  // (1) 0.09692
/*2  */ {                                                             // (15) 0.004405
/*4  */     uint32_t val = 0;                                         // (10) 0.04846
/*6  */     struct pci_status *g = opaque;                            // (9) 0.05286
/*8  */     switch (addr) {                                           // (12) 0.03524
/*10 */         case PCI_BASE:                                        // (5) 0.05727
/*12 */             val = g->up;                                      // (2) 0.07489
/*14 */             break;                                            // (6) 0.05727
/*16 */         case PCI_BASE + 4:                                    // (4) 0.06608
/*18 */             val = g->down;                                    // (3) 0.07489
/*20 */             break;                                            // (7) 0.05727
/*22 */         default:                                              // (11) 0.03965
/*24 */             break;                                            // (8) 0.05727
/*26 */     }                                                         // (14) 0.01762
/*30 */     PIIX4_DPRINTF("pcihotplug read %x == %x\n", addr, val);   // (0) 0.1322
/*32 */     return val;                                               // (13) 0.02643
/*34 */ }                                                             // (16) 0.004405
