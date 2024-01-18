// commit message qemu@6ab3fc32ea (target=1, prob=0.6863154, correct=True): hw: replace most use of qemu_chr_fe_write with qemu_chr_fe_write_all
/*0  */ void lm32_juart_set_jtx(DeviceState *d, uint32_t jtx)  // (1) 0.1623
/*2  */ {                                                      // (8) 0.006494
/*4  */     LM32JuartState *s = LM32_JUART(d);                 // (3) 0.1299
/*6  */     unsigned char ch = jtx & 0xff;                     // (4) 0.08442
/*10 */     trace_lm32_juart_set_jtx(s->jtx);                  // (2) 0.1429
/*14 */     s->jtx = jtx;                                      // (5) 0.07143
/*16 */     if (s->chr) {                                      // (6) 0.07143
/*20 */         qemu_chr_fe_write_all(s->chr, &ch, 1);         // (0) 0.1948
/*22 */     }                                                  // (7) 0.02597
/*24 */ }                                                      // (9) 0.006494
