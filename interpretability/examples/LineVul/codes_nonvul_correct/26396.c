// commit message qemu@a8170e5e97 (target=0, prob=0.0062332437, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static void intel_hda_mmio_writel(void *opaque, target_phys_addr_t addr, uint32_t val)  // (0) 0.3143
/*2  */ {                                                                                       // (4) 0.009524
/*4  */     IntelHDAState *d = opaque;                                                          // (3) 0.1143
/*6  */     const IntelHDAReg *reg = intel_hda_reg_find(d, addr);                               // (1) 0.2286
/*10 */     intel_hda_reg_write(d, reg, val, 0xffffffff);                                       // (2) 0.219
/*12 */ }                                                                                       // (5) 0.009524
