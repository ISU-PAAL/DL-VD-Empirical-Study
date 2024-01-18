// commit message qemu@4bb3893908 (target=0, prob=0.9872815, correct=False): wm8750: add record buffer underrun check
/*0  */ uint32_t wm8750_adc_dat(void *opaque)            // (2) 0.1195
/*2  */ {                                                // (9) 0.006289
/*4  */     WM8750State *s = (WM8750State *) opaque;     // (3) 0.1132
/*6  */     uint32_t *data;                              // (7) 0.06289
/*10 */     if (s->idx_in >= sizeof(s->data_in))         // (1) 0.1258
/*12 */         wm8750_in_load(s);                       // (4) 0.1132
/*16 */     data = (uint32_t *) &s->data_in[s->idx_in];  // (0) 0.1572
/*18 */     s->req_in -= 4;                              // (6) 0.06918
/*20 */     s->idx_in += 4;                              // (5) 0.07547
/*22 */     return *data;                                // (8) 0.04403
/*24 */ }                                                // (10) 0.006289
