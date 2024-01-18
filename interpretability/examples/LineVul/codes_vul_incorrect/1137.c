// commit message FFmpeg@95801b6a07 (target=1, prob=0.42683843, correct=False): alac : check readsamplesize to ensure get_bits() doesn't fail. Patch by Matthieu Castet <castet.matthieu AT free fr>
/*0   */ static int alac_decode_frame(AVCodecContext *avctx,                                                                      // (7) 0.03516
/*2   */                              void *outbuffer, int *outputsize,                                                           // (1) 0.07422
/*4   */                              const uint8_t *inbuffer, int input_buffer_size)                                             // (0) 0.08594
/*6   */ {                                                                                                                        // (28) 0.001953
/*8   */     ALACContext *alac = avctx->priv_data;                                                                                // (10) 0.0332
/*12  */     int channels;                                                                                                        // (26) 0.01172
/*14  */     unsigned int outputsamples;                                                                                          // (21) 0.01562
/*16  */     int hassize;                                                                                                         // (25) 0.01367
/*18  */     int readsamplesize;                                                                                                  // (22) 0.01562
/*20  */     int wasted_bytes;                                                                                                    // (20) 0.01563
/*22  */     int isnotcompressed;                                                                                                 // (19) 0.01758
/*24  */     uint8_t interlacing_shift;                                                                                           // (15) 0.02539
/*26  */     uint8_t interlacing_leftweight;                                                                                      // (14) 0.02734
/*30  */     /* short-circuit null buffers */                                                                                     // (17) 0.02148
/*32  */     if (!inbuffer || !input_buffer_size)                                                                                 // (12) 0.0293
/*34  */         return input_buffer_size;                                                                                        // (13) 0.02734
/*38  */     /* initialize from the extradata */                                                                                  // (18) 0.01953
/*40  */     if (!alac->context_initialized) {                                                                                    // (16) 0.02539
/*42  */         if (alac->avctx->extradata_size != ALAC_EXTRADATA_SIZE) {                                                        // (4) 0.0625
/*44  */             av_log(avctx, AV_LOG_ERROR, "alac: expected %d extradata bytes\n",                                           // (2) 0.07227
/*46  */                 ALAC_EXTRADATA_SIZE);                                                                                    // (5) 0.04883
/*48  */             return input_buffer_size;                                                                                    // (8) 0.03516
/*50  */         }                                                                                                                // (24) 0.01562
/*52  */         if (alac_set_info(alac)) {                                                                                       // (6) 0.03906
/*54  */             av_log(avctx, AV_LOG_ERROR, "alac: set_info failed\n");                                                      // (3) 0.06836
/*56  */             return input_buffer_size;                                                                                    // (9) 0.03516
/*58  */         }                                                                                                                // (23) 0.01562
/*60  */         alac->context_initialized = 1;                                                                                   // (11) 0.03125
/*62  */     }                                                                                                                    // (27) 0.007812
/*66  */     init_get_bits(&alac->gb, inbuffer, input_buffer_size * 8);                                                           // 0.0
/*70  */     channels = get_bits(&alac->gb, 3) + 1;                                                                               // 0.0
/*72  */     if (channels > MAX_CHANNELS) {                                                                                       // 0.0
/*74  */         av_log(avctx, AV_LOG_ERROR, "channels > %d not supported\n",                                                     // 0.0
/*76  */                MAX_CHANNELS);                                                                                            // 0.0
/*78  */         return input_buffer_size;                                                                                        // 0.0
/*80  */     }                                                                                                                    // 0.0
/*84  */     /* 2^result = something to do with output waiting.                                                                   // 0.0
/*86  */      * perhaps matters if we read > 1 frame in a pass?                                                                   // 0.0
/*88  */      */                                                                                                                  // 0.0
/*90  */     skip_bits(&alac->gb, 4);                                                                                             // 0.0
/*94  */     skip_bits(&alac->gb, 12); /* unknown, skip 12 bits */                                                                // 0.0
/*98  */     /* the output sample size is stored soon */                                                                          // 0.0
/*100 */     hassize = get_bits1(&alac->gb);                                                                                      // 0.0
/*104 */     wasted_bytes = get_bits(&alac->gb, 2); /* unknown ? */                                                               // 0.0
/*108 */     /* whether the frame is compressed */                                                                                // 0.0
/*110 */     isnotcompressed = get_bits1(&alac->gb);                                                                              // 0.0
/*114 */     if (hassize) {                                                                                                       // 0.0
/*116 */         /* now read the number of samples as a 32bit integer */                                                          // 0.0
/*118 */         outputsamples = get_bits_long(&alac->gb, 32);                                                                    // 0.0
/*120 */         if(outputsamples > alac->setinfo_max_samples_per_frame){                                                         // 0.0
/*122 */             av_log(avctx, AV_LOG_ERROR, "outputsamples %d > %d\n", outputsamples, alac->setinfo_max_samples_per_frame);  // 0.0
/*124 */             return -1;                                                                                                   // 0.0
/*126 */         }                                                                                                                // 0.0
/*128 */     } else                                                                                                               // 0.0
/*130 */         outputsamples = alac->setinfo_max_samples_per_frame;                                                             // 0.0
/*134 */     if(outputsamples > *outputsize / alac->bytespersample){                                                              // 0.0
/*136 */         av_log(avctx, AV_LOG_ERROR, "sample buffer too small\n");                                                        // 0.0
/*138 */         return -1;                                                                                                       // 0.0
/*140 */     }                                                                                                                    // 0.0
/*144 */     *outputsize = outputsamples * alac->bytespersample;                                                                  // 0.0
/*146 */     readsamplesize = alac->setinfo_sample_size - (wasted_bytes * 8) + channels - 1;                                      // 0.0
/*150 */     if (!isnotcompressed) {                                                                                              // 0.0
/*152 */         /* so it is compressed */                                                                                        // 0.0
/*154 */         int16_t predictor_coef_table[channels][32];                                                                      // 0.0
/*156 */         int predictor_coef_num[channels];                                                                                // 0.0
/*158 */         int prediction_type[channels];                                                                                   // 0.0
/*160 */         int prediction_quantitization[channels];                                                                         // 0.0
/*162 */         int ricemodifier[channels];                                                                                      // 0.0
/*164 */         int i, chan;                                                                                                     // 0.0
/*168 */         interlacing_shift = get_bits(&alac->gb, 8);                                                                      // 0.0
/*170 */         interlacing_leftweight = get_bits(&alac->gb, 8);                                                                 // 0.0
/*174 */         for (chan = 0; chan < channels; chan++) {                                                                        // 0.0
/*176 */             prediction_type[chan] = get_bits(&alac->gb, 4);                                                              // 0.0
/*178 */             prediction_quantitization[chan] = get_bits(&alac->gb, 4);                                                    // 0.0
/*182 */             ricemodifier[chan] = get_bits(&alac->gb, 3);                                                                 // 0.0
/*184 */             predictor_coef_num[chan] = get_bits(&alac->gb, 5);                                                           // 0.0
/*188 */             /* read the predictor table */                                                                               // 0.0
/*190 */             for (i = 0; i < predictor_coef_num[chan]; i++)                                                               // 0.0
/*192 */                 predictor_coef_table[chan][i] = (int16_t)get_bits(&alac->gb, 16);                                        // 0.0
/*194 */         }                                                                                                                // 0.0
/*198 */         if (wasted_bytes)                                                                                                // 0.0
/*200 */             av_log(avctx, AV_LOG_ERROR, "FIXME: unimplemented, unhandling of wasted_bytes\n");                           // 0.0
/*204 */         for (chan = 0; chan < channels; chan++) {                                                                        // 0.0
/*206 */             bastardized_rice_decompress(alac,                                                                            // 0.0
/*208 */                                         alac->predicterror_buffer[chan],                                                 // 0.0
/*210 */                                         outputsamples,                                                                   // 0.0
/*212 */                                         readsamplesize,                                                                  // 0.0
/*214 */                                         alac->setinfo_rice_initialhistory,                                               // 0.0
/*216 */                                         alac->setinfo_rice_kmodifier,                                                    // 0.0
/*218 */                                         ricemodifier[chan] * alac->setinfo_rice_historymult / 4,                         // 0.0
/*220 */                                         (1 << alac->setinfo_rice_kmodifier) - 1);                                        // 0.0
/*224 */             if (prediction_type[chan] == 0) {                                                                            // 0.0
/*226 */                 /* adaptive fir */                                                                                       // 0.0
/*228 */                 predictor_decompress_fir_adapt(alac->predicterror_buffer[chan],                                          // 0.0
/*230 */                                                alac->outputsamples_buffer[chan],                                         // 0.0
/*232 */                                                outputsamples,                                                            // 0.0
/*234 */                                                readsamplesize,                                                           // 0.0
/*236 */                                                predictor_coef_table[chan],                                               // 0.0
/*238 */                                                predictor_coef_num[chan],                                                 // 0.0
/*240 */                                                prediction_quantitization[chan]);                                         // 0.0
/*242 */             } else {                                                                                                     // 0.0
/*244 */                 av_log(avctx, AV_LOG_ERROR, "FIXME: unhandled prediction type: %i\n", prediction_type[chan]);            // 0.0
/*246 */                 /* I think the only other prediction type (or perhaps this is                                            // 0.0
/*248 */                  * just a boolean?) runs adaptive fir twice.. like:                                                      // 0.0
/*250 */                  * predictor_decompress_fir_adapt(predictor_error, tempout, ...)                                         // 0.0
/*252 */                  * predictor_decompress_fir_adapt(predictor_error, outputsamples ...)                                    // 0.0
/*254 */                  * little strange..                                                                                      // 0.0
/*256 */                  */                                                                                                      // 0.0
/*258 */             }                                                                                                            // 0.0
/*260 */         }                                                                                                                // 0.0
/*262 */     } else {                                                                                                             // 0.0
/*264 */         /* not compressed, easy case */                                                                                  // 0.0
/*266 */         int i, chan;                                                                                                     // 0.0
/*268 */         for (i = 0; i < outputsamples; i++)                                                                              // 0.0
/*270 */             for (chan = 0; chan < channels; chan++) {                                                                    // 0.0
/*272 */                 int32_t audiobits;                                                                                       // 0.0
/*276 */                 audiobits = get_bits_long(&alac->gb, alac->setinfo_sample_size);                                         // 0.0
/*278 */                 audiobits = extend_sign32(audiobits, alac->setinfo_sample_size);                                         // 0.0
/*282 */                 alac->outputsamples_buffer[chan][i] = audiobits;                                                         // 0.0
/*284 */             }                                                                                                            // 0.0
/*286 */         /* wasted_bytes = 0; */                                                                                          // 0.0
/*288 */         interlacing_shift = 0;                                                                                           // 0.0
/*290 */         interlacing_leftweight = 0;                                                                                      // 0.0
/*292 */     }                                                                                                                    // 0.0
/*294 */     if (get_bits(&alac->gb, 3) != 7)                                                                                     // 0.0
/*296 */         av_log(avctx, AV_LOG_ERROR, "Error : Wrong End Of Frame\n");                                                     // 0.0
/*300 */     switch(alac->setinfo_sample_size) {                                                                                  // 0.0
/*302 */     case 16:                                                                                                             // 0.0
/*304 */         if (channels == 2) {                                                                                             // 0.0
/*306 */             reconstruct_stereo_16(alac->outputsamples_buffer,                                                            // 0.0
/*308 */                                   (int16_t*)outbuffer,                                                                   // 0.0
/*310 */                                   alac->numchannels,                                                                     // 0.0
/*312 */                                   outputsamples,                                                                         // 0.0
/*314 */                                   interlacing_shift,                                                                     // 0.0
/*316 */                                   interlacing_leftweight);                                                               // 0.0
/*318 */         } else {                                                                                                         // 0.0
/*320 */             int i;                                                                                                       // 0.0
/*322 */             for (i = 0; i < outputsamples; i++) {                                                                        // 0.0
/*324 */                 int16_t sample = alac->outputsamples_buffer[0][i];                                                       // 0.0
/*326 */                 ((int16_t*)outbuffer)[i * alac->numchannels] = sample;                                                   // 0.0
/*328 */             }                                                                                                            // 0.0
/*330 */         }                                                                                                                // 0.0
/*332 */         break;                                                                                                           // 0.0
/*334 */     case 20:                                                                                                             // 0.0
/*336 */     case 24:                                                                                                             // 0.0
/*338 */         // It is not clear if there exist any encoder that creates 24 bit ALAC                                           // 0.0
/*340 */         // files. iTunes convert 24 bit raw files to 16 bit before encoding.                                             // 0.0
/*342 */     case 32:                                                                                                             // 0.0
/*344 */         av_log(avctx, AV_LOG_ERROR, "FIXME: unimplemented sample size %i\n", alac->setinfo_sample_size);                 // 0.0
/*346 */         break;                                                                                                           // 0.0
/*348 */     default:                                                                                                             // 0.0
/*350 */         break;                                                                                                           // 0.0
/*352 */     }                                                                                                                    // 0.0
/*356 */     if (input_buffer_size * 8 - get_bits_count(&alac->gb) > 8)                                                           // 0.0
/*358 */         av_log(avctx, AV_LOG_ERROR, "Error : %d bits left\n", input_buffer_size * 8 - get_bits_count(&alac->gb));        // 0.0
/*362 */     return input_buffer_size;                                                                                            // 0.0
/*364 */ }                                                                                                                        // 0.0
