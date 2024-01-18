// commit message FFmpeg@eef9f06508 (target=0, prob=0.40684664, correct=True): avplay: Allow to override the codec
/*0   */ static int stream_component_open(PlayerState *is, int stream_index)                              // (14) 0.03516
/*2   */ {                                                                                                // (26) 0.001953
/*4   */     AVFormatContext *ic = is->ic;                                                                // (17) 0.02539
/*6   */     AVCodecContext *avctx;                                                                       // (19) 0.02148
/*8   */     AVCodec *codec;                                                                              // (21) 0.01953
/*10  */     SDL_AudioSpec wanted_spec, spec;                                                             // (16) 0.02539
/*12  */     AVDictionary *opts;                                                                          // (22) 0.01953
/*14  */     AVDictionaryEntry *t = NULL;                                                                 // (18) 0.02344
/*16  */     int ret = 0;                                                                                 // (23) 0.01563
/*20  */     if (stream_index < 0 || stream_index >= ic->nb_streams)                                      // (6) 0.04297
/*22  */         return -1;                                                                               // (20) 0.02148
/*24  */     avctx = ic->streams[stream_index]->codec;                                                    // (13) 0.03711
/*28  */     opts = filter_codec_opts(codec_opts, avctx->codec_id, ic, ic->streams[stream_index], NULL);  // (0) 0.08008
/*32  */     codec = avcodec_find_decoder(avctx->codec_id);                                               // (8) 0.04297
/*34  */     avctx->workaround_bugs   = workaround_bugs;                                                  // (15) 0.0332
/*36  */     avctx->idct_algo         = idct;                                                             // (5) 0.04492
/*38  */     avctx->skip_frame        = skip_frame;                                                       // (10) 0.04102
/*40  */     avctx->skip_idct         = skip_idct;                                                        // (4) 0.04687
/*42  */     avctx->skip_loop_filter  = skip_loop_filter;                                                 // (12) 0.03711
/*44  */     avctx->error_concealment = error_concealment;                                                // (11) 0.03906
/*48  */     if (fast)                                                                                    // (25) 0.01367
/*50  */         avctx->flags2 |= AV_CODEC_FLAG2_FAST;                                                    // (2) 0.05078
/*54  */     if (!av_dict_get(opts, "threads", NULL, 0))                                                  // (7) 0.04297
/*56  */         av_dict_set(&opts, "threads", "auto", 0);                                                // (3) 0.04883
/*58  */     if (avctx->codec_type == AVMEDIA_TYPE_VIDEO)                                                 // (9) 0.04102
/*60  */         av_dict_set(&opts, "refcounted_frames", "1", 0);                                         // (1) 0.05469
/*62  */     if (!codec ||                                                                                // (24) 0.01562
/*64  */         (ret = avcodec_open2(avctx, codec, &opts)) < 0) {                                        // 0.0
/*66  */         goto fail;                                                                               // 0.0
/*68  */     }                                                                                            // 0.0
/*70  */     if ((t = av_dict_get(opts, "", NULL, AV_DICT_IGNORE_SUFFIX))) {                              // 0.0
/*72  */         av_log(NULL, AV_LOG_ERROR, "Option %s not found.\n", t->key);                            // 0.0
/*74  */         ret =  AVERROR_OPTION_NOT_FOUND;                                                         // 0.0
/*76  */         goto fail;                                                                               // 0.0
/*78  */     }                                                                                            // 0.0
/*82  */     /* prepare audio output */                                                                   // 0.0
/*84  */     if (avctx->codec_type == AVMEDIA_TYPE_AUDIO) {                                               // 0.0
/*86  */         is->sdl_sample_rate = avctx->sample_rate;                                                // 0.0
/*90  */         if (!avctx->channel_layout)                                                              // 0.0
/*92  */             avctx->channel_layout = av_get_default_channel_layout(avctx->channels);              // 0.0
/*94  */         if (!avctx->channel_layout) {                                                            // 0.0
/*96  */             fprintf(stderr, "unable to guess channel layout\n");                                 // 0.0
/*98  */             ret = AVERROR_INVALIDDATA;                                                           // 0.0
/*100 */             goto fail;                                                                           // 0.0
/*102 */         }                                                                                        // 0.0
/*104 */         if (avctx->channels == 1)                                                                // 0.0
/*106 */             is->sdl_channel_layout = AV_CH_LAYOUT_MONO;                                          // 0.0
/*108 */         else                                                                                     // 0.0
/*110 */             is->sdl_channel_layout = AV_CH_LAYOUT_STEREO;                                        // 0.0
/*112 */         is->sdl_channels = av_get_channel_layout_nb_channels(is->sdl_channel_layout);            // 0.0
/*116 */         wanted_spec.format = AUDIO_S16SYS;                                                       // 0.0
/*118 */         wanted_spec.freq = is->sdl_sample_rate;                                                  // 0.0
/*120 */         wanted_spec.channels = is->sdl_channels;                                                 // 0.0
/*122 */         wanted_spec.silence = 0;                                                                 // 0.0
/*124 */         wanted_spec.samples = SDL_AUDIO_BUFFER_SIZE;                                             // 0.0
/*126 */         wanted_spec.callback = sdl_audio_callback;                                               // 0.0
/*128 */         wanted_spec.userdata = is;                                                               // 0.0
/*130 */         if (SDL_OpenAudio(&wanted_spec, &spec) < 0) {                                            // 0.0
/*132 */             fprintf(stderr, "SDL_OpenAudio: %s\n", SDL_GetError());                              // 0.0
/*134 */             ret = AVERROR_UNKNOWN;                                                               // 0.0
/*136 */             goto fail;                                                                           // 0.0
/*138 */         }                                                                                        // 0.0
/*140 */         is->audio_hw_buf_size = spec.size;                                                       // 0.0
/*142 */         is->sdl_sample_fmt          = AV_SAMPLE_FMT_S16;                                         // 0.0
/*144 */         is->resample_sample_fmt     = is->sdl_sample_fmt;                                        // 0.0
/*146 */         is->resample_channel_layout = avctx->channel_layout;                                     // 0.0
/*148 */         is->resample_sample_rate    = avctx->sample_rate;                                        // 0.0
/*150 */     }                                                                                            // 0.0
/*154 */     ic->streams[stream_index]->discard = AVDISCARD_DEFAULT;                                      // 0.0
/*156 */     switch (avctx->codec_type) {                                                                 // 0.0
/*158 */     case AVMEDIA_TYPE_AUDIO:                                                                     // 0.0
/*160 */         is->audio_stream = stream_index;                                                         // 0.0
/*162 */         is->audio_st = ic->streams[stream_index];                                                // 0.0
/*164 */         is->audio_buf_size  = 0;                                                                 // 0.0
/*166 */         is->audio_buf_index = 0;                                                                 // 0.0
/*170 */         /* init averaging filter */                                                              // 0.0
/*172 */         is->audio_diff_avg_coef  = exp(log(0.01) / AUDIO_DIFF_AVG_NB);                           // 0.0
/*174 */         is->audio_diff_avg_count = 0;                                                            // 0.0
/*176 */         /* since we do not have a precise anough audio fifo fullness,                            // 0.0
/*178 */            we correct audio sync only if larger than this threshold */                           // 0.0
/*180 */         is->audio_diff_threshold = 2.0 * SDL_AUDIO_BUFFER_SIZE / avctx->sample_rate;             // 0.0
/*184 */         memset(&is->audio_pkt, 0, sizeof(is->audio_pkt));                                        // 0.0
/*186 */         packet_queue_init(&is->audioq);                                                          // 0.0
/*188 */         SDL_PauseAudio(0);                                                                       // 0.0
/*190 */         break;                                                                                   // 0.0
/*192 */     case AVMEDIA_TYPE_VIDEO:                                                                     // 0.0
/*194 */         is->video_stream = stream_index;                                                         // 0.0
/*196 */         is->video_st = ic->streams[stream_index];                                                // 0.0
/*200 */         packet_queue_init(&is->videoq);                                                          // 0.0
/*202 */         is->video_tid = SDL_CreateThread(video_thread, is);                                      // 0.0
/*204 */         break;                                                                                   // 0.0
/*206 */     case AVMEDIA_TYPE_SUBTITLE:                                                                  // 0.0
/*208 */         is->subtitle_stream = stream_index;                                                      // 0.0
/*210 */         is->subtitle_st = ic->streams[stream_index];                                             // 0.0
/*212 */         packet_queue_init(&is->subtitleq);                                                       // 0.0
/*216 */         is->subtitle_tid = SDL_CreateThread(subtitle_thread, is);                                // 0.0
/*218 */         break;                                                                                   // 0.0
/*220 */     default:                                                                                     // 0.0
/*222 */         break;                                                                                   // 0.0
/*224 */     }                                                                                            // 0.0
/*228 */ fail:                                                                                            // 0.0
/*230 */     av_dict_free(&opts);                                                                         // 0.0
/*234 */     return ret;                                                                                  // 0.0
/*236 */ }                                                                                                // 0.0
