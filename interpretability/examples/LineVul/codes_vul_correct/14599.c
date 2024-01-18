// commit message FFmpeg@290e7eb77b (target=1, prob=0.99904305, correct=True): Fix possible endless loop when decoding amr.
/*0  */ void ff_clear_fixed_vector(float *out, const AMRFixed *in, int size)    // (1) 0.1361
/*2  */ {                                                                       // (9) 0.005917
/*4  */     int i;                                                              // (7) 0.0355
/*8  */     for (i=0; i < in->n; i++) {                                         // (4) 0.1065
/*10 */         int x  = in->x[i], repeats = !((in->no_repeat_mask >> i) & 1);  // (0) 0.2012
/*15 */         do {                                                            // (6) 0.05325
/*17 */             out[x] = 0.0;                                               // (3) 0.1183
/*19 */             x += in->pitch_lag;                                         // (2) 0.1183
/*21 */         } while (x < size && repeats);                                  // (5) 0.09467
/*23 */     }                                                                   // (8) 0.02367
/*25 */ }                                                                       // (10) 0.005917
