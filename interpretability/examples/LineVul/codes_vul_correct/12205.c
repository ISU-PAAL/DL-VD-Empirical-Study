// commit message qemu@b4ba67d9a7 (target=1, prob=0.99758947, correct=True): libqos: Change PCI accessors to take opaque BAR handle
/*0  */ static void stop_tco(const TestData *d)                      // (3) 0.1092
/*2  */ {                                                            // (5) 0.008403
/*4  */     uint32_t val;                                            // (4) 0.07563
/*8  */     val = qpci_io_readw(d->dev, d->tco_io_base + TCO1_CNT);  // (0) 0.2857
/*10 */     val |= TCO_TMR_HLT;                                      // (2) 0.1261
/*12 */     qpci_io_writew(d->dev, d->tco_io_base + TCO1_CNT, val);  // (1) 0.2857
/*14 */ }                                                            // (6) 0.008403
