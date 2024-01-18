// commit message FFmpeg@101ef19ef4 (target=1, prob=0.49773186, correct=False): binkaudio: add some buffer overread checks.
/*0   */ static void decode_block(BinkAudioContext *s, short *out, int use_dct)                  // (8) 0.04492
/*2   */ {                                                                                       // (24) 0.001953
/*4   */     int ch, i, j, k;                                                                    // (15) 0.02344
/*6   */     float q, quant[25];                                                                 // (18) 0.01953
/*8   */     int width, coeff;                                                                   // (21) 0.01758
/*10  */     GetBitContext *gb = &s->gb;                                                         // (13) 0.02734
/*14  */     if (use_dct)                                                                        // (19) 0.01953
/*16  */         skip_bits(gb, 2);                                                               // (12) 0.0293
/*20  */     for (ch = 0; ch < s->channels; ch++) {                                              // (10) 0.03711
/*22  */         FFTSample *coeffs = s->coeffs_ptr[ch];                                          // (6) 0.04883
/*24  */         if (s->version_b) {                                                             // (11) 0.03125
/*26  */             coeffs[0] = av_int2flt(get_bits(gb, 32)) * s->root;                         // (2) 0.07422
/*28  */             coeffs[1] = av_int2flt(get_bits(gb, 32)) * s->root;                         // (1) 0.07422
/*30  */         } else {                                                                        // (20) 0.01953
/*32  */             coeffs[0] = get_float(gb) * s->root;                                        // (4) 0.05664
/*34  */             coeffs[1] = get_float(gb) * s->root;                                        // (5) 0.05664
/*36  */         }                                                                               // (23) 0.01562
/*40  */         for (i = 0; i < s->num_bands; i++) {                                            // (7) 0.04687
/*42  */             /* constant is result of 0.066399999/log10(M_E) */                          // (3) 0.06055
/*44  */             int value = get_bits(gb, 8);                                                // (9) 0.04297
/*46  */             quant[i] = expf(FFMIN(value, 95) * 0.15289164787221953823f) * s->root;      // (0) 0.08789
/*48  */         }                                                                               // (22) 0.01562
/*52  */         k = 0;                                                                          // (16) 0.02148
/*54  */         q = quant[0];                                                                   // (14) 0.02539
/*58  */         // parse coefficients                                                           // (17) 0.01953
/*60  */         i = 2;                                                                          // 0.0
/*62  */         while (i < s->frame_len) {                                                      // 0.0
/*64  */             if (s->version_b) {                                                         // 0.0
/*66  */                 j = i + 16;                                                             // 0.0
/*68  */             } else if (get_bits1(gb)) {                                                 // 0.0
/*70  */                 j = i + rle_length_tab[get_bits(gb, 4)] * 8;                            // 0.0
/*72  */             } else {                                                                    // 0.0
/*74  */                 j = i + 8;                                                              // 0.0
/*76  */             }                                                                           // 0.0
/*80  */             j = FFMIN(j, s->frame_len);                                                 // 0.0
/*84  */             width = get_bits(gb, 4);                                                    // 0.0
/*86  */             if (width == 0) {                                                           // 0.0
/*88  */                 memset(coeffs + i, 0, (j - i) * sizeof(*coeffs));                       // 0.0
/*90  */                 i = j;                                                                  // 0.0
/*92  */                 while (s->bands[k] < i)                                                 // 0.0
/*94  */                     q = quant[k++];                                                     // 0.0
/*96  */             } else {                                                                    // 0.0
/*98  */                 while (i < j) {                                                         // 0.0
/*100 */                     if (s->bands[k] == i)                                               // 0.0
/*102 */                         q = quant[k++];                                                 // 0.0
/*104 */                     coeff = get_bits(gb, width);                                        // 0.0
/*106 */                     if (coeff) {                                                        // 0.0
/*108 */                         if (get_bits1(gb))                                              // 0.0
/*110 */                             coeffs[i] = -q * coeff;                                     // 0.0
/*112 */                         else                                                            // 0.0
/*114 */                             coeffs[i] =  q * coeff;                                     // 0.0
/*116 */                     } else {                                                            // 0.0
/*118 */                         coeffs[i] = 0.0f;                                               // 0.0
/*120 */                     }                                                                   // 0.0
/*122 */                     i++;                                                                // 0.0
/*124 */                 }                                                                       // 0.0
/*126 */             }                                                                           // 0.0
/*128 */         }                                                                               // 0.0
/*132 */         if (CONFIG_BINKAUDIO_DCT_DECODER && use_dct) {                                  // 0.0
/*134 */             coeffs[0] /= 0.5;                                                           // 0.0
/*136 */             s->trans.dct.dct_calc(&s->trans.dct,  coeffs);                              // 0.0
/*138 */             s->dsp.vector_fmul_scalar(coeffs, coeffs, s->frame_len / 2, s->frame_len);  // 0.0
/*140 */         }                                                                               // 0.0
/*142 */         else if (CONFIG_BINKAUDIO_RDFT_DECODER)                                         // 0.0
/*144 */             s->trans.rdft.rdft_calc(&s->trans.rdft, coeffs);                            // 0.0
/*146 */     }                                                                                   // 0.0
/*150 */     s->fmt_conv.float_to_int16_interleave(out, (const float **)s->coeffs_ptr,           // 0.0
/*152 */                                           s->frame_len, s->channels);                   // 0.0
/*156 */     if (!s->first) {                                                                    // 0.0
/*158 */         int count = s->overlap_len * s->channels;                                       // 0.0
/*160 */         int shift = av_log2(count);                                                     // 0.0
/*162 */         for (i = 0; i < count; i++) {                                                   // 0.0
/*164 */             out[i] = (s->previous[i] * (count - i) + out[i] * i) >> shift;              // 0.0
/*166 */         }                                                                               // 0.0
/*168 */     }                                                                                   // 0.0
/*172 */     memcpy(s->previous, out + s->block_size,                                            // 0.0
/*174 */            s->overlap_len * s->channels * sizeof(*out));                                // 0.0
/*178 */     s->first = 0;                                                                       // 0.0
/*180 */ }                                                                                       // 0.0
