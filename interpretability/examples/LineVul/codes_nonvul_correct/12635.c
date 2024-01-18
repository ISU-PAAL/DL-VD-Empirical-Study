// commit message qemu@f1c2dc7c86 (target=0, prob=0.041497968, correct=True): spapr-pci: rework MSI/MSIX
/*0  */ static void spapr_msi_write(void *opaque, hwaddr addr,     // (4) 0.1034
/*2  */                             uint64_t data, unsigned size)  // (0) 0.1773
/*4  */ {                                                          // (8) 0.004926
/*6  */     sPAPRPHBState *phb = opaque;                           // (6) 0.07882
/*8  */     int ndev = addr >> 16;                                 // (7) 0.05419
/*10 */     int vec = ((addr & 0xFFFF) >> 2) | data;               // (5) 0.0936
/*12 */     uint32_t irq = phb->msi_table[ndev].irq + vec;         // (2) 0.1281
/*16 */     trace_spapr_pci_msi_write(addr, data, irq);            // (3) 0.1182
/*20 */     qemu_irq_pulse(xics_get_qirq(spapr->icp, irq));        // (1) 0.1576
/*22 */ }                                                          // (9) 0.004926
