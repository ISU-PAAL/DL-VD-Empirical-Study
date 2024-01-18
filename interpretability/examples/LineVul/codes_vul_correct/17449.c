// commit message qemu@b4ba67d9a7 (target=1, prob=0.99327844, correct=True): libqos: Change PCI accessors to take opaque BAR handle
/*0  */ void qpci_memread(QPCIDevice *dev, void *data, void *buf, size_t len)  // (0) 0.2929
/*2  */ {                                                                      // (4) 0.0101
/*4  */     uintptr_t addr = (uintptr_t)data;                                  // (3) 0.1717
/*8  */     g_assert(addr >= QPCI_PIO_LIMIT);                                  // (2) 0.202
/*10 */     dev->bus->memread(dev->bus, addr, buf, len);                       // (1) 0.202
/*12 */ }                                                                      // (5) 0.0101
