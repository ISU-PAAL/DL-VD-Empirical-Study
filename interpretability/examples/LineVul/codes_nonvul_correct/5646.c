// commit message qemu@e1f8c729fa (target=0, prob=0.0064161606, correct=True): pxa2xx_pic: update to use qdev
/*0  */ void pxa25x_timer_init(target_phys_addr_t base, qemu_irq *irqs)  // (0) 0.299
/*2  */ {                                                                // (4) 0.01031
/*4  */     pxa2xx_timer_info *s = pxa2xx_timer_init(base, irqs);        // (1) 0.2887
/*6  */     s->freq = PXA25X_FREQ;                                       // (2) 0.1856
/*8  */     s->tm4 = NULL;                                               // (3) 0.1031
/*10 */ }                                                                // (5) 0.01031
