// commit message FFmpeg@57cc1ad35f (target=0, prob=0.84544104, correct=False): aacenc: reduce the number of loop index variables
/*0   */ static av_always_inline float quantize_and_encode_band_cost_template(                               // (8) 0.04102
/*2   */                                 struct AACEncContext *s,                                            // (7) 0.07422
/*4   */                                 PutBitContext *pb, const float *in,                                 // (4) 0.08203
/*6   */                                 const float *scaled, int size, int scale_idx,                       // (1) 0.08984
/*8   */                                 int cb, const float lambda, const float uplim,                      // (2) 0.08594
/*10  */                                 int *bits, int BT_ZERO, int BT_UNSIGNED,                            // (0) 0.09375
/*12  */                                 int BT_PAIR, int BT_ESC)                                            // (3) 0.08398
/*14  */ {                                                                                                   // (18) 0.001953
/*16  */     const float IQ = ff_aac_pow2sf_tab[200 + scale_idx - SCALE_ONE_POS + SCALE_DIV_512];            // (6) 0.07812
/*18  */     const float  Q = ff_aac_pow2sf_tab[200 - scale_idx + SCALE_ONE_POS - SCALE_DIV_512];            // (5) 0.08008
/*20  */     const float CLIPPED_ESCAPE = 165140.0f*IQ;                                                      // (9) 0.04102
/*22  */     int i, j, k;                                                                                    // (14) 0.01953
/*24  */     float cost = 0;                                                                                 // (16) 0.01562
/*26  */     const int dim = BT_PAIR ? 2 : 4;                                                                // (13) 0.03125
/*28  */     int resbits = 0;                                                                                // (15) 0.01758
/*30  */     const float  Q34 = sqrtf(Q * sqrtf(Q));                                                         // (10) 0.04102
/*32  */     const int range  = aac_cb_range[cb];                                                            // (12) 0.0332
/*34  */     const int maxval = aac_cb_maxval[cb];                                                           // (11) 0.03516
/*36  */     int off;                                                                                        // (17) 0.01172
/*40  */     if (BT_ZERO) {                                                                                  // 0.0
/*42  */         for (i = 0; i < size; i++)                                                                  // 0.0
/*44  */             cost += in[i]*in[i];                                                                    // 0.0
/*46  */         if (bits)                                                                                   // 0.0
/*48  */             *bits = 0;                                                                              // 0.0
/*50  */         return cost * lambda;                                                                       // 0.0
/*52  */     }                                                                                               // 0.0
/*54  */     if (!scaled) {                                                                                  // 0.0
/*56  */         abs_pow34_v(s->scoefs, in, size);                                                           // 0.0
/*58  */         scaled = s->scoefs;                                                                         // 0.0
/*60  */     }                                                                                               // 0.0
/*62  */     quantize_bands(s->qcoefs, in, scaled, size, Q34, !BT_UNSIGNED, maxval);                         // 0.0
/*64  */     if (BT_UNSIGNED) {                                                                              // 0.0
/*66  */         off = 0;                                                                                    // 0.0
/*68  */     } else {                                                                                        // 0.0
/*70  */         off = maxval;                                                                               // 0.0
/*72  */     }                                                                                               // 0.0
/*74  */     for (i = 0; i < size; i += dim) {                                                               // 0.0
/*76  */         const float *vec;                                                                           // 0.0
/*78  */         int *quants = s->qcoefs + i;                                                                // 0.0
/*80  */         int curidx = 0;                                                                             // 0.0
/*82  */         int curbits;                                                                                // 0.0
/*84  */         float rd = 0.0f;                                                                            // 0.0
/*86  */         for (j = 0; j < dim; j++) {                                                                 // 0.0
/*88  */             curidx *= range;                                                                        // 0.0
/*90  */             curidx += quants[j] + off;                                                              // 0.0
/*92  */         }                                                                                           // 0.0
/*94  */         curbits =  ff_aac_spectral_bits[cb-1][curidx];                                              // 0.0
/*96  */         vec     = &ff_aac_codebook_vectors[cb-1][curidx*dim];                                       // 0.0
/*98  */         if (BT_UNSIGNED) {                                                                          // 0.0
/*100 */             for (k = 0; k < dim; k++) {                                                             // 0.0
/*102 */                 float t = fabsf(in[i+k]);                                                           // 0.0
/*104 */                 float di;                                                                           // 0.0
/*106 */                 if (BT_ESC && vec[k] == 64.0f) { //FIXME: slow                                      // 0.0
/*108 */                     if (t >= CLIPPED_ESCAPE) {                                                      // 0.0
/*110 */                         di = t - CLIPPED_ESCAPE;                                                    // 0.0
/*112 */                         curbits += 21;                                                              // 0.0
/*114 */                     } else {                                                                        // 0.0
/*116 */                         int c = av_clip(quant(t, Q), 0, 8191);                                      // 0.0
/*118 */                         di = t - c*cbrtf(c)*IQ;                                                     // 0.0
/*120 */                         curbits += av_log2(c)*2 - 4 + 1;                                            // 0.0
/*122 */                     }                                                                               // 0.0
/*124 */                 } else {                                                                            // 0.0
/*126 */                     di = t - vec[k]*IQ;                                                             // 0.0
/*128 */                 }                                                                                   // 0.0
/*130 */                 if (vec[k] != 0.0f)                                                                 // 0.0
/*132 */                     curbits++;                                                                      // 0.0
/*134 */                 rd += di*di;                                                                        // 0.0
/*136 */             }                                                                                       // 0.0
/*138 */         } else {                                                                                    // 0.0
/*140 */             for (k = 0; k < dim; k++) {                                                             // 0.0
/*142 */                 float di = in[i+k] - vec[k]*IQ;                                                     // 0.0
/*144 */                 rd += di*di;                                                                        // 0.0
/*146 */             }                                                                                       // 0.0
/*148 */         }                                                                                           // 0.0
/*150 */         cost    += rd * lambda + curbits;                                                           // 0.0
/*152 */         resbits += curbits;                                                                         // 0.0
/*154 */         if (cost >= uplim)                                                                          // 0.0
/*156 */             return uplim;                                                                           // 0.0
/*158 */         if (pb) {                                                                                   // 0.0
/*160 */             put_bits(pb, ff_aac_spectral_bits[cb-1][curidx], ff_aac_spectral_codes[cb-1][curidx]);  // 0.0
/*162 */             if (BT_UNSIGNED)                                                                        // 0.0
/*164 */                 for (j = 0; j < dim; j++)                                                           // 0.0
/*166 */                     if (ff_aac_codebook_vectors[cb-1][curidx*dim+j] != 0.0f)                        // 0.0
/*168 */                         put_bits(pb, 1, in[i+j] < 0.0f);                                            // 0.0
/*170 */             if (BT_ESC) {                                                                           // 0.0
/*172 */                 for (j = 0; j < 2; j++) {                                                           // 0.0
/*174 */                     if (ff_aac_codebook_vectors[cb-1][curidx*2+j] == 64.0f) {                       // 0.0
/*176 */                         int coef = av_clip(quant(fabsf(in[i+j]), Q), 0, 8191);                      // 0.0
/*178 */                         int len = av_log2(coef);                                                    // 0.0
/*182 */                         put_bits(pb, len - 4 + 1, (1 << (len - 4 + 1)) - 2);                        // 0.0
/*184 */                         put_bits(pb, len, coef & ((1 << len) - 1));                                 // 0.0
/*186 */                     }                                                                               // 0.0
/*188 */                 }                                                                                   // 0.0
/*190 */             }                                                                                       // 0.0
/*192 */         }                                                                                           // 0.0
/*194 */     }                                                                                               // 0.0
/*198 */     if (bits)                                                                                       // 0.0
/*200 */         *bits = resbits;                                                                            // 0.0
/*202 */     return cost;                                                                                    // 0.0
/*204 */ }                                                                                                   // 0.0
