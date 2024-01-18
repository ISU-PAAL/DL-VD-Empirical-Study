// commit message qemu@0919ac7876 (target=0, prob=0.013055011, correct=True): omap_intc: Qdevify
/*0  */ struct omap_uwire_s *omap_uwire_init(MemoryRegion *system_memory,               // (3) 0.08362
/*2  */                 target_phys_addr_t base,                                        // (5) 0.08362
/*4  */                 qemu_irq *irq, qemu_irq dma, omap_clk clk)                      // (0) 0.1463
/*6  */ {                                                                               // (12) 0.003484
/*8  */     struct omap_uwire_s *s = (struct omap_uwire_s *)                            // (6) 0.08362
/*10 */             g_malloc0(sizeof(struct omap_uwire_s));                             // (2) 0.101
/*14 */     s->txirq = irq[0];                                                          // (7) 0.04878
/*16 */     s->rxirq = irq[1];                                                          // (8) 0.04878
/*18 */     s->txdrq = dma;                                                             // (10) 0.04181
/*20 */     omap_uwire_reset(s);                                                        // (9) 0.0453
/*24 */     memory_region_init_io(&s->iomem, &omap_uwire_ops, s, "omap-uwire", 0x800);  // (1) 0.1324
/*26 */     memory_region_add_subregion(system_memory, base, &s->iomem);                // (4) 0.08362
/*30 */     return s;                                                                   // (11) 0.02091
/*32 */ }                                                                               // (13) 0.003484
