// commit message qemu@caae58cba0 (target=1, prob=0.018273523, correct=False): pseries: Improve handling of multiple PCI host bridges
/*0  */ static void pci_spapr_set_irq(void *opaque, int irq_num, int level)               // (2) 0.1444
/*2  */ {                                                                                 // (8) 0.005348
/*4  */     /*                                                                            // (7) 0.02139
/*6  */      * Here we use the number returned by pci_spapr_map_irq to find a             // (3) 0.1337
/*8  */      * corresponding qemu_irq.                                                    // (5) 0.06952
/*10 */      */                                                                           // (6) 0.02674
/*12 */     sPAPRPHBState *phb = opaque;                                                  // (4) 0.08556
/*16 */     trace_spapr_pci_lsi_set(phb->busname, irq_num, phb->lsi_table[irq_num].irq);  // (0) 0.2353
/*18 */     qemu_set_irq(spapr_phb_lsi_qirq(phb, irq_num), level);                        // (1) 0.1925
/*20 */ }                                                                                 // (9) 0.005348
