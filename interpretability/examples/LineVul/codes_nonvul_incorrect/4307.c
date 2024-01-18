// commit message FFmpeg@6ebc724060 (target=0, prob=0.5873279, correct=False): aacsbr: Check that bs_num_env is valid before writing arrays with it as an offset.
/*0   */ static int read_sbr_grid(AACContext *ac, SpectralBandReplication *sbr,                                                // (7) 0.04691
/*2   */                          GetBitContext *gb, SBRData *ch_data)                                                         // (2) 0.07421
/*4   */ {                                                                                                                     // (19) 0.001953
/*6   */     int i;                                                                                                            // (18) 0.01172
/*8   */     unsigned bs_pointer = 0;                                                                                          // (16) 0.02149
/*10  */     // frameLengthFlag ? 15 : 16; 960 sample length frames unsupported; this value is numTimeSlots                    // (6) 0.04894
/*12  */     int abs_bord_trail = 16;                                                                                          // (15) 0.02734
/*14  */     int num_rel_lead, num_rel_trail;                                                                                  // (14) 0.0332
/*16  */     unsigned bs_num_env_old = ch_data->bs_num_env;                                                                    // (10) 0.04491
/*20  */     ch_data->bs_freq_res[0] = ch_data->bs_freq_res[ch_data->bs_num_env];                                              // (3) 0.0742
/*22  */     ch_data->bs_amp_res = sbr->bs_amp_res_header;                                                                     // (9) 0.04687
/*24  */     ch_data->t_env_num_env_old = ch_data->t_env[bs_num_env_old];                                                      // (4) 0.06444
/*28  */     switch (ch_data->bs_frame_class = get_bits(gb, 2)) {                                                              // (8) 0.04687
/*30  */     case FIXFIX:                                                                                                      // (17) 0.01367
/*32  */         ch_data->bs_num_env                 = 1 << get_bits(gb, 2);                                                   // (1) 0.08397
/*34  */         num_rel_lead                        = ch_data->bs_num_env - 1;                                                // (0) 0.09373
/*36  */         if (ch_data->bs_num_env == 1)                                                                                 // (13) 0.04101
/*38  */             ch_data->bs_amp_res = 0;                                                                                  // (11) 0.04491
/*42  */         if (ch_data->bs_num_env > 4) {                                                                                // (12) 0.04296
/*44  */             av_log(ac->avccontext, AV_LOG_ERROR,                                                                      // (5) 0.05468
/*46  */                    "Invalid bitstream, too many SBR envelopes in FIXFIX type SBR frame: %d\n",                        // 0.0
/*48  */                    ch_data->bs_num_env);                                                                              // 0.0
/*50  */             return -1;                                                                                                // 0.0
/*52  */         }                                                                                                             // 0.0
/*56  */         ch_data->t_env[0]                   = 0;                                                                      // 0.0
/*58  */         ch_data->t_env[ch_data->bs_num_env] = abs_bord_trail;                                                         // 0.0
/*62  */         abs_bord_trail = (abs_bord_trail + (ch_data->bs_num_env >> 1)) /                                              // 0.0
/*64  */                    ch_data->bs_num_env;                                                                               // 0.0
/*66  */         for (i = 0; i < num_rel_lead; i++)                                                                            // 0.0
/*68  */             ch_data->t_env[i + 1] = ch_data->t_env[i] + abs_bord_trail;                                               // 0.0
/*72  */         ch_data->bs_freq_res[1] = get_bits1(gb);                                                                      // 0.0
/*74  */         for (i = 1; i < ch_data->bs_num_env; i++)                                                                     // 0.0
/*76  */             ch_data->bs_freq_res[i + 1] = ch_data->bs_freq_res[1];                                                    // 0.0
/*78  */         break;                                                                                                        // 0.0
/*80  */     case FIXVAR:                                                                                                      // 0.0
/*82  */         abs_bord_trail                     += get_bits(gb, 2);                                                        // 0.0
/*84  */         num_rel_trail                       = get_bits(gb, 2);                                                        // 0.0
/*86  */         ch_data->bs_num_env                 = num_rel_trail + 1;                                                      // 0.0
/*88  */         ch_data->t_env[0]                   = 0;                                                                      // 0.0
/*90  */         ch_data->t_env[ch_data->bs_num_env] = abs_bord_trail;                                                         // 0.0
/*94  */         for (i = 0; i < num_rel_trail; i++)                                                                           // 0.0
/*96  */             ch_data->t_env[ch_data->bs_num_env - 1 - i] =                                                             // 0.0
/*98  */                 ch_data->t_env[ch_data->bs_num_env - i] - 2 * get_bits(gb, 2) - 2;                                    // 0.0
/*102 */         bs_pointer = get_bits(gb, ceil_log2[ch_data->bs_num_env]);                                                    // 0.0
/*106 */         for (i = 0; i < ch_data->bs_num_env; i++)                                                                     // 0.0
/*108 */             ch_data->bs_freq_res[ch_data->bs_num_env - i] = get_bits1(gb);                                            // 0.0
/*110 */         break;                                                                                                        // 0.0
/*112 */     case VARFIX:                                                                                                      // 0.0
/*114 */         ch_data->t_env[0]                   = get_bits(gb, 2);                                                        // 0.0
/*116 */         num_rel_lead                        = get_bits(gb, 2);                                                        // 0.0
/*118 */         ch_data->bs_num_env                 = num_rel_lead + 1;                                                       // 0.0
/*120 */         ch_data->t_env[ch_data->bs_num_env] = abs_bord_trail;                                                         // 0.0
/*124 */         for (i = 0; i < num_rel_lead; i++)                                                                            // 0.0
/*126 */             ch_data->t_env[i + 1] = ch_data->t_env[i] + 2 * get_bits(gb, 2) + 2;                                      // 0.0
/*130 */         bs_pointer = get_bits(gb, ceil_log2[ch_data->bs_num_env]);                                                    // 0.0
/*134 */         get_bits1_vector(gb, ch_data->bs_freq_res + 1, ch_data->bs_num_env);                                          // 0.0
/*136 */         break;                                                                                                        // 0.0
/*138 */     case VARVAR:                                                                                                      // 0.0
/*140 */         ch_data->t_env[0]                   = get_bits(gb, 2);                                                        // 0.0
/*142 */         abs_bord_trail                     += get_bits(gb, 2);                                                        // 0.0
/*144 */         num_rel_lead                        = get_bits(gb, 2);                                                        // 0.0
/*146 */         num_rel_trail                       = get_bits(gb, 2);                                                        // 0.0
/*148 */         ch_data->bs_num_env                 = num_rel_lead + num_rel_trail + 1;                                       // 0.0
/*150 */         ch_data->t_env[ch_data->bs_num_env] = abs_bord_trail;                                                         // 0.0
/*154 */         if (ch_data->bs_num_env > 5) {                                                                                // 0.0
/*156 */             av_log(ac->avccontext, AV_LOG_ERROR,                                                                      // 0.0
/*158 */                    "Invalid bitstream, too many SBR envelopes in VARVAR type SBR frame: %d\n",                        // 0.0
/*160 */                    ch_data->bs_num_env);                                                                              // 0.0
/*162 */             return -1;                                                                                                // 0.0
/*164 */         }                                                                                                             // 0.0
/*168 */         for (i = 0; i < num_rel_lead; i++)                                                                            // 0.0
/*170 */             ch_data->t_env[i + 1] = ch_data->t_env[i] + 2 * get_bits(gb, 2) + 2;                                      // 0.0
/*172 */         for (i = 0; i < num_rel_trail; i++)                                                                           // 0.0
/*174 */             ch_data->t_env[ch_data->bs_num_env - 1 - i] =                                                             // 0.0
/*176 */                 ch_data->t_env[ch_data->bs_num_env - i] - 2 * get_bits(gb, 2) - 2;                                    // 0.0
/*180 */         bs_pointer = get_bits(gb, ceil_log2[ch_data->bs_num_env]);                                                    // 0.0
/*184 */         get_bits1_vector(gb, ch_data->bs_freq_res + 1, ch_data->bs_num_env);                                          // 0.0
/*186 */         break;                                                                                                        // 0.0
/*188 */     }                                                                                                                 // 0.0
/*192 */     if (bs_pointer > ch_data->bs_num_env + 1) {                                                                       // 0.0
/*194 */         av_log(ac->avccontext, AV_LOG_ERROR,                                                                          // 0.0
/*196 */                "Invalid bitstream, bs_pointer points to a middle noise border outside the time borders table: %d\n",  // 0.0
/*198 */                bs_pointer);                                                                                           // 0.0
/*200 */         return -1;                                                                                                    // 0.0
/*202 */     }                                                                                                                 // 0.0
/*206 */     ch_data->bs_num_noise = (ch_data->bs_num_env > 1) + 1;                                                            // 0.0
/*210 */     ch_data->t_q[0]                     = ch_data->t_env[0];                                                          // 0.0
/*212 */     ch_data->t_q[ch_data->bs_num_noise] = ch_data->t_env[ch_data->bs_num_env];                                        // 0.0
/*214 */     if (ch_data->bs_num_noise > 1) {                                                                                  // 0.0
/*216 */         unsigned int idx;                                                                                             // 0.0
/*218 */         if (ch_data->bs_frame_class == FIXFIX) {                                                                      // 0.0
/*220 */             idx = ch_data->bs_num_env >> 1;                                                                           // 0.0
/*222 */         } else if (ch_data->bs_frame_class & 1) { // FIXVAR or VARVAR                                                 // 0.0
/*224 */             idx = ch_data->bs_num_env - FFMAX(bs_pointer - 1, 1);                                                     // 0.0
/*226 */         } else { // VARFIX                                                                                            // 0.0
/*228 */             if (!bs_pointer)                                                                                          // 0.0
/*230 */                 idx = 1;                                                                                              // 0.0
/*232 */             else if (bs_pointer == 1)                                                                                 // 0.0
/*234 */                 idx = ch_data->bs_num_env - 1;                                                                        // 0.0
/*236 */             else // bs_pointer > 1                                                                                    // 0.0
/*238 */                 idx = bs_pointer - 1;                                                                                 // 0.0
/*240 */         }                                                                                                             // 0.0
/*242 */         ch_data->t_q[1] = ch_data->t_env[idx];                                                                        // 0.0
/*244 */     }                                                                                                                 // 0.0
/*248 */     ch_data->e_a[0] = -(ch_data->e_a[1] != bs_num_env_old); // l_APrev                                                // 0.0
/*250 */     ch_data->e_a[1] = -1;                                                                                             // 0.0
/*252 */     if ((ch_data->bs_frame_class & 1) && bs_pointer) { // FIXVAR or VARVAR and bs_pointer != 0                        // 0.0
/*254 */         ch_data->e_a[1] = ch_data->bs_num_env + 1 - bs_pointer;                                                       // 0.0
/*256 */     } else if ((ch_data->bs_frame_class == 2) && (bs_pointer > 1)) // VARFIX and bs_pointer > 1                       // 0.0
/*258 */         ch_data->e_a[1] = bs_pointer - 1;                                                                             // 0.0
/*262 */     return 0;                                                                                                         // 0.0
/*264 */ }                                                                                                                     // 0.0
