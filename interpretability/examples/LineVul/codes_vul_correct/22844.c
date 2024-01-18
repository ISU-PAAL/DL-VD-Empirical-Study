// commit message FFmpeg@ee90119e9e (target=1, prob=0.58156073, correct=True): binkaudio: remove unneeded GET_BITS_SAFE macro
/*0   */ static int decode_block(BinkAudioContext *s, float **out, int use_dct)    // (10) 0.04492
/*2   */ {                                                                         // (23) 0.001953
/*4   */     int ch, i, j, k;                                                      // (17) 0.02344
/*6   */     float q, quant[25];                                                   // (18) 0.01953
/*8   */     int width, coeff;                                                     // (21) 0.01758
/*10  */     GetBitContext *gb = &s->gb;                                           // (16) 0.02734
/*14  */     if (use_dct)                                                          // (19) 0.01953
/*16  */         skip_bits(gb, 2);                                                 // (15) 0.0293
/*20  */     for (ch = 0; ch < s->channels; ch++) {                                // (13) 0.03711
/*22  */         FFTSample *coeffs = out[ch];                                      // (12) 0.03711
/*26  */         if (s->version_b) {                                               // (14) 0.03125
/*28  */             if (get_bits_left(gb) < 64)                                   // (8) 0.04687
/*30  */                 return AVERROR_INVALIDDATA;                               // (5) 0.04883
/*32  */             coeffs[0] = av_int2float(get_bits_long(gb, 32)) * s->root;    // (0) 0.07617
/*34  */             coeffs[1] = av_int2float(get_bits_long(gb, 32)) * s->root;    // (1) 0.07617
/*36  */         } else {                                                          // (20) 0.01953
/*38  */             if (get_bits_left(gb) < 58)                                   // (9) 0.04687
/*40  */                 return AVERROR_INVALIDDATA;                               // (6) 0.04883
/*42  */             coeffs[0] = get_float(gb) * s->root;                          // (2) 0.05664
/*44  */             coeffs[1] = get_float(gb) * s->root;                          // (3) 0.05664
/*46  */         }                                                                 // (22) 0.01562
/*50  */         if (get_bits_left(gb) < s->num_bands * 8)                         // (4) 0.05078
/*52  */             return AVERROR_INVALIDDATA;                                   // (11) 0.04102
/*54  */         for (i = 0; i < s->num_bands; i++) {                              // (7) 0.04687
/*56  */             int value = get_bits(gb, 8);                                  // 0.0
/*58  */             quant[i]  = quant_table[FFMIN(value, 95)];                    // 0.0
/*60  */         }                                                                 // 0.0
/*64  */         k = 0;                                                            // 0.0
/*66  */         q = quant[0];                                                     // 0.0
/*70  */         // parse coefficients                                             // 0.0
/*72  */         i = 2;                                                            // 0.0
/*74  */         while (i < s->frame_len) {                                        // 0.0
/*76  */             if (s->version_b) {                                           // 0.0
/*78  */                 j = i + 16;                                               // 0.0
/*80  */             } else {                                                      // 0.0
/*82  */                 int v;                                                    // 0.0
/*84  */                 GET_BITS_SAFE(v, 1);                                      // 0.0
/*86  */                 if (v) {                                                  // 0.0
/*88  */                     GET_BITS_SAFE(v, 4);                                  // 0.0
/*90  */                     j = i + rle_length_tab[v] * 8;                        // 0.0
/*92  */                 } else {                                                  // 0.0
/*94  */                     j = i + 8;                                            // 0.0
/*96  */                 }                                                         // 0.0
/*98  */             }                                                             // 0.0
/*102 */             j = FFMIN(j, s->frame_len);                                   // 0.0
/*106 */             GET_BITS_SAFE(width, 4);                                      // 0.0
/*108 */             if (width == 0) {                                             // 0.0
/*110 */                 memset(coeffs + i, 0, (j - i) * sizeof(*coeffs));         // 0.0
/*112 */                 i = j;                                                    // 0.0
/*114 */                 while (s->bands[k] < i)                                   // 0.0
/*116 */                     q = quant[k++];                                       // 0.0
/*118 */             } else {                                                      // 0.0
/*120 */                 while (i < j) {                                           // 0.0
/*122 */                     if (s->bands[k] == i)                                 // 0.0
/*124 */                         q = quant[k++];                                   // 0.0
/*126 */                     GET_BITS_SAFE(coeff, width);                          // 0.0
/*128 */                     if (coeff) {                                          // 0.0
/*130 */                         int v;                                            // 0.0
/*132 */                         GET_BITS_SAFE(v, 1);                              // 0.0
/*134 */                         if (v)                                            // 0.0
/*136 */                             coeffs[i] = -q * coeff;                       // 0.0
/*138 */                         else                                              // 0.0
/*140 */                             coeffs[i] =  q * coeff;                       // 0.0
/*142 */                     } else {                                              // 0.0
/*144 */                         coeffs[i] = 0.0f;                                 // 0.0
/*146 */                     }                                                     // 0.0
/*148 */                     i++;                                                  // 0.0
/*150 */                 }                                                         // 0.0
/*152 */             }                                                             // 0.0
/*154 */         }                                                                 // 0.0
/*158 */         if (CONFIG_BINKAUDIO_DCT_DECODER && use_dct) {                    // 0.0
/*160 */             coeffs[0] /= 0.5;                                             // 0.0
/*162 */             s->trans.dct.dct_calc(&s->trans.dct,  coeffs);                // 0.0
/*164 */         }                                                                 // 0.0
/*166 */         else if (CONFIG_BINKAUDIO_RDFT_DECODER)                           // 0.0
/*168 */             s->trans.rdft.rdft_calc(&s->trans.rdft, coeffs);              // 0.0
/*170 */     }                                                                     // 0.0
/*174 */     for (ch = 0; ch < s->channels; ch++) {                                // 0.0
/*176 */         int j;                                                            // 0.0
/*178 */         int count = s->overlap_len * s->channels;                         // 0.0
/*180 */         if (!s->first) {                                                  // 0.0
/*182 */             j = ch;                                                       // 0.0
/*184 */             for (i = 0; i < s->overlap_len; i++, j += s->channels)        // 0.0
/*186 */                 out[ch][i] = (s->previous[ch][i] * (count - j) +          // 0.0
/*188 */                                       out[ch][i] *          j) / count;   // 0.0
/*190 */         }                                                                 // 0.0
/*192 */         memcpy(s->previous[ch], &out[ch][s->frame_len - s->overlap_len],  // 0.0
/*194 */                s->overlap_len * sizeof(*s->previous[ch]));                // 0.0
/*196 */     }                                                                     // 0.0
/*200 */     s->first = 0;                                                         // 0.0
/*204 */     return 0;                                                             // 0.0
/*206 */ }                                                                         // 0.0
