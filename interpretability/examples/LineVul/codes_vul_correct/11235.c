// commit message qemu@b45c03f585 (target=1, prob=0.6038976, correct=True): arm: Use g_new() & friends where that makes obvious sense
/*0  */ struct omap_uart_s *omap_uart_init(hwaddr base,                           // (9) 0.0481
/*2  */                 qemu_irq irq, omap_clk fclk, omap_clk iclk,               // (2) 0.1063
/*4  */                 qemu_irq txdma, qemu_irq rxdma,                           // (4) 0.08861
/*6  */                 const char *label, CharDriverState *chr)                  // (6) 0.06835
/*8  */ {                                                                         // (14) 0.002532
/*10 */     struct omap_uart_s *s = (struct omap_uart_s *)                        // (8) 0.0557
/*12 */             g_malloc0(sizeof(struct omap_uart_s));                        // (5) 0.07089
/*16 */     s->base = base;                                                       // (12) 0.02278
/*18 */     s->fclk = fclk;                                                       // (10) 0.03291
/*20 */     s->irq = irq;                                                         // (11) 0.02785
/*22 */     s->serial = serial_mm_init(get_system_memory(), base, 2, irq,         // (7) 0.06582
/*24 */                                omap_clk_getrate(fclk)/16,                 // (1) 0.1139
/*26 */                                chr ?: qemu_chr_new(label, "null", NULL),  // (0) 0.1266
/*28 */                                DEVICE_NATIVE_ENDIAN);                     // (3) 0.09873
/*30 */     return s;                                                             // (13) 0.01519
/*32 */ }                                                                         // (15) 0.002532
