// commit message qemu@a89f364ae8 (target=0, prob=0.22208884, correct=True): Replace all occurances of __FUNCTION__ with __func__
/*0   */ static uint64_t pxa2xx_gpio_read(void *opaque, hwaddr offset,                // (4) 0.04883
/*2   */                                  unsigned size)                              // (2) 0.06836
/*4   */ {                                                                            // (25) 0.001953
/*6   */     PXA2xxGPIOInfo *s = (PXA2xxGPIOInfo *) opaque;                           // (3) 0.05078
/*8   */     uint32_t ret;                                                            // (23) 0.01758
/*10  */     int bank;                                                                // (24) 0.01172
/*12  */     if (offset >= 0x200)                                                     // (19) 0.02148
/*14  */         return 0;                                                            // (20) 0.01953
/*18  */     bank = pxa2xx_gpio_regs[offset].bank;                                    // (8) 0.03906
/*20  */     switch (pxa2xx_gpio_regs[offset].reg) {                                  // (7) 0.04102
/*22  */     case GPDR:		/* GPIO Pin-Direction registers */                           // (9) 0.03516
/*24  */         return s->dir[bank];                                                 // (17) 0.02734
/*28  */     case GPSR:		/* GPIO Pin-Output Set registers */                          // (15) 0.0332
/*30  */         qemu_log_mask(LOG_GUEST_ERROR,                                       // (5) 0.04297
/*32  */                       "pxa2xx GPIO: read from write only register GPSR\n");  // (1) 0.07422
/*34  */         return 0;                                                            // (21) 0.01953
/*38  */     case GPCR:		/* GPIO Pin-Output Clear registers */                        // (10) 0.03516
/*40  */         qemu_log_mask(LOG_GUEST_ERROR,                                       // (6) 0.04297
/*42  */                       "pxa2xx GPIO: read from write only register GPCR\n");  // (0) 0.07617
/*44  */         return 0;                                                            // (22) 0.01953
/*48  */     case GRER:		/* GPIO Rising-Edge Detect Enable registers */               // (11) 0.03516
/*50  */         return s->rising[bank];                                              // (18) 0.02734
/*54  */     case GFER:		/* GPIO Falling-Edge Detect Enable registers */              // (12) 0.03516
/*56  */         return s->falling[bank];                                             // (16) 0.0293
/*60  */     case GAFR_L:	/* GPIO Alternate Function registers */                     // (14) 0.0332
/*62  */         return s->gafr[bank * 2];                                            // (13) 0.03516
/*66  */     case GAFR_U:	/* GPIO Alternate Function registers */                     // 0.0
/*68  */         return s->gafr[bank * 2 + 1];                                        // 0.0
/*72  */     case GPLR:		/* GPIO Pin-Level registers */                               // 0.0
/*74  */         ret = (s->olevel[bank] & s->dir[bank]) |                             // 0.0
/*76  */                 (s->ilevel[bank] & ~s->dir[bank]);                           // 0.0
/*78  */         qemu_irq_raise(s->read_notify);                                      // 0.0
/*80  */         return ret;                                                          // 0.0
/*84  */     case GEDR:		/* GPIO Edge Detect Status registers */                      // 0.0
/*86  */         return s->status[bank];                                              // 0.0
/*90  */     default:                                                                 // 0.0
/*92  */         hw_error("%s: Bad offset " REG_FMT "\n", __FUNCTION__, offset);      // 0.0
/*94  */     }                                                                        // 0.0
/*98  */     return 0;                                                                // 0.0
/*100 */ }                                                                            // 0.0
