// commit message qemu@b4ba67d9a7 (target=1, prob=0.9970511, correct=True): libqos: Change PCI accessors to take opaque BAR handle
/*0  */ static void start_tco(const TestData *d)                     // (3) 0.1083
/*2  */ {                                                            // (5) 0.008333
/*4  */     uint32_t val;                                            // (4) 0.075
/*8  */     val = qpci_io_readw(d->dev, d->tco_io_base + TCO1_CNT);  // (0) 0.2833
/*10 */     val &= ~TCO_TMR_HLT;                                     // (2) 0.1333
/*12 */     qpci_io_writew(d->dev, d->tco_io_base + TCO1_CNT, val);  // (1) 0.2833
/*14 */ }                                                            // (6) 0.008333
