// commit message qemu@0919ac7876 (target=0, prob=0.0051632766, correct=True): omap_intc: Qdevify
/*0  */ static uint64_t omap_ulpd_pm_read(void *opaque, target_phys_addr_t addr,  // (3) 0.05664
/*2  */                                   unsigned size)                          // (0) 0.07031
/*4  */ {                                                                         // (26) 0.001953
/*6  */     struct omap_mpu_state_s *s = (struct omap_mpu_state_s *) opaque;      // (2) 0.05859
/*8  */     uint16_t ret;                                                         // (23) 0.01758
/*12 */     if (size != 2) {                                                      // (22) 0.01953
/*14 */         return omap_badwidth_read16(opaque, addr);                        // (9) 0.04297
/*16 */     }                                                                     // (25) 0.007812
/*20 */     switch (addr) {                                                       // (24) 0.01562
/*22 */     case 0x14:	/* IT_STATUS */                                            // (15) 0.0293
/*24 */         ret = s->ulpd_pm_regs[addr >> 2];                                 // (7) 0.04492
/*26 */         s->ulpd_pm_regs[addr >> 2] = 0;                                   // (5) 0.04688
/*28 */         qemu_irq_lower(s->irq[1][OMAP_INT_GAUGE_32K]);                    // (1) 0.06641
/*30 */         return ret;                                                       // (21) 0.01953
/*34 */     case 0x18:	/* Reserved */                                             // (18) 0.02344
/*36 */     case 0x1c:	/* Reserved */                                             // (16) 0.02539
/*38 */     case 0x20:	/* Reserved */                                             // (19) 0.02344
/*40 */     case 0x28:	/* Reserved */                                             // (20) 0.02344
/*42 */     case 0x2c:	/* Reserved */                                             // (17) 0.02539
/*44 */         OMAP_BAD_REG(addr);                                               // (12) 0.0332
/*46 */     case 0x00:	/* COUNTER_32_LSB */                                       // (10) 0.03516
/*48 */     case 0x04:	/* COUNTER_32_MSB */                                       // (11) 0.03516
/*50 */     case 0x08:	/* COUNTER_HIGH_FREQ_LSB */                                // (8) 0.04492
/*52 */     case 0x0c:	/* COUNTER_HIGH_FREQ_MSB */                                // (6) 0.04688
/*54 */     case 0x10:	/* GAUGING_CTRL */                                         // (13) 0.0332
/*56 */     case 0x24:	/* SETUP_ANALOG_CELL3_ULPD1 */                             // (4) 0.04883
/*58 */     case 0x30:	/* CLOCK_CTRL */                                           // (14) 0.03125
/*60 */     case 0x34:	/* SOFT_REQ */                                             // 0.0
/*62 */     case 0x38:	/* COUNTER_32_FIQ */                                       // 0.0
/*64 */     case 0x3c:	/* DPLL_CTRL */                                            // 0.0
/*66 */     case 0x40:	/* STATUS_REQ */                                           // 0.0
/*68 */         /* XXX: check clk::usecount state for every clock */              // 0.0
/*70 */     case 0x48:	/* LOCL_TIME */                                            // 0.0
/*72 */     case 0x4c:	/* APLL_CTRL */                                            // 0.0
/*74 */     case 0x50:	/* POWER_CTRL */                                           // 0.0
/*76 */         return s->ulpd_pm_regs[addr >> 2];                                // 0.0
/*78 */     }                                                                     // 0.0
/*82 */     OMAP_BAD_REG(addr);                                                   // 0.0
/*84 */     return 0;                                                             // 0.0
/*86 */ }                                                                         // 0.0
