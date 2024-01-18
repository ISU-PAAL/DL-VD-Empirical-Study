// commit message qemu@a8170e5e97 (target=0, prob=0.0060694916, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static void intel_hda_mmio_writeb(void *opaque, target_phys_addr_t addr, uint32_t val)  // (0) 0.3204
/*2  */ {                                                                                       // (4) 0.009709
/*4  */     IntelHDAState *d = opaque;                                                          // (3) 0.1165
/*6  */     const IntelHDAReg *reg = intel_hda_reg_find(d, addr);                               // (1) 0.233
/*10 */     intel_hda_reg_write(d, reg, val, 0xff);                                             // (2) 0.2039
/*12 */ }                                                                                       // (5) 0.009709
