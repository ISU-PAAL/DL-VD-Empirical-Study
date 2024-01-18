// commit message FFmpeg@2f4233614a (target=0, prob=0.41540217, correct=True): ffserver_config: set defaults basing on absence of set value
/*0   */ static void add_codec(FFServerStream *stream, AVCodecContext *av,                        // (8) 0.03906
/*2   */                       FFServerConfig *config)                                            // (4) 0.05273
/*4   */ {                                                                                        // (25) 0.001954
/*6   */     AVStream *st;                                                                        // (22) 0.01563
/*8   */     AVDictionary **opts, *recommended = NULL;                                            // (14) 0.03125
/*10  */     char *enc_config;                                                                    // (20) 0.01758
/*14  */     if(stream->nb_streams >= FF_ARRAY_ELEMS(stream->streams))                            // (5) 0.05078
/*16  */         return;                                                                          // (21) 0.01758
/*20  */     opts = av->codec_type == AVMEDIA_TYPE_AUDIO ?                                        // (7) 0.04297
/*22  */            &config->audio_opts : &config->video_opts;                                    // (6) 0.05078
/*24  */     av_dict_copy(&recommended, *opts, 0);                                                // (11) 0.03516
/*26  */     av_opt_set_dict2(av->priv_data, opts, AV_OPT_SEARCH_CHILDREN);                       // (1) 0.06641
/*28  */     av_opt_set_dict2(av, opts, AV_OPT_SEARCH_CHILDREN);                                  // (3) 0.05859
/*30  */     if (av_dict_count(*opts))                                                            // (16) 0.02734
/*32  */         av_log(NULL, AV_LOG_WARNING,                                                     // (10) 0.03711
/*34  */                "Something is wrong, %d options are not set!\n", av_dict_count(*opts));   // (0) 0.07422
/*38  */     if (config->stream_use_defaults) {                                                   // (15) 0.0293
/*40  */     //TODO: reident                                                                      // (19) 0.01953
/*42  */     /* compute default parameters */                                                     // (23) 0.01563
/*44  */     switch(av->codec_type) {                                                             // (17) 0.02539
/*46  */     case AVMEDIA_TYPE_AUDIO:                                                             // (18) 0.02539
/*48  */         if (av->bit_rate == 0) {                                                         // (13) 0.03516
/*50  */             av->bit_rate = 64000;                                                        // (9) 0.03906
/*52  */             av_dict_set_int(&recommended, "ab", av->bit_rate, 0);                        // (2) 0.06445
/*54  */         }                                                                                // (24) 0.01562
/*56  */         if (av->sample_rate == 0) {                                                      // (12) 0.03516
/*58  */             av->sample_rate = 22050;                                                     // 0.0
/*60  */             av_dict_set_int(&recommended, "ar", av->sample_rate, 0);                     // 0.0
/*62  */         }                                                                                // 0.0
/*64  */         if (av->channels == 0) {                                                         // 0.0
/*66  */             av->channels = 1;                                                            // 0.0
/*68  */             av_dict_set_int(&recommended, "ac", av->channels, 0);                        // 0.0
/*70  */         }                                                                                // 0.0
/*72  */         break;                                                                           // 0.0
/*74  */     case AVMEDIA_TYPE_VIDEO:                                                             // 0.0
/*76  */         if (av->bit_rate == 0) {                                                         // 0.0
/*78  */             av->bit_rate = 64000;                                                        // 0.0
/*80  */             av_dict_set_int(&recommended, "b", av->bit_rate, 0);                         // 0.0
/*82  */         }                                                                                // 0.0
/*84  */         if (av->time_base.num == 0){                                                     // 0.0
/*86  */             av->time_base.den = 5;                                                       // 0.0
/*88  */             av->time_base.num = 1;                                                       // 0.0
/*90  */             av_dict_set(&recommended, "time_base", "1/5", 0);                            // 0.0
/*92  */         }                                                                                // 0.0
/*94  */         if (av->width == 0 || av->height == 0) {                                         // 0.0
/*96  */             av->width = 160;                                                             // 0.0
/*98  */             av->height = 128;                                                            // 0.0
/*100 */             av_dict_set(&recommended, "video_size", "160x128", 0);                       // 0.0
/*102 */         }                                                                                // 0.0
/*104 */         /* Bitrate tolerance is less for streaming */                                    // 0.0
/*106 */         if (av->bit_rate_tolerance == 0) {                                               // 0.0
/*108 */             av->bit_rate_tolerance = FFMAX(av->bit_rate / 4,                             // 0.0
/*110 */                       (int64_t)av->bit_rate*av->time_base.num/av->time_base.den);        // 0.0
/*112 */             av_dict_set_int(&recommended, "bt", av->bit_rate_tolerance, 0);              // 0.0
/*114 */         }                                                                                // 0.0
/*118 */         if (!av->rc_eq) {                                                                // 0.0
/*120 */             av->rc_eq = av_strdup("tex^qComp");                                          // 0.0
/*122 */             av_dict_set(&recommended, "rc_eq", "tex^qComp", 0);                          // 0.0
/*124 */         }                                                                                // 0.0
/*126 */         if (!av->rc_max_rate) {                                                          // 0.0
/*128 */             av->rc_max_rate = av->bit_rate * 2;                                          // 0.0
/*130 */             av_dict_set_int(&recommended, "maxrate", av->rc_max_rate, 0);                // 0.0
/*132 */         }                                                                                // 0.0
/*136 */         if (av->rc_max_rate && !av->rc_buffer_size) {                                    // 0.0
/*138 */             av->rc_buffer_size = av->rc_max_rate;                                        // 0.0
/*140 */             av_dict_set_int(&recommended, "bufsize", av->rc_buffer_size, 0);             // 0.0
/*142 */         }                                                                                // 0.0
/*144 */         break;                                                                           // 0.0
/*146 */     default:                                                                             // 0.0
/*148 */         abort();                                                                         // 0.0
/*150 */     }                                                                                    // 0.0
/*152 */     } else {                                                                             // 0.0
/*154 */         switch(av->codec_type) {                                                         // 0.0
/*156 */         case AVMEDIA_TYPE_AUDIO:                                                         // 0.0
/*158 */             if (av->bit_rate == 0)                                                       // 0.0
/*160 */                 report_config_error(config->filename, config->line_num, AV_LOG_ERROR,    // 0.0
/*162 */                                     &config->errors, "audio bit rate is not set\n");     // 0.0
/*164 */             if (av->sample_rate == 0)                                                    // 0.0
/*166 */                 report_config_error(config->filename, config->line_num, AV_LOG_ERROR,    // 0.0
/*168 */                                     &config->errors, "audio sample rate is not set\n");  // 0.0
/*170 */             break;                                                                       // 0.0
/*172 */         case AVMEDIA_TYPE_VIDEO:                                                         // 0.0
/*174 */             if (av->width == 0 || av->height == 0)                                       // 0.0
/*176 */                 report_config_error(config->filename, config->line_num, AV_LOG_ERROR,    // 0.0
/*178 */                                     &config->errors, "video size is not set\n");         // 0.0
/*180 */             break;                                                                       // 0.0
/*182 */         default:                                                                         // 0.0
/*184 */             av_assert0(0);                                                               // 0.0
/*186 */         }                                                                                // 0.0
/*188 */     }                                                                                    // 0.0
/*192 */     st = av_mallocz(sizeof(AVStream));                                                   // 0.0
/*194 */     if (!st)                                                                             // 0.0
/*196 */         return;                                                                          // 0.0
/*198 */     av_dict_get_string(recommended, &enc_config, '=', ',');                              // 0.0
/*200 */     av_dict_free(&recommended);                                                          // 0.0
/*202 */     av_stream_set_recommended_encoder_configuration(st, enc_config);                     // 0.0
/*204 */     st->codec = av;                                                                      // 0.0
/*206 */     stream->streams[stream->nb_streams++] = st;                                          // 0.0
/*208 */ }                                                                                        // 0.0
