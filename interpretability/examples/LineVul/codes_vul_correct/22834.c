// commit message qemu@a879125b47 (target=1, prob=0.90950406, correct=True): tests/libqos/pci-pc: Avoid shifting left into sign bit
/*0 */ static uint32_t qpci_pc_config_readl(QPCIBus *bus, int devfn, uint8_t offset)  // (0) 0.4074
/*2 */ {                                                                              // (3) 0.01235
/*4 */     outl(0xcf8, (1 << 31) | (devfn << 8) | offset);                            // (1) 0.3086
/*6 */     return inl(0xcfc);                                                         // (2) 0.1481
/*8 */ }                                                                              // (4) 0.01235
