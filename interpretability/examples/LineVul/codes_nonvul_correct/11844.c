// commit message qemu@75554a3ca1 (target=0, prob=0.009517563, correct=True): Allow attaching devices to OMAP UARTs.
/*0  */ struct omap_uart_s *omap2_uart_init(struct omap_target_agent_s *ta,    // (4) 0.08434
/*2  */                 qemu_irq irq, omap_clk fclk, omap_clk iclk,            // (1) 0.1265
/*4  */                 qemu_irq txdma, qemu_irq rxdma, CharDriverState *chr)  // (0) 0.1265
/*6  */ {                                                                      // (12) 0.003012
/*8  */     target_phys_addr_t base = omap_l4_attach(ta, 0, 0);                // (7) 0.07831
/*10 */     struct omap_uart_s *s = omap_uart_init(base, irq,                  // (8) 0.0753
/*12 */                     fclk, iclk, txdma, rxdma, chr);                    // (2) 0.1145
/*14 */     int iomemtype = cpu_register_io_memory(0, omap_uart_readfn,        // (6) 0.08133
/*16 */                     omap_uart_writefn, s);                             // (3) 0.08735
/*20 */     s->ta = ta;                                                        // (9) 0.02711
/*22 */     s->base = base;                                                    // (10) 0.02711
/*26 */     cpu_register_physical_memory(s->base + 0x20, 0x100, iomemtype);    // (5) 0.08434
/*30 */     return s;                                                          // (11) 0.01807
/*32 */ }                                                                      // (13) 0.003012
