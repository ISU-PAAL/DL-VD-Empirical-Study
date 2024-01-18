// commit message FFmpeg@fe8c9420dd (target=1, prob=0.4586996, correct=False): avcodec/aacps: Check border_position to be monotone
/*0   */ int AAC_RENAME(ff_ps_read_data)(AVCodecContext *avctx, GetBitContext *gb_host, PSContext *ps, int bits_left)   // (0) 0.08008
/*2   */ {                                                                                                              // (22) 0.001954
/*4   */     int e;                                                                                                     // (20) 0.01172
/*6   */     int bit_count_start = get_bits_count(gb_host);                                                             // (10) 0.03906
/*8   */     int header;                                                                                                // (21) 0.01172
/*10  */     int bits_consumed;                                                                                         // (18) 0.01758
/*12  */     GetBitContext gbc = *gb_host, *gb = &gbc;                                                                  // (7) 0.04102
/*16  */     header = get_bits1(gb);                                                                                    // (16) 0.02344
/*18  */     if (header) {     //enable_ps_header                                                                       // (12) 0.03516
/*20  */         ps->enable_iid = get_bits1(gb);                                                                        // (8) 0.04102
/*22  */         if (ps->enable_iid) {                                                                                  // (14) 0.0332
/*24  */             int iid_mode = get_bits(gb, 3);                                                                    // (6) 0.04883
/*26  */             if (iid_mode > 5) {                                                                                // (9) 0.04102
/*28  */                 av_log(avctx, AV_LOG_ERROR, "iid_mode %d is reserved.\n",                                      // (1) 0.08008
/*30  */                        iid_mode);                                                                              // (5) 0.05273
/*32  */                 goto err;                                                                                      // (13) 0.03516
/*34  */             }                                                                                                  // (17) 0.02344
/*36  */             ps->nr_iid_par    = nr_iidicc_par_tab[iid_mode];                                                   // (3) 0.07617
/*38  */             ps->iid_quant     = iid_mode > 2;                                                                  // (4) 0.05664
/*40  */             ps->nr_ipdopd_par = nr_iidopd_par_tab[iid_mode];                                                   // (2) 0.07617
/*42  */         }                                                                                                      // (19) 0.01562
/*44  */         ps->enable_icc = get_bits1(gb);                                                                        // (11) 0.03906
/*46  */         if (ps->enable_icc) {                                                                                  // (15) 0.03125
/*48  */             ps->icc_mode = get_bits(gb, 3);                                                                    // 0.0
/*50  */             if (ps->icc_mode > 5) {                                                                            // 0.0
/*52  */                 av_log(avctx, AV_LOG_ERROR, "icc_mode %d is reserved.\n",                                      // 0.0
/*54  */                        ps->icc_mode);                                                                          // 0.0
/*56  */                 goto err;                                                                                      // 0.0
/*58  */             }                                                                                                  // 0.0
/*60  */             ps->nr_icc_par = nr_iidicc_par_tab[ps->icc_mode];                                                  // 0.0
/*62  */         }                                                                                                      // 0.0
/*64  */         ps->enable_ext = get_bits1(gb);                                                                        // 0.0
/*66  */     }                                                                                                          // 0.0
/*70  */     ps->frame_class = get_bits1(gb);                                                                           // 0.0
/*72  */     ps->num_env_old = ps->num_env;                                                                             // 0.0
/*74  */     ps->num_env     = num_env_tab[ps->frame_class][get_bits(gb, 2)];                                           // 0.0
/*78  */     ps->border_position[0] = -1;                                                                               // 0.0
/*80  */     if (ps->frame_class) {                                                                                     // 0.0
/*82  */         for (e = 1; e <= ps->num_env; e++)                                                                     // 0.0
/*84  */             ps->border_position[e] = get_bits(gb, 5);                                                          // 0.0
/*86  */     } else                                                                                                     // 0.0
/*88  */         for (e = 1; e <= ps->num_env; e++)                                                                     // 0.0
/*90  */             ps->border_position[e] = (e * numQMFSlots >> ff_log2_tab[ps->num_env]) - 1;                        // 0.0
/*94  */     if (ps->enable_iid) {                                                                                      // 0.0
/*96  */         for (e = 0; e < ps->num_env; e++) {                                                                    // 0.0
/*98  */             int dt = get_bits1(gb);                                                                            // 0.0
/*100 */             if (read_iid_data(avctx, gb, ps, ps->iid_par, huff_iid[2*dt+ps->iid_quant], e, dt))                // 0.0
/*102 */                 goto err;                                                                                      // 0.0
/*104 */         }                                                                                                      // 0.0
/*106 */     } else                                                                                                     // 0.0
/*108 */         memset(ps->iid_par, 0, sizeof(ps->iid_par));                                                           // 0.0
/*112 */     if (ps->enable_icc)                                                                                        // 0.0
/*114 */         for (e = 0; e < ps->num_env; e++) {                                                                    // 0.0
/*116 */             int dt = get_bits1(gb);                                                                            // 0.0
/*118 */             if (read_icc_data(avctx, gb, ps, ps->icc_par, dt ? huff_icc_dt : huff_icc_df, e, dt))              // 0.0
/*120 */                 goto err;                                                                                      // 0.0
/*122 */         }                                                                                                      // 0.0
/*124 */     else                                                                                                       // 0.0
/*126 */         memset(ps->icc_par, 0, sizeof(ps->icc_par));                                                           // 0.0
/*130 */     if (ps->enable_ext) {                                                                                      // 0.0
/*132 */         int cnt = get_bits(gb, 4);                                                                             // 0.0
/*134 */         if (cnt == 15) {                                                                                       // 0.0
/*136 */             cnt += get_bits(gb, 8);                                                                            // 0.0
/*138 */         }                                                                                                      // 0.0
/*140 */         cnt *= 8;                                                                                              // 0.0
/*142 */         while (cnt > 7) {                                                                                      // 0.0
/*144 */             int ps_extension_id = get_bits(gb, 2);                                                             // 0.0
/*146 */             cnt -= 2 + ps_read_extension_data(gb, ps, ps_extension_id);                                        // 0.0
/*148 */         }                                                                                                      // 0.0
/*150 */         if (cnt < 0) {                                                                                         // 0.0
/*152 */             av_log(avctx, AV_LOG_ERROR, "ps extension overflow %d\n", cnt);                                    // 0.0
/*154 */             goto err;                                                                                          // 0.0
/*156 */         }                                                                                                      // 0.0
/*158 */         skip_bits(gb, cnt);                                                                                    // 0.0
/*160 */     }                                                                                                          // 0.0
/*164 */     ps->enable_ipdopd &= !PS_BASELINE;                                                                         // 0.0
/*168 */     //Fix up envelopes                                                                                         // 0.0
/*170 */     if (!ps->num_env || ps->border_position[ps->num_env] < numQMFSlots - 1) {                                  // 0.0
/*172 */         //Create a fake envelope                                                                               // 0.0
/*174 */         int source = ps->num_env ? ps->num_env - 1 : ps->num_env_old - 1;                                      // 0.0
/*176 */         int b;                                                                                                 // 0.0
/*178 */         if (source >= 0 && source != ps->num_env) {                                                            // 0.0
/*180 */             if (ps->enable_iid) {                                                                              // 0.0
/*182 */                 memcpy(ps->iid_par+ps->num_env, ps->iid_par+source, sizeof(ps->iid_par[0]));                   // 0.0
/*184 */             }                                                                                                  // 0.0
/*186 */             if (ps->enable_icc) {                                                                              // 0.0
/*188 */                 memcpy(ps->icc_par+ps->num_env, ps->icc_par+source, sizeof(ps->icc_par[0]));                   // 0.0
/*190 */             }                                                                                                  // 0.0
/*192 */             if (ps->enable_ipdopd) {                                                                           // 0.0
/*194 */                 memcpy(ps->ipd_par+ps->num_env, ps->ipd_par+source, sizeof(ps->ipd_par[0]));                   // 0.0
/*196 */                 memcpy(ps->opd_par+ps->num_env, ps->opd_par+source, sizeof(ps->opd_par[0]));                   // 0.0
/*198 */             }                                                                                                  // 0.0
/*200 */         }                                                                                                      // 0.0
/*202 */         if (ps->enable_iid){                                                                                   // 0.0
/*204 */             for (b = 0; b < ps->nr_iid_par; b++) {                                                             // 0.0
/*206 */                 if (FFABS(ps->iid_par[ps->num_env][b]) > 7 + 8 * ps->iid_quant) {                              // 0.0
/*208 */                     av_log(avctx, AV_LOG_ERROR, "iid_par invalid\n");                                          // 0.0
/*210 */                     goto err;                                                                                  // 0.0
/*212 */                 }                                                                                              // 0.0
/*214 */             }                                                                                                  // 0.0
/*216 */         }                                                                                                      // 0.0
/*218 */         if (ps->enable_icc){                                                                                   // 0.0
/*220 */             for (b = 0; b < ps->nr_iid_par; b++) {                                                             // 0.0
/*222 */                 if (ps->icc_par[ps->num_env][b] > 7U) {                                                        // 0.0
/*224 */                     av_log(avctx, AV_LOG_ERROR, "icc_par invalid\n");                                          // 0.0
/*226 */                     goto err;                                                                                  // 0.0
/*228 */                 }                                                                                              // 0.0
/*230 */             }                                                                                                  // 0.0
/*232 */         }                                                                                                      // 0.0
/*234 */         ps->num_env++;                                                                                         // 0.0
/*236 */         ps->border_position[ps->num_env] = numQMFSlots - 1;                                                    // 0.0
/*238 */     }                                                                                                          // 0.0
/*244 */     ps->is34bands_old = ps->is34bands;                                                                         // 0.0
/*246 */     if (!PS_BASELINE && (ps->enable_iid || ps->enable_icc))                                                    // 0.0
/*248 */         ps->is34bands = (ps->enable_iid && ps->nr_iid_par == 34) ||                                            // 0.0
/*250 */                         (ps->enable_icc && ps->nr_icc_par == 34);                                              // 0.0
/*254 */     //Baseline                                                                                                 // 0.0
/*256 */     if (!ps->enable_ipdopd) {                                                                                  // 0.0
/*258 */         memset(ps->ipd_par, 0, sizeof(ps->ipd_par));                                                           // 0.0
/*260 */         memset(ps->opd_par, 0, sizeof(ps->opd_par));                                                           // 0.0
/*262 */     }                                                                                                          // 0.0
/*266 */     if (header)                                                                                                // 0.0
/*268 */         ps->start = 1;                                                                                         // 0.0
/*272 */     bits_consumed = get_bits_count(gb) - bit_count_start;                                                      // 0.0
/*274 */     if (bits_consumed <= bits_left) {                                                                          // 0.0
/*276 */         skip_bits_long(gb_host, bits_consumed);                                                                // 0.0
/*278 */         return bits_consumed;                                                                                  // 0.0
/*280 */     }                                                                                                          // 0.0
/*282 */     av_log(avctx, AV_LOG_ERROR, "Expected to read %d PS bits actually read %d.\n", bits_left, bits_consumed);  // 0.0
/*284 */ err:                                                                                                           // 0.0
/*286 */     ps->start = 0;                                                                                             // 0.0
/*288 */     skip_bits_long(gb_host, bits_left);                                                                        // 0.0
/*290 */     memset(ps->iid_par, 0, sizeof(ps->iid_par));                                                               // 0.0
/*292 */     memset(ps->icc_par, 0, sizeof(ps->icc_par));                                                               // 0.0
/*294 */     memset(ps->ipd_par, 0, sizeof(ps->ipd_par));                                                               // 0.0
/*296 */     memset(ps->opd_par, 0, sizeof(ps->opd_par));                                                               // 0.0
/*298 */     return bits_left;                                                                                          // 0.0
/*300 */ }                                                                                                              // 0.0
