// commit message FFmpeg@2df0c32ea1 (target=0, prob=0.4545881, correct=True): lavc: use a separate field for exporting audio encoder padding
/*0   */ static int av_cold libopus_encode_init(AVCodecContext *avctx)                                       // (8) 0.04102
/*2   */ {                                                                                                   // (23) 0.001972
/*4   */     LibopusEncContext *opus = avctx->priv_data;                                                     // (14) 0.0332
/*6   */     const uint8_t *channel_mapping;                                                                 // (16) 0.02734
/*8   */     OpusMSEncoder *enc;                                                                             // (21) 0.02148
/*10  */     int ret = OPUS_OK;                                                                              // (20) 0.02148
/*12  */     int coupled_stream_count, header_size, frame_size;                                              // (13) 0.03515
/*16  */     coupled_stream_count = opus_coupled_streams[avctx->channels - 1];                               // (5) 0.05273
/*18  */     opus->stream_count   = avctx->channels - coupled_stream_count;                                  // (6) 0.04687
/*20  */     channel_mapping      = libav_libopus_channel_map[avctx->channels - 1];                          // (3) 0.06054
/*24  */     /* FIXME: Opus can handle up to 255 channels. However, the mapping for                          // (9) 0.04101
/*26  */      * anything greater than 8 is undefined. */                                                     // (18) 0.02539
/*28  */     if (avctx->channels > 8)                                                                        // (19) 0.02539
/*30  */         av_log(avctx, AV_LOG_WARNING,                                                               // (11) 0.03906
/*32  */                "Channel layout undefined for %d channels.\n", avctx->channels);                     // (2) 0.06249
/*36  */     if (!avctx->bit_rate) {                                                                         // (17) 0.02539
/*38  */         /* Sane default copied from opusenc */                                                      // (15) 0.0332
/*40  */         avctx->bit_rate = 64000 * opus->stream_count +                                              // (7) 0.04687
/*42  */                           32000 * coupled_stream_count;                                             // (1) 0.0664
/*44  */         av_log(avctx, AV_LOG_WARNING,                                                               // (10) 0.03906
/*46  */                "No bit rate set. Defaulting to %d bps.\n", avctx->bit_rate);                        // (0) 0.07421
/*48  */     }                                                                                               // (22) 0.007812
/*52  */     if (avctx->bit_rate < 500 || avctx->bit_rate > 256000 * avctx->channels) {                      // (4) 0.06054
/*54  */         av_log(avctx, AV_LOG_ERROR, "The bit rate %d bps is unsupported. "                          // 0.0
/*56  */                "Please choose a value between 500 and %d.\n", avctx->bit_rate,                      // 0.0
/*58  */                256000 * avctx->channels);                                                           // 0.0
/*60  */         return AVERROR(EINVAL);                                                                     // 0.0
/*62  */     }                                                                                               // 0.0
/*66  */     frame_size = opus->opts.frame_duration * 48000 / 1000;                                          // 0.0
/*68  */     switch (frame_size) {                                                                           // 0.0
/*70  */     case 120:                                                                                       // 0.0
/*72  */     case 240:                                                                                       // 0.0
/*74  */         if (opus->opts.application != OPUS_APPLICATION_RESTRICTED_LOWDELAY)                         // 0.0
/*76  */             av_log(avctx, AV_LOG_WARNING,                                                           // 0.0
/*78  */                    "LPC mode cannot be used with a frame duration of less "                         // 0.0
/*80  */                    "than 10ms. Enabling restricted low-delay mode.\n"                               // 0.0
/*82  */                    "Use a longer frame duration if this is not what you want.\n");                  // 0.0
/*84  */         /* Frame sizes less than 10 ms can only use MDCT mode, so switching to                      // 0.0
/*86  */          * RESTRICTED_LOWDELAY avoids an unnecessary extra 2.5ms lookahead. */                      // 0.0
/*88  */         opus->opts.application = OPUS_APPLICATION_RESTRICTED_LOWDELAY;                              // 0.0
/*90  */     case 480:                                                                                       // 0.0
/*92  */     case 960:                                                                                       // 0.0
/*94  */     case 1920:                                                                                      // 0.0
/*96  */     case 2880:                                                                                      // 0.0
/*98  */         opus->opts.packet_size =                                                                    // 0.0
/*100 */         avctx->frame_size      = frame_size * avctx->sample_rate / 48000;                           // 0.0
/*102 */         break;                                                                                      // 0.0
/*104 */     default:                                                                                        // 0.0
/*106 */         av_log(avctx, AV_LOG_ERROR, "Invalid frame duration: %g.\n"                                 // 0.0
/*108 */                "Frame duration must be exactly one of: 2.5, 5, 10, 20, 40 or 60.\n",                // 0.0
/*110 */                opus->opts.frame_duration);                                                          // 0.0
/*112 */         return AVERROR(EINVAL);                                                                     // 0.0
/*114 */     }                                                                                               // 0.0
/*118 */     if (avctx->compression_level < 0 || avctx->compression_level > 10) {                            // 0.0
/*120 */         av_log(avctx, AV_LOG_WARNING,                                                               // 0.0
/*122 */                "Compression level must be in the range 0 to 10. "                                   // 0.0
/*124 */                "Defaulting to 10.\n");                                                              // 0.0
/*126 */         opus->opts.complexity = 10;                                                                 // 0.0
/*128 */     } else {                                                                                        // 0.0
/*130 */         opus->opts.complexity = avctx->compression_level;                                           // 0.0
/*132 */     }                                                                                               // 0.0
/*136 */     if (avctx->cutoff) {                                                                            // 0.0
/*138 */         switch (avctx->cutoff) {                                                                    // 0.0
/*140 */         case  4000:                                                                                 // 0.0
/*142 */             opus->opts.max_bandwidth = OPUS_BANDWIDTH_NARROWBAND;                                   // 0.0
/*144 */             break;                                                                                  // 0.0
/*146 */         case  6000:                                                                                 // 0.0
/*148 */             opus->opts.max_bandwidth = OPUS_BANDWIDTH_MEDIUMBAND;                                   // 0.0
/*150 */             break;                                                                                  // 0.0
/*152 */         case  8000:                                                                                 // 0.0
/*154 */             opus->opts.max_bandwidth = OPUS_BANDWIDTH_WIDEBAND;                                     // 0.0
/*156 */             break;                                                                                  // 0.0
/*158 */         case 12000:                                                                                 // 0.0
/*160 */             opus->opts.max_bandwidth = OPUS_BANDWIDTH_SUPERWIDEBAND;                                // 0.0
/*162 */             break;                                                                                  // 0.0
/*164 */         case 20000:                                                                                 // 0.0
/*166 */             opus->opts.max_bandwidth = OPUS_BANDWIDTH_FULLBAND;                                     // 0.0
/*168 */             break;                                                                                  // 0.0
/*170 */         default:                                                                                    // 0.0
/*172 */             av_log(avctx, AV_LOG_WARNING,                                                           // 0.0
/*174 */                    "Invalid frequency cutoff: %d. Using default maximum bandwidth.\n"               // 0.0
/*176 */                    "Cutoff frequency must be exactly one of: 4000, 6000, 8000, 12000 or 20000.\n",  // 0.0
/*178 */                    avctx->cutoff);                                                                  // 0.0
/*180 */             avctx->cutoff = 0;                                                                      // 0.0
/*182 */         }                                                                                           // 0.0
/*184 */     }                                                                                               // 0.0
/*188 */     enc = opus_multistream_encoder_create(avctx->sample_rate, avctx->channels,                      // 0.0
/*190 */                                           opus->stream_count,                                       // 0.0
/*192 */                                           coupled_stream_count,                                     // 0.0
/*194 */                                           channel_mapping,                                          // 0.0
/*196 */                                           opus->opts.application, &ret);                            // 0.0
/*198 */     if (ret != OPUS_OK) {                                                                           // 0.0
/*200 */         av_log(avctx, AV_LOG_ERROR,                                                                 // (12) 0.03906
/*202 */                "Failed to create encoder: %s\n", opus_strerror(ret));                               // 0.0
/*204 */         return ff_opus_error_to_averror(ret);                                                       // 0.0
/*206 */     }                                                                                               // 0.0
/*210 */     ret = libopus_configure_encoder(avctx, enc, &opus->opts);                                       // 0.0
/*212 */     if (ret != OPUS_OK) {                                                                           // 0.0
/*214 */         ret = ff_opus_error_to_averror(ret);                                                        // 0.0
/*216 */         goto fail;                                                                                  // 0.0
/*218 */     }                                                                                               // 0.0
/*222 */     header_size = 19 + (avctx->channels > 2 ? 2 + avctx->channels : 0);                             // 0.0
/*224 */     avctx->extradata = av_malloc(header_size + FF_INPUT_BUFFER_PADDING_SIZE);                       // 0.0
/*226 */     if (!avctx->extradata) {                                                                        // 0.0
/*228 */         av_log(avctx, AV_LOG_ERROR, "Failed to allocate extradata.\n");                             // 0.0
/*230 */         ret = AVERROR(ENOMEM);                                                                      // 0.0
/*232 */         goto fail;                                                                                  // 0.0
/*234 */     }                                                                                               // 0.0
/*236 */     avctx->extradata_size = header_size;                                                            // 0.0
/*240 */     opus->samples = av_mallocz(frame_size * avctx->channels *                                       // 0.0
/*242 */                                av_get_bytes_per_sample(avctx->sample_fmt));                         // 0.0
/*244 */     if (!opus->samples) {                                                                           // 0.0
/*246 */         av_log(avctx, AV_LOG_ERROR, "Failed to allocate samples buffer.\n");                        // 0.0
/*248 */         ret = AVERROR(ENOMEM);                                                                      // 0.0
/*250 */         goto fail;                                                                                  // 0.0
/*252 */     }                                                                                               // 0.0
/*256 */     ret = opus_multistream_encoder_ctl(enc, OPUS_GET_LOOKAHEAD(&avctx->delay));                     // 0.0
/*258 */     if (ret != OPUS_OK)                                                                             // 0.0
/*260 */         av_log(avctx, AV_LOG_WARNING,                                                               // 0.0
/*262 */                "Unable to get number of lookahead samples: %s\n",                                   // 0.0
/*264 */                opus_strerror(ret));                                                                 // 0.0
/*268 */     libopus_write_header(avctx, opus->stream_count, coupled_stream_count,                           // 0.0
/*270 */                          opus_vorbis_channel_map[avctx->channels - 1]);                             // 0.0
/*274 */     ff_af_queue_init(avctx, &opus->afq);                                                            // 0.0
/*278 */     opus->enc = enc;                                                                                // 0.0
/*282 */     return 0;                                                                                       // 0.0
/*286 */ fail:                                                                                               // 0.0
/*288 */     opus_multistream_encoder_destroy(enc);                                                          // 0.0
/*290 */     av_freep(&avctx->extradata);                                                                    // 0.0
/*292 */     return ret;                                                                                     // 0.0
/*294 */ }                                                                                                   // 0.0
