// commit message FFmpeg@527f89e059 (target=1, prob=0.466902, correct=False): avcodec/aacps: Fix undefined behavior
/*0   */ static void stereo_processing(PSContext *ps, INTFLOAT (*l)[32][2], INTFLOAT (*r)[32][2], int is34)  // (4) 0.07227
/*2   */ {                                                                                                   // (15) 0.001953
/*4   */     int e, b, k;                                                                                    // (14) 0.01953
/*8   */     INTFLOAT (*H11)[PS_MAX_NUM_ENV+1][PS_MAX_NR_IIDICC] = ps->H11;                                  // (0) 0.07617
/*10  */     INTFLOAT (*H12)[PS_MAX_NUM_ENV+1][PS_MAX_NR_IIDICC] = ps->H12;                                  // (1) 0.07617
/*12  */     INTFLOAT (*H21)[PS_MAX_NUM_ENV+1][PS_MAX_NR_IIDICC] = ps->H21;                                  // (3) 0.07617
/*14  */     INTFLOAT (*H22)[PS_MAX_NUM_ENV+1][PS_MAX_NR_IIDICC] = ps->H22;                                  // (2) 0.07617
/*16  */     int8_t *opd_hist = ps->opd_hist;                                                                // (12) 0.03906
/*18  */     int8_t *ipd_hist = ps->ipd_hist;                                                                // (13) 0.03906
/*20  */     int8_t iid_mapped_buf[PS_MAX_NUM_ENV][PS_MAX_NR_IIDICC];                                        // (8) 0.06836
/*22  */     int8_t icc_mapped_buf[PS_MAX_NUM_ENV][PS_MAX_NR_IIDICC];                                        // (7) 0.06836
/*24  */     int8_t ipd_mapped_buf[PS_MAX_NUM_ENV][PS_MAX_NR_IIDICC];                                        // (6) 0.06836
/*26  */     int8_t opd_mapped_buf[PS_MAX_NUM_ENV][PS_MAX_NR_IIDICC];                                        // (5) 0.06836
/*28  */     int8_t (*iid_mapped)[PS_MAX_NR_IIDICC] = iid_mapped_buf;                                        // (10) 0.06641
/*30  */     int8_t (*icc_mapped)[PS_MAX_NR_IIDICC] = icc_mapped_buf;                                        // (11) 0.06445
/*32  */     int8_t (*ipd_mapped)[PS_MAX_NR_IIDICC] = ipd_mapped_buf;                                        // (9) 0.06641
/*34  */     int8_t (*opd_mapped)[PS_MAX_NR_IIDICC] = opd_mapped_buf;                                        // 0.0
/*36  */     const int8_t *k_to_i = is34 ? k_to_i_34 : k_to_i_20;                                            // 0.0
/*38  */     TABLE_CONST INTFLOAT (*H_LUT)[8][4] = (PS_BASELINE || ps->icc_mode < 3) ? HA : HB;              // 0.0
/*42  */     //Remapping                                                                                     // 0.0
/*44  */     if (ps->num_env_old) {                                                                          // 0.0
/*46  */         memcpy(H11[0][0], H11[0][ps->num_env_old], PS_MAX_NR_IIDICC*sizeof(H11[0][0][0]));          // 0.0
/*48  */         memcpy(H11[1][0], H11[1][ps->num_env_old], PS_MAX_NR_IIDICC*sizeof(H11[1][0][0]));          // 0.0
/*50  */         memcpy(H12[0][0], H12[0][ps->num_env_old], PS_MAX_NR_IIDICC*sizeof(H12[0][0][0]));          // 0.0
/*52  */         memcpy(H12[1][0], H12[1][ps->num_env_old], PS_MAX_NR_IIDICC*sizeof(H12[1][0][0]));          // 0.0
/*54  */         memcpy(H21[0][0], H21[0][ps->num_env_old], PS_MAX_NR_IIDICC*sizeof(H21[0][0][0]));          // 0.0
/*56  */         memcpy(H21[1][0], H21[1][ps->num_env_old], PS_MAX_NR_IIDICC*sizeof(H21[1][0][0]));          // 0.0
/*58  */         memcpy(H22[0][0], H22[0][ps->num_env_old], PS_MAX_NR_IIDICC*sizeof(H22[0][0][0]));          // 0.0
/*60  */         memcpy(H22[1][0], H22[1][ps->num_env_old], PS_MAX_NR_IIDICC*sizeof(H22[1][0][0]));          // 0.0
/*62  */     }                                                                                               // 0.0
/*66  */     if (is34) {                                                                                     // 0.0
/*68  */         remap34(&iid_mapped, ps->iid_par, ps->nr_iid_par, ps->num_env, 1);                          // 0.0
/*70  */         remap34(&icc_mapped, ps->icc_par, ps->nr_icc_par, ps->num_env, 1);                          // 0.0
/*72  */         if (ps->enable_ipdopd) {                                                                    // 0.0
/*74  */             remap34(&ipd_mapped, ps->ipd_par, ps->nr_ipdopd_par, ps->num_env, 0);                   // 0.0
/*76  */             remap34(&opd_mapped, ps->opd_par, ps->nr_ipdopd_par, ps->num_env, 0);                   // 0.0
/*78  */         }                                                                                           // 0.0
/*80  */         if (!ps->is34bands_old) {                                                                   // 0.0
/*82  */             map_val_20_to_34(H11[0][0]);                                                            // 0.0
/*84  */             map_val_20_to_34(H11[1][0]);                                                            // 0.0
/*86  */             map_val_20_to_34(H12[0][0]);                                                            // 0.0
/*88  */             map_val_20_to_34(H12[1][0]);                                                            // 0.0
/*90  */             map_val_20_to_34(H21[0][0]);                                                            // 0.0
/*92  */             map_val_20_to_34(H21[1][0]);                                                            // 0.0
/*94  */             map_val_20_to_34(H22[0][0]);                                                            // 0.0
/*96  */             map_val_20_to_34(H22[1][0]);                                                            // 0.0
/*98  */             ipdopd_reset(ipd_hist, opd_hist);                                                       // 0.0
/*100 */         }                                                                                           // 0.0
/*102 */     } else {                                                                                        // 0.0
/*104 */         remap20(&iid_mapped, ps->iid_par, ps->nr_iid_par, ps->num_env, 1);                          // 0.0
/*106 */         remap20(&icc_mapped, ps->icc_par, ps->nr_icc_par, ps->num_env, 1);                          // 0.0
/*108 */         if (ps->enable_ipdopd) {                                                                    // 0.0
/*110 */             remap20(&ipd_mapped, ps->ipd_par, ps->nr_ipdopd_par, ps->num_env, 0);                   // 0.0
/*112 */             remap20(&opd_mapped, ps->opd_par, ps->nr_ipdopd_par, ps->num_env, 0);                   // 0.0
/*114 */         }                                                                                           // 0.0
/*116 */         if (ps->is34bands_old) {                                                                    // 0.0
/*118 */             map_val_34_to_20(H11[0][0]);                                                            // 0.0
/*120 */             map_val_34_to_20(H11[1][0]);                                                            // 0.0
/*122 */             map_val_34_to_20(H12[0][0]);                                                            // 0.0
/*124 */             map_val_34_to_20(H12[1][0]);                                                            // 0.0
/*126 */             map_val_34_to_20(H21[0][0]);                                                            // 0.0
/*128 */             map_val_34_to_20(H21[1][0]);                                                            // 0.0
/*130 */             map_val_34_to_20(H22[0][0]);                                                            // 0.0
/*132 */             map_val_34_to_20(H22[1][0]);                                                            // 0.0
/*134 */             ipdopd_reset(ipd_hist, opd_hist);                                                       // 0.0
/*136 */         }                                                                                           // 0.0
/*138 */     }                                                                                               // 0.0
/*142 */     //Mixing                                                                                        // 0.0
/*144 */     for (e = 0; e < ps->num_env; e++) {                                                             // 0.0
/*146 */         for (b = 0; b < NR_PAR_BANDS[is34]; b++) {                                                  // 0.0
/*148 */             INTFLOAT h11, h12, h21, h22;                                                            // 0.0
/*150 */             h11 = H_LUT[iid_mapped[e][b] + 7 + 23 * ps->iid_quant][icc_mapped[e][b]][0];            // 0.0
/*152 */             h12 = H_LUT[iid_mapped[e][b] + 7 + 23 * ps->iid_quant][icc_mapped[e][b]][1];            // 0.0
/*154 */             h21 = H_LUT[iid_mapped[e][b] + 7 + 23 * ps->iid_quant][icc_mapped[e][b]][2];            // 0.0
/*156 */             h22 = H_LUT[iid_mapped[e][b] + 7 + 23 * ps->iid_quant][icc_mapped[e][b]][3];            // 0.0
/*160 */             if (!PS_BASELINE && ps->enable_ipdopd && b < NR_IPDOPD_BANDS[is34]) {                   // 0.0
/*162 */                 //The spec say says to only run this smoother when enable_ipdopd                    // 0.0
/*164 */                 //is set but the reference decoder appears to run it constantly                     // 0.0
/*166 */                 INTFLOAT h11i, h12i, h21i, h22i;                                                    // 0.0
/*168 */                 INTFLOAT ipd_adj_re, ipd_adj_im;                                                    // 0.0
/*170 */                 int opd_idx = opd_hist[b] * 8 + opd_mapped[e][b];                                   // 0.0
/*172 */                 int ipd_idx = ipd_hist[b] * 8 + ipd_mapped[e][b];                                   // 0.0
/*174 */                 INTFLOAT opd_re = pd_re_smooth[opd_idx];                                            // 0.0
/*176 */                 INTFLOAT opd_im = pd_im_smooth[opd_idx];                                            // 0.0
/*178 */                 INTFLOAT ipd_re = pd_re_smooth[ipd_idx];                                            // 0.0
/*180 */                 INTFLOAT ipd_im = pd_im_smooth[ipd_idx];                                            // 0.0
/*182 */                 opd_hist[b] = opd_idx & 0x3F;                                                       // 0.0
/*184 */                 ipd_hist[b] = ipd_idx & 0x3F;                                                       // 0.0
/*188 */                 ipd_adj_re = AAC_MADD30(opd_re, ipd_re, opd_im, ipd_im);                            // 0.0
/*190 */                 ipd_adj_im = AAC_MSUB30(opd_im, ipd_re, opd_re, ipd_im);                            // 0.0
/*192 */                 h11i = AAC_MUL30(h11,  opd_im);                                                     // 0.0
/*194 */                 h11  = AAC_MUL30(h11,  opd_re);                                                     // 0.0
/*196 */                 h12i = AAC_MUL30(h12,  ipd_adj_im);                                                 // 0.0
/*198 */                 h12  = AAC_MUL30(h12,  ipd_adj_re);                                                 // 0.0
/*200 */                 h21i = AAC_MUL30(h21,  opd_im);                                                     // 0.0
/*202 */                 h21  = AAC_MUL30(h21,  opd_re);                                                     // 0.0
/*204 */                 h22i = AAC_MUL30(h22,  ipd_adj_im);                                                 // 0.0
/*206 */                 h22  = AAC_MUL30(h22,  ipd_adj_re);                                                 // 0.0
/*208 */                 H11[1][e+1][b] = h11i;                                                              // 0.0
/*210 */                 H12[1][e+1][b] = h12i;                                                              // 0.0
/*212 */                 H21[1][e+1][b] = h21i;                                                              // 0.0
/*214 */                 H22[1][e+1][b] = h22i;                                                              // 0.0
/*216 */             }                                                                                       // 0.0
/*218 */             H11[0][e+1][b] = h11;                                                                   // 0.0
/*220 */             H12[0][e+1][b] = h12;                                                                   // 0.0
/*222 */             H21[0][e+1][b] = h21;                                                                   // 0.0
/*224 */             H22[0][e+1][b] = h22;                                                                   // 0.0
/*226 */         }                                                                                           // 0.0
/*228 */         for (k = 0; k < NR_BANDS[is34]; k++) {                                                      // 0.0
/*230 */             LOCAL_ALIGNED_16(INTFLOAT, h, [2], [4]);                                                // 0.0
/*232 */             LOCAL_ALIGNED_16(INTFLOAT, h_step, [2], [4]);                                           // 0.0
/*234 */             int start = ps->border_position[e];                                                     // 0.0
/*236 */             int stop  = ps->border_position[e+1];                                                   // 0.0
/*238 */             INTFLOAT width = Q30(1.f) / ((stop - start) ? (stop - start) : 1);                      // 0.0
/*240 */ #if USE_FIXED                                                                                       // 0.0
/*242 */             width <<= 1;                                                                            // 0.0
/*244 */ #endif                                                                                              // 0.0
/*246 */             b = k_to_i[k];                                                                          // 0.0
/*248 */             h[0][0] = H11[0][e][b];                                                                 // 0.0
/*250 */             h[0][1] = H12[0][e][b];                                                                 // 0.0
/*252 */             h[0][2] = H21[0][e][b];                                                                 // 0.0
/*254 */             h[0][3] = H22[0][e][b];                                                                 // 0.0
/*256 */             if (!PS_BASELINE && ps->enable_ipdopd) {                                                // 0.0
/*258 */             //Is this necessary? ps_04_new seems unchanged                                          // 0.0
/*260 */             if ((is34 && k <= 13 && k >= 9) || (!is34 && k <= 1)) {                                 // 0.0
/*262 */                 h[1][0] = -H11[1][e][b];                                                            // 0.0
/*264 */                 h[1][1] = -H12[1][e][b];                                                            // 0.0
/*266 */                 h[1][2] = -H21[1][e][b];                                                            // 0.0
/*268 */                 h[1][3] = -H22[1][e][b];                                                            // 0.0
/*270 */             } else {                                                                                // 0.0
/*272 */                 h[1][0] = H11[1][e][b];                                                             // 0.0
/*274 */                 h[1][1] = H12[1][e][b];                                                             // 0.0
/*276 */                 h[1][2] = H21[1][e][b];                                                             // 0.0
/*278 */                 h[1][3] = H22[1][e][b];                                                             // 0.0
/*280 */             }                                                                                       // 0.0
/*282 */             }                                                                                       // 0.0
/*284 */             //Interpolation                                                                         // 0.0
/*286 */             h_step[0][0] = AAC_MSUB31_V3(H11[0][e+1][b], h[0][0], width);                           // 0.0
/*288 */             h_step[0][1] = AAC_MSUB31_V3(H12[0][e+1][b], h[0][1], width);                           // 0.0
/*290 */             h_step[0][2] = AAC_MSUB31_V3(H21[0][e+1][b], h[0][2], width);                           // 0.0
/*292 */             h_step[0][3] = AAC_MSUB31_V3(H22[0][e+1][b], h[0][3], width);                           // 0.0
/*294 */             if (!PS_BASELINE && ps->enable_ipdopd) {                                                // 0.0
/*296 */                 h_step[1][0] = AAC_MSUB31_V3(H11[1][e+1][b], h[1][0], width);                       // 0.0
/*298 */                 h_step[1][1] = AAC_MSUB31_V3(H12[1][e+1][b], h[1][1], width);                       // 0.0
/*300 */                 h_step[1][2] = AAC_MSUB31_V3(H21[1][e+1][b], h[1][2], width);                       // 0.0
/*302 */                 h_step[1][3] = AAC_MSUB31_V3(H22[1][e+1][b], h[1][3], width);                       // 0.0
/*304 */             }                                                                                       // 0.0
/*306 */             ps->dsp.stereo_interpolate[!PS_BASELINE && ps->enable_ipdopd](                          // 0.0
/*308 */                 l[k] + start + 1, r[k] + start + 1,                                                 // 0.0
/*310 */                 h, h_step, stop - start);                                                           // 0.0
/*312 */         }                                                                                           // 0.0
/*314 */     }                                                                                               // 0.0
/*316 */ }                                                                                                   // 0.0
