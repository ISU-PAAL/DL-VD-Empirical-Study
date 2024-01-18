// commit message qemu@f3c7d0389f (target=1, prob=0.9595947, correct=True): hw: Fix qemu_allocate_irqs() leaks
/*0  */ struct omap_mmc_s *omap2_mmc_init(struct omap_target_agent_s *ta,         // (5) 0.06466
/*2  */                 BlockDriverState *bd, qemu_irq irq, qemu_irq dma[],       // (0) 0.08621
/*4  */                 omap_clk fclk, omap_clk iclk)                             // (4) 0.07112
/*6  */ {                                                                         // (22) 0.002155
/*8  */     struct omap_mmc_s *s = (struct omap_mmc_s *)                          // (7) 0.05172
/*10 */             g_malloc0(sizeof(struct omap_mmc_s));                         // (6) 0.0625
/*14 */     s->irq = irq;                                                         // (14) 0.02371
/*16 */     s->dma = dma;                                                         // (15) 0.02371
/*18 */     s->clk = fclk;                                                        // (12) 0.02586
/*20 */     s->lines = 4;                                                         // (18) 0.0194
/*22 */     s->rev = 2;                                                           // (19) 0.0194
/*26 */     omap_mmc_reset(s);                                                    // (11) 0.02802
/*30 */     memory_region_init_io(&s->iomem, NULL, &omap_mmc_ops, s, "omap.mmc",  // (2) 0.07759
/*32 */                           omap_l4_region_size(ta, 0));                    // (1) 0.08405
/*34 */     omap_l4_attach(ta, 0, &s->iomem);                                     // (8) 0.04526
/*38 */     /* Instantiate the storage */                                         // (17) 0.0194
/*40 */     s->card = sd_init(bd, false);                                         // (10) 0.03233
/*42 */     if (s->card == NULL) {                                                // (13) 0.02586
/*44 */         exit(1);                                                          // (16) 0.02371
/*46 */     }                                                                     // (21) 0.008621
/*50 */     s->cdet = qemu_allocate_irqs(omap_mmc_cover_cb, s, 1)[0];             // (3) 0.07328
/*52 */     sd_set_cb(s->card, NULL, s->cdet);                                    // (9) 0.0431
/*56 */     return s;                                                             // (20) 0.01293
/*58 */ }                                                                         // (23) 0.002155
