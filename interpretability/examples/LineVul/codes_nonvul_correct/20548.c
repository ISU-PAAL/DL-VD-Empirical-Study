// commit message qemu@a8170e5e97 (target=0, prob=0.004954007, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static uint64_t lsi_mmio_read(void *opaque, target_phys_addr_t addr,  // (1) 0.2647
/*2  */                               unsigned size)                          // (0) 0.3137
/*4  */ {                                                                     // (4) 0.009804
/*6  */     LSIState *s = opaque;                                             // (3) 0.1078
/*10 */     return lsi_reg_readb(s, addr & 0xff);                             // (2) 0.1863
/*12 */ }                                                                     // (5) 0.009804
