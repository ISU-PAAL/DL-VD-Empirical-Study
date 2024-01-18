// commit message FFmpeg@72a6244b5d (target=0, prob=0.62473685, correct=False): ac3: detect dba errors and prevent writing past end of array
/*0   */ void ff_ac3_bit_alloc_calc_mask(AC3BitAllocParameters *s, int16_t *band_psd,                           // (6) 0.06639
/*2   */                                 int start, int end, int fast_gain, int is_lfe,                         // (2) 0.0937
/*4   */                                 int dba_mode, int dba_nsegs, uint8_t *dba_offsets,                     // (0) 0.1093
/*6   */                                 uint8_t *dba_lengths, uint8_t *dba_values,                             // (1) 0.1015
/*8   */                                 int16_t *mask)                                                         // (3) 0.07429
/*10  */ {                                                                                                      // (18) 0.00198
/*12  */     int16_t excite[50]; /* excitation */                                                               // (12) 0.03124
/*14  */     int bin, k;                                                                                        // (16) 0.01564
/*16  */     int bndstrt, bndend, begin, end1, tmp;                                                             // (10) 0.03906
/*18  */     int lowcomp, fastleak, slowleak;                                                                   // (13) 0.02928
/*22  */     /* excitation function */                                                                          // (17) 0.01562
/*24  */     bndstrt = bin_to_band_tab[start];                                                                  // (11) 0.03514
/*26  */     bndend = bin_to_band_tab[end-1] + 1;                                                               // (9) 0.04296
/*30  */     if (bndstrt == 0) {                                                                                // (14) 0.02541
/*32  */         lowcomp = 0;                                                                                   // (15) 0.02342
/*34  */         lowcomp = calc_lowcomp1(lowcomp, band_psd[0], band_psd[1], 384);                               // (4) 0.06832
/*36  */         excite[0] = band_psd[0] - fast_gain - lowcomp;                                                 // (7) 0.05466
/*38  */         lowcomp = calc_lowcomp1(lowcomp, band_psd[1], band_psd[2], 384);                               // (5) 0.06832
/*40  */         excite[1] = band_psd[1] - fast_gain - lowcomp;                                                 // (8) 0.05466
/*42  */         begin = 7;                                                                                     // 0.0
/*44  */         for (bin = 2; bin < 7; bin++) {                                                                // 0.0
/*46  */             if (!(is_lfe && bin == 6))                                                                 // 0.0
/*48  */                 lowcomp = calc_lowcomp1(lowcomp, band_psd[bin], band_psd[bin+1], 384);                 // 0.0
/*50  */             fastleak = band_psd[bin] - fast_gain;                                                      // 0.0
/*52  */             slowleak = band_psd[bin] - s->slow_gain;                                                   // 0.0
/*54  */             excite[bin] = fastleak - lowcomp;                                                          // 0.0
/*56  */             if (!(is_lfe && bin == 6)) {                                                               // 0.0
/*58  */                 if (band_psd[bin] <= band_psd[bin+1]) {                                                // 0.0
/*60  */                     begin = bin + 1;                                                                   // 0.0
/*62  */                     break;                                                                             // 0.0
/*64  */                 }                                                                                      // 0.0
/*66  */             }                                                                                          // 0.0
/*68  */         }                                                                                              // 0.0
/*72  */         end1=bndend;                                                                                   // 0.0
/*74  */         if (end1 > 22) end1=22;                                                                        // 0.0
/*78  */         for (bin = begin; bin < end1; bin++) {                                                         // 0.0
/*80  */             if (!(is_lfe && bin == 6))                                                                 // 0.0
/*82  */                 lowcomp = calc_lowcomp(lowcomp, band_psd[bin], band_psd[bin+1], bin);                  // 0.0
/*86  */             fastleak = FFMAX(fastleak - s->fast_decay, band_psd[bin] - fast_gain);                     // 0.0
/*88  */             slowleak = FFMAX(slowleak - s->slow_decay, band_psd[bin] - s->slow_gain);                  // 0.0
/*90  */             excite[bin] = FFMAX(fastleak - lowcomp, slowleak);                                         // 0.0
/*92  */         }                                                                                              // 0.0
/*94  */         begin = 22;                                                                                    // 0.0
/*96  */     } else {                                                                                           // 0.0
/*98  */         /* coupling channel */                                                                         // 0.0
/*100 */         begin = bndstrt;                                                                               // 0.0
/*104 */         fastleak = (s->cpl_fast_leak << 8) + 768;                                                      // 0.0
/*106 */         slowleak = (s->cpl_slow_leak << 8) + 768;                                                      // 0.0
/*108 */     }                                                                                                  // 0.0
/*112 */     for (bin = begin; bin < bndend; bin++) {                                                           // 0.0
/*114 */         fastleak = FFMAX(fastleak - s->fast_decay, band_psd[bin] - fast_gain);                         // 0.0
/*116 */         slowleak = FFMAX(slowleak - s->slow_decay, band_psd[bin] - s->slow_gain);                      // 0.0
/*118 */         excite[bin] = FFMAX(fastleak, slowleak);                                                       // 0.0
/*120 */     }                                                                                                  // 0.0
/*124 */     /* compute masking curve */                                                                        // 0.0
/*128 */     for (bin = bndstrt; bin < bndend; bin++) {                                                         // 0.0
/*130 */         tmp = s->db_per_bit - band_psd[bin];                                                           // 0.0
/*132 */         if (tmp > 0) {                                                                                 // 0.0
/*134 */             excite[bin] += tmp >> 2;                                                                   // 0.0
/*136 */         }                                                                                              // 0.0
/*138 */         mask[bin] = FFMAX(ff_ac3_hearing_threshold_tab[bin >> s->sr_shift][s->sr_code], excite[bin]);  // 0.0
/*140 */     }                                                                                                  // 0.0
/*144 */     /* delta bit allocation */                                                                         // 0.0
/*148 */     if (dba_mode == DBA_REUSE || dba_mode == DBA_NEW) {                                                // 0.0
/*150 */         int band, seg, delta;                                                                          // 0.0
/*152 */         band = 0;                                                                                      // 0.0
/*154 */         for (seg = 0; seg < FFMIN(8, dba_nsegs); seg++) {                                              // 0.0
/*156 */             band = FFMIN(49, band + dba_offsets[seg]);                                                 // 0.0
/*158 */             if (dba_values[seg] >= 4) {                                                                // 0.0
/*160 */                 delta = (dba_values[seg] - 3) << 7;                                                    // 0.0
/*162 */             } else {                                                                                   // 0.0
/*164 */                 delta = (dba_values[seg] - 4) << 7;                                                    // 0.0
/*166 */             }                                                                                          // 0.0
/*168 */             for (k = 0; k < dba_lengths[seg]; k++) {                                                   // 0.0
/*170 */                 mask[band] += delta;                                                                   // 0.0
/*172 */                 band++;                                                                                // 0.0
/*174 */             }                                                                                          // 0.0
/*176 */         }                                                                                              // 0.0
/*178 */     }                                                                                                  // 0.0
/*180 */ }                                                                                                      // 0.0
