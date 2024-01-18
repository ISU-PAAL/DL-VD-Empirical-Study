// commit message qemu@84a3a53cf6 (target=1, prob=0.80820906, correct=True): omap: Don't use hw_error() in device init() methods
/*0  */ static int omap_gpio_init(SysBusDevice *sbd)                                // (8) 0.05882
/*2  */ {                                                                           // (13) 0.00346
/*4  */     DeviceState *dev = DEVICE(sbd);                                         // (9) 0.04844
/*6  */     struct omap_gpif_s *s = OMAP1_GPIO(dev);                                // (6) 0.07958
/*10 */     if (!s->clk) {                                                          // (10) 0.03806
/*12 */         hw_error("omap-gpio: clk not connected\n");                         // (2) 0.08651
/*14 */     }                                                                       // (12) 0.01384
/*16 */     qdev_init_gpio_in(dev, omap_gpio_set, 16);                              // (3) 0.08651
/*18 */     qdev_init_gpio_out(dev, s->omap1.handler, 16);                          // (4) 0.08651
/*20 */     sysbus_init_irq(sbd, &s->omap1.irq);                                    // (5) 0.08304
/*22 */     memory_region_init_io(&s->iomem, OBJECT(s), &omap_gpio_ops, &s->omap1,  // (0) 0.128
/*24 */                           "omap.gpio", 0x1000);                             // (1) 0.1246
/*26 */     sysbus_init_mmio(sbd, &s->iomem);                                       // (7) 0.0692
/*28 */     return 0;                                                               // (11) 0.02076
/*30 */ }                                                                           // (14) 0.00346
