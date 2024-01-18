// commit message FFmpeg@a1e093a6fb (target=0, prob=0.4575331, correct=True): alac: fix bps check
/*0   */ static int decode_element(AVCodecContext *avctx, void *data, int ch_index,                          // (9) 0.04501
/*2   */                           int channels)                                                             // (3) 0.05469
/*4   */ {                                                                                                   // (25) 0.001954
/*6   */     ALACContext *alac = avctx->priv_data;                                                           // (15) 0.0332
/*8   */     int has_size, bps, is_compressed, decorr_shift, decorr_left_weight, ret;                        // (2) 0.05859
/*10  */     uint32_t output_samples;                                                                        // (18) 0.02343
/*12  */     int i, ch;                                                                                      // (22) 0.01563
/*16  */     skip_bits(&alac->gb, 4);  /* element instance tag */                                            // (10) 0.03906
/*18  */     skip_bits(&alac->gb, 12); /* unused header bits */                                              // (12) 0.0371
/*22  */     /* the number of output samples is stored in the frame */                                       // (17) 0.02929
/*24  */     has_size = get_bits1(&alac->gb);                                                                // (16) 0.0332
/*28  */     alac->extra_bits = get_bits(&alac->gb, 2) << 3;                                                 // (6) 0.04687
/*30  */     bps = alac->sample_size - alac->extra_bits + channels - 1;                                      // (7) 0.04687
/*32  */     if (bps > 32) {                                                                                 // (20) 0.01953
/*34  */         av_log(avctx, AV_LOG_ERROR, "bps is unsupported: %d\n", bps);                               // (0) 0.06444
/*36  */         return AVERROR_PATCHWELCOME;                                                                // (13) 0.0371
/*38  */     }                                                                                               // (23) 0.007811
/*42  */     /* whether the frame is compressed */                                                           // (19) 0.01953
/*44  */     is_compressed = !get_bits1(&alac->gb);                                                          // (11) 0.03711
/*48  */     if (has_size)                                                                                   // (21) 0.01758
/*50  */         output_samples = get_bits_long(&alac->gb, 32);                                              // (5) 0.04882
/*52  */     else                                                                                            // (24) 0.007811
/*54  */         output_samples = alac->max_samples_per_frame;                                               // (8) 0.04687
/*56  */     if (!output_samples || output_samples > alac->max_samples_per_frame) {                          // (4) 0.05468
/*58  */         av_log(avctx, AV_LOG_ERROR, "invalid samples per frame: %d\n",                              // (1) 0.06249
/*60  */                output_samples);                                                                     // (14) 0.0371
/*62  */         return AVERROR_INVALIDDATA;                                                                 // 0.0
/*64  */     }                                                                                               // 0.0
/*66  */     if (!alac->nb_samples) {                                                                        // 0.0
/*68  */         /* get output buffer */                                                                     // 0.0
/*70  */         alac->frame.nb_samples = output_samples;                                                    // 0.0
/*72  */         if ((ret = avctx->get_buffer(avctx, &alac->frame)) < 0) {                                   // 0.0
/*74  */             av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");                                   // 0.0
/*76  */             return ret;                                                                             // 0.0
/*78  */         }                                                                                           // 0.0
/*80  */     } else if (output_samples != alac->nb_samples) {                                                // 0.0
/*82  */         av_log(avctx, AV_LOG_ERROR, "sample count mismatch: %u != %d\n",                            // 0.0
/*84  */                output_samples, alac->nb_samples);                                                   // 0.0
/*86  */         return AVERROR_INVALIDDATA;                                                                 // 0.0
/*88  */     }                                                                                               // 0.0
/*90  */     alac->nb_samples = output_samples;                                                              // 0.0
/*92  */     if (alac->direct_output) {                                                                      // 0.0
/*94  */         for (ch = 0; ch < channels; ch++)                                                           // 0.0
/*96  */             alac->output_samples_buffer[ch] = (int32_t *)alac->frame.extended_data[ch_index + ch];  // 0.0
/*98  */     }                                                                                               // 0.0
/*102 */     if (is_compressed) {                                                                            // 0.0
/*104 */         int16_t lpc_coefs[2][32];                                                                   // 0.0
/*106 */         int lpc_order[2];                                                                           // 0.0
/*108 */         int prediction_type[2];                                                                     // 0.0
/*110 */         int lpc_quant[2];                                                                           // 0.0
/*112 */         int rice_history_mult[2];                                                                   // 0.0
/*116 */         decorr_shift       = get_bits(&alac->gb, 8);                                                // 0.0
/*118 */         decorr_left_weight = get_bits(&alac->gb, 8);                                                // 0.0
/*122 */         for (ch = 0; ch < channels; ch++) {                                                         // 0.0
/*124 */             prediction_type[ch]   = get_bits(&alac->gb, 4);                                         // 0.0
/*126 */             lpc_quant[ch]         = get_bits(&alac->gb, 4);                                         // 0.0
/*128 */             rice_history_mult[ch] = get_bits(&alac->gb, 3);                                         // 0.0
/*130 */             lpc_order[ch]         = get_bits(&alac->gb, 5);                                         // 0.0
/*134 */             /* read the predictor table */                                                          // 0.0
/*136 */             for (i = lpc_order[ch] - 1; i >= 0; i--)                                                // 0.0
/*138 */                 lpc_coefs[ch][i] = get_sbits(&alac->gb, 16);                                        // 0.0
/*140 */         }                                                                                           // 0.0
/*144 */         if (alac->extra_bits) {                                                                     // 0.0
/*146 */             for (i = 0; i < alac->nb_samples; i++) {                                                // 0.0
/*148 */                 if(get_bits_left(&alac->gb) <= 0)                                                   // 0.0
/*150 */                     return -1;                                                                      // 0.0
/*152 */                 for (ch = 0; ch < channels; ch++)                                                   // 0.0
/*154 */                     alac->extra_bits_buffer[ch][i] = get_bits(&alac->gb, alac->extra_bits);         // 0.0
/*156 */             }                                                                                       // 0.0
/*158 */         }                                                                                           // 0.0
/*160 */         for (ch = 0; ch < channels; ch++) {                                                         // 0.0
/*162 */             int ret=rice_decompress(alac, alac->predict_error_buffer[ch],                           // 0.0
/*164 */                             alac->nb_samples, bps,                                                  // 0.0
/*166 */                             rice_history_mult[ch] * alac->rice_history_mult / 4);                   // 0.0
/*168 */             if(ret<0)                                                                               // 0.0
/*170 */                 return ret;                                                                         // 0.0
/*174 */             /* adaptive FIR filter */                                                               // 0.0
/*176 */             if (prediction_type[ch] == 15) {                                                        // 0.0
/*178 */                 /* Prediction type 15 runs the adaptive FIR twice.                                  // 0.0
/*180 */                  * The first pass uses the special-case coef_num = 31, while                        // 0.0
/*182 */                  * the second pass uses the coefs from the bitstream.                               // 0.0
/*184 */                  *                                                                                  // 0.0
/*186 */                  * However, this prediction type is not currently used by the                       // 0.0
/*188 */                  * reference encoder.                                                               // 0.0
/*190 */                  */                                                                                 // 0.0
/*192 */                 lpc_prediction(alac->predict_error_buffer[ch],                                      // 0.0
/*194 */                                alac->predict_error_buffer[ch],                                      // 0.0
/*196 */                                alac->nb_samples, bps, NULL, 31, 0);                                 // 0.0
/*198 */             } else if (prediction_type[ch] > 0) {                                                   // 0.0
/*200 */                 av_log(avctx, AV_LOG_WARNING, "unknown prediction type: %i\n",                      // 0.0
/*202 */                        prediction_type[ch]);                                                        // 0.0
/*204 */             }                                                                                       // 0.0
/*206 */             lpc_prediction(alac->predict_error_buffer[ch],                                          // 0.0
/*208 */                            alac->output_samples_buffer[ch], alac->nb_samples,                       // 0.0
/*210 */                            bps, lpc_coefs[ch], lpc_order[ch], lpc_quant[ch]);                       // 0.0
/*212 */         }                                                                                           // 0.0
/*214 */     } else {                                                                                        // 0.0
/*216 */         /* not compressed, easy case */                                                             // 0.0
/*218 */         for (i = 0; i < alac->nb_samples; i++) {                                                    // 0.0
/*220 */             if(get_bits_left(&alac->gb) <= 0)                                                       // 0.0
/*222 */                 return -1;                                                                          // 0.0
/*224 */             for (ch = 0; ch < channels; ch++) {                                                     // 0.0
/*226 */                 alac->output_samples_buffer[ch][i] =                                                // 0.0
/*228 */                          get_sbits_long(&alac->gb, alac->sample_size);                              // 0.0
/*230 */             }                                                                                       // 0.0
/*232 */         }                                                                                           // 0.0
/*234 */         alac->extra_bits   = 0;                                                                     // 0.0
/*236 */         decorr_shift       = 0;                                                                     // 0.0
/*238 */         decorr_left_weight = 0;                                                                     // 0.0
/*240 */     }                                                                                               // 0.0
/*244 */     if (channels == 2 && decorr_left_weight) {                                                      // 0.0
/*246 */         decorrelate_stereo(alac->output_samples_buffer, alac->nb_samples,                           // 0.0
/*248 */                            decorr_shift, decorr_left_weight);                                       // 0.0
/*250 */     }                                                                                               // 0.0
/*254 */     if (alac->extra_bits) {                                                                         // 0.0
/*256 */         append_extra_bits(alac->output_samples_buffer, alac->extra_bits_buffer,                     // 0.0
/*258 */                           alac->extra_bits, channels, alac->nb_samples);                            // 0.0
/*260 */     }                                                                                               // 0.0
/*264 */     if(av_sample_fmt_is_planar(avctx->sample_fmt)) {                                                // 0.0
/*266 */     switch(alac->sample_size) {                                                                     // 0.0
/*268 */     case 16: {                                                                                      // 0.0
/*270 */         for (ch = 0; ch < channels; ch++) {                                                         // 0.0
/*272 */             int16_t *outbuffer = (int16_t *)alac->frame.extended_data[ch_index + ch];               // 0.0
/*274 */             for (i = 0; i < alac->nb_samples; i++)                                                  // 0.0
/*276 */                 *outbuffer++ = alac->output_samples_buffer[ch][i];                                  // 0.0
/*278 */         }}                                                                                          // 0.0
/*280 */         break;                                                                                      // 0.0
/*282 */     case 24: {                                                                                      // 0.0
/*284 */         for (ch = 0; ch < channels; ch++) {                                                         // 0.0
/*286 */             for (i = 0; i < alac->nb_samples; i++)                                                  // 0.0
/*288 */                 alac->output_samples_buffer[ch][i] <<= 8;                                           // 0.0
/*290 */         }}                                                                                          // 0.0
/*292 */         break;                                                                                      // 0.0
/*294 */     }                                                                                               // 0.0
/*296 */     }else{                                                                                          // 0.0
/*298 */         switch(alac->sample_size) {                                                                 // 0.0
/*300 */         case 16: {                                                                                  // 0.0
/*302 */             int16_t *outbuffer = ((int16_t *)alac->frame.extended_data[0]) + ch_index;              // 0.0
/*304 */             for (i = 0; i < alac->nb_samples; i++) {                                                // 0.0
/*306 */                 for (ch = 0; ch < channels; ch++)                                                   // 0.0
/*308 */                     *outbuffer++ = alac->output_samples_buffer[ch][i];                              // 0.0
/*310 */                 outbuffer += alac->channels - channels;                                             // 0.0
/*312 */             }                                                                                       // 0.0
/*314 */             }                                                                                       // 0.0
/*316 */             break;                                                                                  // 0.0
/*318 */         case 24: {                                                                                  // 0.0
/*320 */             int32_t *outbuffer = ((int32_t *)alac->frame.extended_data[0]) + ch_index;              // 0.0
/*322 */             for (i = 0; i < alac->nb_samples; i++) {                                                // 0.0
/*324 */                 for (ch = 0; ch < channels; ch++)                                                   // 0.0
/*326 */                     *outbuffer++ = alac->output_samples_buffer[ch][i] << 8;                         // 0.0
/*328 */                 outbuffer += alac->channels - channels;                                             // 0.0
/*330 */             }                                                                                       // 0.0
/*332 */             }                                                                                       // 0.0
/*334 */             break;                                                                                  // 0.0
/*336 */         case 32: {                                                                                  // 0.0
/*338 */             int32_t *outbuffer = ((int32_t *)alac->frame.extended_data[0]) + ch_index;              // 0.0
/*340 */             for (i = 0; i < alac->nb_samples; i++) {                                                // 0.0
/*342 */                 for (ch = 0; ch < channels; ch++)                                                   // 0.0
/*344 */                     *outbuffer++ = alac->output_samples_buffer[ch][i];                              // 0.0
/*346 */                 outbuffer += alac->channels - channels;                                             // 0.0
/*348 */             }                                                                                       // 0.0
/*350 */             }                                                                                       // 0.0
/*352 */             break;                                                                                  // 0.0
/*354 */         }                                                                                           // 0.0
/*356 */     }                                                                                               // 0.0
/*360 */     return 0;                                                                                       // 0.0
/*362 */ }                                                                                                   // 0.0
