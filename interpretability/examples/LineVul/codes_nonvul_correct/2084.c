// commit message qemu@a8170e5e97 (target=0, prob=0.009768578, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static void omap_pwt_write(void *opaque, target_phys_addr_t addr,              // (8) 0.04688
/*2  */                            uint64_t value, unsigned size)                      // (5) 0.06836
/*4  */ {                                                                              // (19) 0.001953
/*6  */     struct omap_pwt_s *s = (struct omap_pwt_s *) opaque;                       // (6) 0.05078
/*8  */     int offset = addr & OMAP_MPUI_REG_MASK;                                    // (9) 0.03906
/*12 */     if (size != 1) {                                                           // (15) 0.01953
/*14 */         return omap_badwidth_write8(opaque, addr, value);                      // (7) 0.04688
/*16 */     }                                                                          // (18) 0.007812
/*20 */     switch (offset) {                                                          // (17) 0.01562
/*22 */     case 0x00:	/* FRC */                                                       // (13) 0.02539
/*24 */         s->frc = value & 0x3f;                                                 // (11) 0.03711
/*26 */         break;                                                                 // (16) 0.01758
/*28 */     case 0x04:	/* VRC */                                                       // (14) 0.02539
/*30 */         if ((value ^ s->vrc) & 1) {                                            // (10) 0.03906
/*32 */             if (value & 1)                                                     // (12) 0.0332
/*34 */                 printf("%s: %iHz buzz on\n", __FUNCTION__, (int)               // (4) 0.07227
/*36 */                                 /* 1.5 MHz from a 12-MHz or 13-MHz PWT_CLK */  // (0) 0.09961
/*38 */                                 ((omap_clk_getrate(s->clk) >> 3) /             // (1) 0.09766
/*40 */                                  /* Pre-multiplexer divider */                 // (3) 0.08008
/*42 */                                  ((s->gcr & 2) ? 1 : 154) /                    // (2) 0.08984
/*44 */                                  /* Octave multiplexer */                      // 0.0
/*46 */                                  (2 << (value & 3)) *                          // 0.0
/*48 */                                  /* 101/107 divider */                         // 0.0
/*50 */                                  ((value & (1 << 2)) ? 101 : 107) *            // 0.0
/*52 */                                  /*  49/55 divider */                          // 0.0
/*54 */                                  ((value & (1 << 3)) ?  49 : 55) *             // 0.0
/*56 */                                  /*  50/63 divider */                          // 0.0
/*58 */                                  ((value & (1 << 4)) ?  50 : 63) *             // 0.0
/*60 */                                  /*  80/127 divider */                         // 0.0
/*62 */                                  ((value & (1 << 5)) ?  80 : 127) /            // 0.0
/*64 */                                  (107 * 55 * 63 * 127)));                      // 0.0
/*66 */             else                                                               // 0.0
/*68 */                 printf("%s: silence!\n", __FUNCTION__);                        // 0.0
/*70 */         }                                                                      // 0.0
/*72 */         s->vrc = value & 0x7f;                                                 // 0.0
/*74 */         break;                                                                 // 0.0
/*76 */     case 0x08:	/* GCR */                                                       // 0.0
/*78 */         s->gcr = value & 3;                                                    // 0.0
/*80 */         break;                                                                 // 0.0
/*82 */     default:                                                                   // 0.0
/*84 */         OMAP_BAD_REG(addr);                                                    // 0.0
/*86 */         return;                                                                // 0.0
/*88 */     }                                                                          // 0.0
/*90 */ }                                                                              // 0.0
