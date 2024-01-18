// commit message qemu@f3c7d0389f (target=1, prob=0.0068879575, correct=False): hw: Fix qemu_allocate_irqs() leaks
/*0  */ void omap_mcbsp_i2s_attach(struct omap_mcbsp_s *s, I2SCodec *slave)           // (2) 0.2462
/*2  */ {                                                                             // (4) 0.007692
/*4  */     s->codec = slave;                                                         // (3) 0.07692
/*6  */     slave->rx_swallow = qemu_allocate_irqs(omap_mcbsp_i2s_swallow, s, 1)[0];  // (0) 0.3
/*8  */     slave->tx_start = qemu_allocate_irqs(omap_mcbsp_i2s_start, s, 1)[0];      // (1) 0.2846
/*10 */ }                                                                             // (5) 0.007692
