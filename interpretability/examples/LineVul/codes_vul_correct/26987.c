// commit message qemu@ad0ebb91cd (target=1, prob=0.82809865, correct=True): pseries: Convert sPAPR TCEs to use generic IOMMU infrastructure
/*0 */ void stq_tce(VIOsPAPRDevice *dev, uint64_t taddr, uint64_t val)  // (0) 0.375
/*2 */ {                                                                // (3) 0.0125
/*4 */     val = tswap64(val);                                          // (2) 0.15
/*6 */     spapr_tce_dma_write(dev, taddr, &val, sizeof(val));          // (1) 0.3375
/*8 */ }                                                                // (4) 0.0125
