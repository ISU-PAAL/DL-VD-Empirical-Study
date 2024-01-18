// commit message FFmpeg@f95cfff077 (target=0, prob=0.65795213, correct=False): ffserver_config: check strchr() return for NULL
/*0   */ static int ffserver_save_avoption(const char *opt, const char *arg, int type, FFServerConfig *config)  // (4) 0.05664
/*2   */ {                                                                                                      // (28) 0.001953
/*4   */     static int hinted = 0;                                                                             // (19) 0.01758
/*6   */     int ret = 0;                                                                                       // (24) 0.01562
/*8   */     AVDictionaryEntry *e;                                                                              // (17) 0.01953
/*10  */     const AVOption *o = NULL;                                                                          // (15) 0.02148
/*12  */     const char *option = NULL;                                                                         // (18) 0.01953
/*14  */     const char *codec_name = NULL;                                                                     // (14) 0.02539
/*16  */     char buff[1024];                                                                                   // (23) 0.01562
/*18  */     AVCodecContext *ctx;                                                                               // (16) 0.01953
/*20  */     AVDictionary **dict;                                                                               // (20) 0.01758
/*22  */     enum AVCodecID guessed_codec_id;                                                                   // (12) 0.0293
/*26  */     switch (type) {                                                                                    // (25) 0.01562
/*28  */     case AV_OPT_FLAG_VIDEO_PARAM:                                                                      // (10) 0.03125
/*30  */         ctx = config->dummy_vctx;                                                                      // (5) 0.03516
/*32  */         dict = &config->video_opts;                                                                    // (7) 0.0332
/*34  */         guessed_codec_id = config->guessed_video_codec_id != AV_CODEC_ID_NONE ?                        // (3) 0.07227
/*36  */                            config->guessed_video_codec_id : AV_CODEC_ID_H264;                          // (0) 0.0957
/*38  */         break;                                                                                         // (22) 0.01758
/*40  */     case AV_OPT_FLAG_AUDIO_PARAM:                                                                      // (9) 0.0332
/*42  */         ctx = config->dummy_actx;                                                                      // (6) 0.03516
/*44  */         dict = &config->audio_opts;                                                                    // (8) 0.0332
/*46  */         guessed_codec_id = config->guessed_audio_codec_id != AV_CODEC_ID_NONE ?                        // (2) 0.07227
/*48  */                            config->guessed_audio_codec_id : AV_CODEC_ID_AAC;                           // (1) 0.0957
/*50  */         break;                                                                                         // (21) 0.01758
/*52  */     default:                                                                                           // (26) 0.009766
/*54  */         av_assert0(0);                                                                                 // (13) 0.02734
/*56  */     }                                                                                                  // (27) 0.007812
/*60  */     if (strchr(opt, ':')) {                                                                            // (11) 0.0293
/*62  */         //explicit private option                                                                      // 0.0
/*64  */         snprintf(buff, sizeof(buff), "%s", opt);                                                       // 0.0
/*66  */         codec_name = buff;                                                                             // 0.0
/*68  */         option = strchr(buff, ':');                                                                    // 0.0
/*70  */         buff[option - buff] = '\0';                                                                    // 0.0
/*72  */         option++;                                                                                      // 0.0
/*74  */         if ((ret = ffserver_set_codec(ctx, codec_name, config)) < 0)                                   // 0.0
/*76  */             return ret;                                                                                // 0.0
/*78  */         if (!ctx->codec || !ctx->priv_data)                                                            // 0.0
/*80  */             return -1;                                                                                 // 0.0
/*82  */     } else {                                                                                           // 0.0
/*84  */         option = opt;                                                                                  // 0.0
/*86  */     }                                                                                                  // 0.0
/*90  */     o = av_opt_find(ctx, option, NULL, type | AV_OPT_FLAG_ENCODING_PARAM, AV_OPT_SEARCH_CHILDREN);     // 0.0
/*92  */     if (!o && (!strcmp(option, "time_base")  || !strcmp(option, "pixel_format") ||                     // 0.0
/*94  */                !strcmp(option, "video_size") || !strcmp(option, "codec_tag")))                         // 0.0
/*96  */         o = av_opt_find(ctx, option, NULL, 0, 0);                                                      // 0.0
/*98  */     if (!o) {                                                                                          // 0.0
/*100 */         report_config_error(config->filename, config->line_num, AV_LOG_ERROR,                          // 0.0
/*102 */                             &config->errors, "Option not found: %s\n", opt);                           // 0.0
/*104 */         if (!hinted && ctx->codec_id == AV_CODEC_ID_NONE) {                                            // 0.0
/*106 */             hinted = 1;                                                                                // 0.0
/*108 */             report_config_error(config->filename, config->line_num, AV_LOG_ERROR, NULL,                // 0.0
/*110 */                                 "If '%s' is a codec private option, then prefix it with codec name, "  // 0.0
/*112 */                                 "for example '%s:%s %s' or define codec earlier.\n",                   // 0.0
/*114 */                                 opt, avcodec_get_name(guessed_codec_id) ,opt, arg);                    // 0.0
/*116 */         }                                                                                              // 0.0
/*118 */     } else if ((ret = av_opt_set(ctx, option, arg, AV_OPT_SEARCH_CHILDREN)) < 0) {                     // 0.0
/*120 */         report_config_error(config->filename, config->line_num, AV_LOG_ERROR,                          // 0.0
/*122 */                 &config->errors, "Invalid value for option %s (%s): %s\n", opt,                        // 0.0
/*124 */                 arg, av_err2str(ret));                                                                 // 0.0
/*126 */     } else if ((e = av_dict_get(*dict, option, NULL, 0))) {                                            // 0.0
/*128 */         if ((o->type == AV_OPT_TYPE_FLAGS) && arg && (arg[0] == '+' || arg[0] == '-'))                 // 0.0
/*130 */             return av_dict_set(dict, option, arg, AV_DICT_APPEND);                                     // 0.0
/*132 */         report_config_error(config->filename, config->line_num, AV_LOG_ERROR,                          // 0.0
/*134 */                 &config->errors,                                                                       // 0.0
/*136 */                 "Redeclaring value of the option %s, previous value: %s\n",                            // 0.0
/*138 */                 opt, e->value);                                                                        // 0.0
/*140 */     } else if (av_dict_set(dict, option, arg, 0) < 0) {                                                // 0.0
/*142 */         return AVERROR(ENOMEM);                                                                        // 0.0
/*144 */     }                                                                                                  // 0.0
/*146 */     return 0;                                                                                          // 0.0
/*148 */ }                                                                                                      // 0.0
