// commit message qemu@786a4ea82e (target=0, prob=0.24450317, correct=True): Convert (ffs(val) - 1) to ctz32(val)
/*0 */ static inline unsigned int msi_nr_vectors(uint16_t flags)                   // (1) 0.2338
/*2 */ {                                                                           // (3) 0.01299
/*4 */     return 1U <<                                                            // (2) 0.09091
/*6 */         ((flags & PCI_MSI_FLAGS_QSIZE) >> (ffs(PCI_MSI_FLAGS_QSIZE) - 1));  // (0) 0.5325
/*8 */ }                                                                           // (4) 0.01299
