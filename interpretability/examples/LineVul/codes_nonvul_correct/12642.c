// commit message qemu@2a1639291b (target=0, prob=0.008613226, correct=True): Remove a local subpage IO hack, now that general subpage IO works.
/*0  */ static void pxa2xx_pm_write(void *opaque, target_phys_addr_t addr,       // (6) 0.05187
/*2  */                 uint32_t value)                                          // (10) 0.04357
/*4  */ {                                                                        // (27) 0.002075
/*6  */     struct pxa2xx_state_s *s = (struct pxa2xx_state_s *) opaque;         // (3) 0.05809
/*8  */     if (addr > s->pm_base + PCMD31) {                                    // (11) 0.03734
/*10 */         /* Special case: PWRI2C registers appear in the same range.  */  // (8) 0.04979
/*12 */         pxa2xx_i2c_write(s->i2c[1], addr, value);                        // (1) 0.06224
/*14 */         return;                                                          // (16) 0.01867
/*16 */     }                                                                    // (25) 0.008299
/*18 */     addr -= s->pm_base;                                                  // (15) 0.02282
/*22 */     switch (addr) {                                                      // (20) 0.0166
/*24 */     case PMCR:                                                           // (23) 0.01452
/*26 */         s->pm_regs[addr >> 2] &= 0x15 & ~(value & 0x2a);                 // (0) 0.06846
/*28 */         s->pm_regs[addr >> 2] |= value & 0x15;                           // (5) 0.05394
/*30 */         break;                                                           // (17) 0.01867
/*34 */     case PSSR:	/* Read-clean registers */                                // (12) 0.03112
/*36 */     case RCSR:                                                           // (21) 0.0166
/*38 */     case PKSR:                                                           // (24) 0.01452
/*40 */         s->pm_regs[addr >> 2] &= ~value;                                 // (9) 0.04772
/*42 */         break;                                                           // (18) 0.01867
/*46 */     default:	/* Read-write registers */                                  // (14) 0.0249
/*48 */         if (addr >= PMCR && addr <= PCMD31 && !(addr & 3)) {             // (4) 0.05602
/*50 */             s->pm_regs[addr >> 2] = value;                               // (7) 0.05187
/*52 */             break;                                                       // (13) 0.02697
/*54 */         }                                                                // (22) 0.0166
/*58 */         printf("%s: Bad register " REG_FMT "\n", __FUNCTION__, addr);    // (2) 0.06224
/*60 */         break;                                                           // (19) 0.01867
/*62 */     }                                                                    // (26) 0.008299
/*64 */ }                                                                        // (28) 0.002075
