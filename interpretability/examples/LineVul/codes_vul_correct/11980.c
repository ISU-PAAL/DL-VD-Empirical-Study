// commit message qemu@a879125b47 (target=1, prob=0.9255185, correct=True): tests/libqos/pci-pc: Avoid shifting left into sign bit
/*0 */ static void qpci_pc_config_writew(QPCIBus *bus, int devfn, uint8_t offset, uint16_t value)  // (0) 0.4235
/*2 */ {                                                                                           // (3) 0.01176
/*4 */     outl(0xcf8, (1 << 31) | (devfn << 8) | offset);                                         // (1) 0.2941
/*6 */     outw(0xcfc, value);                                                                     // (2) 0.1529
/*8 */ }                                                                                           // (4) 0.01176
