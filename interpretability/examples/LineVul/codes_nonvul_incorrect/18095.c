// commit message FFmpeg@af2ee6fc49 (target=0, prob=0.58677715, correct=False): Remove useless costly inf checks from the trellis scalefactor search.
/*0   */ static void search_for_quantizers_anmr(AVCodecContext *avctx, AACEncContext *s,                                                  // (4) 0.05078
/*2   */                                        SingleChannelElement *sce,                                                                // (0) 0.08789
/*4   */                                        const float lambda)                                                                       // (1) 0.08203
/*6   */ {                                                                                                                                // (26) 0.001953
/*8   */     int q, w, w2, g, start = 0;                                                                                                  // (11) 0.03321
/*10  */     int i, j;                                                                                                                    // (19) 0.01562
/*12  */     int idx;                                                                                                                     // (22) 0.01367
/*14  */     TrellisPath paths[TRELLIS_STAGES][TRELLIS_STATES];                                                                           // (6) 0.04883
/*16  */     int bandaddr[TRELLIS_STAGES];                                                                                                // (16) 0.0293
/*18  */     int minq;                                                                                                                    // (23) 0.01367
/*20  */     float mincost;                                                                                                               // (21) 0.01367
/*22  */     float q0f = FLT_MAX, q1f = 0.0f, qnrgf = 0.0f;                                                                               // (2) 0.0625
/*24  */     int q0, q1, qcnt = 0;                                                                                                        // (14) 0.03125
/*28  */     for (i = 0; i < 1024; i++) {                                                                                                 // (13) 0.03125
/*30  */         float t = fabsf(sce->coeffs[i]);                                                                                         // (9) 0.04297
/*32  */         if (t > 0.0f) {                                                                                                          // (12) 0.0332
/*34  */             q0f = FFMIN(q0f, t);                                                                                                 // (7) 0.04687
/*36  */             q1f = FFMAX(q1f, t);                                                                                                 // (8) 0.04687
/*38  */             qnrgf += t*t;                                                                                                        // (10) 0.03906
/*40  */             qcnt++;                                                                                                              // (15) 0.0293
/*42  */         }                                                                                                                        // (20) 0.01562
/*44  */     }                                                                                                                            // (25) 0.007812
/*48  */     if (!qcnt) {                                                                                                                 // (17) 0.01953
/*50  */         memset(sce->sf_idx, 0, sizeof(sce->sf_idx));                                                                             // (3) 0.05859
/*52  */         memset(sce->zeroes, 1, sizeof(sce->zeroes));                                                                             // (5) 0.05078
/*54  */         return;                                                                                                                  // (18) 0.01758
/*56  */     }                                                                                                                            // (24) 0.007812
/*60  */     //minimum scalefactor index is when minimum nonzero coefficient after quantizing is not clipped                              // 0.0
/*62  */     q0 = av_clip_uint8(log2(q0f)*4 - 69 + SCALE_ONE_POS - SCALE_DIV_512);                                                        // 0.0
/*64  */     //maximum scalefactor index is when maximum coefficient after quantizing is still not zero                                   // 0.0
/*66  */     q1 = av_clip_uint8(log2(q1f)*4 +  6 + SCALE_ONE_POS - SCALE_DIV_512);                                                        // 0.0
/*68  */     //av_log(NULL, AV_LOG_ERROR, "q0 %d, q1 %d\n", q0, q1);                                                                      // 0.0
/*70  */     if (q1 - q0 > 60) {                                                                                                          // 0.0
/*72  */         int q0low  = q0;                                                                                                         // 0.0
/*74  */         int q1high = q1;                                                                                                         // 0.0
/*76  */         //minimum scalefactor index is when maximum nonzero coefficient after quantizing is not clipped                          // 0.0
/*78  */         int qnrg = av_clip_uint8(log2(sqrt(qnrgf/qcnt))*4 - 31 + SCALE_ONE_POS - SCALE_DIV_512);                                 // 0.0
/*80  */         q1 = qnrg + 30;                                                                                                          // 0.0
/*82  */         q0 = qnrg - 30;                                                                                                          // 0.0
/*84  */     //av_log(NULL, AV_LOG_ERROR, "q0 %d, q1 %d\n", q0, q1);                                                                      // 0.0
/*86  */         if (q0 < q0low) {                                                                                                        // 0.0
/*88  */             q1 += q0low - q0;                                                                                                    // 0.0
/*90  */             q0  = q0low;                                                                                                         // 0.0
/*92  */         } else if (q1 > q1high) {                                                                                                // 0.0
/*94  */             q0 -= q1 - q1high;                                                                                                   // 0.0
/*96  */             q1  = q1high;                                                                                                        // 0.0
/*98  */         }                                                                                                                        // 0.0
/*100 */     }                                                                                                                            // 0.0
/*102 */     //av_log(NULL, AV_LOG_ERROR, "q0 %d, q1 %d\n", q0, q1);                                                                      // 0.0
/*106 */     for (i = 0; i < TRELLIS_STATES; i++) {                                                                                       // 0.0
/*108 */         paths[0][i].cost    = 0.0f;                                                                                              // 0.0
/*110 */         paths[0][i].prev    = -1;                                                                                                // 0.0
/*112 */     }                                                                                                                            // 0.0
/*114 */     for (j = 1; j < TRELLIS_STAGES; j++) {                                                                                       // 0.0
/*116 */         for (i = 0; i < TRELLIS_STATES; i++) {                                                                                   // 0.0
/*118 */             paths[j][i].cost    = INFINITY;                                                                                      // 0.0
/*120 */             paths[j][i].prev    = -2;                                                                                            // 0.0
/*122 */         }                                                                                                                        // 0.0
/*124 */     }                                                                                                                            // 0.0
/*126 */     idx = 1;                                                                                                                     // 0.0
/*128 */     abs_pow34_v(s->scoefs, sce->coeffs, 1024);                                                                                   // 0.0
/*130 */     for (w = 0; w < sce->ics.num_windows; w += sce->ics.group_len[w]) {                                                          // 0.0
/*132 */         start = w*128;                                                                                                           // 0.0
/*134 */         for (g = 0; g < sce->ics.num_swb; g++) {                                                                                 // 0.0
/*136 */             const float *coefs = sce->coeffs + start;                                                                            // 0.0
/*138 */             float qmin, qmax;                                                                                                    // 0.0
/*140 */             int nz = 0;                                                                                                          // 0.0
/*144 */             bandaddr[idx] = w * 16 + g;                                                                                          // 0.0
/*146 */             qmin = INT_MAX;                                                                                                      // 0.0
/*148 */             qmax = 0.0f;                                                                                                         // 0.0
/*150 */             for (w2 = 0; w2 < sce->ics.group_len[w]; w2++) {                                                                     // 0.0
/*152 */                 FFPsyBand *band = &s->psy.psy_bands[s->cur_channel*PSY_MAX_BANDS+(w+w2)*16+g];                                   // 0.0
/*154 */                 if (band->energy <= band->threshold || band->threshold == 0.0f) {                                                // 0.0
/*156 */                     sce->zeroes[(w+w2)*16+g] = 1;                                                                                // 0.0
/*158 */                     continue;                                                                                                    // 0.0
/*160 */                 }                                                                                                                // 0.0
/*162 */                 sce->zeroes[(w+w2)*16+g] = 0;                                                                                    // 0.0
/*164 */                 nz = 1;                                                                                                          // 0.0
/*166 */                 for (i = 0; i < sce->ics.swb_sizes[g]; i++) {                                                                    // 0.0
/*168 */                     float t = fabsf(coefs[w2*128+i]);                                                                            // 0.0
/*170 */                     if (t > 0.0f)                                                                                                // 0.0
/*172 */                         qmin = FFMIN(qmin, t);                                                                                   // 0.0
/*174 */                     qmax = FFMAX(qmax, t);                                                                                       // 0.0
/*176 */                 }                                                                                                                // 0.0
/*178 */             }                                                                                                                    // 0.0
/*180 */             if (nz) {                                                                                                            // 0.0
/*182 */                 int minscale, maxscale;                                                                                          // 0.0
/*184 */                 float minrd = INFINITY;                                                                                          // 0.0
/*186 */                 //minimum scalefactor index is when minimum nonzero coefficient after quantizing is not clipped                  // 0.0
/*188 */                 minscale = av_clip_uint8(log2(qmin)*4 - 69 + SCALE_ONE_POS - SCALE_DIV_512);                                     // 0.0
/*190 */                 //maximum scalefactor index is when maximum coefficient after quantizing is still not zero                       // 0.0
/*192 */                 maxscale = av_clip_uint8(log2(qmax)*4 +  6 + SCALE_ONE_POS - SCALE_DIV_512);                                     // 0.0
/*194 */                 minscale = av_clip(minscale - q0, 0, TRELLIS_STATES - 1);                                                        // 0.0
/*196 */                 maxscale = av_clip(maxscale - q0, 0, TRELLIS_STATES);                                                            // 0.0
/*198 */                 for (q = minscale; q < maxscale; q++) {                                                                          // 0.0
/*200 */                     float dist = 0;                                                                                              // 0.0
/*202 */                     int cb = find_min_book(sce->sf_idx[w*16+g], sce->ics.group_len[w], sce->ics.swb_sizes[g], s->scoefs+start);  // 0.0
/*204 */                     for (w2 = 0; w2 < sce->ics.group_len[w]; w2++) {                                                             // 0.0
/*206 */                         FFPsyBand *band = &s->psy.psy_bands[s->cur_channel*PSY_MAX_BANDS+(w+w2)*16+g];                           // 0.0
/*208 */                         dist += quantize_band_cost(s, coefs + w2*128, s->scoefs + start + w2*128, sce->ics.swb_sizes[g],         // 0.0
/*210 */                                                             q + q0, cb, lambda / band->threshold, INFINITY, NULL);               // 0.0
/*212 */                     }                                                                                                            // 0.0
/*214 */                     minrd = FFMIN(minrd, dist);                                                                                  // 0.0
/*218 */                     for (i = 0; i < q1 - q0; i++) {                                                                              // 0.0
/*220 */                         float cost;                                                                                              // 0.0
/*222 */                         if (isinf(paths[idx - 1][i].cost))                                                                       // 0.0
/*224 */                             continue;                                                                                            // 0.0
/*226 */                         cost = paths[idx - 1][i].cost + dist                                                                     // 0.0
/*228 */                                + ff_aac_scalefactor_bits[q - i + SCALE_DIFF_ZERO];                                               // 0.0
/*230 */                         if (cost < paths[idx][q].cost) {                                                                         // 0.0
/*232 */                             paths[idx][q].cost    = cost;                                                                        // 0.0
/*234 */                             paths[idx][q].prev    = i;                                                                           // 0.0
/*236 */                         }                                                                                                        // 0.0
/*238 */                     }                                                                                                            // 0.0
/*240 */                 }                                                                                                                // 0.0
/*242 */             } else {                                                                                                             // 0.0
/*244 */                 for (q = 0; q < q1 - q0; q++) {                                                                                  // 0.0
/*246 */                     if (!isinf(paths[idx - 1][q].cost)) {                                                                        // 0.0
/*248 */                         paths[idx][q].cost = paths[idx - 1][q].cost + 1;                                                         // 0.0
/*250 */                         paths[idx][q].prev = q;                                                                                  // 0.0
/*252 */                         continue;                                                                                                // 0.0
/*254 */                     }                                                                                                            // 0.0
/*256 */                     for (i = 0; i < q1 - q0; i++) {                                                                              // 0.0
/*258 */                         float cost;                                                                                              // 0.0
/*260 */                         if (isinf(paths[idx - 1][i].cost))                                                                       // 0.0
/*262 */                             continue;                                                                                            // 0.0
/*264 */                         cost = paths[idx - 1][i].cost + ff_aac_scalefactor_bits[q - i + SCALE_DIFF_ZERO];                        // 0.0
/*266 */                         if (cost < paths[idx][q].cost) {                                                                         // 0.0
/*268 */                             paths[idx][q].cost    = cost;                                                                        // 0.0
/*270 */                             paths[idx][q].prev    = i;                                                                           // 0.0
/*272 */                         }                                                                                                        // 0.0
/*274 */                     }                                                                                                            // 0.0
/*276 */                 }                                                                                                                // 0.0
/*278 */             }                                                                                                                    // 0.0
/*280 */             sce->zeroes[w*16+g] = !nz;                                                                                           // 0.0
/*282 */             start += sce->ics.swb_sizes[g];                                                                                      // 0.0
/*284 */             idx++;                                                                                                               // 0.0
/*286 */         }                                                                                                                        // 0.0
/*288 */     }                                                                                                                            // 0.0
/*290 */     idx--;                                                                                                                       // 0.0
/*292 */     mincost = paths[idx][0].cost;                                                                                                // 0.0
/*294 */     minq    = 0;                                                                                                                 // 0.0
/*296 */     for (i = 1; i < TRELLIS_STATES; i++) {                                                                                       // 0.0
/*298 */         if (paths[idx][i].cost < mincost) {                                                                                      // 0.0
/*300 */             mincost = paths[idx][i].cost;                                                                                        // 0.0
/*302 */             minq = i;                                                                                                            // 0.0
/*304 */         }                                                                                                                        // 0.0
/*306 */     }                                                                                                                            // 0.0
/*308 */     while (idx) {                                                                                                                // 0.0
/*310 */         sce->sf_idx[bandaddr[idx]] = minq + q0;                                                                                  // 0.0
/*312 */         minq = paths[idx][minq].prev;                                                                                            // 0.0
/*314 */         idx--;                                                                                                                   // 0.0
/*316 */     }                                                                                                                            // 0.0
/*318 */     //set the same quantizers inside window groups                                                                               // 0.0
/*320 */     for (w = 0; w < sce->ics.num_windows; w += sce->ics.group_len[w])                                                            // 0.0
/*322 */         for (g = 0;  g < sce->ics.num_swb; g++)                                                                                  // 0.0
/*324 */             for (w2 = 1; w2 < sce->ics.group_len[w]; w2++)                                                                       // 0.0
/*326 */                 sce->sf_idx[(w+w2)*16+g] = sce->sf_idx[w*16+g];                                                                  // 0.0
/*328 */ }                                                                                                                                // 0.0
