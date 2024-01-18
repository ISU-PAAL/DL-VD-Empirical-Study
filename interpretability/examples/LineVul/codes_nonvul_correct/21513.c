// commit message qemu@b2bedb2144 (target=0, prob=0.010133367, correct=True): Remove blanks before \n in output strings
/*0  */ static uint32_t bonito_readl(void *opaque, target_phys_addr_t addr)  // (1) 0.1381
/*2  */ {                                                                    // (11) 0.005525
/*4  */     PCIBonitoState *s = opaque;                                      // (5) 0.07182
/*6  */     uint32_t saddr;                                                  // (7) 0.05525
/*10 */     saddr = (addr - BONITO_REGBASE) >> 2;                            // (2) 0.116
/*14 */     DPRINTF("bonito_readl "TARGET_FMT_plx"  \n", addr);              // (0) 0.1547
/*16 */     switch (saddr) {                                                 // (8) 0.04972
/*18 */     case BONITO_INTISR:                                              // (6) 0.07182
/*20 */         return s->regs[saddr];                                       // (3) 0.0884
/*22 */     default:                                                         // (9) 0.02762
/*24 */         return s->regs[saddr];                                       // (4) 0.0884
/*26 */     }                                                                // (10) 0.0221
/*28 */ }                                                                    // (12) 0.005525
