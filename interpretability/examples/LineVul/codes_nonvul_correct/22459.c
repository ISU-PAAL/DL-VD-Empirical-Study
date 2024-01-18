// commit message FFmpeg@934fe00680 (target=0, prob=0.2537096, correct=True): ffmpeg: better warning about loop_input
/*0   */ static int opt_input_file(OptionsContext *o, const char *opt, const char *filename)                       // (6) 0.04492
/*2   */ {                                                                                                         // (27) 0.001953
/*4   */     AVFormatContext *ic;                                                                                  // (21) 0.01758
/*6   */     AVInputFormat *file_iformat = NULL;                                                                   // (11) 0.02734
/*8   */     int err, i, ret;                                                                                      // (18) 0.01953
/*10  */     int64_t timestamp;                                                                                    // (22) 0.01758
/*12  */     uint8_t buf[128];                                                                                     // (16) 0.02148
/*14  */     AVDictionary **opts;                                                                                  // (20) 0.01953
/*16  */     int orig_nb_streams;                     // number of streams before avformat_find_stream_info        // (0) 0.08594
/*20  */     if (o->format) {                                                                                      // (19) 0.01953
/*22  */         if (!(file_iformat = av_find_input_format(o->format))) {                                          // (4) 0.05469
/*24  */             av_log(NULL, AV_LOG_FATAL, "Unknown input format: '%s'\n", o->format);                        // (2) 0.08008
/*26  */             exit_program(1);                                                                              // (9) 0.0332
/*28  */         }                                                                                                 // (24) 0.01562
/*30  */     }                                                                                                     // (26) 0.007812
/*34  */     if (!strcmp(filename, "-"))                                                                           // (13) 0.02539
/*36  */         filename = "pipe:";                                                                               // (12) 0.02539
/*40  */     using_stdin |= !strncmp(filename, "pipe:", 5) ||                                                      // (7) 0.04492
/*42  */                     !strcmp(filename, "/dev/stdin");                                                      // (3) 0.06055
/*46  */     /* get default parameters from command line */                                                        // (17) 0.02148
/*48  */     ic = avformat_alloc_context();                                                                        // (15) 0.02344
/*50  */     if (!ic) {                                                                                            // (23) 0.01562
/*52  */         print_error(filename, AVERROR(ENOMEM));                                                           // (8) 0.04102
/*54  */         exit_program(1);                                                                                  // (14) 0.02539
/*56  */     }                                                                                                     // (25) 0.007812
/*58  */     if (o->nb_audio_sample_rate) {                                                                        // (10) 0.03125
/*60  */         snprintf(buf, sizeof(buf), "%d", o->audio_sample_rate[o->nb_audio_sample_rate - 1].u.i);          // (1) 0.08398
/*62  */         av_dict_set(&format_opts, "sample_rate", buf, 0);                                                 // (5) 0.05273
/*64  */     }                                                                                                     // 0.0
/*66  */     if (o->nb_audio_channels) {                                                                           // 0.0
/*68  */         snprintf(buf, sizeof(buf), "%d", o->audio_channels[o->nb_audio_channels - 1].u.i);                // 0.0
/*70  */         av_dict_set(&format_opts, "channels", buf, 0);                                                    // 0.0
/*72  */     }                                                                                                     // 0.0
/*74  */     if (o->nb_frame_rates) {                                                                              // 0.0
/*76  */         av_dict_set(&format_opts, "framerate", o->frame_rates[o->nb_frame_rates - 1].u.str, 0);           // 0.0
/*78  */     }                                                                                                     // 0.0
/*80  */     if (o->nb_frame_sizes) {                                                                              // 0.0
/*82  */         av_dict_set(&format_opts, "video_size", o->frame_sizes[o->nb_frame_sizes - 1].u.str, 0);          // 0.0
/*84  */     }                                                                                                     // 0.0
/*86  */     if (o->nb_frame_pix_fmts)                                                                             // 0.0
/*88  */         av_dict_set(&format_opts, "pixel_format", o->frame_pix_fmts[o->nb_frame_pix_fmts - 1].u.str, 0);  // 0.0
/*92  */     ic->video_codec_id   = video_codec_name ?                                                             // 0.0
/*94  */         find_codec_or_die(video_codec_name   , AVMEDIA_TYPE_VIDEO   , 0)->id : CODEC_ID_NONE;             // 0.0
/*96  */     ic->audio_codec_id   = audio_codec_name ?                                                             // 0.0
/*98  */         find_codec_or_die(audio_codec_name   , AVMEDIA_TYPE_AUDIO   , 0)->id : CODEC_ID_NONE;             // 0.0
/*100 */     ic->subtitle_codec_id= subtitle_codec_name ?                                                          // 0.0
/*102 */         find_codec_or_die(subtitle_codec_name, AVMEDIA_TYPE_SUBTITLE, 0)->id : CODEC_ID_NONE;             // 0.0
/*104 */     ic->flags |= AVFMT_FLAG_NONBLOCK;                                                                     // 0.0
/*106 */     ic->interrupt_callback = int_cb;                                                                      // 0.0
/*110 */     if (loop_input) {                                                                                     // 0.0
/*112 */         av_log(NULL, AV_LOG_WARNING, "-loop_input is deprecated, use -loop 1\n");                         // 0.0
/*114 */         ic->loop_input = loop_input;                                                                      // 0.0
/*116 */     }                                                                                                     // 0.0
/*120 */     /* open the input file with generic avformat function */                                              // 0.0
/*122 */     err = avformat_open_input(&ic, filename, file_iformat, &format_opts);                                 // 0.0
/*124 */     if (err < 0) {                                                                                        // 0.0
/*126 */         print_error(filename, err);                                                                       // 0.0
/*128 */         exit_program(1);                                                                                  // 0.0
/*130 */     }                                                                                                     // 0.0
/*132 */     assert_avoptions(format_opts);                                                                        // 0.0
/*136 */     /* apply forced codec ids */                                                                          // 0.0
/*138 */     for (i = 0; i < ic->nb_streams; i++)                                                                  // 0.0
/*140 */         choose_decoder(o, ic, ic->streams[i]);                                                            // 0.0
/*144 */     /* Set AVCodecContext options for avformat_find_stream_info */                                        // 0.0
/*146 */     opts = setup_find_stream_info_opts(ic, codec_opts);                                                   // 0.0
/*148 */     orig_nb_streams = ic->nb_streams;                                                                     // 0.0
/*152 */     /* If not enough info to get the stream parameters, we decode the                                     // 0.0
/*154 */        first frames to get it. (used in mpeg case for example) */                                         // 0.0
/*156 */     ret = avformat_find_stream_info(ic, opts);                                                            // 0.0
/*158 */     if (ret < 0) {                                                                                        // 0.0
/*160 */         av_log(NULL, AV_LOG_FATAL, "%s: could not find codec parameters\n", filename);                    // 0.0
/*162 */         av_close_input_file(ic);                                                                          // 0.0
/*164 */         exit_program(1);                                                                                  // 0.0
/*166 */     }                                                                                                     // 0.0
/*170 */     timestamp = o->start_time;                                                                            // 0.0
/*172 */     /* add the stream start time */                                                                       // 0.0
/*174 */     if (ic->start_time != AV_NOPTS_VALUE)                                                                 // 0.0
/*176 */         timestamp += ic->start_time;                                                                      // 0.0
/*180 */     /* if seeking requested, we execute it */                                                             // 0.0
/*182 */     if (o->start_time != 0) {                                                                             // 0.0
/*184 */         ret = av_seek_frame(ic, -1, timestamp, AVSEEK_FLAG_BACKWARD);                                     // 0.0
/*186 */         if (ret < 0) {                                                                                    // 0.0
/*188 */             av_log(NULL, AV_LOG_WARNING, "%s: could not seek to position %0.3f\n",                        // 0.0
/*190 */                    filename, (double)timestamp / AV_TIME_BASE);                                           // 0.0
/*192 */         }                                                                                                 // 0.0
/*194 */     }                                                                                                     // 0.0
/*198 */     /* update the current parameters so that they match the one of the input stream */                    // 0.0
/*200 */     add_input_streams(o, ic);                                                                             // 0.0
/*204 */     /* dump the file content */                                                                           // 0.0
/*206 */     av_dump_format(ic, nb_input_files, filename, 0);                                                      // 0.0
/*210 */     input_files = grow_array(input_files, sizeof(*input_files), &nb_input_files, nb_input_files + 1);     // 0.0
/*212 */     input_files[nb_input_files - 1].ctx        = ic;                                                      // 0.0
/*214 */     input_files[nb_input_files - 1].ist_index  = nb_input_streams - ic->nb_streams;                       // 0.0
/*216 */     input_files[nb_input_files - 1].ts_offset  = o->input_ts_offset - (copy_ts ? 0 : timestamp);          // 0.0
/*218 */     input_files[nb_input_files - 1].nb_streams = ic->nb_streams;                                          // 0.0
/*220 */     input_files[nb_input_files - 1].rate_emu   = o->rate_emu;                                             // 0.0
/*224 */     for (i = 0; i < o->nb_dump_attachment; i++) {                                                         // 0.0
/*226 */         int j;                                                                                            // 0.0
/*230 */         for (j = 0; j < ic->nb_streams; j++) {                                                            // 0.0
/*232 */             AVStream *st = ic->streams[j];                                                                // 0.0
/*236 */             if (check_stream_specifier(ic, st, o->dump_attachment[i].specifier) == 1)                     // 0.0
/*238 */                 dump_attachment(st, o->dump_attachment[i].u.str);                                         // 0.0
/*240 */         }                                                                                                 // 0.0
/*242 */     }                                                                                                     // 0.0
/*246 */     for (i = 0; i < orig_nb_streams; i++)                                                                 // 0.0
/*248 */         av_dict_free(&opts[i]);                                                                           // 0.0
/*250 */     av_freep(&opts);                                                                                      // 0.0
/*254 */     reset_options(o, 1);                                                                                  // 0.0
/*256 */     return 0;                                                                                             // 0.0
/*258 */ }                                                                                                         // 0.0
