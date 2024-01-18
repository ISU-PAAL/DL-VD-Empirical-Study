// commit message qemu@a89f364ae8 (target=0, prob=0.007116855, correct=True): Replace all occurances of __FUNCTION__ with __func__
/*0  */ static uint64_t pxa2xx_mm_read(void *opaque, hwaddr addr,              // (2) 0.1116
/*2  */                                unsigned size)                          // (0) 0.1535
/*4  */ {                                                                      // (12) 0.004651
/*6  */     PXA2xxState *s = (PXA2xxState *) opaque;                           // (4) 0.1023
/*10 */     switch (addr) {                                                    // (8) 0.03721
/*12 */     case MDCNFG ... SA1110:                                            // (6) 0.06047
/*14 */         if ((addr & 3) == 0)                                           // (5) 0.07442
/*16 */             return s->mm_regs[addr >> 2];                              // (3) 0.107
/*20 */     default:                                                           // (10) 0.02326
/*22 */         printf("%s: Bad register " REG_FMT "\n", __FUNCTION__, addr);  // (1) 0.1395
/*24 */         break;                                                         // (7) 0.04186
/*26 */     }                                                                  // (11) 0.0186
/*28 */     return 0;                                                          // (9) 0.02791
/*30 */ }                                                                      // (13) 0.004651
