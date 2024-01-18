// commit message FFmpeg@3ca5df36a5 (target=1, prob=0.80834323, correct=True): wmall: use AVFrame API properly
/*0   */ static int decode_subframe(WmallDecodeCtx *s)                                                     // (15) 0.03321
/*2   */ {                                                                                                 // (24) 0.001983
/*4   */     int offset        = s->samples_per_frame;                                                     // (7) 0.04294
/*6   */     int subframe_len  = s->samples_per_frame;                                                     // (14) 0.03709
/*8   */     int total_samples = s->samples_per_frame * s->num_channels;                                   // (1) 0.0488
/*10  */     int i, j, rawpcm_tile, padding_zeroes, res;                                                   // (8) 0.04139
/*14  */     s->subframe_offset = get_bits_count(&s->gb);                                                  // (12) 0.03905
/*18  */     /* reset channel context and find the next block offset and size                              // (19) 0.02928
/*20  */         == the next block of the channel with the smallest number of                              // (13) 0.03709
/*22  */         decoded samples */                                                                        // (21) 0.02147
/*24  */     for (i = 0; i < s->num_channels; i++) {                                                       // (10) 0.04099
/*26  */         if (offset > s->channel[i].decoded_samples) {                                             // (4) 0.04685
/*28  */             offset = s->channel[i].decoded_samples;                                               // (2) 0.0488
/*30  */             subframe_len =                                                                        // (18) 0.03123
/*32  */                 s->channel[i].subframe_len[s->channel[i].cur_subframe];                           // (0) 0.07222
/*34  */         }                                                                                         // (22) 0.01562
/*36  */     }                                                                                             // (23) 0.007809
/*40  */     /* get a list of all channels that contain the estimated block */                             // (17) 0.03123
/*42  */     s->channels_for_cur_subframe = 0;                                                             // (16) 0.03318
/*44  */     for (i = 0; i < s->num_channels; i++) {                                                       // (11) 0.04099
/*46  */         const int cur_subframe = s->channel[i].cur_subframe;                                      // (3) 0.0488
/*48  */         /* subtract already processed samples */                                                  // (20) 0.02537
/*50  */         total_samples -= s->channel[i].decoded_samples;                                           // (5) 0.04685
/*54  */         /* and count if there are multiple subframes that match our profile */                    // (9) 0.04099
/*56  */         if (offset == s->channel[i].decoded_samples &&                                            // (6) 0.0449
/*58  */             subframe_len == s->channel[i].subframe_len[cur_subframe]) {                           // 0.0
/*60  */             total_samples -= s->channel[i].subframe_len[cur_subframe];                            // 0.0
/*62  */             s->channel[i].decoded_samples +=                                                      // 0.0
/*64  */                 s->channel[i].subframe_len[cur_subframe];                                         // 0.0
/*66  */             s->channel_indexes_for_cur_subframe[s->channels_for_cur_subframe] = i;                // 0.0
/*68  */             ++s->channels_for_cur_subframe;                                                       // 0.0
/*70  */         }                                                                                         // 0.0
/*72  */     }                                                                                             // 0.0
/*76  */     /* check if the frame will be complete after processing the                                   // 0.0
/*78  */         estimated block */                                                                        // 0.0
/*80  */     if (!total_samples)                                                                           // 0.0
/*82  */         s->parsed_all_subframes = 1;                                                              // 0.0
/*88  */     s->seekable_tile = get_bits1(&s->gb);                                                         // 0.0
/*90  */     if (s->seekable_tile) {                                                                       // 0.0
/*92  */         clear_codec_buffers(s);                                                                   // 0.0
/*96  */         s->do_arith_coding    = get_bits1(&s->gb);                                                // 0.0
/*98  */         if (s->do_arith_coding) {                                                                 // 0.0
/*100 */             avpriv_request_sample(s->avctx, "Arithmetic coding");                                 // 0.0
/*102 */             return AVERROR_PATCHWELCOME;                                                          // 0.0
/*104 */         }                                                                                         // 0.0
/*106 */         s->do_ac_filter       = get_bits1(&s->gb);                                                // 0.0
/*108 */         s->do_inter_ch_decorr = get_bits1(&s->gb);                                                // 0.0
/*110 */         s->do_mclms           = get_bits1(&s->gb);                                                // 0.0
/*114 */         if (s->do_ac_filter)                                                                      // 0.0
/*116 */             decode_ac_filter(s);                                                                  // 0.0
/*120 */         if (s->do_mclms)                                                                          // 0.0
/*122 */             decode_mclms(s);                                                                      // 0.0
/*126 */         if ((res = decode_cdlms(s)) < 0)                                                          // 0.0
/*128 */             return res;                                                                           // 0.0
/*130 */         s->movave_scaling = get_bits(&s->gb, 3);                                                  // 0.0
/*132 */         s->quant_stepsize = get_bits(&s->gb, 8) + 1;                                              // 0.0
/*136 */         reset_codec(s);                                                                           // 0.0
/*138 */     } else if (!s->cdlms[0][0].order) {                                                           // 0.0
/*140 */         av_log(s->avctx, AV_LOG_DEBUG,                                                            // 0.0
/*142 */                "Waiting for seekable tile\n");                                                    // 0.0
/*144 */         s->frame.nb_samples = 0;                                                                  // 0.0
/*146 */         return -1;                                                                                // 0.0
/*148 */     }                                                                                             // 0.0
/*152 */     rawpcm_tile = get_bits1(&s->gb);                                                              // 0.0
/*156 */     for (i = 0; i < s->num_channels; i++)                                                         // 0.0
/*158 */         s->is_channel_coded[i] = 1;                                                               // 0.0
/*162 */     if (!rawpcm_tile) {                                                                           // 0.0
/*164 */         for (i = 0; i < s->num_channels; i++)                                                     // 0.0
/*166 */             s->is_channel_coded[i] = get_bits1(&s->gb);                                           // 0.0
/*170 */         if (s->bV3RTM) {                                                                          // 0.0
/*172 */             // LPC                                                                                // 0.0
/*174 */             s->do_lpc = get_bits1(&s->gb);                                                        // 0.0
/*176 */             if (s->do_lpc) {                                                                      // 0.0
/*178 */                 decode_lpc(s);                                                                    // 0.0
/*180 */                 avpriv_request_sample(s->avctx, "Expect wrong output since "                      // 0.0
/*182 */                                       "inverse LPC filter");                                      // 0.0
/*184 */             }                                                                                     // 0.0
/*186 */         } else                                                                                    // 0.0
/*188 */             s->do_lpc = 0;                                                                        // 0.0
/*190 */     }                                                                                             // 0.0
/*196 */     if (get_bits1(&s->gb))                                                                        // 0.0
/*198 */         padding_zeroes = get_bits(&s->gb, 5);                                                     // 0.0
/*200 */     else                                                                                          // 0.0
/*202 */         padding_zeroes = 0;                                                                       // 0.0
/*206 */     if (rawpcm_tile) {                                                                            // 0.0
/*208 */         int bits = s->bits_per_sample - padding_zeroes;                                           // 0.0
/*210 */         if (bits <= 0) {                                                                          // 0.0
/*212 */             av_log(s->avctx, AV_LOG_ERROR,                                                        // 0.0
/*214 */                    "Invalid number of padding bits in raw PCM tile\n");                           // 0.0
/*216 */             return AVERROR_INVALIDDATA;                                                           // 0.0
/*218 */         }                                                                                         // 0.0
/*220 */         av_dlog(s->avctx, "RAWPCM %d bits per sample. "                                           // 0.0
/*222 */                 "total %d bits, remain=%d\n", bits,                                               // 0.0
/*224 */                 bits * s->num_channels * subframe_len, get_bits_count(&s->gb));                   // 0.0
/*226 */         for (i = 0; i < s->num_channels; i++)                                                     // 0.0
/*228 */             for (j = 0; j < subframe_len; j++)                                                    // 0.0
/*230 */                 s->channel_coeffs[i][j] = get_sbits(&s->gb, bits);                                // 0.0
/*232 */     } else {                                                                                      // 0.0
/*234 */         for (i = 0; i < s->num_channels; i++)                                                     // 0.0
/*236 */             if (s->is_channel_coded[i]) {                                                         // 0.0
/*238 */                 decode_channel_residues(s, i, subframe_len);                                      // 0.0
/*240 */                 if (s->seekable_tile)                                                             // 0.0
/*242 */                     use_high_update_speed(s, i);                                                  // 0.0
/*244 */                 else                                                                              // 0.0
/*246 */                     use_normal_update_speed(s, i);                                                // 0.0
/*248 */                 revert_cdlms(s, i, 0, subframe_len);                                              // 0.0
/*250 */             } else {                                                                              // 0.0
/*252 */                 memset(s->channel_residues[i], 0, sizeof(**s->channel_residues) * subframe_len);  // 0.0
/*254 */             }                                                                                     // 0.0
/*256 */     }                                                                                             // 0.0
/*258 */     if (s->do_mclms)                                                                              // 0.0
/*260 */         revert_mclms(s, subframe_len);                                                            // 0.0
/*262 */     if (s->do_inter_ch_decorr)                                                                    // 0.0
/*264 */         revert_inter_ch_decorr(s, subframe_len);                                                  // 0.0
/*266 */     if (s->do_ac_filter)                                                                          // 0.0
/*268 */         revert_acfilter(s, subframe_len);                                                         // 0.0
/*272 */     /* Dequantize */                                                                              // 0.0
/*274 */     if (s->quant_stepsize != 1)                                                                   // 0.0
/*276 */         for (i = 0; i < s->num_channels; i++)                                                     // 0.0
/*278 */             for (j = 0; j < subframe_len; j++)                                                    // 0.0
/*280 */                 s->channel_residues[i][j] *= s->quant_stepsize;                                   // 0.0
/*284 */     /* Write to proper output buffer depending on bit-depth */                                    // 0.0
/*286 */     for (i = 0; i < s->channels_for_cur_subframe; i++) {                                          // 0.0
/*288 */         int c = s->channel_indexes_for_cur_subframe[i];                                           // 0.0
/*290 */         int subframe_len = s->channel[c].subframe_len[s->channel[c].cur_subframe];                // 0.0
/*294 */         for (j = 0; j < subframe_len; j++) {                                                      // 0.0
/*296 */             if (s->bits_per_sample == 16) {                                                       // 0.0
/*298 */                 *s->samples_16[c]++ = (int16_t) s->channel_residues[c][j] << padding_zeroes;      // 0.0
/*300 */             } else {                                                                              // 0.0
/*302 */                 *s->samples_32[c]++ = s->channel_residues[c][j] << padding_zeroes;                // 0.0
/*304 */             }                                                                                     // 0.0
/*306 */         }                                                                                         // 0.0
/*308 */     }                                                                                             // 0.0
/*312 */     /* handled one subframe */                                                                    // 0.0
/*314 */     for (i = 0; i < s->channels_for_cur_subframe; i++) {                                          // 0.0
/*316 */         int c = s->channel_indexes_for_cur_subframe[i];                                           // 0.0
/*318 */         if (s->channel[c].cur_subframe >= s->channel[c].num_subframes) {                          // 0.0
/*320 */             av_log(s->avctx, AV_LOG_ERROR, "broken subframe\n");                                  // 0.0
/*322 */             return AVERROR_INVALIDDATA;                                                           // 0.0
/*324 */         }                                                                                         // 0.0
/*326 */         ++s->channel[c].cur_subframe;                                                             // 0.0
/*328 */     }                                                                                             // 0.0
/*330 */     return 0;                                                                                     // 0.0
/*332 */ }                                                                                                 // 0.0
