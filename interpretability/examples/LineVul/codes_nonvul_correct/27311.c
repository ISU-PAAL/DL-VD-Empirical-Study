// commit message qemu@a8170e5e97 (target=0, prob=0.033867087, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static struct omap_mcbsp_s *omap_mcbsp_init(MemoryRegion *system_memory,        // (7) 0.05102
/*2  */                                             target_phys_addr_t base,            // (2) 0.1061
/*4  */                                             qemu_irq txirq, qemu_irq rxirq,     // (0) 0.1306
/*6  */                                             qemu_irq *dma, omap_clk clk)        // (1) 0.1245
/*8  */ {                                                                               // (16) 0.002041
/*10 */     struct omap_mcbsp_s *s = (struct omap_mcbsp_s *)                            // (9) 0.04898
/*12 */             g_malloc0(sizeof(struct omap_mcbsp_s));                             // (6) 0.05918
/*16 */     s->txirq = txirq;                                                           // (13) 0.02653
/*18 */     s->rxirq = rxirq;                                                           // (10) 0.02857
/*20 */     s->txdrq = dma[0];                                                          // (11) 0.02857
/*22 */     s->rxdrq = dma[1];                                                          // (12) 0.02857
/*24 */     s->sink_timer = qemu_new_timer_ns(vm_clock, omap_mcbsp_sink_tick, s);       // (4) 0.07551
/*26 */     s->source_timer = qemu_new_timer_ns(vm_clock, omap_mcbsp_source_tick, s);   // (5) 0.07143
/*28 */     omap_mcbsp_reset(s);                                                        // (14) 0.02653
/*32 */     memory_region_init_io(&s->iomem, &omap_mcbsp_ops, s, "omap-mcbsp", 0x800);  // (3) 0.07755
/*34 */     memory_region_add_subregion(system_memory, base, &s->iomem);                // (8) 0.04898
/*38 */     return s;                                                                   // (15) 0.01224
/*40 */ }                                                                               // (17) 0.002041
