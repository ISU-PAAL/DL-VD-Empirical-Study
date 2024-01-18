// commit message qemu@1673510204 (target=1, prob=0.034355223, correct=False): Remove screendump dummy functions.
/*0  */ static int jazz_led_init(SysBusDevice *dev)                    // (7) 0.05556
/*2  */ {                                                              // (9) 0.003968
/*4  */     LedState *s = FROM_SYSBUS(LedState, dev);                  // (5) 0.0754
/*8  */     memory_region_init_io(&s->iomem, &led_ops, s, "led", 1);   // (3) 0.1111
/*10 */     sysbus_init_mmio(dev, &s->iomem);                          // (6) 0.0754
/*14 */     s->ds = graphic_console_init(jazz_led_update_display,      // (4) 0.0873
/*16 */                                  jazz_led_invalidate_display,  // (0) 0.1667
/*18 */                                  jazz_led_screen_dump,         // (2) 0.1587
/*20 */                                  jazz_led_text_update, s);     // (1) 0.1667
/*24 */     return 0;                                                  // (8) 0.02381
/*26 */ }                                                              // (10) 0.003968
