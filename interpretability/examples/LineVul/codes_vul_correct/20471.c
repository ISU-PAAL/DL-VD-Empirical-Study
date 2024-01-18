// commit message qemu@b0f74c87a1 (target=1, prob=0.8857508, correct=True): Don't use "hz" in identifiers to make AIX happy.
/*0  */ void wm8750_set_bclk_in(void *opaque, int hz)         // (1) 0.213
/*2  */ {                                                     // (5) 0.009259
/*4  */     struct wm8750_s *s = (struct wm8750_s *) opaque;  // (0) 0.2222
/*8  */     s->ext_adc_hz = hz;                               // (3) 0.1389
/*10 */     s->ext_dac_hz = hz;                               // (4) 0.1389
/*12 */     wm8750_clk_update(s, 1);                          // (2) 0.1574
/*14 */ }                                                     // (6) 0.009259
