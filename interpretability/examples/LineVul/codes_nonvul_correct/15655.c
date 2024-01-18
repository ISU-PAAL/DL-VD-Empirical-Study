// commit message qemu@a8170e5e97 (target=0, prob=0.005940166, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ e1000_mmio_read(void *opaque, target_phys_addr_t addr, unsigned size)  // (1) 0.1613
/*2  */ {                                                                      // (9) 0.006452
/*4  */     E1000State *s = opaque;                                            // (5) 0.07097
/*6  */     unsigned int index = (addr & 0x1ffff) >> 2;                        // (4) 0.1161
/*10 */     if (index < NREADOPS && macreg_readops[index])                     // (3) 0.1226
/*12 */     {                                                                  // (7) 0.02581
/*14 */         return macreg_readops[index](s, index);                        // (2) 0.129
/*16 */     }                                                                  // (8) 0.02581
/*18 */     DBGOUT(UNKNOWN, "MMIO unknown read addr=0x%08x\n", index<<2);      // (0) 0.1935
/*20 */     return 0;                                                          // (6) 0.03871
/*22 */ }                                                                      // (10) 0.006452
